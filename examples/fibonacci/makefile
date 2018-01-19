CC=emcc
SOURCES=main.cpp
LDFLAGS=-O3 --llvm-opts 2 --llvm-lto 1

all:
	$(CC) $(SOURCES) --bind -s ASSERTIONS=1  -s MODULARIZE=1 -s EXPORT_NAME="'APPCpp'" -s WASM=1 -s AGGRESSIVE_VARIABLE_ELIMINATION=1 -s INLINING_LIMIT=1 -s NO_EXIT_RUNTIME=1 -s EXPORTED_FUNCTIONS="['_malloc','_free']"  -s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]' -std=c++11  $(LDFLAGS) -o main.wasm.js
	$(CC) $(SOURCES) --bind -s ASSERTIONS=1  -s MODULARIZE=1 -s EXPORT_NAME="'APPCpp'" -s AGGRESSIVE_VARIABLE_ELIMINATION=1 -s INLINING_LIMIT=1 -s NO_EXIT_RUNTIME=1 -s EXPORTED_FUNCTIONS="['_malloc','_free']"  -s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]' -std=c++11  $(LDFLAGS) -o main.asm.js

clean:
	rm -f main.wasm.js
	rm -f main.asm.js
