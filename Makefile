service_files = $(patsubst %.c, %.o, $(wildcard service/*.c))

%.o: %.c 
	gcc -c $< -o $@ 

main: $(service_files)
	gcc $(wildcard service/*.o) -o main

build: main

clean:
	rm -f main service/*.o
