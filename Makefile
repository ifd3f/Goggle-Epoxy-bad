# Compiler
CC=g++
# Compiler arguments
C_ARGS = -I /usr/include/eigen3 -std=c++14 -Wall -g -DBOOST_LOG_DYN_LINK
# Linker arguments
L_ARGS = -lboost_system -lboost_log -lpthread

OUTPUT=main.out
.DEFAULT_GOAL := all

build/%.o: directories src/%.cpp
	$(CC) $(C_ARGS) -c src/$*.cpp -o build/$*.o

.PHONY: all
all: build/main.o build/motion.o
	$(CC) build/*.o $(L_ARGS) -o $(OUTPUT) 

.PHONY: directories
directories:
	mkdir -p build
 
.PHONY: clean
clean:
	rm -f build/*.o
	rm -f build/$(OUTPUT)
