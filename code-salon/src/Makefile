CC = g++
SWIG = swig
SWIG_FLAGS = -c++ -python
CFLAGS = -std=c++11 -fPIC
PYTHONI = -I/usr/include/python3.6
PYTHONL = -Xlinker -export-dynamic

all: _cpp_stylist.so

cpp_salon: cpp_stylist.o cpp_salon.o
	$(CC) $(CFLAGS) -o cpp_salon cpp_salon.o cpp_stylist.o

_cpp_stylist.so: cpp_stylist_wrap.o cpp_stylist.o
	$(CC) $(PYTHONL) -shared cpp_stylist.o cpp_stylist_wrap.o -o _cpp_stylist.so
	
_cpp_salon.so: cpp_salon_wrap.o cpp_salon.o
	$(CC) $(PYTHONL) -shared cpp_salon.o cpp_salon_wrap.o -o _cpp_salon.so
	
cpp_salon.o :
	$(CC) $(CFLAGS) -c cpp_salon.cpp
	
cpp_salon_wrap.o: cpp_salon_wrap.cxx cpp_stylist.o
	$(CC) $(CFLAGS) -c cpp_salon_wrap.cxx $(PYTHONI)

cpp_stylist_wrap.o: cpp_stylist_wrap.cxx
	$(CC) $(CFLAGS) -c cpp_stylist_wrap.cxx $(PYTHONI)

cpp_salon_wrap.cxx:
	$(SWIG) $(SWIG_FLAGS) cpp_salon.i
	
cpp_stylist_wrap.cxx:
	$(SWIG) $(SWIG_FLAGS) cpp_stylist.i

cpp_stylist.o : 
	$(CC) $(CFLAGS) -c cpp_stylist.cpp

clean:
	rm -f *.o cpp_salon cpp_stylist.py *.so *_wrap.cxx *.pyc
	
run: cpp_salon
	./cpp_salon