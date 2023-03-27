#compiler
CC := gcc
CFLAGS = -Wall -Werror 
LDLIBS += -lSDL2 -lSDL2_image

reader: main.o extract.o display.o
	$(CC) $(CFLAGS) -o reader main.o extract.o display.o $(LDLIBS)

main.o: main.c extract.h display.h
	$(CC) $(CFLAGS) -c -g main.c

extract.o: extract.c extract.h
	$(CC) $(CFLAGS) -c -g extract.c

display.o: display.c display.h
	$(CC) $(CFLAGS) -c -g display.c

clean: 
	rm -f reader *.o
