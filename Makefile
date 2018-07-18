# Compiler
CC=g++

MODULES := src
SRC_NAMES := 

include $(MODULES:%=%/module.mk)

SRC := $(SRC_NAMES:%=%.cpp)
DEP := $(SRC_NAMES:%=%.d)
OBJ := $(SRC_NAMES:src/%=build/%.o)

LIB = \
	boost_system \
	boost_log \
	pthread \
	cairo \
	crypt \
	wiringPi

INC = \
	/usr/include/eigen3/ \
	/usr/include/cairo/

# Compiler arguments
C_ARGS = $(INC:%=-I %) -std=c++17 -pedantic -Wall -Wextra -Wno-unused-parameter -g -DBOOST_LOG_DYN_LINK
# Linker arguments
L_ARGS = $(LIB:%=-l%)

TARGET=main.out
.DEFAULT_GOAL := all

include $(DEP)

$(DEP): $(SRC)
	echo $@
	$(CC) $(C_ARGS) $(@:.d=.cpp) -MM -MT $(@:src/%.d=build/%.o) | sed 's/\.cpp\|\.hpp/\.o/' > $@

build/%.o: src/%.cpp
	echo $@
	$(CC) $(C_ARGS) -c $^ -o $@

.PHONY: link-main
link-main: $(OBJ)
	$(CC) $(L_ARGS) $(OBJ) -o $(TARGET)

.PHONY: all
all: link-main

.PHONY: clean
clean:
	rm -f build/*.o $(TARGET) *.d
	rm -rf */*.d
