LOCAL_PATH:=$(call my-dir)
include $(CLEAR_VARS)

define all-cpp-files-under
 $(patsubst ./%,%,$(shell cd $(LOCAL_PATH) ; find $(1) -name "*.cpp" -and -not -name ".*") )
endef

define all-c-files-under
 $(patsubst ./%,%,$(shell cd $(LOCAL_PATH) ; find $(1) -name "*.c" -and -not -name ".*") )
endef

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/include/ \
	$(LOCAL_PATH)/src/ \
	$(LOCAL_PATH)/third_party/freetype/include/ \
	$(LOCAL_PATH)/third_party/zlib/ \
	$(LOCAL_PATH)/third_party/libpng/ \
	$(LOCAL_PATH)/third_party/libjpeg/ \
	$(LOCAL_PATH)/third_party/icu/source/common/ \
	
LOCAL_CPPFLAGS :=	-O2 -g -Wall -Wno-unused-function -Wno-unused-parameter -Wno-strict-aliasing -fmessage-length=0  -fPIC -std=c++11 
#LOCAL_CFLAGS :=  -O2 -g -Wall -fmessage-length=0 -fPIC
LOCAL_CPPFLAGS += -DPOLA_GLES

LOCAL_CPPFLAGS += -fexceptions -frtti

LOCAL_SRC_FILES := $(sort $(call all-cpp-files-under, src/)) \


ft2_files = third_party/freetype/src/autofit/autofit.c\
	third_party/freetype/src/base/ftbase.c\
	third_party/freetype/src/base/ftbbox.c\
	third_party/freetype/src/base/ftbdf.c\
	third_party/freetype/src/base/ftbitmap.c\
	third_party/freetype/src/base/ftcid.c\
	third_party/freetype/src/base/ftdebug.c\
	third_party/freetype/src/base/ftfstype.c\
	third_party/freetype/src/base/ftgasp.c\
	third_party/freetype/src/base/ftglyph.c\
	third_party/freetype/src/base/ftgxval.c\
	third_party/freetype/src/base/ftinit.c\
	third_party/freetype/src/base/ftlcdfil.c\
	third_party/freetype/src/base/ftmm.c\
	third_party/freetype/src/base/ftotval.c\
	third_party/freetype/src/base/ftpatent.c\
	third_party/freetype/src/base/ftpfr.c\
	third_party/freetype/src/base/ftstroke.c\
	third_party/freetype/src/base/ftsynth.c\
	third_party/freetype/src/base/ftsystem.c\
	third_party/freetype/src/base/fttype1.c\
	third_party/freetype/src/base/ftwinfnt.c\
	third_party/freetype/src/bdf/bdf.c\
	third_party/freetype/src/bzip2/ftbzip2.c\
	third_party/freetype/src/cache/ftcache.c\
	third_party/freetype/src/cff/cff.c\
	third_party/freetype/src/cid/type1cid.c\
	third_party/freetype/src/gxvalid/gxvalid.c\
	third_party/freetype/src/gzip/ftgzip.c\
	third_party/freetype/src/lzw/ftlzw.c\
	third_party/freetype/src/otvalid/otvalid.c\
	third_party/freetype/src/pcf/pcf.c\
	third_party/freetype/src/pfr/pfr.c\
	third_party/freetype/src/psaux/psaux.c\
	third_party/freetype/src/pshinter/pshinter.c\
	third_party/freetype/src/psnames/psnames.c\
	third_party/freetype/src/raster/raster.c\
	third_party/freetype/src/sfnt/sfnt.c\
	third_party/freetype/src/smooth/smooth.c\
	third_party/freetype/src/truetype/truetype.c\
	third_party/freetype/src/type1/type1.c\
	third_party/freetype/src/type42/type42.c\
	third_party/freetype/src/winfonts/winfnt.c

LOCAL_CFLAGS += -DFT2_BUILD_LIBRARY

zlib_files := \
	third_party/zlib/adler32.c \
	third_party/zlib/compress.c \
	third_party/zlib/crc32.c \
	third_party/zlib/deflate.c \
	third_party/zlib/gzclose.c \
	third_party/zlib/gzlib.c \
	third_party/zlib/gzread.c \
	third_party/zlib/gzwrite.c \
	third_party/zlib/infback.c \
	third_party/zlib/inflate.c \
	third_party/zlib/inftrees.c \
	third_party/zlib/inffast.c \
	third_party/zlib/trees.c \
	third_party/zlib/uncompr.c \
	third_party/zlib/zutil.c

