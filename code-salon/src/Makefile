CC = g++
SWIG = swig
SWIG_FLAGS = -c++ -python
CFLAGS = -std=c++11 -fPIC
PYTHONI = -I/usr/include/python3.6
PYTHONL = -Xlinker -export-dynamic
BIN_PATH = /home/vagrant/project/code-salon/bin
DEPS_PATH = $(BIN_PATH)/code-salon-deps
GO_BUILD = go build
SAMPLE_INPUT = /home/vagrant/project/sample_input
SAMPLE_OUTPUT = /home/vagrant/project/output

all: _cpp_stylist.so
	cp salon.py $(DEPS_PATH)
	$(GO_BUILD) -o $(BIN_PATH)/salon salon.go
	

_cpp_stylist.so: cpp_stylist_wrap.o cpp_stylist.o
	$(CC) $(PYTHONL) -shared $(DEPS_PATH)/cpp_stylist.o $(DEPS_PATH)/cpp_stylist_wrap.o -o $(DEPS_PATH)/_cpp_stylist.so
	
cpp_salon.o :
	$(CC) $(CFLAGS) -c cpp_salon.cpp -o $(DEPS_PATH)/cpp_salon.o

cpp_stylist_wrap.o: cpp_stylist_wrap.cxx
	cp *.h $(DEPS_PATH)
	$(CC) $(CFLAGS) -c $(DEPS_PATH)/cpp_stylist_wrap.cxx $(PYTHONI) -o $(DEPS_PATH)/cpp_stylist_wrap.o
	
cpp_stylist_wrap.cxx:
	mkdir -p $(DEPS_PATH)
	cp cpp_stylist.i $(DEPS_PATH)
	$(SWIG) $(SWIG_FLAGS) $(DEPS_PATH)/cpp_stylist.i

cpp_stylist.o : 
	$(CC) $(CFLAGS) -c cpp_stylist.cpp -o $(DEPS_PATH)/cpp_stylist.o

clean:
	rm -f *.o cpp_salon cpp_stylist.py *.so *_wrap.cxx *.pyc
	rm -rf $(BIN_PATH)