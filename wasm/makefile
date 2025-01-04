TARGET = test

# Build CHIP-8

# Build CHIP-8 WebAssembly 

# gcc -c test.c `sdl2-config --cflags`
# gcc -c sdl_file.c `sdl2-config --cflags`
# gcc test.o sdl_file.o -o test `sdl2-config --libs`

# emcc test.c sdl_file.c -s USE_SDL=2 -o index.html 

# Default target
all: test

test: test.o sdl_file.o
	gcc $^ -o $@ `sdl2-config --libs`

test.o sdl_file.o:
	gcc -c $@.c `sdl2-config --cflags`

# For debugging
debug: $(OBJ)
	gcc -g 
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS) -DDEBUG

# Build the executable
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

# Clean up generated files
clean:
	rm *.o *.exe