png_files = third_party/libpng/png.c\
	third_party/libpng/pngerror.c\
	third_party/libpng/pngread.c\
	third_party/libpng/pngrutil.c\
	third_party/libpng/pngrio.c\
	third_party/libpng/pngtrans.c\
	third_party/libpng/pngrtran.c\
	third_party/libpng/pngset.c\
	third_party/libpng/pngwrite.c\
	third_party/libpng/pngmem.c\
	third_party/libpng/pngget.c\
	third_party/libpng/pngwutil.c\
	third_party/libpng/pngwio.c\
	third_party/libpng/pngwtran.c

LOCAL_ARM_MODE := arm
#LOCAL_CFLAGS += -std=gnu89  -DTARGET_ARCH_ARM -ftrapv
#LOCAL_CFLAGS_arm := -DPNG_ARM_NEON_OPT=2 -fno-slp-vectorize

LOCAL_SRC_FILES += \
	third_party/libpng/arm/arm_init.c \
	third_party/libpng/arm/filter_neon.S \
	third_party/libpng/arm/filter_neon_intrinsics.c

jpeg_files := \
	third_party/libjpeg/jcapimin.c\
	third_party/libjpeg/jcapistd.c\
	third_party/libjpeg/jccoefct.c\
	third_party/libjpeg/jccolor.c\
	third_party/libjpeg/jcdctmgr.c\
	third_party/libjpeg/jchuff.c\
	third_party/libjpeg/jcinit.c\
	third_party/libjpeg/jcmainct.c\
	third_party/libjpeg/jcmarker.c\
	third_party/libjpeg/jcmaster.c\
	third_party/libjpeg/jcomapi.c\
	third_party/libjpeg/jcparam.c\
	third_party/libjpeg/jcprepct.c\
	third_party/libjpeg/jcsample.c\
	third_party/libjpeg/jctrans.c\
	third_party/libjpeg/jdapimin.c\
	third_party/libjpeg/jdapistd.c\
	third_party/libjpeg/jdatadst.c\
	third_party/libjpeg/jdatasrc.c\
	third_party/libjpeg/jdcoefct.c\
	third_party/libjpeg/jdcolor.c\
	third_party/libjpeg/jddctmgr.c\
	third_party/libjpeg/jdhuff.c\
	third_party/libjpeg/jdinput.c\
	third_party/libjpeg/jdmainct.c\
	third_party/libjpeg/jdmarker.c\
	third_party/libjpeg/jdmaster.c\
	third_party/libjpeg/jdmerge.c\
	third_party/libjpeg/jdpostct.c\
	third_party/libjpeg/jdsample.c\
	third_party/libjpeg/jdtrans.c\
	third_party/libjpeg/jerror.c\
	third_party/libjpeg/jfdctflt.c\
	third_party/libjpeg/jfdctfst.c\
	third_party/libjpeg/jfdctint.c\
	third_party/libjpeg/jidctflt.c\
	third_party/libjpeg/jidctfst.c\
	third_party/libjpeg/jidctint.c\
	third_party/libjpeg/jquant1.c\
	third_party/libjpeg/jquant2.c\
	third_party/libjpeg/jutils.c\
	third_party/libjpeg/jmemmgr.c\
	third_party/libjpeg/jmemnobs.c\
	third_party/libjpeg/jdarith.c\
	third_party/libjpeg/jcarith.c\
	third_party/libjpeg/jaricom.c

icu_files := $(sort $(call all-cpp-files-under, third_party/icu/source/common))
icu_files += $(sort $(call all-c-files-under, third_party/icu/source/common))
icu_files +=  third_party/icu/source/stubdata/stubdata.c
LOCAL_CFLAGS += -DU_COMMON_IMPLEMENTATION
LOCAL_CPPFLAGS += -DU_COMMON_IMPLEMENTATION
LOCAL_LDLIBS := -ldl

LOCAL_SRC_FILES += $(ft2_files) \
	$(zlib_files) \
	$(png_files) \
	$(jpeg_files) \
	$(icu_files) \
	

LOCAL_MODULE := libpola

LOCAL_SHARED_LIBRARIES := \
	libc++ \
	libGLESv2 \
	libGLESv1_CM \
	libdl \

LOCAL_C_INCLUDES += \
	$(LOCAL_PATH)/ \
	$(TOP)/bionic \
	external/libcxx/include \
	
include $(BUILD_SHARED_LIBRARY)