## SETUP
    sudo apt-get install -y autoconf automake bison build-essential cmake curl doxygen flex git gtkwave libftdi-dev libftdi1 libjpeg-dev libsdl2-dev libsdl2-ttf-dev \
    libsndfile1-dev graphicsmagick-libmagick-dev-compat libtool libusb-1.0-0-dev pkg-config python3-pip rsync scons texinfo wget
    
## OPEN OCD
    git clone https://github.com/GreenWaves-Technologies/gap8_openocd.git
    cd gap8_openocd
    ./bootstrap
    ./configure --program-prefix=gap8- --prefix=/usr --datarootdir=/usr/share/gap8-openocd
    make -j
    sudo make -j install
    sudo cp /usr/share/gap8-openocd/openocd/contrib/60-openocd.rules /etc/udev/rules.d
    sudo udevadm control --reload-rules && sudo udevadm trigger
    sudo usermod -a -G dialout $USER
    export GAPY_OPENOCD_CABLE=interface/ftdi/olimex-arm-usb-ocd-h.cfg
    
## TOOLCHAIN
    git clone https://github.com/GreenWaves-Technologies/gap_riscv_toolchain_ubuntu_18.git
    cd gap_riscv_toolchain_ubuntu_18
    ./install.sh
    
## SDK
    git clone https://github.com/GreenWaves-Technologies/gap_sdk.git
    cd gap_sdk
    source config/gapoc_b_v2.sh
    pip install -r tools/nntool/requirements.txt
    pip install -r requirements.txt
    make sdk
