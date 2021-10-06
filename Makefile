CC = g++
CFLAGS = -std=c++11 -Wextra -Wall -pedantic
LDLIBS = -lreadline

NAME = interp
# SRC = interp.cpp rpn.cpp
DEPS = rpn.hpp
OBJS = interp.o rpn.o

all: $(NAME)

debug: CFLAGS += -g -Og -fsanitize=address -fsanitize=leak
debug: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDLIBS)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o

distclean: clean
	rm -f $(NAME)
