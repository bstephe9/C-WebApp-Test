clean_files = *.exe *.o
output = sdl_test
CC = gcc
CFLAGS = -g -std=c17
INCLUDES = C:\MinGW\x86_64-w64-mingw32\include\SDL2
LIBS = C:\MinGW\x86_64-w64-mingw32\lib -lmingw32 -lSDL2main -lSDL2

test:
	$(CC) -o test test.c $(CFLAGS) -I$(INCLUDES) -L$(LIBS)

s:
	$(CC) -o sdl_test sdl_test.c $(CFLAGS) -I$(INCLUDES) -L$(LIBS) 

clean:
	rm $(clean_files)