
TOPDIR := .
BUILD_SYSTEM := $(TOPDIR)/build
OUT_DIR := $(TOPDIR)/out

hide:=@
TARGET_GLOBAL_ARFLAGS:=crs

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

###########################################################
## Commands for munging the dependency files GCC generates
###########################################################
# $(1): the input .d file
# $(2): the output .P file
define transform-d-to-p-args
$(hide) cp $(1) $(2); \
        sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
                -e '/^$$/ d' -e 's/$$/ :/' < $(1) >> $(2); \
        rm -f $(1)
endef

define transform-d-to-p
$(call transform-d-to-p-args,$(@:%.o=%.d),$(@:%.o=%.P))
endef



define _concat-if-arg2-not-empty
$(if $(2),$(hide) $(1) $(2))
endef

# Split long argument list into smaller groups and call the command repeatedly
# Call the command at least once even if there are no arguments, as otherwise
# the output file won't be created.
#
# $(1): the command without arguments
# $(2): the arguments
define split-long-arguments
$(hide) $(1) $(wordlist 1,500,$(2))
$(call _concat-if-arg2-not-empty,$(1),$(wordlist 501,1000,$(2)))
$(call _concat-if-arg2-not-empty,$(1),$(wordlist 1001,1500,$(2)))
$(call _concat-if-arg2-not-empty,$(1),$(wordlist 1501,2000,$(2)))
$(call _concat-if-arg2-not-empty,$(1),$(wordlist 2001,2500,$(2)))
$(call _concat-if-arg2-not-empty,$(1),$(wordlist 2501,3000,$(2)))
$(call _concat-if-arg2-not-empty,$(1),$(wordlist 3001,99999,$(2)))
endef

# Explicitly delete the archive first so that ar doesn't
# try to add to an existing archive.
define transform-o-to-static-lib
@mkdir -p $(dir $@)
@rm -f $@
@echo "target StaticLib: $(PRIVATE_MODULE) ($@)"
$(call split-long-arguments,$(AR) $(TARGET_GLOBAL_ARFLAGS) $(PRIVATE_ARFLAGS) $@,$(filter %.o, $^))
endef

CLEAR_VARS := $(BUILD_SYSTEM)/clear_vars.mk
BUILD_STATIC_LIBRARY:= $(BUILD_SYSTEM)/static_library.mk

MAKEFILE_LIST:=.