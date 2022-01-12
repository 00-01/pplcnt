## url
    https://github.com/GreenWaves-Technologies/gap_sdk/tree/master/tools/nntool

## install here
    cd ~/gap_sdk/tools/nntool
    python3 -m pip install -r requirements.txt
    pip3 install flatbuffers tf-nightly
    nntool

## onnx
### url
    https://github.com/onnx/onnx

### install
    sudo apt install python3-pip python3-dev libprotobuf-dev protobuf-compiler
    
    export CMAKE_ARGS="-DONNX_USE_PROTOBUF_SHARED_LIBS=ON"
    git clone --recursive https://github.com/onnx/onnx.git
    cd onnx
    # prefer lite proto
    set CMAKE_ARGS=-DONNX_USE_LITE_PROTO=ON
    pip install -e .
    
    git clone https://github.com/protocolbuffers/protobuf.git
    cd protobuf
    git checkout v3.16.0
    git submodule update --init --recursive
    mkdir build_source && cd build_source
    cmake ../cmake -Dprotobuf_BUILD_SHARED_LIBS=OFF -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_INSTALL_SYSCONFDIR=/etc -DCMAKE_POSITION_INDEPENDENT_CODE=ON -Dprotobuf_BUILD_TESTS=OFF -DCMAKE_BUILD_TYPE=Release
    make -j$(nproc)
    make install
    
    pip3 install numpy protobuf six typing-extensions cmd2 setuptools bfloat16 onnx
