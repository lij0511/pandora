
cflags = -lpthread -lX11 -lGL -lGLEW -D_GNU_SOURCE

testlibs = $(builddir)/libpolaris.so $(builddir)/libft2.so $(builddir)/libpng.so $(builddir)/libjpeg.so $(builddir)/libz.so $(builddir)/libicu.so

thread_test: test/thread_test.cpp
	$(CXX) $(CXXFLAGS) $(CFLAGS) $^ $(testlibs) -o $(builddir)/$@ $(cflags) $(INCLUDEFLAGS)

gl_test: test/gl_test.cpp
	$(CXX) $(CXXFLAGS) $(CFLAGS) $^ $(testlibs) -o $(builddir)/$@ $(cflags) -lGLU -lglut $(INCLUDEFLAGS)
	
md2_loader_test: test/md2_loader_test.cpp
	$(CXX) $(CXXFLAGS) $(CFLAGS) $^ $(testlibs) -o $(builddir)/$@ $(cflags) -lGLU -lglut $(INCLUDEFLAGS)
	
test: thread_test
