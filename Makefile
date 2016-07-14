CC = gcc
CXX = g++
AR = ar

-include build/core.mk

LOCAL_PATH:=$(call my-dir)
include $(CLEAR_VARS)

LOCAL_C_INCLUDES = ./src ./include \
	third_party/freetype/include \
	third_party/zlib \
	third_party/libpng \
	third_party/libjpeg \
	third_party/icu/source/common \

LOCAL_CPPFLAGS :=	-O2 -g -Wall -Wno-unused-function -Wno-strict-aliasing -fmessage-length=0  -fPIC -std=c++11 
LOCAL_CFLAGS :=  -O2 -g -Wall -fmessage-length=0 -fPIC
LOCAL_CPPFLAGS += -DPOLA_GL -DPOLA_LINUX_X11

LOCAL_SRC_FILES := $(shell find src/ -name '*.cpp')
include third_party/third_party.mk

LOCAL_MODULE := libpola

all : libpola

include $(BUILD_STATIC_LIBRARY)

include test/test.mk

.PHONY: clean
	#@find src/core -name '*.cpp' | xargs echo;
clean:
	@if [ -d out ]; then find out/ -name '*.o' -o -name '*.a' -o -name '*.d'  -o -name '*.P' | xargs rm -rf; fi

cleanall:
	@if [ -d out ]; then find out/ -name '*' | xargs rm -rf; fi
	
