    set debug true
### open model
    open path/to/model.tflite -q(if file is quantized)
    adjust
    fusion --scale8
### normalization
    set input_norm_func "x: x/128-1"
    imageformat input_1
### generate and save model to c file
    gen ATModel.c -t -T path/to/tensor
### save above code to file
    save_state
### 
