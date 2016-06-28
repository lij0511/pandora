
TARGET_ := $(LOCAL_MODULE).a

intermediates := $(OUT_DIR)/intermediates/$(LOCAL_MODULE)

PRIVATE_C_INCLUDES := $(addprefix -I , $(LOCAL_C_INCLUDES))

c_sources := $(filter %.c,$(LOCAL_SRC_FILES))
c_objects := $(addprefix $(intermediates)/,$(c_sources:.c=.o))

ifneq ($(strip $(c_objects)),)
$(c_objects): $(intermediates)/%.o: \
	$(LOCAL_PATH)/%.c |
	@mkdir -p $(dir $@)
	$(CC) $(LOCAL_CFLAGS) -o $@ -c $< $(PRIVATE_C_INCLUDES)
#-include $(cpp_objects:%.o=%.d)
endif

cpp_sources := $(filter %.cpp,$(LOCAL_SRC_FILES))
cpp_objects := $(addprefix $(intermediates)/,$(cpp_sources:.cpp=.o))

ifneq ($(strip $(cpp_objects)),)
$(cpp_objects): $(intermediates)/%.o: \
	$(LOCAL_PATH)/%.cpp |
	@mkdir -p $(dir $@)
	$(CXX) $(LOCAL_CPPFLAGS) -o $@ -c $< $(PRIVATE_C_INCLUDES)
#-include $(cpp_objects:%.o=%.d)
endif

$(TARGET_) : $(c_objects)
$(TARGET_) : $(cpp_objects)
