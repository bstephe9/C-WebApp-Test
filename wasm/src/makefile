clean_files = *.exe *.o *.html test.js *.wasm
output = sdl_test
objects = test.o sdl_file.o

CC = gcc

all: $(objects)
	$(CC) $^ -o test `sdl2-config --libs`

$(objects): %.o: %.c
	$(CC) -c $^ -o $@ `sdl2-config --cflags`

# Generate emcc js/wasm files and move to public/
local:
	echo "var Module = { canvas: document.getElementById('canvas') };" > temp_pre.js
	emcc sdl_file.c test.c -s USE_SDL=2 -o test.js \
		--pre-js temp_pre.js
	rm temp_pre.js
	# Remove local paths in file
	sed '/^\/\/ include: C:.*/d; /^\/\/ end include: C:.*/d' test.js > test_cleaned.js
	mv test_cleaned.js test.js
	mv test.js test.wasm ../../public

clean:
	rm $(clean_files)