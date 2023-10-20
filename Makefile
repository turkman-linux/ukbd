service_files = $(patsubst %.c, %.o, $(wildcard service/*.c))

%.o: %.c 
	gcc -c $< -o $@ 

main: $(service_files)
	gcc $(wildcard service/*.o) $(CFLAGS) -nostdlib -lc -o main
	strip main

build: main

clean:
	rm -vf main service/*.o
