    set debug true
    open location/to/file.tflite -q(if file is quantized)
    adjust
    fusion --scale8
    set input_norm_func "x: x/128-1"
    imageformat input_1
