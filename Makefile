library_files = $(patsubst %.c, %.o, $(wildcard library/*.c))
service_files = $(patsubst %.c, %.o, $(wildcard service/*.c))

all: clean _build

%.o: %.c 
	$(CC) -c $< -o $@ -Ilibrary -fPIC

main: $(service_files)
	mkdir -p build
	$(CC) $(service_files) -o main \
	    -Ilibrary -nostdlib -lukbd  -Lbuild -lc -o build/main
	strip build/main

libukbd: $(library_files)
	mkdir -p build
	$(CC) $(library_files) -o build/libukbd.so \
	    -shared -fPIC -Ilibrary -nostdlib -lc
	strip build/libukbd.so

run: build
	LD_LIBRARY_PATH=$$PWD/build build/main

test:
	valac data/test.vala -o build/test-vala --vapidir=./library/ --pkg libukbd -X -I./library -X -L./build -X -lukbd
	$(CC) data/test.c -o build/test-c -Ilibrary -lukbd -Lbuild
	@echo -ne "\033[33mPython test\033[;0m\n"
	LD_LIBRARY_PATH=$$PWD/build python3 data/test.py
	@echo -ne "\033[33mC test\033[;0m\n"
	LD_LIBRARY_PATH=$$PWD/build build/test-c
	@echo -ne "\033[33mVala test\033[;0m\n"
	LD_LIBRARY_PATH=$$PWD/build build/test-vala
	@if [[ `uname -m` == "x86_64" ]]; then \
	    make test-x86 ;\
	fi

test-x86:
	$(CC) data/test.s -o build/test-asm -Ilibrary -lukbd -Lbuild -nostdlib
	@echo -ne "\033[33mx86_64 Assembly test\033[;0m\n"
	LD_LIBRARY_PATH=$$PWD/build build/test-asm


_build: libukbd main

clean:
	rm -vfr $(service_files) $(library_files) build */__pycache__
