
TOPDIR := .
BUILD_SYSTEM := $(TOPDIR)/build
OUT_DIR := $(TOPDIR)/out

# Figure out where we are.
define my-dir
$(strip \
  $(eval LOCAL_MODULE_MAKEFILE := $$(lastword $$(MAKEFILE_LIST))) \
  $(if $(filter $(BUILD_SYSTEM)/% $(OUT_DIR)/%,$(LOCAL_MODULE_MAKEFILE)), \
    $(error my-dir must be called before including any other makefile.) \
   , \
    $(patsubst %/,%,$(dir $(LOCAL_MODULE_MAKEFILE))) \
   ) \
 )
endef

define all-makefiles-under
$(wildcard $(1)/*/pola.mk)
endef


CLEAR_VARS := $(BUILD_SYSTEM)/clear_vars.mk
BUILD_STATIC_LIBRARY:= $(BUILD_SYSTEM)/static_library.mk