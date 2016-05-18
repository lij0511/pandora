
cflags = -lpthread -lX11 -lGL -lGLEW -D_GNU_SOURCE

testlibs = $(builddir)/libpolaris.so

thread_test: test/thread_test.cpp
	$(CXX) $(CXXFLAGS) $(CFLAGS) $^ $(testlibs) -o $(builddir)/$@ $(cflags) $(INCLUDEFLAGS)
	
test: thread_test
