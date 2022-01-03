#ifndef __CNN_COPY_GENERATORS_H__
#define __CNN_COPY_GENERATORS_H__
#include <stdint.h>
#include "AutoTilerLib.h"
#include "CNN_Copy_Generators.c"

extern void LoadCNN_Copy_Library();

/** \brief CNN_MatTranspose

        Generator for Matrix Transposition

        Template:
        \param  Name:           Name of the generated user kernel

        \param  Ctrl:           Overide generator default options (TileOrientation, Parallel Features), Def=(TILE_HOR, 1)

        \param  Size:    	1: byte, 2: half word, size of In/Out tensor items

        \param  InFeat          Number of matrices
        \param  Width           For 1x1 convolution, width of an input feature map
        \param  Height          For 1x1 convolution, height of an input feature map

	\parama	MatTransOper    KOP_MATTRANSP

	\param  Signature:	Name(In, Out)
*/

extern int CNN_MatTranspose(
    char *Name,
    CNN_GenControl_T *Ctrl,
    int DataSize,
    int InFeat,
    int Width,
    int Height,
    KernelOper_T MatTransOper
);

#define CNN_MatTranspose_SQ8(__name, __ctrl, __feat, __width, __height, __oper)\
	CNN_MatTranspose(__name, __ctrl, 1, __feat, __width, __height, __oper)

#define CNN_MatTranspose_fp16(__name, __ctrl, __feat, __width, __height, __oper)\
	CNN_MatTranspose(__name, __ctrl, 2, __feat, __width, __height, __oper)


/** \brief CNN_3DTensorPermute
 
        Generator for 3D Tensor permutations:  CHW => {CWH, HWC, WHC, WCH, HCW}, HWC => {HCW, WCH, CWH, CHW, WHC}

        Template:
	\param	Name:           Name of the generated user kernel

	\param	Ctrl:           Overide generator default options

	\param	Size:    	1: byte, 2: half word, size of In/Out tensor items

	\param	InFeat          Number of channels of the tensor
	\param	Width           Tensor width
	\param	Height          Tensor height

	\param	MatPermOper     Permutation oper:  KOP_MATPERM_CHW2CWH, KOP_MATPERM_CHW2HWC, KOP_MATPERM_CHW2WHC, KOP_MATPERM_CHW2WCH, KOP_MATPERM_CHW2HCW
						   KOP_MATPERM_HWC2HCW, KOP_MATPERM_HWC2WCH, KOP_MATPERM_HWC2CWH, KOP_MATPERM_HWC2CHW, KOP_MATPERM_HWC2WHC

	\param  Signature:	Name(In, Out)

*/
extern int CNN_3DTensorPermute(
	char *Name,
	CNN_GenControl_T *Ctrl,
	int Size,
	int InFeat,
	int Width,
	int Height,
 	KernelOper_T MatPermOper
);

#define CNN_3DTensorPermute_SQ8(__name, __ctrl, __feat, __width, __height, __oper) \
	CNN_3DTensorPermute(__name, __ctrl, 1, __feat, __width, __height, __oper)

#define CNN_3DTensorPermute_fp16(__name, __ctrl, __feat, __width, __height, __oper) \
	CNN_3DTensorPermute(__name, __ctrl, 2, __feat, __width, __height, __oper)

extern int CNN_Copy(
	char *Name,
	CNN_GenControl_T *Ctrl,
	int Sz,
	int FeatureSize
);

int CNN_Norm(
	char *Name,
	int Width,
	int Height,
	int DoOffset,
	KernelOper_T kop
);

int CNN_Convert(
	char *Name,
	int In_DataSize,
	int Out_DataSize,
	int Sz,
	KernelOper_T kop
);

#endif
