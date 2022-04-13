
ifndef GAP_SDK_HOME
    $(error Source sourceme in gap_sdk first)
endif

MODEL_VERSION=v1.1

BOARD_NUM=02
CAL=Calibration/$(BOARD_NUM)/Calibration.bin

#APP_CFLAGS += -DMODEL_VERSION=$(MODEL_VERSION)
#APP_CFLAGS += -DBOARD_NUM=$(BOARD_NUM)

## UART or BT
APP_CFLAGS += -DUART

#APP_CFLAGS += -DDRAW_BOX

#APP_CFLAGS += -DOFFSET_IMAGE_EVERY_BOOT=1

DEBUG = 0

## SHUTTERLESS_FILTER or CUSTOM_FILTER
APP_CFLAGS += -DSHUTTERLESS_FILTER

#APP_CFLAGS += -DLOOP

MODE ?= INPUT_CAMERA
ifeq ($(MODE), INPUT_FILE)
    ## test application with input file from host PC(shutterless filtering is desactivated in this mode)
    APP_CFLAGS += -DINPUT_FILE
    APP_CFLAGS += -DCI
else ifeq ($(MODE), INPUT_RAW_FILE)
    ## test prefiltering with a raw image
    APP_CFLAGS += -DINPUT_RAW_FILE
    APP_CFLAGS += -DCI
else ifeq ($(MODE), INPUT_CAMERA)
    ## Camera is default so no flags are needed
endif

## In full demo mode silent should be activated, since printfs block the execution
## if set over jtag.  To disable all printf (needed to flash application to boot from flash)
APP_CFLAGS += -DSILENT=1

#0 or 1
#SAVE_TO_PC=1

#APP_CFLAGS += -DSLEEP    ## ONLY in PulpOS

#NO_IMAGE=1    ## For debugging don't load an image. run the network with zeros

#HYPER or QSPI
EXT_MEM_TYPE ?= HYPER
APP_CFLAGS += -D$(EXT_MEM_TYPE)

APP_CFLAGS += -DNN_8BIT

pulpChip = GAP
APP = PeopleDetection
BOARD_NAME = gapoc_b
PMSIS_OS ?= pulpos
io = host
TRAINED_TFLITE_MODEL = model/$(MODEL_VERSION).tflite
MODEL_PREFIX = lynred
MODEL_SUFFIX = _8BIT
QUANT_BITS = 8

ifndef NN_BITS
    NN_BITS = 8
endif

MAKEFILE_PATH := $(dir $(realpath $(firstword $(MAKEFILE_LIST))))

$(info Building GAP8 with $(NN_BITS) bit quantization)

# training of the model is slightly different depending on quantization.
# 8 bit mode signed 8 bit is used so the input to the model needs to be shifted 1 bit
ifeq ($(EXT_MEM_TYPE), HYPER)
    NNTOOL_SCRIPT = model/nntool_script8
else
    NNTOOL_SCRIPT = model/nntool_script8_spi
endif

MAIN_STACK_SIZE = 4096

## MEMORY ALLOCATION : L1 MEMORY ALLOCATION MUST INCLUDE SPACE FOR ALLOCATED STACKS!!
ifeq '$(TARGET_CHIP_FAMILY)' 'GAP9'
    MODEL_L1_MEMORY = $(shell expr 125000 \- $(TOTAL_STACK_SIZE))
    MODEL_L2_MEMORY = 1300000
    MODEL_L3_MEMORY = 8388608
else
    MODEL_L1_MEMORY = 50000
    MODEL_L2_MEMORY = 150000
    MODEL_L3_MEMORY = 2000000
endif

ifeq ($(EXT_MEM_TYPE), HYPER)
    MODEL_L3_EXEC = hram    # hram = HyperBus RAM
    MODEL_L3_CONST = hflash    # hflash = HyperBus Flash
else
    MODEL_L3_EXEC = qspiram    # qspiram = Quad SPI RAM
    MODEL_L3_CONST = qspiflash    # qpsiflash = Quad SPI Flash
endif

#APP_SRCS += main.c ImgIO.c SSDParams.c $(MODEL_GEN_C) SSDBasicKernels.c $(MODEL_LIB_POW2) $(SSD_MODEL_GEN_C) ImageDraw.c BleNotifier.c
APP_SRCS += main.c ImgIO.c $(CNN_LIB) $(MODEL_GEN_C) ImageDraw.c BleNotifier.c

APP_CFLAGS += -w -O3 -s -mno-memcpy -fno-tree-loop-distribute-patterns
APP_CFLAGS += -I. -I$(MODEL_COMMON_INC) -I$(TILER_EMU_INC) -I$(TILER_INC) $(CNN_LIB_INCLUDE) -I$(MODEL_BUILD) -I$(TILER_CNN_KERNEL_PATH_SQ8)
APP_LDFLAGS += -L$(MAKEFILE_PATH)/shutterless/ -lshutterless -lm
APP_INC +=

ifeq ($(platform), gvsoc)
    $(info Platform is GVSOC)
    READFS_FILES = $(realpath $(MODEL_TENSORS)) $(realpath $(CAL))
else
    READFS_FILES += $(realpath $(MODEL_TENSORS)) $(realpath $(CAL))
    PLPBRIDGE_FLAGS += -f
endif

ifeq ($(SAVE_TO_PC), 1)
    APP_CFLAGS += -DSAVE_TO_PC
    prepare_debug:
	    mkdir -p dump_out_imgs
	    rm -rf dump_out_imgs/*
else
    prepare_debug:
	    true
endif


all:: model prepare_debug    # all depends on the model

clean_all:: clean_model
	rm -rf BUILD*
	rm -rf dump_out_imgs

.PHONY: all clean_all

include model_decl.mk
include model_rules.mk
include $(RULES_DIR)/pmsis_rules.mk
