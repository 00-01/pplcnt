## NNTOOL
### [optional]
    set debug true
### open model
    open path/to/model.tflite -q
    adjust
    fusion --scale8
### [optional] normalization
    set input_norm_func "x: x/128-1"
    imageformat input_1
### generate and save model to c file
    gen ATModel.c -t -T path/to/tensor
### [optional] save above command history to file
    save_state
### 
    nntool -s nntool_script.txt(json) path/to/model.tflite [-q]

## AUTOTILER
### from ATModel.c, compile and run following code in linux shell
    gcc ATModel.c -g -o Gentile -I. -I${TILER_INC} -I${TILER_EMU_INC} -I${TILER_CNN_GENERATOR_PATH} -I${TILER_CNN_GENERATOR_PATH_SQ8} -I${NNTOOL_GENERATOR_PATH} -I${TILER_CNN_KERNEL_PATH} -I${TILER_CNN_KERNEL_PATH_SQ8} -I${NNTOOL_KERNELS_PATH} ${TILER_LIB} ${TILER_CNN_GENERATOR_PATH}/CNN_Generator_Util.c ${TILER_CNN_GENERATOR_PATH_SQ8}/CNN_Generators_SQ8.c ${NNTOOL_GENERATOR_PATH}/nntool_extra_generators.c
    
### All the symbols are defined when the sdk is sourced. You can look at their values with following
    env | grep TILER
    env | grep NNTOOL
    
### Now the AT executable can be run:
    export L1_MEMORY=64000
    export L2_MEMORY=300000
    export L3_MEMORY=8000000
    ./Gentile -o output/path/dir -c output/path/dir --L1 ${L1_MEMORY} --L2 ${L2_MEMORY} --L3 ${L3_MEMORY}

### It's suggested that you automate this process with usage of a build tool such as make, to see some templates you can look in the examples/nntool folder inside the GAP_SDK_HOME.

https://greenwaves-technologies.com/sdk-manuals/nn_quick_start_guide/
