MODEL_PYTHON = python
MODEL_SUFFIX ?=
MODEL_PREFIX ?= lynred

# training models is slightly different depending on the quantization.
# 8 bit mode signed 8 bit is used, so input to models needs to be shifted 1 bit
ifeq ($(QUANT_BITS),8)
    TRAIN_SUFFIX = _8BIT
    MODEL_SQ8 = 1
else
    ifeq ($(QUANT_BITS),16)
        TRAIN_SUFFIX = _16BIT
    else
        $(error Dont know how to build with this bit width)
    endif
endif

MODEL_PYTHON = python

USE_DISP ?= 0
ifdef USE_DISP
    SDL_FLAGS = -lSDL2_ttf -LSDL2_image -lSDL2
else
    SDL_FLAGS = 
endif

# Increase this to improve accuracy
MODEL_COMMON ?= common
MODEL_COMMON_INC ?= $(GAP_SDK_HOME)/libs/gap_lib/include
MODEL_COMMON_SRC ?= $(GAP_SDK_HOME)/libs/gap_lib/img_io
MODEL_COMMON_SRC_FILES ?= ImgIO.c
MODEL_COMMON_SRCS = $(realpath $(addprefix $(MODEL_COMMON_SRC)/,$(MODEL_COMMON_SRC_FILES)))

MODEL_BUILD = BUILD_MODEL$(TRAIN_SUFFIX)
MODEL_NAME = $(MODEL_PREFIX).tflite
MODEL_TFLITE = $(MODEL_BUILD)/$(MODEL_NAME)

TENSORS_DIR = $(MODEL_BUILD)/tensors
MODEL_TENSORS = $(MODEL_BUILD)/$(MODEL_PREFIX)_L3_Flash_Const.dat

MODEL_STATE = $(MODEL_BUILD)/$(MODEL_PREFIX).json
MODEL_SRC = $(MODEL_PREFIX)Model.c
MODEL_HEADER = $(MODEL_PREFIX)Info.h
MODEL_GEN = $(MODEL_BUILD)/$(MODEL_PREFIX)Kernels 
MODEL_GEN_C = $(addsuffix .c, $(MODEL_GEN))
MODEL_GEN_CLEAN = $(MODEL_GEN_C) $(addsuffix .h, $(MODEL_GEN))
MODEL_GEN_EXE = $(MODEL_BUILD)/GenTile

MODEL_GENFLAGS_EXTRA =

EXTRA_GENERATOR_SRC =

$(info script $(NNTOOL_SCRIPT))
ifndef NNTOOL_SCRIPT
    NNTOOL_SCRIPT = model/nntool_script
endif
IMAGES = images
RM = rm -f

NNTOOL = nntool

include $(RULES_DIR)/at_common_decl.mk
