#compiler
CC := gcc

CFLAGS = -Wall -Werror 
LDLIBS += -lSDL2 -lSDL2_image

reader: main.o text.o display.o
	$(CC) $(CFLAGS) -o reader main.o text.o display.o $(LDLIBS)

main.o: main.c text.h display.h
	$(CC) $(CFLAGS) -c -g main.c

text.o: text.c text.h
	$(CC) $(CFLAGS) -c -g text.c

display.o: display.c display.h
	$(CC) $(CFLAGS) -c -g display.c

clean: 
	rm -f reader *.o
