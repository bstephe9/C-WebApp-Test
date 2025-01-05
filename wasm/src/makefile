clean_files = *.exe *.o *.html *.js *.wasm
output = sdl_test
objects = test.o sdl_file.o

CC = gcc

all: $(objects)
	$(CC) $^ -o test `sdl2-config --libs`

$(objects): %.o: %.c
	$(CC) -c $^ -o $@ `sdl2-config --cflags`

html:
	emcc sdl_file.c test.c -s USE_SDL=2 -o test.html

clean:
	rm $(clean_files)