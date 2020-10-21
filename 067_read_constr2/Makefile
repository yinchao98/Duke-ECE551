CFLAGS=-Wall -Werror -pedantic -ggdb3
OBJS=code.o
PROGRAM=code

$(PROGRAM): $(OBJS)
	g++ $(CFLAGS) -o $@ $(OBJS)

%.o: %.c code.h
	g++ -c $(CFLAGS) $<

clean:
	rm -f $(OBJS) $(PROGRAM) *~
