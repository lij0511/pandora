

cppflags := $(LOCAL_CPPFLAGS)
cppflags += -lpthread -lX11 -lGL -lGLEW -D_GNU_SOURCE

builddir := out

testlibs = -L./out/libs/libpola -lpola
includes := $(addprefix -I , $(LOCAL_C_INCLUDES))

thread_test: test/thread_test.cpp
	$(CXX) $^ $(testlibs) -o $(builddir)/$@ $(includes) $(cppflags) 

gl_test: test/gl_test.cpp
	$(CXX) $^ $(testlibs) -o $(builddir)/$@ -lGLU -lglut $(includes) $(cppflags)

gl2d_test: test/gl2d_test.cpp
	$(CXX) $^ $(testlibs) -o $(builddir)/$@ -lGLU -lglut $(includes) $(cppflags)

lights_test: test/lights_test.cpp
	$(CXX) $^ $(testlibs) -o $(builddir)/$@ -lGLU -lglut $(includes) $(cppflags)
	
md2_loader_test: test/md2_loader_test.cpp
	$(CXX) $^ $(testlibs) -o $(builddir)/$@ -lGLU -lglut $(includes) $(cppflags)
	
v_test: test/v_test.cpp
	$(CXX) $^ $(testlibs) -o $(builddir)/$@ -lGLU -lglut $(includes) $(cppflags)

io_test: test/io_test.cpp
	$(CXX) $^ $(testlibs) -o $(builddir)/$@ -lGLU -lglut $(includes) $(cppflags)

image_test: test/image_test.cpp
	$(CXX) $^ $(testlibs) -o $(builddir)/$@ -lGLU -lglut $(includes) $(cppflags)

blend_test: test/blend_test.cpp
	$(CXX) $^ $(testlibs) -o $(builddir)/$@ -lGLU -lglut $(includes) $(cppflags)
	
test: thread_test gl_test gl2d_test lights_test md2_loader_test v_test io_test image_test blend_test
