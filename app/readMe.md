# CALIBRATION
## mmake
    cd dataset_tools/gap8_capture_raw_images
    make clean all run
## copy cal file
    cp -p offset_img/Calibration.bin ../../gap8_project_v2/Calibration/{BOARD_NUM}/

# GAPFLOW
## NNTOOL
    set debug true
### open model
    open path/to/model.tflite -q
    adjust
    fusion --scale8
### [optional] normalization
    set input_norm_func "x: x/128-1"
    imageformat input_1
### quantization
    aquant -s SQ8 samples/*.p* 
### generate and save model to c file
    gen ATModel.c -t -T path/to/tensor
### [optional] save above command history to file
    save_state
###  
    nntool -s nntool_script.txt(json) path/to/model.tflite [-q]

## AUTOTILER
#### 1. comment out CNN_Copy_Generators.h
#### 2. change CNN_Generators.c
#### 3. change out CNN_Copy_Generators.c


### from ATModel.c, compile and run following code in linux shell
    gcc ATModel.c -g -o GenTile -I. -I${TILER_INC} -I${TILER_EMU_INC} -I${TILER_CNN_GENERATOR_PATH} -I${TILER_CNN_GENERATOR_PATH_SQ8} -I${NNTOOL_GENERATOR_PATH} -I${TILER_CNN_KERNEL_PATH} -I${TILER_CNN_KERNEL_PATH_SQ8} -I${NNTOOL_KERNELS_PATH} ${TILER_LIB} ${TILER_CNN_GENERATOR_PATH}/CNN_Generator_Util.c ${TILER_CNN_GENERATOR_PATH_SQ8}/CNN_Generators_SQ8.c
    ######## ${NNTOOL_GENERATOR_PATH}/nntool_extra_generators.c (do not include this variable) ########

### All the symbols are defined when the sdk is sourced. You can look at their values with following
    env | grep TILER
    env | grep NNTOOL

### run AT executable(Gentile). '.' is the output path.
    export L1_MEMORY=64000
    export L2_MEMORY=300000
    export L3_MEMORY=8000000
    ./Gentile -o . -c . --L1 ${L1_MEMORY} --L2 ${L2_MEMORY} --L3 ${L3_MEMORY}

### It's suggested that you automate this process with usage of a build tool such as make, to see some templates you can look in the examples/nntool folder inside the GAP_SDK_HOME.


imageformat input_1 bw8 offset_int8 set l3_ram_ext_managed True set l2_ram_ext_managed False set graph_reorder_constant_in true set graph_const_exec_from_flash true set graph_warm_construct true set input_norm_func "x: x"
# ssd_setter max_bb_before_nms 200
# set graph_trace_exec true
# set graph_produce_node_names true
# set graph_produce_operinfos true
# set graph_monitor_cycles true
# set graph_dump_tensor 4
# set graph_dump_one_node S127_Op_CONV_2D_0_45_TOUT_0
# set graph_dump_one_node S137_Act_Hsigmoid
# This line is to dump all layer output
# set graph_dump_tensor 7

