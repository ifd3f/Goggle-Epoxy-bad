# Compiler
CC=g++

NO_DEPS := clean
MODULES := src
SRC_NAMES := 

include $(MODULES:%=%/module.mk)

SRC := $(SRC_NAMES:%=%.cpp)
DEP := $(SRC_NAMES:src/%=.d/%.d)
OBJ := $(SRC_NAMES:src/%=build/%.o)

LIB = \
	boost_system \
	boost_log \
	pthread \
	cairo \
	crypt \
	wiringPi

INC = \
	src/ \
	/usr/include/eigen3/ \
	/usr/include/cairo/

# Compiler arguments
C_ARGS = $(INC:%=-I %) -std=c++17 -pedantic -Wall -Wextra -Wno-unused-parameter -g -DBOOST_LOG_DYN_LINK
C_ARGS_RELEASE = $(INC:%=-I %) -std=c++17 -pedantic -Wall -Wextra -Wno-unused-parameter -DBOOST_LOG_DYN_LINK
# Linker arguments
L_ARGS = $(INC:%=-I %) $(LIB:%=-l%)

TARGET = main.out
.DEFAULT_GOAL := all

.d/%.d: src/%.cpp .d/
	$(CC) $(C_ARGS) src/$*.cpp -MM -MT build/$*.o | sed -e 's@ˆ\(.*\)\.o:@\1.d \1.o:@' > $@

build/%.o: src/%.cpp build/
	$(CC) $(C_ARGS) -c src/$*.cpp -o $@

.d/:
	mkdir -p .d/ .d/devices/

build/:
	mkdir -p build/ build/devices/

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
