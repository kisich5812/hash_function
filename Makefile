COMPILER=gcc

all: hash

hash: main.o flags.o
	$(COMPILER) $(C_FLAGS) main.o flags.o -o hash

main.o: src/main.c
	$(COMPILER) $(C_FLAGS) -c src/main.c

flags.o: src/flags.c
	$(COMPILER) $(C_FLAGS) -c src/flags.c

obj_clean:
	rm -rf *.o

clean:
	rm -rf *.o hash
