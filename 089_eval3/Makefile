CFLAGS=-std=gnu99 -pedantic -Wall -Werror -ggdb3
PROGS=cyoa-step1 cyoa-step2 cyoa-step3 cyoa-step4
OBJS=$(patsubst %,%.o,$(PROGS)) rand_story.o
all: $(PROGS)
cyoa-step%: cyoa-step%.o page.o book.o
	g++ -o $@ $^
%.o: %.c
	g++ $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -f *~ $(PROGS) $(OBJS)

page.o: page.h
book.o: book.h
