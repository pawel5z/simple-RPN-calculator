CC = g++
CFLAGS = -std=c++11 -Wextra -Wall -pedantic

NAME = interp
SRC = interp.cpp onp.cpp
DEPS = onp.hpp
OBJS = interp.o onp.o

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o

distclean: clean
	rm -f $(NAME)
