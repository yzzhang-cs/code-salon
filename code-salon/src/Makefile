CC = g++
CFLAGS = -std=c++11

cpp_salon: cpp_stylist.o
	$(CC) $(CFLAGS) -o cpp_salon cpp_salon.cpp cpp_stylist.o

cpp_stylist.o : 
	$(CC) $(CFLAGS) -c cpp_stylist.cpp

clean:
	rm -f *.o cpp_salon