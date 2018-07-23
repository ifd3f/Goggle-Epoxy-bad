# Compiler
CC=g++

NO_DEPS := clean
MODULES := src
SRC_NAMES := 
SRC_DIRS :=

include $(MODULES:%=%/module.mk)

SRC := $(SRC_NAMES:%=%.cpp)
DEP := $(SRC_NAMES:src/%=.d/%.d)
OBJ := $(SRC_NAMES:src/%=build/%.o)

INC = \
	./src/ \
	/usr/include/ \
	/usr/include/eigen3/ \
	/usr/include/cairo/ \
	/usr/local/include/ \
	/usr/include/pango-1.0/ \
	/usr/include/freetype2/

LINK_DIRS = \
	/usr/lib/x86_64-linux-gnu \
	/usr/lib \
	/usr/local/lib

LIB = \
	cairo \
	pango-1.0 \
	crypt \
	wiringPi
	

# Compiler arguments
C_ARGS = $(INC:%=-I%) `pkg-config --cflags glib-2.0` -std=c++17 -pedantic -Wall -Wextra -Wno-unused-parameter -g -DBOOST_LOG_DYN_LINK
C_ARGS_RELEASE = $(INC:%=-I%) -std=c++17 -pedantic -Wall -Wextra -Wno-unused-parameter -DBOOST_LOG_DYN_LINK
# Linker arguments
L_ARGS = $(INC:%=-I%) $(LINK_DIRS:%=-L%) $(LIB:%=-l%)

TARGET = main.out
.DEFAULT_GOAL := all

.d/%.d: src/%.cpp .d/
	$(CC) $(C_ARGS) src/$*.cpp -MM -MG -MT build/$*.o | sed -e 's@ˆ\(.*\)\.o:@\1.d \1.o:@' > $@

build/%.o: src/%.cpp build/
	$(CC) -o $@ $(C_ARGS) -c src/$*.cpp

.d/:
	mkdir -p $(SRC_DIRS:%=.d/%)

build/:
	mkdir -p $(SRC_DIRS:%=build/%)

.PHONY: link-main
link-main: $(OBJ)
	$(CC) $(L_ARGS) $(OBJ) -o $(TARGET)

.PHONY: all
all: link-main

.PHONY: clean
clean:
	find . | grep -e '\.d$$' -e '\.o$$' -e '\.out$$' | xargs rm -rf

ifneq ($(MAKECMDGOALS), clean)
include $(DEP)
endif
