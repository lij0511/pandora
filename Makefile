CC = gcc
CXX = g++
AR = ar

BITS = $(shell getconf LONG_BIT)
M64 = 
ARCH = x86
ifeq ($(BITS),32)
    M64 = -m32
else
    ifeq ($(BITS),64)
        M64 = -m64
        ARCH = x64
    else
    endif
endif

-include build/core.mk

LOCAL_PATH:=$(call my-dir)
include $(CLEAR_VARS)

LOCAL_C_INCLUDES = ./src ./include \
	third_party/freetype/include \
	third_party/zlib \
	third_party/libpng \
	third_party/libjpeg \
	third_party/icu/source/common \
	third_party/harfbuzz_ng/src \
	extensions/ParticleUniverse \
	third_party/fbxsdk/include \

LOCAL_CPPFLAGS :=	-O2 -g -Wall -Wno-unused-function -Wno-strict-aliasing -fmessage-length=0  -fPIC -std=c++11 $(M64)
LOCAL_CFLAGS :=  -O2 -g -Wall -fmessage-length=0 -fPIC $(M64)
LOCAL_CPPFLAGS += -DPOLA_GL -DPOLA_LINUX_X11
LOCAL_CPPFLAGS += -DMESH_LOADER_FBX

LOCAL_SRC_FILES := $(shell find src/ -name '*.cpp')
LOCAL_SRC_FILES += $(shell find extensions/ParticleUniverse/ -name '*.cpp')
include third_party/third_party.mk

LOCAL_MODULE := libpola

all : libpola

include $(BUILD_STATIC_LIBRARY)

include test/test.mk

.PHONY: clean
	#@find src/core -name '*.cpp' | xargs echo;
clean:
	@if [ -d out ]; then find out/ -name '*' | xargs rm -rf; fi
	
