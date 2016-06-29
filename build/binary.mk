objs := $(OUT_DIR)/objs/$(LOCAL_MODULE)

PRIVATE_C_INCLUDES := $(addprefix -I , $(LOCAL_C_INCLUDES))

c_sources := $(filter %.c,$(LOCAL_SRC_FILES))
c_objects := $(addprefix $(objs)/,$(c_sources:.c=.o))

ifneq ($(strip $(c_objects)),)
$(c_objects): $(objs)/%.o: \
	$(LOCAL_PATH)/%.c |
	@mkdir -p $(dir $@)
	$(CC) $(LOCAL_CFLAGS) -MMD -MF $(patsubst %.o,%.d,$@) -o $@ -c $< $(PRIVATE_C_INCLUDES)
	$(transform-d-to-p)
-include $(cpp_objects:%.o=%.P)
endif

cpp_sources := $(filter %.cpp,$(LOCAL_SRC_FILES))
cpp_objects := $(addprefix $(objs)/,$(cpp_sources:.cpp=.o))

ifneq ($(strip $(cpp_objects)),)
$(cpp_objects): $(objs)/%.o: \
	$(LOCAL_PATH)/%.cpp |
	@mkdir -p $(dir $@)
	$(CXX) $(LOCAL_CPPFLAGS) -MMD -MF $(patsubst %.o,%.d,$@) -o $@ -c $< $(PRIVATE_C_INCLUDES)
	$(transform-d-to-p)
-include $(cpp_objects:%.o=%.P)
endif

all_objects := $(c_objects) $(cpp_objects)