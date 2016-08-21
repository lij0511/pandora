

cppflags := $(LOCAL_CPPFLAGS)
cppflags += -D_GNU_SOURCE

builddir := out

testlibs = -L./out/libs/libpola -lpola   ./third_party/fbxsdk/lib/$(ARCH)/libfbxsdk.a

syslibs = -lpthread -lX11 -lGL -lGLEW  -lGLU -lglut -ldl

c_includes = ./include \
	third_party/freetype/include \
	third_party/zlib \
	third_party/libpng \
	third_party/libjpeg \
	third_party/icu/source/common \
	third_party/harfbuzz_ng/src \
	extensions/ParticleUniverse \
	third_party/fbxsdk/include \
	
includes := $(addprefix -I , $(c_includes))

thread_test: test/thread_test.cpp
	$(CXX) $^ $(testlibs) $(syslibs) -o $(builddir)/$@ $(includes) $(cppflags) 

gl_test: test/gl_test.cpp
	$(CXX) $^ $(testlibs) $(syslibs) -o $(builddir)/$@ $(includes) $(cppflags)

gl2d_test: test/gl2d_test.cpp
	$(CXX) $^ $(testlibs) $(syslibs) -o $(builddir)/$@ $(includes) $(cppflags)

lights_test: test/lights_test.cpp
	$(CXX) $^ $(testlibs) $(syslibs) -o $(builddir)/$@ $(includes) $(cppflags)
	
md2_loader_test: test/md2_loader_test.cpp
	$(CXX) $^ $(testlibs) $(syslibs) -o $(builddir)/$@ $(includes) $(cppflags)
	
v_test: test/v_test.cpp
	$(CXX) $^ $(testlibs) $(syslibs) -o $(builddir)/$@ $(includes) $(cppflags)

io_test: test/io_test.cpp
	$(CXX) $^ $(testlibs) $(syslibs) -o $(builddir)/$@ $(includes) $(cppflags)

image_test: test/image_test.cpp
	$(CXX) $^ $(testlibs) $(syslibs) -o $(builddir)/$@ $(includes) $(cppflags)

blend_test: test/blend_test.cpp
	$(CXX) $^ $(testlibs) $(syslibs) -o $(builddir)/$@ $(includes) $(cppflags)

rptest: test/rptest.cpp
	$(CXX) $^ $(testlibs) $(syslibs) -o $(builddir)/$@ $(includes) $(cppflags)

fbx_loader_test: test/fbx_loader_test.cpp test/Common.cpp
	$(CXX) $^ $(testlibs) $(syslibs) -o $(builddir)/$@ $(includes) $(cppflags)
	
test: thread_test gl_test lights_test md2_loader_test v_test io_test image_test blend_test rptest
