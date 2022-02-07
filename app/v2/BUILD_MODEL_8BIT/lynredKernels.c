#include "lynredKernels.h"
L1_CL_MEM AT_L1_POINTER lynred_L1_Memory;
L2_MEM AT_L2_POINTER lynred_L2_Memory;
AT_HYPERRAM_POINTER lynred_L3_Memory;
extern AT_HYPERRAM_T HyperRam;
static AT_HYPERFLASH_FS_T HyperFlash;
void S1_Op_input_1_formatter(
		unsigned char * __restrict__ In,
		signed char * __restrict__ Out)

{
	/* Shared L1: 12800 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaW_Evt1;
	KerNormBW_fps_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile0 Dim: 1]
	Ker Arg: In, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 6400 [Tile0, 1:[80x80], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[80x80], 1]
		Tile0: [0, 6400, 6400], Tile1: [0, 6400, 6400], Tile2; [0, 6400, 6400]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 6400 [Tile0, 1:[80x80], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[80x80], 1]
		Tile0: [0, 6400, 6400], Tile1: [0, 6400, 6400], Tile2; [0, 6400, 6400]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (unsigned char *__restrict__) (lynred_L1_Memory+0);
	KerArg0->Out = (signed char *__restrict__) (lynred_L1_Memory+6400);
	KerArg0->W = (unsigned short int) (80);
	KerArg0->H = (unsigned short int) (80);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+0), 6400, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on Tile0 */
		int T0Ind_Last = 1;
		/*====================== Call Kernel LOC_LOOP =========================*/
		AT_FORK(gap_ncore(), (void *) CNN_NormBW_offset_fps, (void *) KerArg0);
		__CALL(CNN_NormBW_offset_fps, KerArg0);
	} /* End iteration on Tile0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+6400), 6400, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S4_Conv2d_32x1x3x3_Relu(
		signed char * __restrict__ In,
		signed char * __restrict__ Filter,
		int * __restrict__ Bias,
		signed char * __restrict__ Out,
		unsigned char * __restrict__ Scale,
		unsigned char * __restrict__ ScaleN,
		signed char * __restrict__ Infos)

{
	/* Shared L1: 48652 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaR_Evt4;
	AT_L2_EVENT DmaR_Evt5;
	AT_L2_EVENT DmaR_Evt6;
	AT_L2_EVENT DmaW_Evt1;
	KerSetBias_SQ8_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerConv_SQ8_T S_KerArg1, *KerArg1 = &S_KerArg1;
	KerConvLinReduct_SQ8_T S_KerArg2, *KerArg2 = &S_KerArg2;

	/* Iteration space related variables */
	int D1Ind, D1Ind_Last;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast;
	int D0Ind, D0Ind_Last;
	/* User kernel arguments related variables */
	unsigned int _C_Out;
	unsigned int _SP_Out, _SC_Out;
	unsigned int _LP_Out, _LC_Out;
	unsigned int _N_In;
	unsigned int _SN_In;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 32, Tiled: 1][Tile0 Dim: 7][D0 Dim: Init: 1, Tiled: 1]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 7 logical tiles, 7 physical tiles
			Total Size: 51200 [D1, [0 x 51200, 51200]][Tile0, 7:[40x6, 5:40x6, 40x4], 1]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 51200, 51200]][Tile0, 7:[40x6, 5:40x6, 40x4], 1]
		Tile0: [0, 7680, 240], Tile1: [240, 7680, 240], Tile2; [480, 7680, 240]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 128 [D1, [0 x 128, 128]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 128, 128]]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Scale, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 32 [D1, [0 x 32, 32]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 32, 32]]
		Tile0: [0, 32, 32], Tile1: [0, 32, 32], Tile2; [0, 32, 32]
	Ker Arg: ScaleN, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 32 [D1, [0 x 32, 32]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 32, 32]]
		Tile0: [0, 32, 32], Tile1: [0, 32, 32], Tile2; [0, 32, 32]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 288 [D1, [0 x 288, 288]][D0, [0 x 288, 288]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 288, 288]][D0, [0 x 288, 288]]
		Tile0: [0, 288, 288], Tile1: [0, 288, 288], Tile2; [0, 288, 288]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 7 logical tiles, 7 physical tiles
			Total Size: 6400 [D0, [0 x 6400, 6400]][Tile0, 7:[80x13, 5:80x13, 80x8], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 7:[80x12], 1][D0, [0 x 6400, 6400]]
		Tile0: [0, 1040, 1040], Tile1: [960, 1040, 1040], Tile2; [1920, 1040, 1040]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 7 logical tiles, 1 physical tiles
			Total Size: 204800 [D1, [0 x 204800, 204800]][Tile0, 7:[40x6, 5:40x6, 40x4], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [0 x 204800, 204800]][Tile0, 7:[40x6, 5:40x6, 40x4], 4]
		Tile0: [0, 30720, 960], Tile1: [0, 30720, 960], Tile2; [0, 30720, 960]
	Ker Arg: Infos, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 7 logical tiles, 1 physical tiles
			Total Size: 9 [Tile0, 7:[9x1, 5:9x1, 9x1], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 7:[9x1, 5:9x1, 9x1], 1]
		Tile0: [0, 9, 9], Tile1: [0, 9, 9], Tile2; [0, 9, 9]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (lynred_L1_Memory+17920);
	KerArg0->W = (unsigned short int) (40);
	KerArg0->Feat = (unsigned short int) (32);
	KerArg0->Bias = (void * __restrict__) (lynred_L1_Memory+2080);
	KerArg1->W = (unsigned short int) (80);
	KerArg1->UsedW = (unsigned short int) (80);
	KerArg1->InFeatures = (unsigned short int) (1);
	KerArg1->OutFeatures = (unsigned short int) (32);
	KerArg1->TotalInFeatures = (unsigned short int) (1);
	KerArg1->Filter = (signed char * __restrict__) (lynred_L1_Memory+2272);
	KerArg1->Out = (int * __restrict__) (lynred_L1_Memory+17920);
	KerArg2->In = (int *__restrict__) (lynred_L1_Memory+17920);
	KerArg2->Feat = (unsigned short int) (32);
	KerArg2->W = (unsigned short int) (40);
	KerArg2->Scale = (unsigned char *__restrict__) (lynred_L1_Memory+2208);
	KerArg2->ScaleN = (unsigned char *__restrict__) (lynred_L1_Memory+2240);
	KerArg2->Infos = (signed char *__restrict__) (lynred_L1_Memory+48640);
	/*================================= Read Tiles Prolog ===============================*/
	_C_Out=0; _SC_Out=7680; _LC_Out=240;
	_SP_Out=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+2080), 128, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Scale+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+2208), 32, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Scale */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) ScaleN+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+2240), 32, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read ScaleN */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+2272), 288, 0, &DmaR_Evt4);
	AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read Filter */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+0+0), 1040, 0, &DmaR_Evt5);
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Infos+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+48640), 9, 0, &DmaR_Evt6);
	AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Infos */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D1 */
		int D1Ind_Last = 1;
		for (T0Ind=0; T0Ind<7; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==6), T0Ind_NextLast = ((T0Ind+1)==6);
			/*================================= Prepare Tiles ===================================*/
			_SN_In = 0;
			if (!(T0Ind_Last)) {
				_N_In = _N_In + (960); _SN_In = (1*((T0Ind_NextLast)?640:1040)); 
			} else if (!(1)) {
				_N_In = _N_In + (-5760); _SN_In = (1*(1040)); 
			}
			/*============================= End Prepare Tiles ===================================*/
			/*================================= Read Tiles ======================================*/
			AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read In */
			if (_SN_In) {
				AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+0+1040*((T0Ind_Total+1)%2)),
						_SN_In, 0, &DmaR_Evt5);
			}
			/*============================= End Read Tiles ======================================*/
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->H = (unsigned short int) (T0Ind_Last?4:6);
			KerArg0->NormBias = (unsigned char) (((char *)(lynred_L1_Memory+48640))[5]);
			AT_FORK(gap_ncore(), (void *) KerParSetBiasB32_SQ8, (void *) KerArg0);
			__CALL(KerParSetBiasB32_SQ8, KerArg0);
			{ /* Single iteration on D0 */
				int D0Ind_Last = 1;
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (signed char * __restrict__) (lynred_L1_Memory+0+1040*((T0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (((T0Ind_Last)?8:13)-0*(T0Ind==0));
				KerArg1->UsedH = (unsigned short int) (((T0Ind_Last)?8:13)-0*(T0Ind==0));
				KerArg1->Pad = (v4s) ((v4s){0,1,0*(T0Ind==0),1*(T0Ind_Last)});
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride2_SQ8, (void *) KerArg1);
				__CALL(KerParConv3x3Stride2_SQ8, KerArg1);
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->Out = (void *__restrict__) (lynred_L1_Memory+2560+7680*((T0Ind_Total)%2));
			KerArg2->H = (unsigned short int) (T0Ind_Last?4:6);
			AT_FORK(gap_ncore(), (void *) KerParReduct_CC_ReLU_SQ8, (void *) KerArg2);
			__CALL(KerParReduct_CC_ReLU_SQ8, KerArg2);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+2560+7680*((T0Ind_Total)%2)),
					_SC_Out, 1600, _LC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (240); _LC_Out = ((T0Ind_NextLast)?160:240); _SC_Out = (32*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S7_Conv2d_32x1x3x3_Relu(
		signed char * __restrict__ In,
		signed char * __restrict__ Filter,
		int * __restrict__ Bias,
		signed char * __restrict__ Out,
		unsigned char * __restrict__ Scale,
		unsigned char * __restrict__ ScaleN,
		signed char * __restrict__ Infos)

{
	/* Shared L1: 47852 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaR_Evt4;
	AT_L2_EVENT DmaR_Evt5;
	AT_L2_EVENT DmaR_Evt6;
	AT_L2_EVENT DmaW_Evt1;
	KerConv_SQ8_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerConvLinReduct_SQ8_T S_KerArg1, *KerArg1 = &S_KerArg1;

	/* Iteration space related variables */
	int D0Ind, D0Ind_Last, D0Ind_NextLast;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast;
	/* User kernel arguments related variables */
	unsigned int _N_In;
	unsigned int _SN_In;
	unsigned int _LN_In;
	unsigned int _C_Out;
	unsigned int _SP_Out, _SC_Out;
	unsigned int _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D0 Dim: Init: 32, Tiled: 4][Tile0 Dim: 3]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 12 logical tiles, 12 physical tiles
			Total Size: 51200 [D0, [3 x 12800, 12800]][Tile0, 3:[40x19, 1:40x20, 40x5], 1]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [3 x 12800, 12800]][Tile0, 3:[40x19, 1:40x20, 40x5], 1]
		Tile0: [0, 6080, 760], Tile1: [680, 6400, 800], Tile2; [1400, 1600, 200]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 4 logical tiles, 1 physical tiles
			Total Size: 128 [D0, [3 x 32, 32]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [3 x 32, 32]]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Scale, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 4 logical tiles, 1 physical tiles
			Total Size: 32 [D0, [3 x 8, 8]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [3 x 8, 8]]
		Tile0: [0, 32, 32], Tile1: [0, 32, 32], Tile2; [0, 32, 32]
	Ker Arg: ScaleN, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 4 logical tiles, 1 physical tiles
			Total Size: 32 [D0, [3 x 8, 8]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [3 x 8, 8]]
		Tile0: [0, 32, 32], Tile1: [0, 32, 32], Tile2; [0, 32, 32]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 4 logical tiles, 1 physical tiles
			Total Size: 288 [D0, [3 x 72, 72]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [3 x 72, 72]]
		Tile0: [0, 288, 288], Tile1: [0, 288, 288], Tile2; [0, 288, 288]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 12 logical tiles, 12 physical tiles
			Total Size: 51200 [D0, [3 x 12800, 12800]][Tile0, 3:[40x18, 1:40x18, 40x4], 1]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [3 x 12800, 12800]][Tile0, 3:[40x18, 1:40x18, 40x4], 1]
		Tile0: [0, 5760, 720], Tile1: [720, 5760, 720], Tile2; [1440, 1280, 160]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 12 logical tiles, 1 physical tiles
			Total Size: 204800 [D0, [3 x 51200, 51200]][Tile0, 3:[40x18, 1:40x18, 40x4], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [3 x 51200, 51200]][Tile0, 3:[40x18, 1:40x18, 40x4], 4]
		Tile0: [0, 23040, 2880], Tile1: [0, 23040, 2880], Tile2; [0, 23040, 2880]
	Ker Arg: Infos, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 3 logical tiles, 1 physical tiles
			Total Size: 9 [Tile0, 3:[9x1, 1:9x1, 9x1], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 3:[9x1, 1:9x1, 9x1], 1]
		Tile0: [0, 9, 9], Tile1: [0, 9, 9], Tile2; [0, 9, 9]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->W = (unsigned short int) (40);
	KerArg0->UsedW = (unsigned short int) (40);
	KerArg0->InFeatures = (unsigned short int) (8);
	KerArg0->OutFeatures = (unsigned short int) (8);
	KerArg0->TotalInFeatures = (unsigned short int) (32);
	KerArg0->Out = (int * __restrict__) (lynred_L1_Memory+24800);
	KerArg1->In = (int *__restrict__) (lynred_L1_Memory+24800);
	KerArg1->Feat = (unsigned short int) (8);
	KerArg1->W = (unsigned short int) (40);
	KerArg1->Infos = (signed char *__restrict__) (lynred_L1_Memory+47840);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+0+0), 6080, 1600, 760, 0, &DmaR_Evt1);
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+12800), 128, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Scale+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+12928), 32, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Scale */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) ScaleN+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+12960), 32, 0, &DmaR_Evt4);
	AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read ScaleN */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+12992), 288, 0, &DmaR_Evt5);
	AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read Filter */
	_C_Out=0; _SC_Out=5760; _LC_Out=720;
	_SP_Out=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Infos+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+47840), 9, 0, &DmaR_Evt6);
	AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Infos */
	/*============================= End Read Tiles Prolog ===============================*/
	for (D0Ind=0; D0Ind<4; D0Ind++) { /* Iteration on D0 */
		int D0Ind_Last = (D0Ind==3), D0Ind_NextLast = ((D0Ind+1)==3);
		for (T0Ind=0; T0Ind<3; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==2), T0Ind_NextLast = ((T0Ind+1)==2);
			/*================================= Prepare Tiles ===================================*/
			_SN_In = 0;
			if (!(T0Ind_Last)) {
				_N_In = _N_In + (720-(40*(T0Ind==0))); _LN_In = ((T0Ind_NextLast)?200:800); _SN_In = (8*_LN_In); 
			} else if (!(D0Ind_Last)) {
				_N_In = _N_In + (12800)+(-1400); _LN_In = (760); _SN_In = (8*_LN_In); 
			}
			/*============================= End Prepare Tiles ===================================*/
			/*================================= Read Tiles ======================================*/
			AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
			if (_SN_In) {
				AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+0+6400*((T0Ind_Total+1)%2)),
						_SN_In, 1600, _LN_In, 0, &DmaR_Evt1);
			}
			/*============================= End Read Tiles ======================================*/
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->In = (signed char * __restrict__) (lynred_L1_Memory+0+6400*((T0Ind_Total)%2));
			KerArg0->H = (unsigned short int) (((T0Ind_Last)?5:20)-1*(T0Ind==0));
			KerArg0->UsedH = (unsigned short int) (((T0Ind_Last)?5:20)-1*(T0Ind==0));
			KerArg0->Filter = (signed char * __restrict__) (lynred_L1_Memory+12992+((D0Ind)*72));
			KerArg0->Bias = (signed char * __restrict__) (lynred_L1_Memory+12800+((D0Ind)*32));
			KerArg0->Pad = (v4s) ((v4s){1,1,1*(T0Ind==0),1*(T0Ind_Last)});
			KerArg0->NormBias = (unsigned char) (((char *)(lynred_L1_Memory+47840))[5]);
			AT_FORK(gap_ncore(), (void *) KerParConvDW3x3Stride1B32_SQ8, (void *) KerArg0);
			__CALL(KerParConvDW3x3Stride1B32_SQ8, KerArg0);
			KerArg1->Out = (void *__restrict__) (lynred_L1_Memory+13280+5760*((T0Ind_Total)%2));
			KerArg1->H = (unsigned short int) (T0Ind_Last?4:18);
			KerArg1->Scale = (unsigned char *__restrict__) (lynred_L1_Memory+12928+((D0Ind)*8));
			KerArg1->ScaleN = (unsigned char *__restrict__) (lynred_L1_Memory+12960+((D0Ind)*8));
			AT_FORK(gap_ncore(), (void *) KerParReduct_CC_ReLU_SQ8, (void *) KerArg1);
			__CALL(KerParReduct_CC_ReLU_SQ8, KerArg1);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+13280+5760*((T0Ind_Total)%2)),
					_SC_Out, 1600, _LC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (720); _LC_Out = ((T0Ind_NextLast)?160:720); _SC_Out = (8*_LC_Out); 
			} else if (!(D0Ind_Last)) {
				_C_Out = _C_Out + (12800)+(-1440); _LC_Out = (720); _SC_Out = (8*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
	} /* End iteration on D0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S10_Conv2d_24x32x1x1(
		signed char * __restrict__ In2,
		signed char * __restrict__ In1,
		int * __restrict__ Bias,
		signed char * __restrict__ Out,
		unsigned char * __restrict__ Scale,
		unsigned char * __restrict__ ScaleN,
		signed char * __restrict__ Infos)

{
	/* Shared L1: 49308 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaR_Evt4;
	AT_L2_EVENT DmaR_Evt5;
	AT_L2_EVENT DmaR_Evt6;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF1;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF2;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF3;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF4;
	KerMatTranspose_fps_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerMatMul_SQ8_T S_KerArg1, *KerArg1 = &S_KerArg1;

	/* Iteration space related variables */
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast;
	/* User kernel arguments related variables */
	unsigned int _N_In2;
	unsigned int _SN_In2;
	unsigned int _LN_In2;
	unsigned int _C_Out;
	unsigned int _SP_Out, _SC_Out;
	unsigned int _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile0 Dim: 5]
	Ker Arg: In2, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 5 logical tiles, 5 physical tiles
			Total Size: 51200 [Tile0, 5:[32x336, 3:32x336, 32x256], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 5:[32x336, 3:32x336, 32x256], 1]
		Tile0: [0, 10752, 336], Tile1: [336, 10752, 336], Tile2; [672, 10752, 336]
	Ker Arg: In1, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 5 logical tiles, 1 physical tiles
			Total Size: 768 [Tile0, 5:[24x32, 3:24x32, 24x32], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 5:[24x32, 3:24x32, 24x32], 1]
		Tile0: [0, 768, 768], Tile1: [0, 768, 768], Tile2; [0, 768, 768]
	Ker Arg: TransIn2, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 5 logical tiles, 1 physical tiles
			Total Size: 51200 [Tile0, 5:[32x336, 3:32x336, 32x256], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 5:[32x336, 3:32x336, 32x256], 1]
		Tile0: [0, 10752, 336], Tile1: [0, 10752, 336], Tile2; [0, 10752, 336]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 5 logical tiles, 1 physical tiles
			Total Size: 96 [Tile0, 5:[24x1, 3:24x1, 24x1], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 5:[24x1, 3:24x1, 24x1], 4]
		Tile0: [0, 96, 96], Tile1: [0, 96, 96], Tile2; [0, 96, 96]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 5 logical tiles, 5 physical tiles
			Total Size: 38400 [Tile0, 5:[24x336, 3:24x336, 24x256], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 5:[24x336, 3:24x336, 24x256], 1]
		Tile0: [0, 8064, 336], Tile1: [336, 8064, 336], Tile2; [672, 8064, 336]
	Ker Arg: Scale, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 5 logical tiles, 1 physical tiles
			Total Size: 24 [Tile0, 5:[24x1, 3:24x1, 24x1], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 5:[24x1, 3:24x1, 24x1], 1]
		Tile0: [0, 24, 24], Tile1: [0, 24, 24], Tile2; [0, 24, 24]
	Ker Arg: ScaleN, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 5 logical tiles, 1 physical tiles
			Total Size: 24 [Tile0, 5:[24x1, 3:24x1, 24x1], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 5:[24x1, 3:24x1, 24x1], 1]
		Tile0: [0, 24, 24], Tile1: [0, 24, 24], Tile2; [0, 24, 24]
	Ker Arg: Infos, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 5 logical tiles, 1 physical tiles
			Total Size: 9 [Tile0, 5:[1x1, 3:1x1, 1x1], 9]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 5:[1x1, 3:1x1, 1x1], 9]
		Tile0: [0, 9, 9], Tile1: [0, 9, 9], Tile2; [0, 9, 9]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (signed char *__restrict__) (lynred_L1_Memory+22272);
	KerArg0->Feat = (unsigned short int) (1);
	KerArg0->H = (unsigned short int) (32);
	KerArg1->In1 = (signed char * __restrict__) (lynred_L1_Memory+0);
	KerArg1->W_In1 = (unsigned short int) (32);
	KerArg1->H_In1 = (unsigned short int) (24);
	KerArg1->In2 = (signed char * __restrict__) (lynred_L1_Memory+22272);
	KerArg1->Bias = (void * __restrict__) (lynred_L1_Memory+33024);
	KerArg1->Scale = (unsigned char * __restrict__) (lynred_L1_Memory+49248);
	KerArg1->ScaleN = (unsigned char * __restrict__) (lynred_L1_Memory+49272);
	KerArg1->Infos = (signed char *__restrict__) (lynred_L1_Memory+49296);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In2+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+768+0), 10752, 1600, 336, 0, &DmaR_Evt1);
	_N_In2=0;
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) In1+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+139492+0), 768, 0, &UchanHF1);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1); /* Wait previous uDMA read In1 */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+139492+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+0), 768, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read In1 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Bias+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+140836+0), 96, 0, &UchanHF2);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF2); /* Wait previous uDMA read Bias */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+140836+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+33024), 96, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Bias */
	_C_Out=0; _SC_Out=8064; _LC_Out=336;
	_SP_Out=0;
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Scale+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+140932+0), 24, 0, &UchanHF3);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF3); /* Wait previous uDMA read Scale */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+140932+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+49248), 24, 0, &DmaR_Evt4);
	AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read Scale */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) ScaleN+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+140956+0), 24, 0, &UchanHF4);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF4); /* Wait previous uDMA read ScaleN */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+140956+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+49272), 24, 0, &DmaR_Evt5);
	AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read ScaleN */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Infos+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+49296), 9, 0, &DmaR_Evt6);
	AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Infos */
	/*============================= End Read Tiles Prolog ===============================*/
	for (T0Ind=0; T0Ind<5; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
		int T0Ind_Last = (T0Ind==4), T0Ind_NextLast = ((T0Ind+1)==4);
		/*================================= Prepare Tiles ===================================*/
		_SN_In2 = 0;
		if (!(T0Ind_Last)) {
			_N_In2 = _N_In2 + (336); _LN_In2 = ((T0Ind_NextLast)?256:336); _SN_In2 = (32*_LN_In2); 
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In2 */
		if (_SN_In2) {
			AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In2+_N_In2), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+768+10752*((T0Ind_Total+1)%2)),
					_SN_In2, 1600, _LN_In2, 0, &DmaR_Evt1);
		}
		/*============================= End Read Tiles ======================================*/
		/*====================== Call Kernel LOC_LOOP =========================*/
		KerArg0->In = (signed char *__restrict__) (lynred_L1_Memory+768+10752*((T0Ind_Total)%2));
		KerArg0->W = (unsigned short int) ((T0Ind_Last)?256:336);
		AT_FORK(gap_ncore(), (void *) CNN_Transpose_fps, (void *) KerArg0);
		__CALL(CNN_Transpose_fps, KerArg0);
		KerArg1->W_In2 = (unsigned short int) ((T0Ind_Last)?256:336);
		KerArg1->Out = (signed char * __restrict__) (lynred_L1_Memory+33120+8064*((T0Ind_Total)%2));
		KerArg1->NormBias = (unsigned char) (((char *)(lynred_L1_Memory+49296))[5]);
		AT_FORK(gap_ncore(), (void *) KerParMatMulB32_SF_SQ8, (void *) KerArg1);
		__CALL(KerParMatMulB32_SF_SQ8, KerArg1);
		/*================================= Write Tiles =====================================*/
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
		AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+33120+8064*((T0Ind_Total)%2)),
				_SC_Out, 1600, _LC_Out, 1, &DmaW_Evt1);
		/*============================= End Write Tiles =====================================*/
		/*================================= Update Arg Pipeline =============================*/
		_SP_Out = _SC_Out;_LP_Out = _LC_Out;
		/*============================= End Update Arg Pipeline =============================*/
		/*================================= Prepare Tiles ===================================*/
		_SC_Out = 0;
		if (!(T0Ind_Last)) {
			_C_Out = _C_Out + (336); _LC_Out = ((T0Ind_NextLast)?256:336); _SC_Out = (24*_LC_Out); 
		}
		/*============================= End Prepare Tiles ===================================*/
	} /* End iteration on Tile0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S13_Conv2d_144x24x1x1_Relu(
		signed char * __restrict__ In2,
		signed char * __restrict__ In1,
		int * __restrict__ Bias,
		signed char * __restrict__ Out,
		unsigned char * __restrict__ Scale,
		unsigned char * __restrict__ ScaleN,
		signed char * __restrict__ Infos)

{
	/* Shared L1: 46092 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaR_Evt4;
	AT_L2_EVENT DmaR_Evt5;
	AT_L2_EVENT DmaR_Evt6;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR4;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF1;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF2;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF3;
	KerMatMul_SQ8_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T1Ind, T1Ind_Total=0, T1Ind_Last, T1Ind_NextLast;
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	unsigned int _N_In2;
	unsigned int _SN_In2;
	unsigned int _LN_In2;
	unsigned int _P_Out, _C_Out;
	unsigned int _SPP_Out, _SP_Out, _SC_Out;
	unsigned int _LPP_Out, _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile1 Dim: 13][Tile0 Dim: 1]
	Ker Arg: In2, Tiled Space: Tile1
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 13 logical tiles, 13 physical tiles
			Total Size: 38400 [Tile1, 13:[24x124, 11:24x124, 24x112], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 13:[24x124, 11:24x124, 24x112], 1]
		Tile0: [0, 2976, 124], Tile1: [124, 2976, 124], Tile2; [248, 2976, 124]
	Ker Arg: In1, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 3456 [Tile0, 1:[24x144], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[24x144], 1]
		Tile0: [0, 3456, 3456], Tile1: [0, 3456, 3456], Tile2; [0, 3456, 3456]
	Ker Arg: KerBuff, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 13 logical tiles, 1 physical tiles
			Total Size: 96 [Tile1, 13:[96x1, 11:96x1, 96x1], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 13:[96x1, 11:96x1, 96x1], 1]
		Tile0: [0, 96, 96], Tile1: [0, 96, 96], Tile2; [0, 96, 96]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 576 [Tile0, 1:[1x144], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x144], 4]
		Tile0: [0, 576, 576], Tile1: [0, 576, 576], Tile2; [0, 576, 576]
	Ker Arg: Out, Tiled Space: Tile1
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 13 logical tiles, 13 physical tiles
			Total Size: 230400 [Tile1, 13:[144x124, 11:144x124, 144x112], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 13:[144x124, 11:144x124, 144x112], 1]
		Tile0: [0, 17856, 124], Tile1: [124, 17856, 124], Tile2; [248, 17856, 124]
	Ker Arg: Scale, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 144 [Tile0, 1:[1x144], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x144], 1]
		Tile0: [0, 144, 144], Tile1: [0, 144, 144], Tile2; [0, 144, 144]
	Ker Arg: ScaleN, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 144 [Tile0, 1:[1x144], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x144], 1]
		Tile0: [0, 144, 144], Tile1: [0, 144, 144], Tile2; [0, 144, 144]
	Ker Arg: Infos, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 13 logical tiles, 1 physical tiles
			Total Size: 9 [Tile1, 13:[1x1, 11:1x1, 1x1], 9]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 13:[1x1, 11:1x1, 1x1], 9]
		Tile0: [0, 9, 9], Tile1: [0, 9, 9], Tile2; [0, 9, 9]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In1 = (signed char * __restrict__) (lynred_L1_Memory+41772);
	KerArg0->W_In1 = (unsigned short int) (24);
	KerArg0->H_In1 = (unsigned short int) (144);
	KerArg0->Bias = (void * __restrict__) (lynred_L1_Memory+45228);
	KerArg0->Scale = (unsigned char * __restrict__) (lynred_L1_Memory+45804);
	KerArg0->ScaleN = (unsigned char * __restrict__) (lynred_L1_Memory+45948);
	KerArg0->BufferColIn2 = (signed char * __restrict__) (lynred_L1_Memory+0);
	KerArg0->ColFirst = (unsigned char) (1);
	KerArg0->Infos = (signed char *__restrict__) (lynred_L1_Memory+41760);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In2+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+96+0), 2976, 1600, 124, 0, &DmaR_Evt1);
	_N_In2=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In1+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+41772), 3456, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read In1 */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+45228), 576, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Bias */
	_C_Out=0; _SC_Out=17856; _LC_Out=124;
	_SPP_Out=0; _SP_Out=0;
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Scale+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+84020+0), 144, 0, &UchanHF1);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1); /* Wait previous uDMA read Scale */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+84020+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+45804), 144, 0, &DmaR_Evt4);
	AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read Scale */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) ScaleN+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+84164+0), 144, 0, &UchanHF2);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF2); /* Wait previous uDMA read ScaleN */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+84164+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+45948), 144, 0, &DmaR_Evt5);
	AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read ScaleN */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Infos+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+84308+0), 9, 0, &UchanHF3);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF3); /* Wait previous uDMA read Infos */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+84308+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+41760), 9, 0, &DmaR_Evt6);
	AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Infos */
	/*============================= End Read Tiles Prolog ===============================*/
	for (T1Ind=0; T1Ind<13; T1Ind++, T1Ind_Total++) { /* Iteration on Tile1 */
		int T1Ind_Last = (T1Ind==12), T1Ind_NextLast = ((T1Ind+1)==12);
		/*================================= Prepare Tiles ===================================*/
		_SN_In2 = 0;
		if (!(T1Ind_Last)) {
			_N_In2 = _N_In2 + (124); _LN_In2 = ((T1Ind_NextLast)?112:124); _SN_In2 = (24*_LN_In2); 
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In2 */
		if (_SN_In2) {
			AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In2+_N_In2), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+96+2976*((T1Ind_Total+1)%2)),
					_SN_In2, 1600, _LN_In2, 0, &DmaR_Evt1);
		}
		/*============================= End Read Tiles ======================================*/
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1;
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->In2 = (signed char * __restrict__) (lynred_L1_Memory+96+2976*((T1Ind_Total)%2));
			KerArg0->W_In2 = (unsigned short int) ((T1Ind_Last)?112:124);
			KerArg0->Out = (signed char * __restrict__) (lynred_L1_Memory+6048+17856*((T1Ind_Total)%2));
			KerArg0->W_Out = (unsigned short int) ((T1Ind_Last)?112:124);
			KerArg0->OutFirstCol = (unsigned short int) ((0)*144);
			KerArg0->NormBias = (unsigned char) (((char *)(lynred_L1_Memory+41760))[5]);
			AT_FORK(gap_ncore(), (void *) KerParMatMulB32_2x4_ReLU_SQ8, (void *) KerArg0);
			__CALL(KerParMatMulB32_2x4_ReLU_SQ8, KerArg0);
		} /* End iteration on Tile0 */
		/*================================= Write Tiles =====================================*/
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
		if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR4); /* Wait previous uDMA write Out */
		if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+17856*((T1Ind_Total+-1)%2)),
					_SP_Out, 1600, _LP_Out, 1, &UchanHR4);
		AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+17856*((T1Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+6048+17856*((T1Ind_Total)%2)),
				_SC_Out, 1, &DmaW_Evt1);
		/*============================= End Write Tiles =====================================*/
		/*================================= Update Arg Pipeline =============================*/
		_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
		_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
		/*============================= End Update Arg Pipeline =============================*/
		/*================================= Prepare Tiles ===================================*/
		_SC_Out = 0;
		if (!(T1Ind_Last)) {
			_C_Out = _C_Out + (124); _LC_Out = ((T1Ind_NextLast)?112:124); _SC_Out = (144*_LC_Out); 
		}
		/*============================= End Prepare Tiles ===================================*/
	} /* End iteration on Tile1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR4); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+17856*((T1Ind_Total+-1)%2)), _SP_Out, 1600, _LP_Out, 1, &UchanHR4);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR4); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S16_Conv2d_144x1x3x3_Relu(
		signed char * __restrict__ In,
		signed char * __restrict__ Filter,
		int * __restrict__ Bias,
		signed char * __restrict__ Out,
		unsigned char * __restrict__ Scale,
		unsigned char * __restrict__ ScaleN,
		signed char * __restrict__ Infos)

{
	/* Shared L1: 49532 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaR_Evt4;
	AT_L2_EVENT DmaR_Evt5;
	AT_L2_EVENT DmaR_Evt6;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF2;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF3;
	AT_HYPERRAM_CL_EVENT UchanHR5;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF4;
	KerConv_SQ8_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerConvLinReduct_SQ8_T S_KerArg1, *KerArg1 = &S_KerArg1;

	/* Iteration space related variables */
	int D0Ind, D0Ind_Last, D0Ind_NextLast, D0Ind_NextNextLast;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast, T0Ind_NextNextLast;
	/* User kernel arguments related variables */
	unsigned int _NN_In;
	unsigned int _SN_In, _SNN_In;
	unsigned int _LN_In, _LNN_In;
	unsigned int _P_Out, _C_Out;
	unsigned int _SPP_Out, _SP_Out, _SC_Out;
	unsigned int _LPP_Out, _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D0 Dim: Init: 144, Tiled: 18][Tile0 Dim: 3]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 54 logical tiles, 54 physical tiles
			Total Size: 230400 [D0, [17 x 12800, 12800]][Tile0, 3:[40x19, 1:40x20, 40x5], 1]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [17 x 12800, 12800]][Tile0, 3:[40x19, 1:40x20, 40x5], 1]
		Tile0: [0, 6080, 760], Tile1: [680, 6400, 800], Tile2; [1400, 1600, 200]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 18 logical tiles, 1 physical tiles
			Total Size: 576 [D0, [17 x 32, 32]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [17 x 32, 32]]
		Tile0: [0, 576, 576], Tile1: [0, 576, 576], Tile2; [0, 576, 576]
	Ker Arg: Scale, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 18 logical tiles, 1 physical tiles
			Total Size: 144 [D0, [17 x 8, 8]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [17 x 8, 8]]
		Tile0: [0, 144, 144], Tile1: [0, 144, 144], Tile2; [0, 144, 144]
	Ker Arg: ScaleN, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 18 logical tiles, 1 physical tiles
			Total Size: 144 [D0, [17 x 8, 8]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [17 x 8, 8]]
		Tile0: [0, 144, 144], Tile1: [0, 144, 144], Tile2; [0, 144, 144]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 18 logical tiles, 1 physical tiles
			Total Size: 1296 [D0, [17 x 72, 72]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [17 x 72, 72]]
		Tile0: [0, 1296, 1296], Tile1: [0, 1296, 1296], Tile2; [0, 1296, 1296]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 54 logical tiles, 54 physical tiles
			Total Size: 230400 [D0, [17 x 12800, 12800]][Tile0, 3:[40x18, 1:40x18, 40x4], 1]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [17 x 12800, 12800]][Tile0, 3:[40x18, 1:40x18, 40x4], 1]
		Tile0: [0, 5760, 720], Tile1: [720, 5760, 720], Tile2; [1440, 1280, 160]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 54 logical tiles, 1 physical tiles
			Total Size: 921600 [D0, [17 x 51200, 51200]][Tile0, 3:[40x18, 1:40x18, 40x4], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [17 x 51200, 51200]][Tile0, 3:[40x18, 1:40x18, 40x4], 4]
		Tile0: [0, 23040, 2880], Tile1: [0, 23040, 2880], Tile2; [0, 23040, 2880]
	Ker Arg: Infos, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 3 logical tiles, 1 physical tiles
			Total Size: 9 [Tile0, 3:[9x1, 1:9x1, 9x1], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 3:[9x1, 1:9x1, 9x1], 1]
		Tile0: [0, 9, 9], Tile1: [0, 9, 9], Tile2; [0, 9, 9]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->W = (unsigned short int) (40);
	KerArg0->UsedW = (unsigned short int) (40);
	KerArg0->InFeatures = (unsigned short int) (8);
	KerArg0->OutFeatures = (unsigned short int) (8);
	KerArg0->TotalInFeatures = (unsigned short int) (144);
	KerArg0->Out = (int * __restrict__) (lynred_L1_Memory+26480);
	KerArg1->In = (int *__restrict__) (lynred_L1_Memory+26480);
	KerArg1->Feat = (unsigned short int) (8);
	KerArg1->W = (unsigned short int) (40);
	KerArg1->Infos = (signed char *__restrict__) (lynred_L1_Memory+49520);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+57956+0), 6080, 1600, 760, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+680), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+57956+6400), 6400, 1600, 800, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+57956+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+0+0), 6080, 0, &DmaR_Evt1);
	_NN_In=680; _SN_In=6400;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+12800), 576, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Scale+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+70756+0), 144, 0, &UchanHF2);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF2); /* Wait previous uDMA read Scale */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+70756+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+13376), 144, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Scale */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) ScaleN+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+70900+0), 144, 0, &UchanHF3);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF3); /* Wait previous uDMA read ScaleN */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+70900+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+13520), 144, 0, &DmaR_Evt4);
	AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read ScaleN */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+13664), 1296, 0, &DmaR_Evt5);
	AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read Filter */
	_C_Out=0; _SC_Out=5760; _LC_Out=720;
	_SPP_Out=0; _SP_Out=0;
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Infos+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+71044+0), 9, 0, &UchanHF4);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF4); /* Wait previous uDMA read Infos */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+71044+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+49520), 9, 0, &DmaR_Evt6);
	AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Infos */
	/*============================= End Read Tiles Prolog ===============================*/
	for (D0Ind=0; D0Ind<18; D0Ind++) { /* Iteration on D0 */
		int D0Ind_Last = (D0Ind==17), D0Ind_NextLast = ((D0Ind+1)==17), D0Ind_NextNextLast = ((D0Ind+2)==17);
		for (T0Ind=0; T0Ind<3; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==2), T0Ind_NextLast = ((T0Ind+1)==2), T0Ind_NextNextLast = ((T0Ind+2)==2);
			/*================================= Prepare Tiles ===================================*/
			_SNN_In = 0;
			if (!(T0Ind_Last)) {
				if (!(T0Ind_NextLast)) {
					_NN_In = _NN_In + (720); _LNN_In = ((1)?200:800); _SNN_In = (8*_LNN_In); 
				} else if (!(D0Ind_Last)) {
					_NN_In = _NN_In + (12800)+(-1400); _LNN_In = (760); _SNN_In = (8*_LNN_In); 
				}
			} else if (!(D0Ind_Last)) {
				_NN_In = _NN_In + (720-40); _LNN_In = (800); _SNN_In = (8*_LNN_In); 
			}
			/*============================= End Prepare Tiles ===================================*/
			/*================================= Read Tiles ======================================*/
			AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
			if (_SNN_In) {
				AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+_NN_In), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+57956+6400*((T0Ind_Total)%2)),
						_SNN_In, 1600, _LNN_In, 0, &UchanHR1);
			}
			AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
			if (_SN_In) {
				AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+57956+6400*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+0+6400*((T0Ind_Total+1)%2)),
						_SN_In, 0, &DmaR_Evt1);
			}
			/*============================= End Read Tiles ======================================*/
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->In = (signed char * __restrict__) (lynred_L1_Memory+0+6400*((T0Ind_Total)%2));
			KerArg0->H = (unsigned short int) (((T0Ind_Last)?5:20)-1*(T0Ind==0));
			KerArg0->UsedH = (unsigned short int) (((T0Ind_Last)?5:20)-1*(T0Ind==0));
			KerArg0->Filter = (signed char * __restrict__) (lynred_L1_Memory+13664+((D0Ind)*72));
			KerArg0->Bias = (signed char * __restrict__) (lynred_L1_Memory+12800+((D0Ind)*32));
			KerArg0->Pad = (v4s) ((v4s){1,1,1*(T0Ind==0),1*(T0Ind_Last)});
			KerArg0->NormBias = (unsigned char) (((char *)(lynred_L1_Memory+49520))[5]);
			AT_FORK(gap_ncore(), (void *) KerParConvDW3x3Stride1B32_SQ8, (void *) KerArg0);
			__CALL(KerParConvDW3x3Stride1B32_SQ8, KerArg0);
			KerArg1->Out = (void *__restrict__) (lynred_L1_Memory+14960+5760*((T0Ind_Total)%2));
			KerArg1->H = (unsigned short int) (T0Ind_Last?4:18);
			KerArg1->Scale = (unsigned char *__restrict__) (lynred_L1_Memory+13376+((D0Ind)*8));
			KerArg1->ScaleN = (unsigned char *__restrict__) (lynred_L1_Memory+13520+((D0Ind)*8));
			AT_FORK(gap_ncore(), (void *) KerParReduct_CC_ReLU_SQ8, (void *) KerArg1);
			__CALL(KerParReduct_CC_ReLU_SQ8, KerArg1);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR5); /* Wait previous uDMA write Out */
			if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+5760*((T0Ind_Total+-1)%2)),
						_SP_Out, 1600, _LP_Out, 1, &UchanHR5);
			AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+5760*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+14960+5760*((T0Ind_Total)%2)),
					_SC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SN_In = _SNN_In;_LN_In = _LNN_In;
			_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
			_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (720); _LC_Out = ((T0Ind_NextLast)?160:720); _SC_Out = (8*_LC_Out); 
			} else if (!(D0Ind_Last)) {
				_C_Out = _C_Out + (12800)+(-1440); _LC_Out = (720); _SC_Out = (8*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
	} /* End iteration on D0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR5); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+5760*((T0Ind_Total+-1)%2)), _SP_Out, 1600, _LP_Out, 1, &UchanHR5);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR5); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S19_Conv2d_32x144x1x1(
		signed char * __restrict__ In2,
		signed char * __restrict__ In1,
		int * __restrict__ Bias,
		signed char * __restrict__ Out,
		unsigned char * __restrict__ Scale,
		unsigned char * __restrict__ ScaleN,
		signed char * __restrict__ Infos)

{
	/* Shared L1: 44812 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaR_Evt4;
	AT_L2_EVENT DmaR_Evt5;
	AT_L2_EVENT DmaR_Evt6;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	AT_HYPERRAM_CL_EVENT UchanHR2;
	KerMatMul_SQ8_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T1Ind, T1Ind_Total=0, T1Ind_Last, T1Ind_NextLast, T1Ind_NextNextLast;
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	unsigned int _NN_In2;
	unsigned int _SN_In2, _SNN_In2;
	unsigned int _LN_In2, _LNN_In2;
	unsigned int _P_Out, _C_Out;
	unsigned int _SPP_Out, _SP_Out, _SC_Out;
	unsigned int _LPP_Out, _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile1 Dim: 15][Tile0 Dim: 1]
	Ker Arg: In2, Tiled Space: Tile1
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 15 logical tiles, 15 physical tiles
			Total Size: 230400 [Tile1, 15:[144x112, 13:144x112, 144x32], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 15:[144x112, 13:144x112, 144x32], 1]
		Tile0: [0, 16128, 112], Tile1: [112, 16128, 112], Tile2; [224, 16128, 112]
	Ker Arg: In1, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 4608 [Tile0, 1:[144x32], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[144x32], 1]
		Tile0: [0, 4608, 4608], Tile1: [0, 4608, 4608], Tile2; [0, 4608, 4608]
	Ker Arg: KerBuff, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 15 logical tiles, 1 physical tiles
			Total Size: 576 [Tile1, 15:[576x1, 13:576x1, 576x1], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 15:[576x1, 13:576x1, 576x1], 1]
		Tile0: [0, 576, 576], Tile1: [0, 576, 576], Tile2; [0, 576, 576]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 128 [Tile0, 1:[1x32], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x32], 4]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Out, Tiled Space: Tile1
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 15 logical tiles, 15 physical tiles
			Total Size: 51200 [Tile1, 15:[32x112, 13:32x112, 32x32], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 15:[32x112, 13:32x112, 32x32], 1]
		Tile0: [0, 3584, 112], Tile1: [112, 3584, 112], Tile2; [224, 3584, 112]
	Ker Arg: Scale, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 32 [Tile0, 1:[1x32], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x32], 1]
		Tile0: [0, 32, 32], Tile1: [0, 32, 32], Tile2; [0, 32, 32]
	Ker Arg: ScaleN, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 32 [Tile0, 1:[1x32], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x32], 1]
		Tile0: [0, 32, 32], Tile1: [0, 32, 32], Tile2; [0, 32, 32]
	Ker Arg: Infos, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 15 logical tiles, 1 physical tiles
			Total Size: 9 [Tile1, 15:[1x1, 13:1x1, 1x1], 9]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 15:[1x1, 13:1x1, 1x1], 9]
		Tile0: [0, 9, 9], Tile1: [0, 9, 9], Tile2; [0, 9, 9]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In1 = (signed char * __restrict__) (lynred_L1_Memory+40012);
	KerArg0->W_In1 = (unsigned short int) (144);
	KerArg0->H_In1 = (unsigned short int) (32);
	KerArg0->Bias = (void * __restrict__) (lynred_L1_Memory+44620);
	KerArg0->Scale = (unsigned char * __restrict__) (lynred_L1_Memory+44748);
	KerArg0->ScaleN = (unsigned char * __restrict__) (lynred_L1_Memory+44780);
	KerArg0->BufferColIn2 = (signed char * __restrict__) (lynred_L1_Memory+0);
	KerArg0->ColFirst = (unsigned char) (1);
	KerArg0->Infos = (signed char *__restrict__) (lynred_L1_Memory+40000);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+0), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), 16128, 1600, 112, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In2 */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+112), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+16128), 16128, 1600, 112, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+576+0), 16128, 0, &DmaR_Evt1);
	_NN_In2=112; _SN_In2=16128;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In1+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+40012), 4608, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read In1 */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+44620), 128, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Bias */
	_C_Out=0; _SC_Out=3584; _LC_Out=112;
	_SPP_Out=0; _SP_Out=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Scale+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+44748), 32, 0, &DmaR_Evt4);
	AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read Scale */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) ScaleN+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+44780), 32, 0, &DmaR_Evt5);
	AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read ScaleN */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Infos+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+40000), 9, 0, &DmaR_Evt6);
	AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Infos */
	/*============================= End Read Tiles Prolog ===============================*/
	for (T1Ind=0; T1Ind<15; T1Ind++, T1Ind_Total++) { /* Iteration on Tile1 */
		int T1Ind_Last = (T1Ind==14), T1Ind_NextLast = ((T1Ind+1)==14), T1Ind_NextNextLast = ((T1Ind+2)==14);
		/*================================= Prepare Tiles ===================================*/
		_SNN_In2 = 0;
		if (!(T1Ind_Last)) {
			if (!(T1Ind_NextLast)) {
				_NN_In2 = _NN_In2 + (112); _LNN_In2 = ((T1Ind_NextNextLast)?32:112); _SNN_In2 = (144*_LNN_In2); 
			}
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In2 */
		if (_SNN_In2) {
			AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+_NN_In2), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+16128*((T1Ind_Total)%2)),
					_SNN_In2, 1600, _LNN_In2, 0, &UchanHR1);
		}
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In2 */
		if (_SN_In2) {
			AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+16128*((T1Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+576+16128*((T1Ind_Total+1)%2)),
					_SN_In2, 0, &DmaR_Evt1);
		}
		/*============================= End Read Tiles ======================================*/
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1;
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->In2 = (signed char * __restrict__) (lynred_L1_Memory+576+16128*((T1Ind_Total)%2));
			KerArg0->W_In2 = (unsigned short int) ((T1Ind_Last)?32:112);
			KerArg0->Out = (signed char * __restrict__) (lynred_L1_Memory+32832+3584*((T1Ind_Total)%2));
			KerArg0->W_Out = (unsigned short int) ((T1Ind_Last)?32:112);
			KerArg0->OutFirstCol = (unsigned short int) ((0)*32);
			KerArg0->NormBias = (unsigned char) (((char *)(lynred_L1_Memory+40000))[5]);
			AT_FORK(gap_ncore(), (void *) KerParMatMulB32_2x4_SQ8, (void *) KerArg0);
			__CALL(KerParMatMulB32_2x4_SQ8, KerArg0);
		} /* End iteration on Tile0 */
		/*================================= Write Tiles =====================================*/
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
		if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
		if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+78692+3584*((T1Ind_Total+-1)%2)),
					_SP_Out, 1600, _LP_Out, 1, &UchanHR2);
		AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+78692+3584*((T1Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+32832+3584*((T1Ind_Total)%2)),
				_SC_Out, 1, &DmaW_Evt1);
		/*============================= End Write Tiles =====================================*/
		/*================================= Update Arg Pipeline =============================*/
		_SN_In2 = _SNN_In2;_LN_In2 = _LNN_In2;
		_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
		_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
		/*============================= End Update Arg Pipeline =============================*/
		/*================================= Prepare Tiles ===================================*/
		_SC_Out = 0;
		if (!(T1Ind_Last)) {
			_C_Out = _C_Out + (112); _LC_Out = ((T1Ind_NextLast)?32:112); _SC_Out = (32*_LC_Out); 
		}
		/*============================= End Prepare Tiles ===================================*/
	} /* End iteration on Tile1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+78692+3584*((T1Ind_Total+-1)%2)), _SP_Out, 1600, _LP_Out, 1, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S22_Conv2d_192x32x1x1_Relu(
		signed char * __restrict__ In2,
		signed char * __restrict__ In1,
		int * __restrict__ Bias,
		signed char * __restrict__ Out,
		unsigned char * __restrict__ Scale,
		unsigned char * __restrict__ ScaleN,
		signed char * __restrict__ Infos)

{
	/* Shared L1: 43276 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaR_Evt4;
	AT_L2_EVENT DmaR_Evt5;
	AT_L2_EVENT DmaR_Evt6;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	AT_HYPERRAM_CL_EVENT UchanHR2;
	KerMatMul_SQ8_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T1Ind, T1Ind_Total=0, T1Ind_Last, T1Ind_NextLast, T1Ind_NextNextLast;
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	unsigned int _NN_In2;
	unsigned int _SN_In2, _SNN_In2;
	unsigned int _LN_In2, _LNN_In2;
	unsigned int _P_Out, _C_Out;
	unsigned int _SPP_Out, _SP_Out, _SC_Out;
	unsigned int _LPP_Out, _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile1 Dim: 20][Tile0 Dim: 1]
	Ker Arg: In2, Tiled Space: Tile1
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 20 logical tiles, 20 physical tiles
			Total Size: 51200 [Tile1, 20:[32x80, 18:32x80, 32x80], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 20:[32x80, 18:32x80, 32x80], 1]
		Tile0: [0, 2560, 80], Tile1: [80, 2560, 80], Tile2; [160, 2560, 80]
	Ker Arg: In1, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 6144 [Tile0, 1:[32x192], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[32x192], 1]
		Tile0: [0, 6144, 6144], Tile1: [0, 6144, 6144], Tile2; [0, 6144, 6144]
	Ker Arg: KerBuff, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 20 logical tiles, 1 physical tiles
			Total Size: 128 [Tile1, 20:[128x1, 18:128x1, 128x1], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 20:[128x1, 18:128x1, 128x1], 1]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 768 [Tile0, 1:[1x192], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x192], 4]
		Tile0: [0, 768, 768], Tile1: [0, 768, 768], Tile2; [0, 768, 768]
	Ker Arg: Out, Tiled Space: Tile1
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 20 logical tiles, 20 physical tiles
			Total Size: 307200 [Tile1, 20:[192x80, 18:192x80, 192x80], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 20:[192x80, 18:192x80, 192x80], 1]
		Tile0: [0, 15360, 80], Tile1: [80, 15360, 80], Tile2; [160, 15360, 80]
	Ker Arg: Scale, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 192 [Tile0, 1:[1x192], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x192], 1]
		Tile0: [0, 192, 192], Tile1: [0, 192, 192], Tile2; [0, 192, 192]
	Ker Arg: ScaleN, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 192 [Tile0, 1:[1x192], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x192], 1]
		Tile0: [0, 192, 192], Tile1: [0, 192, 192], Tile2; [0, 192, 192]
	Ker Arg: Infos, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 20 logical tiles, 1 physical tiles
			Total Size: 9 [Tile1, 20:[1x1, 18:1x1, 1x1], 9]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 20:[1x1, 18:1x1, 1x1], 9]
		Tile0: [0, 9, 9], Tile1: [0, 9, 9], Tile2; [0, 9, 9]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In1 = (signed char * __restrict__) (lynred_L1_Memory+35980);
	KerArg0->W_In1 = (unsigned short int) (32);
	KerArg0->H_In1 = (unsigned short int) (192);
	KerArg0->W_In2 = (unsigned short int) (80);
	KerArg0->Bias = (void * __restrict__) (lynred_L1_Memory+42124);
	KerArg0->Scale = (unsigned char * __restrict__) (lynred_L1_Memory+42892);
	KerArg0->ScaleN = (unsigned char * __restrict__) (lynred_L1_Memory+43084);
	KerArg0->W_Out = (unsigned short int) (80);
	KerArg0->BufferColIn2 = (signed char * __restrict__) (lynred_L1_Memory+0);
	KerArg0->ColFirst = (unsigned char) (1);
	KerArg0->Infos = (signed char *__restrict__) (lynred_L1_Memory+35968);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+0), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+77156+0), 2560, 1600, 80, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In2 */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+80), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+77156+2560), 2560, 1600, 80, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+77156+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+128+0), 2560, 0, &DmaR_Evt1);
	_NN_In2=80; _SN_In2=2560;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In1+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+35980), 6144, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read In1 */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+42124), 768, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Bias */
	_C_Out=0; _SC_Out=15360; _LC_Out=80;
	_SPP_Out=0; _SP_Out=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Scale+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+42892), 192, 0, &DmaR_Evt4);
	AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read Scale */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) ScaleN+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+43084), 192, 0, &DmaR_Evt5);
	AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read ScaleN */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Infos+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+35968), 9, 0, &DmaR_Evt6);
	AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Infos */
	/*============================= End Read Tiles Prolog ===============================*/
	for (T1Ind=0; T1Ind<20; T1Ind++, T1Ind_Total++) { /* Iteration on Tile1 */
		int T1Ind_Last = (T1Ind==19), T1Ind_NextLast = ((T1Ind+1)==19), T1Ind_NextNextLast = ((T1Ind+2)==19);
		/*================================= Prepare Tiles ===================================*/
		_SNN_In2 = 0;
		if (!(T1Ind_Last)) {
			if (!(T1Ind_NextLast)) {
				_NN_In2 = _NN_In2 + (80); _LNN_In2 = (80); _SNN_In2 = (32*_LNN_In2); 
			}
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In2 */
		if (_SNN_In2) {
			AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+_NN_In2), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+77156+2560*((T1Ind_Total)%2)),
					_SNN_In2, 1600, _LNN_In2, 0, &UchanHR1);
		}
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In2 */
		if (_SN_In2) {
			AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+77156+2560*((T1Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+128+2560*((T1Ind_Total+1)%2)),
					_SN_In2, 0, &DmaR_Evt1);
		}
		/*============================= End Read Tiles ======================================*/
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1;
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->In2 = (signed char * __restrict__) (lynred_L1_Memory+128+2560*((T1Ind_Total)%2));
			KerArg0->Out = (signed char * __restrict__) (lynred_L1_Memory+5248+15360*((T1Ind_Total)%2));
			KerArg0->OutFirstCol = (unsigned short int) ((0)*192);
			KerArg0->NormBias = (unsigned char) (((char *)(lynred_L1_Memory+35968))[5]);
			AT_FORK(gap_ncore(), (void *) KerParMatMulB32_2x4_ReLU_SQ8, (void *) KerArg0);
			__CALL(KerParMatMulB32_2x4_ReLU_SQ8, KerArg0);
		} /* End iteration on Tile0 */
		/*================================= Write Tiles =====================================*/
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
		if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
		if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+15360*((T1Ind_Total+-1)%2)),
					_SP_Out, 1600, _LP_Out, 1, &UchanHR2);
		AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+15360*((T1Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+5248+15360*((T1Ind_Total)%2)),
				_SC_Out, 1, &DmaW_Evt1);
		/*============================= End Write Tiles =====================================*/
		/*================================= Update Arg Pipeline =============================*/
		_SN_In2 = _SNN_In2;_LN_In2 = _LNN_In2;
		_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
		_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
		/*============================= End Update Arg Pipeline =============================*/
		/*================================= Prepare Tiles ===================================*/
		_SC_Out = 0;
		if (!(T1Ind_Last)) {
			_C_Out = _C_Out + (80); _LC_Out = (80); _SC_Out = (192*_LC_Out); 
		}
		/*============================= End Prepare Tiles ===================================*/
	} /* End iteration on Tile1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+15360*((T1Ind_Total+-1)%2)), _SP_Out, 1600, _LP_Out, 1, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S25_Conv2d_192x1x3x3_Relu(
		signed char * __restrict__ In,
		signed char * __restrict__ Filter,
		int * __restrict__ Bias,
		signed char * __restrict__ Out,
		unsigned char * __restrict__ Scale,
		unsigned char * __restrict__ ScaleN,
		signed char * __restrict__ Infos)

{
	/* Shared L1: 48668 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaR_Evt4;
	AT_L2_EVENT DmaR_Evt5;
	AT_L2_EVENT DmaR_Evt6;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	AT_HYPERRAM_CL_EVENT UchanHR2;
	KerConv_SQ8_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerConvLinReduct_SQ8_T S_KerArg1, *KerArg1 = &S_KerArg1;

	/* Iteration space related variables */
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast, D0Ind_NextNextLast;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast, T0Ind_NextNextLast;
	/* User kernel arguments related variables */
	unsigned int _NN_In;
	unsigned int _SN_In, _SNN_In;
	unsigned int _LN_In, _LNN_In;
	unsigned int _N_Filter;
	unsigned int _SN_Filter;
	unsigned int _P_Out, _C_Out;
	unsigned int _SPP_Out, _SP_Out, _SC_Out;
	unsigned int _LPP_Out, _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D0 Dim: Init: 192, Tiled: 24][Tile0 Dim: 3]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 72 logical tiles, 72 physical tiles
			Total Size: 307200 [D0, [23 x 12800, 12800]][Tile0, 3:[40x19, 1:40x20, 40x5], 1]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [23 x 12800, 12800]][Tile0, 3:[40x19, 1:40x20, 40x5], 1]
		Tile0: [0, 6080, 760], Tile1: [680, 6400, 800], Tile2; [1400, 1600, 200]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 24 logical tiles, 1 physical tiles
			Total Size: 768 [D0, [23 x 32, 32]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [23 x 32, 32]]
		Tile0: [0, 768, 768], Tile1: [0, 768, 768], Tile2; [0, 768, 768]
	Ker Arg: Scale, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 24 logical tiles, 1 physical tiles
			Total Size: 192 [D0, [23 x 8, 8]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [23 x 8, 8]]
		Tile0: [0, 192, 192], Tile1: [0, 192, 192], Tile2; [0, 192, 192]
	Ker Arg: ScaleN, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 24 logical tiles, 1 physical tiles
			Total Size: 192 [D0, [23 x 8, 8]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [23 x 8, 8]]
		Tile0: [0, 192, 192], Tile1: [0, 192, 192], Tile2; [0, 192, 192]
	Ker Arg: Filter, Tiled Space: D0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 24 logical tiles, 24 physical tiles
			Total Size: 1728 [D0, [23 x 72, 72]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [23 x 72, 72]]
		Tile0: [0, 72, 72], Tile1: [72, 72, 72], Tile2; [144, 72, 72]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 72 logical tiles, 72 physical tiles
			Total Size: 307200 [D0, [23 x 12800, 12800]][Tile0, 3:[40x18, 1:40x18, 40x4], 1]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [23 x 12800, 12800]][Tile0, 3:[40x18, 1:40x18, 40x4], 1]
		Tile0: [0, 5760, 720], Tile1: [720, 5760, 720], Tile2; [1440, 1280, 160]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 72 logical tiles, 1 physical tiles
			Total Size: 1228800 [D0, [23 x 51200, 51200]][Tile0, 3:[40x18, 1:40x18, 40x4], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [23 x 51200, 51200]][Tile0, 3:[40x18, 1:40x18, 40x4], 4]
		Tile0: [0, 23040, 2880], Tile1: [0, 23040, 2880], Tile2; [0, 23040, 2880]
	Ker Arg: Infos, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 3 logical tiles, 1 physical tiles
			Total Size: 9 [Tile0, 3:[9x1, 1:9x1, 9x1], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 3:[9x1, 1:9x1, 9x1], 1]
		Tile0: [0, 9, 9], Tile1: [0, 9, 9], Tile2; [0, 9, 9]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->W = (unsigned short int) (40);
	KerArg0->UsedW = (unsigned short int) (40);
	KerArg0->InFeatures = (unsigned short int) (8);
	KerArg0->OutFeatures = (unsigned short int) (8);
	KerArg0->TotalInFeatures = (unsigned short int) (8);
	KerArg0->Out = (int * __restrict__) (lynred_L1_Memory+25616);
	KerArg1->In = (int *__restrict__) (lynred_L1_Memory+25616);
	KerArg1->Feat = (unsigned short int) (8);
	KerArg1->W = (unsigned short int) (40);
	KerArg1->Infos = (signed char *__restrict__) (lynred_L1_Memory+48656);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+57956+0), 6080, 1600, 760, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+680), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+57956+6400), 6400, 1600, 800, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+57956+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+0+0), 6080, 0, &DmaR_Evt1);
	_NN_In=680; _SN_In=6400;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+12800), 768, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Scale+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+13568), 192, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Scale */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) ScaleN+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+13760), 192, 0, &DmaR_Evt4);
	AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read ScaleN */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+13952+0), 72, 0, &DmaR_Evt5);
	_N_Filter=0;
	_C_Out=0; _SC_Out=5760; _LC_Out=720;
	_SPP_Out=0; _SP_Out=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Infos+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+48656), 9, 0, &DmaR_Evt6);
	AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Infos */
	/*============================= End Read Tiles Prolog ===============================*/
	for (D0Ind=0; D0Ind<24; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
		int D0Ind_Last = (D0Ind==23), D0Ind_NextLast = ((D0Ind+1)==23), D0Ind_NextNextLast = ((D0Ind+2)==23);
		/*================================= Prepare Tiles ===================================*/
		_SN_Filter = 0;
		if (!(D0Ind_Last)) {
			_N_Filter = _N_Filter + (72); _SN_Filter = (72); 
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read Filter */
		if (_SN_Filter) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+_N_Filter), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+13952+72*((D0Ind_Total+1)%2)),
					_SN_Filter, 0, &DmaR_Evt5);
		}
		/*============================= End Read Tiles ======================================*/
		for (T0Ind=0; T0Ind<3; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==2), T0Ind_NextLast = ((T0Ind+1)==2), T0Ind_NextNextLast = ((T0Ind+2)==2);
			/*================================= Prepare Tiles ===================================*/
			_SNN_In = 0;
			if (!(T0Ind_Last)) {
				if (!(T0Ind_NextLast)) {
					_NN_In = _NN_In + (720); _LNN_In = ((1)?200:800); _SNN_In = (8*_LNN_In); 
				} else if (!(D0Ind_Last)) {
					_NN_In = _NN_In + (12800)+(-1400); _LNN_In = (760); _SNN_In = (8*_LNN_In); 
				}
			} else if (!(D0Ind_Last)) {
				_NN_In = _NN_In + (720-40); _LNN_In = (800); _SNN_In = (8*_LNN_In); 
			}
			/*============================= End Prepare Tiles ===================================*/
			/*================================= Read Tiles ======================================*/
			AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
			if (_SNN_In) {
				AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+_NN_In), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+57956+6400*((T0Ind_Total)%2)),
						_SNN_In, 1600, _LNN_In, 0, &UchanHR1);
			}
			AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
			if (_SN_In) {
				AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+57956+6400*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+0+6400*((T0Ind_Total+1)%2)),
						_SN_In, 0, &DmaR_Evt1);
			}
			/*============================= End Read Tiles ======================================*/
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->In = (signed char * __restrict__) (lynred_L1_Memory+0+6400*((T0Ind_Total)%2));
			KerArg0->H = (unsigned short int) (((T0Ind_Last)?5:20)-1*(T0Ind==0));
			KerArg0->UsedH = (unsigned short int) (((T0Ind_Last)?5:20)-1*(T0Ind==0));
			KerArg0->Filter = (signed char * __restrict__) (lynred_L1_Memory+13952+72*((D0Ind_Total)%2));
			KerArg0->Bias = (signed char * __restrict__) (lynred_L1_Memory+12800+((D0Ind)*32));
			KerArg0->Pad = (v4s) ((v4s){1,1,1*(T0Ind==0),1*(T0Ind_Last)});
			KerArg0->NormBias = (unsigned char) (((char *)(lynred_L1_Memory+48656))[5]);
			AT_FORK(gap_ncore(), (void *) KerParConvDW3x3Stride1B32_SQ8, (void *) KerArg0);
			__CALL(KerParConvDW3x3Stride1B32_SQ8, KerArg0);
			KerArg1->Out = (void *__restrict__) (lynred_L1_Memory+14096+5760*((T0Ind_Total)%2));
			KerArg1->H = (unsigned short int) (T0Ind_Last?4:18);
			KerArg1->Scale = (unsigned char *__restrict__) (lynred_L1_Memory+13568+((D0Ind)*8));
			KerArg1->ScaleN = (unsigned char *__restrict__) (lynred_L1_Memory+13760+((D0Ind)*8));
			AT_FORK(gap_ncore(), (void *) KerParReduct_CC_ReLU_SQ8, (void *) KerArg1);
			__CALL(KerParReduct_CC_ReLU_SQ8, KerArg1);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
			if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+5760*((T0Ind_Total+-1)%2)),
						_SP_Out, 1600, _LP_Out, 1, &UchanHR2);
			AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+5760*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+14096+5760*((T0Ind_Total)%2)),
					_SC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SN_In = _SNN_In;_LN_In = _LNN_In;
			_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
			_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (720); _LC_Out = ((T0Ind_NextLast)?160:720); _SC_Out = (8*_LC_Out); 
			} else if (!(D0Ind_Last)) {
				_C_Out = _C_Out + (12800)+(-1440); _LC_Out = (720); _SC_Out = (8*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
		/*================================= Update Arg Pipeline =============================*/
		/*============================= End Update Arg Pipeline =============================*/
	} /* End iteration on D0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+5760*((T0Ind_Total+-1)%2)), _SP_Out, 1600, _LP_Out, 1, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S28_Conv2d_32x192x1x1(
		signed char * __restrict__ In2,
		signed char * __restrict__ In1,
		int * __restrict__ Bias,
		signed char * __restrict__ Out,
		unsigned char * __restrict__ Scale,
		unsigned char * __restrict__ ScaleN,
		signed char * __restrict__ Infos)

{
	/* Shared L1: 42956 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaR_Evt4;
	AT_L2_EVENT DmaR_Evt5;
	AT_L2_EVENT DmaR_Evt6;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	AT_HYPERRAM_CL_EVENT UchanHR2;
	KerMatMul_SQ8_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T1Ind, T1Ind_Total=0, T1Ind_Last, T1Ind_NextLast, T1Ind_NextNextLast;
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	unsigned int _NN_In2;
	unsigned int _SN_In2, _SNN_In2;
	unsigned int _LN_In2, _LNN_In2;
	unsigned int _P_Out, _C_Out;
	unsigned int _SPP_Out, _SP_Out, _SC_Out;
	unsigned int _LPP_Out, _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile1 Dim: 20][Tile0 Dim: 1]
	Ker Arg: In2, Tiled Space: Tile1
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 20 logical tiles, 20 physical tiles
			Total Size: 307200 [Tile1, 20:[192x80, 18:192x80, 192x80], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 20:[192x80, 18:192x80, 192x80], 1]
		Tile0: [0, 15360, 80], Tile1: [80, 15360, 80], Tile2; [160, 15360, 80]
	Ker Arg: In1, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 6144 [Tile0, 1:[192x32], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[192x32], 1]
		Tile0: [0, 6144, 6144], Tile1: [0, 6144, 6144], Tile2; [0, 6144, 6144]
	Ker Arg: KerBuff, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 20 logical tiles, 1 physical tiles
			Total Size: 768 [Tile1, 20:[768x1, 18:768x1, 768x1], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 20:[768x1, 18:768x1, 768x1], 1]
		Tile0: [0, 768, 768], Tile1: [0, 768, 768], Tile2; [0, 768, 768]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 128 [Tile0, 1:[1x32], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x32], 4]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Out, Tiled Space: Tile1
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 20 logical tiles, 20 physical tiles
			Total Size: 51200 [Tile1, 20:[32x80, 18:32x80, 32x80], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 20:[32x80, 18:32x80, 32x80], 1]
		Tile0: [0, 2560, 80], Tile1: [80, 2560, 80], Tile2; [160, 2560, 80]
	Ker Arg: Scale, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 32 [Tile0, 1:[1x32], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x32], 1]
		Tile0: [0, 32, 32], Tile1: [0, 32, 32], Tile2; [0, 32, 32]
	Ker Arg: ScaleN, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 32 [Tile0, 1:[1x32], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x32], 1]
		Tile0: [0, 32, 32], Tile1: [0, 32, 32], Tile2; [0, 32, 32]
	Ker Arg: Infos, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 20 logical tiles, 1 physical tiles
			Total Size: 9 [Tile1, 20:[1x1, 18:1x1, 1x1], 9]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 20:[1x1, 18:1x1, 1x1], 9]
		Tile0: [0, 9, 9], Tile1: [0, 9, 9], Tile2; [0, 9, 9]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In1 = (signed char * __restrict__) (lynred_L1_Memory+36620);
	KerArg0->W_In1 = (unsigned short int) (192);
	KerArg0->H_In1 = (unsigned short int) (32);
	KerArg0->W_In2 = (unsigned short int) (80);
	KerArg0->Bias = (void * __restrict__) (lynred_L1_Memory+42764);
	KerArg0->Scale = (unsigned char * __restrict__) (lynred_L1_Memory+42892);
	KerArg0->ScaleN = (unsigned char * __restrict__) (lynred_L1_Memory+42924);
	KerArg0->W_Out = (unsigned short int) (80);
	KerArg0->BufferColIn2 = (signed char * __restrict__) (lynred_L1_Memory+0);
	KerArg0->ColFirst = (unsigned char) (1);
	KerArg0->Infos = (signed char *__restrict__) (lynred_L1_Memory+36608);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+0), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), 15360, 1600, 80, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In2 */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+80), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+15360), 15360, 1600, 80, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+768+0), 15360, 0, &DmaR_Evt1);
	_NN_In2=80; _SN_In2=15360;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In1+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+36620), 6144, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read In1 */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+42764), 128, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Bias */
	_C_Out=0; _SC_Out=2560; _LC_Out=80;
	_SPP_Out=0; _SP_Out=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Scale+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+42892), 32, 0, &DmaR_Evt4);
	AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read Scale */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) ScaleN+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+42924), 32, 0, &DmaR_Evt5);
	AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read ScaleN */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Infos+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+36608), 9, 0, &DmaR_Evt6);
	AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Infos */
	/*============================= End Read Tiles Prolog ===============================*/
	for (T1Ind=0; T1Ind<20; T1Ind++, T1Ind_Total++) { /* Iteration on Tile1 */
		int T1Ind_Last = (T1Ind==19), T1Ind_NextLast = ((T1Ind+1)==19), T1Ind_NextNextLast = ((T1Ind+2)==19);
		/*================================= Prepare Tiles ===================================*/
		_SNN_In2 = 0;
		if (!(T1Ind_Last)) {
			if (!(T1Ind_NextLast)) {
				_NN_In2 = _NN_In2 + (80); _LNN_In2 = (80); _SNN_In2 = (192*_LNN_In2); 
			}
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In2 */
		if (_SNN_In2) {
			AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+_NN_In2), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+15360*((T1Ind_Total)%2)),
					_SNN_In2, 1600, _LNN_In2, 0, &UchanHR1);
		}
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In2 */
		if (_SN_In2) {
			AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+15360*((T1Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+768+15360*((T1Ind_Total+1)%2)),
					_SN_In2, 0, &DmaR_Evt1);
		}
		/*============================= End Read Tiles ======================================*/
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1;
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->In2 = (signed char * __restrict__) (lynred_L1_Memory+768+15360*((T1Ind_Total)%2));
			KerArg0->Out = (signed char * __restrict__) (lynred_L1_Memory+31488+2560*((T1Ind_Total)%2));
			KerArg0->OutFirstCol = (unsigned short int) ((0)*32);
			KerArg0->NormBias = (unsigned char) (((char *)(lynred_L1_Memory+36608))[5]);
			AT_FORK(gap_ncore(), (void *) KerParMatMulB32_2x4_SQ8, (void *) KerArg0);
			__CALL(KerParMatMulB32_2x4_SQ8, KerArg0);
		} /* End iteration on Tile0 */
		/*================================= Write Tiles =====================================*/
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
		if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
		if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+77156+2560*((T1Ind_Total+-1)%2)),
					_SP_Out, 1600, _LP_Out, 1, &UchanHR2);
		AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+77156+2560*((T1Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+31488+2560*((T1Ind_Total)%2)),
				_SC_Out, 1, &DmaW_Evt1);
		/*============================= End Write Tiles =====================================*/
		/*================================= Update Arg Pipeline =============================*/
		_SN_In2 = _SNN_In2;_LN_In2 = _LNN_In2;
		_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
		_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
		/*============================= End Update Arg Pipeline =============================*/
		/*================================= Prepare Tiles ===================================*/
		_SC_Out = 0;
		if (!(T1Ind_Last)) {
			_C_Out = _C_Out + (80); _LC_Out = (80); _SC_Out = (32*_LC_Out); 
		}
		/*============================= End Prepare Tiles ===================================*/
	} /* End iteration on Tile1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+77156+2560*((T1Ind_Total+-1)%2)), _SP_Out, 1600, _LP_Out, 1, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S29_MatAdd_32x40x40(
		signed char * __restrict__ In1,
		signed char * __restrict__ In2,
		signed char * __restrict__ Out,
		signed char * __restrict__ Infos)

{
	/* Shared L1: 49980 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	AT_HYPERRAM_CL_EVENT UchanHR2;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF3;
	KerMat3_SQ8_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast, T0Ind_NextNextLast;
	/* User kernel arguments related variables */
	unsigned int _NN_In1;
	unsigned int _SN_In1, _SNN_In1;
	unsigned int _NN_In2;
	unsigned int _SN_In2, _SNN_In2;
	unsigned int _C_Out;
	unsigned int _SP_Out, _SC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile0 Dim: 7]
	Ker Arg: In1, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 7 logical tiles, 7 physical tiles
			Total Size: 51200 [Tile0, 7:[1x8328, 5:1x8328, 1x1232], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 7:[1x8328, 5:1x8328, 1x1232], 1]
		Tile0: [0, 8328, 8328], Tile1: [8328, 8328, 8328], Tile2; [16656, 8328, 8328]
	Ker Arg: In2, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 7 logical tiles, 7 physical tiles
			Total Size: 51200 [Tile0, 7:[1x8328, 5:1x8328, 1x1232], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 7:[1x8328, 5:1x8328, 1x1232], 1]
		Tile0: [0, 8328, 8328], Tile1: [8328, 8328, 8328], Tile2; [16656, 8328, 8328]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 7 logical tiles, 7 physical tiles
			Total Size: 51200 [Tile0, 7:[1x8328, 5:1x8328, 1x1232], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 7:[1x8328, 5:1x8328, 1x1232], 1]
		Tile0: [0, 8328, 8328], Tile1: [8328, 8328, 8328], Tile2; [16656, 8328, 8328]
	Ker Arg: Infos, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 7 logical tiles, 1 physical tiles
			Total Size: 9 [Tile0, 7:[1x1, 5:1x1, 1x1], 9]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 7:[1x1, 5:1x1, 1x1], 9]
		Tile0: [0, 9, 9], Tile1: [0, 9, 9], Tile2; [0, 9, 9]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->DoScale = (unsigned char) (1);
	KerArg0->Infos = (signed char *__restrict__) (lynred_L1_Memory+49968);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In1+0), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+97636+0), 8328, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In1 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In1+8328), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+97636+8328), 8328, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+97636+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+0+0), 8328, 0, &DmaR_Evt1);
	_NN_In1=8328; _SN_In1=8328;
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+0), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+114292+0), 8328, 0, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read In2 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+8328), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+114292+8328), 8328, 0, &UchanHR2);
	AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+114292+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+16656+0), 8328, 0, &DmaR_Evt2);
	_NN_In2=8328; _SN_In2=8328;
	_C_Out=0; _SC_Out=8328;
	_SP_Out=0;
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Infos+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+137860+0), 9, 0, &UchanHF3);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF3); /* Wait previous uDMA read Infos */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+137860+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+49968), 9, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Infos */
	/*============================= End Read Tiles Prolog ===============================*/
	for (T0Ind=0; T0Ind<7; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
		int T0Ind_Last = (T0Ind==6), T0Ind_NextLast = ((T0Ind+1)==6), T0Ind_NextNextLast = ((T0Ind+2)==6);
		/*================================= Prepare Tiles ===================================*/
		_SNN_In1 = 0;
		if (!(T0Ind_Last)) {
			if (!(T0Ind_NextLast)) {
				_NN_In1 = _NN_In1 + (8328); _SNN_In1 = ((T0Ind_NextNextLast)?1232:8328); 
			}
		}
		_SNN_In2 = 0;
		if (!(T0Ind_Last)) {
			if (!(T0Ind_NextLast)) {
				_NN_In2 = _NN_In2 + (8328); _SNN_In2 = ((T0Ind_NextNextLast)?1232:8328); 
			}
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In1 */
		if (_SNN_In1) {
			AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In1+_NN_In1), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+97636+8328*((T0Ind_Total)%2)),
					_SNN_In1, 0, &UchanHR1);
		}
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In1 */
		if (_SN_In1) {
			AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+97636+8328*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+0+8328*((T0Ind_Total+1)%2)),
					_SN_In1, 0, &DmaR_Evt1);
		}
		AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read In2 */
		if (_SNN_In2) {
			AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+_NN_In2), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+114292+8328*((T0Ind_Total)%2)),
					_SNN_In2, 0, &UchanHR2);
		}
		AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read In2 */
		if (_SN_In2) {
			AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+114292+8328*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+16656+8328*((T0Ind_Total+1)%2)),
					_SN_In2, 0, &DmaR_Evt2);
		}
		/*============================= End Read Tiles ======================================*/
		/*====================== Call Kernel LOC_LOOP =========================*/
		KerArg0->In1 = (signed char *__restrict__) (lynred_L1_Memory+0+8328*((T0Ind_Total)%2));
		KerArg0->In2 = (signed char *__restrict__) (lynred_L1_Memory+16656+8328*((T0Ind_Total)%2));
		KerArg0->Out = (signed char *__restrict__) (lynred_L1_Memory+33312+8328*((T0Ind_Total)%2));
		KerArg0->Feat = (unsigned short int) (T0Ind_Last?1232:8328);
		AT_FORK(gap_ncore(), (void *) KerMatAdd_SQ8, (void *) KerArg0);
		__CALL(KerMatAdd_SQ8, KerArg0);
		/*================================= Write Tiles =====================================*/
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+33312+8328*((T0Ind_Total)%2)),
				_SC_Out, 1, &DmaW_Evt1);
		/*============================= End Write Tiles =====================================*/
		/*================================= Update Arg Pipeline =============================*/
		_SN_In1 = _SNN_In1;
		_SN_In2 = _SNN_In2;
		_SP_Out = _SC_Out;
		/*============================= End Update Arg Pipeline =============================*/
		/*================================= Prepare Tiles ===================================*/
		_SC_Out = 0;
		if (!(T0Ind_Last)) {
			_C_Out = _C_Out + (8328); _SC_Out = ((T0Ind_NextLast)?1232:8328); 
		}
		/*============================= End Prepare Tiles ===================================*/
	} /* End iteration on Tile0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S32_Conv2d_192x32x1x1_Relu(
		signed char * __restrict__ In2,
		signed char * __restrict__ In1,
		int * __restrict__ Bias,
		signed char * __restrict__ Out,
		unsigned char * __restrict__ Scale,
		unsigned char * __restrict__ ScaleN,
		signed char * __restrict__ Infos)

{
	/* Shared L1: 43276 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaR_Evt4;
	AT_L2_EVENT DmaR_Evt5;
	AT_L2_EVENT DmaR_Evt6;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR4;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF1;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF2;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF3;
	KerMatMul_SQ8_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T1Ind, T1Ind_Total=0, T1Ind_Last, T1Ind_NextLast;
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	unsigned int _N_In2;
	unsigned int _SN_In2;
	unsigned int _LN_In2;
	unsigned int _P_Out, _C_Out;
	unsigned int _SPP_Out, _SP_Out, _SC_Out;
	unsigned int _LPP_Out, _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile1 Dim: 20][Tile0 Dim: 1]
	Ker Arg: In2, Tiled Space: Tile1
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 20 logical tiles, 20 physical tiles
			Total Size: 51200 [Tile1, 20:[32x80, 18:32x80, 32x80], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 20:[32x80, 18:32x80, 32x80], 1]
		Tile0: [0, 2560, 80], Tile1: [80, 2560, 80], Tile2; [160, 2560, 80]
	Ker Arg: In1, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 6144 [Tile0, 1:[32x192], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[32x192], 1]
		Tile0: [0, 6144, 6144], Tile1: [0, 6144, 6144], Tile2; [0, 6144, 6144]
	Ker Arg: KerBuff, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 20 logical tiles, 1 physical tiles
			Total Size: 128 [Tile1, 20:[128x1, 18:128x1, 128x1], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 20:[128x1, 18:128x1, 128x1], 1]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 768 [Tile0, 1:[1x192], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x192], 4]
		Tile0: [0, 768, 768], Tile1: [0, 768, 768], Tile2; [0, 768, 768]
	Ker Arg: Out, Tiled Space: Tile1
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 20 logical tiles, 20 physical tiles
			Total Size: 307200 [Tile1, 20:[192x80, 18:192x80, 192x80], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 20:[192x80, 18:192x80, 192x80], 1]
		Tile0: [0, 15360, 80], Tile1: [80, 15360, 80], Tile2; [160, 15360, 80]
	Ker Arg: Scale, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 192 [Tile0, 1:[1x192], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x192], 1]
		Tile0: [0, 192, 192], Tile1: [0, 192, 192], Tile2; [0, 192, 192]
	Ker Arg: ScaleN, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 192 [Tile0, 1:[1x192], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x192], 1]
		Tile0: [0, 192, 192], Tile1: [0, 192, 192], Tile2; [0, 192, 192]
	Ker Arg: Infos, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 20 logical tiles, 1 physical tiles
			Total Size: 9 [Tile1, 20:[1x1, 18:1x1, 1x1], 9]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 20:[1x1, 18:1x1, 1x1], 9]
		Tile0: [0, 9, 9], Tile1: [0, 9, 9], Tile2; [0, 9, 9]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In1 = (signed char * __restrict__) (lynred_L1_Memory+35980);
	KerArg0->W_In1 = (unsigned short int) (32);
	KerArg0->H_In1 = (unsigned short int) (192);
	KerArg0->W_In2 = (unsigned short int) (80);
	KerArg0->Bias = (void * __restrict__) (lynred_L1_Memory+42124);
	KerArg0->Scale = (unsigned char * __restrict__) (lynred_L1_Memory+42892);
	KerArg0->ScaleN = (unsigned char * __restrict__) (lynred_L1_Memory+43084);
	KerArg0->W_Out = (unsigned short int) (80);
	KerArg0->BufferColIn2 = (signed char * __restrict__) (lynred_L1_Memory+0);
	KerArg0->ColFirst = (unsigned char) (1);
	KerArg0->Infos = (signed char *__restrict__) (lynred_L1_Memory+35968);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In2+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+128+0), 2560, 1600, 80, 0, &DmaR_Evt1);
	_N_In2=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In1+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+35980), 6144, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read In1 */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+42124), 768, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Bias */
	_C_Out=0; _SC_Out=15360; _LC_Out=80;
	_SPP_Out=0; _SP_Out=0;
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Scale+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+129124+0), 192, 0, &UchanHF1);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1); /* Wait previous uDMA read Scale */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+129124+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+42892), 192, 0, &DmaR_Evt4);
	AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read Scale */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) ScaleN+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+129316+0), 192, 0, &UchanHF2);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF2); /* Wait previous uDMA read ScaleN */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+129316+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+43084), 192, 0, &DmaR_Evt5);
	AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read ScaleN */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Infos+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+129508+0), 9, 0, &UchanHF3);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF3); /* Wait previous uDMA read Infos */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+129508+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+35968), 9, 0, &DmaR_Evt6);
	AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Infos */
	/*============================= End Read Tiles Prolog ===============================*/
	for (T1Ind=0; T1Ind<20; T1Ind++, T1Ind_Total++) { /* Iteration on Tile1 */
		int T1Ind_Last = (T1Ind==19), T1Ind_NextLast = ((T1Ind+1)==19);
		/*================================= Prepare Tiles ===================================*/
		_SN_In2 = 0;
		if (!(T1Ind_Last)) {
			_N_In2 = _N_In2 + (80); _LN_In2 = (80); _SN_In2 = (32*_LN_In2); 
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In2 */
		if (_SN_In2) {
			AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In2+_N_In2), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+128+2560*((T1Ind_Total+1)%2)),
					_SN_In2, 1600, _LN_In2, 0, &DmaR_Evt1);
		}
		/*============================= End Read Tiles ======================================*/
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1;
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->In2 = (signed char * __restrict__) (lynred_L1_Memory+128+2560*((T1Ind_Total)%2));
			KerArg0->Out = (signed char * __restrict__) (lynred_L1_Memory+5248+15360*((T1Ind_Total)%2));
			KerArg0->OutFirstCol = (unsigned short int) ((0)*192);
			KerArg0->NormBias = (unsigned char) (((char *)(lynred_L1_Memory+35968))[5]);
			AT_FORK(gap_ncore(), (void *) KerParMatMulB32_2x4_ReLU_SQ8, (void *) KerArg0);
			__CALL(KerParMatMulB32_2x4_ReLU_SQ8, KerArg0);
		} /* End iteration on Tile0 */
		/*================================= Write Tiles =====================================*/
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
		if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR4); /* Wait previous uDMA write Out */
		if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+97636+15360*((T1Ind_Total+-1)%2)),
					_SP_Out, 1600, _LP_Out, 1, &UchanHR4);
		AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+97636+15360*((T1Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+5248+15360*((T1Ind_Total)%2)),
				_SC_Out, 1, &DmaW_Evt1);
		/*============================= End Write Tiles =====================================*/
		/*================================= Update Arg Pipeline =============================*/
		_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
		_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
		/*============================= End Update Arg Pipeline =============================*/
		/*================================= Prepare Tiles ===================================*/
		_SC_Out = 0;
		if (!(T1Ind_Last)) {
			_C_Out = _C_Out + (80); _LC_Out = (80); _SC_Out = (192*_LC_Out); 
		}
		/*============================= End Prepare Tiles ===================================*/
	} /* End iteration on Tile1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR4); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+97636+15360*((T1Ind_Total+-1)%2)), _SP_Out, 1600, _LP_Out, 1, &UchanHR4);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR4); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S35_Conv2d_192x1x3x3_Relu(
		signed char * __restrict__ In,
		signed char * __restrict__ Filter,
		int * __restrict__ Bias,
		signed char * __restrict__ Out,
		unsigned char * __restrict__ Scale,
		unsigned char * __restrict__ ScaleN,
		signed char * __restrict__ Infos)

{
	/* Shared L1: 48668 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaR_Evt4;
	AT_L2_EVENT DmaR_Evt5;
	AT_L2_EVENT DmaR_Evt6;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF2;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF3;
	AT_HYPERRAM_CL_EVENT UchanHR5;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF4;
	KerConv_SQ8_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerConvLinReduct_SQ8_T S_KerArg1, *KerArg1 = &S_KerArg1;

	/* Iteration space related variables */
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast, D0Ind_NextNextLast;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast, T0Ind_NextNextLast;
	/* User kernel arguments related variables */
	unsigned int _NN_In;
	unsigned int _SN_In, _SNN_In;
	unsigned int _LN_In, _LNN_In;
	unsigned int _N_Filter;
	unsigned int _SN_Filter;
	unsigned int _P_Out, _C_Out;
	unsigned int _SPP_Out, _SP_Out, _SC_Out;
	unsigned int _LPP_Out, _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D0 Dim: Init: 192, Tiled: 24][Tile0 Dim: 3]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 72 logical tiles, 72 physical tiles
			Total Size: 307200 [D0, [23 x 12800, 12800]][Tile0, 3:[40x19, 1:40x20, 40x5], 1]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [23 x 12800, 12800]][Tile0, 3:[40x19, 1:40x20, 40x5], 1]
		Tile0: [0, 6080, 760], Tile1: [680, 6400, 800], Tile2; [1400, 1600, 200]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 24 logical tiles, 1 physical tiles
			Total Size: 768 [D0, [23 x 32, 32]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [23 x 32, 32]]
		Tile0: [0, 768, 768], Tile1: [0, 768, 768], Tile2; [0, 768, 768]
	Ker Arg: Scale, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 24 logical tiles, 1 physical tiles
			Total Size: 192 [D0, [23 x 8, 8]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [23 x 8, 8]]
		Tile0: [0, 192, 192], Tile1: [0, 192, 192], Tile2; [0, 192, 192]
	Ker Arg: ScaleN, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 24 logical tiles, 1 physical tiles
			Total Size: 192 [D0, [23 x 8, 8]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [23 x 8, 8]]
		Tile0: [0, 192, 192], Tile1: [0, 192, 192], Tile2; [0, 192, 192]
	Ker Arg: Filter, Tiled Space: D0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 24 logical tiles, 24 physical tiles
			Total Size: 1728 [D0, [23 x 72, 72]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [23 x 72, 72]]
		Tile0: [0, 72, 72], Tile1: [72, 72, 72], Tile2; [144, 72, 72]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 72 logical tiles, 72 physical tiles
			Total Size: 307200 [D0, [23 x 12800, 12800]][Tile0, 3:[40x18, 1:40x18, 40x4], 1]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [23 x 12800, 12800]][Tile0, 3:[40x18, 1:40x18, 40x4], 1]
		Tile0: [0, 5760, 720], Tile1: [720, 5760, 720], Tile2; [1440, 1280, 160]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 72 logical tiles, 1 physical tiles
			Total Size: 1228800 [D0, [23 x 51200, 51200]][Tile0, 3:[40x18, 1:40x18, 40x4], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [23 x 51200, 51200]][Tile0, 3:[40x18, 1:40x18, 40x4], 4]
		Tile0: [0, 23040, 2880], Tile1: [0, 23040, 2880], Tile2; [0, 23040, 2880]
	Ker Arg: Infos, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 3 logical tiles, 1 physical tiles
			Total Size: 9 [Tile0, 3:[9x1, 1:9x1, 9x1], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 3:[9x1, 1:9x1, 9x1], 1]
		Tile0: [0, 9, 9], Tile1: [0, 9, 9], Tile2; [0, 9, 9]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->W = (unsigned short int) (40);
	KerArg0->UsedW = (unsigned short int) (40);
	KerArg0->InFeatures = (unsigned short int) (8);
	KerArg0->OutFeatures = (unsigned short int) (8);
	KerArg0->TotalInFeatures = (unsigned short int) (8);
	KerArg0->Out = (int * __restrict__) (lynred_L1_Memory+25616);
	KerArg1->In = (int *__restrict__) (lynred_L1_Memory+25616);
	KerArg1->Feat = (unsigned short int) (8);
	KerArg1->W = (unsigned short int) (40);
	KerArg1->Infos = (signed char *__restrict__) (lynred_L1_Memory+48656);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+97636+0), 6080, 1600, 760, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+680), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+97636+6400), 6400, 1600, 800, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+97636+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+0+0), 6080, 0, &DmaR_Evt1);
	_NN_In=680; _SN_In=6400;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+12800), 768, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Scale+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+121956+0), 192, 0, &UchanHF2);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF2); /* Wait previous uDMA read Scale */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+121956+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+13568), 192, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Scale */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) ScaleN+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+122148+0), 192, 0, &UchanHF3);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF3); /* Wait previous uDMA read ScaleN */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+122148+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+13760), 192, 0, &DmaR_Evt4);
	AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read ScaleN */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+13952+0), 72, 0, &DmaR_Evt5);
	_N_Filter=0;
	_C_Out=0; _SC_Out=5760; _LC_Out=720;
	_SPP_Out=0; _SP_Out=0;
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Infos+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+122340+0), 9, 0, &UchanHF4);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF4); /* Wait previous uDMA read Infos */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+122340+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+48656), 9, 0, &DmaR_Evt6);
	AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Infos */
	/*============================= End Read Tiles Prolog ===============================*/
	for (D0Ind=0; D0Ind<24; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
		int D0Ind_Last = (D0Ind==23), D0Ind_NextLast = ((D0Ind+1)==23), D0Ind_NextNextLast = ((D0Ind+2)==23);
		/*================================= Prepare Tiles ===================================*/
		_SN_Filter = 0;
		if (!(D0Ind_Last)) {
			_N_Filter = _N_Filter + (72); _SN_Filter = (72); 
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read Filter */
		if (_SN_Filter) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+_N_Filter), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+13952+72*((D0Ind_Total+1)%2)),
					_SN_Filter, 0, &DmaR_Evt5);
		}
		/*============================= End Read Tiles ======================================*/
		for (T0Ind=0; T0Ind<3; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==2), T0Ind_NextLast = ((T0Ind+1)==2), T0Ind_NextNextLast = ((T0Ind+2)==2);
			/*================================= Prepare Tiles ===================================*/
			_SNN_In = 0;
			if (!(T0Ind_Last)) {
				if (!(T0Ind_NextLast)) {
					_NN_In = _NN_In + (720); _LNN_In = ((1)?200:800); _SNN_In = (8*_LNN_In); 
				} else if (!(D0Ind_Last)) {
					_NN_In = _NN_In + (12800)+(-1400); _LNN_In = (760); _SNN_In = (8*_LNN_In); 
				}
			} else if (!(D0Ind_Last)) {
				_NN_In = _NN_In + (720-40); _LNN_In = (800); _SNN_In = (8*_LNN_In); 
			}
			/*============================= End Prepare Tiles ===================================*/
			/*================================= Read Tiles ======================================*/
			AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
			if (_SNN_In) {
				AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+_NN_In), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+97636+6400*((T0Ind_Total)%2)),
						_SNN_In, 1600, _LNN_In, 0, &UchanHR1);
			}
			AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
			if (_SN_In) {
				AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+97636+6400*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+0+6400*((T0Ind_Total+1)%2)),
						_SN_In, 0, &DmaR_Evt1);
			}
			/*============================= End Read Tiles ======================================*/
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->In = (signed char * __restrict__) (lynred_L1_Memory+0+6400*((T0Ind_Total)%2));
			KerArg0->H = (unsigned short int) (((T0Ind_Last)?5:20)-1*(T0Ind==0));
			KerArg0->UsedH = (unsigned short int) (((T0Ind_Last)?5:20)-1*(T0Ind==0));
			KerArg0->Filter = (signed char * __restrict__) (lynred_L1_Memory+13952+72*((D0Ind_Total)%2));
			KerArg0->Bias = (signed char * __restrict__) (lynred_L1_Memory+12800+((D0Ind)*32));
			KerArg0->Pad = (v4s) ((v4s){1,1,1*(T0Ind==0),1*(T0Ind_Last)});
			KerArg0->NormBias = (unsigned char) (((char *)(lynred_L1_Memory+48656))[5]);
			AT_FORK(gap_ncore(), (void *) KerParConvDW3x3Stride1B32_SQ8, (void *) KerArg0);
			__CALL(KerParConvDW3x3Stride1B32_SQ8, KerArg0);
			KerArg1->Out = (void *__restrict__) (lynred_L1_Memory+14096+5760*((T0Ind_Total)%2));
			KerArg1->H = (unsigned short int) (T0Ind_Last?4:18);
			KerArg1->Scale = (unsigned char *__restrict__) (lynred_L1_Memory+13568+((D0Ind)*8));
			KerArg1->ScaleN = (unsigned char *__restrict__) (lynred_L1_Memory+13760+((D0Ind)*8));
			AT_FORK(gap_ncore(), (void *) KerParReduct_CC_ReLU_SQ8, (void *) KerArg1);
			__CALL(KerParReduct_CC_ReLU_SQ8, KerArg1);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR5); /* Wait previous uDMA write Out */
			if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+110436+5760*((T0Ind_Total+-1)%2)),
						_SP_Out, 1600, _LP_Out, 1, &UchanHR5);
			AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+110436+5760*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+14096+5760*((T0Ind_Total)%2)),
					_SC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SN_In = _SNN_In;_LN_In = _LNN_In;
			_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
			_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (720); _LC_Out = ((T0Ind_NextLast)?160:720); _SC_Out = (8*_LC_Out); 
			} else if (!(D0Ind_Last)) {
				_C_Out = _C_Out + (12800)+(-1440); _LC_Out = (720); _SC_Out = (8*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
		/*================================= Update Arg Pipeline =============================*/
		/*============================= End Update Arg Pipeline =============================*/
	} /* End iteration on D0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR5); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+110436+5760*((T0Ind_Total+-1)%2)), _SP_Out, 1600, _LP_Out, 1, &UchanHR5);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR5); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S38_Conv2d_32x192x1x1(
		signed char * __restrict__ In2,
		signed char * __restrict__ In1,
		int * __restrict__ Bias,
		signed char * __restrict__ Out,
		unsigned char * __restrict__ Scale,
		unsigned char * __restrict__ ScaleN,
		signed char * __restrict__ Infos)

{
	/* Shared L1: 42956 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaR_Evt4;
	AT_L2_EVENT DmaR_Evt5;
	AT_L2_EVENT DmaR_Evt6;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF2;
	AT_HYPERRAM_CL_EVENT UchanHR6;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF3;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF4;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF5;
	KerMatMul_SQ8_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T1Ind, T1Ind_Total=0, T1Ind_Last, T1Ind_NextLast, T1Ind_NextNextLast;
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	unsigned int _NN_In2;
	unsigned int _SN_In2, _SNN_In2;
	unsigned int _LN_In2, _LNN_In2;
	unsigned int _P_Out, _C_Out;
	unsigned int _SPP_Out, _SP_Out, _SC_Out;
	unsigned int _LPP_Out, _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile1 Dim: 20][Tile0 Dim: 1]
	Ker Arg: In2, Tiled Space: Tile1
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 20 logical tiles, 20 physical tiles
			Total Size: 307200 [Tile1, 20:[192x80, 18:192x80, 192x80], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 20:[192x80, 18:192x80, 192x80], 1]
		Tile0: [0, 15360, 80], Tile1: [80, 15360, 80], Tile2; [160, 15360, 80]
	Ker Arg: In1, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 6144 [Tile0, 1:[192x32], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[192x32], 1]
		Tile0: [0, 6144, 6144], Tile1: [0, 6144, 6144], Tile2; [0, 6144, 6144]
	Ker Arg: KerBuff, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 20 logical tiles, 1 physical tiles
			Total Size: 768 [Tile1, 20:[768x1, 18:768x1, 768x1], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 20:[768x1, 18:768x1, 768x1], 1]
		Tile0: [0, 768, 768], Tile1: [0, 768, 768], Tile2; [0, 768, 768]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 128 [Tile0, 1:[1x32], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x32], 4]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Out, Tiled Space: Tile1
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 20 logical tiles, 20 physical tiles
			Total Size: 51200 [Tile1, 20:[32x80, 18:32x80, 32x80], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 20:[32x80, 18:32x80, 32x80], 1]
		Tile0: [0, 2560, 80], Tile1: [80, 2560, 80], Tile2; [160, 2560, 80]
	Ker Arg: Scale, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 32 [Tile0, 1:[1x32], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x32], 1]
		Tile0: [0, 32, 32], Tile1: [0, 32, 32], Tile2; [0, 32, 32]
	Ker Arg: ScaleN, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 32 [Tile0, 1:[1x32], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x32], 1]
		Tile0: [0, 32, 32], Tile1: [0, 32, 32], Tile2; [0, 32, 32]
	Ker Arg: Infos, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 20 logical tiles, 1 physical tiles
			Total Size: 9 [Tile1, 20:[1x1, 18:1x1, 1x1], 9]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 20:[1x1, 18:1x1, 1x1], 9]
		Tile0: [0, 9, 9], Tile1: [0, 9, 9], Tile2; [0, 9, 9]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In1 = (signed char * __restrict__) (lynred_L1_Memory+36620);
	KerArg0->W_In1 = (unsigned short int) (192);
	KerArg0->H_In1 = (unsigned short int) (32);
	KerArg0->W_In2 = (unsigned short int) (80);
	KerArg0->Bias = (void * __restrict__) (lynred_L1_Memory+42764);
	KerArg0->Scale = (unsigned char * __restrict__) (lynred_L1_Memory+42892);
	KerArg0->ScaleN = (unsigned char * __restrict__) (lynred_L1_Memory+42924);
	KerArg0->W_Out = (unsigned short int) (80);
	KerArg0->BufferColIn2 = (signed char * __restrict__) (lynred_L1_Memory+0);
	KerArg0->ColFirst = (unsigned char) (1);
	KerArg0->Infos = (signed char *__restrict__) (lynred_L1_Memory+36608);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+0), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+102756+0), 15360, 1600, 80, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In2 */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+80), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+102756+15360), 15360, 1600, 80, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+102756+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+768+0), 15360, 0, &DmaR_Evt1);
	_NN_In2=80; _SN_In2=15360;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In1+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+36620), 6144, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read In1 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Bias+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+139620+0), 128, 0, &UchanHF2);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF2); /* Wait previous uDMA read Bias */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+139620+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+42764), 128, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Bias */
	_C_Out=0; _SC_Out=2560; _LC_Out=80;
	_SPP_Out=0; _SP_Out=0;
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Scale+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+139748+0), 32, 0, &UchanHF3);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF3); /* Wait previous uDMA read Scale */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+139748+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+42892), 32, 0, &DmaR_Evt4);
	AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read Scale */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) ScaleN+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+139780+0), 32, 0, &UchanHF4);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF4); /* Wait previous uDMA read ScaleN */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+139780+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+42924), 32, 0, &DmaR_Evt5);
	AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read ScaleN */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Infos+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+139812+0), 9, 0, &UchanHF5);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF5); /* Wait previous uDMA read Infos */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+139812+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+36608), 9, 0, &DmaR_Evt6);
	AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Infos */
	/*============================= End Read Tiles Prolog ===============================*/
	for (T1Ind=0; T1Ind<20; T1Ind++, T1Ind_Total++) { /* Iteration on Tile1 */
		int T1Ind_Last = (T1Ind==19), T1Ind_NextLast = ((T1Ind+1)==19), T1Ind_NextNextLast = ((T1Ind+2)==19);
		/*================================= Prepare Tiles ===================================*/
		_SNN_In2 = 0;
		if (!(T1Ind_Last)) {
			if (!(T1Ind_NextLast)) {
				_NN_In2 = _NN_In2 + (80); _LNN_In2 = (80); _SNN_In2 = (192*_LNN_In2); 
			}
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In2 */
		if (_SNN_In2) {
			AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+_NN_In2), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+102756+15360*((T1Ind_Total)%2)),
					_SNN_In2, 1600, _LNN_In2, 0, &UchanHR1);
		}
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In2 */
		if (_SN_In2) {
			AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+102756+15360*((T1Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+768+15360*((T1Ind_Total+1)%2)),
					_SN_In2, 0, &DmaR_Evt1);
		}
		/*============================= End Read Tiles ======================================*/
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1;
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->In2 = (signed char * __restrict__) (lynred_L1_Memory+768+15360*((T1Ind_Total)%2));
			KerArg0->Out = (signed char * __restrict__) (lynred_L1_Memory+31488+2560*((T1Ind_Total)%2));
			KerArg0->OutFirstCol = (unsigned short int) ((0)*32);
			KerArg0->NormBias = (unsigned char) (((char *)(lynred_L1_Memory+36608))[5]);
			AT_FORK(gap_ncore(), (void *) KerParMatMulB32_2x4_SQ8, (void *) KerArg0);
			__CALL(KerParMatMulB32_2x4_SQ8, KerArg0);
		} /* End iteration on Tile0 */
		/*================================= Write Tiles =====================================*/
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
		if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR6); /* Wait previous uDMA write Out */
		if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+97636+2560*((T1Ind_Total+-1)%2)),
					_SP_Out, 1600, _LP_Out, 1, &UchanHR6);
		AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+97636+2560*((T1Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+31488+2560*((T1Ind_Total)%2)),
				_SC_Out, 1, &DmaW_Evt1);
		/*============================= End Write Tiles =====================================*/
		/*================================= Update Arg Pipeline =============================*/
		_SN_In2 = _SNN_In2;_LN_In2 = _LNN_In2;
		_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
		_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
		/*============================= End Update Arg Pipeline =============================*/
		/*================================= Prepare Tiles ===================================*/
		_SC_Out = 0;
		if (!(T1Ind_Last)) {
			_C_Out = _C_Out + (80); _LC_Out = (80); _SC_Out = (32*_LC_Out); 
		}
		/*============================= End Prepare Tiles ===================================*/
	} /* End iteration on Tile1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR6); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+97636+2560*((T1Ind_Total+-1)%2)), _SP_Out, 1600, _LP_Out, 1, &UchanHR6);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR6); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S39_MatAdd_32x40x40(
		signed char * __restrict__ In1,
		signed char * __restrict__ In2,
		signed char * __restrict__ Out,
		signed char * __restrict__ Infos)

{
	/* Shared L1: 49980 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	AT_HYPERRAM_CL_EVENT UchanHR3;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF2;
	KerMat3_SQ8_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast, T0Ind_NextNextLast;
	/* User kernel arguments related variables */
	unsigned int _N_In1;
	unsigned int _SN_In1;
	unsigned int _NN_In2;
	unsigned int _SN_In2, _SNN_In2;
	unsigned int _P_Out, _C_Out;
	unsigned int _SPP_Out, _SP_Out, _SC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile0 Dim: 7]
	Ker Arg: In1, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 7 logical tiles, 7 physical tiles
			Total Size: 51200 [Tile0, 7:[1x8328, 5:1x8328, 1x1232], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 7:[1x8328, 5:1x8328, 1x1232], 1]
		Tile0: [0, 8328, 8328], Tile1: [8328, 8328, 8328], Tile2; [16656, 8328, 8328]
	Ker Arg: In2, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 7 logical tiles, 7 physical tiles
			Total Size: 51200 [Tile0, 7:[1x8328, 5:1x8328, 1x1232], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 7:[1x8328, 5:1x8328, 1x1232], 1]
		Tile0: [0, 8328, 8328], Tile1: [8328, 8328, 8328], Tile2; [16656, 8328, 8328]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 7 logical tiles, 7 physical tiles
			Total Size: 51200 [Tile0, 7:[1x8328, 5:1x8328, 1x1232], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 7:[1x8328, 5:1x8328, 1x1232], 1]
		Tile0: [0, 8328, 8328], Tile1: [8328, 8328, 8328], Tile2; [16656, 8328, 8328]
	Ker Arg: Infos, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 7 logical tiles, 1 physical tiles
			Total Size: 9 [Tile0, 7:[1x1, 5:1x1, 1x1], 9]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 7:[1x1, 5:1x1, 1x1], 9]
		Tile0: [0, 9, 9], Tile1: [0, 9, 9], Tile2; [0, 9, 9]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->DoScale = (unsigned char) (1);
	KerArg0->Infos = (signed char *__restrict__) (lynred_L1_Memory+49968);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In1+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+0+0), 8328, 0, &DmaR_Evt1);
	_N_In1=0;
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+0), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+97636+0), 8328, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In2 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+8328), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+97636+8328), 8328, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+97636+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+16656+0), 8328, 0, &DmaR_Evt2);
	_NN_In2=8328; _SN_In2=8328;
	_C_Out=0; _SC_Out=8328;
	_SPP_Out=0; _SP_Out=0;
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Infos+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+137860+0), 9, 0, &UchanHF2);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF2); /* Wait previous uDMA read Infos */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+137860+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+49968), 9, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Infos */
	/*============================= End Read Tiles Prolog ===============================*/
	for (T0Ind=0; T0Ind<7; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
		int T0Ind_Last = (T0Ind==6), T0Ind_NextLast = ((T0Ind+1)==6), T0Ind_NextNextLast = ((T0Ind+2)==6);
		/*================================= Prepare Tiles ===================================*/
		_SN_In1 = 0;
		if (!(T0Ind_Last)) {
			_N_In1 = _N_In1 + (8328); _SN_In1 = ((T0Ind_NextLast)?1232:8328); 
		}
		_SNN_In2 = 0;
		if (!(T0Ind_Last)) {
			if (!(T0Ind_NextLast)) {
				_NN_In2 = _NN_In2 + (8328); _SNN_In2 = ((T0Ind_NextNextLast)?1232:8328); 
			}
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In1 */
		if (_SN_In1) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In1+_N_In1), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+0+8328*((T0Ind_Total+1)%2)),
					_SN_In1, 0, &DmaR_Evt1);
		}
		AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In2 */
		if (_SNN_In2) {
			AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+_NN_In2), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+97636+8328*((T0Ind_Total)%2)),
					_SNN_In2, 0, &UchanHR1);
		}
		AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read In2 */
		if (_SN_In2) {
			AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+97636+8328*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+16656+8328*((T0Ind_Total+1)%2)),
					_SN_In2, 0, &DmaR_Evt2);
		}
		/*============================= End Read Tiles ======================================*/
		/*====================== Call Kernel LOC_LOOP =========================*/
		KerArg0->In1 = (signed char *__restrict__) (lynred_L1_Memory+0+8328*((T0Ind_Total)%2));
		KerArg0->In2 = (signed char *__restrict__) (lynred_L1_Memory+16656+8328*((T0Ind_Total)%2));
		KerArg0->Out = (signed char *__restrict__) (lynred_L1_Memory+33312+8328*((T0Ind_Total)%2));
		KerArg0->Feat = (unsigned short int) (T0Ind_Last?1232:8328);
		AT_FORK(gap_ncore(), (void *) KerMatAdd_SQ8, (void *) KerArg0);
		__CALL(KerMatAdd_SQ8, KerArg0);
		/*================================= Write Tiles =====================================*/
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
		if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR3); /* Wait previous uDMA write Out */
		if (_SP_Out) AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+114292+8328*((T0Ind_Total+-1)%2)),
					_SP_Out, 1, &UchanHR3);
		AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+114292+8328*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+33312+8328*((T0Ind_Total)%2)),
				_SC_Out, 1, &DmaW_Evt1);
		/*============================= End Write Tiles =====================================*/
		/*================================= Update Arg Pipeline =============================*/
		_SN_In2 = _SNN_In2;
		_SPP_Out = _SP_Out;
		_P_Out = _C_Out;_SP_Out = _SC_Out;
		/*============================= End Update Arg Pipeline =============================*/
		/*================================= Prepare Tiles ===================================*/
		_SC_Out = 0;
		if (!(T0Ind_Last)) {
			_C_Out = _C_Out + (8328); _SC_Out = ((T0Ind_NextLast)?1232:8328); 
		}
		/*============================= End Prepare Tiles ===================================*/
	} /* End iteration on Tile0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR3); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+114292+8328*((T0Ind_Total+-1)%2)), _SP_Out, 1, &UchanHR3);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR3); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S42_Conv2d_192x32x1x1_Relu(
		signed char * __restrict__ In2,
		signed char * __restrict__ In1,
		int * __restrict__ Bias,
		signed char * __restrict__ Out,
		unsigned char * __restrict__ Scale,
		unsigned char * __restrict__ ScaleN,
		signed char * __restrict__ Infos)

{
	/* Shared L1: 43276 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaR_Evt4;
	AT_L2_EVENT DmaR_Evt5;
	AT_L2_EVENT DmaR_Evt6;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	AT_HYPERRAM_CL_EVENT UchanHR5;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF2;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF3;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF4;
	KerMatMul_SQ8_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T1Ind, T1Ind_Total=0, T1Ind_Last, T1Ind_NextLast, T1Ind_NextNextLast;
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	unsigned int _NN_In2;
	unsigned int _SN_In2, _SNN_In2;
	unsigned int _LN_In2, _LNN_In2;
	unsigned int _P_Out, _C_Out;
	unsigned int _SPP_Out, _SP_Out, _SC_Out;
	unsigned int _LPP_Out, _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile1 Dim: 20][Tile0 Dim: 1]
	Ker Arg: In2, Tiled Space: Tile1
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 20 logical tiles, 20 physical tiles
			Total Size: 51200 [Tile1, 20:[32x80, 18:32x80, 32x80], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 20:[32x80, 18:32x80, 32x80], 1]
		Tile0: [0, 2560, 80], Tile1: [80, 2560, 80], Tile2; [160, 2560, 80]
	Ker Arg: In1, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 6144 [Tile0, 1:[32x192], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[32x192], 1]
		Tile0: [0, 6144, 6144], Tile1: [0, 6144, 6144], Tile2; [0, 6144, 6144]
	Ker Arg: KerBuff, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 20 logical tiles, 1 physical tiles
			Total Size: 128 [Tile1, 20:[128x1, 18:128x1, 128x1], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 20:[128x1, 18:128x1, 128x1], 1]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 768 [Tile0, 1:[1x192], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x192], 4]
		Tile0: [0, 768, 768], Tile1: [0, 768, 768], Tile2; [0, 768, 768]
	Ker Arg: Out, Tiled Space: Tile1
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 20 logical tiles, 20 physical tiles
			Total Size: 307200 [Tile1, 20:[192x80, 18:192x80, 192x80], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 20:[192x80, 18:192x80, 192x80], 1]
		Tile0: [0, 15360, 80], Tile1: [80, 15360, 80], Tile2; [160, 15360, 80]
	Ker Arg: Scale, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 192 [Tile0, 1:[1x192], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x192], 1]
		Tile0: [0, 192, 192], Tile1: [0, 192, 192], Tile2; [0, 192, 192]
	Ker Arg: ScaleN, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 192 [Tile0, 1:[1x192], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x192], 1]
		Tile0: [0, 192, 192], Tile1: [0, 192, 192], Tile2; [0, 192, 192]
	Ker Arg: Infos, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 20 logical tiles, 1 physical tiles
			Total Size: 9 [Tile1, 20:[1x1, 18:1x1, 1x1], 9]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 20:[1x1, 18:1x1, 1x1], 9]
		Tile0: [0, 9, 9], Tile1: [0, 9, 9], Tile2; [0, 9, 9]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In1 = (signed char * __restrict__) (lynred_L1_Memory+35980);
	KerArg0->W_In1 = (unsigned short int) (32);
	KerArg0->H_In1 = (unsigned short int) (192);
	KerArg0->W_In2 = (unsigned short int) (80);
	KerArg0->Bias = (void * __restrict__) (lynred_L1_Memory+42124);
	KerArg0->Scale = (unsigned char * __restrict__) (lynred_L1_Memory+42892);
	KerArg0->ScaleN = (unsigned char * __restrict__) (lynred_L1_Memory+43084);
	KerArg0->W_Out = (unsigned short int) (80);
	KerArg0->BufferColIn2 = (signed char * __restrict__) (lynred_L1_Memory+0);
	KerArg0->ColFirst = (unsigned char) (1);
	KerArg0->Infos = (signed char *__restrict__) (lynred_L1_Memory+35968);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+0), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+77156+0), 2560, 1600, 80, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In2 */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+80), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+77156+2560), 2560, 1600, 80, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+77156+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+128+0), 2560, 0, &DmaR_Evt1);
	_NN_In2=80; _SN_In2=2560;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In1+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+35980), 6144, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read In1 */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+42124), 768, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Bias */
	_C_Out=0; _SC_Out=15360; _LC_Out=80;
	_SPP_Out=0; _SP_Out=0;
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Scale+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+82276+0), 192, 0, &UchanHF2);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF2); /* Wait previous uDMA read Scale */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+82276+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+42892), 192, 0, &DmaR_Evt4);
	AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read Scale */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) ScaleN+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+82468+0), 192, 0, &UchanHF3);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF3); /* Wait previous uDMA read ScaleN */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+82468+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+43084), 192, 0, &DmaR_Evt5);
	AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read ScaleN */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Infos+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+82660+0), 9, 0, &UchanHF4);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF4); /* Wait previous uDMA read Infos */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+82660+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+35968), 9, 0, &DmaR_Evt6);
	AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Infos */
	/*============================= End Read Tiles Prolog ===============================*/
	for (T1Ind=0; T1Ind<20; T1Ind++, T1Ind_Total++) { /* Iteration on Tile1 */
		int T1Ind_Last = (T1Ind==19), T1Ind_NextLast = ((T1Ind+1)==19), T1Ind_NextNextLast = ((T1Ind+2)==19);
		/*================================= Prepare Tiles ===================================*/
		_SNN_In2 = 0;
		if (!(T1Ind_Last)) {
			if (!(T1Ind_NextLast)) {
				_NN_In2 = _NN_In2 + (80); _LNN_In2 = (80); _SNN_In2 = (32*_LNN_In2); 
			}
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In2 */
		if (_SNN_In2) {
			AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+_NN_In2), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+77156+2560*((T1Ind_Total)%2)),
					_SNN_In2, 1600, _LNN_In2, 0, &UchanHR1);
		}
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In2 */
		if (_SN_In2) {
			AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+77156+2560*((T1Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+128+2560*((T1Ind_Total+1)%2)),
					_SN_In2, 0, &DmaR_Evt1);
		}
		/*============================= End Read Tiles ======================================*/
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1;
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->In2 = (signed char * __restrict__) (lynred_L1_Memory+128+2560*((T1Ind_Total)%2));
			KerArg0->Out = (signed char * __restrict__) (lynred_L1_Memory+5248+15360*((T1Ind_Total)%2));
			KerArg0->OutFirstCol = (unsigned short int) ((0)*192);
			KerArg0->NormBias = (unsigned char) (((char *)(lynred_L1_Memory+35968))[5]);
			AT_FORK(gap_ncore(), (void *) KerParMatMulB32_2x4_ReLU_SQ8, (void *) KerArg0);
			__CALL(KerParMatMulB32_2x4_ReLU_SQ8, KerArg0);
		} /* End iteration on Tile0 */
		/*================================= Write Tiles =====================================*/
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
		if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR5); /* Wait previous uDMA write Out */
		if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+15360*((T1Ind_Total+-1)%2)),
					_SP_Out, 1600, _LP_Out, 1, &UchanHR5);
		AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+15360*((T1Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+5248+15360*((T1Ind_Total)%2)),
				_SC_Out, 1, &DmaW_Evt1);
		/*============================= End Write Tiles =====================================*/
		/*================================= Update Arg Pipeline =============================*/
		_SN_In2 = _SNN_In2;_LN_In2 = _LNN_In2;
		_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
		_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
		/*============================= End Update Arg Pipeline =============================*/
		/*================================= Prepare Tiles ===================================*/
		_SC_Out = 0;
		if (!(T1Ind_Last)) {
			_C_Out = _C_Out + (80); _LC_Out = (80); _SC_Out = (192*_LC_Out); 
		}
		/*============================= End Prepare Tiles ===================================*/
	} /* End iteration on Tile1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR5); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+15360*((T1Ind_Total+-1)%2)), _SP_Out, 1600, _LP_Out, 1, &UchanHR5);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR5); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S45_Conv2d_12x192x1x1(
		signed char * __restrict__ In2,
		signed char * __restrict__ In1,
		int * __restrict__ Bias,
		signed char * __restrict__ Out,
		unsigned char * __restrict__ Scale,
		unsigned char * __restrict__ ScaleN,
		signed char * __restrict__ Infos)

{
	/* Shared L1: 47220 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaR_Evt4;
	AT_L2_EVENT DmaR_Evt5;
	AT_L2_EVENT DmaR_Evt6;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	KerMatMul_SQ8_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T1Ind, T1Ind_Total=0, T1Ind_Last, T1Ind_NextLast, T1Ind_NextNextLast;
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	unsigned int _NN_In2;
	unsigned int _SN_In2, _SNN_In2;
	unsigned int _LN_In2, _LNN_In2;
	unsigned int _C_Out;
	unsigned int _SP_Out, _SC_Out;
	unsigned int _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile1 Dim: 15][Tile0 Dim: 1]
	Ker Arg: In2, Tiled Space: Tile1
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 15 logical tiles, 15 physical tiles
			Total Size: 307200 [Tile1, 15:[192x108, 13:192x108, 192x88], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 15:[192x108, 13:192x108, 192x88], 1]
		Tile0: [0, 20736, 108], Tile1: [108, 20736, 108], Tile2; [216, 20736, 108]
	Ker Arg: In1, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 2304 [Tile0, 1:[192x12], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[192x12], 1]
		Tile0: [0, 2304, 2304], Tile1: [0, 2304, 2304], Tile2; [0, 2304, 2304]
	Ker Arg: KerBuff, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 15 logical tiles, 1 physical tiles
			Total Size: 768 [Tile1, 15:[768x1, 13:768x1, 768x1], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 15:[768x1, 13:768x1, 768x1], 1]
		Tile0: [0, 768, 768], Tile1: [0, 768, 768], Tile2; [0, 768, 768]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 48 [Tile0, 1:[1x12], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x12], 4]
		Tile0: [0, 48, 48], Tile1: [0, 48, 48], Tile2; [0, 48, 48]
	Ker Arg: Out, Tiled Space: Tile1
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 15 logical tiles, 15 physical tiles
			Total Size: 19200 [Tile1, 15:[12x108, 13:12x108, 12x88], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 15:[12x108, 13:12x108, 12x88], 1]
		Tile0: [0, 1296, 108], Tile1: [108, 1296, 108], Tile2; [216, 1296, 108]
	Ker Arg: Scale, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 12 [Tile0, 1:[1x12], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x12], 1]
		Tile0: [0, 12, 12], Tile1: [0, 12, 12], Tile2; [0, 12, 12]
	Ker Arg: ScaleN, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 12 [Tile0, 1:[1x12], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x12], 1]
		Tile0: [0, 12, 12], Tile1: [0, 12, 12], Tile2; [0, 12, 12]
	Ker Arg: Infos, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 15 logical tiles, 1 physical tiles
			Total Size: 9 [Tile1, 15:[1x1, 13:1x1, 1x1], 9]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 15:[1x1, 13:1x1, 1x1], 9]
		Tile0: [0, 9, 9], Tile1: [0, 9, 9], Tile2; [0, 9, 9]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In1 = (signed char * __restrict__) (lynred_L1_Memory+44844);
	KerArg0->W_In1 = (unsigned short int) (192);
	KerArg0->H_In1 = (unsigned short int) (12);
	KerArg0->Bias = (void * __restrict__) (lynred_L1_Memory+47148);
	KerArg0->Scale = (unsigned char * __restrict__) (lynred_L1_Memory+47196);
	KerArg0->ScaleN = (unsigned char * __restrict__) (lynred_L1_Memory+47208);
	KerArg0->BufferColIn2 = (signed char * __restrict__) (lynred_L1_Memory+0);
	KerArg0->ColFirst = (unsigned char) (1);
	KerArg0->Infos = (signed char *__restrict__) (lynred_L1_Memory+44832);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+0), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), 20736, 1600, 108, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In2 */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+108), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+20736), 20736, 1600, 108, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+768+0), 20736, 0, &DmaR_Evt1);
	_NN_In2=108; _SN_In2=20736;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In1+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+44844), 2304, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read In1 */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+47148), 48, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Bias */
	_C_Out=0; _SC_Out=1296; _LC_Out=108;
	_SP_Out=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Scale+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+47196), 12, 0, &DmaR_Evt4);
	AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read Scale */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) ScaleN+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+47208), 12, 0, &DmaR_Evt5);
	AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read ScaleN */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Infos+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+44832), 9, 0, &DmaR_Evt6);
	AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Infos */
	/*============================= End Read Tiles Prolog ===============================*/
	for (T1Ind=0; T1Ind<15; T1Ind++, T1Ind_Total++) { /* Iteration on Tile1 */
		int T1Ind_Last = (T1Ind==14), T1Ind_NextLast = ((T1Ind+1)==14), T1Ind_NextNextLast = ((T1Ind+2)==14);
		/*================================= Prepare Tiles ===================================*/
		_SNN_In2 = 0;
		if (!(T1Ind_Last)) {
			if (!(T1Ind_NextLast)) {
				_NN_In2 = _NN_In2 + (108); _LNN_In2 = ((T1Ind_NextNextLast)?88:108); _SNN_In2 = (192*_LNN_In2); 
			}
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In2 */
		if (_SNN_In2) {
			AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+_NN_In2), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+20736*((T1Ind_Total)%2)),
					_SNN_In2, 1600, _LNN_In2, 0, &UchanHR1);
		}
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In2 */
		if (_SN_In2) {
			AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+20736*((T1Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+768+20736*((T1Ind_Total+1)%2)),
					_SN_In2, 0, &DmaR_Evt1);
		}
		/*============================= End Read Tiles ======================================*/
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1;
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->In2 = (signed char * __restrict__) (lynred_L1_Memory+768+20736*((T1Ind_Total)%2));
			KerArg0->W_In2 = (unsigned short int) ((T1Ind_Last)?88:108);
			KerArg0->Out = (signed char * __restrict__) (lynred_L1_Memory+42240+1296*((T1Ind_Total)%2));
			KerArg0->W_Out = (unsigned short int) ((T1Ind_Last)?88:108);
			KerArg0->OutFirstCol = (unsigned short int) ((0)*12);
			KerArg0->NormBias = (unsigned char) (((char *)(lynred_L1_Memory+44832))[5]);
			AT_FORK(gap_ncore(), (void *) KerParMatMulB32_2x4_SQ8, (void *) KerArg0);
			__CALL(KerParMatMulB32_2x4_SQ8, KerArg0);
		} /* End iteration on Tile0 */
		/*================================= Write Tiles =====================================*/
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
		AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+42240+1296*((T1Ind_Total)%2)),
				_SC_Out, 1600, _LC_Out, 1, &DmaW_Evt1);
		/*============================= End Write Tiles =====================================*/
		/*================================= Update Arg Pipeline =============================*/
		_SN_In2 = _SNN_In2;_LN_In2 = _LNN_In2;
		_SP_Out = _SC_Out;_LP_Out = _LC_Out;
		/*============================= End Update Arg Pipeline =============================*/
		/*================================= Prepare Tiles ===================================*/
		_SC_Out = 0;
		if (!(T1Ind_Last)) {
			_C_Out = _C_Out + (108); _LC_Out = ((T1Ind_NextLast)?88:108); _SC_Out = (12*_LC_Out); 
		}
		/*============================= End Prepare Tiles ===================================*/
	} /* End iteration on Tile1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S46_Op_CONV_2D_0_15_trans_out0(
		signed char * __restrict__ In,
		signed char * __restrict__ Out)

{
	/* Shared L1: 38400 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	KerMatTranspose_fps_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile0 Dim: 1]
	Ker Arg: In, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 19200 [Tile0, 1:[480x40], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[480x40], 1]
		Tile0: [0, 19200, 19200], Tile1: [0, 19200, 19200], Tile2; [0, 19200, 19200]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 19200 [Tile0, 1:[40x480], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[40x480], 1]
		Tile0: [0, 19200, 19200], Tile1: [0, 19200, 19200], Tile2; [0, 19200, 19200]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (signed char *__restrict__) (lynred_L1_Memory+0);
	KerArg0->Out = (signed char *__restrict__) (lynred_L1_Memory+19200);
	KerArg0->Feat = (unsigned short int) (12);
	KerArg0->W = (unsigned short int) (40);
	KerArg0->H = (unsigned short int) (40);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+0), 19200, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on Tile0 */
		int T0Ind_Last = 1;
		/*====================== Call Kernel LOC_LOOP =========================*/
		AT_FORK(gap_ncore(), (void *) CNN_MatPermCHW2HWC_fps, (void *) KerArg0);
		__CALL(CNN_MatPermCHW2HWC_fps, KerArg0);
	} /* End iteration on Tile0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+19200), 19200, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+0), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), 19200, 1, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S50_Conv2d_6x192x1x1_Sigmoid(
		signed char * __restrict__ In2,
		signed char * __restrict__ In1,
		int * __restrict__ Bias,
		signed char * __restrict__ Out,
		unsigned char * __restrict__ Scale,
		unsigned char * __restrict__ ScaleN,
		signed char * __restrict__ Infos)

{
	/* Shared L1: 47908 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaR_Evt4;
	AT_L2_EVENT DmaR_Evt5;
	AT_L2_EVENT DmaR_Evt6;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF2;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF3;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF4;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF5;
	KerMatMul_SQ8_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerActivation_SQ8_T S_KerArg1, *KerArg1 = &S_KerArg1;

	/* Iteration space related variables */
	int T1Ind, T1Ind_Total=0, T1Ind_Last, T1Ind_NextLast, T1Ind_NextNextLast;
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	unsigned int _NN_In2;
	unsigned int _SN_In2, _SNN_In2;
	unsigned int _LN_In2, _LNN_In2;
	unsigned int _C_Out;
	unsigned int _SP_Out, _SC_Out;
	unsigned int _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile1 Dim: 14][Tile0 Dim: 1]
	Ker Arg: In2, Tiled Space: Tile1
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 14 logical tiles, 14 physical tiles
			Total Size: 307200 [Tile1, 14:[192x116, 12:192x116, 192x92], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 14:[192x116, 12:192x116, 192x92], 1]
		Tile0: [0, 22272, 116], Tile1: [116, 22272, 116], Tile2; [232, 22272, 116]
	Ker Arg: In1, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 1152 [Tile0, 1:[192x6], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[192x6], 1]
		Tile0: [0, 1152, 1152], Tile1: [0, 1152, 1152], Tile2; [0, 1152, 1152]
	Ker Arg: KerBuff, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 14 logical tiles, 1 physical tiles
			Total Size: 768 [Tile1, 14:[768x1, 12:768x1, 768x1], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 14:[768x1, 12:768x1, 768x1], 1]
		Tile0: [0, 768, 768], Tile1: [0, 768, 768], Tile2; [0, 768, 768]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 24 [Tile0, 1:[1x6], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x6], 4]
		Tile0: [0, 24, 24], Tile1: [0, 24, 24], Tile2; [0, 24, 24]
	Ker Arg: Out, Tiled Space: Tile1
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 14 logical tiles, 14 physical tiles
			Total Size: 9600 [Tile1, 14:[6x116, 12:6x116, 6x92], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 14:[6x116, 12:6x116, 6x92], 1]
		Tile0: [0, 696, 116], Tile1: [116, 696, 116], Tile2; [232, 696, 116]
	Ker Arg: Scale, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 6 [Tile0, 1:[1x6], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x6], 1]
		Tile0: [0, 6, 6], Tile1: [0, 6, 6], Tile2; [0, 6, 6]
	Ker Arg: ScaleN, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 6 [Tile0, 1:[1x6], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x6], 1]
		Tile0: [0, 6, 6], Tile1: [0, 6, 6], Tile2; [0, 6, 6]
	Ker Arg: Infos, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 14 logical tiles, 1 physical tiles
			Total Size: 9 [Tile1, 14:[1x1, 12:1x1, 1x1], 9]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 14:[1x1, 12:1x1, 1x1], 9]
		Tile0: [0, 9, 9], Tile1: [0, 9, 9], Tile2; [0, 9, 9]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In1 = (signed char * __restrict__) (lynred_L1_Memory+46716);
	KerArg0->W_In1 = (unsigned short int) (192);
	KerArg0->H_In1 = (unsigned short int) (6);
	KerArg0->Bias = (void * __restrict__) (lynred_L1_Memory+47868);
	KerArg0->Scale = (unsigned char * __restrict__) (lynred_L1_Memory+47892);
	KerArg0->ScaleN = (unsigned char * __restrict__) (lynred_L1_Memory+47900);
	KerArg0->BufferColIn2 = (signed char * __restrict__) (lynred_L1_Memory+0);
	KerArg0->ColFirst = (unsigned char) (1);
	KerArg0->Infos = (signed char *__restrict__) (lynred_L1_Memory+46704);
	KerArg1->Feat = (unsigned short int) (1);
	KerArg1->H = (unsigned short int) (6);
	KerArg1->Infos = (signed char *__restrict__) (lynred_L1_Memory+46704);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+0), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), 22272, 1600, 116, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In2 */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+116), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+22272), 22272, 1600, 116, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+768+0), 22272, 0, &DmaR_Evt1);
	_NN_In2=116; _SN_In2=22272;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In1+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+46716), 1152, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read In1 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Bias+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+101732+0), 24, 0, &UchanHF2);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF2); /* Wait previous uDMA read Bias */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+101732+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+47868), 24, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Bias */
	_C_Out=0; _SC_Out=696; _LC_Out=116;
	_SP_Out=0;
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Scale+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+101768+0), 6, 0, &UchanHF3);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF3); /* Wait previous uDMA read Scale */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+101768+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+47892), 6, 0, &DmaR_Evt4);
	AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read Scale */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) ScaleN+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+101776+0), 6, 0, &UchanHF4);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF4); /* Wait previous uDMA read ScaleN */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+101776+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+47900), 6, 0, &DmaR_Evt5);
	AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read ScaleN */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Infos+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+101756+0), 9, 0, &UchanHF5);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF5); /* Wait previous uDMA read Infos */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+101756+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+46704), 9, 0, &DmaR_Evt6);
	AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Infos */
	/*============================= End Read Tiles Prolog ===============================*/
	for (T1Ind=0; T1Ind<14; T1Ind++, T1Ind_Total++) { /* Iteration on Tile1 */
		int T1Ind_Last = (T1Ind==13), T1Ind_NextLast = ((T1Ind+1)==13), T1Ind_NextNextLast = ((T1Ind+2)==13);
		/*================================= Prepare Tiles ===================================*/
		_SNN_In2 = 0;
		if (!(T1Ind_Last)) {
			if (!(T1Ind_NextLast)) {
				_NN_In2 = _NN_In2 + (116); _LNN_In2 = ((T1Ind_NextNextLast)?92:116); _SNN_In2 = (192*_LNN_In2); 
			}
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In2 */
		if (_SNN_In2) {
			AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+_NN_In2), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+22272*((T1Ind_Total)%2)),
					_SNN_In2, 1600, _LNN_In2, 0, &UchanHR1);
		}
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In2 */
		if (_SN_In2) {
			AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+22272*((T1Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+768+22272*((T1Ind_Total+1)%2)),
					_SN_In2, 0, &DmaR_Evt1);
		}
		/*============================= End Read Tiles ======================================*/
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1;
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->In2 = (signed char * __restrict__) (lynred_L1_Memory+768+22272*((T1Ind_Total)%2));
			KerArg0->W_In2 = (unsigned short int) ((T1Ind_Last)?92:116);
			KerArg0->Out = (signed char * __restrict__) (lynred_L1_Memory+45312+696*((T1Ind_Total)%2));
			KerArg0->W_Out = (unsigned short int) ((T1Ind_Last)?92:116);
			KerArg0->OutFirstCol = (unsigned short int) ((0)*6);
			KerArg0->NormBias = (unsigned char) (((char *)(lynred_L1_Memory+46704))[5]);
			AT_FORK(gap_ncore(), (void *) KerParMatMulB32_2x4_SQ8, (void *) KerArg0);
			__CALL(KerParMatMulB32_2x4_SQ8, KerArg0);
		} /* End iteration on Tile0 */
		/*====================== Call Kernel LOC_LOOP_EPILOG =========================*/
		KerArg1->In = (signed char *__restrict__) (lynred_L1_Memory+45312+696*((T1Ind_Total)%2));
		KerArg1->Out = (signed char *__restrict__) (lynred_L1_Memory+45312+696*((T1Ind_Total)%2));
		KerArg1->W = (unsigned short int) ((T1Ind_Last)?92:116);
		AT_FORK(gap_ncore(), (void *) Ker_Sigmoid_SQ8, (void *) KerArg1);
		__CALL(Ker_Sigmoid_SQ8, KerArg1);
		/*================================= Write Tiles =====================================*/
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
		AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+45312+696*((T1Ind_Total)%2)),
				_SC_Out, 1600, _LC_Out, 1, &DmaW_Evt1);
		/*============================= End Write Tiles =====================================*/
		/*================================= Update Arg Pipeline =============================*/
		_SN_In2 = _SNN_In2;_LN_In2 = _LNN_In2;
		_SP_Out = _SC_Out;_LP_Out = _LC_Out;
		/*============================= End Update Arg Pipeline =============================*/
		/*================================= Prepare Tiles ===================================*/
		_SC_Out = 0;
		if (!(T1Ind_Last)) {
			_C_Out = _C_Out + (116); _LC_Out = ((T1Ind_NextLast)?92:116); _SC_Out = (6*_LC_Out); 
		}
		/*============================= End Prepare Tiles ===================================*/
	} /* End iteration on Tile1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S51_Op_CONV_2D_0_17_trans_out0(
		signed char * __restrict__ In,
		signed char * __restrict__ Out)

{
	/* Shared L1: 19200 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	KerMatTranspose_fps_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile0 Dim: 1]
	Ker Arg: In, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 9600 [Tile0, 1:[240x40], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[240x40], 1]
		Tile0: [0, 9600, 9600], Tile1: [0, 9600, 9600], Tile2; [0, 9600, 9600]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 9600 [Tile0, 1:[40x240], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[40x240], 1]
		Tile0: [0, 9600, 9600], Tile1: [0, 9600, 9600], Tile2; [0, 9600, 9600]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (signed char *__restrict__) (lynred_L1_Memory+0);
	KerArg0->Out = (signed char *__restrict__) (lynred_L1_Memory+9600);
	KerArg0->Feat = (unsigned short int) (6);
	KerArg0->W = (unsigned short int) (40);
	KerArg0->H = (unsigned short int) (40);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+0), 9600, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on Tile0 */
		int T0Ind_Last = 1;
		/*====================== Call Kernel LOC_LOOP =========================*/
		AT_FORK(gap_ncore(), (void *) CNN_MatPermCHW2HWC_fps, (void *) KerArg0);
		__CALL(CNN_MatPermCHW2HWC_fps, KerArg0);
	} /* End iteration on Tile0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+9600), 9600, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+0), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), 9600, 1, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S55_Conv2d_192x1x3x3_Relu(
		signed char * __restrict__ In,
		signed char * __restrict__ Filter,
		int * __restrict__ Bias,
		signed char * __restrict__ Out,
		unsigned char * __restrict__ Scale,
		unsigned char * __restrict__ ScaleN,
		signed char * __restrict__ Infos)

{
	/* Shared L1: 47692 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaR_Evt4;
	AT_L2_EVENT DmaR_Evt5;
	AT_L2_EVENT DmaR_Evt6;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF1;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF2;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF3;
	AT_HYPERRAM_CL_EVENT UchanHR4;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF5;
	KerConv_SQ8_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerConvLinReduct_SQ8_T S_KerArg1, *KerArg1 = &S_KerArg1;

	/* Iteration space related variables */
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast, D0Ind_NextNextLast;
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	unsigned int _C_Out;
	unsigned int _SP_Out, _SC_Out;
	unsigned int _LP_Out, _LC_Out;
	unsigned int _NN_In;
	unsigned int _SN_In, _SNN_In;
	unsigned int _LN_In, _LNN_In;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D0 Dim: Init: 192, Tiled: 24][Tile0 Dim: 1]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 24 logical tiles, 24 physical tiles
			Total Size: 76800 [D0, [23 x 3200, 3200]][Tile0, 1:[20x20], 1]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [23 x 3200, 3200]][Tile0, 1:[20x20], 1]
		Tile0: [0, 3200, 400], Tile1: [3200, 3200, 400], Tile2; [6400, 3200, 400]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 24 logical tiles, 1 physical tiles
			Total Size: 768 [D0, [23 x 32, 32]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [23 x 32, 32]]
		Tile0: [0, 768, 768], Tile1: [0, 768, 768], Tile2; [0, 768, 768]
	Ker Arg: Scale, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 24 logical tiles, 1 physical tiles
			Total Size: 192 [D0, [23 x 8, 8]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [23 x 8, 8]]
		Tile0: [0, 192, 192], Tile1: [0, 192, 192], Tile2; [0, 192, 192]
	Ker Arg: ScaleN, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 24 logical tiles, 1 physical tiles
			Total Size: 192 [D0, [23 x 8, 8]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [23 x 8, 8]]
		Tile0: [0, 192, 192], Tile1: [0, 192, 192], Tile2; [0, 192, 192]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 24 logical tiles, 1 physical tiles
			Total Size: 1728 [D0, [23 x 72, 72]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [23 x 72, 72]]
		Tile0: [0, 1728, 1728], Tile1: [0, 1728, 1728], Tile2; [0, 1728, 1728]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 24 logical tiles, 24 physical tiles
			Total Size: 307200 [D0, [23 x 12800, 12800]][Tile0, 1:[40x40], 1]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [23 x 12800, 12800]][Tile0, 1:[40x40], 1]
		Tile0: [0, 12800, 1600], Tile1: [12800, 12800, 1600], Tile2; [25600, 12800, 1600]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 24 logical tiles, 1 physical tiles
			Total Size: 307200 [D0, [23 x 12800, 12800]][Tile0, 1:[20x20], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [23 x 12800, 12800]][Tile0, 1:[20x20], 4]
		Tile0: [0, 12800, 1600], Tile1: [0, 12800, 1600], Tile2; [0, 12800, 1600]
	Ker Arg: Infos, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 9 [Tile0, 1:[9x1], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[9x1], 1]
		Tile0: [0, 9, 9], Tile1: [0, 9, 9], Tile2; [0, 9, 9]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->W = (unsigned short int) (40);
	KerArg0->UsedW = (unsigned short int) (40);
	KerArg0->InFeatures = (unsigned short int) (8);
	KerArg0->OutFeatures = (unsigned short int) (8);
	KerArg0->TotalInFeatures = (unsigned short int) (192);
	KerArg0->Out = (int * __restrict__) (lynred_L1_Memory+34880);
	KerArg0->Pad = (v4s) ((v4s){0,1,0,1});
	KerArg1->In = (int *__restrict__) (lynred_L1_Memory+34880);
	KerArg1->Feat = (unsigned short int) (8);
	KerArg1->W = (unsigned short int) (20);
	KerArg1->H = (unsigned short int) (20);
	KerArg1->Infos = (signed char *__restrict__) (lynred_L1_Memory+47680);
	/*================================= Read Tiles Prolog ===============================*/
	_C_Out=0; _SC_Out=3200; _LC_Out=400;
	_SP_Out=0;
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Bias+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+148836+0), 768, 0, &UchanHF1);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1); /* Wait previous uDMA read Bias */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+148836+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+25600), 768, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Bias */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Scale+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+149604+0), 192, 0, &UchanHF2);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF2); /* Wait previous uDMA read Scale */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+149604+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+26368), 192, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Scale */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) ScaleN+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+149796+0), 192, 0, &UchanHF3);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF3); /* Wait previous uDMA read ScaleN */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+149796+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+26560), 192, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read ScaleN */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+26752), 1728, 0, &DmaR_Evt4);
	AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read Filter */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), 12800, 1600, 1600, 0, &UchanHR4);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR4); /* Wait previous uDMA read In */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+12800), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+12800), 12800, 1600, 1600, 0, &UchanHR4);
	AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+0+0), 12800, 0, &DmaR_Evt5);
	_NN_In=12800; _SN_In=12800;
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Infos+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+149991+0), 9, 0, &UchanHF5);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF5); /* Wait previous uDMA read Infos */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+149991+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+47680), 9, 0, &DmaR_Evt6);
	AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Infos */
	/*============================= End Read Tiles Prolog ===============================*/
	for (D0Ind=0; D0Ind<24; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
		int D0Ind_Last = (D0Ind==23), D0Ind_NextLast = ((D0Ind+1)==23), D0Ind_NextNextLast = ((D0Ind+2)==23);
		/*================================= Prepare Tiles ===================================*/
		_SNN_In = 0;
		if (!(D0Ind_Last)) {
			if (!(D0Ind_NextLast)) {
				_NN_In = _NN_In + (12800); _LNN_In = (1600); _SNN_In = (8*_LNN_In); 
			}
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR4); /* Wait previous uDMA read In */
		if (_SNN_In) {
			AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+_NN_In), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+12800*((D0Ind_Total)%2)),
					_SNN_In, 1600, _LNN_In, 0, &UchanHR4);
		}
		AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read In */
		if (_SN_In) {
			AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+12800*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+0+12800*((D0Ind_Total+1)%2)),
					_SN_In, 0, &DmaR_Evt5);
		}
		/*============================= End Read Tiles ======================================*/
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1;
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->In = (signed char * __restrict__) (lynred_L1_Memory+0+12800*((D0Ind_Total)%2));
			KerArg0->H = (unsigned short int) (41-0*(1)-1*(1));
			KerArg0->UsedH = (unsigned short int) (41-0*(1)-1*(1));
			KerArg0->Filter = (signed char * __restrict__) (lynred_L1_Memory+26752+((D0Ind)*72));
			KerArg0->Bias = (signed char * __restrict__) (lynred_L1_Memory+25600+((D0Ind)*32));
			KerArg0->NormBias = (unsigned char) (((char *)(lynred_L1_Memory+47680))[5]);
			AT_FORK(gap_ncore(), (void *) KerParConvDW3x3Stride2B32_SQ8, (void *) KerArg0);
			__CALL(KerParConvDW3x3Stride2B32_SQ8, KerArg0);
			KerArg1->Out = (void *__restrict__) (lynred_L1_Memory+28480+3200*((D0Ind_Total)%2));
			KerArg1->Scale = (unsigned char *__restrict__) (lynred_L1_Memory+26368+((D0Ind)*8));
			KerArg1->ScaleN = (unsigned char *__restrict__) (lynred_L1_Memory+26560+((D0Ind)*8));
			AT_FORK(gap_ncore(), (void *) KerParReduct_CC_ReLU_SQ8, (void *) KerArg1);
			__CALL(KerParReduct_CC_ReLU_SQ8, KerArg1);
		} /* End iteration on Tile0 */
		/*================================= Write Tiles =====================================*/
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
		AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+28480+3200*((D0Ind_Total)%2)),
				_SC_Out, 400, _LC_Out, 1, &DmaW_Evt1);
		/*============================= End Write Tiles =====================================*/
		/*================================= Update Arg Pipeline =============================*/
		_SP_Out = _SC_Out;_LP_Out = _LC_Out;
		_SN_In = _SNN_In;_LN_In = _LNN_In;
		/*============================= End Update Arg Pipeline =============================*/
		/*================================= Prepare Tiles ===================================*/
		_SC_Out = 0;
		if (!(D0Ind_Last)) {
			_C_Out = _C_Out + (3200); _LC_Out = (400); _SC_Out = (8*_LC_Out); 
		}
		/*============================= End Prepare Tiles ===================================*/
	} /* End iteration on D0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S58_Conv2d_64x192x1x1(
		signed char * __restrict__ In2,
		signed char * __restrict__ In1,
		int * __restrict__ Bias,
		signed char * __restrict__ Out,
		unsigned char * __restrict__ Scale,
		unsigned char * __restrict__ ScaleN,
		signed char * __restrict__ Infos)

{
	/* Shared L1: 35980 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaR_Evt4;
	AT_L2_EVENT DmaR_Evt5;
	AT_L2_EVENT DmaR_Evt6;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF1;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF2;
	AT_HYPERRAM_CL_EVENT UchanHR6;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF3;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF4;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF5;
	KerMatMul_SQ8_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T1Ind, T1Ind_Total=0, T1Ind_Last, T1Ind_NextLast;
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	unsigned int _N_In2;
	unsigned int _SN_In2;
	unsigned int _LN_In2;
	unsigned int _P_Out, _C_Out;
	unsigned int _SPP_Out, _SP_Out, _SC_Out;
	unsigned int _LPP_Out, _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile1 Dim: 10][Tile0 Dim: 1]
	Ker Arg: In2, Tiled Space: Tile1
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 10 logical tiles, 10 physical tiles
			Total Size: 76800 [Tile1, 10:[192x44, 8:192x44, 192x4], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 10:[192x44, 8:192x44, 192x4], 1]
		Tile0: [0, 8448, 44], Tile1: [44, 8448, 44], Tile2; [88, 8448, 44]
	Ker Arg: In1, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 12288 [Tile0, 1:[192x64], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[192x64], 1]
		Tile0: [0, 12288, 12288], Tile1: [0, 12288, 12288], Tile2; [0, 12288, 12288]
	Ker Arg: KerBuff, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 10 logical tiles, 1 physical tiles
			Total Size: 768 [Tile1, 10:[768x1, 8:768x1, 768x1], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 10:[768x1, 8:768x1, 768x1], 1]
		Tile0: [0, 768, 768], Tile1: [0, 768, 768], Tile2; [0, 768, 768]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 256 [Tile0, 1:[1x64], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x64], 4]
		Tile0: [0, 256, 256], Tile1: [0, 256, 256], Tile2; [0, 256, 256]
	Ker Arg: Out, Tiled Space: Tile1
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 10 logical tiles, 10 physical tiles
			Total Size: 25600 [Tile1, 10:[64x44, 8:64x44, 64x4], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 10:[64x44, 8:64x44, 64x4], 1]
		Tile0: [0, 2816, 44], Tile1: [44, 2816, 44], Tile2; [88, 2816, 44]
	Ker Arg: Scale, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 64 [Tile0, 1:[1x64], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x64], 1]
		Tile0: [0, 64, 64], Tile1: [0, 64, 64], Tile2; [0, 64, 64]
	Ker Arg: ScaleN, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 64 [Tile0, 1:[1x64], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x64], 1]
		Tile0: [0, 64, 64], Tile1: [0, 64, 64], Tile2; [0, 64, 64]
	Ker Arg: Infos, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 10 logical tiles, 1 physical tiles
			Total Size: 9 [Tile1, 10:[1x1, 8:1x1, 1x1], 9]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 10:[1x1, 8:1x1, 1x1], 9]
		Tile0: [0, 9, 9], Tile1: [0, 9, 9], Tile2; [0, 9, 9]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In1 = (signed char * __restrict__) (lynred_L1_Memory+23308);
	KerArg0->W_In1 = (unsigned short int) (192);
	KerArg0->H_In1 = (unsigned short int) (64);
	KerArg0->Bias = (void * __restrict__) (lynred_L1_Memory+35596);
	KerArg0->Scale = (unsigned char * __restrict__) (lynred_L1_Memory+35852);
	KerArg0->ScaleN = (unsigned char * __restrict__) (lynred_L1_Memory+35916);
	KerArg0->BufferColIn2 = (signed char * __restrict__) (lynred_L1_Memory+0);
	KerArg0->ColFirst = (unsigned char) (1);
	KerArg0->Infos = (signed char *__restrict__) (lynred_L1_Memory+23296);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In2+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+768+0), 8448, 400, 44, 0, &DmaR_Evt1);
	_N_In2=0;
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) In1+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+52068+0), 12288, 0, &UchanHF1);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1); /* Wait previous uDMA read In1 */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+52068+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+23308), 12288, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read In1 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Bias+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+64356+0), 256, 0, &UchanHF2);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF2); /* Wait previous uDMA read Bias */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+64356+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+35596), 256, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Bias */
	_C_Out=0; _SC_Out=2816; _LC_Out=44;
	_SPP_Out=0; _SP_Out=0;
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Scale+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+64612+0), 64, 0, &UchanHF3);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF3); /* Wait previous uDMA read Scale */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+64612+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+35852), 64, 0, &DmaR_Evt4);
	AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read Scale */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) ScaleN+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+64676+0), 64, 0, &UchanHF4);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF4); /* Wait previous uDMA read ScaleN */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+64676+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+35916), 64, 0, &DmaR_Evt5);
	AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read ScaleN */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Infos+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+64740+0), 9, 0, &UchanHF5);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF5); /* Wait previous uDMA read Infos */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+64740+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+23296), 9, 0, &DmaR_Evt6);
	AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Infos */
	/*============================= End Read Tiles Prolog ===============================*/
	for (T1Ind=0; T1Ind<10; T1Ind++, T1Ind_Total++) { /* Iteration on Tile1 */
		int T1Ind_Last = (T1Ind==9), T1Ind_NextLast = ((T1Ind+1)==9);
		/*================================= Prepare Tiles ===================================*/
		_SN_In2 = 0;
		if (!(T1Ind_Last)) {
			_N_In2 = _N_In2 + (44); _LN_In2 = ((T1Ind_NextLast)?4:44); _SN_In2 = (192*_LN_In2); 
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In2 */
		if (_SN_In2) {
			AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In2+_N_In2), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+768+8448*((T1Ind_Total+1)%2)),
					_SN_In2, 400, _LN_In2, 0, &DmaR_Evt1);
		}
		/*============================= End Read Tiles ======================================*/
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1;
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->In2 = (signed char * __restrict__) (lynred_L1_Memory+768+8448*((T1Ind_Total)%2));
			KerArg0->W_In2 = (unsigned short int) ((T1Ind_Last)?4:44);
			KerArg0->Out = (signed char * __restrict__) (lynred_L1_Memory+17664+2816*((T1Ind_Total)%2));
			KerArg0->W_Out = (unsigned short int) ((T1Ind_Last)?4:44);
			KerArg0->OutFirstCol = (unsigned short int) ((0)*64);
			KerArg0->NormBias = (unsigned char) (((char *)(lynred_L1_Memory+23296))[5]);
			AT_FORK(gap_ncore(), (void *) KerParMatMulB32_2x4_SQ8, (void *) KerArg0);
			__CALL(KerParMatMulB32_2x4_SQ8, KerArg0);
		} /* End iteration on Tile0 */
		/*================================= Write Tiles =====================================*/
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
		if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR6); /* Wait previous uDMA write Out */
		if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+2816*((T1Ind_Total+-1)%2)),
					_SP_Out, 400, _LP_Out, 1, &UchanHR6);
		AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+2816*((T1Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+17664+2816*((T1Ind_Total)%2)),
				_SC_Out, 1, &DmaW_Evt1);
		/*============================= End Write Tiles =====================================*/
		/*================================= Update Arg Pipeline =============================*/
		_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
		_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
		/*============================= End Update Arg Pipeline =============================*/
		/*================================= Prepare Tiles ===================================*/
		_SC_Out = 0;
		if (!(T1Ind_Last)) {
			_C_Out = _C_Out + (44); _LC_Out = ((T1Ind_NextLast)?4:44); _SC_Out = (64*_LC_Out); 
		}
		/*============================= End Prepare Tiles ===================================*/
	} /* End iteration on Tile1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR6); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+2816*((T1Ind_Total+-1)%2)), _SP_Out, 400, _LP_Out, 1, &UchanHR6);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR6); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S61_Conv2d_384x64x1x1_Relu(
		signed char * __restrict__ In2,
		signed char * __restrict__ In1,
		int * __restrict__ Bias,
		signed char * __restrict__ Out,
		unsigned char * __restrict__ Scale,
		unsigned char * __restrict__ ScaleN,
		signed char * __restrict__ Infos)

{
	/* Shared L1: 48140 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaR_Evt4;
	AT_L2_EVENT DmaR_Evt5;
	AT_L2_EVENT DmaR_Evt6;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF1;
	AT_HYPERRAM_CL_EVENT UchanHR2;
	AT_HYPERRAM_CL_EVENT UchanHR6;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF3;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF4;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF5;
	KerMatMul_SQ8_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T1Ind, T1Ind_Total=0, T1Ind_Last, T1Ind_NextLast, T1Ind_NextNextLast;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast, T0Ind_NextNextLast;
	/* User kernel arguments related variables */
	unsigned int _NN_In1;
	unsigned int _SN_In1, _SNN_In1;
	unsigned int _NN_In2;
	unsigned int _SN_In2, _SNN_In2;
	unsigned int _LN_In2, _LNN_In2;
	unsigned int _P_Out, _C_Out;
	unsigned int _SPP_Out, _SP_Out, _SC_Out;
	unsigned int _LPP_Out, _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile1 Dim: 15][Tile0 Dim: 3]
	Ker Arg: KerBuff, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 15 logical tiles, 1 physical tiles
			Total Size: 256 [Tile1, 15:[256x1, 13:256x1, 256x1], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 15:[256x1, 13:256x1, 256x1], 1]
		Tile0: [0, 256, 256], Tile1: [0, 256, 256], Tile2; [0, 256, 256]
	Ker Arg: In1, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 3 logical tiles, 3 physical tiles
			Total Size: 24576 [Tile0, 3:[64x160, 1:64x160, 64x64], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 3:[64x160, 1:64x160, 64x64], 1]
		Tile0: [0, 10240, 10240], Tile1: [10240, 10240, 10240], Tile2; [20480, 4096, 4096]
	Ker Arg: In2, Tiled Space: Tile1
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 15 logical tiles, 15 physical tiles
			Total Size: 25600 [Tile1, 15:[64x28, 13:64x28, 64x8], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 15:[64x28, 13:64x28, 64x8], 1]
		Tile0: [0, 1792, 28], Tile1: [28, 1792, 28], Tile2; [56, 1792, 28]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 3 logical tiles, 1 physical tiles
			Total Size: 1536 [Tile0, 3:[1x160, 1:1x160, 1x64], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 3:[1x160, 1:1x160, 1x64], 4]
		Tile0: [0, 1536, 1536], Tile1: [0, 1536, 1536], Tile2; [0, 1536, 1536]
	Ker Arg: Out, Tiled Space: Tile1
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 15 logical tiles, 15 physical tiles
			Total Size: 153600 [Tile1, 15:[384x28, 13:384x28, 384x8], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 15:[384x28, 13:384x28, 384x8], 1]
		Tile0: [0, 10752, 28], Tile1: [28, 10752, 28], Tile2; [56, 10752, 28]
	Ker Arg: Scale, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 3 logical tiles, 1 physical tiles
			Total Size: 384 [Tile0, 3:[1x160, 1:1x160, 1x64], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 3:[1x160, 1:1x160, 1x64], 1]
		Tile0: [0, 384, 384], Tile1: [0, 384, 384], Tile2; [0, 384, 384]
	Ker Arg: ScaleN, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 3 logical tiles, 1 physical tiles
			Total Size: 384 [Tile0, 3:[1x160, 1:1x160, 1x64], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 3:[1x160, 1:1x160, 1x64], 1]
		Tile0: [0, 384, 384], Tile1: [0, 384, 384], Tile2; [0, 384, 384]
	Ker Arg: Infos, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 15 logical tiles, 1 physical tiles
			Total Size: 9 [Tile1, 15:[1x1, 13:1x1, 1x1], 9]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 15:[1x1, 13:1x1, 1x1], 9]
		Tile0: [0, 9, 9], Tile1: [0, 9, 9], Tile2; [0, 9, 9]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->W_In1 = (unsigned short int) (64);
	KerArg0->BufferColIn2 = (signed char * __restrict__) (lynred_L1_Memory+0);
	KerArg0->ColFirst = (unsigned char) (1);
	KerArg0->Infos = (signed char *__restrict__) (lynred_L1_Memory+25344);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) In1+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+71524+0), 10240, 0, &UchanHF1);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1); /* Wait previous uDMA read In1 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) In1+10240), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+71524+10240), 10240, 0, &UchanHF1);
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+71524+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+25356+0), 10240, 0, &DmaR_Evt1);
	_NN_In1=10240; _SN_In1=10240;
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+0), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), 1792, 400, 28, 0, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read In2 */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+28), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+1792), 1792, 400, 28, 0, &UchanHR2);
	AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+256+0), 1792, 0, &DmaR_Evt2);
	_NN_In2=28; _SN_In2=1792;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+45836), 1536, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Bias */
	_C_Out=0; _SC_Out=10752; _LC_Out=28;
	_SPP_Out=0; _SP_Out=0;
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Scale+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+92004+0), 384, 0, &UchanHF3);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF3); /* Wait previous uDMA read Scale */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+92004+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+47372), 384, 0, &DmaR_Evt4);
	AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read Scale */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) ScaleN+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+92388+0), 384, 0, &UchanHF4);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF4); /* Wait previous uDMA read ScaleN */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+92388+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+47756), 384, 0, &DmaR_Evt5);
	AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read ScaleN */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Infos+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+92772+0), 9, 0, &UchanHF5);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF5); /* Wait previous uDMA read Infos */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+92772+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+25344), 9, 0, &DmaR_Evt6);
	AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Infos */
	/*============================= End Read Tiles Prolog ===============================*/
	for (T1Ind=0; T1Ind<15; T1Ind++, T1Ind_Total++) { /* Iteration on Tile1 */
		int T1Ind_Last = (T1Ind==14), T1Ind_NextLast = ((T1Ind+1)==14), T1Ind_NextNextLast = ((T1Ind+2)==14);
		/*================================= Prepare Tiles ===================================*/
		_SNN_In2 = 0;
		if (!(T1Ind_Last)) {
			if (!(T1Ind_NextLast)) {
				_NN_In2 = _NN_In2 + (28); _LNN_In2 = ((T1Ind_NextNextLast)?8:28); _SNN_In2 = (64*_LNN_In2); 
			}
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read In2 */
		if (_SNN_In2) {
			AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+_NN_In2), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+1792*((T1Ind_Total)%2)),
					_SNN_In2, 400, _LNN_In2, 0, &UchanHR2);
		}
		AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read In2 */
		if (_SN_In2) {
			AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+1792*((T1Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+256+1792*((T1Ind_Total+1)%2)),
					_SN_In2, 0, &DmaR_Evt2);
		}
		/*============================= End Read Tiles ======================================*/
		for (T0Ind=0; T0Ind<3; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==2), T0Ind_NextLast = ((T0Ind+1)==2), T0Ind_NextNextLast = ((T0Ind+2)==2);
			/*================================= Prepare Tiles ===================================*/
			_SNN_In1 = 0;
			if (!(T0Ind_Last)) {
				if (!(T0Ind_NextLast)) {
					_NN_In1 = _NN_In1 + (10240); _SNN_In1 = ((1)?4096:10240); 
				} else if (!(T1Ind_Last)) {
					_NN_In1 = _NN_In1 + (-20480); _SNN_In1 = (10240); 
				}
			} else if (!((T1Ind_Last))) {
				_NN_In1 = _NN_In1 + (10240); _SNN_In1 = (10240); 
			}
			/*============================= End Prepare Tiles ===================================*/
			/*================================= Read Tiles ======================================*/
			AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1); /* Wait previous uDMA read In1 */
			if (_SNN_In1) {
				AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) In1+_NN_In1), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+71524+10240*((T0Ind_Total)%2)),
						_SNN_In1, 0, &UchanHF1);
			}
			AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In1 */
			if (_SN_In1) {
				AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+71524+10240*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+25356+10240*((T0Ind_Total+1)%2)),
						_SN_In1, 0, &DmaR_Evt1);
			}
			/*============================= End Read Tiles ======================================*/
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->In1 = (signed char * __restrict__) (lynred_L1_Memory+25356+10240*((T0Ind_Total)%2));
			KerArg0->H_In1 = (unsigned short int) (T0Ind_Last?64:160);
			KerArg0->In2 = (signed char * __restrict__) (lynred_L1_Memory+256+1792*((T1Ind_Total)%2));
			KerArg0->W_In2 = (unsigned short int) ((T1Ind_Last)?8:28);
			KerArg0->Bias = (void * __restrict__) (lynred_L1_Memory+45836+(640*(T0Ind)));
			KerArg0->Scale = (unsigned char * __restrict__) (lynred_L1_Memory+47372+(160*(T0Ind)));
			KerArg0->ScaleN = (unsigned char * __restrict__) (lynred_L1_Memory+47756+(160*(T0Ind)));
			KerArg0->Out = (signed char * __restrict__) (lynred_L1_Memory+3840+10752*((T1Ind_Total)%2));
			KerArg0->W_Out = (unsigned short int) ((T1Ind_Last)?8:28);
			KerArg0->OutFirstCol = (unsigned short int) ((T0Ind)*160);
			KerArg0->NormBias = (unsigned char) (((char *)(lynred_L1_Memory+25344))[5]);
			AT_FORK(gap_ncore(), (void *) KerParMatMulB32_2x4_ReLU_SQ8, (void *) KerArg0);
			__CALL(KerParMatMulB32_2x4_ReLU_SQ8, KerArg0);
			/*================================= Update Arg Pipeline =============================*/
			_SN_In1 = _SNN_In1;
			/*============================= End Update Arg Pipeline =============================*/
		} /* End iteration on Tile0 */
		/*================================= Write Tiles =====================================*/
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
		if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR6); /* Wait previous uDMA write Out */
		if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+50020+10752*((T1Ind_Total+-1)%2)),
					_SP_Out, 400, _LP_Out, 1, &UchanHR6);
		AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+50020+10752*((T1Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+3840+10752*((T1Ind_Total)%2)),
				_SC_Out, 1, &DmaW_Evt1);
		/*============================= End Write Tiles =====================================*/
		/*================================= Update Arg Pipeline =============================*/
		_SN_In2 = _SNN_In2;_LN_In2 = _LNN_In2;
		_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
		_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
		/*============================= End Update Arg Pipeline =============================*/
		/*================================= Prepare Tiles ===================================*/
		_SC_Out = 0;
		if (!(T1Ind_Last)) {
			_C_Out = _C_Out + (28); _LC_Out = ((T1Ind_NextLast)?8:28); _SC_Out = (384*_LC_Out); 
		}
		/*============================= End Prepare Tiles ===================================*/
	} /* End iteration on Tile1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR6); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+50020+10752*((T1Ind_Total+-1)%2)), _SP_Out, 400, _LP_Out, 1, &UchanHR6);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR6); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S64_Conv2d_384x1x3x3_Relu(
		signed char * __restrict__ In,
		signed char * __restrict__ Filter,
		int * __restrict__ Bias,
		signed char * __restrict__ Out,
		unsigned char * __restrict__ Scale,
		unsigned char * __restrict__ ScaleN,
		signed char * __restrict__ Infos)

{
	/* Shared L1: 31372 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaR_Evt4;
	AT_L2_EVENT DmaR_Evt5;
	AT_L2_EVENT DmaR_Evt6;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	AT_HYPERRAM_CL_EVENT UchanHR3;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF2;
	KerConv_SQ8_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerConvLinReduct_SQ8_T S_KerArg1, *KerArg1 = &S_KerArg1;

	/* Iteration space related variables */
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast, D0Ind_NextNextLast;
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	unsigned int _NN_In;
	unsigned int _SN_In, _SNN_In;
	unsigned int _LN_In, _LNN_In;
	unsigned int _P_Out, _C_Out;
	unsigned int _SPP_Out, _SP_Out, _SC_Out;
	unsigned int _LPP_Out, _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D0 Dim: Init: 384, Tiled: 48][Tile0 Dim: 1]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 48 logical tiles, 48 physical tiles
			Total Size: 153600 [D0, [47 x 3200, 3200]][Tile0, 1:[20x20], 1]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [47 x 3200, 3200]][Tile0, 1:[20x20], 1]
		Tile0: [0, 3200, 400], Tile1: [3200, 3200, 400], Tile2; [6400, 3200, 400]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 48 logical tiles, 1 physical tiles
			Total Size: 1536 [D0, [47 x 32, 32]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [47 x 32, 32]]
		Tile0: [0, 1536, 1536], Tile1: [0, 1536, 1536], Tile2; [0, 1536, 1536]
	Ker Arg: Scale, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 48 logical tiles, 1 physical tiles
			Total Size: 384 [D0, [47 x 8, 8]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [47 x 8, 8]]
		Tile0: [0, 384, 384], Tile1: [0, 384, 384], Tile2; [0, 384, 384]
	Ker Arg: ScaleN, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 48 logical tiles, 1 physical tiles
			Total Size: 384 [D0, [47 x 8, 8]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [47 x 8, 8]]
		Tile0: [0, 384, 384], Tile1: [0, 384, 384], Tile2; [0, 384, 384]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 48 logical tiles, 1 physical tiles
			Total Size: 3456 [D0, [47 x 72, 72]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [47 x 72, 72]]
		Tile0: [0, 3456, 3456], Tile1: [0, 3456, 3456], Tile2; [0, 3456, 3456]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 48 logical tiles, 48 physical tiles
			Total Size: 153600 [D0, [47 x 3200, 3200]][Tile0, 1:[20x20], 1]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [47 x 3200, 3200]][Tile0, 1:[20x20], 1]
		Tile0: [0, 3200, 400], Tile1: [3200, 3200, 400], Tile2; [6400, 3200, 400]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 48 logical tiles, 1 physical tiles
			Total Size: 614400 [D0, [47 x 12800, 12800]][Tile0, 1:[20x20], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [47 x 12800, 12800]][Tile0, 1:[20x20], 4]
		Tile0: [0, 12800, 1600], Tile1: [0, 12800, 1600], Tile2; [0, 12800, 1600]
	Ker Arg: Infos, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 9 [Tile0, 1:[9x1], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[9x1], 1]
		Tile0: [0, 9, 9], Tile1: [0, 9, 9], Tile2; [0, 9, 9]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->W = (unsigned short int) (20);
	KerArg0->UsedW = (unsigned short int) (20);
	KerArg0->InFeatures = (unsigned short int) (8);
	KerArg0->OutFeatures = (unsigned short int) (8);
	KerArg0->TotalInFeatures = (unsigned short int) (384);
	KerArg0->Out = (int * __restrict__) (lynred_L1_Memory+18560);
	KerArg0->Pad = (v4s) ((v4s){1,1,1,1});
	KerArg1->In = (int *__restrict__) (lynred_L1_Memory+18560);
	KerArg1->Feat = (unsigned short int) (8);
	KerArg1->W = (unsigned short int) (20);
	KerArg1->H = (unsigned short int) (20);
	KerArg1->Infos = (signed char *__restrict__) (lynred_L1_Memory+31360);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), 3200, 400, 400, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+3200), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+3200), 3200, 400, 400, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+0+0), 3200, 0, &DmaR_Evt1);
	_NN_In=3200; _SN_In=3200;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+6400), 1536, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Scale+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+7936), 384, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Scale */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) ScaleN+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+8320), 384, 0, &DmaR_Evt4);
	AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read ScaleN */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+8704), 3456, 0, &DmaR_Evt5);
	AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read Filter */
	_C_Out=0; _SC_Out=3200; _LC_Out=400;
	_SPP_Out=0; _SP_Out=0;
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Infos+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+59236+0), 9, 0, &UchanHF2);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF2); /* Wait previous uDMA read Infos */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+59236+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+31360), 9, 0, &DmaR_Evt6);
	AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Infos */
	/*============================= End Read Tiles Prolog ===============================*/
	for (D0Ind=0; D0Ind<48; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
		int D0Ind_Last = (D0Ind==47), D0Ind_NextLast = ((D0Ind+1)==47), D0Ind_NextNextLast = ((D0Ind+2)==47);
		/*================================= Prepare Tiles ===================================*/
		_SNN_In = 0;
		if (!(D0Ind_Last)) {
			if (!(D0Ind_NextLast)) {
				_NN_In = _NN_In + (3200); _LNN_In = (400); _SNN_In = (8*_LNN_In); 
			}
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
		if (_SNN_In) {
			AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+_NN_In), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+3200*((D0Ind_Total)%2)),
					_SNN_In, 400, _LNN_In, 0, &UchanHR1);
		}
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
		if (_SN_In) {
			AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+3200*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+0+3200*((D0Ind_Total+1)%2)),
					_SN_In, 0, &DmaR_Evt1);
		}
		/*============================= End Read Tiles ======================================*/
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1;
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->In = (signed char * __restrict__) (lynred_L1_Memory+0+3200*((D0Ind_Total)%2));
			KerArg0->H = (unsigned short int) (22-1*(1)-1*(1));
			KerArg0->UsedH = (unsigned short int) (22-1*(1)-1*(1));
			KerArg0->Filter = (signed char * __restrict__) (lynred_L1_Memory+8704+((D0Ind)*72));
			KerArg0->Bias = (signed char * __restrict__) (lynred_L1_Memory+6400+((D0Ind)*32));
			KerArg0->NormBias = (unsigned char) (((char *)(lynred_L1_Memory+31360))[5]);
			AT_FORK(gap_ncore(), (void *) KerParConvDW3x3Stride1B32_SQ8, (void *) KerArg0);
			__CALL(KerParConvDW3x3Stride1B32_SQ8, KerArg0);
			KerArg1->Out = (void *__restrict__) (lynred_L1_Memory+12160+3200*((D0Ind_Total)%2));
			KerArg1->Scale = (unsigned char *__restrict__) (lynred_L1_Memory+7936+((D0Ind)*8));
			KerArg1->ScaleN = (unsigned char *__restrict__) (lynred_L1_Memory+8320+((D0Ind)*8));
			AT_FORK(gap_ncore(), (void *) KerParReduct_CC_ReLU_SQ8, (void *) KerArg1);
			__CALL(KerParReduct_CC_ReLU_SQ8, KerArg1);
		} /* End iteration on Tile0 */
		/*================================= Write Tiles =====================================*/
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
		if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR3); /* Wait previous uDMA write Out */
		if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+52836+3200*((D0Ind_Total+-1)%2)),
					_SP_Out, 400, _LP_Out, 1, &UchanHR3);
		AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+52836+3200*((D0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+12160+3200*((D0Ind_Total)%2)),
				_SC_Out, 1, &DmaW_Evt1);
		/*============================= End Write Tiles =====================================*/
		/*================================= Update Arg Pipeline =============================*/
		_SN_In = _SNN_In;_LN_In = _LNN_In;
		_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
		_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
		/*============================= End Update Arg Pipeline =============================*/
		/*================================= Prepare Tiles ===================================*/
		_SC_Out = 0;
		if (!(D0Ind_Last)) {
			_C_Out = _C_Out + (3200); _LC_Out = (400); _SC_Out = (8*_LC_Out); 
		}
		/*============================= End Prepare Tiles ===================================*/
	} /* End iteration on D0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR3); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+52836+3200*((D0Ind_Total+-1)%2)), _SP_Out, 400, _LP_Out, 1, &UchanHR3);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR3); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S67_Conv2d_64x384x1x1(
		signed char * __restrict__ In2,
		signed char * __restrict__ In1,
		int * __restrict__ Bias,
		signed char * __restrict__ Out,
		unsigned char * __restrict__ Scale,
		unsigned char * __restrict__ ScaleN,
		signed char * __restrict__ Infos)

{
	/* Shared L1: 44428 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaR_Evt4;
	AT_L2_EVENT DmaR_Evt5;
	AT_L2_EVENT DmaR_Evt6;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF2;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF3;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF4;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF5;
	KerMatMul_SQ8_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T1Ind, T1Ind_Total=0, T1Ind_Last, T1Ind_NextLast, T1Ind_NextNextLast;
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	unsigned int _NN_In2;
	unsigned int _SN_In2, _SNN_In2;
	unsigned int _LN_In2, _LNN_In2;
	unsigned int _C_Out;
	unsigned int _SP_Out, _SC_Out;
	unsigned int _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile1 Dim: 20][Tile0 Dim: 1]
	Ker Arg: In2, Tiled Space: Tile1
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 20 logical tiles, 20 physical tiles
			Total Size: 153600 [Tile1, 20:[384x20, 18:384x20, 384x20], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 20:[384x20, 18:384x20, 384x20], 1]
		Tile0: [0, 7680, 20], Tile1: [20, 7680, 20], Tile2; [40, 7680, 20]
	Ker Arg: In1, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 24576 [Tile0, 1:[384x64], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[384x64], 1]
		Tile0: [0, 24576, 24576], Tile1: [0, 24576, 24576], Tile2; [0, 24576, 24576]
	Ker Arg: KerBuff, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 20 logical tiles, 1 physical tiles
			Total Size: 1536 [Tile1, 20:[1536x1, 18:1536x1, 1536x1], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 20:[1536x1, 18:1536x1, 1536x1], 1]
		Tile0: [0, 1536, 1536], Tile1: [0, 1536, 1536], Tile2; [0, 1536, 1536]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 256 [Tile0, 1:[1x64], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x64], 4]
		Tile0: [0, 256, 256], Tile1: [0, 256, 256], Tile2; [0, 256, 256]
	Ker Arg: Out, Tiled Space: Tile1
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 20 logical tiles, 20 physical tiles
			Total Size: 25600 [Tile1, 20:[64x20, 18:64x20, 64x20], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 20:[64x20, 18:64x20, 64x20], 1]
		Tile0: [0, 1280, 20], Tile1: [20, 1280, 20], Tile2; [40, 1280, 20]
	Ker Arg: Scale, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 64 [Tile0, 1:[1x64], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x64], 1]
		Tile0: [0, 64, 64], Tile1: [0, 64, 64], Tile2; [0, 64, 64]
	Ker Arg: ScaleN, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 64 [Tile0, 1:[1x64], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x64], 1]
		Tile0: [0, 64, 64], Tile1: [0, 64, 64], Tile2; [0, 64, 64]
	Ker Arg: Infos, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 20 logical tiles, 1 physical tiles
			Total Size: 9 [Tile1, 20:[1x1, 18:1x1, 1x1], 9]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 20:[1x1, 18:1x1, 1x1], 9]
		Tile0: [0, 9, 9], Tile1: [0, 9, 9], Tile2; [0, 9, 9]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In1 = (signed char * __restrict__) (lynred_L1_Memory+19468);
	KerArg0->W_In1 = (unsigned short int) (384);
	KerArg0->H_In1 = (unsigned short int) (64);
	KerArg0->W_In2 = (unsigned short int) (20);
	KerArg0->Bias = (void * __restrict__) (lynred_L1_Memory+44044);
	KerArg0->Scale = (unsigned char * __restrict__) (lynred_L1_Memory+44300);
	KerArg0->ScaleN = (unsigned char * __restrict__) (lynred_L1_Memory+44364);
	KerArg0->W_Out = (unsigned short int) (20);
	KerArg0->BufferColIn2 = (signed char * __restrict__) (lynred_L1_Memory+0);
	KerArg0->ColFirst = (unsigned char) (1);
	KerArg0->Infos = (signed char *__restrict__) (lynred_L1_Memory+19456);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+0), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), 7680, 400, 20, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In2 */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+20), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+7680), 7680, 400, 20, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+1536+0), 7680, 0, &DmaR_Evt1);
	_NN_In2=20; _SN_In2=7680;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In1+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+19468), 24576, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read In1 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Bias+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+61796+0), 256, 0, &UchanHF2);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF2); /* Wait previous uDMA read Bias */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+61796+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+44044), 256, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Bias */
	_C_Out=0; _SC_Out=1280; _LC_Out=20;
	_SP_Out=0;
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Scale+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+62052+0), 64, 0, &UchanHF3);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF3); /* Wait previous uDMA read Scale */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+62052+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+44300), 64, 0, &DmaR_Evt4);
	AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read Scale */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) ScaleN+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+62116+0), 64, 0, &UchanHF4);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF4); /* Wait previous uDMA read ScaleN */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+62116+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+44364), 64, 0, &DmaR_Evt5);
	AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read ScaleN */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Infos+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+62180+0), 9, 0, &UchanHF5);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF5); /* Wait previous uDMA read Infos */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+62180+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+19456), 9, 0, &DmaR_Evt6);
	AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Infos */
	/*============================= End Read Tiles Prolog ===============================*/
	for (T1Ind=0; T1Ind<20; T1Ind++, T1Ind_Total++) { /* Iteration on Tile1 */
		int T1Ind_Last = (T1Ind==19), T1Ind_NextLast = ((T1Ind+1)==19), T1Ind_NextNextLast = ((T1Ind+2)==19);
		/*================================= Prepare Tiles ===================================*/
		_SNN_In2 = 0;
		if (!(T1Ind_Last)) {
			if (!(T1Ind_NextLast)) {
				_NN_In2 = _NN_In2 + (20); _LNN_In2 = (20); _SNN_In2 = (384*_LNN_In2); 
			}
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In2 */
		if (_SNN_In2) {
			AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+_NN_In2), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+7680*((T1Ind_Total)%2)),
					_SNN_In2, 400, _LNN_In2, 0, &UchanHR1);
		}
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In2 */
		if (_SN_In2) {
			AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+7680*((T1Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+1536+7680*((T1Ind_Total+1)%2)),
					_SN_In2, 0, &DmaR_Evt1);
		}
		/*============================= End Read Tiles ======================================*/
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1;
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->In2 = (signed char * __restrict__) (lynred_L1_Memory+1536+7680*((T1Ind_Total)%2));
			KerArg0->Out = (signed char * __restrict__) (lynred_L1_Memory+16896+1280*((T1Ind_Total)%2));
			KerArg0->OutFirstCol = (unsigned short int) ((0)*64);
			KerArg0->NormBias = (unsigned char) (((char *)(lynred_L1_Memory+19456))[5]);
			AT_FORK(gap_ncore(), (void *) KerParMatMulB32_2x4_SQ8, (void *) KerArg0);
			__CALL(KerParMatMulB32_2x4_SQ8, KerArg0);
		} /* End iteration on Tile0 */
		/*================================= Write Tiles =====================================*/
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
		AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+16896+1280*((T1Ind_Total)%2)),
				_SC_Out, 400, _LC_Out, 1, &DmaW_Evt1);
		/*============================= End Write Tiles =====================================*/
		/*================================= Update Arg Pipeline =============================*/
		_SN_In2 = _SNN_In2;_LN_In2 = _LNN_In2;
		_SP_Out = _SC_Out;_LP_Out = _LC_Out;
		/*============================= End Update Arg Pipeline =============================*/
		/*================================= Prepare Tiles ===================================*/
		_SC_Out = 0;
		if (!(T1Ind_Last)) {
			_C_Out = _C_Out + (20); _LC_Out = (20); _SC_Out = (64*_LC_Out); 
		}
		/*============================= End Prepare Tiles ===================================*/
	} /* End iteration on Tile1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S68_MatAdd_64x20x20(
		signed char * __restrict__ In1,
		signed char * __restrict__ In2,
		signed char * __restrict__ Out,
		signed char * __restrict__ Infos)

{
	/* Shared L1: 49980 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF2;
	KerMat3_SQ8_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast, T0Ind_NextNextLast;
	/* User kernel arguments related variables */
	unsigned int _NN_In1;
	unsigned int _SN_In1, _SNN_In1;
	unsigned int _N_In2;
	unsigned int _SN_In2;
	unsigned int _C_Out;
	unsigned int _SP_Out, _SC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile0 Dim: 4]
	Ker Arg: In1, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 4 logical tiles, 4 physical tiles
			Total Size: 25600 [Tile0, 4:[1x8328, 2:1x8328, 1x616], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 4:[1x8328, 2:1x8328, 1x616], 1]
		Tile0: [0, 8328, 8328], Tile1: [8328, 8328, 8328], Tile2; [16656, 8328, 8328]
	Ker Arg: In2, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 4 logical tiles, 4 physical tiles
			Total Size: 25600 [Tile0, 4:[1x8328, 2:1x8328, 1x616], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 4:[1x8328, 2:1x8328, 1x616], 1]
		Tile0: [0, 8328, 8328], Tile1: [8328, 8328, 8328], Tile2; [16656, 8328, 8328]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 4 logical tiles, 4 physical tiles
			Total Size: 25600 [Tile0, 4:[1x8328, 2:1x8328, 1x616], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 4:[1x8328, 2:1x8328, 1x616], 1]
		Tile0: [0, 8328, 8328], Tile1: [8328, 8328, 8328], Tile2; [16656, 8328, 8328]
	Ker Arg: Infos, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 4 logical tiles, 1 physical tiles
			Total Size: 9 [Tile0, 4:[1x1, 2:1x1, 1x1], 9]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 4:[1x1, 2:1x1, 1x1], 9]
		Tile0: [0, 9, 9], Tile1: [0, 9, 9], Tile2; [0, 9, 9]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->DoScale = (unsigned char) (1);
	KerArg0->Infos = (signed char *__restrict__) (lynred_L1_Memory+49968);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In1+0), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), 8328, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In1 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In1+8328), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+8328), 8328, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+0+0), 8328, 0, &DmaR_Evt1);
	_NN_In1=8328; _SN_In1=8328;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In2+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+16656+0), 8328, 0, &DmaR_Evt2);
	_N_In2=0;
	_C_Out=0; _SC_Out=8328;
	_SP_Out=0;
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Infos+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+141172+0), 9, 0, &UchanHF2);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF2); /* Wait previous uDMA read Infos */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+141172+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+49968), 9, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Infos */
	/*============================= End Read Tiles Prolog ===============================*/
	for (T0Ind=0; T0Ind<4; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
		int T0Ind_Last = (T0Ind==3), T0Ind_NextLast = ((T0Ind+1)==3), T0Ind_NextNextLast = ((T0Ind+2)==3);
		/*================================= Prepare Tiles ===================================*/
		_SNN_In1 = 0;
		if (!(T0Ind_Last)) {
			if (!(T0Ind_NextLast)) {
				_NN_In1 = _NN_In1 + (8328); _SNN_In1 = ((T0Ind_NextNextLast)?616:8328); 
			}
		}
		_SN_In2 = 0;
		if (!(T0Ind_Last)) {
			_N_In2 = _N_In2 + (8328); _SN_In2 = ((T0Ind_NextLast)?616:8328); 
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In1 */
		if (_SNN_In1) {
			AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In1+_NN_In1), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+8328*((T0Ind_Total)%2)),
					_SNN_In1, 0, &UchanHR1);
		}
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In1 */
		if (_SN_In1) {
			AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+8328*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+0+8328*((T0Ind_Total+1)%2)),
					_SN_In1, 0, &DmaR_Evt1);
		}
		AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read In2 */
		if (_SN_In2) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In2+_N_In2), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+16656+8328*((T0Ind_Total+1)%2)),
					_SN_In2, 0, &DmaR_Evt2);
		}
		/*============================= End Read Tiles ======================================*/
		/*====================== Call Kernel LOC_LOOP =========================*/
		KerArg0->In1 = (signed char *__restrict__) (lynred_L1_Memory+0+8328*((T0Ind_Total)%2));
		KerArg0->In2 = (signed char *__restrict__) (lynred_L1_Memory+16656+8328*((T0Ind_Total)%2));
		KerArg0->Out = (signed char *__restrict__) (lynred_L1_Memory+33312+8328*((T0Ind_Total)%2));
		KerArg0->Feat = (unsigned short int) (T0Ind_Last?616:8328);
		AT_FORK(gap_ncore(), (void *) KerMatAdd_SQ8, (void *) KerArg0);
		__CALL(KerMatAdd_SQ8, KerArg0);
		/*================================= Write Tiles =====================================*/
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+33312+8328*((T0Ind_Total)%2)),
				_SC_Out, 1, &DmaW_Evt1);
		/*============================= End Write Tiles =====================================*/
		/*================================= Update Arg Pipeline =============================*/
		_SN_In1 = _SNN_In1;
		_SP_Out = _SC_Out;
		/*============================= End Update Arg Pipeline =============================*/
		/*================================= Prepare Tiles ===================================*/
		_SC_Out = 0;
		if (!(T0Ind_Last)) {
			_C_Out = _C_Out + (8328); _SC_Out = ((T0Ind_NextLast)?616:8328); 
		}
		/*============================= End Prepare Tiles ===================================*/
	} /* End iteration on Tile0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S71_Conv2d_384x64x1x1_Relu(
		signed char * __restrict__ In2,
		signed char * __restrict__ In1,
		int * __restrict__ Bias,
		signed char * __restrict__ Out,
		unsigned char * __restrict__ Scale,
		unsigned char * __restrict__ ScaleN,
		signed char * __restrict__ Infos)

{
	/* Shared L1: 48140 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaR_Evt4;
	AT_L2_EVENT DmaR_Evt5;
	AT_L2_EVENT DmaR_Evt6;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR2;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF1;
	KerMatMul_SQ8_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T1Ind, T1Ind_Total=0, T1Ind_Last, T1Ind_NextLast;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast;
	/* User kernel arguments related variables */
	unsigned int _N_In1;
	unsigned int _SN_In1;
	unsigned int _N_In2;
	unsigned int _SN_In2;
	unsigned int _LN_In2;
	unsigned int _P_Out, _C_Out;
	unsigned int _SPP_Out, _SP_Out, _SC_Out;
	unsigned int _LPP_Out, _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile1 Dim: 15][Tile0 Dim: 3]
	Ker Arg: KerBuff, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 15 logical tiles, 1 physical tiles
			Total Size: 256 [Tile1, 15:[256x1, 13:256x1, 256x1], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 15:[256x1, 13:256x1, 256x1], 1]
		Tile0: [0, 256, 256], Tile1: [0, 256, 256], Tile2; [0, 256, 256]
	Ker Arg: In1, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 3 logical tiles, 3 physical tiles
			Total Size: 24576 [Tile0, 3:[64x160, 1:64x160, 64x64], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 3:[64x160, 1:64x160, 64x64], 1]
		Tile0: [0, 10240, 10240], Tile1: [10240, 10240, 10240], Tile2; [20480, 4096, 4096]
	Ker Arg: In2, Tiled Space: Tile1
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 15 logical tiles, 15 physical tiles
			Total Size: 25600 [Tile1, 15:[64x28, 13:64x28, 64x8], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 15:[64x28, 13:64x28, 64x8], 1]
		Tile0: [0, 1792, 28], Tile1: [28, 1792, 28], Tile2; [56, 1792, 28]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 3 logical tiles, 1 physical tiles
			Total Size: 1536 [Tile0, 3:[1x160, 1:1x160, 1x64], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 3:[1x160, 1:1x160, 1x64], 4]
		Tile0: [0, 1536, 1536], Tile1: [0, 1536, 1536], Tile2; [0, 1536, 1536]
	Ker Arg: Out, Tiled Space: Tile1
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 15 logical tiles, 15 physical tiles
			Total Size: 153600 [Tile1, 15:[384x28, 13:384x28, 384x8], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 15:[384x28, 13:384x28, 384x8], 1]
		Tile0: [0, 10752, 28], Tile1: [28, 10752, 28], Tile2; [56, 10752, 28]
	Ker Arg: Scale, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 3 logical tiles, 1 physical tiles
			Total Size: 384 [Tile0, 3:[1x160, 1:1x160, 1x64], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 3:[1x160, 1:1x160, 1x64], 1]
		Tile0: [0, 384, 384], Tile1: [0, 384, 384], Tile2; [0, 384, 384]
	Ker Arg: ScaleN, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 3 logical tiles, 1 physical tiles
			Total Size: 384 [Tile0, 3:[1x160, 1:1x160, 1x64], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 3:[1x160, 1:1x160, 1x64], 1]
		Tile0: [0, 384, 384], Tile1: [0, 384, 384], Tile2; [0, 384, 384]
	Ker Arg: Infos, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 15 logical tiles, 1 physical tiles
			Total Size: 9 [Tile1, 15:[1x1, 13:1x1, 1x1], 9]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 15:[1x1, 13:1x1, 1x1], 9]
		Tile0: [0, 9, 9], Tile1: [0, 9, 9], Tile2; [0, 9, 9]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->W_In1 = (unsigned short int) (64);
	KerArg0->BufferColIn2 = (signed char * __restrict__) (lynred_L1_Memory+0);
	KerArg0->ColFirst = (unsigned char) (1);
	KerArg0->Infos = (signed char *__restrict__) (lynred_L1_Memory+25344);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In1+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+25356+0), 10240, 0, &DmaR_Evt1);
	_N_In1=0;
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In2+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+256+0), 1792, 400, 28, 0, &DmaR_Evt2);
	_N_In2=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+45836), 1536, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Bias */
	_C_Out=0; _SC_Out=10752; _LC_Out=28;
	_SPP_Out=0; _SP_Out=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Scale+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+47372), 384, 0, &DmaR_Evt4);
	AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read Scale */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) ScaleN+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+47756), 384, 0, &DmaR_Evt5);
	AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read ScaleN */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Infos+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+73700+0), 9, 0, &UchanHF1);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1); /* Wait previous uDMA read Infos */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+73700+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+25344), 9, 0, &DmaR_Evt6);
	AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Infos */
	/*============================= End Read Tiles Prolog ===============================*/
	for (T1Ind=0; T1Ind<15; T1Ind++, T1Ind_Total++) { /* Iteration on Tile1 */
		int T1Ind_Last = (T1Ind==14), T1Ind_NextLast = ((T1Ind+1)==14);
		/*================================= Prepare Tiles ===================================*/
		_SN_In2 = 0;
		if (!(T1Ind_Last)) {
			_N_In2 = _N_In2 + (28); _LN_In2 = ((T1Ind_NextLast)?8:28); _SN_In2 = (64*_LN_In2); 
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read In2 */
		if (_SN_In2) {
			AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In2+_N_In2), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+256+1792*((T1Ind_Total+1)%2)),
					_SN_In2, 400, _LN_In2, 0, &DmaR_Evt2);
		}
		/*============================= End Read Tiles ======================================*/
		for (T0Ind=0; T0Ind<3; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==2), T0Ind_NextLast = ((T0Ind+1)==2);
			/*================================= Prepare Tiles ===================================*/
			_SN_In1 = 0;
			if (!(T0Ind_Last)) {
				_N_In1 = _N_In1 + (10240); _SN_In1 = ((T0Ind_NextLast)?4096:10240); 
			} else if (!(T1Ind_Last)) {
				_N_In1 = _N_In1 + (-20480); _SN_In1 = (10240); 
			}
			/*============================= End Prepare Tiles ===================================*/
			/*================================= Read Tiles ======================================*/
			AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In1 */
			if (_SN_In1) {
				AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In1+_N_In1), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+25356+10240*((T0Ind_Total+1)%2)),
						_SN_In1, 0, &DmaR_Evt1);
			}
			/*============================= End Read Tiles ======================================*/
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->In1 = (signed char * __restrict__) (lynred_L1_Memory+25356+10240*((T0Ind_Total)%2));
			KerArg0->H_In1 = (unsigned short int) (T0Ind_Last?64:160);
			KerArg0->In2 = (signed char * __restrict__) (lynred_L1_Memory+256+1792*((T1Ind_Total)%2));
			KerArg0->W_In2 = (unsigned short int) ((T1Ind_Last)?8:28);
			KerArg0->Bias = (void * __restrict__) (lynred_L1_Memory+45836+(640*(T0Ind)));
			KerArg0->Scale = (unsigned char * __restrict__) (lynred_L1_Memory+47372+(160*(T0Ind)));
			KerArg0->ScaleN = (unsigned char * __restrict__) (lynred_L1_Memory+47756+(160*(T0Ind)));
			KerArg0->Out = (signed char * __restrict__) (lynred_L1_Memory+3840+10752*((T1Ind_Total)%2));
			KerArg0->W_Out = (unsigned short int) ((T1Ind_Last)?8:28);
			KerArg0->OutFirstCol = (unsigned short int) ((T0Ind)*160);
			KerArg0->NormBias = (unsigned char) (((char *)(lynred_L1_Memory+25344))[5]);
			AT_FORK(gap_ncore(), (void *) KerParMatMulB32_2x4_ReLU_SQ8, (void *) KerArg0);
			__CALL(KerParMatMulB32_2x4_ReLU_SQ8, KerArg0);
			/*================================= Update Arg Pipeline =============================*/
			/*============================= End Update Arg Pipeline =============================*/
		} /* End iteration on Tile0 */
		/*================================= Write Tiles =====================================*/
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
		if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
		if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+10752*((T1Ind_Total+-1)%2)),
					_SP_Out, 400, _LP_Out, 1, &UchanHR2);
		AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+10752*((T1Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+3840+10752*((T1Ind_Total)%2)),
				_SC_Out, 1, &DmaW_Evt1);
		/*============================= End Write Tiles =====================================*/
		/*================================= Update Arg Pipeline =============================*/
		_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
		_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
		/*============================= End Update Arg Pipeline =============================*/
		/*================================= Prepare Tiles ===================================*/
		_SC_Out = 0;
		if (!(T1Ind_Last)) {
			_C_Out = _C_Out + (28); _LC_Out = ((T1Ind_NextLast)?8:28); _SC_Out = (384*_LC_Out); 
		}
		/*============================= End Prepare Tiles ===================================*/
	} /* End iteration on Tile1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+10752*((T1Ind_Total+-1)%2)), _SP_Out, 400, _LP_Out, 1, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S74_Conv2d_384x1x3x3_Relu(
		signed char * __restrict__ In,
		signed char * __restrict__ Filter,
		int * __restrict__ Bias,
		signed char * __restrict__ Out,
		unsigned char * __restrict__ Scale,
		unsigned char * __restrict__ ScaleN,
		signed char * __restrict__ Infos)

{
	/* Shared L1: 31372 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaR_Evt4;
	AT_L2_EVENT DmaR_Evt5;
	AT_L2_EVENT DmaR_Evt6;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	AT_HYPERRAM_CL_EVENT UchanHR3;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF2;
	KerConv_SQ8_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerConvLinReduct_SQ8_T S_KerArg1, *KerArg1 = &S_KerArg1;

	/* Iteration space related variables */
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast, D0Ind_NextNextLast;
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	unsigned int _NN_In;
	unsigned int _SN_In, _SNN_In;
	unsigned int _LN_In, _LNN_In;
	unsigned int _P_Out, _C_Out;
	unsigned int _SPP_Out, _SP_Out, _SC_Out;
	unsigned int _LPP_Out, _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D0 Dim: Init: 384, Tiled: 48][Tile0 Dim: 1]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 48 logical tiles, 48 physical tiles
			Total Size: 153600 [D0, [47 x 3200, 3200]][Tile0, 1:[20x20], 1]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [47 x 3200, 3200]][Tile0, 1:[20x20], 1]
		Tile0: [0, 3200, 400], Tile1: [3200, 3200, 400], Tile2; [6400, 3200, 400]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 48 logical tiles, 1 physical tiles
			Total Size: 1536 [D0, [47 x 32, 32]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [47 x 32, 32]]
		Tile0: [0, 1536, 1536], Tile1: [0, 1536, 1536], Tile2; [0, 1536, 1536]
	Ker Arg: Scale, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 48 logical tiles, 1 physical tiles
			Total Size: 384 [D0, [47 x 8, 8]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [47 x 8, 8]]
		Tile0: [0, 384, 384], Tile1: [0, 384, 384], Tile2; [0, 384, 384]
	Ker Arg: ScaleN, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 48 logical tiles, 1 physical tiles
			Total Size: 384 [D0, [47 x 8, 8]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [47 x 8, 8]]
		Tile0: [0, 384, 384], Tile1: [0, 384, 384], Tile2; [0, 384, 384]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 48 logical tiles, 1 physical tiles
			Total Size: 3456 [D0, [47 x 72, 72]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [47 x 72, 72]]
		Tile0: [0, 3456, 3456], Tile1: [0, 3456, 3456], Tile2; [0, 3456, 3456]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 48 logical tiles, 48 physical tiles
			Total Size: 153600 [D0, [47 x 3200, 3200]][Tile0, 1:[20x20], 1]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [47 x 3200, 3200]][Tile0, 1:[20x20], 1]
		Tile0: [0, 3200, 400], Tile1: [3200, 3200, 400], Tile2; [6400, 3200, 400]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 48 logical tiles, 1 physical tiles
			Total Size: 614400 [D0, [47 x 12800, 12800]][Tile0, 1:[20x20], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [47 x 12800, 12800]][Tile0, 1:[20x20], 4]
		Tile0: [0, 12800, 1600], Tile1: [0, 12800, 1600], Tile2; [0, 12800, 1600]
	Ker Arg: Infos, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 9 [Tile0, 1:[9x1], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[9x1], 1]
		Tile0: [0, 9, 9], Tile1: [0, 9, 9], Tile2; [0, 9, 9]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->W = (unsigned short int) (20);
	KerArg0->UsedW = (unsigned short int) (20);
	KerArg0->InFeatures = (unsigned short int) (8);
	KerArg0->OutFeatures = (unsigned short int) (8);
	KerArg0->TotalInFeatures = (unsigned short int) (384);
	KerArg0->Out = (int * __restrict__) (lynred_L1_Memory+18560);
	KerArg0->Pad = (v4s) ((v4s){1,1,1,1});
	KerArg1->In = (int *__restrict__) (lynred_L1_Memory+18560);
	KerArg1->Feat = (unsigned short int) (8);
	KerArg1->W = (unsigned short int) (20);
	KerArg1->H = (unsigned short int) (20);
	KerArg1->Infos = (signed char *__restrict__) (lynred_L1_Memory+31360);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), 3200, 400, 400, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+3200), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+3200), 3200, 400, 400, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+0+0), 3200, 0, &DmaR_Evt1);
	_NN_In=3200; _SN_In=3200;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+6400), 1536, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Scale+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+7936), 384, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Scale */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) ScaleN+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+8320), 384, 0, &DmaR_Evt4);
	AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read ScaleN */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+8704), 3456, 0, &DmaR_Evt5);
	AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read Filter */
	_C_Out=0; _SC_Out=3200; _LC_Out=400;
	_SPP_Out=0; _SP_Out=0;
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Infos+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+59236+0), 9, 0, &UchanHF2);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF2); /* Wait previous uDMA read Infos */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+59236+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+31360), 9, 0, &DmaR_Evt6);
	AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Infos */
	/*============================= End Read Tiles Prolog ===============================*/
	for (D0Ind=0; D0Ind<48; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
		int D0Ind_Last = (D0Ind==47), D0Ind_NextLast = ((D0Ind+1)==47), D0Ind_NextNextLast = ((D0Ind+2)==47);
		/*================================= Prepare Tiles ===================================*/
		_SNN_In = 0;
		if (!(D0Ind_Last)) {
			if (!(D0Ind_NextLast)) {
				_NN_In = _NN_In + (3200); _LNN_In = (400); _SNN_In = (8*_LNN_In); 
			}
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
		if (_SNN_In) {
			AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+_NN_In), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+3200*((D0Ind_Total)%2)),
					_SNN_In, 400, _LNN_In, 0, &UchanHR1);
		}
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
		if (_SN_In) {
			AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+3200*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+0+3200*((D0Ind_Total+1)%2)),
					_SN_In, 0, &DmaR_Evt1);
		}
		/*============================= End Read Tiles ======================================*/
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1;
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->In = (signed char * __restrict__) (lynred_L1_Memory+0+3200*((D0Ind_Total)%2));
			KerArg0->H = (unsigned short int) (22-1*(1)-1*(1));
			KerArg0->UsedH = (unsigned short int) (22-1*(1)-1*(1));
			KerArg0->Filter = (signed char * __restrict__) (lynred_L1_Memory+8704+((D0Ind)*72));
			KerArg0->Bias = (signed char * __restrict__) (lynred_L1_Memory+6400+((D0Ind)*32));
			KerArg0->NormBias = (unsigned char) (((char *)(lynred_L1_Memory+31360))[5]);
			AT_FORK(gap_ncore(), (void *) KerParConvDW3x3Stride1B32_SQ8, (void *) KerArg0);
			__CALL(KerParConvDW3x3Stride1B32_SQ8, KerArg0);
			KerArg1->Out = (void *__restrict__) (lynred_L1_Memory+12160+3200*((D0Ind_Total)%2));
			KerArg1->Scale = (unsigned char *__restrict__) (lynred_L1_Memory+7936+((D0Ind)*8));
			KerArg1->ScaleN = (unsigned char *__restrict__) (lynred_L1_Memory+8320+((D0Ind)*8));
			AT_FORK(gap_ncore(), (void *) KerParReduct_CC_ReLU_SQ8, (void *) KerArg1);
			__CALL(KerParReduct_CC_ReLU_SQ8, KerArg1);
		} /* End iteration on Tile0 */
		/*================================= Write Tiles =====================================*/
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
		if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR3); /* Wait previous uDMA write Out */
		if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+52836+3200*((D0Ind_Total+-1)%2)),
					_SP_Out, 400, _LP_Out, 1, &UchanHR3);
		AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+52836+3200*((D0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+12160+3200*((D0Ind_Total)%2)),
				_SC_Out, 1, &DmaW_Evt1);
		/*============================= End Write Tiles =====================================*/
		/*================================= Update Arg Pipeline =============================*/
		_SN_In = _SNN_In;_LN_In = _LNN_In;
		_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
		_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
		/*============================= End Update Arg Pipeline =============================*/
		/*================================= Prepare Tiles ===================================*/
		_SC_Out = 0;
		if (!(D0Ind_Last)) {
			_C_Out = _C_Out + (3200); _LC_Out = (400); _SC_Out = (8*_LC_Out); 
		}
		/*============================= End Prepare Tiles ===================================*/
	} /* End iteration on D0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR3); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+52836+3200*((D0Ind_Total+-1)%2)), _SP_Out, 400, _LP_Out, 1, &UchanHR3);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR3); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S77_Conv2d_64x384x1x1(
		signed char * __restrict__ In2,
		signed char * __restrict__ In1,
		int * __restrict__ Bias,
		signed char * __restrict__ Out,
		unsigned char * __restrict__ Scale,
		unsigned char * __restrict__ ScaleN,
		signed char * __restrict__ Infos)

{
	/* Shared L1: 44428 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaR_Evt4;
	AT_L2_EVENT DmaR_Evt5;
	AT_L2_EVENT DmaR_Evt6;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF2;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF3;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF4;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF5;
	KerMatMul_SQ8_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T1Ind, T1Ind_Total=0, T1Ind_Last, T1Ind_NextLast, T1Ind_NextNextLast;
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	unsigned int _NN_In2;
	unsigned int _SN_In2, _SNN_In2;
	unsigned int _LN_In2, _LNN_In2;
	unsigned int _C_Out;
	unsigned int _SP_Out, _SC_Out;
	unsigned int _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile1 Dim: 20][Tile0 Dim: 1]
	Ker Arg: In2, Tiled Space: Tile1
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 20 logical tiles, 20 physical tiles
			Total Size: 153600 [Tile1, 20:[384x20, 18:384x20, 384x20], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 20:[384x20, 18:384x20, 384x20], 1]
		Tile0: [0, 7680, 20], Tile1: [20, 7680, 20], Tile2; [40, 7680, 20]
	Ker Arg: In1, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 24576 [Tile0, 1:[384x64], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[384x64], 1]
		Tile0: [0, 24576, 24576], Tile1: [0, 24576, 24576], Tile2; [0, 24576, 24576]
	Ker Arg: KerBuff, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 20 logical tiles, 1 physical tiles
			Total Size: 1536 [Tile1, 20:[1536x1, 18:1536x1, 1536x1], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 20:[1536x1, 18:1536x1, 1536x1], 1]
		Tile0: [0, 1536, 1536], Tile1: [0, 1536, 1536], Tile2; [0, 1536, 1536]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 256 [Tile0, 1:[1x64], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x64], 4]
		Tile0: [0, 256, 256], Tile1: [0, 256, 256], Tile2; [0, 256, 256]
	Ker Arg: Out, Tiled Space: Tile1
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 20 logical tiles, 20 physical tiles
			Total Size: 25600 [Tile1, 20:[64x20, 18:64x20, 64x20], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 20:[64x20, 18:64x20, 64x20], 1]
		Tile0: [0, 1280, 20], Tile1: [20, 1280, 20], Tile2; [40, 1280, 20]
	Ker Arg: Scale, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 64 [Tile0, 1:[1x64], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x64], 1]
		Tile0: [0, 64, 64], Tile1: [0, 64, 64], Tile2; [0, 64, 64]
	Ker Arg: ScaleN, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 64 [Tile0, 1:[1x64], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x64], 1]
		Tile0: [0, 64, 64], Tile1: [0, 64, 64], Tile2; [0, 64, 64]
	Ker Arg: Infos, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 20 logical tiles, 1 physical tiles
			Total Size: 9 [Tile1, 20:[1x1, 18:1x1, 1x1], 9]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 20:[1x1, 18:1x1, 1x1], 9]
		Tile0: [0, 9, 9], Tile1: [0, 9, 9], Tile2; [0, 9, 9]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In1 = (signed char * __restrict__) (lynred_L1_Memory+19468);
	KerArg0->W_In1 = (unsigned short int) (384);
	KerArg0->H_In1 = (unsigned short int) (64);
	KerArg0->W_In2 = (unsigned short int) (20);
	KerArg0->Bias = (void * __restrict__) (lynred_L1_Memory+44044);
	KerArg0->Scale = (unsigned char * __restrict__) (lynred_L1_Memory+44300);
	KerArg0->ScaleN = (unsigned char * __restrict__) (lynred_L1_Memory+44364);
	KerArg0->W_Out = (unsigned short int) (20);
	KerArg0->BufferColIn2 = (signed char * __restrict__) (lynred_L1_Memory+0);
	KerArg0->ColFirst = (unsigned char) (1);
	KerArg0->Infos = (signed char *__restrict__) (lynred_L1_Memory+19456);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+0), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), 7680, 400, 20, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In2 */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+20), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+7680), 7680, 400, 20, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+1536+0), 7680, 0, &DmaR_Evt1);
	_NN_In2=20; _SN_In2=7680;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In1+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+19468), 24576, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read In1 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Bias+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+87396+0), 256, 0, &UchanHF2);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF2); /* Wait previous uDMA read Bias */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+87396+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+44044), 256, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Bias */
	_C_Out=0; _SC_Out=1280; _LC_Out=20;
	_SP_Out=0;
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Scale+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+87652+0), 64, 0, &UchanHF3);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF3); /* Wait previous uDMA read Scale */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+87652+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+44300), 64, 0, &DmaR_Evt4);
	AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read Scale */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) ScaleN+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+87716+0), 64, 0, &UchanHF4);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF4); /* Wait previous uDMA read ScaleN */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+87716+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+44364), 64, 0, &DmaR_Evt5);
	AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read ScaleN */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Infos+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+87780+0), 9, 0, &UchanHF5);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF5); /* Wait previous uDMA read Infos */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+87780+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+19456), 9, 0, &DmaR_Evt6);
	AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Infos */
	/*============================= End Read Tiles Prolog ===============================*/
	for (T1Ind=0; T1Ind<20; T1Ind++, T1Ind_Total++) { /* Iteration on Tile1 */
		int T1Ind_Last = (T1Ind==19), T1Ind_NextLast = ((T1Ind+1)==19), T1Ind_NextNextLast = ((T1Ind+2)==19);
		/*================================= Prepare Tiles ===================================*/
		_SNN_In2 = 0;
		if (!(T1Ind_Last)) {
			if (!(T1Ind_NextLast)) {
				_NN_In2 = _NN_In2 + (20); _LNN_In2 = (20); _SNN_In2 = (384*_LNN_In2); 
			}
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In2 */
		if (_SNN_In2) {
			AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+_NN_In2), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+7680*((T1Ind_Total)%2)),
					_SNN_In2, 400, _LNN_In2, 0, &UchanHR1);
		}
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In2 */
		if (_SN_In2) {
			AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+7680*((T1Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+1536+7680*((T1Ind_Total+1)%2)),
					_SN_In2, 0, &DmaR_Evt1);
		}
		/*============================= End Read Tiles ======================================*/
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1;
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->In2 = (signed char * __restrict__) (lynred_L1_Memory+1536+7680*((T1Ind_Total)%2));
			KerArg0->Out = (signed char * __restrict__) (lynred_L1_Memory+16896+1280*((T1Ind_Total)%2));
			KerArg0->OutFirstCol = (unsigned short int) ((0)*64);
			KerArg0->NormBias = (unsigned char) (((char *)(lynred_L1_Memory+19456))[5]);
			AT_FORK(gap_ncore(), (void *) KerParMatMulB32_2x4_SQ8, (void *) KerArg0);
			__CALL(KerParMatMulB32_2x4_SQ8, KerArg0);
		} /* End iteration on Tile0 */
		/*================================= Write Tiles =====================================*/
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
		AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+16896+1280*((T1Ind_Total)%2)),
				_SC_Out, 400, _LC_Out, 1, &DmaW_Evt1);
		/*============================= End Write Tiles =====================================*/
		/*================================= Update Arg Pipeline =============================*/
		_SN_In2 = _SNN_In2;_LN_In2 = _LNN_In2;
		_SP_Out = _SC_Out;_LP_Out = _LC_Out;
		/*============================= End Update Arg Pipeline =============================*/
		/*================================= Prepare Tiles ===================================*/
		_SC_Out = 0;
		if (!(T1Ind_Last)) {
			_C_Out = _C_Out + (20); _LC_Out = (20); _SC_Out = (64*_LC_Out); 
		}
		/*============================= End Prepare Tiles ===================================*/
	} /* End iteration on Tile1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S78_MatAdd_64x20x20(
		signed char * __restrict__ In1,
		signed char * __restrict__ In2,
		signed char * __restrict__ Out,
		signed char * __restrict__ Infos)

{
	/* Shared L1: 49980 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF1;
	KerMat3_SQ8_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast;
	/* User kernel arguments related variables */
	unsigned int _N_In1;
	unsigned int _SN_In1;
	unsigned int _N_In2;
	unsigned int _SN_In2;
	unsigned int _C_Out;
	unsigned int _SP_Out, _SC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile0 Dim: 4]
	Ker Arg: In1, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 4 logical tiles, 4 physical tiles
			Total Size: 25600 [Tile0, 4:[1x8328, 2:1x8328, 1x616], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 4:[1x8328, 2:1x8328, 1x616], 1]
		Tile0: [0, 8328, 8328], Tile1: [8328, 8328, 8328], Tile2; [16656, 8328, 8328]
	Ker Arg: In2, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 4 logical tiles, 4 physical tiles
			Total Size: 25600 [Tile0, 4:[1x8328, 2:1x8328, 1x616], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 4:[1x8328, 2:1x8328, 1x616], 1]
		Tile0: [0, 8328, 8328], Tile1: [8328, 8328, 8328], Tile2; [16656, 8328, 8328]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 4 logical tiles, 4 physical tiles
			Total Size: 25600 [Tile0, 4:[1x8328, 2:1x8328, 1x616], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 4:[1x8328, 2:1x8328, 1x616], 1]
		Tile0: [0, 8328, 8328], Tile1: [8328, 8328, 8328], Tile2; [16656, 8328, 8328]
	Ker Arg: Infos, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 4 logical tiles, 1 physical tiles
			Total Size: 9 [Tile0, 4:[1x1, 2:1x1, 1x1], 9]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 4:[1x1, 2:1x1, 1x1], 9]
		Tile0: [0, 9, 9], Tile1: [0, 9, 9], Tile2; [0, 9, 9]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->DoScale = (unsigned char) (1);
	KerArg0->Infos = (signed char *__restrict__) (lynred_L1_Memory+49968);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In1+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+0+0), 8328, 0, &DmaR_Evt1);
	_N_In1=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In2+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+16656+0), 8328, 0, &DmaR_Evt2);
	_N_In2=0;
	_C_Out=0; _SC_Out=8328;
	_SP_Out=0;
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Infos+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), 9, 0, &UchanHF1);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1); /* Wait previous uDMA read Infos */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+49968), 9, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Infos */
	/*============================= End Read Tiles Prolog ===============================*/
	for (T0Ind=0; T0Ind<4; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
		int T0Ind_Last = (T0Ind==3), T0Ind_NextLast = ((T0Ind+1)==3);
		/*================================= Prepare Tiles ===================================*/
		_SN_In1 = 0;
		if (!(T0Ind_Last)) {
			_N_In1 = _N_In1 + (8328); _SN_In1 = ((T0Ind_NextLast)?616:8328); 
		}
		_SN_In2 = 0;
		if (!(T0Ind_Last)) {
			_N_In2 = _N_In2 + (8328); _SN_In2 = ((T0Ind_NextLast)?616:8328); 
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In1 */
		if (_SN_In1) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In1+_N_In1), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+0+8328*((T0Ind_Total+1)%2)),
					_SN_In1, 0, &DmaR_Evt1);
		}
		AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read In2 */
		if (_SN_In2) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In2+_N_In2), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+16656+8328*((T0Ind_Total+1)%2)),
					_SN_In2, 0, &DmaR_Evt2);
		}
		/*============================= End Read Tiles ======================================*/
		/*====================== Call Kernel LOC_LOOP =========================*/
		KerArg0->In1 = (signed char *__restrict__) (lynred_L1_Memory+0+8328*((T0Ind_Total)%2));
		KerArg0->In2 = (signed char *__restrict__) (lynred_L1_Memory+16656+8328*((T0Ind_Total)%2));
		KerArg0->Out = (signed char *__restrict__) (lynred_L1_Memory+33312+8328*((T0Ind_Total)%2));
		KerArg0->Feat = (unsigned short int) (T0Ind_Last?616:8328);
		AT_FORK(gap_ncore(), (void *) KerMatAdd_SQ8, (void *) KerArg0);
		__CALL(KerMatAdd_SQ8, KerArg0);
		/*================================= Write Tiles =====================================*/
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+33312+8328*((T0Ind_Total)%2)),
				_SC_Out, 1, &DmaW_Evt1);
		/*============================= End Write Tiles =====================================*/
		/*================================= Update Arg Pipeline =============================*/
		_SP_Out = _SC_Out;
		/*============================= End Update Arg Pipeline =============================*/
		/*================================= Prepare Tiles ===================================*/
		_SC_Out = 0;
		if (!(T0Ind_Last)) {
			_C_Out = _C_Out + (8328); _SC_Out = ((T0Ind_NextLast)?616:8328); 
		}
		/*============================= End Prepare Tiles ===================================*/
	} /* End iteration on Tile0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S81_Conv2d_384x64x1x1_Relu(
		signed char * __restrict__ In2,
		signed char * __restrict__ In1,
		int * __restrict__ Bias,
		signed char * __restrict__ Out,
		unsigned char * __restrict__ Scale,
		unsigned char * __restrict__ ScaleN,
		signed char * __restrict__ Infos)

{
	/* Shared L1: 48140 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaR_Evt4;
	AT_L2_EVENT DmaR_Evt5;
	AT_L2_EVENT DmaR_Evt6;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF1;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF2;
	AT_HYPERRAM_CL_EVENT UchanHR6;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF3;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF4;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF5;
	KerMatMul_SQ8_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T1Ind, T1Ind_Total=0, T1Ind_Last, T1Ind_NextLast;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast, T0Ind_NextNextLast;
	/* User kernel arguments related variables */
	unsigned int _NN_In1;
	unsigned int _SN_In1, _SNN_In1;
	unsigned int _N_In2;
	unsigned int _SN_In2;
	unsigned int _LN_In2;
	unsigned int _P_Out, _C_Out;
	unsigned int _SPP_Out, _SP_Out, _SC_Out;
	unsigned int _LPP_Out, _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile1 Dim: 15][Tile0 Dim: 3]
	Ker Arg: KerBuff, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 15 logical tiles, 1 physical tiles
			Total Size: 256 [Tile1, 15:[256x1, 13:256x1, 256x1], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 15:[256x1, 13:256x1, 256x1], 1]
		Tile0: [0, 256, 256], Tile1: [0, 256, 256], Tile2; [0, 256, 256]
	Ker Arg: In1, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 3 logical tiles, 3 physical tiles
			Total Size: 24576 [Tile0, 3:[64x160, 1:64x160, 64x64], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 3:[64x160, 1:64x160, 64x64], 1]
		Tile0: [0, 10240, 10240], Tile1: [10240, 10240, 10240], Tile2; [20480, 4096, 4096]
	Ker Arg: In2, Tiled Space: Tile1
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 15 logical tiles, 15 physical tiles
			Total Size: 25600 [Tile1, 15:[64x28, 13:64x28, 64x8], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 15:[64x28, 13:64x28, 64x8], 1]
		Tile0: [0, 1792, 28], Tile1: [28, 1792, 28], Tile2; [56, 1792, 28]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 3 logical tiles, 1 physical tiles
			Total Size: 1536 [Tile0, 3:[1x160, 1:1x160, 1x64], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 3:[1x160, 1:1x160, 1x64], 4]
		Tile0: [0, 1536, 1536], Tile1: [0, 1536, 1536], Tile2; [0, 1536, 1536]
	Ker Arg: Out, Tiled Space: Tile1
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 15 logical tiles, 15 physical tiles
			Total Size: 153600 [Tile1, 15:[384x28, 13:384x28, 384x8], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 15:[384x28, 13:384x28, 384x8], 1]
		Tile0: [0, 10752, 28], Tile1: [28, 10752, 28], Tile2; [56, 10752, 28]
	Ker Arg: Scale, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 3 logical tiles, 1 physical tiles
			Total Size: 384 [Tile0, 3:[1x160, 1:1x160, 1x64], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 3:[1x160, 1:1x160, 1x64], 1]
		Tile0: [0, 384, 384], Tile1: [0, 384, 384], Tile2; [0, 384, 384]
	Ker Arg: ScaleN, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 3 logical tiles, 1 physical tiles
			Total Size: 384 [Tile0, 3:[1x160, 1:1x160, 1x64], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 3:[1x160, 1:1x160, 1x64], 1]
		Tile0: [0, 384, 384], Tile1: [0, 384, 384], Tile2; [0, 384, 384]
	Ker Arg: Infos, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 15 logical tiles, 1 physical tiles
			Total Size: 9 [Tile1, 15:[1x1, 13:1x1, 1x1], 9]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 15:[1x1, 13:1x1, 1x1], 9]
		Tile0: [0, 9, 9], Tile1: [0, 9, 9], Tile2; [0, 9, 9]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->W_In1 = (unsigned short int) (64);
	KerArg0->BufferColIn2 = (signed char * __restrict__) (lynred_L1_Memory+0);
	KerArg0->ColFirst = (unsigned char) (1);
	KerArg0->Infos = (signed char *__restrict__) (lynred_L1_Memory+25344);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) In1+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+67940+0), 10240, 0, &UchanHF1);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1); /* Wait previous uDMA read In1 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) In1+10240), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+67940+10240), 10240, 0, &UchanHF1);
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+67940+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+25356+0), 10240, 0, &DmaR_Evt1);
	_NN_In1=10240; _SN_In1=10240;
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In2+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+256+0), 1792, 400, 28, 0, &DmaR_Evt2);
	_N_In2=0;
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Bias+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+91876+0), 1536, 0, &UchanHF2);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF2); /* Wait previous uDMA read Bias */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+91876+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+45836), 1536, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Bias */
	_C_Out=0; _SC_Out=10752; _LC_Out=28;
	_SPP_Out=0; _SP_Out=0;
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Scale+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+93412+0), 384, 0, &UchanHF3);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF3); /* Wait previous uDMA read Scale */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+93412+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+47372), 384, 0, &DmaR_Evt4);
	AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read Scale */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) ScaleN+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+93796+0), 384, 0, &UchanHF4);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF4); /* Wait previous uDMA read ScaleN */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+93796+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+47756), 384, 0, &DmaR_Evt5);
	AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read ScaleN */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Infos+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+94180+0), 9, 0, &UchanHF5);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF5); /* Wait previous uDMA read Infos */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+94180+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+25344), 9, 0, &DmaR_Evt6);
	AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Infos */
	/*============================= End Read Tiles Prolog ===============================*/
	for (T1Ind=0; T1Ind<15; T1Ind++, T1Ind_Total++) { /* Iteration on Tile1 */
		int T1Ind_Last = (T1Ind==14), T1Ind_NextLast = ((T1Ind+1)==14);
		/*================================= Prepare Tiles ===================================*/
		_SN_In2 = 0;
		if (!(T1Ind_Last)) {
			_N_In2 = _N_In2 + (28); _LN_In2 = ((T1Ind_NextLast)?8:28); _SN_In2 = (64*_LN_In2); 
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read In2 */
		if (_SN_In2) {
			AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In2+_N_In2), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+256+1792*((T1Ind_Total+1)%2)),
					_SN_In2, 400, _LN_In2, 0, &DmaR_Evt2);
		}
		/*============================= End Read Tiles ======================================*/
		for (T0Ind=0; T0Ind<3; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==2), T0Ind_NextLast = ((T0Ind+1)==2), T0Ind_NextNextLast = ((T0Ind+2)==2);
			/*================================= Prepare Tiles ===================================*/
			_SNN_In1 = 0;
			if (!(T0Ind_Last)) {
				if (!(T0Ind_NextLast)) {
					_NN_In1 = _NN_In1 + (10240); _SNN_In1 = ((1)?4096:10240); 
				} else if (!(T1Ind_Last)) {
					_NN_In1 = _NN_In1 + (-20480); _SNN_In1 = (10240); 
				}
			} else if (!((T1Ind_Last))) {
				_NN_In1 = _NN_In1 + (10240); _SNN_In1 = (10240); 
			}
			/*============================= End Prepare Tiles ===================================*/
			/*================================= Read Tiles ======================================*/
			AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1); /* Wait previous uDMA read In1 */
			if (_SNN_In1) {
				AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) In1+_NN_In1), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+67940+10240*((T0Ind_Total)%2)),
						_SNN_In1, 0, &UchanHF1);
			}
			AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In1 */
			if (_SN_In1) {
				AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+67940+10240*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+25356+10240*((T0Ind_Total+1)%2)),
						_SN_In1, 0, &DmaR_Evt1);
			}
			/*============================= End Read Tiles ======================================*/
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->In1 = (signed char * __restrict__) (lynred_L1_Memory+25356+10240*((T0Ind_Total)%2));
			KerArg0->H_In1 = (unsigned short int) (T0Ind_Last?64:160);
			KerArg0->In2 = (signed char * __restrict__) (lynred_L1_Memory+256+1792*((T1Ind_Total)%2));
			KerArg0->W_In2 = (unsigned short int) ((T1Ind_Last)?8:28);
			KerArg0->Bias = (void * __restrict__) (lynred_L1_Memory+45836+(640*(T0Ind)));
			KerArg0->Scale = (unsigned char * __restrict__) (lynred_L1_Memory+47372+(160*(T0Ind)));
			KerArg0->ScaleN = (unsigned char * __restrict__) (lynred_L1_Memory+47756+(160*(T0Ind)));
			KerArg0->Out = (signed char * __restrict__) (lynred_L1_Memory+3840+10752*((T1Ind_Total)%2));
			KerArg0->W_Out = (unsigned short int) ((T1Ind_Last)?8:28);
			KerArg0->OutFirstCol = (unsigned short int) ((T0Ind)*160);
			KerArg0->NormBias = (unsigned char) (((char *)(lynred_L1_Memory+25344))[5]);
			AT_FORK(gap_ncore(), (void *) KerParMatMulB32_2x4_ReLU_SQ8, (void *) KerArg0);
			__CALL(KerParMatMulB32_2x4_ReLU_SQ8, KerArg0);
			/*================================= Update Arg Pipeline =============================*/
			_SN_In1 = _SNN_In1;
			/*============================= End Update Arg Pipeline =============================*/
		} /* End iteration on Tile0 */
		/*================================= Write Tiles =====================================*/
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
		if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR6); /* Wait previous uDMA write Out */
		if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+10752*((T1Ind_Total+-1)%2)),
					_SP_Out, 400, _LP_Out, 1, &UchanHR6);
		AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+10752*((T1Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+3840+10752*((T1Ind_Total)%2)),
				_SC_Out, 1, &DmaW_Evt1);
		/*============================= End Write Tiles =====================================*/
		/*================================= Update Arg Pipeline =============================*/
		_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
		_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
		/*============================= End Update Arg Pipeline =============================*/
		/*================================= Prepare Tiles ===================================*/
		_SC_Out = 0;
		if (!(T1Ind_Last)) {
			_C_Out = _C_Out + (28); _LC_Out = ((T1Ind_NextLast)?8:28); _SC_Out = (384*_LC_Out); 
		}
		/*============================= End Prepare Tiles ===================================*/
	} /* End iteration on Tile1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR6); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+10752*((T1Ind_Total+-1)%2)), _SP_Out, 400, _LP_Out, 1, &UchanHR6);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR6); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S84_Conv2d_384x1x3x3_Relu(
		signed char * __restrict__ In,
		signed char * __restrict__ Filter,
		int * __restrict__ Bias,
		signed char * __restrict__ Out,
		unsigned char * __restrict__ Scale,
		unsigned char * __restrict__ ScaleN,
		signed char * __restrict__ Infos)

{
	/* Shared L1: 31372 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaR_Evt4;
	AT_L2_EVENT DmaR_Evt5;
	AT_L2_EVENT DmaR_Evt6;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF2;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF3;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF4;
	AT_HYPERRAM_CL_EVENT UchanHR6;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF5;
	KerConv_SQ8_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerConvLinReduct_SQ8_T S_KerArg1, *KerArg1 = &S_KerArg1;

	/* Iteration space related variables */
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast, D0Ind_NextNextLast;
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	unsigned int _NN_In;
	unsigned int _SN_In, _SNN_In;
	unsigned int _LN_In, _LNN_In;
	unsigned int _P_Out, _C_Out;
	unsigned int _SPP_Out, _SP_Out, _SC_Out;
	unsigned int _LPP_Out, _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D0 Dim: Init: 384, Tiled: 48][Tile0 Dim: 1]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 48 logical tiles, 48 physical tiles
			Total Size: 153600 [D0, [47 x 3200, 3200]][Tile0, 1:[20x20], 1]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [47 x 3200, 3200]][Tile0, 1:[20x20], 1]
		Tile0: [0, 3200, 400], Tile1: [3200, 3200, 400], Tile2; [6400, 3200, 400]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 48 logical tiles, 1 physical tiles
			Total Size: 1536 [D0, [47 x 32, 32]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [47 x 32, 32]]
		Tile0: [0, 1536, 1536], Tile1: [0, 1536, 1536], Tile2; [0, 1536, 1536]
	Ker Arg: Scale, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 48 logical tiles, 1 physical tiles
			Total Size: 384 [D0, [47 x 8, 8]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [47 x 8, 8]]
		Tile0: [0, 384, 384], Tile1: [0, 384, 384], Tile2; [0, 384, 384]
	Ker Arg: ScaleN, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 48 logical tiles, 1 physical tiles
			Total Size: 384 [D0, [47 x 8, 8]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [47 x 8, 8]]
		Tile0: [0, 384, 384], Tile1: [0, 384, 384], Tile2; [0, 384, 384]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 48 logical tiles, 1 physical tiles
			Total Size: 3456 [D0, [47 x 72, 72]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [47 x 72, 72]]
		Tile0: [0, 3456, 3456], Tile1: [0, 3456, 3456], Tile2; [0, 3456, 3456]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 48 logical tiles, 48 physical tiles
			Total Size: 153600 [D0, [47 x 3200, 3200]][Tile0, 1:[20x20], 1]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [47 x 3200, 3200]][Tile0, 1:[20x20], 1]
		Tile0: [0, 3200, 400], Tile1: [3200, 3200, 400], Tile2; [6400, 3200, 400]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 48 logical tiles, 1 physical tiles
			Total Size: 614400 [D0, [47 x 12800, 12800]][Tile0, 1:[20x20], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [47 x 12800, 12800]][Tile0, 1:[20x20], 4]
		Tile0: [0, 12800, 1600], Tile1: [0, 12800, 1600], Tile2; [0, 12800, 1600]
	Ker Arg: Infos, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 9 [Tile0, 1:[9x1], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[9x1], 1]
		Tile0: [0, 9, 9], Tile1: [0, 9, 9], Tile2; [0, 9, 9]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->W = (unsigned short int) (20);
	KerArg0->UsedW = (unsigned short int) (20);
	KerArg0->InFeatures = (unsigned short int) (8);
	KerArg0->OutFeatures = (unsigned short int) (8);
	KerArg0->TotalInFeatures = (unsigned short int) (384);
	KerArg0->Out = (int * __restrict__) (lynred_L1_Memory+18560);
	KerArg0->Pad = (v4s) ((v4s){1,1,1,1});
	KerArg1->In = (int *__restrict__) (lynred_L1_Memory+18560);
	KerArg1->Feat = (unsigned short int) (8);
	KerArg1->W = (unsigned short int) (20);
	KerArg1->H = (unsigned short int) (20);
	KerArg1->Infos = (signed char *__restrict__) (lynred_L1_Memory+31360);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), 3200, 400, 400, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+3200), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+3200), 3200, 400, 400, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+0+0), 3200, 0, &DmaR_Evt1);
	_NN_In=3200; _SN_In=3200;
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Bias+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+59236+0), 1536, 0, &UchanHF2);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF2); /* Wait previous uDMA read Bias */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+59236+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+6400), 1536, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Bias */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Scale+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+60772+0), 384, 0, &UchanHF3);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF3); /* Wait previous uDMA read Scale */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+60772+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+7936), 384, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Scale */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) ScaleN+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+61156+0), 384, 0, &UchanHF4);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF4); /* Wait previous uDMA read ScaleN */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+61156+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+8320), 384, 0, &DmaR_Evt4);
	AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read ScaleN */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+8704), 3456, 0, &DmaR_Evt5);
	AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read Filter */
	_C_Out=0; _SC_Out=3200; _LC_Out=400;
	_SPP_Out=0; _SP_Out=0;
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Infos+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+61540+0), 9, 0, &UchanHF5);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF5); /* Wait previous uDMA read Infos */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+61540+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+31360), 9, 0, &DmaR_Evt6);
	AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Infos */
	/*============================= End Read Tiles Prolog ===============================*/
	for (D0Ind=0; D0Ind<48; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
		int D0Ind_Last = (D0Ind==47), D0Ind_NextLast = ((D0Ind+1)==47), D0Ind_NextNextLast = ((D0Ind+2)==47);
		/*================================= Prepare Tiles ===================================*/
		_SNN_In = 0;
		if (!(D0Ind_Last)) {
			if (!(D0Ind_NextLast)) {
				_NN_In = _NN_In + (3200); _LNN_In = (400); _SNN_In = (8*_LNN_In); 
			}
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
		if (_SNN_In) {
			AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+_NN_In), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+3200*((D0Ind_Total)%2)),
					_SNN_In, 400, _LNN_In, 0, &UchanHR1);
		}
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
		if (_SN_In) {
			AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+3200*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+0+3200*((D0Ind_Total+1)%2)),
					_SN_In, 0, &DmaR_Evt1);
		}
		/*============================= End Read Tiles ======================================*/
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1;
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->In = (signed char * __restrict__) (lynred_L1_Memory+0+3200*((D0Ind_Total)%2));
			KerArg0->H = (unsigned short int) (22-1*(1)-1*(1));
			KerArg0->UsedH = (unsigned short int) (22-1*(1)-1*(1));
			KerArg0->Filter = (signed char * __restrict__) (lynred_L1_Memory+8704+((D0Ind)*72));
			KerArg0->Bias = (signed char * __restrict__) (lynred_L1_Memory+6400+((D0Ind)*32));
			KerArg0->NormBias = (unsigned char) (((char *)(lynred_L1_Memory+31360))[5]);
			AT_FORK(gap_ncore(), (void *) KerParConvDW3x3Stride1B32_SQ8, (void *) KerArg0);
			__CALL(KerParConvDW3x3Stride1B32_SQ8, KerArg0);
			KerArg1->Out = (void *__restrict__) (lynred_L1_Memory+12160+3200*((D0Ind_Total)%2));
			KerArg1->Scale = (unsigned char *__restrict__) (lynred_L1_Memory+7936+((D0Ind)*8));
			KerArg1->ScaleN = (unsigned char *__restrict__) (lynred_L1_Memory+8320+((D0Ind)*8));
			AT_FORK(gap_ncore(), (void *) KerParReduct_CC_ReLU_SQ8, (void *) KerArg1);
			__CALL(KerParReduct_CC_ReLU_SQ8, KerArg1);
		} /* End iteration on Tile0 */
		/*================================= Write Tiles =====================================*/
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
		if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR6); /* Wait previous uDMA write Out */
		if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+52836+3200*((D0Ind_Total+-1)%2)),
					_SP_Out, 400, _LP_Out, 1, &UchanHR6);
		AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+52836+3200*((D0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+12160+3200*((D0Ind_Total)%2)),
				_SC_Out, 1, &DmaW_Evt1);
		/*============================= End Write Tiles =====================================*/
		/*================================= Update Arg Pipeline =============================*/
		_SN_In = _SNN_In;_LN_In = _LNN_In;
		_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
		_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
		/*============================= End Update Arg Pipeline =============================*/
		/*================================= Prepare Tiles ===================================*/
		_SC_Out = 0;
		if (!(D0Ind_Last)) {
			_C_Out = _C_Out + (3200); _LC_Out = (400); _SC_Out = (8*_LC_Out); 
		}
		/*============================= End Prepare Tiles ===================================*/
	} /* End iteration on D0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR6); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+52836+3200*((D0Ind_Total+-1)%2)), _SP_Out, 400, _LP_Out, 1, &UchanHR6);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR6); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S87_Conv2d_96x384x1x1(
		signed char * __restrict__ In2,
		signed char * __restrict__ In1,
		int * __restrict__ Bias,
		signed char * __restrict__ Out,
		unsigned char * __restrict__ Scale,
		unsigned char * __restrict__ ScaleN,
		signed char * __restrict__ Infos)

{
	/* Shared L1: 45900 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaR_Evt4;
	AT_L2_EVENT DmaR_Evt5;
	AT_L2_EVENT DmaR_Evt6;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF2;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF3;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF4;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF5;
	KerMatMul_SQ8_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T1Ind, T1Ind_Total=0, T1Ind_Last, T1Ind_NextLast, T1Ind_NextNextLast;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast;
	/* User kernel arguments related variables */
	unsigned int _N_In1;
	unsigned int _SN_In1;
	unsigned int _NN_In2;
	unsigned int _SN_In2, _SNN_In2;
	unsigned int _LN_In2, _LNN_In2;
	unsigned int _C_Out;
	unsigned int _SP_Out, _SC_Out;
	unsigned int _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile1 Dim: 20][Tile0 Dim: 3]
	Ker Arg: KerBuff, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 20 logical tiles, 1 physical tiles
			Total Size: 1536 [Tile1, 20:[1536x1, 18:1536x1, 1536x1], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 20:[1536x1, 18:1536x1, 1536x1], 1]
		Tile0: [0, 1536, 1536], Tile1: [0, 1536, 1536], Tile2; [0, 1536, 1536]
	Ker Arg: In1, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 3 logical tiles, 3 physical tiles
			Total Size: 36864 [Tile0, 3:[384x32, 1:384x32, 384x32], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 3:[384x32, 1:384x32, 384x32], 1]
		Tile0: [0, 12288, 12288], Tile1: [12288, 12288, 12288], Tile2; [24576, 12288, 12288]
	Ker Arg: In2, Tiled Space: Tile1
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 20 logical tiles, 20 physical tiles
			Total Size: 153600 [Tile1, 20:[384x20, 18:384x20, 384x20], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 20:[384x20, 18:384x20, 384x20], 1]
		Tile0: [0, 7680, 20], Tile1: [20, 7680, 20], Tile2; [40, 7680, 20]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 3 logical tiles, 1 physical tiles
			Total Size: 384 [Tile0, 3:[1x32, 1:1x32, 1x32], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 3:[1x32, 1:1x32, 1x32], 4]
		Tile0: [0, 384, 384], Tile1: [0, 384, 384], Tile2; [0, 384, 384]
	Ker Arg: Out, Tiled Space: Tile1
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 20 logical tiles, 20 physical tiles
			Total Size: 38400 [Tile1, 20:[96x20, 18:96x20, 96x20], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 20:[96x20, 18:96x20, 96x20], 1]
		Tile0: [0, 1920, 20], Tile1: [20, 1920, 20], Tile2; [40, 1920, 20]
	Ker Arg: Scale, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 3 logical tiles, 1 physical tiles
			Total Size: 96 [Tile0, 3:[1x32, 1:1x32, 1x32], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 3:[1x32, 1:1x32, 1x32], 1]
		Tile0: [0, 96, 96], Tile1: [0, 96, 96], Tile2; [0, 96, 96]
	Ker Arg: ScaleN, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 3 logical tiles, 1 physical tiles
			Total Size: 96 [Tile0, 3:[1x32, 1:1x32, 1x32], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 3:[1x32, 1:1x32, 1x32], 1]
		Tile0: [0, 96, 96], Tile1: [0, 96, 96], Tile2; [0, 96, 96]
	Ker Arg: Infos, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 20 logical tiles, 1 physical tiles
			Total Size: 9 [Tile1, 20:[1x1, 18:1x1, 1x1], 9]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 20:[1x1, 18:1x1, 1x1], 9]
		Tile0: [0, 9, 9], Tile1: [0, 9, 9], Tile2; [0, 9, 9]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->W_In1 = (unsigned short int) (384);
	KerArg0->H_In1 = (unsigned short int) (32);
	KerArg0->W_In2 = (unsigned short int) (20);
	KerArg0->W_Out = (unsigned short int) (20);
	KerArg0->BufferColIn2 = (signed char * __restrict__) (lynred_L1_Memory+0);
	KerArg0->ColFirst = (unsigned char) (1);
	KerArg0->Infos = (signed char *__restrict__) (lynred_L1_Memory+20736);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In1+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+20748+0), 12288, 0, &DmaR_Evt1);
	_N_In1=0;
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+0), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), 7680, 400, 20, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In2 */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+20), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+7680), 7680, 400, 20, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+1536+0), 7680, 0, &DmaR_Evt2);
	_NN_In2=20; _SN_In2=7680;
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Bias+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+137060+0), 384, 0, &UchanHF2);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF2); /* Wait previous uDMA read Bias */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+137060+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+45324), 384, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Bias */
	_C_Out=0; _SC_Out=1920; _LC_Out=20;
	_SP_Out=0;
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Scale+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+137444+0), 96, 0, &UchanHF3);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF3); /* Wait previous uDMA read Scale */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+137444+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+45708), 96, 0, &DmaR_Evt4);
	AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read Scale */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) ScaleN+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+137540+0), 96, 0, &UchanHF4);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF4); /* Wait previous uDMA read ScaleN */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+137540+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+45804), 96, 0, &DmaR_Evt5);
	AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read ScaleN */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Infos+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+137636+0), 9, 0, &UchanHF5);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF5); /* Wait previous uDMA read Infos */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+137636+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+20736), 9, 0, &DmaR_Evt6);
	AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Infos */
	/*============================= End Read Tiles Prolog ===============================*/
	for (T1Ind=0; T1Ind<20; T1Ind++, T1Ind_Total++) { /* Iteration on Tile1 */
		int T1Ind_Last = (T1Ind==19), T1Ind_NextLast = ((T1Ind+1)==19), T1Ind_NextNextLast = ((T1Ind+2)==19);
		/*================================= Prepare Tiles ===================================*/
		_SNN_In2 = 0;
		if (!(T1Ind_Last)) {
			if (!(T1Ind_NextLast)) {
				_NN_In2 = _NN_In2 + (20); _LNN_In2 = (20); _SNN_In2 = (384*_LNN_In2); 
			}
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In2 */
		if (_SNN_In2) {
			AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+_NN_In2), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+7680*((T1Ind_Total)%2)),
					_SNN_In2, 400, _LNN_In2, 0, &UchanHR1);
		}
		AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read In2 */
		if (_SN_In2) {
			AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+7680*((T1Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+1536+7680*((T1Ind_Total+1)%2)),
					_SN_In2, 0, &DmaR_Evt2);
		}
		/*============================= End Read Tiles ======================================*/
		for (T0Ind=0; T0Ind<3; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==2), T0Ind_NextLast = ((T0Ind+1)==2);
			/*================================= Prepare Tiles ===================================*/
			_SN_In1 = 0;
			if (!(T0Ind_Last)) {
				_N_In1 = _N_In1 + (12288); _SN_In1 = (12288); 
			} else if (!(T1Ind_Last)) {
				_N_In1 = _N_In1 + (-24576); _SN_In1 = (12288); 
			}
			/*============================= End Prepare Tiles ===================================*/
			/*================================= Read Tiles ======================================*/
			AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In1 */
			if (_SN_In1) {
				AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In1+_N_In1), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+20748+12288*((T0Ind_Total+1)%2)),
						_SN_In1, 0, &DmaR_Evt1);
			}
			/*============================= End Read Tiles ======================================*/
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->In1 = (signed char * __restrict__) (lynred_L1_Memory+20748+12288*((T0Ind_Total)%2));
			KerArg0->In2 = (signed char * __restrict__) (lynred_L1_Memory+1536+7680*((T1Ind_Total)%2));
			KerArg0->Bias = (void * __restrict__) (lynred_L1_Memory+45324+(128*(T0Ind)));
			KerArg0->Scale = (unsigned char * __restrict__) (lynred_L1_Memory+45708+(32*(T0Ind)));
			KerArg0->ScaleN = (unsigned char * __restrict__) (lynred_L1_Memory+45804+(32*(T0Ind)));
			KerArg0->Out = (signed char * __restrict__) (lynred_L1_Memory+16896+1920*((T1Ind_Total)%2));
			KerArg0->OutFirstCol = (unsigned short int) ((T0Ind)*32);
			KerArg0->NormBias = (unsigned char) (((char *)(lynred_L1_Memory+20736))[5]);
			AT_FORK(gap_ncore(), (void *) KerParMatMulB32_2x4_SQ8, (void *) KerArg0);
			__CALL(KerParMatMulB32_2x4_SQ8, KerArg0);
			/*================================= Update Arg Pipeline =============================*/
			/*============================= End Update Arg Pipeline =============================*/
		} /* End iteration on Tile0 */
		/*================================= Write Tiles =====================================*/
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
		AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+16896+1920*((T1Ind_Total)%2)),
				_SC_Out, 400, _LC_Out, 1, &DmaW_Evt1);
		/*============================= End Write Tiles =====================================*/
		/*================================= Update Arg Pipeline =============================*/
		_SN_In2 = _SNN_In2;_LN_In2 = _LNN_In2;
		_SP_Out = _SC_Out;_LP_Out = _LC_Out;
		/*============================= End Update Arg Pipeline =============================*/
		/*================================= Prepare Tiles ===================================*/
		_SC_Out = 0;
		if (!(T1Ind_Last)) {
			_C_Out = _C_Out + (20); _LC_Out = (20); _SC_Out = (96*_LC_Out); 
		}
		/*============================= End Prepare Tiles ===================================*/
	} /* End iteration on Tile1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S90_Conv2d_576x96x1x1_Relu(
		signed char * __restrict__ In2,
		signed char * __restrict__ In1,
		int * __restrict__ Bias,
		signed char * __restrict__ Out,
		unsigned char * __restrict__ Scale,
		unsigned char * __restrict__ ScaleN,
		signed char * __restrict__ Infos)

{
	/* Shared L1: 47372 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaR_Evt4;
	AT_L2_EVENT DmaR_Evt5;
	AT_L2_EVENT DmaR_Evt6;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF1;
	AT_HYPERRAM_CL_EVENT UchanHR5;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF2;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF3;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF4;
	KerMatMul_SQ8_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T1Ind, T1Ind_Total=0, T1Ind_Last, T1Ind_NextLast, T1Ind_NextNextLast;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast;
	/* User kernel arguments related variables */
	unsigned int _N_In2;
	unsigned int _SN_In2;
	unsigned int _LN_In2;
	unsigned int _NN_In1;
	unsigned int _SN_In1, _SNN_In1;
	unsigned int _P_Out, _C_Out;
	unsigned int _SPP_Out, _SP_Out, _SC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile1 Dim: 15][Tile0 Dim: 20]
	Ker Arg: In2, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 20 logical tiles, 20 physical tiles
			Total Size: 38400 [Tile0, 20:[96x20, 18:96x20, 96x20], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 20:[96x20, 18:96x20, 96x20], 1]
		Tile0: [0, 1920, 20], Tile1: [20, 1920, 20], Tile2; [40, 1920, 20]
	Ker Arg: In1, Tiled Space: Tile1
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 15 logical tiles, 15 physical tiles
			Total Size: 55296 [Tile1, 15:[96x40, 13:96x40, 96x16], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 15:[96x40, 13:96x40, 96x16], 1]
		Tile0: [0, 3840, 3840], Tile1: [3840, 3840, 3840], Tile2; [7680, 3840, 3840]
	Ker Arg: KerBuff, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 20 logical tiles, 1 physical tiles
			Total Size: 384 [Tile0, 20:[384x1, 18:384x1, 384x1], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 20:[384x1, 18:384x1, 384x1], 1]
		Tile0: [0, 384, 384], Tile1: [0, 384, 384], Tile2; [0, 384, 384]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 15 logical tiles, 1 physical tiles
			Total Size: 2304 [Tile1, 15:[1x40, 13:1x40, 1x16], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 15:[1x40, 13:1x40, 1x16], 4]
		Tile0: [0, 2304, 2304], Tile1: [0, 2304, 2304], Tile2; [0, 2304, 2304]
	Ker Arg: Out, Tiled Space: Tile1
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 15 logical tiles, 15 physical tiles
			Total Size: 230400 [Tile1, 15:[400x40, 13:400x40, 400x16], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 15:[400x40, 13:400x40, 400x16], 1]
		Tile0: [0, 16000, 16000], Tile1: [16000, 16000, 16000], Tile2; [32000, 16000, 16000]
	Ker Arg: Scale, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 15 logical tiles, 1 physical tiles
			Total Size: 576 [Tile1, 15:[1x40, 13:1x40, 1x16], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 15:[1x40, 13:1x40, 1x16], 1]
		Tile0: [0, 576, 576], Tile1: [0, 576, 576], Tile2; [0, 576, 576]
	Ker Arg: ScaleN, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 15 logical tiles, 1 physical tiles
			Total Size: 576 [Tile1, 15:[1x40, 13:1x40, 1x16], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 15:[1x40, 13:1x40, 1x16], 1]
		Tile0: [0, 576, 576], Tile1: [0, 576, 576], Tile2; [0, 576, 576]
	Ker Arg: Infos, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 20 logical tiles, 1 physical tiles
			Total Size: 9 [Tile0, 20:[1x1, 18:1x1, 1x1], 9]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 20:[1x1, 18:1x1, 1x1], 9]
		Tile0: [0, 9, 9], Tile1: [0, 9, 9], Tile2; [0, 9, 9]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->W_In1 = (unsigned short int) (96);
	KerArg0->W_In2 = (unsigned short int) (20);
	KerArg0->W_Out = (unsigned short int) (400);
	KerArg0->BufferColIn2 = (signed char * __restrict__) (lynred_L1_Memory+43136);
	KerArg0->ColFirst = (unsigned char) (0);
	KerArg0->Infos = (signed char *__restrict__) (lynred_L1_Memory+47360);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In2+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+43520+0), 1920, 400, 20, 0, &DmaR_Evt1);
	_N_In2=0;
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) In1+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), 3840, 0, &UchanHF1);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1); /* Wait previous uDMA read In1 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) In1+3840), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+46436+3840), 3840, 0, &UchanHF1);
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+0+0), 3840, 0, &DmaR_Evt2);
	_NN_In1=3840; _SN_In1=3840;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+7680), 2304, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Bias */
	_C_Out=0; _SC_Out=16000;
	_SPP_Out=0; _SP_Out=0;
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Scale+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+56420+0), 576, 0, &UchanHF2);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF2); /* Wait previous uDMA read Scale */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+56420+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+41984), 576, 0, &DmaR_Evt4);
	AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read Scale */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) ScaleN+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+56996+0), 576, 0, &UchanHF3);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF3); /* Wait previous uDMA read ScaleN */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+56996+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+42560), 576, 0, &DmaR_Evt5);
	AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read ScaleN */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Infos+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+57572+0), 9, 0, &UchanHF4);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF4); /* Wait previous uDMA read Infos */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+57572+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+47360), 9, 0, &DmaR_Evt6);
	AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Infos */
	/*============================= End Read Tiles Prolog ===============================*/
	for (T1Ind=0; T1Ind<15; T1Ind++, T1Ind_Total++) { /* Iteration on Tile1 */
		int T1Ind_Last = (T1Ind==14), T1Ind_NextLast = ((T1Ind+1)==14), T1Ind_NextNextLast = ((T1Ind+2)==14);
		/*================================= Prepare Tiles ===================================*/
		_SNN_In1 = 0;
		if (!(T1Ind_Last)) {
			if (!(T1Ind_NextLast)) {
				_NN_In1 = _NN_In1 + (3840); _SNN_In1 = ((T1Ind_NextNextLast)?1536:3840); 
			}
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1); /* Wait previous uDMA read In1 */
		if (_SNN_In1) {
			AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) In1+_NN_In1), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+46436+3840*((T1Ind_Total)%2)),
					_SNN_In1, 0, &UchanHF1);
		}
		AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read In1 */
		if (_SN_In1) {
			AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+46436+3840*((T1Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+0+3840*((T1Ind_Total+1)%2)),
					_SN_In1, 0, &DmaR_Evt2);
		}
		/*============================= End Read Tiles ======================================*/
		for (T0Ind=0; T0Ind<20; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==19), T0Ind_NextLast = ((T0Ind+1)==19);
			/*================================= Prepare Tiles ===================================*/
			_SN_In2 = 0;
			if (!(T0Ind_Last)) {
				_N_In2 = _N_In2 + (20); _LN_In2 = (20); _SN_In2 = (96*_LN_In2); 
			} else if (!(T1Ind_Last)) {
				_N_In2 = _N_In2 + (-380); _LN_In2 = (20); _SN_In2 = (96*_LN_In2); 
			}
			/*============================= End Prepare Tiles ===================================*/
			/*================================= Read Tiles ======================================*/
			AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In2 */
			if (_SN_In2) {
				AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In2+_N_In2), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+43520+1920*((T0Ind_Total+1)%2)),
						_SN_In2, 400, _LN_In2, 0, &DmaR_Evt1);
			}
			/*============================= End Read Tiles ======================================*/
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->In1 = (signed char * __restrict__) (lynred_L1_Memory+0+3840*((T1Ind_Total)%2));
			KerArg0->H_In1 = (unsigned short int) (T1Ind_Last?16:40);
			KerArg0->In2 = (signed char * __restrict__) (lynred_L1_Memory+43520+1920*((T0Ind_Total)%2));
			KerArg0->Bias = (void * __restrict__) (lynred_L1_Memory+7680+(160*(T1Ind)));
			KerArg0->Scale = (unsigned char * __restrict__) (lynred_L1_Memory+41984+(40*(T1Ind)));
			KerArg0->ScaleN = (unsigned char * __restrict__) (lynred_L1_Memory+42560+(40*(T1Ind)));
			KerArg0->Out = (signed char * __restrict__) (lynred_L1_Memory+9984+16000*((T1Ind_Total)%2));
			KerArg0->OutFirstCol = (unsigned short int) ((T0Ind)*20);
			KerArg0->NormBias = (unsigned char) (((char *)(lynred_L1_Memory+47360))[5]);
			AT_FORK(gap_ncore(), (void *) KerParMatMulB32_2x4_ReLU_SQ8, (void *) KerArg0);
			__CALL(KerParMatMulB32_2x4_ReLU_SQ8, KerArg0);
			/*================================= Update Arg Pipeline =============================*/
			/*============================= End Update Arg Pipeline =============================*/
		} /* End iteration on Tile0 */
		/*================================= Write Tiles =====================================*/
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
		if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR5); /* Wait previous uDMA write Out */
		if (_SP_Out) AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+100196+16000*((T1Ind_Total+-1)%2)),
					_SP_Out, 1, &UchanHR5);
		AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+100196+16000*((T1Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+9984+16000*((T1Ind_Total)%2)),
				_SC_Out, 1, &DmaW_Evt1);
		/*============================= End Write Tiles =====================================*/
		/*================================= Update Arg Pipeline =============================*/
		_SN_In1 = _SNN_In1;
		_SPP_Out = _SP_Out;
		_P_Out = _C_Out;_SP_Out = _SC_Out;
		/*============================= End Update Arg Pipeline =============================*/
		/*================================= Prepare Tiles ===================================*/
		_SC_Out = 0;
		if (!(T1Ind_Last)) {
			_C_Out = _C_Out + (16000); _SC_Out = ((T1Ind_NextLast)?6400:16000); 
		}
		/*============================= End Prepare Tiles ===================================*/
	} /* End iteration on Tile1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR5); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+100196+16000*((T1Ind_Total+-1)%2)), _SP_Out, 1, &UchanHR5);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR5); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S93_Conv2d_32x576x1x1(
		signed char * __restrict__ In2,
		signed char * __restrict__ In1,
		int * __restrict__ Bias,
		signed char * __restrict__ Out,
		unsigned char * __restrict__ Scale,
		unsigned char * __restrict__ ScaleN,
		signed char * __restrict__ Infos)

{
	/* Shared L1: 35532 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaR_Evt4;
	AT_L2_EVENT DmaR_Evt5;
	AT_L2_EVENT DmaR_Evt6;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF2;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF3;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF4;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF5;
	KerMatMul_SQ8_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T1Ind, T1Ind_Total=0, T1Ind_Last, T1Ind_NextLast, T1Ind_NextNextLast;
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	unsigned int _NN_In2;
	unsigned int _SN_In2, _SNN_In2;
	unsigned int _LN_In2, _LNN_In2;
	unsigned int _C_Out;
	unsigned int _SP_Out, _SC_Out;
	unsigned int _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile1 Dim: 34][Tile0 Dim: 1]
	Ker Arg: In2, Tiled Space: Tile1
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 34 logical tiles, 34 physical tiles
			Total Size: 230400 [Tile1, 34:[576x12, 32:576x12, 576x4], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 34:[576x12, 32:576x12, 576x4], 1]
		Tile0: [0, 6912, 12], Tile1: [12, 6912, 12], Tile2; [24, 6912, 12]
	Ker Arg: In1, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 18432 [Tile0, 1:[576x32], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[576x32], 1]
		Tile0: [0, 18432, 18432], Tile1: [0, 18432, 18432], Tile2; [0, 18432, 18432]
	Ker Arg: KerBuff, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 34 logical tiles, 1 physical tiles
			Total Size: 2304 [Tile1, 34:[2304x1, 32:2304x1, 2304x1], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 34:[2304x1, 32:2304x1, 2304x1], 1]
		Tile0: [0, 2304, 2304], Tile1: [0, 2304, 2304], Tile2; [0, 2304, 2304]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 128 [Tile0, 1:[1x32], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x32], 4]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Out, Tiled Space: Tile1
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 34 logical tiles, 34 physical tiles
			Total Size: 12800 [Tile1, 34:[32x12, 32:32x12, 32x4], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 34:[32x12, 32:32x12, 32x4], 1]
		Tile0: [0, 384, 12], Tile1: [12, 384, 12], Tile2; [24, 384, 12]
	Ker Arg: Scale, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 32 [Tile0, 1:[1x32], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x32], 1]
		Tile0: [0, 32, 32], Tile1: [0, 32, 32], Tile2; [0, 32, 32]
	Ker Arg: ScaleN, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 32 [Tile0, 1:[1x32], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x32], 1]
		Tile0: [0, 32, 32], Tile1: [0, 32, 32], Tile2; [0, 32, 32]
	Ker Arg: Infos, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 34 logical tiles, 1 physical tiles
			Total Size: 9 [Tile1, 34:[1x1, 32:1x1, 1x1], 9]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 34:[1x1, 32:1x1, 1x1], 9]
		Tile0: [0, 9, 9], Tile1: [0, 9, 9], Tile2; [0, 9, 9]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In1 = (signed char * __restrict__) (lynred_L1_Memory+16908);
	KerArg0->W_In1 = (unsigned short int) (576);
	KerArg0->H_In1 = (unsigned short int) (32);
	KerArg0->Bias = (void * __restrict__) (lynred_L1_Memory+35340);
	KerArg0->Scale = (unsigned char * __restrict__) (lynred_L1_Memory+35468);
	KerArg0->ScaleN = (unsigned char * __restrict__) (lynred_L1_Memory+35500);
	KerArg0->BufferColIn2 = (signed char * __restrict__) (lynred_L1_Memory+0);
	KerArg0->ColFirst = (unsigned char) (1);
	KerArg0->Infos = (signed char *__restrict__) (lynred_L1_Memory+16896);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+0), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), 6912, 400, 12, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In2 */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+12), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+6912), 6912, 400, 12, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+2304+0), 6912, 0, &DmaR_Evt1);
	_NN_In2=12; _SN_In2=6912;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In1+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+16908), 18432, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read In1 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Bias+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+73060+0), 128, 0, &UchanHF2);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF2); /* Wait previous uDMA read Bias */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+73060+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+35340), 128, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Bias */
	_C_Out=0; _SC_Out=384; _LC_Out=12;
	_SP_Out=0;
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Scale+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+73188+0), 32, 0, &UchanHF3);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF3); /* Wait previous uDMA read Scale */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+73188+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+35468), 32, 0, &DmaR_Evt4);
	AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read Scale */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) ScaleN+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+73220+0), 32, 0, &UchanHF4);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF4); /* Wait previous uDMA read ScaleN */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+73220+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+35500), 32, 0, &DmaR_Evt5);
	AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read ScaleN */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Infos+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+73252+0), 9, 0, &UchanHF5);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF5); /* Wait previous uDMA read Infos */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+73252+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+16896), 9, 0, &DmaR_Evt6);
	AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Infos */
	/*============================= End Read Tiles Prolog ===============================*/
	for (T1Ind=0; T1Ind<34; T1Ind++, T1Ind_Total++) { /* Iteration on Tile1 */
		int T1Ind_Last = (T1Ind==33), T1Ind_NextLast = ((T1Ind+1)==33), T1Ind_NextNextLast = ((T1Ind+2)==33);
		/*================================= Prepare Tiles ===================================*/
		_SNN_In2 = 0;
		if (!(T1Ind_Last)) {
			if (!(T1Ind_NextLast)) {
				_NN_In2 = _NN_In2 + (12); _LNN_In2 = ((T1Ind_NextNextLast)?4:12); _SNN_In2 = (576*_LNN_In2); 
			}
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In2 */
		if (_SNN_In2) {
			AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+_NN_In2), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+6912*((T1Ind_Total)%2)),
					_SNN_In2, 400, _LNN_In2, 0, &UchanHR1);
		}
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In2 */
		if (_SN_In2) {
			AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+6912*((T1Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+2304+6912*((T1Ind_Total+1)%2)),
					_SN_In2, 0, &DmaR_Evt1);
		}
		/*============================= End Read Tiles ======================================*/
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1;
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->In2 = (signed char * __restrict__) (lynred_L1_Memory+2304+6912*((T1Ind_Total)%2));
			KerArg0->W_In2 = (unsigned short int) ((T1Ind_Last)?4:12);
			KerArg0->Out = (signed char * __restrict__) (lynred_L1_Memory+16128+384*((T1Ind_Total)%2));
			KerArg0->W_Out = (unsigned short int) ((T1Ind_Last)?4:12);
			KerArg0->OutFirstCol = (unsigned short int) ((0)*32);
			KerArg0->NormBias = (unsigned char) (((char *)(lynred_L1_Memory+16896))[5]);
			AT_FORK(gap_ncore(), (void *) KerParMatMulB32_2x4_SQ8, (void *) KerArg0);
			__CALL(KerParMatMulB32_2x4_SQ8, KerArg0);
		} /* End iteration on Tile0 */
		/*================================= Write Tiles =====================================*/
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
		AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+16128+384*((T1Ind_Total)%2)),
				_SC_Out, 400, _LC_Out, 1, &DmaW_Evt1);
		/*============================= End Write Tiles =====================================*/
		/*================================= Update Arg Pipeline =============================*/
		_SN_In2 = _SNN_In2;_LN_In2 = _LNN_In2;
		_SP_Out = _SC_Out;_LP_Out = _LC_Out;
		/*============================= End Update Arg Pipeline =============================*/
		/*================================= Prepare Tiles ===================================*/
		_SC_Out = 0;
		if (!(T1Ind_Last)) {
			_C_Out = _C_Out + (12); _LC_Out = ((T1Ind_NextLast)?4:12); _SC_Out = (32*_LC_Out); 
		}
		/*============================= End Prepare Tiles ===================================*/
	} /* End iteration on Tile1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S94_Op_CONV_2D_0_33_trans_out0(
		signed char * __restrict__ In,
		signed char * __restrict__ Out)

{
	/* Shared L1: 25600 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	KerMatTranspose_fps_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile0 Dim: 1]
	Ker Arg: In, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 12800 [Tile0, 1:[640x20], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[640x20], 1]
		Tile0: [0, 12800, 12800], Tile1: [0, 12800, 12800], Tile2; [0, 12800, 12800]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 12800 [Tile0, 1:[20x640], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[20x640], 1]
		Tile0: [0, 12800, 12800], Tile1: [0, 12800, 12800], Tile2; [0, 12800, 12800]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (signed char *__restrict__) (lynred_L1_Memory+0);
	KerArg0->Out = (signed char *__restrict__) (lynred_L1_Memory+12800);
	KerArg0->Feat = (unsigned short int) (32);
	KerArg0->W = (unsigned short int) (20);
	KerArg0->H = (unsigned short int) (20);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+0), 12800, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on Tile0 */
		int T0Ind_Last = 1;
		/*====================== Call Kernel LOC_LOOP =========================*/
		AT_FORK(gap_ncore(), (void *) CNN_MatPermCHW2HWC_fps, (void *) KerArg0);
		__CALL(CNN_MatPermCHW2HWC_fps, KerArg0);
	} /* End iteration on Tile0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+12800), 12800, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+0), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), 12800, 1, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S98_Conv2d_16x576x1x1_Sigmoid(
		signed char * __restrict__ In2,
		signed char * __restrict__ In1,
		int * __restrict__ Bias,
		signed char * __restrict__ Out,
		unsigned char * __restrict__ Scale,
		unsigned char * __restrict__ ScaleN,
		signed char * __restrict__ Infos)

{
	/* Shared L1: 40044 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaR_Evt4;
	AT_L2_EVENT DmaR_Evt5;
	AT_L2_EVENT DmaR_Evt6;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF2;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF3;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF4;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF5;
	KerMatMul_SQ8_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerActivation_SQ8_T S_KerArg1, *KerArg1 = &S_KerArg1;

	/* Iteration space related variables */
	int T1Ind, T1Ind_Total=0, T1Ind_Last, T1Ind_NextLast, T1Ind_NextNextLast;
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	unsigned int _NN_In2;
	unsigned int _SN_In2, _SNN_In2;
	unsigned int _LN_In2, _LNN_In2;
	unsigned int _C_Out;
	unsigned int _SP_Out, _SC_Out;
	unsigned int _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile1 Dim: 17][Tile0 Dim: 1]
	Ker Arg: In2, Tiled Space: Tile1
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 17 logical tiles, 17 physical tiles
			Total Size: 230400 [Tile1, 17:[576x24, 15:576x24, 576x16], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 17:[576x24, 15:576x24, 576x16], 1]
		Tile0: [0, 13824, 24], Tile1: [24, 13824, 24], Tile2; [48, 13824, 24]
	Ker Arg: In1, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 9216 [Tile0, 1:[576x16], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[576x16], 1]
		Tile0: [0, 9216, 9216], Tile1: [0, 9216, 9216], Tile2; [0, 9216, 9216]
	Ker Arg: KerBuff, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 17 logical tiles, 1 physical tiles
			Total Size: 2304 [Tile1, 17:[2304x1, 15:2304x1, 2304x1], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 17:[2304x1, 15:2304x1, 2304x1], 1]
		Tile0: [0, 2304, 2304], Tile1: [0, 2304, 2304], Tile2; [0, 2304, 2304]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 64 [Tile0, 1:[1x16], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x16], 4]
		Tile0: [0, 64, 64], Tile1: [0, 64, 64], Tile2; [0, 64, 64]
	Ker Arg: Out, Tiled Space: Tile1
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 17 logical tiles, 17 physical tiles
			Total Size: 6400 [Tile1, 17:[16x24, 15:16x24, 16x16], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 17:[16x24, 15:16x24, 16x16], 1]
		Tile0: [0, 384, 24], Tile1: [24, 384, 24], Tile2; [48, 384, 24]
	Ker Arg: Scale, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 16 [Tile0, 1:[1x16], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x16], 1]
		Tile0: [0, 16, 16], Tile1: [0, 16, 16], Tile2; [0, 16, 16]
	Ker Arg: ScaleN, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 16 [Tile0, 1:[1x16], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x16], 1]
		Tile0: [0, 16, 16], Tile1: [0, 16, 16], Tile2; [0, 16, 16]
	Ker Arg: Infos, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 17 logical tiles, 1 physical tiles
			Total Size: 9 [Tile1, 17:[1x1, 15:1x1, 1x1], 9]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 17:[1x1, 15:1x1, 1x1], 9]
		Tile0: [0, 9, 9], Tile1: [0, 9, 9], Tile2; [0, 9, 9]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In1 = (signed char * __restrict__) (lynred_L1_Memory+30732);
	KerArg0->W_In1 = (unsigned short int) (576);
	KerArg0->H_In1 = (unsigned short int) (16);
	KerArg0->Bias = (void * __restrict__) (lynred_L1_Memory+39948);
	KerArg0->Scale = (unsigned char * __restrict__) (lynred_L1_Memory+40012);
	KerArg0->ScaleN = (unsigned char * __restrict__) (lynred_L1_Memory+40028);
	KerArg0->BufferColIn2 = (signed char * __restrict__) (lynred_L1_Memory+0);
	KerArg0->ColFirst = (unsigned char) (1);
	KerArg0->Infos = (signed char *__restrict__) (lynred_L1_Memory+30720);
	KerArg1->Feat = (unsigned short int) (1);
	KerArg1->H = (unsigned short int) (16);
	KerArg1->Infos = (signed char *__restrict__) (lynred_L1_Memory+30720);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+0), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), 13824, 400, 24, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In2 */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+24), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+13824), 13824, 400, 24, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+2304+0), 13824, 0, &DmaR_Evt1);
	_NN_In2=24; _SN_In2=13824;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In1+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+30732), 9216, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read In1 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Bias+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+80484+0), 64, 0, &UchanHF2);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF2); /* Wait previous uDMA read Bias */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+80484+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+39948), 64, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Bias */
	_C_Out=0; _SC_Out=384; _LC_Out=24;
	_SP_Out=0;
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Scale+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+80548+0), 16, 0, &UchanHF3);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF3); /* Wait previous uDMA read Scale */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+80548+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+40012), 16, 0, &DmaR_Evt4);
	AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read Scale */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) ScaleN+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+80564+0), 16, 0, &UchanHF4);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF4); /* Wait previous uDMA read ScaleN */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+80564+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+40028), 16, 0, &DmaR_Evt5);
	AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read ScaleN */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Infos+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+80580+0), 9, 0, &UchanHF5);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF5); /* Wait previous uDMA read Infos */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+80580+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+30720), 9, 0, &DmaR_Evt6);
	AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Infos */
	/*============================= End Read Tiles Prolog ===============================*/
	for (T1Ind=0; T1Ind<17; T1Ind++, T1Ind_Total++) { /* Iteration on Tile1 */
		int T1Ind_Last = (T1Ind==16), T1Ind_NextLast = ((T1Ind+1)==16), T1Ind_NextNextLast = ((T1Ind+2)==16);
		/*================================= Prepare Tiles ===================================*/
		_SNN_In2 = 0;
		if (!(T1Ind_Last)) {
			if (!(T1Ind_NextLast)) {
				_NN_In2 = _NN_In2 + (24); _LNN_In2 = ((T1Ind_NextNextLast)?16:24); _SNN_In2 = (576*_LNN_In2); 
			}
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In2 */
		if (_SNN_In2) {
			AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+_NN_In2), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+13824*((T1Ind_Total)%2)),
					_SNN_In2, 400, _LNN_In2, 0, &UchanHR1);
		}
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In2 */
		if (_SN_In2) {
			AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+13824*((T1Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+2304+13824*((T1Ind_Total+1)%2)),
					_SN_In2, 0, &DmaR_Evt1);
		}
		/*============================= End Read Tiles ======================================*/
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1;
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->In2 = (signed char * __restrict__) (lynred_L1_Memory+2304+13824*((T1Ind_Total)%2));
			KerArg0->W_In2 = (unsigned short int) ((T1Ind_Last)?16:24);
			KerArg0->Out = (signed char * __restrict__) (lynred_L1_Memory+29952+384*((T1Ind_Total)%2));
			KerArg0->W_Out = (unsigned short int) ((T1Ind_Last)?16:24);
			KerArg0->OutFirstCol = (unsigned short int) ((0)*16);
			KerArg0->NormBias = (unsigned char) (((char *)(lynred_L1_Memory+30720))[5]);
			AT_FORK(gap_ncore(), (void *) KerParMatMulB32_2x4_SQ8, (void *) KerArg0);
			__CALL(KerParMatMulB32_2x4_SQ8, KerArg0);
		} /* End iteration on Tile0 */
		/*====================== Call Kernel LOC_LOOP_EPILOG =========================*/
		KerArg1->In = (signed char *__restrict__) (lynred_L1_Memory+29952+384*((T1Ind_Total)%2));
		KerArg1->Out = (signed char *__restrict__) (lynred_L1_Memory+29952+384*((T1Ind_Total)%2));
		KerArg1->W = (unsigned short int) ((T1Ind_Last)?16:24);
		AT_FORK(gap_ncore(), (void *) Ker_Sigmoid_SQ8, (void *) KerArg1);
		__CALL(Ker_Sigmoid_SQ8, KerArg1);
		/*================================= Write Tiles =====================================*/
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
		AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+29952+384*((T1Ind_Total)%2)),
				_SC_Out, 400, _LC_Out, 1, &DmaW_Evt1);
		/*============================= End Write Tiles =====================================*/
		/*================================= Update Arg Pipeline =============================*/
		_SN_In2 = _SNN_In2;_LN_In2 = _LNN_In2;
		_SP_Out = _SC_Out;_LP_Out = _LC_Out;
		/*============================= End Update Arg Pipeline =============================*/
		/*================================= Prepare Tiles ===================================*/
		_SC_Out = 0;
		if (!(T1Ind_Last)) {
			_C_Out = _C_Out + (24); _LC_Out = ((T1Ind_NextLast)?16:24); _SC_Out = (16*_LC_Out); 
		}
		/*============================= End Prepare Tiles ===================================*/
	} /* End iteration on Tile1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S99_Op_CONV_2D_0_35_trans_out0(
		signed char * __restrict__ In,
		signed char * __restrict__ Out)

{
	/* Shared L1: 12800 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	KerMatTranspose_fps_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile0 Dim: 1]
	Ker Arg: In, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 6400 [Tile0, 1:[320x20], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[320x20], 1]
		Tile0: [0, 6400, 6400], Tile1: [0, 6400, 6400], Tile2; [0, 6400, 6400]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 6400 [Tile0, 1:[20x320], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[20x320], 1]
		Tile0: [0, 6400, 6400], Tile1: [0, 6400, 6400], Tile2; [0, 6400, 6400]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (signed char *__restrict__) (lynred_L1_Memory+0);
	KerArg0->Out = (signed char *__restrict__) (lynred_L1_Memory+6400);
	KerArg0->Feat = (unsigned short int) (16);
	KerArg0->W = (unsigned short int) (20);
	KerArg0->H = (unsigned short int) (20);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+0), 6400, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on Tile0 */
		int T0Ind_Last = 1;
		/*====================== Call Kernel LOC_LOOP =========================*/
		AT_FORK(gap_ncore(), (void *) CNN_MatPermCHW2HWC_fps, (void *) KerArg0);
		__CALL(CNN_MatPermCHW2HWC_fps, KerArg0);
	} /* End iteration on Tile0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+6400), 6400, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+0), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), 6400, 1, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S103_Conv2d_128x576x1x1_Relu(
		signed char * __restrict__ In2,
		signed char * __restrict__ In1,
		int * __restrict__ Bias,
		signed char * __restrict__ Out,
		unsigned char * __restrict__ Scale,
		unsigned char * __restrict__ ScaleN,
		signed char * __restrict__ Infos)

{
	/* Shared L1: 38412 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaR_Evt4;
	AT_L2_EVENT DmaR_Evt5;
	AT_L2_EVENT DmaR_Evt6;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF1;
	AT_HYPERRAM_CL_EVENT UchanHR2;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF3;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF4;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF5;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF6;
	KerMatMul_SQ8_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T1Ind, T1Ind_Total=0, T1Ind_Last, T1Ind_NextLast, T1Ind_NextNextLast;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast, T0Ind_NextNextLast;
	/* User kernel arguments related variables */
	unsigned int _NN_In1;
	unsigned int _SN_In1, _SNN_In1;
	unsigned int _NN_In2;
	unsigned int _SN_In2, _SNN_In2;
	unsigned int _LN_In2, _LNN_In2;
	unsigned int _C_Out;
	unsigned int _SP_Out, _SC_Out;
	unsigned int _LP_Out, _LC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile1 Dim: 34][Tile0 Dim: 8]
	Ker Arg: KerBuff, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 34 logical tiles, 1 physical tiles
			Total Size: 2304 [Tile1, 34:[2304x1, 32:2304x1, 2304x1], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 34:[2304x1, 32:2304x1, 2304x1], 1]
		Tile0: [0, 2304, 2304], Tile1: [0, 2304, 2304], Tile2; [0, 2304, 2304]
	Ker Arg: In1, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 8 logical tiles, 8 physical tiles
			Total Size: 73728 [Tile0, 8:[576x16, 6:576x16, 576x16], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 8:[576x16, 6:576x16, 576x16], 1]
		Tile0: [0, 9216, 9216], Tile1: [9216, 9216, 9216], Tile2; [18432, 9216, 9216]
	Ker Arg: In2, Tiled Space: Tile1
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 34 logical tiles, 34 physical tiles
			Total Size: 230400 [Tile1, 34:[576x12, 32:576x12, 576x4], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 34:[576x12, 32:576x12, 576x4], 1]
		Tile0: [0, 6912, 12], Tile1: [12, 6912, 12], Tile2; [24, 6912, 12]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 8 logical tiles, 1 physical tiles
			Total Size: 512 [Tile0, 8:[1x16, 6:1x16, 1x16], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 8:[1x16, 6:1x16, 1x16], 4]
		Tile0: [0, 512, 512], Tile1: [0, 512, 512], Tile2; [0, 512, 512]
	Ker Arg: Out, Tiled Space: Tile1
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 34 logical tiles, 34 physical tiles
			Total Size: 51200 [Tile1, 34:[128x12, 32:128x12, 128x4], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 34:[128x12, 32:128x12, 128x4], 1]
		Tile0: [0, 1536, 12], Tile1: [12, 1536, 12], Tile2; [24, 1536, 12]
	Ker Arg: Scale, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 8 logical tiles, 1 physical tiles
			Total Size: 128 [Tile0, 8:[1x16, 6:1x16, 1x16], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 8:[1x16, 6:1x16, 1x16], 1]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: ScaleN, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 8 logical tiles, 1 physical tiles
			Total Size: 128 [Tile0, 8:[1x16, 6:1x16, 1x16], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 8:[1x16, 6:1x16, 1x16], 1]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Infos, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 34 logical tiles, 1 physical tiles
			Total Size: 9 [Tile1, 34:[1x1, 32:1x1, 1x1], 9]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 34:[1x1, 32:1x1, 1x1], 9]
		Tile0: [0, 9, 9], Tile1: [0, 9, 9], Tile2; [0, 9, 9]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->W_In1 = (unsigned short int) (576);
	KerArg0->H_In1 = (unsigned short int) (16);
	KerArg0->BufferColIn2 = (signed char * __restrict__) (lynred_L1_Memory+0);
	KerArg0->ColFirst = (unsigned char) (1);
	KerArg0->Infos = (signed char *__restrict__) (lynred_L1_Memory+19200);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) In1+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+111460+0), 9216, 0, &UchanHF1);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1); /* Wait previous uDMA read In1 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) In1+9216), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+111460+9216), 9216, 0, &UchanHF1);
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+111460+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+19212+0), 9216, 0, &DmaR_Evt1);
	_NN_In1=9216; _SN_In1=9216;
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+0), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+97636+0), 6912, 400, 12, 0, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read In2 */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+12), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+97636+6912), 6912, 400, 12, 0, &UchanHR2);
	AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+97636+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+2304+0), 6912, 0, &DmaR_Evt2);
	_NN_In2=12; _SN_In2=6912;
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Bias+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+129892+0), 512, 0, &UchanHF3);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF3); /* Wait previous uDMA read Bias */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+129892+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+37644), 512, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Bias */
	_C_Out=0; _SC_Out=1536; _LC_Out=12;
	_SP_Out=0;
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Scale+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+130404+0), 128, 0, &UchanHF4);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF4); /* Wait previous uDMA read Scale */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+130404+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+38156), 128, 0, &DmaR_Evt4);
	AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read Scale */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) ScaleN+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+130532+0), 128, 0, &UchanHF5);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF5); /* Wait previous uDMA read ScaleN */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+130532+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+38284), 128, 0, &DmaR_Evt5);
	AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read ScaleN */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Infos+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+130660+0), 9, 0, &UchanHF6);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF6); /* Wait previous uDMA read Infos */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+130660+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+19200), 9, 0, &DmaR_Evt6);
	AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Infos */
	/*============================= End Read Tiles Prolog ===============================*/
	for (T1Ind=0; T1Ind<34; T1Ind++, T1Ind_Total++) { /* Iteration on Tile1 */
		int T1Ind_Last = (T1Ind==33), T1Ind_NextLast = ((T1Ind+1)==33), T1Ind_NextNextLast = ((T1Ind+2)==33);
		/*================================= Prepare Tiles ===================================*/
		_SNN_In2 = 0;
		if (!(T1Ind_Last)) {
			if (!(T1Ind_NextLast)) {
				_NN_In2 = _NN_In2 + (12); _LNN_In2 = ((T1Ind_NextNextLast)?4:12); _SNN_In2 = (576*_LNN_In2); 
			}
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read In2 */
		if (_SNN_In2) {
			AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In2+_NN_In2), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+97636+6912*((T1Ind_Total)%2)),
					_SNN_In2, 400, _LNN_In2, 0, &UchanHR2);
		}
		AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read In2 */
		if (_SN_In2) {
			AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+97636+6912*((T1Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+2304+6912*((T1Ind_Total+1)%2)),
					_SN_In2, 0, &DmaR_Evt2);
		}
		/*============================= End Read Tiles ======================================*/
		for (T0Ind=0; T0Ind<8; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==7), T0Ind_NextLast = ((T0Ind+1)==7), T0Ind_NextNextLast = ((T0Ind+2)==7);
			/*================================= Prepare Tiles ===================================*/
			_SNN_In1 = 0;
			if (!(T0Ind_Last)) {
				if (!(T0Ind_NextLast)) {
					_NN_In1 = _NN_In1 + (9216); _SNN_In1 = (9216); 
				} else if (!(T1Ind_Last)) {
					_NN_In1 = _NN_In1 + (-64512); _SNN_In1 = (9216); 
				}
			} else if (!((T1Ind_Last))) {
				_NN_In1 = _NN_In1 + (9216); _SNN_In1 = (9216); 
			}
			/*============================= End Prepare Tiles ===================================*/
			/*================================= Read Tiles ======================================*/
			AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1); /* Wait previous uDMA read In1 */
			if (_SNN_In1) {
				AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) In1+_NN_In1), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+111460+9216*((T0Ind_Total)%2)),
						_SNN_In1, 0, &UchanHF1);
			}
			AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In1 */
			if (_SN_In1) {
				AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+111460+9216*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+19212+9216*((T0Ind_Total+1)%2)),
						_SN_In1, 0, &DmaR_Evt1);
			}
			/*============================= End Read Tiles ======================================*/
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->In1 = (signed char * __restrict__) (lynred_L1_Memory+19212+9216*((T0Ind_Total)%2));
			KerArg0->In2 = (signed char * __restrict__) (lynred_L1_Memory+2304+6912*((T1Ind_Total)%2));
			KerArg0->W_In2 = (unsigned short int) ((T1Ind_Last)?4:12);
			KerArg0->Bias = (void * __restrict__) (lynred_L1_Memory+37644+(64*(T0Ind)));
			KerArg0->Scale = (unsigned char * __restrict__) (lynred_L1_Memory+38156+(16*(T0Ind)));
			KerArg0->ScaleN = (unsigned char * __restrict__) (lynred_L1_Memory+38284+(16*(T0Ind)));
			KerArg0->Out = (signed char * __restrict__) (lynred_L1_Memory+16128+1536*((T1Ind_Total)%2));
			KerArg0->W_Out = (unsigned short int) ((T1Ind_Last)?4:12);
			KerArg0->OutFirstCol = (unsigned short int) ((T0Ind)*16);
			KerArg0->NormBias = (unsigned char) (((char *)(lynred_L1_Memory+19200))[5]);
			AT_FORK(gap_ncore(), (void *) KerParMatMulB32_2x4_ReLU_SQ8, (void *) KerArg0);
			__CALL(KerParMatMulB32_2x4_ReLU_SQ8, KerArg0);
			/*================================= Update Arg Pipeline =============================*/
			_SN_In1 = _SNN_In1;
			/*============================= End Update Arg Pipeline =============================*/
		} /* End iteration on Tile0 */
		/*================================= Write Tiles =====================================*/
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
		AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+16128+1536*((T1Ind_Total)%2)),
				_SC_Out, 400, _LC_Out, 1, &DmaW_Evt1);
		/*============================= End Write Tiles =====================================*/
		/*================================= Update Arg Pipeline =============================*/
		_SN_In2 = _SNN_In2;_LN_In2 = _LNN_In2;
		_SP_Out = _SC_Out;_LP_Out = _LC_Out;
		/*============================= End Update Arg Pipeline =============================*/
		/*================================= Prepare Tiles ===================================*/
		_SC_Out = 0;
		if (!(T1Ind_Last)) {
			_C_Out = _C_Out + (12); _LC_Out = ((T1Ind_NextLast)?4:12); _SC_Out = (128*_LC_Out); 
		}
		/*============================= End Prepare Tiles ===================================*/
	} /* End iteration on Tile1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S106_Conv2d_256x128x3x3_Relu(
		signed char * __restrict__ In,
		signed char * __restrict__ Filter,
		int * __restrict__ Bias,
		signed char * __restrict__ Out,
		unsigned char * __restrict__ Scale,
		unsigned char * __restrict__ ScaleN,
		signed char * __restrict__ Infos)

{
	/* Shared L1: 47756 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaR_Evt4;
	AT_L2_EVENT DmaR_Evt5;
	AT_L2_EVENT DmaR_Evt6;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF1;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF2;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF3;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF4;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF5;
	KerSetBias_SQ8_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerConv_SQ8_T S_KerArg1, *KerArg1 = &S_KerArg1;
	KerConvLinReduct_SQ8_T S_KerArg2, *KerArg2 = &S_KerArg2;

	/* Iteration space related variables */
	int D1Ind, D1Ind_Total=0, D1Ind_Last, D1Ind_NextLast, D1Ind_NextNextLast;
	int T0Ind, T0Ind_Last, T0Ind_NextLast;
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast, D0Ind_NextNextLast;
	/* User kernel arguments related variables */
	unsigned int _C_Out;
	unsigned int _SP_Out, _SC_Out;
	unsigned int _LP_Out, _LC_Out;
	unsigned int _NN_Filter;
	unsigned int _SN_Filter, _SNN_Filter;
	unsigned int _N_In;
	unsigned int _SN_In;
	unsigned int _LN_In;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 256, Tiled: 4][Tile0 Dim: 1][D0 Dim: Init: 128, Tiled: 32]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 4 logical tiles, 4 physical tiles
			Total Size: 25600 [D1, [3 x 6400, 6400]][Tile0, 1:[10x10], 1]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [3 x 6400, 6400]][Tile0, 1:[10x10], 1]
		Tile0: [0, 6400, 100], Tile1: [6400, 6400, 100], Tile2; [12800, 6400, 100]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 4 logical tiles, 1 physical tiles
			Total Size: 1024 [D1, [3 x 256, 256]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [3 x 256, 256]]
		Tile0: [0, 1024, 1024], Tile1: [0, 1024, 1024], Tile2; [0, 1024, 1024]
	Ker Arg: Scale, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 4 logical tiles, 1 physical tiles
			Total Size: 256 [D1, [3 x 64, 64]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [3 x 64, 64]]
		Tile0: [0, 256, 256], Tile1: [0, 256, 256], Tile2; [0, 256, 256]
	Ker Arg: ScaleN, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 4 logical tiles, 1 physical tiles
			Total Size: 256 [D1, [3 x 64, 64]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [3 x 64, 64]]
		Tile0: [0, 256, 256], Tile1: [0, 256, 256], Tile2; [0, 256, 256]
	Ker Arg: Filter, Tiled Space: D0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 128 logical tiles, 128 physical tiles
			Total Size: 294912 [D1, [3 x 73728, 73728]][D0, [31 x 2304, 2304]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [3 x 73728, 73728]][D0, [31 x 2304, 2304]]
		Tile0: [0, 2304, 2304], Tile1: [2304, 2304, 2304], Tile2; [4608, 2304, 2304]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 32 logical tiles, 32 physical tiles
			Total Size: 51200 [D0, [31 x 1600, 1600]][Tile0, 1:[20x20], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[20x21, 30:20x21, 20x20], 1][D0, [31 x 1600, 1600]]
		Tile0: [0, 1600, 400], Tile1: [1600, 1600, 400], Tile2; [3200, 1600, 400]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 4 logical tiles, 1 physical tiles
			Total Size: 102400 [D1, [3 x 25600, 25600]][Tile0, 1:[10x10], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [3 x 25600, 25600]][Tile0, 1:[10x10], 4]
		Tile0: [0, 25600, 400], Tile1: [0, 25600, 400], Tile2; [0, 25600, 400]
	Ker Arg: Infos, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 9 [Tile0, 1:[9x1], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[9x1], 1]
		Tile0: [0, 9, 9], Tile1: [0, 9, 9], Tile2; [0, 9, 9]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (lynred_L1_Memory+22144);
	KerArg0->W = (unsigned short int) (10);
	KerArg0->H = (unsigned short int) (10);
	KerArg0->Feat = (unsigned short int) (64);
	KerArg1->W = (unsigned short int) (20);
	KerArg1->UsedW = (unsigned short int) (20);
	KerArg1->InFeatures = (unsigned short int) (4);
	KerArg1->OutFeatures = (unsigned short int) (64);
	KerArg1->TotalInFeatures = (unsigned short int) (4);
	KerArg1->Out = (int * __restrict__) (lynred_L1_Memory+22144);
	KerArg1->Pad = (v4s) ((v4s){0,1,0,1});
	KerArg2->In = (int *__restrict__) (lynred_L1_Memory+22144);
	KerArg2->Feat = (unsigned short int) (64);
	KerArg2->W = (unsigned short int) (10);
	KerArg2->H = (unsigned short int) (10);
	KerArg2->Infos = (signed char *__restrict__) (lynred_L1_Memory+47744);
	/*================================= Read Tiles Prolog ===============================*/
	_C_Out=0; _SC_Out=6400; _LC_Out=100;
	_SP_Out=0;
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Bias+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+131940+0), 1024, 0, &UchanHF1);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1); /* Wait previous uDMA read Bias */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+131940+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+3200), 1024, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Bias */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Scale+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+132964+0), 256, 0, &UchanHF2);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF2); /* Wait previous uDMA read Scale */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+132964+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+4224), 256, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Scale */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) ScaleN+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+133220+0), 256, 0, &UchanHF3);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF3); /* Wait previous uDMA read ScaleN */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+133220+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+4480), 256, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read ScaleN */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Filter+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+123236+0), 2304, 0, &UchanHF4);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF4); /* Wait previous uDMA read Filter */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Filter+2304), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+123236+2304), 2304, 0, &UchanHF4);
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+123236+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+4736+0), 2304, 0, &DmaR_Evt4);
	_NN_Filter=2304; _SN_Filter=2304;
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+0+0), 1600, 400, 400, 0, &DmaR_Evt5);
	_N_In=0;
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Infos+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+133476+0), 9, 0, &UchanHF5);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF5); /* Wait previous uDMA read Infos */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+133476+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+47744), 9, 0, &DmaR_Evt6);
	AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Infos */
	/*============================= End Read Tiles Prolog ===============================*/
	for (D1Ind=0; D1Ind<4; D1Ind++, D1Ind_Total++) { /* Iteration on D1 */
		int D1Ind_Last = (D1Ind==3), D1Ind_NextLast = ((D1Ind+1)==3), D1Ind_NextNextLast = ((D1Ind+2)==3);
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1, T0Ind_NextLast = 1;
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->Bias = (void * __restrict__) (lynred_L1_Memory+3200+((D1Ind)*256));
			KerArg0->NormBias = (unsigned char) (((char *)(lynred_L1_Memory+47744))[5]);
			AT_FORK(gap_ncore(), (void *) KerParSetBiasB32_SQ8, (void *) KerArg0);
			__CALL(KerParSetBiasB32_SQ8, KerArg0);
			for (D0Ind=0; D0Ind<32; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==31), D0Ind_NextLast = ((D0Ind+1)==31), D0Ind_NextNextLast = ((D0Ind+2)==31);
				/*================================= Prepare Tiles ===================================*/
				_SNN_Filter = 0;
				if (!(D0Ind_Last)) {
					if (!(D0Ind_NextLast)) {
						_NN_Filter = _NN_Filter + ((2304)); _SNN_Filter = (((D1Ind_Last)?(2304):(2304))); 
					} else if (!((1))) {
						_NN_Filter = _NN_Filter + ((-71424)); _SNN_Filter = (((D1Ind_Last)?(2304):(2304))); 
					} else if (!(D1Ind_Last)) {
						_NN_Filter = _NN_Filter + (73728)+((-71424)); _SNN_Filter = (((D1Ind_NextLast)?(2304):(2304))); 
					}
				} else if (!((1))) {
					_NN_Filter = _NN_Filter + ((2304)); _SNN_Filter = (((D1Ind_Last)?(2304):(2304))); 
				} else if (!(D1Ind_Last)) {
					_NN_Filter = _NN_Filter + ((2304)); _SNN_Filter = (((D1Ind_NextLast)?(2304):(2304))); 
				}
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (1600); _LN_In = (400); _SN_In = (4*_LN_In); 
				} else if (!(D1Ind_Last)) {
					_N_In = _N_In + (-49600); _LN_In = (400); _SN_In = (4*_LN_In); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF4); /* Wait previous uDMA read Filter */
				if (_SNN_Filter) {
					AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Filter+_NN_Filter), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+123236+2304*((D0Ind_Total)%2)),
							_SNN_Filter, 0, &UchanHF4);
				}
				AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read Filter */
				if (_SN_Filter) {
					AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+123236+2304*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+4736+2304*((D0Ind_Total+1)%2)),
							_SN_Filter, 0, &DmaR_Evt4);
				}
				AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+0+1600*((D0Ind_Total+1)%2)),
							_SN_In, 400, _LN_In, 0, &DmaR_Evt5);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (signed char * __restrict__) (lynred_L1_Memory+0+1600*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (21-0*(1)-1*(1));
				KerArg1->UsedH = (unsigned short int) (21-0*(1)-1*(1));
				KerArg1->Filter = (signed char * __restrict__) (lynred_L1_Memory+4736+2304*((D0Ind_Total)%2));
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride2_SQ8, (void *) KerArg1);
				__CALL(KerParConv3x3Stride2_SQ8, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				_SN_Filter = _SNN_Filter;
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->Out = (void *__restrict__) (lynred_L1_Memory+9344+6400*((D1Ind_Total)%2));
			KerArg2->Scale = (unsigned char *__restrict__) (lynred_L1_Memory+4224+((D1Ind)*64));
			KerArg2->ScaleN = (unsigned char *__restrict__) (lynred_L1_Memory+4480+((D1Ind)*64));
			AT_FORK(gap_ncore(), (void *) KerParReduct_CC_ReLU_SQ8, (void *) KerArg2);
			__CALL(KerParReduct_CC_ReLU_SQ8, KerArg2);
		} /* End iteration on Tile0 */
		/*================================= Write Tiles =====================================*/
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
		AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+9344+6400*((D1Ind_Total)%2)),
				_SC_Out, 100, _LC_Out, 1, &DmaW_Evt1);
		/*============================= End Write Tiles =====================================*/
		/*================================= Update Arg Pipeline =============================*/
		_SP_Out = _SC_Out;_LP_Out = _LC_Out;
		/*============================= End Update Arg Pipeline =============================*/
		/*================================= Prepare Tiles ===================================*/
		_SC_Out = 0;
		if (!(D1Ind_Last)) {
			_C_Out = _C_Out + (6400); _LC_Out = (100); _SC_Out = (64*_LC_Out); 
		}
		/*============================= End Prepare Tiles ===================================*/
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S109_Conv2d_32x256x1x1(
		signed char * __restrict__ In2,
		signed char * __restrict__ In1,
		int * __restrict__ Bias,
		signed char * __restrict__ Out,
		unsigned char * __restrict__ Scale,
		unsigned char * __restrict__ ScaleN,
		signed char * __restrict__ Infos)

{
	/* Shared L1: 38220 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaR_Evt4;
	AT_L2_EVENT DmaR_Evt5;
	AT_L2_EVENT DmaR_Evt6;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF1;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF2;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF3;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF4;
	KerMatMul_SQ8_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T1Ind, T1Ind_Last;
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile1 Dim: 1][Tile0 Dim: 1]
	Ker Arg: KerBuff, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 1024 [Tile1, 1:[1024x1], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[1024x1], 1]
		Tile0: [0, 1024, 1024], Tile1: [0, 1024, 1024], Tile2; [0, 1024, 1024]
	Ker Arg: In1, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 8192 [Tile0, 1:[256x32], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[256x32], 1]
		Tile0: [0, 8192, 8192], Tile1: [0, 8192, 8192], Tile2; [0, 8192, 8192]
	Ker Arg: In2, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 25600 [Tile1, 1:[256x100], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[256x100], 1]
		Tile0: [0, 25600, 25600], Tile1: [0, 25600, 25600], Tile2; [0, 25600, 25600]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 128 [Tile0, 1:[1x32], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x32], 4]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 3200 [Tile1, 1:[32x100], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[32x100], 1]
		Tile0: [0, 3200, 3200], Tile1: [0, 3200, 3200], Tile2; [0, 3200, 3200]
	Ker Arg: Scale, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 32 [Tile0, 1:[1x32], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x32], 1]
		Tile0: [0, 32, 32], Tile1: [0, 32, 32], Tile2; [0, 32, 32]
	Ker Arg: ScaleN, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 32 [Tile0, 1:[1x32], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x32], 1]
		Tile0: [0, 32, 32], Tile1: [0, 32, 32], Tile2; [0, 32, 32]
	Ker Arg: Infos, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 9 [Tile1, 1:[1x1], 9]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[1x1], 9]
		Tile0: [0, 9, 9], Tile1: [0, 9, 9], Tile2; [0, 9, 9]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In1 = (signed char * __restrict__) (lynred_L1_Memory+29836);
	KerArg0->W_In1 = (unsigned short int) (256);
	KerArg0->H_In1 = (unsigned short int) (32);
	KerArg0->In2 = (signed char * __restrict__) (lynred_L1_Memory+1024);
	KerArg0->W_In2 = (unsigned short int) (100);
	KerArg0->Bias = (void * __restrict__) (lynred_L1_Memory+38028);
	KerArg0->Scale = (unsigned char * __restrict__) (lynred_L1_Memory+38156);
	KerArg0->ScaleN = (unsigned char * __restrict__) (lynred_L1_Memory+38188);
	KerArg0->Out = (signed char * __restrict__) (lynred_L1_Memory+26624);
	KerArg0->W_Out = (unsigned short int) (100);
	KerArg0->BufferColIn2 = (signed char * __restrict__) (lynred_L1_Memory+0);
	KerArg0->ColFirst = (unsigned char) (1);
	KerArg0->Infos = (signed char *__restrict__) (lynred_L1_Memory+29824);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In1+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+29836), 8192, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In1 */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In2+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+1024), 25600, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read In2 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Bias+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), 128, 0, &UchanHF1);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1); /* Wait previous uDMA read Bias */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+38028), 128, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Bias */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Scale+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+46564+0), 32, 0, &UchanHF2);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF2); /* Wait previous uDMA read Scale */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+46564+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+38156), 32, 0, &DmaR_Evt4);
	AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read Scale */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) ScaleN+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+46596+0), 32, 0, &UchanHF3);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF3); /* Wait previous uDMA read ScaleN */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+46596+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+38188), 32, 0, &DmaR_Evt5);
	AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read ScaleN */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Infos+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+46628+0), 9, 0, &UchanHF4);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF4); /* Wait previous uDMA read Infos */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+46628+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+29824), 9, 0, &DmaR_Evt6);
	AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Infos */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on Tile1 */
		int T1Ind_Last = 1;
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1;
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->OutFirstCol = (unsigned short int) ((0)*32);
			KerArg0->NormBias = (unsigned char) (((char *)(lynred_L1_Memory+29824))[5]);
			AT_FORK(gap_ncore(), (void *) KerParMatMulB32_2x4_SQ8, (void *) KerArg0);
			__CALL(KerParMatMulB32_2x4_SQ8, KerArg0);
		} /* End iteration on Tile0 */
	} /* End iteration on Tile1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+26624), 3200, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S110_Op_CONV_2D_0_39_trans_out0(
		signed char * __restrict__ In,
		signed char * __restrict__ Out)

{
	/* Shared L1: 6400 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	KerMatTranspose_fps_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile0 Dim: 1]
	Ker Arg: In, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 3200 [Tile0, 1:[320x10], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[320x10], 1]
		Tile0: [0, 3200, 3200], Tile1: [0, 3200, 3200], Tile2; [0, 3200, 3200]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 3200 [Tile0, 1:[10x320], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[10x320], 1]
		Tile0: [0, 3200, 3200], Tile1: [0, 3200, 3200], Tile2; [0, 3200, 3200]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (signed char *__restrict__) (lynred_L1_Memory+0);
	KerArg0->Out = (signed char *__restrict__) (lynred_L1_Memory+3200);
	KerArg0->Feat = (unsigned short int) (32);
	KerArg0->W = (unsigned short int) (10);
	KerArg0->H = (unsigned short int) (10);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+0), 3200, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on Tile0 */
		int T0Ind_Last = 1;
		/*====================== Call Kernel LOC_LOOP =========================*/
		AT_FORK(gap_ncore(), (void *) CNN_MatPermCHW2HWC_fps, (void *) KerArg0);
		__CALL(CNN_MatPermCHW2HWC_fps, KerArg0);
	} /* End iteration on Tile0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+3200), 3200, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+0), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), 3200, 1, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S114_Conv2d_16x256x1x1_Sigmoid(
		signed char * __restrict__ In2,
		signed char * __restrict__ In1,
		int * __restrict__ Bias,
		signed char * __restrict__ Out,
		unsigned char * __restrict__ Scale,
		unsigned char * __restrict__ ScaleN,
		signed char * __restrict__ Infos)

{
	/* Shared L1: 32428 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaR_Evt4;
	AT_L2_EVENT DmaR_Evt5;
	AT_L2_EVENT DmaR_Evt6;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF1;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF2;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF3;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF4;
	KerMatMul_SQ8_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerActivation_SQ8_T S_KerArg1, *KerArg1 = &S_KerArg1;

	/* Iteration space related variables */
	int T1Ind, T1Ind_Last;
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile1 Dim: 1][Tile0 Dim: 1]
	Ker Arg: KerBuff, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 1024 [Tile1, 1:[1024x1], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[1024x1], 1]
		Tile0: [0, 1024, 1024], Tile1: [0, 1024, 1024], Tile2; [0, 1024, 1024]
	Ker Arg: In1, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 4096 [Tile0, 1:[256x16], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[256x16], 1]
		Tile0: [0, 4096, 4096], Tile1: [0, 4096, 4096], Tile2; [0, 4096, 4096]
	Ker Arg: In2, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 25600 [Tile1, 1:[256x100], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[256x100], 1]
		Tile0: [0, 25600, 25600], Tile1: [0, 25600, 25600], Tile2; [0, 25600, 25600]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 64 [Tile0, 1:[1x16], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x16], 4]
		Tile0: [0, 64, 64], Tile1: [0, 64, 64], Tile2; [0, 64, 64]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 1600 [Tile1, 1:[16x100], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[16x100], 1]
		Tile0: [0, 1600, 1600], Tile1: [0, 1600, 1600], Tile2; [0, 1600, 1600]
	Ker Arg: Scale, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 16 [Tile0, 1:[1x16], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x16], 1]
		Tile0: [0, 16, 16], Tile1: [0, 16, 16], Tile2; [0, 16, 16]
	Ker Arg: ScaleN, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 16 [Tile0, 1:[1x16], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x16], 1]
		Tile0: [0, 16, 16], Tile1: [0, 16, 16], Tile2; [0, 16, 16]
	Ker Arg: Infos, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 9 [Tile1, 1:[1x1], 9]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[1x1], 9]
		Tile0: [0, 9, 9], Tile1: [0, 9, 9], Tile2; [0, 9, 9]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In1 = (signed char * __restrict__) (lynred_L1_Memory+28236);
	KerArg0->W_In1 = (unsigned short int) (256);
	KerArg0->H_In1 = (unsigned short int) (16);
	KerArg0->In2 = (signed char * __restrict__) (lynred_L1_Memory+1024);
	KerArg0->W_In2 = (unsigned short int) (100);
	KerArg0->Bias = (void * __restrict__) (lynred_L1_Memory+32332);
	KerArg0->Scale = (unsigned char * __restrict__) (lynred_L1_Memory+32396);
	KerArg0->ScaleN = (unsigned char * __restrict__) (lynred_L1_Memory+32412);
	KerArg0->Out = (signed char * __restrict__) (lynred_L1_Memory+26624);
	KerArg0->W_Out = (unsigned short int) (100);
	KerArg0->BufferColIn2 = (signed char * __restrict__) (lynred_L1_Memory+0);
	KerArg0->ColFirst = (unsigned char) (1);
	KerArg0->Infos = (signed char *__restrict__) (lynred_L1_Memory+28224);
	KerArg1->In = (signed char *__restrict__) (lynred_L1_Memory+26624);
	KerArg1->Out = (signed char *__restrict__) (lynred_L1_Memory+26624);
	KerArg1->Feat = (unsigned short int) (1);
	KerArg1->W = (unsigned short int) (100);
	KerArg1->H = (unsigned short int) (16);
	KerArg1->Infos = (signed char *__restrict__) (lynred_L1_Memory+28224);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In1+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+28236), 4096, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In1 */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In2+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+1024), 25600, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read In2 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Bias+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), 64, 0, &UchanHF1);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1); /* Wait previous uDMA read Bias */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+32332), 64, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Bias */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Scale+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+46500+0), 16, 0, &UchanHF2);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF2); /* Wait previous uDMA read Scale */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+46500+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+32396), 16, 0, &DmaR_Evt4);
	AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read Scale */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) ScaleN+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+46516+0), 16, 0, &UchanHF3);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF3); /* Wait previous uDMA read ScaleN */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+46516+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+32412), 16, 0, &DmaR_Evt5);
	AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read ScaleN */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Infos+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+46532+0), 9, 0, &UchanHF4);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF4); /* Wait previous uDMA read Infos */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+46532+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+28224), 9, 0, &DmaR_Evt6);
	AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Infos */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on Tile1 */
		int T1Ind_Last = 1;
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1;
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->OutFirstCol = (unsigned short int) ((0)*16);
			KerArg0->NormBias = (unsigned char) (((char *)(lynred_L1_Memory+28224))[5]);
			AT_FORK(gap_ncore(), (void *) KerParMatMulB32_2x4_SQ8, (void *) KerArg0);
			__CALL(KerParMatMulB32_2x4_SQ8, KerArg0);
		} /* End iteration on Tile0 */
		/*====================== Call Kernel LOC_LOOP_EPILOG =========================*/
		AT_FORK(gap_ncore(), (void *) Ker_Sigmoid_SQ8, (void *) KerArg1);
		__CALL(Ker_Sigmoid_SQ8, KerArg1);
	} /* End iteration on Tile1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+26624), 1600, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S115_Op_CONV_2D_0_41_trans_out0(
		signed char * __restrict__ In,
		signed char * __restrict__ Out)

{
	/* Shared L1: 3200 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	KerMatTranspose_fps_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile0 Dim: 1]
	Ker Arg: In, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 1600 [Tile0, 1:[160x10], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[160x10], 1]
		Tile0: [0, 1600, 1600], Tile1: [0, 1600, 1600], Tile2; [0, 1600, 1600]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 1600 [Tile0, 1:[10x160], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[10x160], 1]
		Tile0: [0, 1600, 1600], Tile1: [0, 1600, 1600], Tile2; [0, 1600, 1600]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (signed char *__restrict__) (lynred_L1_Memory+0);
	KerArg0->Out = (signed char *__restrict__) (lynred_L1_Memory+1600);
	KerArg0->Feat = (unsigned short int) (16);
	KerArg0->W = (unsigned short int) (10);
	KerArg0->H = (unsigned short int) (10);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+0), 1600, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on Tile0 */
		int T0Ind_Last = 1;
		/*====================== Call Kernel LOC_LOOP =========================*/
		AT_FORK(gap_ncore(), (void *) CNN_MatPermCHW2HWC_fps, (void *) KerArg0);
		__CALL(CNN_MatPermCHW2HWC_fps, KerArg0);
	} /* End iteration on Tile0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+1600), 1600, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+0), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), 1600, 1, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S119_Conv2d_128x256x1x1_Relu(
		signed char * __restrict__ In2,
		signed char * __restrict__ In1,
		int * __restrict__ Bias,
		signed char * __restrict__ Out,
		unsigned char * __restrict__ Scale,
		unsigned char * __restrict__ ScaleN,
		signed char * __restrict__ Infos)

{
	/* Shared L1: 44620 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaR_Evt4;
	AT_L2_EVENT DmaR_Evt5;
	AT_L2_EVENT DmaR_Evt6;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF1;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF2;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF3;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF4;
	KerMatMul_SQ8_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T1Ind, T1Ind_Total=0, T1Ind_Last, T1Ind_NextLast;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast;
	/* User kernel arguments related variables */
	unsigned int _N_In2;
	unsigned int _SN_In2;
	unsigned int _LN_In2;
	unsigned int _N_In1;
	unsigned int _SN_In1;
	unsigned int _C_Out;
	unsigned int _SP_Out, _SC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile1 Dim: 4][Tile0 Dim: 4]
	Ker Arg: In2, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 4 logical tiles, 4 physical tiles
			Total Size: 25600 [Tile0, 4:[256x28, 2:256x28, 256x16], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 4:[256x28, 2:256x28, 256x16], 1]
		Tile0: [0, 7168, 28], Tile1: [28, 7168, 28], Tile2; [56, 7168, 28]
	Ker Arg: In1, Tiled Space: Tile1
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 4 logical tiles, 4 physical tiles
			Total Size: 32768 [Tile1, 4:[256x40, 2:256x40, 256x8], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 4:[256x40, 2:256x40, 256x8], 1]
		Tile0: [0, 10240, 10240], Tile1: [10240, 10240, 10240], Tile2; [20480, 10240, 10240]
	Ker Arg: KerBuff, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 4 logical tiles, 1 physical tiles
			Total Size: 1024 [Tile0, 4:[1024x1, 2:1024x1, 1024x1], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 4:[1024x1, 2:1024x1, 1024x1], 1]
		Tile0: [0, 1024, 1024], Tile1: [0, 1024, 1024], Tile2; [0, 1024, 1024]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 4 logical tiles, 1 physical tiles
			Total Size: 512 [Tile1, 4:[1x40, 2:1x40, 1x8], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 4:[1x40, 2:1x40, 1x8], 4]
		Tile0: [0, 512, 512], Tile1: [0, 512, 512], Tile2; [0, 512, 512]
	Ker Arg: Out, Tiled Space: Tile1
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 4 logical tiles, 4 physical tiles
			Total Size: 12800 [Tile1, 4:[100x40, 2:100x40, 100x8], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 4:[100x40, 2:100x40, 100x8], 1]
		Tile0: [0, 4000, 4000], Tile1: [4000, 4000, 4000], Tile2; [8000, 4000, 4000]
	Ker Arg: Scale, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 4 logical tiles, 1 physical tiles
			Total Size: 128 [Tile1, 4:[1x40, 2:1x40, 1x8], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 4:[1x40, 2:1x40, 1x8], 1]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: ScaleN, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 4 logical tiles, 1 physical tiles
			Total Size: 128 [Tile1, 4:[1x40, 2:1x40, 1x8], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 4:[1x40, 2:1x40, 1x8], 1]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Infos, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 4 logical tiles, 1 physical tiles
			Total Size: 9 [Tile0, 4:[1x1, 2:1x1, 1x1], 9]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 4:[1x1, 2:1x1, 1x1], 9]
		Tile0: [0, 9, 9], Tile1: [0, 9, 9], Tile2; [0, 9, 9]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->W_In1 = (unsigned short int) (256);
	KerArg0->W_Out = (unsigned short int) (100);
	KerArg0->BufferColIn2 = (signed char * __restrict__) (lynred_L1_Memory+29248);
	KerArg0->ColFirst = (unsigned char) (0);
	KerArg0->Infos = (signed char *__restrict__) (lynred_L1_Memory+44608);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In2+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+30272+0), 7168, 100, 28, 0, &DmaR_Evt1);
	_N_In2=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In1+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+0+0), 10240, 0, &DmaR_Evt2);
	_N_In1=0;
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Bias+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+92004+0), 512, 0, &UchanHF1);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1); /* Wait previous uDMA read Bias */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+92004+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+20480), 512, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Bias */
	_C_Out=0; _SC_Out=4000;
	_SP_Out=0;
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Scale+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+92516+0), 128, 0, &UchanHF2);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF2); /* Wait previous uDMA read Scale */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+92516+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+28992), 128, 0, &DmaR_Evt4);
	AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read Scale */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) ScaleN+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+92644+0), 128, 0, &UchanHF3);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF3); /* Wait previous uDMA read ScaleN */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+92644+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+29120), 128, 0, &DmaR_Evt5);
	AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read ScaleN */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Infos+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+92772+0), 9, 0, &UchanHF4);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF4); /* Wait previous uDMA read Infos */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+92772+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+44608), 9, 0, &DmaR_Evt6);
	AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Infos */
	/*============================= End Read Tiles Prolog ===============================*/
	for (T1Ind=0; T1Ind<4; T1Ind++, T1Ind_Total++) { /* Iteration on Tile1 */
		int T1Ind_Last = (T1Ind==3), T1Ind_NextLast = ((T1Ind+1)==3);
		/*================================= Prepare Tiles ===================================*/
		_SN_In1 = 0;
		if (!(T1Ind_Last)) {
			_N_In1 = _N_In1 + (10240); _SN_In1 = ((T1Ind_NextLast)?2048:10240); 
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read In1 */
		if (_SN_In1) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In1+_N_In1), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+0+10240*((T1Ind_Total+1)%2)),
					_SN_In1, 0, &DmaR_Evt2);
		}
		/*============================= End Read Tiles ======================================*/
		for (T0Ind=0; T0Ind<4; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==3), T0Ind_NextLast = ((T0Ind+1)==3);
			/*================================= Prepare Tiles ===================================*/
			_SN_In2 = 0;
			if (!(T0Ind_Last)) {
				_N_In2 = _N_In2 + (28); _LN_In2 = ((T0Ind_NextLast)?16:28); _SN_In2 = (256*_LN_In2); 
			} else if (!(T1Ind_Last)) {
				_N_In2 = _N_In2 + (-84); _LN_In2 = (28); _SN_In2 = (256*_LN_In2); 
			}
			/*============================= End Prepare Tiles ===================================*/
			/*================================= Read Tiles ======================================*/
			AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In2 */
			if (_SN_In2) {
				AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In2+_N_In2), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+30272+7168*((T0Ind_Total+1)%2)),
						_SN_In2, 100, _LN_In2, 0, &DmaR_Evt1);
			}
			/*============================= End Read Tiles ======================================*/
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->In1 = (signed char * __restrict__) (lynred_L1_Memory+0+10240*((T1Ind_Total)%2));
			KerArg0->H_In1 = (unsigned short int) (T1Ind_Last?8:40);
			KerArg0->In2 = (signed char * __restrict__) (lynred_L1_Memory+30272+7168*((T0Ind_Total)%2));
			KerArg0->W_In2 = (unsigned short int) ((T0Ind_Last)?16:28);
			KerArg0->Bias = (void * __restrict__) (lynred_L1_Memory+20480+(160*(T1Ind)));
			KerArg0->Scale = (unsigned char * __restrict__) (lynred_L1_Memory+28992+(40*(T1Ind)));
			KerArg0->ScaleN = (unsigned char * __restrict__) (lynred_L1_Memory+29120+(40*(T1Ind)));
			KerArg0->Out = (signed char * __restrict__) (lynred_L1_Memory+20992+4000*((T1Ind_Total)%2));
			KerArg0->OutFirstCol = (unsigned short int) ((T0Ind)*28);
			KerArg0->NormBias = (unsigned char) (((char *)(lynred_L1_Memory+44608))[5]);
			AT_FORK(gap_ncore(), (void *) KerParMatMulB32_2x4_ReLU_SQ8, (void *) KerArg0);
			__CALL(KerParMatMulB32_2x4_ReLU_SQ8, KerArg0);
			/*================================= Update Arg Pipeline =============================*/
			/*============================= End Update Arg Pipeline =============================*/
		} /* End iteration on Tile0 */
		/*================================= Write Tiles =====================================*/
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+20992+4000*((T1Ind_Total)%2)),
				_SC_Out, 1, &DmaW_Evt1);
		/*============================= End Write Tiles =====================================*/
		/*================================= Update Arg Pipeline =============================*/
		_SP_Out = _SC_Out;
		/*============================= End Update Arg Pipeline =============================*/
		/*================================= Prepare Tiles ===================================*/
		_SC_Out = 0;
		if (!(T1Ind_Last)) {
			_C_Out = _C_Out + (4000); _SC_Out = ((T1Ind_NextLast)?800:4000); 
		}
		/*============================= End Prepare Tiles ===================================*/
	} /* End iteration on Tile1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S122_Conv2d_256x128x3x3_Relu(
		signed char * __restrict__ In,
		signed char * __restrict__ Filter,
		int * __restrict__ Bias,
		signed char * __restrict__ Out,
		unsigned char * __restrict__ Scale,
		unsigned char * __restrict__ ScaleN,
		signed char * __restrict__ Infos)

{
	/* Shared L1: 49164 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaR_Evt4;
	AT_L2_EVENT DmaR_Evt5;
	AT_L2_EVENT DmaR_Evt6;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF1;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF2;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF3;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF4;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF5;
	KerSetBias_SQ8_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerConv_SQ8_T S_KerArg1, *KerArg1 = &S_KerArg1;
	KerConvLinReduct_SQ8_T S_KerArg2, *KerArg2 = &S_KerArg2;

	/* Iteration space related variables */
	int D1Ind, D1Ind_Total=0, D1Ind_Last, D1Ind_NextLast, D1Ind_NextNextLast;
	int T0Ind, T0Ind_Last, T0Ind_NextLast;
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast, D0Ind_NextNextLast;
	/* User kernel arguments related variables */
	unsigned int _C_Out;
	unsigned int _SP_Out, _SC_Out;
	unsigned int _LP_Out, _LC_Out;
	unsigned int _NN_Bias;
	unsigned int _SN_Bias, _SNN_Bias;
	unsigned int _NN_Filter;
	unsigned int _SN_Filter, _SNN_Filter;
	unsigned int _N_In;
	unsigned int _SN_In;
	unsigned int _LN_In;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 256, Tiled: 2][Tile0 Dim: 1][D0 Dim: Init: 128, Tiled: 32]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 2 physical tiles
			Total Size: 6400 [D1, [1 x 5200, 1200]][Tile0, 1:[5x5], 1]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 5200, 1200]][Tile0, 1:[5x5], 1]
		Tile0: [0, 5200, 25], Tile1: [5200, 1200, 25], Tile2; [0, 5200, 25]
	Ker Arg: Bias, Tiled Space: D1
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 2 logical tiles, 2 physical tiles
			Total Size: 1024 [D1, [1 x 832, 192]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 832, 192]]
		Tile0: [0, 832, 832], Tile1: [832, 192, 192], Tile2; [0, 832, 832]
	Ker Arg: Scale, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 256 [D1, [1 x 208, 48]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 208, 48]]
		Tile0: [0, 256, 256], Tile1: [0, 256, 256], Tile2; [0, 256, 256]
	Ker Arg: ScaleN, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 256 [D1, [1 x 208, 48]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 208, 48]]
		Tile0: [0, 256, 256], Tile1: [0, 256, 256], Tile2; [0, 256, 256]
	Ker Arg: Filter, Tiled Space: D0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 64 logical tiles, 64 physical tiles
			Total Size: 294912 [D1, [1 x 239616, 55296]][D0, [31 x 7488, 7488]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 239616, 55296]][D0, [31 x 7488, 7488]]
		Tile0: [0, 7488, 7488], Tile1: [7488, 7488, 7488], Tile2; [14976, 7488, 7488]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 32 logical tiles, 32 physical tiles
			Total Size: 12800 [D0, [31 x 400, 400]][Tile0, 1:[10x10], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[10x11, 30:10x11, 10x10], 1][D0, [31 x 400, 400]]
		Tile0: [0, 400, 100], Tile1: [400, 400, 100], Tile2; [800, 400, 100]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 25600 [D1, [1 x 20800, 4800]][Tile0, 1:[5x5], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 20800, 4800]][Tile0, 1:[5x5], 4]
		Tile0: [0, 20800, 100], Tile1: [0, 20800, 100], Tile2; [0, 20800, 100]
	Ker Arg: Infos, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 9 [Tile0, 1:[9x1], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[9x1], 1]
		Tile0: [0, 9, 9], Tile1: [0, 9, 9], Tile2; [0, 9, 9]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (lynred_L1_Memory+28352);
	KerArg0->W = (unsigned short int) (5);
	KerArg0->H = (unsigned short int) (5);
	KerArg1->W = (unsigned short int) (10);
	KerArg1->UsedW = (unsigned short int) (10);
	KerArg1->InFeatures = (unsigned short int) (4);
	KerArg1->TotalInFeatures = (unsigned short int) (4);
	KerArg1->Out = (int * __restrict__) (lynred_L1_Memory+28352);
	KerArg1->Pad = (v4s) ((v4s){0,1,0,1});
	KerArg2->In = (int *__restrict__) (lynred_L1_Memory+28352);
	KerArg2->W = (unsigned short int) (5);
	KerArg2->H = (unsigned short int) (5);
	KerArg2->Infos = (signed char *__restrict__) (lynred_L1_Memory+49152);
	/*================================= Read Tiles Prolog ===============================*/
	_C_Out=0; _SC_Out=5200; _LC_Out=25;
	_SP_Out=0;
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Bias+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+84708+0), 832, 0, &UchanHF1);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1); /* Wait previous uDMA read Bias */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Bias+832), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+84708+832), 192, 0, &UchanHF1);
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+84708+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+800+0), 832, 0, &DmaR_Evt1);
	_NN_Bias=832; _SN_Bias=192;
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Scale+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+86372+0), 256, 0, &UchanHF2);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF2); /* Wait previous uDMA read Scale */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+86372+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+2464), 256, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Scale */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) ScaleN+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+86628+0), 256, 0, &UchanHF3);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF3); /* Wait previous uDMA read ScaleN */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+86628+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+2720), 256, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read ScaleN */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Filter+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+65636+0), 7488, 0, &UchanHF4);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF4); /* Wait previous uDMA read Filter */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Filter+7488), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+65636+7488), 7488, 0, &UchanHF4);
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+65636+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+2976+0), 7488, 0, &DmaR_Evt4);
	_NN_Filter=7488; _SN_Filter=7488;
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+0+0), 400, 100, 100, 0, &DmaR_Evt5);
	_N_In=0;
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Infos+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+86980+0), 9, 0, &UchanHF5);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF5); /* Wait previous uDMA read Infos */
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+86980+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+49152), 9, 0, &DmaR_Evt6);
	AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Infos */
	/*============================= End Read Tiles Prolog ===============================*/
	for (D1Ind=0; D1Ind<2; D1Ind++, D1Ind_Total++) { /* Iteration on D1 */
		int D1Ind_Last = (D1Ind==1), D1Ind_NextLast = ((D1Ind+1)==1), D1Ind_NextNextLast = ((D1Ind+2)==1);
		/*================================= Prepare Tiles ===================================*/
		_SNN_Bias = 0;
		if (!(D1Ind_Last)) {
			if (!(1)) {
				_NN_Bias = _NN_Bias + (832); _SNN_Bias = ((1)?192:832); 
			}
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1); /* Wait previous uDMA read Bias */
		if (_SNN_Bias) {
			AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Bias+_NN_Bias), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+84708+832*((D1Ind_Total)%2)),
					_SNN_Bias, 0, &UchanHF1);
		}
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Bias */
		if (_SN_Bias) {
			AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+84708+832*((D1Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+800+832*((D1Ind_Total+1)%2)),
					_SN_Bias, 0, &DmaR_Evt1);
		}
		/*============================= End Read Tiles ======================================*/
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1, T0Ind_NextLast = 1;
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->Feat = (unsigned short int) ((D1Ind_Last)?48:208);
			KerArg0->Bias = (void * __restrict__) (lynred_L1_Memory+800+832*((D1Ind_Total)%2));
			KerArg0->NormBias = (unsigned char) (((char *)(lynred_L1_Memory+49152))[5]);
			AT_FORK(gap_ncore(), (void *) KerParSetBiasB32_SQ8, (void *) KerArg0);
			__CALL(KerParSetBiasB32_SQ8, KerArg0);
			for (D0Ind=0; D0Ind<32; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==31), D0Ind_NextLast = ((D0Ind+1)==31), D0Ind_NextNextLast = ((D0Ind+2)==31);
				/*================================= Prepare Tiles ===================================*/
				_SNN_Filter = 0;
				if (!(D0Ind_Last)) {
					if (!(D0Ind_NextLast)) {
						_NN_Filter = _NN_Filter + (((D1Ind_Last)?(1728):(7488))); _SNN_Filter = (((D1Ind_Last)?(1728):(7488))); 
					} else if (!((1))) {
						_NN_Filter = _NN_Filter + (((D1Ind_Last)?(-53568):(-232128))); _SNN_Filter = (((D1Ind_Last)?(1728):(7488))); 
					} else if (!(D1Ind_Last)) {
						_NN_Filter = _NN_Filter + (239616)+(((D1Ind_Last)?(-53568):(-232128))); _SNN_Filter = (((1)?(1728):(7488))); 
					}
				} else if (!((1))) {
					_NN_Filter = _NN_Filter + (((D1Ind_Last)?(1728):(7488))); _SNN_Filter = (((D1Ind_Last)?(1728):(7488))); 
				} else if (!(D1Ind_Last)) {
					_NN_Filter = _NN_Filter + (((1)?(1728):(7488))); _SNN_Filter = (((1)?(1728):(7488))); 
				}
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (400); _LN_In = (100); _SN_In = (4*_LN_In); 
				} else if (!(D1Ind_Last)) {
					_N_In = _N_In + (-12400); _LN_In = (100); _SN_In = (4*_LN_In); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF4); /* Wait previous uDMA read Filter */
				if (_SNN_Filter) {
					AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) Filter+_NN_Filter), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+65636+7488*((D0Ind_Total)%2)),
							_SNN_Filter, 0, &UchanHF4);
				}
				AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read Filter */
				if (_SN_Filter) {
					AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+65636+7488*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+2976+7488*((D0Ind_Total+1)%2)),
							_SN_Filter, 0, &DmaR_Evt4);
				}
				AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+0+400*((D0Ind_Total+1)%2)),
							_SN_In, 100, _LN_In, 0, &DmaR_Evt5);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (signed char * __restrict__) (lynred_L1_Memory+0+400*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (11-0*(1)-1*(1));
				KerArg1->UsedH = (unsigned short int) (11-0*(1)-1*(1));
				KerArg1->OutFeatures = (unsigned short int) ((D1Ind_Last)?48:208);
				KerArg1->Filter = (signed char * __restrict__) (lynred_L1_Memory+2976+7488*((D0Ind_Total)%2));
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride2_SQ8, (void *) KerArg1);
				__CALL(KerParConv3x3Stride2_SQ8, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				_SN_Filter = _SNN_Filter;
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->Out = (void *__restrict__) (lynred_L1_Memory+17952+5200*((D1Ind_Total)%2));
			KerArg2->Feat = (unsigned short int) ((D1Ind_Last)?48:208);
			KerArg2->Scale = (unsigned char *__restrict__) (lynred_L1_Memory+2464+((D1Ind)*208));
			KerArg2->ScaleN = (unsigned char *__restrict__) (lynred_L1_Memory+2720+((D1Ind)*208));
			AT_FORK(gap_ncore(), (void *) KerParReduct_CC_ReLU_SQ8, (void *) KerArg2);
			__CALL(KerParReduct_CC_ReLU_SQ8, KerArg2);
		} /* End iteration on Tile0 */
		/*================================= Write Tiles =====================================*/
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
		AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+17952+5200*((D1Ind_Total)%2)),
				_SC_Out, 25, _LC_Out, 1, &DmaW_Evt1);
		/*============================= End Write Tiles =====================================*/
		/*================================= Update Arg Pipeline =============================*/
		_SP_Out = _SC_Out;_LP_Out = _LC_Out;
		_SN_Bias = _SNN_Bias;
		/*============================= End Update Arg Pipeline =============================*/
		/*================================= Prepare Tiles ===================================*/
		_SC_Out = 0;
		if (!(D1Ind_Last)) {
			_C_Out = _C_Out + (5200); _LC_Out = (25); _SC_Out = (((1)?48:208)*_LC_Out); 
		}
		/*============================= End Prepare Tiles ===================================*/
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S125_Conv2d_32x256x1x1(
		signed char * __restrict__ In2,
		signed char * __restrict__ In1,
		int * __restrict__ Bias,
		signed char * __restrict__ Out,
		unsigned char * __restrict__ Scale,
		unsigned char * __restrict__ ScaleN,
		signed char * __restrict__ Infos)

{
	/* Shared L1: 16620 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaR_Evt4;
	AT_L2_EVENT DmaR_Evt5;
	AT_L2_EVENT DmaR_Evt6;
	AT_L2_EVENT DmaW_Evt1;
	KerMatMul_SQ8_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T1Ind, T1Ind_Last;
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile1 Dim: 1][Tile0 Dim: 1]
	Ker Arg: KerBuff, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 1024 [Tile0, 1:[1024x1], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1024x1], 1]
		Tile0: [0, 1024, 1024], Tile1: [0, 1024, 1024], Tile2; [0, 1024, 1024]
	Ker Arg: In1, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 8192 [Tile1, 1:[256x32], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[256x32], 1]
		Tile0: [0, 8192, 8192], Tile1: [0, 8192, 8192], Tile2; [0, 8192, 8192]
	Ker Arg: In2, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 6400 [Tile0, 1:[256x25], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[256x25], 1]
		Tile0: [0, 6400, 6400], Tile1: [0, 6400, 6400], Tile2; [0, 6400, 6400]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 128 [Tile1, 1:[1x32], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[1x32], 4]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 800 [Tile1, 1:[25x32], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[25x32], 1]
		Tile0: [0, 800, 800], Tile1: [0, 800, 800], Tile2; [0, 800, 800]
	Ker Arg: Scale, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 32 [Tile1, 1:[1x32], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[1x32], 1]
		Tile0: [0, 32, 32], Tile1: [0, 32, 32], Tile2; [0, 32, 32]
	Ker Arg: ScaleN, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 32 [Tile1, 1:[1x32], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[1x32], 1]
		Tile0: [0, 32, 32], Tile1: [0, 32, 32], Tile2; [0, 32, 32]
	Ker Arg: Infos, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 9 [Tile0, 1:[1x1], 9]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x1], 9]
		Tile0: [0, 9, 9], Tile1: [0, 9, 9], Tile2; [0, 9, 9]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In1 = (signed char * __restrict__) (lynred_L1_Memory+0);
	KerArg0->W_In1 = (unsigned short int) (256);
	KerArg0->H_In1 = (unsigned short int) (32);
	KerArg0->In2 = (signed char * __restrict__) (lynred_L1_Memory+10208);
	KerArg0->W_In2 = (unsigned short int) (25);
	KerArg0->Bias = (void * __restrict__) (lynred_L1_Memory+8192);
	KerArg0->Scale = (unsigned char * __restrict__) (lynred_L1_Memory+9120);
	KerArg0->ScaleN = (unsigned char * __restrict__) (lynred_L1_Memory+9152);
	KerArg0->Out = (signed char * __restrict__) (lynred_L1_Memory+8320);
	KerArg0->W_Out = (unsigned short int) (25);
	KerArg0->BufferColIn2 = (signed char * __restrict__) (lynred_L1_Memory+9184);
	KerArg0->ColFirst = (unsigned char) (0);
	KerArg0->Infos = (signed char *__restrict__) (lynred_L1_Memory+16608);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In1+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+0), 8192, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In1 */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In2+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+10208), 6400, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read In2 */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+8192), 128, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Scale+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+9120), 32, 0, &DmaR_Evt4);
	AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read Scale */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) ScaleN+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+9152), 32, 0, &DmaR_Evt5);
	AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read ScaleN */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Infos+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+16608), 9, 0, &DmaR_Evt6);
	AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Infos */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on Tile1 */
		int T1Ind_Last = 1;
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1;
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->OutFirstCol = (unsigned short int) ((0)*25);
			KerArg0->NormBias = (unsigned char) (((char *)(lynred_L1_Memory+16608))[5]);
			AT_FORK(gap_ncore(), (void *) KerParMatMulB32_2x4_SQ8, (void *) KerArg0);
			__CALL(KerParMatMulB32_2x4_SQ8, KerArg0);
		} /* End iteration on Tile0 */
	} /* End iteration on Tile1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+8320), 800, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S126_Op_CONV_2D_0_45_trans_out0(
		signed char * __restrict__ In,
		signed char * __restrict__ Out)

{
	/* Shared L1: 1600 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	KerMatTranspose_fps_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile0 Dim: 1]
	Ker Arg: In, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 800 [Tile0, 1:[160x5], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[160x5], 1]
		Tile0: [0, 800, 800], Tile1: [0, 800, 800], Tile2; [0, 800, 800]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 800 [Tile0, 1:[5x160], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[5x160], 1]
		Tile0: [0, 800, 800], Tile1: [0, 800, 800], Tile2; [0, 800, 800]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (signed char *__restrict__) (lynred_L1_Memory+0);
	KerArg0->Out = (signed char *__restrict__) (lynred_L1_Memory+800);
	KerArg0->Feat = (unsigned short int) (32);
	KerArg0->W = (unsigned short int) (5);
	KerArg0->H = (unsigned short int) (5);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+0), 800, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on Tile0 */
		int T0Ind_Last = 1;
		/*====================== Call Kernel LOC_LOOP =========================*/
		AT_FORK(gap_ncore(), (void *) CNN_MatPermCHW2HWC_fps, (void *) KerArg0);
		__CALL(CNN_MatPermCHW2HWC_fps, KerArg0);
	} /* End iteration on Tile0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+47236+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+800), 800, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+0), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+47236+0), 800, 1, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S132_Conv2d_16x256x1x1_Sigmoid(
		signed char * __restrict__ In2,
		signed char * __restrict__ In1,
		int * __restrict__ Bias,
		signed char * __restrict__ Out,
		unsigned char * __restrict__ Scale,
		unsigned char * __restrict__ ScaleN,
		signed char * __restrict__ Infos)

{
	/* Shared L1: 12028 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaR_Evt4;
	AT_L2_EVENT DmaR_Evt5;
	AT_L2_EVENT DmaR_Evt6;
	AT_L2_EVENT DmaW_Evt1;
	KerMatMul_SQ8_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerActivation_SQ8_T S_KerArg1, *KerArg1 = &S_KerArg1;

	/* Iteration space related variables */
	int T1Ind, T1Ind_Last;
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile1 Dim: 1][Tile0 Dim: 1]
	Ker Arg: KerBuff, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 1024 [Tile1, 1:[1024x1], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[1024x1], 1]
		Tile0: [0, 1024, 1024], Tile1: [0, 1024, 1024], Tile2; [0, 1024, 1024]
	Ker Arg: In1, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 4096 [Tile0, 1:[256x16], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[256x16], 1]
		Tile0: [0, 4096, 4096], Tile1: [0, 4096, 4096], Tile2; [0, 4096, 4096]
	Ker Arg: In2, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 6400 [Tile1, 1:[256x25], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[256x25], 1]
		Tile0: [0, 6400, 6400], Tile1: [0, 6400, 6400], Tile2; [0, 6400, 6400]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 64 [Tile0, 1:[1x16], 4]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x16], 4]
		Tile0: [0, 64, 64], Tile1: [0, 64, 64], Tile2; [0, 64, 64]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 400 [Tile1, 1:[16x25], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[16x25], 1]
		Tile0: [0, 400, 400], Tile1: [0, 400, 400], Tile2; [0, 400, 400]
	Ker Arg: Scale, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 16 [Tile0, 1:[1x16], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x16], 1]
		Tile0: [0, 16, 16], Tile1: [0, 16, 16], Tile2; [0, 16, 16]
	Ker Arg: ScaleN, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 16 [Tile0, 1:[1x16], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x16], 1]
		Tile0: [0, 16, 16], Tile1: [0, 16, 16], Tile2; [0, 16, 16]
	Ker Arg: Infos, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 9 [Tile1, 1:[1x1], 9]
		KerArgItSpace (User Kernel Iter Order):
			[Tile1, 1:[1x1], 9]
		Tile0: [0, 9, 9], Tile1: [0, 9, 9], Tile2; [0, 9, 9]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In1 = (signed char * __restrict__) (lynred_L1_Memory+7836);
	KerArg0->W_In1 = (unsigned short int) (256);
	KerArg0->H_In1 = (unsigned short int) (16);
	KerArg0->In2 = (signed char * __restrict__) (lynred_L1_Memory+1024);
	KerArg0->W_In2 = (unsigned short int) (25);
	KerArg0->Bias = (void * __restrict__) (lynred_L1_Memory+11932);
	KerArg0->Scale = (unsigned char * __restrict__) (lynred_L1_Memory+11996);
	KerArg0->ScaleN = (unsigned char * __restrict__) (lynred_L1_Memory+12012);
	KerArg0->Out = (signed char * __restrict__) (lynred_L1_Memory+7424);
	KerArg0->W_Out = (unsigned short int) (25);
	KerArg0->BufferColIn2 = (signed char * __restrict__) (lynred_L1_Memory+0);
	KerArg0->ColFirst = (unsigned char) (1);
	KerArg0->Infos = (signed char *__restrict__) (lynred_L1_Memory+7824);
	KerArg1->In = (signed char *__restrict__) (lynred_L1_Memory+7424);
	KerArg1->Out = (signed char *__restrict__) (lynred_L1_Memory+7424);
	KerArg1->Feat = (unsigned short int) (1);
	KerArg1->W = (unsigned short int) (25);
	KerArg1->H = (unsigned short int) (16);
	KerArg1->Infos = (signed char *__restrict__) (lynred_L1_Memory+7824);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In1+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+7836), 4096, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In1 */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In2+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+1024), 6400, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read In2 */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+11932), 64, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Scale+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+11996), 16, 0, &DmaR_Evt4);
	AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read Scale */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) ScaleN+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+12012), 16, 0, &DmaR_Evt5);
	AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read ScaleN */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Infos+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+7824), 9, 0, &DmaR_Evt6);
	AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Infos */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on Tile1 */
		int T1Ind_Last = 1;
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1;
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->OutFirstCol = (unsigned short int) ((0)*16);
			KerArg0->NormBias = (unsigned char) (((char *)(lynred_L1_Memory+7824))[5]);
			AT_FORK(gap_ncore(), (void *) KerParMatMulB32_2x4_SQ8, (void *) KerArg0);
			__CALL(KerParMatMulB32_2x4_SQ8, KerArg0);
		} /* End iteration on Tile0 */
		/*====================== Call Kernel LOC_LOOP_EPILOG =========================*/
		AT_FORK(gap_ncore(), (void *) Ker_Sigmoid_SQ8, (void *) KerArg1);
		__CALL(Ker_Sigmoid_SQ8, KerArg1);
	} /* End iteration on Tile1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+7424), 400, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S133_Op_CONV_2D_0_49_trans_out0(
		signed char * __restrict__ In,
		signed char * __restrict__ Out)

{
	/* Shared L1: 800 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	KerMatTranspose_fps_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile0 Dim: 1]
	Ker Arg: In, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 400 [Tile0, 1:[80x5], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[80x5], 1]
		Tile0: [0, 400, 400], Tile1: [0, 400, 400], Tile2; [0, 400, 400]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 400 [Tile0, 1:[5x80], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[5x80], 1]
		Tile0: [0, 400, 400], Tile1: [0, 400, 400], Tile2; [0, 400, 400]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (signed char *__restrict__) (lynred_L1_Memory+0);
	KerArg0->Out = (signed char *__restrict__) (lynred_L1_Memory+400);
	KerArg0->Feat = (unsigned short int) (16);
	KerArg0->W = (unsigned short int) (5);
	KerArg0->H = (unsigned short int) (5);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+0), 400, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on Tile0 */
		int T0Ind_Last = 1;
		/*====================== Call Kernel LOC_LOOP =========================*/
		AT_FORK(gap_ncore(), (void *) CNN_MatPermCHW2HWC_fps, (void *) KerArg0);
		__CALL(CNN_MatPermCHW2HWC_fps, KerArg0);
	} /* End iteration on Tile0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46836+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+400), 400, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+0), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46836+0), 400, 1, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S137_Op_CUSTOM_0_53(
		int8_t * __restrict__ boxes_in,
		int8_t * __restrict__ classes_in,
		int8_t * __restrict__ anchors_in,
		int16_t * bbox_out,
		int8_t * class_out,
		int8_t * scores_out,
		uint8_t *  in_scales,
		uint8_t *  in_norms)

{
	/* Shared L1: 49964 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaR_Evt4;
	AT_L2_EVENT DmaR_Evt5;
	AT_L2_EVENT DmaW_Evt1;
	AT_L2_EVENT DmaW_Evt2;
	AT_L2_EVENT DmaW_Evt3;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	AT_HYPERRAM_CL_EVENT UchanHR2;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF3;
	Ker_SSD_Init_ArgT S_KerArg0, *KerArg0 = &S_KerArg0;
	Ker_SSD_Decoder_ArgT S_KerArg1, *KerArg1 = &S_KerArg1;
	Ker_SSD_NMS_ArgT S_KerArg2, *KerArg2 = &S_KerArg2;

	/* Iteration space related variables */
	int D0Ind, D0Ind_Last;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast, T0Ind_NextNextLast;
	/* User kernel arguments related variables */
	unsigned int _NN_boxes_in;
	unsigned int _SN_boxes_in, _SNN_boxes_in;
	unsigned int _NN_classes_in;
	unsigned int _SN_classes_in, _SNN_classes_in;
	unsigned int _NN_anchors_in;
	unsigned int _SN_anchors_in, _SNN_anchors_in;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D0 Dim: 1][Tile0 Dim: 4]
	Ker Arg: boxes_in, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 4 logical tiles, 4 physical tiles
			Total Size: 36000 [Tile0, 4:[4x2312, 2:4x2312, 4x2064], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 4:[4x2312, 2:4x2312, 4x2064], 1]
		Tile0: [0, 9248, 9248], Tile1: [9248, 9248, 9248], Tile2; [18496, 9248, 9248]
	Ker Arg: classes_in, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 4 logical tiles, 4 physical tiles
			Total Size: 18000 [Tile0, 4:[2x2312, 2:2x2312, 2x2064], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 4:[2x2312, 2:2x2312, 2x2064], 1]
		Tile0: [0, 4624, 4624], Tile1: [4624, 4624, 4624], Tile2; [9248, 4624, 4624]
	Ker Arg: anchors_in, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 4 logical tiles, 4 physical tiles
			Total Size: 36000 [Tile0, 4:[4x2312, 2:4x2312, 4x2064], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 4:[4x2312, 2:4x2312, 4x2064], 1]
		Tile0: [0, 9248, 9248], Tile1: [9248, 9248, 9248], Tile2; [18496, 9248, 9248]
	Ker Arg: bbox_buf, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 3600 [D0, [0 x 3600, 3600]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 3600, 3600]]
		Tile0: [0, 3600, 3600], Tile1: [0, 3600, 3600], Tile2; [0, 3600, 3600]
	Ker Arg: bbox_out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 80 [D0, [0 x 80, 80]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 80, 80]]
		Tile0: [0, 80, 80], Tile1: [0, 80, 80], Tile2; [0, 80, 80]
	Ker Arg: scores_out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 10 [D0, [0 x 10, 10]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 10, 10]]
		Tile0: [0, 10, 10], Tile1: [0, 10, 10], Tile2; [0, 10, 10]
	Ker Arg: class_out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 10 [D0, [0 x 10, 10]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 10, 10]]
		Tile0: [0, 10, 10], Tile1: [0, 10, 10], Tile2; [0, 10, 10]
	Ker Arg: bbox_idx, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 2 [D0, [0 x 2, 2]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 2, 2]]
		Tile0: [0, 2, 2], Tile1: [0, 2, 2], Tile2; [0, 2, 2]
	Ker Arg: in_scales, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 8 [D0, [0 x 8, 8]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 8, 8]]
		Tile0: [0, 8, 8], Tile1: [0, 8, 8], Tile2; [0, 8, 8]
	Ker Arg: in_norms, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 8 [D0, [0 x 8, 8]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 8, 8]]
		Tile0: [0, 8, 8], Tile1: [0, 8, 8], Tile2; [0, 8, 8]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->n_max_bb = (int16_t ) (300);
	KerArg1->Box_W = (int16_t ) (4);
	KerArg1->Class_W = (int16_t ) (2);
	KerArg1->ScoreThr = (int) (76);
	KerArg1->n_max_bb = (int16_t ) (300);
	KerArg2->n_out_box = (int16_t) (10);
	KerArg2->NMSThr = (int) (12);
	KerArg2->n_max_bb = (int16_t ) (300);
	/*================================= Read Tiles Prolog ===============================*/
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) boxes_in+0), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), 9248, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read boxes_in */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) boxes_in+9248), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+9248), 9248, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+0+0), 9248, 0, &DmaR_Evt1);
	_NN_boxes_in=9248; _SN_boxes_in=9248;
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) classes_in+0), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+64932+0), 4624, 0, &UchanHR2);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read classes_in */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) classes_in+4624), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+64932+4624), 4624, 0, &UchanHR2);
	AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+64932+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+18496+0), 4624, 0, &DmaR_Evt2);
	_NN_classes_in=4624; _SN_classes_in=4624;
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) anchors_in+0), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+74180+0), 9248, 0, &UchanHF3);
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF3); /* Wait previous uDMA read anchors_in */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) anchors_in+9248), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+74180+9248), 9248, 0, &UchanHF3);
	AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+74180+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+27744+0), 9248, 0, &DmaR_Evt3);
	_NN_anchors_in=9248; _SN_anchors_in=9248;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) in_scales+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+49948), 8, 0, &DmaR_Evt4);
	AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read in_scales */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) in_norms+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+49956), 8, 0, &DmaR_Evt5);
	AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read in_norms */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D0 */
		int D0Ind_Last = 1;
		/*====================== Call Kernel LOC_LOOP_PROLOG =========================*/
		KerArg0->bbox_idx = (int16_t *) (lynred_L1_Memory+49944);
		KerArg0->bbox_buf = (bbox_t *) (lynred_L1_Memory+46240);
		Ker_SSD_Init(KerArg0);
		for (T0Ind=0; T0Ind<4; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==3), T0Ind_NextLast = ((T0Ind+1)==3), T0Ind_NextNextLast = ((T0Ind+2)==3);
			/*================================= Prepare Tiles ===================================*/
			_SNN_boxes_in = 0;
			if (!(T0Ind_Last)) {
				if (!(T0Ind_NextLast)) {
					_NN_boxes_in = _NN_boxes_in + (9248); _SNN_boxes_in = ((T0Ind_NextNextLast)?8256:9248); 
				} else if (!(1)) {
					_NN_boxes_in = _NN_boxes_in + (-27744); _SNN_boxes_in = (9248); 
				}
			} else if (!((1))) {
				_NN_boxes_in = _NN_boxes_in + (9248); _SNN_boxes_in = (9248); 
			}
			_SNN_classes_in = 0;
			if (!(T0Ind_Last)) {
				if (!(T0Ind_NextLast)) {
					_NN_classes_in = _NN_classes_in + (4624); _SNN_classes_in = ((T0Ind_NextNextLast)?4128:4624); 
				} else if (!(1)) {
					_NN_classes_in = _NN_classes_in + (-13872); _SNN_classes_in = (4624); 
				}
			} else if (!((1))) {
				_NN_classes_in = _NN_classes_in + (4624); _SNN_classes_in = (4624); 
			}
			_SNN_anchors_in = 0;
			if (!(T0Ind_Last)) {
				if (!(T0Ind_NextLast)) {
					_NN_anchors_in = _NN_anchors_in + (9248); _SNN_anchors_in = ((T0Ind_NextNextLast)?8256:9248); 
				} else if (!(1)) {
					_NN_anchors_in = _NN_anchors_in + (-27744); _SNN_anchors_in = (9248); 
				}
			} else if (!((1))) {
				_NN_anchors_in = _NN_anchors_in + (9248); _SNN_anchors_in = (9248); 
			}
			/*============================= End Prepare Tiles ===================================*/
			/*================================= Read Tiles ======================================*/
			AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read boxes_in */
			if (_SNN_boxes_in) {
				AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) boxes_in+_NN_boxes_in), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+9248*((T0Ind_Total)%2)),
						_SNN_boxes_in, 0, &UchanHR1);
			}
			AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read boxes_in */
			if (_SN_boxes_in) {
				AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+46436+9248*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+0+9248*((T0Ind_Total+1)%2)),
						_SN_boxes_in, 0, &DmaR_Evt1);
			}
			AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR2); /* Wait previous uDMA read classes_in */
			if (_SNN_classes_in) {
				AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) classes_in+_NN_classes_in), ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+64932+4624*((T0Ind_Total)%2)),
						_SNN_classes_in, 0, &UchanHR2);
			}
			AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read classes_in */
			if (_SN_classes_in) {
				AT_L2_COPY(0, ((AT_HYPERRAM_INT_ADDR_TYPE) lynred_L2_Memory+64932+4624*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+18496+4624*((T0Ind_Total+1)%2)),
						_SN_classes_in, 0, &DmaR_Evt2);
			}
			AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF3); /* Wait previous uDMA read anchors_in */
			if (_SNN_anchors_in) {
				AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) anchors_in+_NN_anchors_in), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+74180+9248*((T0Ind_Total)%2)),
						_SNN_anchors_in, 0, &UchanHF3);
			}
			AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read anchors_in */
			if (_SN_anchors_in) {
				AT_L2_COPY(0, ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory+74180+9248*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+27744+9248*((T0Ind_Total+1)%2)),
						_SN_anchors_in, 0, &DmaR_Evt3);
			}
			/*============================= End Read Tiles ======================================*/
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg1->boxes_in = (int8_t * __restrict__) (lynred_L1_Memory+0+9248*((T0Ind_Total)%2));
			KerArg1->classes_in = (int8_t * __restrict__) (lynred_L1_Memory+18496+4624*((T0Ind_Total)%2));
			KerArg1->anchors_in = (int8_t * __restrict__) (lynred_L1_Memory+27744+9248*((T0Ind_Total)%2));
			KerArg1->bbox_buf = (bbox_t *) (lynred_L1_Memory+46240);
			KerArg1->H = (int16_t ) (T0Ind_Last?2064:2312);
			KerArg1->in_scales = (uint8_t *) (lynred_L1_Memory+49948);
			KerArg1->in_norms = (uint8_t *) (lynred_L1_Memory+49956);
			KerArg1->bbox_idx = (int16_t *) (lynred_L1_Memory+49944);
			AT_FORK(gap_ncore(), (void *) Ker_SSD_Decoder, (void *) KerArg1);
			__CALL(Ker_SSD_Decoder, KerArg1);
			/*================================= Update Arg Pipeline =============================*/
			_SN_boxes_in = _SNN_boxes_in;
			_SN_classes_in = _SNN_classes_in;
			_SN_anchors_in = _SNN_anchors_in;
			/*============================= End Update Arg Pipeline =============================*/
		} /* End iteration on Tile0 */
		/*====================== Call Kernel LOC_LOOP_EPILOG =========================*/
		KerArg2->bbox_buf = (bbox_t *) (lynred_L1_Memory+46240);
		KerArg2->bbox_out = (int16_t *) (lynred_L1_Memory+49840);
		KerArg2->scores_out = (int8_t *) (lynred_L1_Memory+49920);
		KerArg2->class_out = (int8_t *) (lynred_L1_Memory+49932);
		KerArg2->bbox_idx = (int16_t *) (lynred_L1_Memory+49944);
		Ker_SSD_NMS(KerArg2);
	} /* End iteration on D0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) bbox_out+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+49840), 80, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write bbox_out */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) scores_out+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+49920), 10, 1, &DmaW_Evt2);
	AT_L2_WAIT(0, &DmaW_Evt2); /* Wait DMA write scores_out */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) class_out+0), ((AT_L2_INT_ADDR_TYPE) lynred_L1_Memory+49932), 10, 1, &DmaW_Evt3);
	AT_L2_WAIT(0, &DmaW_Evt3); /* Wait DMA write class_out */
	/*============================ End Write Tiles Epilog ===============================*/
}
int lynredCNN_Construct(int Warm)

{
	if (Warm) {
		lynred_L1_Memory = (AT_L1_POINTER) AT_L1_ALLOC(0, 49980);
		if (lynred_L1_Memory == 0) return 4;
		return 0;
	}
	AT_HYPERFLASH_FS_FC_EVENT UchanHF1;
	AT_HYPERFLASH_FS_CONF_T HyperFlashConf;
	int Error;
	AT_HYPERFLASH_FS_CONF_INIT(&HyperFlashConf, AT_MEM_L3_HFLASH, 0);
	AT_HYPERFLASH_FS_OPEN(&HyperFlash, &HyperFlashConf, "lynred_L3_Flash_Const.dat", &Error);
	if (Error) return 1;
	lynred_L3_Memory = (AT_HYPERRAM_POINTER) AT_HYPERRAM_ALLOC(&HyperRam, 665600);
	if (lynred_L3_Memory == 0) return 2;
	lynred_L2_Memory = (AT_L2_POINTER) AT_L2_ALLOC(0, 150000);
	if (lynred_L2_Memory == 0) return 3;
	lynred_L1_Memory = (AT_L1_POINTER) AT_L1_ALLOC(0, 49980);
	if (lynred_L1_Memory == 0) return 4;
	/* Moving Stdconstant21, size 288 from HyperFlash at 1098224 to (size 288) L2 at 9792..10079 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1098224), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 9792), 288, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving 1_convbias, size 128 from HyperFlash at 1103472 to (size 128) L2 at 10368..10495 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1103472), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 10368), 128, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving S4_Mul_scale, size 32 from HyperFlash at 1105920 to (size 32) L2 at 10624..10655 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1105920), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 10624), 32, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving S4_Mul_shift, size 32 from HyperFlash at 1105952 to (size 32) L2 at 10656..10687 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1105952), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 10656), 32, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving S4_Infos, size 9 from HyperFlash at 1106600 to (size 9) L2 at 10752..10760 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1106600), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 10752), 9, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Stdconstant50, size 288 from HyperFlash at 1098512 to (size 288) L2 at 10080..10367 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1098512), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 10080), 288, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Stdconstant3, size 128 from HyperFlash at 1103600 to (size 128) L2 at 10496..10623 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1103600), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 10496), 128, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving S7_Mul_scale, size 32 from HyperFlash at 1105984 to (size 32) L2 at 10688..10719 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1105984), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 10688), 32, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving S7_Mul_shift, size 32 from HyperFlash at 1106016 to (size 32) L2 at 10720..10751 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1106016), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 10720), 32, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving S7_Infos, size 9 from HyperFlash at 1106612 to (size 9) L2 at 10764..10772 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1106612), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 10764), 9, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving S10_Infos, size 9 from HyperFlash at 1106624 to (size 12) L2 at 46424..46435 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1106624), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 46424), 9, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Stdconstant4, size 576 from HyperFlash at 1089904 to (size 576) L2 at 45848..46423 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1089904), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 45848), 576, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Stdconstant6, size 768 from HyperFlash at 1085296 to (size 768) L2 at 9024..9791 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1085296), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 9024), 768, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Stdconstant54, size 1728 from HyperFlash at 1065632 to (size 1728) L2 at 2304..4031 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1065632), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 2304), 1728, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Stdconstant56, size 1728 from HyperFlash at 1067360 to (size 1728) L2 at 4032..5759 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1067360), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 4032), 1728, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Stdconstant30, size 2304 from HyperFlash at 1061024 to (size 2304) L2 at 0..2303 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1061024), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 0), 2304, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Stdconstant58, size 1728 from HyperFlash at 1069088 to (size 1728) L2 at 5760..7487 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1069088), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 5760), 1728, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Stdconstant12, size 1536 from HyperFlash at 1070816 to (size 1536) L2 at 7488..9023 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1070816), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 7488), 1536, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Stdconstant18, size 2304 from HyperFlash at 1063328 to (size 2304) L2 at 43544..45847 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1063328), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 43544), 2304, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving Stdconstant46, size 32768 from HyperFlash at 791712 to (size 32768) L2 at 10776..43543 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 791712), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 10776), 32768, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	return 0;
}
int lynredCNN_Destruct(int Warm)

{
	if (Warm) {
		AT_L1_FREE(0, lynred_L1_Memory, 49980);
		return 0;
	}
	AT_HYPERRAM_FREE(&HyperRam, lynred_L3_Memory, 665600);
	AT_L2_FREE(0, lynred_L2_Memory, 150000);
	AT_L1_FREE(0, lynred_L1_Memory, 49980);
	AT_HYPERFLASH_FS_CLOSE(&HyperFlash);
	return 0;
}
int lynredCNN(
		unsigned char * __restrict__ Input_1,
		signed short * __restrict__ Output_1,
		signed char * __restrict__ Output_2,
		signed char * __restrict__ Output_3)

{
	AT_HYPERFLASH_FS_CL_EVENT UchanHF0;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF1;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF2;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF3;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF4;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF5;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF6;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF7;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF8;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF9;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF10;
	AT_HYPERFLASH_FS_CL_EVENT UchanHF11;
	S1_Op_input_1_formatter(
		((unsigned char * __restrict__) Input_1), /* In */
		((signed char * __restrict__) (lynred_L2_Memory+46436)) /* Out */
	);
	S4_Conv2d_32x1x3x3_Relu(
		((signed char * __restrict__) (lynred_L2_Memory+46436)), /* In */
		((signed char * __restrict__) (lynred_L2_Memory+9792)), /* Filter */
		((signed int * __restrict__) (lynred_L2_Memory+10368)), /* Bias */
		((signed char * __restrict__) (lynred_L2_Memory+97636)), /* Out */
		((unsigned char * __restrict__) (lynred_L2_Memory+10624)), /* Scale */
		((signed char * __restrict__) (lynred_L2_Memory+10656)), /* ScaleN */
		((signed char * __restrict__) (lynred_L2_Memory+10752)) /* Infos */
	);
	S7_Conv2d_32x1x3x3_Relu(
		((signed char * __restrict__) (lynred_L2_Memory+97636)), /* In */
		((signed char * __restrict__) (lynred_L2_Memory+10080)), /* Filter */
		((signed int * __restrict__) (lynred_L2_Memory+10496)), /* Bias */
		((signed char * __restrict__) (lynred_L2_Memory+46436)), /* Out */
		((unsigned char * __restrict__) (lynred_L2_Memory+10688)), /* Scale */
		((signed char * __restrict__) (lynred_L2_Memory+10720)), /* ScaleN */
		((signed char * __restrict__) (lynred_L2_Memory+10764)) /* Infos */
	);
	/* Moving Stdconstant23, size 3456 from HyperFlash at 1047200 to (size 3456) L2 at 136036 using event 0 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1047200), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 136036), 3456, 0, &UchanHF0);
	S10_Conv2d_24x32x1x1(
		((signed char * __restrict__) (lynred_L2_Memory+46436)), /* In2 */
		((signed char * __restrict__) (lynred_L3_Flash+1084528)), /* In1 */
		((signed int * __restrict__) (lynred_L3_Flash+1105008)), /* Bias */
		((signed char * __restrict__) (lynred_L2_Memory+97636)), /* Out */
		((unsigned char * __restrict__) (lynred_L3_Flash+1106432)), /* Scale */
		((signed char * __restrict__) (lynred_L3_Flash+1106456)), /* ScaleN */
		((signed char * __restrict__) (lynred_L2_Memory+46424)) /* Infos */
	);
	/* Moving Stdconstant52, size 1296 from HyperFlash at 1080032 to (size 1296) L2 at 82148 using event 1 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1080032), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 82148), 1296, 0, &UchanHF1);
	/* Moving Stdconstant5, size 576 from HyperFlash at 1090480 to (size 576) L2 at 83444 using event 2 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1090480), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 83444), 576, 0, &UchanHF2);
	/* Moving Stdconstant24, size 4608 from HyperFlash at 1034400 to (size 4608) L2 at 92004 using event 3 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1034400), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 92004), 4608, 0, &UchanHF3);
	/* Moving Stdconstant53, size 128 from HyperFlash at 1103728 to (size 128) L2 at 96996 using event 4 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1103728), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 96996), 128, 0, &UchanHF4);
	/* Moving S19_Mul_scale, size 32 from HyperFlash at 1106048 to (size 32) L2 at 97124 using event 5 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1106048), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 97124), 32, 0, &UchanHF5);
	/* Moving S19_Mul_shift, size 32 from HyperFlash at 1106080 to (size 32) L2 at 97156 using event 6 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1106080), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 97156), 32, 0, &UchanHF6);
	/* Moving S19_Infos, size 9 from HyperFlash at 1106660 to (size 9) L2 at 97188 using event 7 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1106660), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 97188), 9, 0, &UchanHF7);
	/* Moving Stdconstant25, size 6144 from HyperFlash at 1003680 to (size 6144) L2 at 85860 using event 8 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1003680), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 85860), 6144, 0, &UchanHF8);
	/* Moving S22_Mul_scale, size 192 from HyperFlash at 1100592 to (size 192) L2 at 96612 using event 9 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1100592), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 96612), 192, 0, &UchanHF9);
	/* Moving S22_Mul_shift, size 192 from HyperFlash at 1100784 to (size 192) L2 at 96804 using event 10 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1100784), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 96804), 192, 0, &UchanHF10);
	/* Moving S22_Infos, size 9 from HyperFlash at 1106672 to (size 9) L2 at 97200 using event 11 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1106672), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 97200), 9, 0, &UchanHF11);
	/* Waiting completion of transfer of Stdconstant23 using event 0 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF0);
	S13_Conv2d_144x24x1x1_Relu(
		((signed char * __restrict__) (lynred_L2_Memory+97636)), /* In2 */
		((signed char * __restrict__) (lynred_L2_Memory+136036)), /* In1 */
		((signed int * __restrict__) (lynred_L2_Memory+45848)), /* Bias */
		((signed char * __restrict__) (lynred_L3_Memory+230400)), /* Out */
		((unsigned char * __restrict__) (lynred_L3_Flash+1102896)), /* Scale */
		((signed char * __restrict__) (lynred_L3_Flash+1103040)), /* ScaleN */
		((signed char * __restrict__) (lynred_L3_Flash+1106636)) /* Infos */
	);
	/* Waiting completion of transfer of Stdconstant52 using event 1 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1);
	/* Waiting completion of transfer of Stdconstant5 using event 2 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF2);
	S16_Conv2d_144x1x3x3_Relu(
		((signed char * __restrict__) (lynred_L3_Memory+230400)), /* In */
		((signed char * __restrict__) (lynred_L2_Memory+82148)), /* Filter */
		((signed int * __restrict__) (lynred_L2_Memory+83444)), /* Bias */
		((signed char * __restrict__) (lynred_L3_Memory+0)), /* Out */
		((unsigned char * __restrict__) (lynred_L3_Flash+1103184)), /* Scale */
		((signed char * __restrict__) (lynred_L3_Flash+1103328)), /* ScaleN */
		((signed char * __restrict__) (lynred_L3_Flash+1106648)) /* Infos */
	);
	/* Moving Stdconstant27, size 6144 from HyperFlash at 1015968 to (size 6144) L2 at 130948 using event 0 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1015968), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 130948), 6144, 0, &UchanHF0);
	/* Moving Stdconstant8, size 768 from HyperFlash at 1086832 to (size 768) L2 at 137092 using event 1 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1086832), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 137092), 768, 0, &UchanHF1);
	/* Waiting completion of transfer of Stdconstant24 using event 3 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF3);
	/* Waiting completion of transfer of Stdconstant53 using event 4 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF4);
	/* Waiting completion of transfer of S19_Mul_scale using event 5 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF5);
	/* Waiting completion of transfer of S19_Mul_shift using event 6 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF6);
	/* Waiting completion of transfer of S19_Infos using event 7 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF7);
	S19_Conv2d_32x144x1x1(
		((signed char * __restrict__) (lynred_L3_Memory+0)), /* In2 */
		((signed char * __restrict__) (lynred_L2_Memory+92004)), /* In1 */
		((signed int * __restrict__) (lynred_L2_Memory+96996)), /* Bias */
		((signed char * __restrict__) (lynred_L3_Memory+614400)), /* Out */
		((unsigned char * __restrict__) (lynred_L2_Memory+97124)), /* Scale */
		((signed char * __restrict__) (lynred_L2_Memory+97156)), /* ScaleN */
		((signed char * __restrict__) (lynred_L2_Memory+97188)) /* Infos */
	);
	/* Moving Stdconstant7, size 768 from HyperFlash at 1086064 to (size 768) L2 at 92004 using event 2 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1086064), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 92004), 768, 0, &UchanHF2);
	/* Moving S25_Mul_scale, size 192 from HyperFlash at 1100976 to (size 192) L2 at 92772 using event 3 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1100976), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 92772), 192, 0, &UchanHF3);
	/* Moving S25_Mul_shift, size 192 from HyperFlash at 1101168 to (size 192) L2 at 92964 using event 4 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1101168), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 92964), 192, 0, &UchanHF4);
	/* Moving S25_Infos, size 9 from HyperFlash at 1106684 to (size 9) L2 at 93156 using event 5 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1106684), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 93156), 9, 0, &UchanHF5);
	/* Waiting completion of transfer of Stdconstant25 using event 8 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF8);
	/* Waiting completion of transfer of S22_Mul_scale using event 9 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF9);
	/* Waiting completion of transfer of S22_Mul_shift using event 10 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF10);
	/* Waiting completion of transfer of S22_Infos using event 11 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF11);
	S22_Conv2d_192x32x1x1_Relu(
		((signed char * __restrict__) (lynred_L3_Memory+614400)), /* In2 */
		((signed char * __restrict__) (lynred_L2_Memory+85860)), /* In1 */
		((signed int * __restrict__) (lynred_L2_Memory+9024)), /* Bias */
		((signed char * __restrict__) (lynred_L3_Memory+307200)), /* Out */
		((unsigned char * __restrict__) (lynred_L2_Memory+96612)), /* Scale */
		((signed char * __restrict__) (lynred_L2_Memory+96804)), /* ScaleN */
		((signed char * __restrict__) (lynred_L2_Memory+97200)) /* Infos */
	);
	/* Moving Stdconstant26, size 6144 from HyperFlash at 1009824 to (size 6144) L2 at 82276 using event 6 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1009824), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 82276), 6144, 0, &UchanHF6);
	/* Moving Stdconstant55, size 128 from HyperFlash at 1103856 to (size 128) L2 at 88420 using event 7 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1103856), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 88420), 128, 0, &UchanHF7);
	/* Moving S28_Mul_scale, size 32 from HyperFlash at 1106112 to (size 32) L2 at 88548 using event 8 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1106112), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 88548), 32, 0, &UchanHF8);
	/* Moving S28_Mul_shift, size 32 from HyperFlash at 1106144 to (size 32) L2 at 88580 using event 9 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1106144), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 88580), 32, 0, &UchanHF9);
	/* Moving S28_Infos, size 9 from HyperFlash at 1106696 to (size 9) L2 at 88612 using event 10 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1106696), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 88612), 9, 0, &UchanHF10);
	/* Waiting completion of transfer of Stdconstant7 using event 2 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF2);
	/* Waiting completion of transfer of S25_Mul_scale using event 3 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF3);
	/* Waiting completion of transfer of S25_Mul_shift using event 4 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF4);
	/* Waiting completion of transfer of S25_Infos using event 5 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF5);
	S25_Conv2d_192x1x3x3_Relu(
		((signed char * __restrict__) (lynred_L3_Memory+307200)), /* In */
		((signed char * __restrict__) (lynred_L2_Memory+2304)), /* Filter */
		((signed int * __restrict__) (lynred_L2_Memory+92004)), /* Bias */
		((signed char * __restrict__) (lynred_L3_Memory+0)), /* Out */
		((unsigned char * __restrict__) (lynred_L2_Memory+92772)), /* Scale */
		((signed char * __restrict__) (lynred_L2_Memory+92964)), /* ScaleN */
		((signed char * __restrict__) (lynred_L2_Memory+93156)) /* Infos */
	);
	/* Waiting completion of transfer of Stdconstant26 using event 6 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF6);
	/* Waiting completion of transfer of Stdconstant55 using event 7 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF7);
	/* Waiting completion of transfer of S28_Mul_scale using event 8 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF8);
	/* Waiting completion of transfer of S28_Mul_shift using event 9 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF9);
	/* Waiting completion of transfer of S28_Infos using event 10 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF10);
	S28_Conv2d_32x192x1x1(
		((signed char * __restrict__) (lynred_L3_Memory+0)), /* In2 */
		((signed char * __restrict__) (lynred_L2_Memory+82276)), /* In1 */
		((signed int * __restrict__) (lynred_L2_Memory+88420)), /* Bias */
		((signed char * __restrict__) (lynred_L3_Memory+307200)), /* Out */
		((unsigned char * __restrict__) (lynred_L2_Memory+88548)), /* Scale */
		((signed char * __restrict__) (lynred_L2_Memory+88580)), /* ScaleN */
		((signed char * __restrict__) (lynred_L2_Memory+88612)) /* Infos */
	);
	S29_MatAdd_32x40x40(
		((signed char * __restrict__) (lynred_L3_Memory+307200)), /* In1 */
		((signed char * __restrict__) (lynred_L3_Memory+614400)), /* In2 */
		((signed char * __restrict__) (lynred_L2_Memory+46436)), /* Out */
		((signed char * __restrict__) (lynred_L3_Flash+1106708)) /* Infos */
	);
	/* Moving Stdconstant9, size 768 from HyperFlash at 1087600 to (size 768) L2 at 128356 using event 2 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1087600), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 128356), 768, 0, &UchanHF2);
	/* Waiting completion of transfer of Stdconstant27 using event 0 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF0);
	/* Waiting completion of transfer of Stdconstant8 using event 1 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1);
	S32_Conv2d_192x32x1x1_Relu(
		((signed char * __restrict__) (lynred_L2_Memory+46436)), /* In2 */
		((signed char * __restrict__) (lynred_L2_Memory+130948)), /* In1 */
		((signed int * __restrict__) (lynred_L2_Memory+137092)), /* Bias */
		((signed char * __restrict__) (lynred_L3_Memory+0)), /* Out */
		((unsigned char * __restrict__) (lynred_L3_Flash+1101360)), /* Scale */
		((signed char * __restrict__) (lynred_L3_Flash+1101552)), /* ScaleN */
		((signed char * __restrict__) (lynred_L3_Flash+1106720)) /* Infos */
	);
	/* Moving Stdconstant28, size 6144 from HyperFlash at 1022112 to (size 6144) L2 at 133476 using event 0 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1022112), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 133476), 6144, 0, &UchanHF0);
	/* Waiting completion of transfer of Stdconstant9 using event 2 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF2);
	S35_Conv2d_192x1x3x3_Relu(
		((signed char * __restrict__) (lynred_L3_Memory+0)), /* In */
		((signed char * __restrict__) (lynred_L2_Memory+4032)), /* Filter */
		((signed int * __restrict__) (lynred_L2_Memory+128356)), /* Bias */
		((signed char * __restrict__) (lynred_L3_Memory+307200)), /* Out */
		((unsigned char * __restrict__) (lynred_L3_Flash+1101744)), /* Scale */
		((signed char * __restrict__) (lynred_L3_Flash+1101936)), /* ScaleN */
		((signed char * __restrict__) (lynred_L3_Flash+1106732)) /* Infos */
	);
	/* Waiting completion of transfer of Stdconstant28 using event 0 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF0);
	S38_Conv2d_32x192x1x1(
		((signed char * __restrict__) (lynred_L3_Memory+307200)), /* In2 */
		((signed char * __restrict__) (lynred_L2_Memory+133476)), /* In1 */
		((signed int * __restrict__) (lynred_L3_Flash+1103984)), /* Bias */
		((signed char * __restrict__) (lynred_L3_Memory+51200)), /* Out */
		((unsigned char * __restrict__) (lynred_L3_Flash+1106176)), /* Scale */
		((signed char * __restrict__) (lynred_L3_Flash+1106208)), /* ScaleN */
		((signed char * __restrict__) (lynred_L3_Flash+1106744)) /* Infos */
	);
	/* Moving Stdconstant29, size 6144 from HyperFlash at 1028256 to (size 6144) L2 at 130948 using event 0 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1028256), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 130948), 6144, 0, &UchanHF0);
	/* Moving Stdconstant10, size 768 from HyperFlash at 1088368 to (size 768) L2 at 137092 using event 1 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1088368), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 137092), 768, 0, &UchanHF1);
	S39_MatAdd_32x40x40(
		((signed char * __restrict__) (lynred_L2_Memory+46436)), /* In1 */
		((signed char * __restrict__) (lynred_L3_Memory+51200)), /* In2 */
		((signed char * __restrict__) (lynred_L3_Memory+0)), /* Out */
		((signed char * __restrict__) (lynred_L3_Flash+1106756)) /* Infos */
	);
	/* Moving Boxpredictorconvolutionalboxhe, size 48 from HyperFlash at 1105872 to (size 48) L2 at 107108 using event 2 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1105872), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 107108), 48, 0, &UchanHF2);
	/* Moving S45_Mul_scale, size 12 from HyperFlash at 1106780 to (size 12) L2 at 107156 using event 3 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1106780), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 107156), 12, 0, &UchanHF3);
	/* Moving S45_Mul_shift, size 12 from HyperFlash at 1106792 to (size 12) L2 at 107168 using event 4 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1106792), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 107168), 12, 0, &UchanHF4);
	/* Moving S45_Infos, size 9 from HyperFlash at 1106804 to (size 9) L2 at 107180 using event 5 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1106804), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 107180), 9, 0, &UchanHF5);
	/* Moving Stdconstant31, size 1152 from HyperFlash at 1081328 to (size 1152) L2 at 100580 using event 6 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1081328), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 100580), 1152, 0, &UchanHF6);
	/* Waiting completion of transfer of Stdconstant29 using event 0 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF0);
	/* Waiting completion of transfer of Stdconstant10 using event 1 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1);
	S42_Conv2d_192x32x1x1_Relu(
		((signed char * __restrict__) (lynred_L3_Memory+0)), /* In2 */
		((signed char * __restrict__) (lynred_L2_Memory+130948)), /* In1 */
		((signed int * __restrict__) (lynred_L2_Memory+137092)), /* Bias */
		((signed char * __restrict__) (lynred_L3_Memory+51200)), /* Out */
		((unsigned char * __restrict__) (lynred_L3_Flash+1102128)), /* Scale */
		((signed char * __restrict__) (lynred_L3_Flash+1102320)), /* ScaleN */
		((signed char * __restrict__) (lynred_L3_Flash+1106768)) /* Infos */
	);
	/* Waiting completion of transfer of Stdconstant31 using event 6 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF6);
	S50_Conv2d_6x192x1x1_Sigmoid(
		((signed char * __restrict__) (lynred_L3_Memory+51200)), /* In2 */
		((signed char * __restrict__) (lynred_L2_Memory+100580)), /* In1 */
		((signed int * __restrict__) (lynred_L3_Flash+1106480)), /* Bias */
		((signed char * __restrict__) (lynred_L2_Memory+90980)), /* Out */
		((unsigned char * __restrict__) (lynred_L3_Flash+1107116)), /* Scale */
		((signed char * __restrict__) (lynred_L3_Flash+1107124)), /* ScaleN */
		((signed char * __restrict__) (lynred_L3_Flash+1106816)) /* Infos */
	);
	S51_Op_CONV_2D_0_17_trans_out0(
		((signed char * __restrict__) (lynred_L2_Memory+90980)), /* In */
		((signed char * __restrict__) (lynred_L3_Memory+394400)) /* Out */
	);
	/* Waiting completion of transfer of Boxpredictorconvolutionalboxhe using event 2 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF2);
	/* Waiting completion of transfer of S45_Mul_scale using event 3 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF3);
	/* Waiting completion of transfer of S45_Mul_shift using event 4 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF4);
	/* Waiting completion of transfer of S45_Infos using event 5 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF5);
	S45_Conv2d_12x192x1x1(
		((signed char * __restrict__) (lynred_L3_Memory+51200)), /* In2 */
		((signed char * __restrict__) (lynred_L2_Memory+0)), /* In1 */
		((signed int * __restrict__) (lynred_L2_Memory+107108)), /* Bias */
		((signed char * __restrict__) (lynred_L2_Memory+87908)), /* Out */
		((unsigned char * __restrict__) (lynred_L2_Memory+107156)), /* Scale */
		((signed char * __restrict__) (lynred_L2_Memory+107168)), /* ScaleN */
		((signed char * __restrict__) (lynred_L2_Memory+107180)) /* Infos */
	);
	S46_Op_CONV_2D_0_15_trans_out0(
		((signed char * __restrict__) (lynred_L2_Memory+87908)), /* In */
		((signed char * __restrict__) (lynred_L3_Memory+358400)) /* Out */
	);
	S55_Conv2d_192x1x3x3_Relu(
		((signed char * __restrict__) (lynred_L3_Memory+51200)), /* In */
		((signed char * __restrict__) (lynred_L2_Memory+5760)), /* Filter */
		((signed int * __restrict__) (lynred_L3_Flash+1089136)), /* Bias */
		((signed char * __restrict__) (lynred_L2_Memory+72036)), /* Out */
		((unsigned char * __restrict__) (lynred_L3_Flash+1102512)), /* Scale */
		((signed char * __restrict__) (lynred_L3_Flash+1102704)), /* ScaleN */
		((signed char * __restrict__) (lynred_L3_Flash+1106828)) /* Infos */
	);
	S58_Conv2d_64x192x1x1(
		((signed char * __restrict__) (lynred_L2_Memory+72036)), /* In2 */
		((signed char * __restrict__) (lynred_L3_Flash+965792)), /* In1 */
		((signed int * __restrict__) (lynred_L3_Flash+1098800)), /* Bias */
		((signed char * __restrict__) (lynred_L3_Memory+0)), /* Out */
		((unsigned char * __restrict__) (lynred_L3_Flash+1105296)), /* Scale */
		((signed char * __restrict__) (lynred_L3_Flash+1105360)), /* ScaleN */
		((signed char * __restrict__) (lynred_L3_Flash+1106840)) /* Infos */
	);
	/* Moving Stdconstant60, size 3456 from HyperFlash at 1050656 to (size 3456) L2 at 113268 using event 0 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1050656), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 113268), 3456, 0, &UchanHF0);
	/* Moving Stdconstant13, size 1536 from HyperFlash at 1072352 to (size 1536) L2 at 116724 using event 1 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1072352), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 116724), 1536, 0, &UchanHF1);
	/* Moving S64_Mul_scale, size 384 from HyperFlash at 1094000 to (size 384) L2 at 118260 using event 2 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1094000), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 118260), 384, 0, &UchanHF2);
	/* Moving S64_Mul_shift, size 384 from HyperFlash at 1094384 to (size 384) L2 at 118644 using event 3 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1094384), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 118644), 384, 0, &UchanHF3);
	/* Moving Stdconstant14, size 1536 from HyperFlash at 1073888 to (size 1536) L2 at 138868 using event 4 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1073888), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 138868), 1536, 0, &UchanHF4);
	/* Moving S71_Mul_scale, size 384 from HyperFlash at 1094768 to (size 384) L2 at 140404 using event 5 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1094768), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 140404), 384, 0, &UchanHF5);
	/* Moving S71_Mul_shift, size 384 from HyperFlash at 1095152 to (size 384) L2 at 140788 using event 6 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1095152), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 140788), 384, 0, &UchanHF6);
	S61_Conv2d_384x64x1x1_Relu(
		((signed char * __restrict__) (lynred_L3_Memory+0)), /* In2 */
		((signed char * __restrict__) (lynred_L3_Flash+824480)), /* In1 */
		((signed int * __restrict__) (lynred_L2_Memory+7488)), /* Bias */
		((signed char * __restrict__) (lynred_L3_Memory+25600)), /* Out */
		((unsigned char * __restrict__) (lynred_L3_Flash+1093232)), /* Scale */
		((signed char * __restrict__) (lynred_L3_Flash+1093616)), /* ScaleN */
		((signed char * __restrict__) (lynred_L3_Flash+1106852)) /* Infos */
	);
	/* Moving Stdconstant34, size 24576 from HyperFlash at 849056 to (size 24576) L2 at 88692 using event 7 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 849056), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 88692), 24576, 0, &UchanHF7);
	/* Waiting completion of transfer of Stdconstant60 using event 0 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF0);
	/* Waiting completion of transfer of Stdconstant13 using event 1 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1);
	/* Waiting completion of transfer of S64_Mul_scale using event 2 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF2);
	/* Waiting completion of transfer of S64_Mul_shift using event 3 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF3);
	S64_Conv2d_384x1x3x3_Relu(
		((signed char * __restrict__) (lynred_L3_Memory+25600)), /* In */
		((signed char * __restrict__) (lynred_L2_Memory+113268)), /* Filter */
		((signed int * __restrict__) (lynred_L2_Memory+116724)), /* Bias */
		((signed char * __restrict__) (lynred_L3_Memory+179200)), /* Out */
		((unsigned char * __restrict__) (lynred_L2_Memory+118260)), /* Scale */
		((signed char * __restrict__) (lynred_L2_Memory+118644)), /* ScaleN */
		((signed char * __restrict__) (lynred_L3_Flash+1106864)) /* Infos */
	);
	/* Moving Stdconstant35, size 24576 from HyperFlash at 873632 to (size 24576) L2 at 114292 using event 0 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 873632), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 114292), 24576, 0, &UchanHF0);
	/* Waiting completion of transfer of Stdconstant34 using event 7 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF7);
	S67_Conv2d_64x384x1x1(
		((signed char * __restrict__) (lynred_L3_Memory+179200)), /* In2 */
		((signed char * __restrict__) (lynred_L2_Memory+88692)), /* In1 */
		((signed int * __restrict__) (lynred_L3_Flash+1099056)), /* Bias */
		((signed char * __restrict__) (lynred_L2_Memory+63092)), /* Out */
		((unsigned char * __restrict__) (lynred_L3_Flash+1105424)), /* Scale */
		((signed char * __restrict__) (lynred_L3_Flash+1105488)), /* ScaleN */
		((signed char * __restrict__) (lynred_L3_Flash+1106876)) /* Infos */
	);
	S68_MatAdd_64x20x20(
		((signed char * __restrict__) (lynred_L3_Memory+0)), /* In1 */
		((signed char * __restrict__) (lynred_L2_Memory+63092)), /* In2 */
		((signed char * __restrict__) (lynred_L2_Memory+88692)), /* Out */
		((signed char * __restrict__) (lynred_L3_Flash+1106888)) /* Infos */
	);
	/* Moving Stdconstant62, size 3456 from HyperFlash at 1054112 to (size 3456) L2 at 67940 using event 1 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1054112), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 67940), 3456, 0, &UchanHF1);
	/* Moving Stdconstant15, size 1536 from HyperFlash at 1075424 to (size 1536) L2 at 71396 using event 2 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1075424), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 71396), 1536, 0, &UchanHF2);
	/* Moving S74_Mul_scale, size 384 from HyperFlash at 1095536 to (size 384) L2 at 72932 using event 3 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1095536), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 72932), 384, 0, &UchanHF3);
	/* Moving S74_Mul_shift, size 384 from HyperFlash at 1095920 to (size 384) L2 at 73316 using event 7 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1095920), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 73316), 384, 0, &UchanHF7);
	/* Waiting completion of transfer of Stdconstant35 using event 0 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF0);
	/* Waiting completion of transfer of Stdconstant14 using event 4 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF4);
	/* Waiting completion of transfer of S71_Mul_scale using event 5 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF5);
	/* Waiting completion of transfer of S71_Mul_shift using event 6 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF6);
	S71_Conv2d_384x64x1x1_Relu(
		((signed char * __restrict__) (lynred_L2_Memory+88692)), /* In2 */
		((signed char * __restrict__) (lynred_L2_Memory+114292)), /* In1 */
		((signed int * __restrict__) (lynred_L2_Memory+138868)), /* Bias */
		((signed char * __restrict__) (lynred_L3_Memory+0)), /* Out */
		((unsigned char * __restrict__) (lynred_L2_Memory+140404)), /* Scale */
		((signed char * __restrict__) (lynred_L2_Memory+140788)), /* ScaleN */
		((signed char * __restrict__) (lynred_L3_Flash+1106900)) /* Infos */
	);
	/* Moving Stdconstant36, size 24576 from HyperFlash at 898208 to (size 24576) L2 at 114292 using event 0 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 898208), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 114292), 24576, 0, &UchanHF0);
	/* Waiting completion of transfer of Stdconstant62 using event 1 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1);
	/* Waiting completion of transfer of Stdconstant15 using event 2 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF2);
	/* Waiting completion of transfer of S74_Mul_scale using event 3 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF3);
	/* Waiting completion of transfer of S74_Mul_shift using event 7 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF7);
	S74_Conv2d_384x1x3x3_Relu(
		((signed char * __restrict__) (lynred_L3_Memory+0)), /* In */
		((signed char * __restrict__) (lynred_L2_Memory+67940)), /* Filter */
		((signed int * __restrict__) (lynred_L2_Memory+71396)), /* Bias */
		((signed char * __restrict__) (lynred_L3_Memory+153600)), /* Out */
		((unsigned char * __restrict__) (lynred_L2_Memory+72932)), /* Scale */
		((signed char * __restrict__) (lynred_L2_Memory+73316)), /* ScaleN */
		((signed char * __restrict__) (lynred_L3_Flash+1106912)) /* Infos */
	);
	/* Waiting completion of transfer of Stdconstant36 using event 0 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF0);
	S77_Conv2d_64x384x1x1(
		((signed char * __restrict__) (lynred_L3_Memory+153600)), /* In2 */
		((signed char * __restrict__) (lynred_L2_Memory+114292)), /* In1 */
		((signed int * __restrict__) (lynred_L3_Flash+1099312)), /* Bias */
		((signed char * __restrict__) (lynred_L2_Memory+61796)), /* Out */
		((unsigned char * __restrict__) (lynred_L3_Flash+1105552)), /* Scale */
		((signed char * __restrict__) (lynred_L3_Flash+1105616)), /* ScaleN */
		((signed char * __restrict__) (lynred_L3_Flash+1106924)) /* Infos */
	);
	S78_MatAdd_64x20x20(
		((signed char * __restrict__) (lynred_L2_Memory+61796)), /* In1 */
		((signed char * __restrict__) (lynred_L2_Memory+88692)), /* In2 */
		((signed char * __restrict__) (lynred_L2_Memory+114292)), /* Out */
		((signed char * __restrict__) (lynred_L3_Flash+1106936)) /* Infos */
	);
	/* Moving Stdconstant64, size 3456 from HyperFlash at 1057568 to (size 3456) L2 at 88420 using event 0 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1057568), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 88420), 3456, 0, &UchanHF0);
	S81_Conv2d_384x64x1x1_Relu(
		((signed char * __restrict__) (lynred_L2_Memory+114292)), /* In2 */
		((signed char * __restrict__) (lynred_L3_Flash+922784)), /* In1 */
		((signed int * __restrict__) (lynred_L3_Flash+1076960)), /* Bias */
		((signed char * __restrict__) (lynred_L3_Memory+0)), /* Out */
		((unsigned char * __restrict__) (lynred_L3_Flash+1096304)), /* Scale */
		((signed char * __restrict__) (lynred_L3_Flash+1096688)), /* ScaleN */
		((signed char * __restrict__) (lynred_L3_Flash+1106948)) /* Infos */
	);
	/* Moving Stdconstant38, size 36864 from HyperFlash at 718848 to (size 36864) L2 at 100196 using event 1 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 718848), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 100196), 36864, 0, &UchanHF1);
	/* Waiting completion of transfer of Stdconstant64 using event 0 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF0);
	S84_Conv2d_384x1x3x3_Relu(
		((signed char * __restrict__) (lynred_L3_Memory+0)), /* In */
		((signed char * __restrict__) (lynred_L2_Memory+88420)), /* Filter */
		((signed int * __restrict__) (lynred_L3_Flash+1078496)), /* Bias */
		((signed char * __restrict__) (lynred_L3_Memory+153600)), /* Out */
		((unsigned char * __restrict__) (lynred_L3_Flash+1097072)), /* Scale */
		((signed char * __restrict__) (lynred_L3_Flash+1097456)), /* ScaleN */
		((signed char * __restrict__) (lynred_L3_Flash+1106960)) /* Infos */
	);
	/* Waiting completion of transfer of Stdconstant38 using event 1 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1);
	S87_Conv2d_96x384x1x1(
		((signed char * __restrict__) (lynred_L3_Memory+153600)), /* In2 */
		((signed char * __restrict__) (lynred_L2_Memory+100196)), /* In1 */
		((signed int * __restrict__) (lynred_L3_Flash+1097840)), /* Bias */
		((signed char * __restrict__) (lynred_L2_Memory+61796)), /* Out */
		((unsigned char * __restrict__) (lynred_L3_Flash+1105104)), /* Scale */
		((signed char * __restrict__) (lynred_L3_Flash+1105200)), /* ScaleN */
		((signed char * __restrict__) (lynred_L3_Flash+1106972)) /* Infos */
	);
	/* Moving Stdconstant41, size 9216 from HyperFlash at 978080 to (size 9216) L2 at 132196 using event 0 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 978080), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 132196), 9216, 0, &UchanHF0);
	S90_Conv2d_576x96x1x1_Relu(
		((signed char * __restrict__) (lynred_L2_Memory+61796)), /* In2 */
		((signed char * __restrict__) (lynred_L3_Flash+663552)), /* In1 */
		((signed int * __restrict__) (lynred_L2_Memory+43544)), /* Bias */
		((signed char * __restrict__) (lynred_L3_Memory+0)), /* Out */
		((unsigned char * __restrict__) (lynred_L3_Flash+1091056)), /* Scale */
		((signed char * __restrict__) (lynred_L3_Flash+1091632)), /* ScaleN */
		((signed char * __restrict__) (lynred_L3_Flash+1106984)) /* Infos */
	);
	/* Waiting completion of transfer of Stdconstant41 using event 0 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF0);
	S98_Conv2d_16x576x1x1_Sigmoid(
		((signed char * __restrict__) (lynred_L3_Memory+0)), /* In2 */
		((signed char * __restrict__) (lynred_L2_Memory+132196)), /* In1 */
		((signed int * __restrict__) (lynred_L3_Flash+1105680)), /* Bias */
		((signed char * __restrict__) (lynred_L2_Memory+74084)), /* Out */
		((unsigned char * __restrict__) (lynred_L3_Flash+1106504)), /* Scale */
		((signed char * __restrict__) (lynred_L3_Flash+1106520)), /* ScaleN */
		((signed char * __restrict__) (lynred_L3_Flash+1107008)) /* Infos */
	);
	/* Moving Stdconstant40, size 18432 from HyperFlash at 947360 to (size 18432) L2 at 80484 using event 0 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 947360), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 80484), 18432, 0, &UchanHF0);
	S99_Op_CONV_2D_0_35_trans_out0(
		((signed char * __restrict__) (lynred_L2_Memory+74084)), /* In */
		((signed char * __restrict__) ((lynred_L3_Memory+394400) + 9600)) /* Out */
	);
	/* Waiting completion of transfer of Stdconstant40 using event 0 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF0);
	S93_Conv2d_32x576x1x1(
		((signed char * __restrict__) (lynred_L3_Memory+0)), /* In2 */
		((signed char * __restrict__) (lynred_L2_Memory+80484)), /* In1 */
		((signed int * __restrict__) (lynred_L3_Flash+1104112)), /* Bias */
		((signed char * __restrict__) (lynred_L2_Memory+60260)), /* Out */
		((unsigned char * __restrict__) (lynred_L3_Flash+1106240)), /* Scale */
		((signed char * __restrict__) (lynred_L3_Flash+1106272)), /* ScaleN */
		((signed char * __restrict__) (lynred_L3_Flash+1106996)) /* Infos */
	);
	S94_Op_CONV_2D_0_33_trans_out0(
		((signed char * __restrict__) (lynred_L2_Memory+60260)), /* In */
		((signed char * __restrict__) ((lynred_L3_Memory+358400) + 19200)) /* Out */
	);
	S103_Conv2d_128x576x1x1_Relu(
		((signed char * __restrict__) (lynred_L3_Memory+0)), /* In2 */
		((signed char * __restrict__) (lynred_L3_Flash+589824)), /* In1 */
		((signed int * __restrict__) (lynred_L3_Flash+1092208)), /* Bias */
		((signed char * __restrict__) (lynred_L2_Memory+46436)), /* Out */
		((unsigned char * __restrict__) (lynred_L3_Flash+1104240)), /* Scale */
		((signed char * __restrict__) (lynred_L3_Flash+1104368)), /* ScaleN */
		((signed char * __restrict__) (lynred_L3_Flash+1107020)) /* Infos */
	);
	/* Moving Stdconstant45, size 4096 from HyperFlash at 1039008 to (size 4096) L2 at 127844 using event 0 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1039008), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 127844), 4096, 0, &UchanHF0);
	S106_Conv2d_256x128x3x3_Relu(
		((signed char * __restrict__) (lynred_L2_Memory+46436)), /* In */
		((signed char * __restrict__) (lynred_L3_Flash+0)), /* Filter */
		((signed int * __restrict__) (lynred_L3_Flash+1082480)), /* Bias */
		((signed char * __restrict__) (lynred_L2_Memory+97636)), /* Out */
		((unsigned char * __restrict__) (lynred_L3_Flash+1099568)), /* Scale */
		((signed char * __restrict__) (lynred_L3_Flash+1099824)), /* ScaleN */
		((signed char * __restrict__) (lynred_L3_Flash+1107032)) /* Infos */
	);
	/* Moving Stdconstant44, size 8192 from HyperFlash at 987296 to (size 8192) L2 at 52836 using event 1 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 987296), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 52836), 8192, 0, &UchanHF1);
	/* Waiting completion of transfer of Stdconstant45 using event 0 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF0);
	S114_Conv2d_16x256x1x1_Sigmoid(
		((signed char * __restrict__) (lynred_L2_Memory+97636)), /* In2 */
		((signed char * __restrict__) (lynred_L2_Memory+127844)), /* In1 */
		((signed int * __restrict__) (lynred_L3_Flash+1105744)), /* Bias */
		((signed char * __restrict__) (lynred_L2_Memory+48036)), /* Out */
		((unsigned char * __restrict__) (lynred_L3_Flash+1106536)), /* Scale */
		((signed char * __restrict__) (lynred_L3_Flash+1106552)), /* ScaleN */
		((signed char * __restrict__) (lynred_L3_Flash+1107056)) /* Infos */
	);
	/* Moving Stdconstant49, size 4096 from HyperFlash at 1043104 to (size 4096) L2 at 80612 using event 0 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1043104), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 80612), 4096, 0, &UchanHF0);
	/* Moving Boxpredictorconvolutionalclass_20f59186, size 64 from HyperFlash at 1105808 to (size 64) L2 at 86884 using event 2 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1105808), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 86884), 64, 0, &UchanHF2);
	/* Moving S132_Mul_scale, size 16 from HyperFlash at 1106568 to (size 16) L2 at 86948 using event 3 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1106568), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 86948), 16, 0, &UchanHF3);
	/* Moving S132_Mul_shift, size 16 from HyperFlash at 1106584 to (size 16) L2 at 86964 using event 4 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1106584), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 86964), 16, 0, &UchanHF4);
	/* Moving S132_Infos, size 9 from HyperFlash at 1107104 to (size 9) L2 at 86992 using event 5 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1107104), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 86992), 9, 0, &UchanHF5);
	S115_Op_CONV_2D_0_41_trans_out0(
		((signed char * __restrict__) (lynred_L2_Memory+48036)), /* In */
		((signed char * __restrict__) ((lynred_L3_Memory+394400) + 16000)) /* Out */
	);
	/* Waiting completion of transfer of Stdconstant44 using event 1 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1);
	S109_Conv2d_32x256x1x1(
		((signed char * __restrict__) (lynred_L2_Memory+97636)), /* In2 */
		((signed char * __restrict__) (lynred_L2_Memory+52836)), /* In1 */
		((signed int * __restrict__) (lynred_L3_Flash+1104496)), /* Bias */
		((signed char * __restrict__) (lynred_L2_Memory+49636)), /* Out */
		((unsigned char * __restrict__) (lynred_L3_Flash+1106304)), /* Scale */
		((signed char * __restrict__) (lynred_L3_Flash+1106336)), /* ScaleN */
		((signed char * __restrict__) (lynred_L3_Flash+1107044)) /* Infos */
	);
	S110_Op_CONV_2D_0_39_trans_out0(
		((signed char * __restrict__) (lynred_L2_Memory+49636)), /* In */
		((signed char * __restrict__) ((lynred_L3_Memory+358400) + 32000)) /* Out */
	);
	S119_Conv2d_128x256x1x1_Relu(
		((signed char * __restrict__) (lynred_L2_Memory+97636)), /* In2 */
		((signed char * __restrict__) (lynred_L2_Memory+10776)), /* In1 */
		((signed int * __restrict__) (lynred_L3_Flash+1092720)), /* Bias */
		((signed char * __restrict__) (lynred_L2_Memory+46436)), /* Out */
		((unsigned char * __restrict__) (lynred_L3_Flash+1104624)), /* Scale */
		((signed char * __restrict__) (lynred_L3_Flash+1104752)), /* ScaleN */
		((signed char * __restrict__) (lynred_L3_Flash+1107068)) /* Infos */
	);
	/* Moving S137_Ssd_scales, size 8 from HyperFlash at 1107132 to (size 8) L2 at 92676 using event 1 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1107132), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 92676), 8, 0, &UchanHF1);
	/* Moving S137_Ssd_norms, size 8 from HyperFlash at 1107140 to (size 8) L2 at 92684 using event 6 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1107140), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 92684), 8, 0, &UchanHF6);
	S122_Conv2d_256x128x3x3_Relu(
		((signed char * __restrict__) (lynred_L2_Memory+46436)), /* In */
		((signed char * __restrict__) (lynred_L3_Flash+294912)), /* Filter */
		((signed int * __restrict__) (lynred_L3_Flash+1083504)), /* Bias */
		((signed char * __restrict__) (lynred_L2_Memory+59236)), /* Out */
		((unsigned char * __restrict__) (lynred_L3_Flash+1100080)), /* Scale */
		((signed char * __restrict__) (lynred_L3_Flash+1100336)), /* ScaleN */
		((signed char * __restrict__) (lynred_L3_Flash+1107080)) /* Infos */
	);
	/* Moving Stdconstant48, size 8192 from HyperFlash at 995488 to (size 8192) L2 at 47236 using event 7 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 995488), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 47236), 8192, 0, &UchanHF7);
	/* Moving Boxpredictorconvolutionalboxhe_db4937ca, size 128 from HyperFlash at 1104880 to (size 128) L2 at 55428 using event 8 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1104880), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 55428), 128, 0, &UchanHF8);
	/* Moving S125_Mul_scale, size 32 from HyperFlash at 1106368 to (size 32) L2 at 55556 using event 9 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1106368), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 55556), 32, 0, &UchanHF9);
	/* Moving S125_Mul_shift, size 32 from HyperFlash at 1106400 to (size 32) L2 at 55588 using event 10 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1106400), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 55588), 32, 0, &UchanHF10);
	/* Moving S125_Infos, size 9 from HyperFlash at 1107092 to (size 9) L2 at 55620 using event 11 */
	AT_HYPERFLASH_FS_CL_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) lynred_L3_Flash + 1107092), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) lynred_L2_Memory + 55620), 9, 0, &UchanHF11);
	/* Waiting completion of transfer of Stdconstant49 using event 0 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF0);
	/* Waiting completion of transfer of Boxpredictorconvolutionalclass_20f59186 using event 2 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF2);
	/* Waiting completion of transfer of S132_Mul_scale using event 3 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF3);
	/* Waiting completion of transfer of S132_Mul_shift using event 4 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF4);
	/* Waiting completion of transfer of S132_Infos using event 5 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF5);
	S132_Conv2d_16x256x1x1_Sigmoid(
		((signed char * __restrict__) (lynred_L2_Memory+59236)), /* In2 */
		((signed char * __restrict__) (lynred_L2_Memory+80612)), /* In1 */
		((signed int * __restrict__) (lynred_L2_Memory+86884)), /* Bias */
		((signed char * __restrict__) (lynred_L2_Memory+46436)), /* Out */
		((unsigned char * __restrict__) (lynred_L2_Memory+86948)), /* Scale */
		((signed char * __restrict__) (lynred_L2_Memory+86964)), /* ScaleN */
		((signed char * __restrict__) (lynred_L2_Memory+86992)) /* Infos */
	);
	S133_Op_CONV_2D_0_49_trans_out0(
		((signed char * __restrict__) (lynred_L2_Memory+46436)), /* In */
		((signed char * __restrict__) ((lynred_L3_Memory+394400) + 17600)) /* Out */
	);
	/* Waiting completion of transfer of Stdconstant48 using event 7 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF7);
	/* Waiting completion of transfer of Boxpredictorconvolutionalboxhe_db4937ca using event 8 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF8);
	/* Waiting completion of transfer of S125_Mul_scale using event 9 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF9);
	/* Waiting completion of transfer of S125_Mul_shift using event 10 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF10);
	/* Waiting completion of transfer of S125_Infos using event 11 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF11);
	S125_Conv2d_32x256x1x1(
		((signed char * __restrict__) (lynred_L2_Memory+59236)), /* In2 */
		((signed char * __restrict__) (lynred_L2_Memory+47236)), /* In1 */
		((signed int * __restrict__) (lynred_L2_Memory+55428)), /* Bias */
		((signed char * __restrict__) (lynred_L2_Memory+46436)), /* Out */
		((unsigned char * __restrict__) (lynred_L2_Memory+55556)), /* Scale */
		((signed char * __restrict__) (lynred_L2_Memory+55588)), /* ScaleN */
		((signed char * __restrict__) (lynred_L2_Memory+55620)) /* Infos */
	);
	S126_Op_CONV_2D_0_45_trans_out0(
		((signed char * __restrict__) (lynred_L2_Memory+46436)), /* In */
		((signed char * __restrict__) ((lynred_L3_Memory+358400) + 35200)) /* Out */
	);
	/* Waiting completion of transfer of S137_Ssd_scales using event 1 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF1);
	/* Waiting completion of transfer of S137_Ssd_norms using event 6 */
	AT_HYPERFLASH_FS_CL_WAIT(&HyperFlash, &UchanHF6);
	S137_Op_CUSTOM_0_53(
		((signed char * __restrict__) (lynred_L3_Memory+358400)), /* boxes_in */
		((signed char * __restrict__) (lynred_L3_Memory+394400)), /* classes_in */
		((signed char * __restrict__) (lynred_L3_Flash+755712)), /* anchors_in */
		((signed short * __restrict__) Output_1), /* bbox_out */
		((signed char * __restrict__) Output_2), /* class_out */
		((signed char * __restrict__) Output_3), /* scores_out */
		((unsigned char * __restrict__) (lynred_L2_Memory+92676)), /* in_scales */
		((signed char * __restrict__) (lynred_L2_Memory+92684)) /* in_norms */
	);
	return 0;
}
