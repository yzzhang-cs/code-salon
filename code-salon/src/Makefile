CC = g++
SWIG = swig
SWIG_FLAGS = -c++ -python
CFLAGS = -std=c++11 -fPIC
PYTHONI = -I/usr/include/python3.6
PYTHONL = -Xlinker -export-dynamic
BIN_PATH = /home/vagrant/project/code-salon/bin
GO_BUILD = go build

all: _cpp_stylist.so
	cp salon.py $(BIN_PATH)
	$(GO_BUILD) -o $(BIN_PATH)/salon salon.go
	

_cpp_stylist.so: cpp_stylist_wrap.o cpp_stylist.o
	$(CC) $(PYTHONL) -shared $(BIN_PATH)/cpp_stylist.o $(BIN_PATH)/cpp_stylist_wrap.o -o $(BIN_PATH)/_cpp_stylist.so
	
cpp_salon.o :
	$(CC) $(CFLAGS) -c cpp_salon.cpp -o $(BIN_PATH)/cpp_salon.o

cpp_stylist_wrap.o: cpp_stylist_wrap.cxx
	cp *.h $(BIN_PATH)
	$(CC) $(CFLAGS) -c $(BIN_PATH)/cpp_stylist_wrap.cxx $(PYTHONI) -o $(BIN_PATH)/cpp_stylist_wrap.o
	
cpp_stylist_wrap.cxx:
	mkdir -p $(BIN_PATH)
	cp cpp_stylist.i $(BIN_PATH)
	$(SWIG) $(SWIG_FLAGS) $(BIN_PATH)/cpp_stylist.i

cpp_stylist.o : 
	$(CC) $(CFLAGS) -c cpp_stylist.cpp -o $(BIN_PATH)/cpp_stylist.o

clean:
	rm -f *.o cpp_salon cpp_stylist.py *.so *_wrap.cxx *.pyc
	rm -rf $(BIN_PATH)
	