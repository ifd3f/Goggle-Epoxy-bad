# Compiler
CC=g++

SRC = \
	main \
	motion \
	scheduler \
	input \
	util \
	activity

SRC_PI = \
	mpl3115a2 \
	l3gd20

LINKED_LIBS = \
	boost_system \
	boost_log \
	pthread \
	cairo

LINKED_LIBS_PI = \
	crypt \
	wiringPi

# Compiler arguments
C_ARGS = -I /usr/include/eigen3 -std=c++17 -Wall -g -DBOOST_LOG_DYN_LINK
# Linker arguments
L_ARGS = $(LINKED_LIBS:%=-l%)
L_ARGS_PI = $(L_ARGS) $(LINKED_LIBS_PI:%=-l%)

OUTPUT=main.out
.DEFAULT_GOAL := all

build/%.o: directories src/%.cpp
	$(CC) $(C_ARGS) -c src/$*.cpp -o build/$*.o

.PHONY: link-no-pi
link-no-pi: $(SRC:%=build/%.o)
	$(CC) $(SRC:%=build/%.o)$(L_ARGS) -o $(OUTPUT) 

.PHONY: link-all
link-all: $(SRC:%=build/%.o) $(SRC_PI:%=build/%.o)
	$(CC) build/*.o $(L_ARGS_PI) -o $(OUTPUT) 

.PHONY: all
all: link-all

.PHONY: directories
directories:
	mkdir -p build
 
.PHONY: clean
clean:
	rm -f build/*.o
	rm -f build/$(OUTPUT)
