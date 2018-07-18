# Compiler
CC=g++

SRC = \
	main \
	motion \
	scheduler \
	input \
	util \
	activity \
	mpl3115a2 \
	l3gd20 \
	gpiobtn \
	context \
	lsm303 \
	ssd1306 \
	exception

SRC_TEST = \
	test

LIB = \
	boost_system \
	boost_log \
	pthread \
	cairo \
	crypt \
	wiringPi

INC = \
	/usr/include/eigen3 \
	/usr/include/cairo

# Compiler arguments
C_ARGS = $(INC:%=-I %) -std=c++17 -pedantic -Wall -Wextra -Wno-unused-parameter -g -DBOOST_LOG_DYN_LINK
# Linker arguments
L_ARGS = $(LIB:%=-l%)

OUTPUT=main.out
.DEFAULT_GOAL := all

build/%.o: directories src/%.cpp
	$(CC) $(C_ARGS) -c src/$*.cpp -o build/$*.o

.PHONY: link-all
link-all: $(SRC:%=build/%.o)
	$(CC) $(SRC:%=build/%.o) $(L_ARGS) -o $(OUTPUT) 

link-test: $(SRC_TEST:%=build/%.o)
	$(CC) $(SRC_TEST:%=build/%.o) $(L_ARGS) -o test.out

.PHONY: all
all: link-all

.PHONY: directories
directories:
	mkdir -p build
 
.PHONY: clean
clean:
	rm -f build/*.o build/$(OUTPUT)
