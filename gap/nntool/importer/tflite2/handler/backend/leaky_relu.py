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

from graph.types.activations import LeakyActivationParameters
from tflite.LeakyReluOptions import LeakyReluOptions
from ..backend_handler import BackendHandler
from ..handler import tflite_op
from .math_mixin import BasicMathMixin


@tflite_op("LEAKY_RELU")
class LeakyRelu(BasicMathMixin, BackendHandler):

    @classmethod
    def _common(cls, node, **kwargs):
        node_opts = node.get_options(LeakyReluOptions)
        return super(LeakyRelu, cls)._common(
            node,
            params_class=LeakyActivationParameters,
            params_args={'leak_factor': node_opts.Alpha()},
            **kwargs)

    @classmethod
    def version_1(cls, node, **kwargs):
        return cls._common(node, **kwargs)
