include build/core.mk

LOCAL_PATH:= ./
include $(CLEAR_VARS)

LOCAL_C_INCLUDES = ./src ./include \
	third_party/freetype/include \
	third_party/zlib \
	third_party/libpng \
	third_party/libjpeg \
	third_party/icu/source/common \

CC = gcc
CXX = g++

LOCAL_CPPFLAGS :=	-O2 -g -Wall -Wno-unused-function -Wno-strict-aliasing -fmessage-length=0  -fPIC -std=c++11 

LOCAL_SRC_FILES := $(shell find src/ -name '*.cpp')
LOCAL_MODULE := libpola

include $(BUILD_STATIC_LIBRARY)

.PHONY: clean
	#@find src/core -name '*.cpp' | xargs echo;
clean:
	@if [ -d out ]; then find out/ -name '*.o' -o -name '*.a' -o -name '*.d' | xargs rm -rf; fi

cleanall:
	@if [ -d out ]; then find out/ -name '*' | xargs rm -rf; fi
	
