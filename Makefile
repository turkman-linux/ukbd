library_files = $(patsubst %.c, %.o, $(wildcard library/*.c))
service_files = $(patsubst %.c, %.o, $(wildcard service/*.c))

all: clean _build

%.o: %.c 
	gcc -c $< -o $@ -Ilibrary -fPIC

main: $(service_files)
	mkdir -p build
	gcc $(service_files) -o main \
	    -Ilibrary -nostdlib -lukbd  -Lbuild -lc -o build/main
	strip build/main

libukbd: $(library_files)
	mkdir -p build
	gcc $(library_files) -o build/libukbd.so \
	    -shared -fPIC -Ilibrary -nostdlib -lc
	strip build/libukbd.so

run: build
	LD_LIBRARY_PATH=$$PWD/build build/main

test:
	LD_LIBRARY_PATH=$$PWD/build python3 test.py

_build: libukbd main

clean:
	rm -vfr $(service_files) $(library_files) build */__pycache__
