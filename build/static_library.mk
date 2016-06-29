
TARGET_ := $(LOCAL_MODULE)

LOCAL_BUILD_MODULE := $(OUT_DIR)/libs/$(LOCAL_MODULE)/$(LOCAL_MODULE).a

include $(BUILD_SYSTEM)/binary.mk

$(TARGET_) : $(LOCAL_BUILD_MODULE)

$(LOCAL_BUILD_MODULE) : $(all_objects)
	$(transform-o-to-static-lib)