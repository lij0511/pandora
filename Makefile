INCLUDEFLAGS = -I ./src

CC = gcc
CXX = g++

CXXFLAGS =	-O2 -g -Wall -Wno-unused-function -Wno-strict-aliasing -fmessage-length=0  -fPIC -std=c++11 

src := src
abs_srcdir := $(abspath $(srcdir))

builddir ?= out

obj := $(builddir)/obj
abs_obj := $(abspath $(obj))

srcs := $(shell find src/ -name '*.cpp')
objs := $(subst $(src), $(obj), $(patsubst %.cpp, %.o, $(srcs)))

sources = $(objs)
deps = $(sources:.o=.d)

# Declare the "all" target first so it is the default,
# even though we don't have the deps yet.
.PHONY: all
all: libpolaris.so

include third_party/third_party.mk
	
libpolaris.so: $(objs)
	$(CXX) $(CXXFLAGS) $(CFLAGS) -shared $^ -o $(builddir)/$@ $(INCLUDEFLAGS)

#include test/test.mk

$(src)/%.dir:
	@mkdir -p $(dir $(subst $(src),$(obj),$@))
	
$(obj)/%.o: $(src)/%.cpp $(src)/%.dir
	$(CXX) $(CXXFLAGS) $(CFLAGS) -o $@ -c $< $(INCLUDEFLAGS)

$(obj)/%.d:$(src)/%.cpp $(src)/%.dir
	@set -e; rm -f $@; $(CXX) $(CXXFLAGS) $(CFLAGS) -MM $(INCLUDEFLAGS) $< > $@.$$$$; \
	sed "s,\(.*\)\.o:,\$(patsubst %.d,%.o,$@):,g" < $@.$$$$ > $@; \
	rm -f $@.$$$$
#	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
#	rm -f $@.$$$$

deps: $(deps)
	
-include $(deps)

.PHONY: clean
	#@find src/core -name '*.cpp' | xargs echo;
clean:
	@if [ -d out ]; then find out/ -name '*.o' -o -name '*.a' -o -name '*.d' | xargs rm -rf; fi

cleanall:
	@if [ -d out ]; then find out/ -name '*' | xargs rm -rf; fi
	
