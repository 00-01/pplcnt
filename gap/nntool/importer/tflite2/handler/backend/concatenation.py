# Copyright (C) 2020  GreenWaves Technologies, SAS

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.

# You should have received a copy of the GNU Affero General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

from collections import Counter
from functools import reduce

import numpy as np
from graph.dim import Dim
from graph.types import ConcatParameters, ConstantInputParameters, NNEdge
from graph.types.others import CopyParameters, ReshapeParameters
from importer.common.constant_mixin import ConstantMixin
from importer.common.provisional_dim import ProvisionalDim
from importer.tflite2.common import LOG
from importer.tflite2.common.tflite_node import TFLiteNode
from tflite.ConcatenationOptions import \
    ConcatenationOptions
from utils.node_id import NodeId

from ..backend_handler import BackendHandler
from ..handler import tflite_op


@tflite_op("CONCATENATION")
class Concatenation(ConstantMixin, BackendHandler):

    @classmethod
    def _maybe_insert_reshape(cls, G, inp, inp_shape, pout_shape):
        out_dim_none = tuple([idx for idx, dim in enumerate(pout_shape) if dim is None])
        in_dim_none = tuple([idx for idx, dim in enumerate(inp_shape) if dim is None])
        if out_dim_none == in_dim_none:
            return inp[0], inp[1]
        old_shape = [dim for dim in inp_shape if dim is not None]
        new_shape = [dim for idx, dim in enumerate(inp_shape) if dim is not None and idx not in out_dim_none]
        if cls.is_constant(inp):
            val = np.reshape(cls.get_constant(inp), new_shape)
            params = ConstantInputParameters(G.unique_name(inp[0].name), value=val,
                                             dims=Dim.unnamed(val.shape))
        else:
            params = ReshapeParameters(G.unique_name(f'{inp[0].name}_reshape'), old_shape=old_shape, shape=new_shape)
            G.add_edge(NNEdge(from_node=inp[0], to_node=params, from_idx=inp[1]))
        return params, 0

    @classmethod
    def _common(cls, node: TFLiteNode, **kwargs):
        node_opts = node.get_options(ConcatenationOptions)
        G = kwargs['G']
        opts = kwargs['opts']
        all_nodes = kwargs['all_nodes']

        inputs = [all_nodes[t] for t in node.input]
        inp_shapes = [input[2].shape for input in inputs]

        buffer_idxes = [tensor.buffer_idx for tensor in node.input]
        non_zero_idxes = [idx for idx in buffer_idxes if idx != 0]
        duplicates = [idx for idx, count in Counter(non_zero_idxes).items() if count > 1]
        if duplicates:
            LOG.warning(f'concat {node.name} has duplicate inputs. Inserting copies but this is not very efficient.')
            for idx in duplicates:
                dup_idxes = [i for i, x in enumerate(buffer_idxes) if x == idx]
                for dup_idx in dup_idxes[1:]:
                    cparams = CopyParameters(G.unique_name(f'{node.name}_dup_{dup_idxes[0]}_{dup_idx}'))
                    dup_inp = inputs[dup_idx]
                    G.add_edge(NNEdge(from_node=dup_inp[0], from_idx=dup_inp[1], to_node=cparams))
                    inputs[dup_idx] = tuple([cparams, 0] + list(dup_inp[2:]))

        axis = node_opts.Axis()
        if any(inp_shape[axis] is None for inp_shape in inp_shapes):
            raise ValueError("concat on undefined axis in node %s" % node.name)

        def red_func(x, y):
            return y.copy() if x is None else [(elem if y[idx] is not None and elem is not None else None) if idx != axis else elem + y[axis]
                                               for idx, elem in enumerate(x)]

        pout_shape = reduce(red_func, inp_shapes)

        if all(cls.is_constant(inp) for inp in inputs):
            # cls.remove_none_from_constants(inputs, pout_shape)
            LOG.info("reducing %s to a constant", node.name)
            value = np.concatenate([cls.get_constant(inp) for inp in inputs], axis=axis)
            params = ConstantInputParameters(node.name, value=value)
        else:
            axis -= sum(1 if dim is None else 0 for dim in pout_shape[:axis:])
            params = ConcatParameters(node.name, axis=axis, axis_hint=None)

            for idx, inp in enumerate(inputs):
                inp_node, inp_idx = cls._maybe_insert_reshape(G, inp, inp_shapes[idx], pout_shape)
                G.add_edge(NNEdge(from_node=inp_node, to_node=params, from_idx=inp_idx, to_idx=idx))
        if opts.get('load_quantization'):
            G.quantization[NodeId(params)] = cls.load_tf_quantization(node.input, node.output)
        cls.fuse_activation(node_opts, node.name, params, **kwargs)
        all_nodes[node.output[0]] = (params, 0, ProvisionalDim(pout_shape))
        return params

    @classmethod
    def version_1(cls, node: TFLiteNode, **kwargs):
        return cls._common(node, **kwargs)
