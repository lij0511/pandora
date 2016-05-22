
cflags = -lpthread -lX11 -lGL -lGLEW -D_GNU_SOURCE

testlibs = $(builddir)/libpolaris.so

thread_test: test/thread_test.cpp
	$(CXX) $(CXXFLAGS) $(CFLAGS) $^ $(testlibs) -o $(builddir)/$@ $(cflags) $(INCLUDEFLAGS)

gl_test: test/gl_test.cpp
	$(CXX) $(CXXFLAGS) $(CFLAGS) $^ $(testlibs) -o $(builddir)/$@ $(cflags) -lGLU -lglut $(INCLUDEFLAGS)
	
md2_loader_test: test/md2_loader_test.cpp
	$(CXX) $(CXXFLAGS) $(CFLAGS) $^ $(testlibs) -o $(builddir)/$@ $(cflags) -lGLU -lglut $(INCLUDEFLAGS)
	
test: thread_test
