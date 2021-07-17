CC = g++
CFLAGS = -std=c++11 -Wextra -Wall -pedantic
LDLIBS = -lreadline

NAME = interp
SRC = interp.cpp onp.cpp
DEPS = onp.hpp
OBJS = interp.o onp.o

all: $(NAME)

debug: CFLAGS += -fsanitize=address -fsanitize=leak
debug: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDLIBS)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o

distclean: clean
	rm -f $(NAME)
