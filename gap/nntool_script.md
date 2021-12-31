### [optional]
    set debug true
### open model
    open path/to/model.tflite -q(if file is quantized)
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
