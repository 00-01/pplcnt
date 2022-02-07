#include <stdint.h>
#include <stdio.h>
#include "AutoTilerLib.h"
#include "CNN_Generators_SQ8.h"

#include "SSD_Generators.h"
#include "CNN_Copy_Generators.h"





void lynredModel(unsigned int L1Memory, unsigned int L2Memory, unsigned int L3Memory, unsigned int L3Flash)
{
    KernelOper_T Cop = KOP_CONV;

    // SetKernelOpts(KER_OPT_NONE, KER_OPT_BUFFER_PROMOTE);
    SetSymbolDynamics();

    SetUsedFilesNames(0, 3, "CNN_BasicKernels_SQ8.h", "lynred.h", "SSD_BasicKernels.h");
    SetGeneratedFilesNames("lynredKernels.c", "lynredKernels.h");
    AT_SetGraphCtrl(AT_GRAPH_CONST_EXEC_FROM_FLASH, AT_OPT_ON);
    AT_SetGraphCtrl(AT_GRAPH_WARM_CONSTRUCT, AT_OPT_ON);

    SetMemoryDeviceInfos(4,
        AT_MEM_L1, L1Memory, "lynred_L1_Memory", 0, 0,
        AT_MEM_L2, L2Memory, "lynred_L2_Memory", 0, 0,
        AT_MEM_L3_HRAM, L3Memory, "lynred_L3_Memory", 0, 1,
        AT_MEM_L3_HFLASH, L3Flash, "lynred_L3_Flash", "lynred_L3_Flash_Const.dat", 0
    );

    LoadCNN_SQ8_Library();
    LoadSSDLibrary();
    LoadCNN_Copy_Library();


    // generator for input_1_formatter
    CNN_Norm("S1_Op_input_1_formatter", 80, 80, 1, KOP_NORM_BW);
    // generator for CONV_2D_0_0_fusion
    CNN_GenControl_T gen_ctrl_S4_Conv2d_32x1x3x3_Relu;
    CNN_InitGenCtrl(&gen_ctrl_S4_Conv2d_32x1x3x3_Relu);
    CNN_SetGenCtrl(&gen_ctrl_S4_Conv2d_32x1x3x3_Relu, "PADTYPE", AT_OPT_VAL(1));
    CNN_ConvolutionPoolAct_SQ8("S4_Conv2d_32x1x3x3_Relu", &gen_ctrl_S4_Conv2d_32x1x3x3_Relu, 4, 1, 1, 32, 80, 80,
        KOP_CONV, 3, 3, 1, 1, 2, 2, 1,
        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
        KOP_RELU);
    // generator for DEPTHWISE_CONV_2D_0_1_fusion
    CNN_ConvolutionPoolAct_SQ8("S7_Conv2d_32x1x3x3_Relu", 0, 4, 1, 32, 32, 40, 40,
        KOP_CONV_DW, 3, 3, 1, 1, 1, 1, 1,
        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
        KOP_RELU);
    // generator for CONV_2D_0_2
    CNN_GenControl_T gen_ctrl_S10_Conv2d_24x32x1x1;
    CNN_InitGenCtrl(&gen_ctrl_S10_Conv2d_24x32x1x1);
    CNN_SetGenCtrl(&gen_ctrl_S10_Conv2d_24x32x1x1, "ENABLEIM2COL", AT_OPT_VAL(1));
    CNN_ConvolutionPoolAct_SQ8("S10_Conv2d_24x32x1x1", &gen_ctrl_S10_Conv2d_24x32x1x1, 4, 1, 32, 24, 40, 40,
        KOP_CONV, 1, 1, 1, 1, 1, 1, 0,
        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
        KOP_NONE);
    // generator for CONV_2D_0_3_fusion
    CNN_GenControl_T gen_ctrl_S13_Conv2d_144x24x1x1_Relu;
    CNN_InitGenCtrl(&gen_ctrl_S13_Conv2d_144x24x1x1_Relu);
    CNN_SetGenCtrl(&gen_ctrl_S13_Conv2d_144x24x1x1_Relu, "ENABLEIM2COL", AT_OPT_VAL(1));
    CNN_ConvolutionPoolAct_SQ8("S13_Conv2d_144x24x1x1_Relu", &gen_ctrl_S13_Conv2d_144x24x1x1_Relu, 4, 1, 24, 144, 40, 40,
        KOP_CONV, 1, 1, 1, 1, 1, 1, 0,
        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
        KOP_RELU);
    // generator for DEPTHWISE_CONV_2D_0_4_fusion
    CNN_ConvolutionPoolAct_SQ8("S16_Conv2d_144x1x3x3_Relu", 0, 4, 1, 144, 144, 40, 40,
        KOP_CONV_DW, 3, 3, 1, 1, 1, 1, 1,
        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
        KOP_RELU);
    // generator for CONV_2D_0_5
    CNN_GenControl_T gen_ctrl_S19_Conv2d_32x144x1x1;
    CNN_InitGenCtrl(&gen_ctrl_S19_Conv2d_32x144x1x1);
    CNN_SetGenCtrl(&gen_ctrl_S19_Conv2d_32x144x1x1, "ENABLEIM2COL", AT_OPT_VAL(1));
    CNN_ConvolutionPoolAct_SQ8("S19_Conv2d_32x144x1x1", &gen_ctrl_S19_Conv2d_32x144x1x1, 4, 1, 144, 32, 40, 40,
        KOP_CONV, 1, 1, 1, 1, 1, 1, 0,
        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
        KOP_NONE);
    // generator for CONV_2D_0_6_fusion
    CNN_GenControl_T gen_ctrl_S22_Conv2d_192x32x1x1_Relu;
    CNN_InitGenCtrl(&gen_ctrl_S22_Conv2d_192x32x1x1_Relu);
    CNN_SetGenCtrl(&gen_ctrl_S22_Conv2d_192x32x1x1_Relu, "ENABLEIM2COL", AT_OPT_VAL(1));
    CNN_ConvolutionPoolAct_SQ8("S22_Conv2d_192x32x1x1_Relu", &gen_ctrl_S22_Conv2d_192x32x1x1_Relu, 4, 1, 32, 192, 40, 40,
        KOP_CONV, 1, 1, 1, 1, 1, 1, 0,
        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
        KOP_RELU);
    // generator for DEPTHWISE_CONV_2D_0_7_fusion
    CNN_ConvolutionPoolAct_SQ8("S25_Conv2d_192x1x3x3_Relu", 0, 4, 1, 192, 192, 40, 40,
        KOP_CONV_DW, 3, 3, 1, 1, 1, 1, 1,
        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
        KOP_RELU);
    // generator for CONV_2D_0_8
    CNN_GenControl_T gen_ctrl_S28_Conv2d_32x192x1x1;
    CNN_InitGenCtrl(&gen_ctrl_S28_Conv2d_32x192x1x1);
    CNN_SetGenCtrl(&gen_ctrl_S28_Conv2d_32x192x1x1, "ENABLEIM2COL", AT_OPT_VAL(1));
    CNN_ConvolutionPoolAct_SQ8("S28_Conv2d_32x192x1x1", &gen_ctrl_S28_Conv2d_32x192x1x1, 4, 1, 192, 32, 40, 40,
        KOP_CONV, 1, 1, 1, 1, 1, 1, 0,
        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
        KOP_NONE);
    
    // generator for ADD_0_9
    CNN_MatAddAct_SQ8("S29_MatAdd_32x40x40", 0, 32, 40, 40, KOP_MATADD, KOP_NONE);
    
    // generator for CONV_2D_0_10_fusion
    CNN_GenControl_T gen_ctrl_S32_Conv2d_192x32x1x1_Relu;
    CNN_InitGenCtrl(&gen_ctrl_S32_Conv2d_192x32x1x1_Relu);
    CNN_SetGenCtrl(&gen_ctrl_S32_Conv2d_192x32x1x1_Relu, "ENABLEIM2COL", AT_OPT_VAL(1));
    CNN_ConvolutionPoolAct_SQ8("S32_Conv2d_192x32x1x1_Relu", &gen_ctrl_S32_Conv2d_192x32x1x1_Relu, 4, 1, 32, 192, 40, 40,
        KOP_CONV, 1, 1, 1, 1, 1, 1, 0,
        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
        KOP_RELU);
    // generator for DEPTHWISE_CONV_2D_0_11_fusion
    CNN_ConvolutionPoolAct_SQ8("S35_Conv2d_192x1x3x3_Relu", 0, 4, 1, 192, 192, 40, 40,
        KOP_CONV_DW, 3, 3, 1, 1, 1, 1, 1,
        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
        KOP_RELU);
    // generator for CONV_2D_0_12
    CNN_GenControl_T gen_ctrl_S38_Conv2d_32x192x1x1;
    CNN_InitGenCtrl(&gen_ctrl_S38_Conv2d_32x192x1x1);
    CNN_SetGenCtrl(&gen_ctrl_S38_Conv2d_32x192x1x1, "ENABLEIM2COL", AT_OPT_VAL(1));
    CNN_ConvolutionPoolAct_SQ8("S38_Conv2d_32x192x1x1", &gen_ctrl_S38_Conv2d_32x192x1x1, 4, 1, 192, 32, 40, 40,
        KOP_CONV, 1, 1, 1, 1, 1, 1, 0,
        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
        KOP_NONE);
    
    // generator for ADD_0_13
    CNN_MatAddAct_SQ8("S39_MatAdd_32x40x40", 0, 32, 40, 40, KOP_MATADD, KOP_NONE);
    
    // generator for CONV_2D_0_14_fusion
    CNN_GenControl_T gen_ctrl_S42_Conv2d_192x32x1x1_Relu;
    CNN_InitGenCtrl(&gen_ctrl_S42_Conv2d_192x32x1x1_Relu);
    CNN_SetGenCtrl(&gen_ctrl_S42_Conv2d_192x32x1x1_Relu, "ENABLEIM2COL", AT_OPT_VAL(1));
    CNN_ConvolutionPoolAct_SQ8("S42_Conv2d_192x32x1x1_Relu", &gen_ctrl_S42_Conv2d_192x32x1x1_Relu, 4, 1, 32, 192, 40, 40,
        KOP_CONV, 1, 1, 1, 1, 1, 1, 0,
        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
        KOP_RELU);
    // generator for CONV_2D_0_15
    CNN_GenControl_T gen_ctrl_S45_Conv2d_12x192x1x1;
    CNN_InitGenCtrl(&gen_ctrl_S45_Conv2d_12x192x1x1);
    CNN_SetGenCtrl(&gen_ctrl_S45_Conv2d_12x192x1x1, "ENABLEIM2COL", AT_OPT_VAL(1));
    CNN_ConvolutionPoolAct_SQ8("S45_Conv2d_12x192x1x1", &gen_ctrl_S45_Conv2d_12x192x1x1, 4, 1, 192, 12, 40, 40,
        KOP_CONV, 1, 1, 1, 1, 1, 1, 0,
        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
        KOP_NONE);
    // generator for CONV_2D_0_15_trans_out0
    // transpose from 12x40x40 to 40x40x12 ((1, 2, 0))
    CNN_3DTensorPermute("S46_Op_CONV_2D_0_15_trans_out0", 0, 1, 12, 40, 40, KOP_MATPERM_CHW2HWC);
    // generator for CONV_2D_0_17_fusion
    CNN_GenControl_T gen_ctrl_S50_Conv2d_6x192x1x1_Sigmoid;
    CNN_InitGenCtrl(&gen_ctrl_S50_Conv2d_6x192x1x1_Sigmoid);
    CNN_SetGenCtrl(&gen_ctrl_S50_Conv2d_6x192x1x1_Sigmoid, "ENABLEIM2COL", AT_OPT_VAL(1));
    CNN_ConvolutionPoolAct_SQ8("S50_Conv2d_6x192x1x1_Sigmoid", &gen_ctrl_S50_Conv2d_6x192x1x1_Sigmoid, 4, 1, 192, 6, 40, 40,
        KOP_CONV, 1, 1, 1, 1, 1, 1, 0,
        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
        KOP_SIGMOID);
    // generator for CONV_2D_0_17_trans_out0
    // transpose from 6x40x40 to 40x40x6 ((1, 2, 0))
    CNN_3DTensorPermute("S51_Op_CONV_2D_0_17_trans_out0", 0, 1, 6, 40, 40, KOP_MATPERM_CHW2HWC);
    // generator for DEPTHWISE_CONV_2D_0_19_fusion
    CNN_GenControl_T gen_ctrl_S55_Conv2d_192x1x3x3_Relu;
    CNN_InitGenCtrl(&gen_ctrl_S55_Conv2d_192x1x3x3_Relu);
    CNN_SetGenCtrl(&gen_ctrl_S55_Conv2d_192x1x3x3_Relu, "PADTYPE", AT_OPT_VAL(1));
    CNN_ConvolutionPoolAct_SQ8("S55_Conv2d_192x1x3x3_Relu", &gen_ctrl_S55_Conv2d_192x1x3x3_Relu, 4, 1, 192, 192, 40, 40,
        KOP_CONV_DW, 3, 3, 1, 1, 2, 2, 1,
        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
        KOP_RELU);
    // generator for CONV_2D_0_20
    CNN_GenControl_T gen_ctrl_S58_Conv2d_64x192x1x1;
    CNN_InitGenCtrl(&gen_ctrl_S58_Conv2d_64x192x1x1);
    CNN_SetGenCtrl(&gen_ctrl_S58_Conv2d_64x192x1x1, "ENABLEIM2COL", AT_OPT_VAL(1));
    CNN_ConvolutionPoolAct_SQ8("S58_Conv2d_64x192x1x1", &gen_ctrl_S58_Conv2d_64x192x1x1, 4, 1, 192, 64, 20, 20,
        KOP_CONV, 1, 1, 1, 1, 1, 1, 0,
        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
        KOP_NONE);
    // generator for CONV_2D_0_21_fusion
    CNN_GenControl_T gen_ctrl_S61_Conv2d_384x64x1x1_Relu;
    CNN_InitGenCtrl(&gen_ctrl_S61_Conv2d_384x64x1x1_Relu);
    CNN_SetGenCtrl(&gen_ctrl_S61_Conv2d_384x64x1x1_Relu, "ENABLEIM2COL", AT_OPT_VAL(1));
    CNN_ConvolutionPoolAct_SQ8("S61_Conv2d_384x64x1x1_Relu", &gen_ctrl_S61_Conv2d_384x64x1x1_Relu, 4, 1, 64, 384, 20, 20,
        KOP_CONV, 1, 1, 1, 1, 1, 1, 0,
        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
        KOP_RELU);
    // generator for DEPTHWISE_CONV_2D_0_22_fusion
    CNN_ConvolutionPoolAct_SQ8("S64_Conv2d_384x1x3x3_Relu", 0, 4, 1, 384, 384, 20, 20,
        KOP_CONV_DW, 3, 3, 1, 1, 1, 1, 1,
        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
        KOP_RELU);
    // generator for CONV_2D_0_23
    CNN_GenControl_T gen_ctrl_S67_Conv2d_64x384x1x1;
    CNN_InitGenCtrl(&gen_ctrl_S67_Conv2d_64x384x1x1);
    CNN_SetGenCtrl(&gen_ctrl_S67_Conv2d_64x384x1x1, "ENABLEIM2COL", AT_OPT_VAL(1));
    CNN_ConvolutionPoolAct_SQ8("S67_Conv2d_64x384x1x1", &gen_ctrl_S67_Conv2d_64x384x1x1, 4, 1, 384, 64, 20, 20,
        KOP_CONV, 1, 1, 1, 1, 1, 1, 0,
        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
        KOP_NONE);
    
    // generator for ADD_0_24
    CNN_MatAddAct_SQ8("S68_MatAdd_64x20x20", 0, 64, 20, 20, KOP_MATADD, KOP_NONE);
    
    // generator for CONV_2D_0_25_fusion
    CNN_GenControl_T gen_ctrl_S71_Conv2d_384x64x1x1_Relu;
    CNN_InitGenCtrl(&gen_ctrl_S71_Conv2d_384x64x1x1_Relu);
    CNN_SetGenCtrl(&gen_ctrl_S71_Conv2d_384x64x1x1_Relu, "ENABLEIM2COL", AT_OPT_VAL(1));
    CNN_ConvolutionPoolAct_SQ8("S71_Conv2d_384x64x1x1_Relu", &gen_ctrl_S71_Conv2d_384x64x1x1_Relu, 4, 1, 64, 384, 20, 20,
        KOP_CONV, 1, 1, 1, 1, 1, 1, 0,
        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
        KOP_RELU);
    // generator for DEPTHWISE_CONV_2D_0_26_fusion
    CNN_ConvolutionPoolAct_SQ8("S74_Conv2d_384x1x3x3_Relu", 0, 4, 1, 384, 384, 20, 20,
        KOP_CONV_DW, 3, 3, 1, 1, 1, 1, 1,
        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
        KOP_RELU);
    // generator for CONV_2D_0_27
    CNN_GenControl_T gen_ctrl_S77_Conv2d_64x384x1x1;
    CNN_InitGenCtrl(&gen_ctrl_S77_Conv2d_64x384x1x1);
    CNN_SetGenCtrl(&gen_ctrl_S77_Conv2d_64x384x1x1, "ENABLEIM2COL", AT_OPT_VAL(1));
    CNN_ConvolutionPoolAct_SQ8("S77_Conv2d_64x384x1x1", &gen_ctrl_S77_Conv2d_64x384x1x1, 4, 1, 384, 64, 20, 20,
        KOP_CONV, 1, 1, 1, 1, 1, 1, 0,
        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
        KOP_NONE);
    
    // generator for ADD_0_28
    CNN_MatAddAct_SQ8("S78_MatAdd_64x20x20", 0, 64, 20, 20, KOP_MATADD, KOP_NONE);
    
    // generator for CONV_2D_0_29_fusion
    CNN_GenControl_T gen_ctrl_S81_Conv2d_384x64x1x1_Relu;
    CNN_InitGenCtrl(&gen_ctrl_S81_Conv2d_384x64x1x1_Relu);
    CNN_SetGenCtrl(&gen_ctrl_S81_Conv2d_384x64x1x1_Relu, "ENABLEIM2COL", AT_OPT_VAL(1));
    CNN_ConvolutionPoolAct_SQ8("S81_Conv2d_384x64x1x1_Relu", &gen_ctrl_S81_Conv2d_384x64x1x1_Relu, 4, 1, 64, 384, 20, 20,
        KOP_CONV, 1, 1, 1, 1, 1, 1, 0,
        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
        KOP_RELU);
    // generator for DEPTHWISE_CONV_2D_0_30_fusion
    CNN_ConvolutionPoolAct_SQ8("S84_Conv2d_384x1x3x3_Relu", 0, 4, 1, 384, 384, 20, 20,
        KOP_CONV_DW, 3, 3, 1, 1, 1, 1, 1,
        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
        KOP_RELU);
    // generator for CONV_2D_0_31
    CNN_GenControl_T gen_ctrl_S87_Conv2d_96x384x1x1;
    CNN_InitGenCtrl(&gen_ctrl_S87_Conv2d_96x384x1x1);
    CNN_SetGenCtrl(&gen_ctrl_S87_Conv2d_96x384x1x1, "ENABLEIM2COL", AT_OPT_VAL(1));
    CNN_ConvolutionPoolAct_SQ8("S87_Conv2d_96x384x1x1", &gen_ctrl_S87_Conv2d_96x384x1x1, 4, 1, 384, 96, 20, 20,
        KOP_CONV, 1, 1, 1, 1, 1, 1, 0,
        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
        KOP_NONE);
    // generator for CONV_2D_0_32_fusion
    CNN_GenControl_T gen_ctrl_S90_Conv2d_576x96x1x1_Relu;
    CNN_InitGenCtrl(&gen_ctrl_S90_Conv2d_576x96x1x1_Relu);
    CNN_SetGenCtrl(&gen_ctrl_S90_Conv2d_576x96x1x1_Relu, "ENABLEIM2COL", AT_OPT_VAL(1));
    CNN_ConvolutionPoolAct_SQ8("S90_Conv2d_576x96x1x1_Relu", &gen_ctrl_S90_Conv2d_576x96x1x1_Relu, 4, 1, 96, 576, 20, 20,
        KOP_CONV, 1, 1, 1, 1, 1, 1, 0,
        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
        KOP_RELU);
    // generator for CONV_2D_0_33
    CNN_GenControl_T gen_ctrl_S93_Conv2d_32x576x1x1;
    CNN_InitGenCtrl(&gen_ctrl_S93_Conv2d_32x576x1x1);
    CNN_SetGenCtrl(&gen_ctrl_S93_Conv2d_32x576x1x1, "ENABLEIM2COL", AT_OPT_VAL(1));
    CNN_ConvolutionPoolAct_SQ8("S93_Conv2d_32x576x1x1", &gen_ctrl_S93_Conv2d_32x576x1x1, 4, 1, 576, 32, 20, 20,
        KOP_CONV, 1, 1, 1, 1, 1, 1, 0,
        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
        KOP_NONE);
    // generator for CONV_2D_0_33_trans_out0
    // transpose from 32x20x20 to 20x20x32 ((1, 2, 0))
    CNN_3DTensorPermute("S94_Op_CONV_2D_0_33_trans_out0", 0, 1, 32, 20, 20, KOP_MATPERM_CHW2HWC);
    // generator for CONV_2D_0_35_fusion
    CNN_GenControl_T gen_ctrl_S98_Conv2d_16x576x1x1_Sigmoid;
    CNN_InitGenCtrl(&gen_ctrl_S98_Conv2d_16x576x1x1_Sigmoid);
    CNN_SetGenCtrl(&gen_ctrl_S98_Conv2d_16x576x1x1_Sigmoid, "ENABLEIM2COL", AT_OPT_VAL(1));
    CNN_ConvolutionPoolAct_SQ8("S98_Conv2d_16x576x1x1_Sigmoid", &gen_ctrl_S98_Conv2d_16x576x1x1_Sigmoid, 4, 1, 576, 16, 20, 20,
        KOP_CONV, 1, 1, 1, 1, 1, 1, 0,
        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
        KOP_SIGMOID);
    // generator for CONV_2D_0_35_trans_out0
    // transpose from 16x20x20 to 20x20x16 ((1, 2, 0))
    CNN_3DTensorPermute("S99_Op_CONV_2D_0_35_trans_out0", 0, 1, 16, 20, 20, KOP_MATPERM_CHW2HWC);
    // generator for CONV_2D_0_37_fusion
    CNN_GenControl_T gen_ctrl_S103_Conv2d_128x576x1x1_Relu;
    CNN_InitGenCtrl(&gen_ctrl_S103_Conv2d_128x576x1x1_Relu);
    CNN_SetGenCtrl(&gen_ctrl_S103_Conv2d_128x576x1x1_Relu, "ENABLEIM2COL", AT_OPT_VAL(1));
    CNN_ConvolutionPoolAct_SQ8("S103_Conv2d_128x576x1x1_Relu", &gen_ctrl_S103_Conv2d_128x576x1x1_Relu, 4, 1, 576, 128, 20, 20,
        KOP_CONV, 1, 1, 1, 1, 1, 1, 0,
        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
        KOP_RELU);
    // generator for CONV_2D_0_38_fusion
    CNN_GenControl_T gen_ctrl_S106_Conv2d_256x128x3x3_Relu;
    CNN_InitGenCtrl(&gen_ctrl_S106_Conv2d_256x128x3x3_Relu);
    CNN_SetGenCtrl(&gen_ctrl_S106_Conv2d_256x128x3x3_Relu, "PADTYPE", AT_OPT_VAL(1));
    CNN_ConvolutionPoolAct_SQ8("S106_Conv2d_256x128x3x3_Relu", &gen_ctrl_S106_Conv2d_256x128x3x3_Relu, 4, 1, 128, 256, 20, 20,
        KOP_CONV, 3, 3, 1, 1, 2, 2, 1,
        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
        KOP_RELU);
    // generator for CONV_2D_0_39
    CNN_GenControl_T gen_ctrl_S109_Conv2d_32x256x1x1;
    CNN_InitGenCtrl(&gen_ctrl_S109_Conv2d_32x256x1x1);
    CNN_SetGenCtrl(&gen_ctrl_S109_Conv2d_32x256x1x1, "ENABLEIM2COL", AT_OPT_VAL(1));
    CNN_ConvolutionPoolAct_SQ8("S109_Conv2d_32x256x1x1", &gen_ctrl_S109_Conv2d_32x256x1x1, 4, 1, 256, 32, 10, 10,
        KOP_CONV, 1, 1, 1, 1, 1, 1, 0,
        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
        KOP_NONE);
    // generator for CONV_2D_0_39_trans_out0
    // transpose from 32x10x10 to 10x10x32 ((1, 2, 0))
    CNN_3DTensorPermute("S110_Op_CONV_2D_0_39_trans_out0", 0, 1, 32, 10, 10, KOP_MATPERM_CHW2HWC);
    // generator for CONV_2D_0_41_fusion
    CNN_GenControl_T gen_ctrl_S114_Conv2d_16x256x1x1_Sigmoid;
    CNN_InitGenCtrl(&gen_ctrl_S114_Conv2d_16x256x1x1_Sigmoid);
    CNN_SetGenCtrl(&gen_ctrl_S114_Conv2d_16x256x1x1_Sigmoid, "ENABLEIM2COL", AT_OPT_VAL(1));
    CNN_ConvolutionPoolAct_SQ8("S114_Conv2d_16x256x1x1_Sigmoid", &gen_ctrl_S114_Conv2d_16x256x1x1_Sigmoid, 4, 1, 256, 16, 10, 10,
        KOP_CONV, 1, 1, 1, 1, 1, 1, 0,
        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
        KOP_SIGMOID);
    // generator for CONV_2D_0_41_trans_out0
    // transpose from 16x10x10 to 10x10x16 ((1, 2, 0))
    CNN_3DTensorPermute("S115_Op_CONV_2D_0_41_trans_out0", 0, 1, 16, 10, 10, KOP_MATPERM_CHW2HWC);
    // generator for CONV_2D_0_43_fusion
    CNN_GenControl_T gen_ctrl_S119_Conv2d_128x256x1x1_Relu;
    CNN_InitGenCtrl(&gen_ctrl_S119_Conv2d_128x256x1x1_Relu);
    CNN_SetGenCtrl(&gen_ctrl_S119_Conv2d_128x256x1x1_Relu, "ENABLEIM2COL", AT_OPT_VAL(1));
    CNN_ConvolutionPoolAct_SQ8("S119_Conv2d_128x256x1x1_Relu", &gen_ctrl_S119_Conv2d_128x256x1x1_Relu, 4, 1, 256, 128, 10, 10,
        KOP_CONV, 1, 1, 1, 1, 1, 1, 0,
        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
        KOP_RELU);
    // generator for CONV_2D_0_44_fusion
    CNN_GenControl_T gen_ctrl_S122_Conv2d_256x128x3x3_Relu;
    CNN_InitGenCtrl(&gen_ctrl_S122_Conv2d_256x128x3x3_Relu);
    CNN_SetGenCtrl(&gen_ctrl_S122_Conv2d_256x128x3x3_Relu, "PADTYPE", AT_OPT_VAL(1));
    CNN_ConvolutionPoolAct_SQ8("S122_Conv2d_256x128x3x3_Relu", &gen_ctrl_S122_Conv2d_256x128x3x3_Relu, 4, 1, 128, 256, 10, 10,
        KOP_CONV, 3, 3, 1, 1, 2, 2, 1,
        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
        KOP_RELU);
    // generator for CONV_2D_0_45
    CNN_GenControl_T gen_ctrl_S125_Conv2d_32x256x1x1;
    CNN_InitGenCtrl(&gen_ctrl_S125_Conv2d_32x256x1x1);
    CNN_SetGenCtrl(&gen_ctrl_S125_Conv2d_32x256x1x1, "ENABLEIM2COL", AT_OPT_VAL(1));
    CNN_ConvolutionPoolAct_SQ8("S125_Conv2d_32x256x1x1", &gen_ctrl_S125_Conv2d_32x256x1x1, 4, 1, 256, 32, 5, 5,
        KOP_CONV, 1, 1, 1, 1, 1, 1, 0,
        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
        KOP_NONE);
    // generator for CONV_2D_0_45_trans_out0
    // transpose from 32x5x5 to 5x5x32 ((1, 2, 0))
    CNN_3DTensorPermute("S126_Op_CONV_2D_0_45_trans_out0", 0, 1, 32, 5, 5, KOP_MATPERM_CHW2HWC);
    // generator for CONV_2D_0_49_fusion
    CNN_GenControl_T gen_ctrl_S132_Conv2d_16x256x1x1_Sigmoid;
    CNN_InitGenCtrl(&gen_ctrl_S132_Conv2d_16x256x1x1_Sigmoid);
    CNN_SetGenCtrl(&gen_ctrl_S132_Conv2d_16x256x1x1_Sigmoid, "ENABLEIM2COL", AT_OPT_VAL(1));
    CNN_ConvolutionPoolAct_SQ8("S132_Conv2d_16x256x1x1_Sigmoid", &gen_ctrl_S132_Conv2d_16x256x1x1_Sigmoid, 4, 1, 256, 16, 5, 5,
        KOP_CONV, 1, 1, 1, 1, 1, 1, 0,
        KOP_NONE, 0, 0, 0, 0, 0, 0, 0,
        KOP_SIGMOID);
    // generator for CONV_2D_0_49_trans_out0
    // transpose from 16x5x5 to 5x5x16 ((1, 2, 0))
    CNN_3DTensorPermute("S133_Op_CONV_2D_0_49_trans_out0", 0, 1, 16, 5, 5, KOP_MATPERM_CHW2HWC);
    
    // generator for CUSTOM_0_53
    CNN_SSD_PostProcess_SQ8("S137_Op_CUSTOM_0_53", 0, 9000, 2, 10, 300, 0.600, 0.100);
    

#define GRAPH
#ifdef GRAPH
    CreateGraph("lynredCNN",
        /* Arguments either passed or globals */
            CArgs(196,
                TCArgInfo("unsigned char * __restrict__", "Input_1", ARG_SCOPE_ARG, ARG_DIR_IN, AT_MEM_L2, AT_MEM_L2, 0),
                TCArgInfo("signed char * __restrict__", "Stdconstant21", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant21.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "1_convbias", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/1_convbias.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S4_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S4_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S4_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S4_Mul_shift.tensor", 1, 1, 8, 0)),
                // all 0
                TCArgInfo("signed char * __restrict__", "S4_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S4_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Stdconstant50", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant50.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Stdconstant3", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant3.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S7_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S7_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S7_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S7_Mul_shift.tensor", 1, 1, 8, 0)),
                // all 0
                TCArgInfo("signed char * __restrict__", "S7_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S7_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Stdconstant22", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant22.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Stdconstant51", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant51.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S10_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S10_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S10_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S10_Mul_shift.tensor", 1, 1, 8, 0)),
                // BiasQ: 0
                TCArgInfo("signed char * __restrict__", "S10_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S10_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Stdconstant23", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant23.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Stdconstant4", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant4.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S13_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S13_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S13_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S13_Mul_shift.tensor", 1, 1, 8, 0)),
                // all 0
                TCArgInfo("signed char * __restrict__", "S13_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S13_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Stdconstant52", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant52.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Stdconstant5", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant5.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S16_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S16_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S16_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S16_Mul_shift.tensor", 1, 1, 8, 0)),
                // all 0
                TCArgInfo("signed char * __restrict__", "S16_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S16_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Stdconstant24", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant24.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Stdconstant53", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant53.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S19_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S19_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S19_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S19_Mul_shift.tensor", 1, 1, 8, 0)),
                // BiasQ: 0
                TCArgInfo("signed char * __restrict__", "S19_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S19_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Stdconstant25", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant25.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Stdconstant6", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant6.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S22_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S22_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S22_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S22_Mul_shift.tensor", 1, 1, 8, 0)),
                // all 0
                TCArgInfo("signed char * __restrict__", "S22_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S22_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Stdconstant54", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant54.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Stdconstant7", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant7.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S25_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S25_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S25_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S25_Mul_shift.tensor", 1, 1, 8, 0)),
                // all 0
                TCArgInfo("signed char * __restrict__", "S25_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S25_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Stdconstant26", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant26.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Stdconstant55", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant55.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S28_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S28_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S28_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S28_Mul_shift.tensor", 1, 1, 8, 0)),
                // BiasQ: 0
                TCArgInfo("signed char * __restrict__", "S28_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S28_Infos.tensor", 1, 1, 8, 0)),
                // In1Scale: 135 In1ScaleN: 7 OutScale: 21 OutScaleN: 5
                TCArgInfo("signed char * __restrict__", "S29_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S29_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Stdconstant27", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant27.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Stdconstant8", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant8.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S32_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S32_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S32_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S32_Mul_shift.tensor", 1, 1, 8, 0)),
                // all 0
                TCArgInfo("signed char * __restrict__", "S32_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S32_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Stdconstant56", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant56.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Stdconstant9", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant9.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S35_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S35_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S35_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S35_Mul_shift.tensor", 1, 1, 8, 0)),
                // all 0
                TCArgInfo("signed char * __restrict__", "S35_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S35_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Stdconstant28", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant28.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Stdconstant57", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant57.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S38_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S38_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S38_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S38_Mul_shift.tensor", 1, 1, 8, 0)),
                // BiasQ: 0
                TCArgInfo("signed char * __restrict__", "S38_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S38_Infos.tensor", 1, 1, 8, 0)),
                // In1Scale: 157 In1ScaleN: 7 OutScale: 37 OutScaleN: 6
                TCArgInfo("signed char * __restrict__", "S39_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S39_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Stdconstant29", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant29.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Stdconstant10", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant10.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S42_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S42_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S42_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S42_Mul_shift.tensor", 1, 1, 8, 0)),
                // all 0
                TCArgInfo("signed char * __restrict__", "S42_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S42_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Stdconstant30", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant30.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Boxpredictorconvolutionalboxhe", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Boxpredictorconvolutionalboxhe.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S45_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S45_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S45_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S45_Mul_shift.tensor", 1, 1, 8, 0)),
                // BiasQ: 0
                TCArgInfo("signed char * __restrict__", "S45_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S45_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Stdconstant31", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant31.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Boxpredictorconvolutionalclass", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Boxpredictorconvolutionalclass.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S50_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S50_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S50_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S50_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.062992 out: 0.007874 qbias: 127 qnorm: 7 A0: x B0: x C0: x
                TCArgInfo("signed char * __restrict__", "S50_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S50_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Stdconstant58", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant58.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Stdconstant11", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant11.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S55_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S55_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S55_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S55_Mul_shift.tensor", 1, 1, 8, 0)),
                // all 0
                TCArgInfo("signed char * __restrict__", "S55_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S55_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Stdconstant32", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant32.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Stdconstant59", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant59.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S58_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S58_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S58_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S58_Mul_shift.tensor", 1, 1, 8, 0)),
                // BiasQ: 0
                TCArgInfo("signed char * __restrict__", "S58_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S58_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Stdconstant33", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant33.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Stdconstant12", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant12.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S61_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S61_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S61_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S61_Mul_shift.tensor", 1, 1, 8, 0)),
                // all 0
                TCArgInfo("signed char * __restrict__", "S61_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S61_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Stdconstant60", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant60.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Stdconstant13", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant13.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S64_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S64_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S64_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S64_Mul_shift.tensor", 1, 1, 8, 0)),
                // all 0
                TCArgInfo("signed char * __restrict__", "S64_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S64_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Stdconstant34", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant34.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Stdconstant61", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant61.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S67_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S67_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S67_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S67_Mul_shift.tensor", 1, 1, 8, 0)),
                // BiasQ: 0
                TCArgInfo("signed char * __restrict__", "S67_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S67_Infos.tensor", 1, 1, 8, 0)),
                // In1Scale: 137 In1ScaleN: 7 OutScale: 195 OutScaleN: 8
                TCArgInfo("signed char * __restrict__", "S68_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S68_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Stdconstant35", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant35.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Stdconstant14", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant14.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S71_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S71_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S71_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S71_Mul_shift.tensor", 1, 1, 8, 0)),
                // all 0
                TCArgInfo("signed char * __restrict__", "S71_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S71_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Stdconstant62", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant62.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Stdconstant15", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant15.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S74_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S74_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S74_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S74_Mul_shift.tensor", 1, 1, 8, 0)),
                // all 0
                TCArgInfo("signed char * __restrict__", "S74_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S74_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Stdconstant36", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant36.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Stdconstant63", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant63.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S77_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S77_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S77_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S77_Mul_shift.tensor", 1, 1, 8, 0)),
                // BiasQ: 0
                TCArgInfo("signed char * __restrict__", "S77_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S77_Infos.tensor", 1, 1, 8, 0)),
                // In1Scale: 65 In1ScaleN: 6 OutScale: 187 OutScaleN: 8
                TCArgInfo("signed char * __restrict__", "S78_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S78_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Stdconstant37", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant37.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Stdconstant16", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant16.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S81_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S81_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S81_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S81_Mul_shift.tensor", 1, 1, 8, 0)),
                // all 0
                TCArgInfo("signed char * __restrict__", "S81_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S81_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Stdconstant64", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant64.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Stdconstant17", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant17.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S84_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S84_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S84_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S84_Mul_shift.tensor", 1, 1, 8, 0)),
                // all 0
                TCArgInfo("signed char * __restrict__", "S84_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S84_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Stdconstant38", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant38.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Stdconstant65", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant65.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S87_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S87_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S87_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S87_Mul_shift.tensor", 1, 1, 8, 0)),
                // BiasQ: 0
                TCArgInfo("signed char * __restrict__", "S87_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S87_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Stdconstant39", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant39.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Stdconstant18", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant18.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S90_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S90_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S90_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S90_Mul_shift.tensor", 1, 1, 8, 0)),
                // all 0
                TCArgInfo("signed char * __restrict__", "S90_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S90_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Stdconstant40", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant40.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Boxpredictorconvolutionalboxhe_319ba674", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Boxpredictorconvolutionalboxhe_319ba674.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S93_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S93_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S93_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S93_Mul_shift.tensor", 1, 1, 8, 0)),
                // BiasQ: 0
                TCArgInfo("signed char * __restrict__", "S93_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S93_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Stdconstant41", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant41.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Boxpredictorconvolutionalclass_ba179d10", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Boxpredictorconvolutionalclass_ba179d10.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S98_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S98_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S98_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S98_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.062992 out: 0.007874 qbias: 127 qnorm: 7 A0: x B0: x C0: x
                TCArgInfo("signed char * __restrict__", "S98_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S98_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Stdconstant42", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant42.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Stdconstant19", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant19.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S103_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S103_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S103_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S103_Mul_shift.tensor", 1, 1, 8, 0)),
                // all 0
                TCArgInfo("signed char * __restrict__", "S103_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S103_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Stdconstant43", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant43.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "13_convbias", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/13_convbias.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S106_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S106_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S106_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S106_Mul_shift.tensor", 1, 1, 8, 0)),
                // all 0
                TCArgInfo("signed char * __restrict__", "S106_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S106_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Stdconstant44", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant44.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Boxpredictorconvolutionalboxhe_8bd56dc8", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Boxpredictorconvolutionalboxhe_8bd56dc8.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S109_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S109_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S109_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S109_Mul_shift.tensor", 1, 1, 8, 0)),
                // BiasQ: 0
                TCArgInfo("signed char * __restrict__", "S109_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S109_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Stdconstant45", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant45.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Boxpredictorconvolutionalclass_24772bd8", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Boxpredictorconvolutionalclass_24772bd8.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S114_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S114_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S114_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S114_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.062992 out: 0.007874 qbias: 127 qnorm: 7 A0: x B0: x C0: x
                TCArgInfo("signed char * __restrict__", "S114_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S114_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Stdconstant46", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant46.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Stdconstant20", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant20.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S119_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S119_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S119_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S119_Mul_shift.tensor", 1, 1, 8, 0)),
                // all 0
                TCArgInfo("signed char * __restrict__", "S119_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S119_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Stdconstant47", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant47.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "15_convbias", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/15_convbias.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S122_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S122_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S122_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S122_Mul_shift.tensor", 1, 1, 8, 0)),
                // all 0
                TCArgInfo("signed char * __restrict__", "S122_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S122_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Stdconstant48", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant48.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Boxpredictorconvolutionalboxhe_db4937ca", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Boxpredictorconvolutionalboxhe_db4937ca.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S125_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S125_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S125_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S125_Mul_shift.tensor", 1, 1, 8, 0)),
                // BiasQ: 0
                TCArgInfo("signed char * __restrict__", "S125_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S125_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Stdconstant49", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant49.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed int * __restrict__", "Boxpredictorconvolutionalclass_20f59186", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Boxpredictorconvolutionalclass_20f59186.tensor", 1, 1, 32, 0)),
                TCArgInfo("unsigned char * __restrict__", "S132_Mul_scale", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S132_Mul_scale.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S132_Mul_shift", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S132_Mul_shift.tensor", 1, 1, 8, 0)),
                // in: 0.062992 out: 0.007874 qbias: 127 qnorm: 7 A0: x B0: x C0: x
                TCArgInfo("signed char * __restrict__", "S132_Infos", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S132_Infos.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "Stdconstant2", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/Stdconstant2.tensor", 1, 1, 8, 0)),
                TCArgInfo("unsigned char * __restrict__", "S137_Ssd_scales", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S137_Ssd_scales.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed char * __restrict__", "S137_Ssd_norms", ARG_SCOPE_GLOBAL, ARG_DIR_CONSTIN, AT_MEM_L3_HFLASH, AT_MEM_UNDEF, ConstInfo("BUILD_MODEL_8BIT/tensors/S137_Ssd_norms.tensor", 1, 1, 8, 0)),
                TCArgInfo("signed short * __restrict__", "Output_1", ARG_SCOPE_ARG, ARG_DIR_OUT, AT_MEM_L2, AT_MEM_L2, 0),
                TCArgInfo("signed char * __restrict__", "Output_2", ARG_SCOPE_ARG, ARG_DIR_OUT, AT_MEM_L2, AT_MEM_L2, 0),
                TCArgInfo("signed char * __restrict__", "Output_3", ARG_SCOPE_ARG, ARG_DIR_OUT, AT_MEM_L2, AT_MEM_L2, 0)
            ),
        /* Locals, allocated dynamically */
        CArgs(44,
            TCArgInfo("signed char * __restrict__", "S1_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed char * __restrict__", "S4_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed char * __restrict__", "S7_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed char * __restrict__", "S10_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed char * __restrict__", "S13_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed char * __restrict__", "S16_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed char * __restrict__", "S19_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed char * __restrict__", "S22_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed char * __restrict__", "S25_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed char * __restrict__", "S28_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed char * __restrict__", "S29_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed char * __restrict__", "S32_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed char * __restrict__", "S35_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed char * __restrict__", "S38_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed char * __restrict__", "S39_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed char * __restrict__", "S42_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed char * __restrict__", "S45_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed char * __restrict__", "S50_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed char * __restrict__", "S55_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed char * __restrict__", "S58_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed char * __restrict__", "S61_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed char * __restrict__", "S64_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed char * __restrict__", "S67_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed char * __restrict__", "S68_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed char * __restrict__", "S71_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed char * __restrict__", "S74_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed char * __restrict__", "S77_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed char * __restrict__", "S78_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed char * __restrict__", "S81_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed char * __restrict__", "S84_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed char * __restrict__", "S87_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed char * __restrict__", "S90_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed char * __restrict__", "S93_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed char * __restrict__", "S98_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed char * __restrict__", "S103_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed char * __restrict__", "S106_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed char * __restrict__", "S109_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed char * __restrict__", "S114_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed char * __restrict__", "S119_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed char * __restrict__", "S122_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed char * __restrict__", "S125_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed char * __restrict__", "S128_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed char * __restrict__", "S132_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0),
            TCArgInfo("signed char * __restrict__", "S135_Output", ARG_SCOPE_LOCAL, ARG_DIR_INOUT, AT_MEM_UNDEF, AT_MEM_UNDEF, 0)
        )
    );

    /* Stacked tensors - Concats */
    AddStackedTensors("S128_Output", 4, "S46_Output", "S94_Output", "S110_Output", "S126_Output");
    AddStackedTensors("S135_Output", 4, "S51_Output", "S99_Output", "S115_Output", "S133_Output");

    // Node input_1_formatter inq 0.00<(u8-0.00)*1.00000000<255.00 outq -1.00<(i8-0.00)*0.00781250<0.99 forced
    AddNode("S1_Op_input_1_formatter", Bindings(2, GNodeArg(GNA_IN, "Input_1", 0), GNodeArg(GNA_OUT, "S1_Output", 0)));
    // Node S4_Conv2d_32x1x3x3_Relu inq -1.00<(i8-0.00)*0.00781250<0.99 forced weightsq chan<(i8-0.00)*chan<chan outq -11.33<(i8-0.00)*0.08847927<11.24 forced biasesq chan<(i32-0.00)*chan<chan
    AddNode("S4_Conv2d_32x1x3x3_Relu", Bindings(7, GNodeArg(GNA_IN, "S1_Output", 0), GNodeArg(GNA_IN, "Stdconstant21", 0), GNodeArg(GNA_IN, "1_convbias", 0), GNodeArg(GNA_OUT, "S4_Output", 0), GNodeArg(GNA_IN, "S4_Mul_scale", 0), GNodeArg(GNA_IN, "S4_Mul_shift", 0), GNodeArg(GNA_IN, "S4_Infos", 0)));
    // Node S7_Conv2d_32x1x3x3_Relu inq -11.33<(i8-0.00)*0.08847927<11.24 forced weightsq chan<(i8-0.00)*chan<chan outq -19.52<(i8-0.00)*0.15248934<19.37 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S7_Conv2d_32x1x3x3_Relu", Bindings(7, GNodeArg(GNA_IN, "S4_Output", 0), GNodeArg(GNA_IN, "Stdconstant50", 0), GNodeArg(GNA_IN, "Stdconstant3", 0), GNodeArg(GNA_OUT, "S7_Output", 0), GNodeArg(GNA_IN, "S7_Mul_scale", 0), GNodeArg(GNA_IN, "S7_Mul_shift", 0), GNodeArg(GNA_IN, "S7_Infos", 0)));
    // Node S10_Conv2d_24x32x1x1 inq -19.52<(i8-0.00)*0.15248934<19.37 weightsq chan<(i8-0.00)*chan<chan outq -16.03<(i8-0.00)*0.12519993<15.90 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S10_Conv2d_24x32x1x1", Bindings(7, GNodeArg(GNA_IN, "S7_Output", 0), GNodeArg(GNA_IN, "Stdconstant22", 0), GNodeArg(GNA_IN, "Stdconstant51", 0), GNodeArg(GNA_OUT, "S10_Output", 0), GNodeArg(GNA_IN, "S10_Mul_scale", 0), GNodeArg(GNA_IN, "S10_Mul_shift", 0), GNodeArg(GNA_IN, "S10_Infos", 0)));
    // Node S13_Conv2d_144x24x1x1_Relu inq -16.03<(i8-0.00)*0.12519993<15.90 weightsq chan<(i8-0.00)*chan<chan outq -18.11<(i8-0.00)*0.14148083<17.97 forced biasesq chan<(i32-0.00)*chan<chan
    AddNode("S13_Conv2d_144x24x1x1_Relu", Bindings(7, GNodeArg(GNA_IN, "S10_Output", 0), GNodeArg(GNA_IN, "Stdconstant23", 0), GNodeArg(GNA_IN, "Stdconstant4", 0), GNodeArg(GNA_OUT, "S13_Output", 0), GNodeArg(GNA_IN, "S13_Mul_scale", 0), GNodeArg(GNA_IN, "S13_Mul_shift", 0), GNodeArg(GNA_IN, "S13_Infos", 0)));
    // Node S16_Conv2d_144x1x3x3_Relu inq -18.11<(i8-0.00)*0.14148083<17.97 forced weightsq chan<(i8-0.00)*chan<chan outq -18.89<(i8-0.00)*0.14758968<18.74 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S16_Conv2d_144x1x3x3_Relu", Bindings(7, GNodeArg(GNA_IN, "S13_Output", 0), GNodeArg(GNA_IN, "Stdconstant52", 0), GNodeArg(GNA_IN, "Stdconstant5", 0), GNodeArg(GNA_OUT, "S16_Output", 0), GNodeArg(GNA_IN, "S16_Mul_scale", 0), GNodeArg(GNA_IN, "S16_Mul_shift", 0), GNodeArg(GNA_IN, "S16_Infos", 0)));
    // Node S19_Conv2d_32x144x1x1 inq -18.89<(i8-0.00)*0.14758968<18.74 weightsq chan<(i8-0.00)*chan<chan outq -12.70<(i8-0.00)*0.09921555<12.60 forced biasesq chan<(i32-0.00)*chan<chan
    AddNode("S19_Conv2d_32x144x1x1", Bindings(7, GNodeArg(GNA_IN, "S16_Output", 0), GNodeArg(GNA_IN, "Stdconstant24", 0), GNodeArg(GNA_IN, "Stdconstant53", 0), GNodeArg(GNA_OUT, "S19_Output", 0), GNodeArg(GNA_IN, "S19_Mul_scale", 0), GNodeArg(GNA_IN, "S19_Mul_shift", 0), GNodeArg(GNA_IN, "S19_Infos", 0)));
    // Node S22_Conv2d_192x32x1x1_Relu inq -12.70<(i8-0.00)*0.09921555<12.60 forced weightsq chan<(i8-0.00)*chan<chan outq -15.41<(i8-0.00)*0.12040800<15.29 forced biasesq chan<(i32-0.00)*chan<chan
    AddNode("S22_Conv2d_192x32x1x1_Relu", Bindings(7, GNodeArg(GNA_IN, "S19_Output", 0), GNodeArg(GNA_IN, "Stdconstant25", 0), GNodeArg(GNA_IN, "Stdconstant6", 0), GNodeArg(GNA_OUT, "S22_Output", 0), GNodeArg(GNA_IN, "S22_Mul_scale", 0), GNodeArg(GNA_IN, "S22_Mul_shift", 0), GNodeArg(GNA_IN, "S22_Infos", 0)));
    // Node S25_Conv2d_192x1x3x3_Relu inq -15.41<(i8-0.00)*0.12040800<15.29 forced weightsq chan<(i8-0.00)*chan<chan outq -18.63<(i8-0.00)*0.14558031<18.49 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S25_Conv2d_192x1x3x3_Relu", Bindings(7, GNodeArg(GNA_IN, "S22_Output", 0), GNodeArg(GNA_IN, "Stdconstant54", 0), GNodeArg(GNA_IN, "Stdconstant7", 0), GNodeArg(GNA_OUT, "S25_Output", 0), GNodeArg(GNA_IN, "S25_Mul_scale", 0), GNodeArg(GNA_IN, "S25_Mul_shift", 0), GNodeArg(GNA_IN, "S25_Infos", 0)));
    // Node S28_Conv2d_32x192x1x1 inq -18.63<(i8-0.00)*0.14558031<18.49 weightsq chan<(i8-0.00)*chan<chan outq -13.36<(i8-0.00)*0.10438375<13.26 forced biasesq chan<(i32-0.00)*chan<chan
    AddNode("S28_Conv2d_32x192x1x1", Bindings(7, GNodeArg(GNA_IN, "S25_Output", 0), GNodeArg(GNA_IN, "Stdconstant26", 0), GNodeArg(GNA_IN, "Stdconstant55", 0), GNodeArg(GNA_OUT, "S28_Output", 0), GNodeArg(GNA_IN, "S28_Mul_scale", 0), GNodeArg(GNA_IN, "S28_Mul_shift", 0), GNodeArg(GNA_IN, "S28_Infos", 0)));
    // Node S29_MatAdd_32x40x40 in1q -13.36<(i8-0.00)*0.10438375<13.26 forced in2q -12.70<(i8-0.00)*0.09921555<12.60 forced outq -19.32<(i8-0.00)*0.15095078<19.17 forced
    AddNode("S29_MatAdd_32x40x40", Bindings(4, GNodeArg(GNA_IN, "S28_Output", 0), GNodeArg(GNA_IN, "S19_Output", 0), GNodeArg(GNA_OUT, "S29_Output", 0), GNodeArg(GNA_IN, "S29_Infos", 0)));
    // Node S32_Conv2d_192x32x1x1_Relu inq -19.32<(i8-0.00)*0.15095078<19.17 forced weightsq chan<(i8-0.00)*chan<chan outq -14.15<(i8-0.00)*0.11052850<14.04 forced biasesq chan<(i32-0.00)*chan<chan
    AddNode("S32_Conv2d_192x32x1x1_Relu", Bindings(7, GNodeArg(GNA_IN, "S29_Output", 0), GNodeArg(GNA_IN, "Stdconstant27", 0), GNodeArg(GNA_IN, "Stdconstant8", 0), GNodeArg(GNA_OUT, "S32_Output", 0), GNodeArg(GNA_IN, "S32_Mul_scale", 0), GNodeArg(GNA_IN, "S32_Mul_shift", 0), GNodeArg(GNA_IN, "S32_Infos", 0)));
    // Node S35_Conv2d_192x1x3x3_Relu inq -14.15<(i8-0.00)*0.11052850<14.04 forced weightsq chan<(i8-0.00)*chan<chan outq -17.04<(i8-0.00)*0.13313278<16.91 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S35_Conv2d_192x1x3x3_Relu", Bindings(7, GNodeArg(GNA_IN, "S32_Output", 0), GNodeArg(GNA_IN, "Stdconstant56", 0), GNodeArg(GNA_IN, "Stdconstant9", 0), GNodeArg(GNA_OUT, "S35_Output", 0), GNodeArg(GNA_IN, "S35_Mul_scale", 0), GNodeArg(GNA_IN, "S35_Mul_shift", 0), GNodeArg(GNA_IN, "S35_Infos", 0)));
    // Node S38_Conv2d_32x192x1x1 inq -17.04<(i8-0.00)*0.13313278<16.91 weightsq chan<(i8-0.00)*chan<chan outq -15.76<(i8-0.00)*0.12313851<15.64 forced biasesq chan<(i32-0.00)*chan<chan
    AddNode("S38_Conv2d_32x192x1x1", Bindings(7, GNodeArg(GNA_IN, "S35_Output", 0), GNodeArg(GNA_IN, "Stdconstant28", 0), GNodeArg(GNA_IN, "Stdconstant57", 0), GNodeArg(GNA_OUT, "S38_Output", 0), GNodeArg(GNA_IN, "S38_Mul_scale", 0), GNodeArg(GNA_IN, "S38_Mul_shift", 0), GNodeArg(GNA_IN, "S38_Infos", 0)));
    // Node S39_MatAdd_32x40x40 in1q -19.32<(i8-0.00)*0.15095078<19.17 forced in2q -15.76<(i8-0.00)*0.12313851<15.64 forced outq -27.32<(i8-0.00)*0.21345488<27.11 forced
    AddNode("S39_MatAdd_32x40x40", Bindings(4, GNodeArg(GNA_IN, "S29_Output", 0), GNodeArg(GNA_IN, "S38_Output", 0), GNodeArg(GNA_OUT, "S39_Output", 0), GNodeArg(GNA_IN, "S39_Infos", 0)));
    // Node S42_Conv2d_192x32x1x1_Relu inq -27.32<(i8-0.00)*0.21345488<27.11 forced weightsq chan<(i8-0.00)*chan<chan outq -11.88<(i8-0.00)*0.09281165<11.79 forced biasesq chan<(i32-0.00)*chan<chan
    AddNode("S42_Conv2d_192x32x1x1_Relu", Bindings(7, GNodeArg(GNA_IN, "S39_Output", 0), GNodeArg(GNA_IN, "Stdconstant29", 0), GNodeArg(GNA_IN, "Stdconstant10", 0), GNodeArg(GNA_OUT, "S42_Output", 0), GNodeArg(GNA_IN, "S42_Mul_scale", 0), GNodeArg(GNA_IN, "S42_Mul_shift", 0), GNodeArg(GNA_IN, "S42_Infos", 0)));
    // Node S45_Conv2d_12x192x1x1 inq -11.88<(i8-0.00)*0.09281165<11.79 forced weightsq chan<(i8-0.00)*chan<chan outq -13.67<(i8-0.00)*0.10683099<13.57 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S45_Conv2d_12x192x1x1", Bindings(7, GNodeArg(GNA_IN, "S42_Output", 0), GNodeArg(GNA_IN, "Stdconstant30", 0), GNodeArg(GNA_IN, "Boxpredictorconvolutionalboxhe", 0), GNodeArg(GNA_OUT, "S45_Output", 0), GNodeArg(GNA_IN, "S45_Mul_scale", 0), GNodeArg(GNA_IN, "S45_Mul_shift", 0), GNodeArg(GNA_IN, "S45_Infos", 0)));
    // Node CONV_2D_0_15_trans_out0 inq -13.67<(i8-0.00)*0.10683099<13.57 outq -13.67<(i8-0.00)*0.10683099<13.57
    AddNode("S46_Op_CONV_2D_0_15_trans_out0", Bindings(2, GNodeArg(GNA_IN, "S45_Output", 0), GNodeArg(GNA_OUT, "S46_Output", 0)));
    // Node S50_Conv2d_6x192x1x1_Sigmoid inq -11.88<(i8-0.00)*0.09281165<11.79 forced weightsq chan<(i8-0.00)*chan<chan outq -1.01<(i8-0.00)*0.00787402<1.00 forced biasesq chan<(i32-0.00)*chan<chan
    AddNode("S50_Conv2d_6x192x1x1_Sigmoid", Bindings(7, GNodeArg(GNA_IN, "S42_Output", 0), GNodeArg(GNA_IN, "Stdconstant31", 0), GNodeArg(GNA_IN, "Boxpredictorconvolutionalclass", 0), GNodeArg(GNA_OUT, "S50_Output", 0), GNodeArg(GNA_IN, "S50_Mul_scale", 0), GNodeArg(GNA_IN, "S50_Mul_shift", 0), GNodeArg(GNA_IN, "S50_Infos", 0)));
    // Node CONV_2D_0_17_trans_out0 inq -1.01<(i8-0.00)*0.00787402<1.00 forced outq -1.01<(i8-0.00)*0.00787402<1.00 forced
    AddNode("S51_Op_CONV_2D_0_17_trans_out0", Bindings(2, GNodeArg(GNA_IN, "S50_Output", 0), GNodeArg(GNA_OUT, "S51_Output", 0)));
    // Node S55_Conv2d_192x1x3x3_Relu inq -11.88<(i8-0.00)*0.09281165<11.79 forced weightsq chan<(i8-0.00)*chan<chan outq -15.96<(i8-0.00)*0.12466998<15.83 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S55_Conv2d_192x1x3x3_Relu", Bindings(7, GNodeArg(GNA_IN, "S42_Output", 0), GNodeArg(GNA_IN, "Stdconstant58", 0), GNodeArg(GNA_IN, "Stdconstant11", 0), GNodeArg(GNA_OUT, "S55_Output", 0), GNodeArg(GNA_IN, "S55_Mul_scale", 0), GNodeArg(GNA_IN, "S55_Mul_shift", 0), GNodeArg(GNA_IN, "S55_Infos", 0)));
    // Node S58_Conv2d_64x192x1x1 inq -15.96<(i8-0.00)*0.12466998<15.83 weightsq chan<(i8-0.00)*chan<chan outq -9.45<(i8-0.00)*0.07385384<9.38 forced biasesq chan<(i32-0.00)*chan<chan
    AddNode("S58_Conv2d_64x192x1x1", Bindings(7, GNodeArg(GNA_IN, "S55_Output", 0), GNodeArg(GNA_IN, "Stdconstant32", 0), GNodeArg(GNA_IN, "Stdconstant59", 0), GNodeArg(GNA_OUT, "S58_Output", 0), GNodeArg(GNA_IN, "S58_Mul_scale", 0), GNodeArg(GNA_IN, "S58_Mul_shift", 0), GNodeArg(GNA_IN, "S58_Infos", 0)));
    // Node S61_Conv2d_384x64x1x1_Relu inq -9.45<(i8-0.00)*0.07385384<9.38 forced weightsq chan<(i8-0.00)*chan<chan outq -10.40<(i8-0.00)*0.08125377<10.32 forced biasesq chan<(i32-0.00)*chan<chan
    AddNode("S61_Conv2d_384x64x1x1_Relu", Bindings(7, GNodeArg(GNA_IN, "S58_Output", 0), GNodeArg(GNA_IN, "Stdconstant33", 0), GNodeArg(GNA_IN, "Stdconstant12", 0), GNodeArg(GNA_OUT, "S61_Output", 0), GNodeArg(GNA_IN, "S61_Mul_scale", 0), GNodeArg(GNA_IN, "S61_Mul_shift", 0), GNodeArg(GNA_IN, "S61_Infos", 0)));
    // Node S64_Conv2d_384x1x3x3_Relu inq -10.40<(i8-0.00)*0.08125377<10.32 forced weightsq chan<(i8-0.00)*chan<chan outq -12.53<(i8-0.00)*0.09787202<12.43 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S64_Conv2d_384x1x3x3_Relu", Bindings(7, GNodeArg(GNA_IN, "S61_Output", 0), GNodeArg(GNA_IN, "Stdconstant60", 0), GNodeArg(GNA_IN, "Stdconstant13", 0), GNodeArg(GNA_OUT, "S64_Output", 0), GNodeArg(GNA_IN, "S64_Mul_scale", 0), GNodeArg(GNA_IN, "S64_Mul_shift", 0), GNodeArg(GNA_IN, "S64_Infos", 0)));
    // Node S67_Conv2d_64x384x1x1 inq -12.53<(i8-0.00)*0.09787202<12.43 weightsq chan<(i8-0.00)*chan<chan outq -8.81<(i8-0.00)*0.06881190<8.74 forced biasesq chan<(i32-0.00)*chan<chan
    AddNode("S67_Conv2d_64x384x1x1", Bindings(7, GNodeArg(GNA_IN, "S64_Output", 0), GNodeArg(GNA_IN, "Stdconstant34", 0), GNodeArg(GNA_IN, "Stdconstant61", 0), GNodeArg(GNA_OUT, "S67_Output", 0), GNodeArg(GNA_IN, "S67_Mul_scale", 0), GNodeArg(GNA_IN, "S67_Mul_shift", 0), GNodeArg(GNA_IN, "S67_Infos", 0)));
    // Node S68_MatAdd_64x20x20 in1q -9.45<(i8-0.00)*0.07385384<9.38 forced in2q -8.81<(i8-0.00)*0.06881190<8.74 forced outq -11.55<(i8-0.00)*0.09020660<11.46 forced
    AddNode("S68_MatAdd_64x20x20", Bindings(4, GNodeArg(GNA_IN, "S58_Output", 0), GNodeArg(GNA_IN, "S67_Output", 0), GNodeArg(GNA_OUT, "S68_Output", 0), GNodeArg(GNA_IN, "S68_Infos", 0)));
    // Node S71_Conv2d_384x64x1x1_Relu inq -11.55<(i8-0.00)*0.09020660<11.46 forced weightsq chan<(i8-0.00)*chan<chan outq -9.80<(i8-0.00)*0.07655590<9.72 forced biasesq chan<(i32-0.00)*chan<chan
    AddNode("S71_Conv2d_384x64x1x1_Relu", Bindings(7, GNodeArg(GNA_IN, "S68_Output", 0), GNodeArg(GNA_IN, "Stdconstant35", 0), GNodeArg(GNA_IN, "Stdconstant14", 0), GNodeArg(GNA_OUT, "S71_Output", 0), GNodeArg(GNA_IN, "S71_Mul_scale", 0), GNodeArg(GNA_IN, "S71_Mul_shift", 0), GNodeArg(GNA_IN, "S71_Infos", 0)));
    // Node S74_Conv2d_384x1x3x3_Relu inq -9.80<(i8-0.00)*0.07655590<9.72 forced weightsq chan<(i8-0.00)*chan<chan outq -11.39<(i8-0.00)*0.08896765<11.30 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S74_Conv2d_384x1x3x3_Relu", Bindings(7, GNodeArg(GNA_IN, "S71_Output", 0), GNodeArg(GNA_IN, "Stdconstant62", 0), GNodeArg(GNA_IN, "Stdconstant15", 0), GNodeArg(GNA_OUT, "S74_Output", 0), GNodeArg(GNA_IN, "S74_Mul_scale", 0), GNodeArg(GNA_IN, "S74_Mul_shift", 0), GNodeArg(GNA_IN, "S74_Infos", 0)));
    // Node S77_Conv2d_64x384x1x1 inq -11.39<(i8-0.00)*0.08896765<11.30 weightsq chan<(i8-0.00)*chan<chan outq -11.70<(i8-0.00)*0.09142317<11.61 forced biasesq chan<(i32-0.00)*chan<chan
    AddNode("S77_Conv2d_64x384x1x1", Bindings(7, GNodeArg(GNA_IN, "S74_Output", 0), GNodeArg(GNA_IN, "Stdconstant36", 0), GNodeArg(GNA_IN, "Stdconstant63", 0), GNodeArg(GNA_OUT, "S77_Output", 0), GNodeArg(GNA_IN, "S77_Mul_scale", 0), GNodeArg(GNA_IN, "S77_Mul_shift", 0), GNodeArg(GNA_IN, "S77_Infos", 0)));
    // Node S78_MatAdd_64x20x20 in1q -11.70<(i8-0.00)*0.09142317<11.61 forced in2q -11.55<(i8-0.00)*0.09020660<11.46 forced outq -15.81<(i8-0.00)*0.12348305<15.68 forced
    AddNode("S78_MatAdd_64x20x20", Bindings(4, GNodeArg(GNA_IN, "S77_Output", 0), GNodeArg(GNA_IN, "S68_Output", 0), GNodeArg(GNA_OUT, "S78_Output", 0), GNodeArg(GNA_IN, "S78_Infos", 0)));
    // Node S81_Conv2d_384x64x1x1_Relu inq -15.81<(i8-0.00)*0.12348305<15.68 forced weightsq chan<(i8-0.00)*chan<chan outq -9.67<(i8-0.00)*0.07552008<9.59 forced biasesq chan<(i32-0.00)*chan<chan
    AddNode("S81_Conv2d_384x64x1x1_Relu", Bindings(7, GNodeArg(GNA_IN, "S78_Output", 0), GNodeArg(GNA_IN, "Stdconstant37", 0), GNodeArg(GNA_IN, "Stdconstant16", 0), GNodeArg(GNA_OUT, "S81_Output", 0), GNodeArg(GNA_IN, "S81_Mul_scale", 0), GNodeArg(GNA_IN, "S81_Mul_shift", 0), GNodeArg(GNA_IN, "S81_Infos", 0)));
    // Node S84_Conv2d_384x1x3x3_Relu inq -9.67<(i8-0.00)*0.07552008<9.59 forced weightsq chan<(i8-0.00)*chan<chan outq -13.43<(i8-0.00)*0.10489037<13.32 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S84_Conv2d_384x1x3x3_Relu", Bindings(7, GNodeArg(GNA_IN, "S81_Output", 0), GNodeArg(GNA_IN, "Stdconstant64", 0), GNodeArg(GNA_IN, "Stdconstant17", 0), GNodeArg(GNA_OUT, "S84_Output", 0), GNodeArg(GNA_IN, "S84_Mul_scale", 0), GNodeArg(GNA_IN, "S84_Mul_shift", 0), GNodeArg(GNA_IN, "S84_Infos", 0)));
    // Node S87_Conv2d_96x384x1x1 inq -13.43<(i8-0.00)*0.10489037<13.32 weightsq chan<(i8-0.00)*chan<chan outq -7.86<(i8-0.00)*0.06141714<7.80 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S87_Conv2d_96x384x1x1", Bindings(7, GNodeArg(GNA_IN, "S84_Output", 0), GNodeArg(GNA_IN, "Stdconstant38", 0), GNodeArg(GNA_IN, "Stdconstant65", 0), GNodeArg(GNA_OUT, "S87_Output", 0), GNodeArg(GNA_IN, "S87_Mul_scale", 0), GNodeArg(GNA_IN, "S87_Mul_shift", 0), GNodeArg(GNA_IN, "S87_Infos", 0)));
    // Node S90_Conv2d_576x96x1x1_Relu inq -7.86<(i8-0.00)*0.06141714<7.80 weightsq chan<(i8-0.00)*chan<chan outq -8.65<(i8-0.00)*0.06757337<8.58 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S90_Conv2d_576x96x1x1_Relu", Bindings(7, GNodeArg(GNA_IN, "S87_Output", 0), GNodeArg(GNA_IN, "Stdconstant39", 0), GNodeArg(GNA_IN, "Stdconstant18", 0), GNodeArg(GNA_OUT, "S90_Output", 0), GNodeArg(GNA_IN, "S90_Mul_scale", 0), GNodeArg(GNA_IN, "S90_Mul_shift", 0), GNodeArg(GNA_IN, "S90_Infos", 0)));
    // Node S93_Conv2d_32x576x1x1 inq -8.65<(i8-0.00)*0.06757337<8.58 weightsq chan<(i8-0.00)*chan<chan outq -13.67<(i8-0.00)*0.10683099<13.57 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S93_Conv2d_32x576x1x1", Bindings(7, GNodeArg(GNA_IN, "S90_Output", 0), GNodeArg(GNA_IN, "Stdconstant40", 0), GNodeArg(GNA_IN, "Boxpredictorconvolutionalboxhe_319ba674", 0), GNodeArg(GNA_OUT, "S93_Output", 0), GNodeArg(GNA_IN, "S93_Mul_scale", 0), GNodeArg(GNA_IN, "S93_Mul_shift", 0), GNodeArg(GNA_IN, "S93_Infos", 0)));
    // Node CONV_2D_0_33_trans_out0 inq -13.67<(i8-0.00)*0.10683099<13.57 outq -13.67<(i8-0.00)*0.10683099<13.57
    AddNode("S94_Op_CONV_2D_0_33_trans_out0", Bindings(2, GNodeArg(GNA_IN, "S93_Output", 0), GNodeArg(GNA_OUT, "S94_Output", 0)));
    // Node S98_Conv2d_16x576x1x1_Sigmoid inq -8.65<(i8-0.00)*0.06757337<8.58 weightsq chan<(i8-0.00)*chan<chan outq -1.01<(i8-0.00)*0.00787402<1.00 forced biasesq chan<(i32-0.00)*chan<chan
    AddNode("S98_Conv2d_16x576x1x1_Sigmoid", Bindings(7, GNodeArg(GNA_IN, "S90_Output", 0), GNodeArg(GNA_IN, "Stdconstant41", 0), GNodeArg(GNA_IN, "Boxpredictorconvolutionalclass_ba179d10", 0), GNodeArg(GNA_OUT, "S98_Output", 0), GNodeArg(GNA_IN, "S98_Mul_scale", 0), GNodeArg(GNA_IN, "S98_Mul_shift", 0), GNodeArg(GNA_IN, "S98_Infos", 0)));
    // Node CONV_2D_0_35_trans_out0 inq -1.01<(i8-0.00)*0.00787402<1.00 forced outq -1.01<(i8-0.00)*0.00787402<1.00 forced
    AddNode("S99_Op_CONV_2D_0_35_trans_out0", Bindings(2, GNodeArg(GNA_IN, "S98_Output", 0), GNodeArg(GNA_OUT, "S99_Output", 0)));
    // Node S103_Conv2d_128x576x1x1_Relu inq -8.65<(i8-0.00)*0.06757337<8.58 weightsq chan<(i8-0.00)*chan<chan outq -8.40<(i8-0.00)*0.06562099<8.33 forced biasesq chan<(i32-0.00)*chan<chan
    AddNode("S103_Conv2d_128x576x1x1_Relu", Bindings(7, GNodeArg(GNA_IN, "S90_Output", 0), GNodeArg(GNA_IN, "Stdconstant42", 0), GNodeArg(GNA_IN, "Stdconstant19", 0), GNodeArg(GNA_OUT, "S103_Output", 0), GNodeArg(GNA_IN, "S103_Mul_scale", 0), GNodeArg(GNA_IN, "S103_Mul_shift", 0), GNodeArg(GNA_IN, "S103_Infos", 0)));
    // Node S106_Conv2d_256x128x3x3_Relu inq -8.40<(i8-0.00)*0.06562099<8.33 forced weightsq chan<(i8-0.00)*chan<chan outq -7.81<(i8-0.00)*0.06099729<7.75 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S106_Conv2d_256x128x3x3_Relu", Bindings(7, GNodeArg(GNA_IN, "S103_Output", 0), GNodeArg(GNA_IN, "Stdconstant43", 0), GNodeArg(GNA_IN, "13_convbias", 0), GNodeArg(GNA_OUT, "S106_Output", 0), GNodeArg(GNA_IN, "S106_Mul_scale", 0), GNodeArg(GNA_IN, "S106_Mul_shift", 0), GNodeArg(GNA_IN, "S106_Infos", 0)));
    // Node S109_Conv2d_32x256x1x1 inq -7.81<(i8-0.00)*0.06099729<7.75 weightsq chan<(i8-0.00)*chan<chan outq -13.67<(i8-0.00)*0.10683099<13.57 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S109_Conv2d_32x256x1x1", Bindings(7, GNodeArg(GNA_IN, "S106_Output", 0), GNodeArg(GNA_IN, "Stdconstant44", 0), GNodeArg(GNA_IN, "Boxpredictorconvolutionalboxhe_8bd56dc8", 0), GNodeArg(GNA_OUT, "S109_Output", 0), GNodeArg(GNA_IN, "S109_Mul_scale", 0), GNodeArg(GNA_IN, "S109_Mul_shift", 0), GNodeArg(GNA_IN, "S109_Infos", 0)));
    // Node CONV_2D_0_39_trans_out0 inq -13.67<(i8-0.00)*0.10683099<13.57 outq -13.67<(i8-0.00)*0.10683099<13.57
    AddNode("S110_Op_CONV_2D_0_39_trans_out0", Bindings(2, GNodeArg(GNA_IN, "S109_Output", 0), GNodeArg(GNA_OUT, "S110_Output", 0)));
    // Node S114_Conv2d_16x256x1x1_Sigmoid inq -7.81<(i8-0.00)*0.06099729<7.75 weightsq chan<(i8-0.00)*chan<chan outq -1.01<(i8-0.00)*0.00787402<1.00 forced biasesq chan<(i32-0.00)*chan<chan
    AddNode("S114_Conv2d_16x256x1x1_Sigmoid", Bindings(7, GNodeArg(GNA_IN, "S106_Output", 0), GNodeArg(GNA_IN, "Stdconstant45", 0), GNodeArg(GNA_IN, "Boxpredictorconvolutionalclass_24772bd8", 0), GNodeArg(GNA_OUT, "S114_Output", 0), GNodeArg(GNA_IN, "S114_Mul_scale", 0), GNodeArg(GNA_IN, "S114_Mul_shift", 0), GNodeArg(GNA_IN, "S114_Infos", 0)));
    // Node CONV_2D_0_41_trans_out0 inq -1.01<(i8-0.00)*0.00787402<1.00 forced outq -1.01<(i8-0.00)*0.00787402<1.00 forced
    AddNode("S115_Op_CONV_2D_0_41_trans_out0", Bindings(2, GNodeArg(GNA_IN, "S114_Output", 0), GNodeArg(GNA_OUT, "S115_Output", 0)));
    // Node S119_Conv2d_128x256x1x1_Relu inq -7.81<(i8-0.00)*0.06099729<7.75 weightsq chan<(i8-0.00)*chan<chan outq -6.94<(i8-0.00)*0.05421366<6.89 forced biasesq chan<(i32-0.00)*chan<chan
    AddNode("S119_Conv2d_128x256x1x1_Relu", Bindings(7, GNodeArg(GNA_IN, "S106_Output", 0), GNodeArg(GNA_IN, "Stdconstant46", 0), GNodeArg(GNA_IN, "Stdconstant20", 0), GNodeArg(GNA_OUT, "S119_Output", 0), GNodeArg(GNA_IN, "S119_Mul_scale", 0), GNodeArg(GNA_IN, "S119_Mul_shift", 0), GNodeArg(GNA_IN, "S119_Infos", 0)));
    // Node S122_Conv2d_256x128x3x3_Relu inq -6.94<(i8-0.00)*0.05421366<6.89 forced weightsq chan<(i8-0.00)*chan<chan outq -7.80<(i8-0.00)*0.06097502<7.74 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S122_Conv2d_256x128x3x3_Relu", Bindings(7, GNodeArg(GNA_IN, "S119_Output", 0), GNodeArg(GNA_IN, "Stdconstant47", 0), GNodeArg(GNA_IN, "15_convbias", 0), GNodeArg(GNA_OUT, "S122_Output", 0), GNodeArg(GNA_IN, "S122_Mul_scale", 0), GNodeArg(GNA_IN, "S122_Mul_shift", 0), GNodeArg(GNA_IN, "S122_Infos", 0)));
    // Node S125_Conv2d_32x256x1x1 inq -7.80<(i8-0.00)*0.06097502<7.74 weightsq chan<(i8-0.00)*chan<chan outq -13.67<(i8-0.00)*0.10683099<13.57 biasesq chan<(i32-0.00)*chan<chan
    AddNode("S125_Conv2d_32x256x1x1", Bindings(7, GNodeArg(GNA_IN, "S122_Output", 0), GNodeArg(GNA_IN, "Stdconstant48", 0), GNodeArg(GNA_IN, "Boxpredictorconvolutionalboxhe_db4937ca", 0), GNodeArg(GNA_OUT, "S125_Output", 0), GNodeArg(GNA_IN, "S125_Mul_scale", 0), GNodeArg(GNA_IN, "S125_Mul_shift", 0), GNodeArg(GNA_IN, "S125_Infos", 0)));
    // Node CONV_2D_0_45_trans_out0 inq -13.67<(i8-0.00)*0.10683099<13.57 outq -13.67<(i8-0.00)*0.10683099<13.57
    AddNode("S126_Op_CONV_2D_0_45_trans_out0", Bindings(2, GNodeArg(GNA_IN, "S125_Output", 0), GNodeArg(GNA_OUT, "S126_Output", 0)));
    // Node S132_Conv2d_16x256x1x1_Sigmoid inq -7.80<(i8-0.00)*0.06097502<7.74 weightsq chan<(i8-0.00)*chan<chan outq -1.01<(i8-0.00)*0.00787402<1.00 forced biasesq chan<(i32-0.00)*chan<chan
    AddNode("S132_Conv2d_16x256x1x1_Sigmoid", Bindings(7, GNodeArg(GNA_IN, "S122_Output", 0), GNodeArg(GNA_IN, "Stdconstant49", 0), GNodeArg(GNA_IN, "Boxpredictorconvolutionalclass_20f59186", 0), GNodeArg(GNA_OUT, "S132_Output", 0), GNodeArg(GNA_IN, "S132_Mul_scale", 0), GNodeArg(GNA_IN, "S132_Mul_shift", 0), GNodeArg(GNA_IN, "S132_Infos", 0)));
    // Node CONV_2D_0_49_trans_out0 inq -1.01<(i8-0.00)*0.00787402<1.00 forced outq -1.01<(i8-0.00)*0.00787402<1.00 forced
    AddNode("S133_Op_CONV_2D_0_49_trans_out0", Bindings(2, GNodeArg(GNA_IN, "S132_Output", 0), GNodeArg(GNA_OUT, "S133_Output", 0)));
    // Node CUSTOM_0_53 offsetsq -13.67<(i8-0.00)*0.10683099<13.57 scoresq -1.01<(i8-0.00)*0.00787402<1.00 forced anchorsq -1.00<(i8-0.00)*0.00777559<0.99 outboxesq -2.00<(i16-0.00)*0.00006104<2.00
    AddNode("S137_Op_CUSTOM_0_53", Bindings(8, GNodeArg(GNA_IN, "S128_Output", 0), GNodeArg(GNA_IN, "S135_Output", 0), GNodeArg(GNA_IN, "Stdconstant2", 0), GNodeArg(GNA_OUT, "Output_1", 0), GNodeArg(GNA_OUT, "Output_2", 0), GNodeArg(GNA_OUT, "Output_3", 0), GNodeArg(GNA_IN, "S137_Ssd_scales", 0), GNodeArg(GNA_IN, "S137_Ssd_norms", 0)));
    CloseGraph();
#endif
}

int main(int argc, char **argv)

{
    if (TilerParseOptions(argc, argv)) {
            printf("Failed to initialize or incorrect output arguments directory.\n"); return 1;
    }
    lynredModel(64000, 300000, 8000000, 20*1024*1024);
    GenerateTilingCode();
    return 0;
}
