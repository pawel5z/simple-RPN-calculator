CFLAGS=-std=c++11 -Wextra -Wall -pedantic
interp : interp.o onp.o
	g++ $(CFLAGS) interp.o onp.o -o interp
interp.o : interp.cpp onp.hpp
	g++ $(CFLAGS) -c interp.cpp -o interp.o
onp.o : onp.cpp onp.hpp
	g++ $(CFLAGS) -c onp.cpp -o onp.o
