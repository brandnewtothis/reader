CC := gcc

CFLAGS = $(shell sdl2-config --cflags) -Wall -Werror -lm
LDLIBS += -lSDL2 -lSDL2_image -lSDL2_ttf

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

