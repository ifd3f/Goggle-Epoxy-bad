# Compiler
CC=/usr/bin/gcc

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
	/usr/lib/ \
	/usr/lib/x86_64-linux-gnu/ \
	/usr/local/lib/

LIB = \
	wiringPi

PKG_CONFIG = \
	glib-2.0 \
	cairo \
	pango
	

# Compiler arguments
C_ARGS = $(INC:%=-I%) `pkg-config --cflags $(PKG_CONFIG)` -std=c++17 -pedantic -Wall -Wextra -Wno-unused-parameter -g -DBOOST_LOG_DYN_LINK
# Linker arguments
L_ARGS = $(INC:%=-I%) $(LINK_DIRS:%=-L%) `pkg-config --libs $(PKG_CONFIG)`

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
	$(CC) -o $(TARGET) $(L_ARGS) $(OBJ)

.PHONY: all
all: link-main

.PHONY: clean
clean:
	find . | grep -e '\.d$$' -e '\.o$$' -e '\.out$$' | xargs rm -rf

ifneq ($(MAKECMDGOALS), clean)
include $(DEP)
endif
