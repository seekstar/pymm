CC				:= g++
FLAGS_DEBUG 	:= -std=c++17 -Wall -Wextra -fexceptions -g
FLAGS_RELEASE 	:= -std=c++17 -Wall -Wextra -fexceptions -O3

BIN_DEBUG	:= bin/debug
BIN_RELEASE := bin/release
SRC		:= src
SRCS		:= $(wildcard $(SRC)/*.cpp)
INCLUDE	:= include
LIB		:= lib

LIBRARIES	:=

OBJ_DEBUG	:= obj/debug
OBJS_DEBUG	:= $(patsubst $(SRC)/%.cpp,$(OBJ_DEBUG)/%.o,$(SRCS))

OBJ_RELEASE	:= obj/release
OBJS_RELEASE:= $(patsubst $(SRC)/%.cpp,$(OBJ_RELEASE)/%.o,$(SRCS))

DEP			:= dep
DEPS		:= $(patsubst $(SRC)%.cpp,$(DEP)/%.d,$(SRCS))

ifeq ($(OS),Windows_NT)
EXECUTABLE	:= main.exe
RM 			:= del
THREAD		:= 1
else
EXECUTABLE	:= main
RM 			:= rm -f
THREAD		:= $(shell grep 'processor' /proc/cpuinfo | sort -u | wc -l)
endif

clean_debug:
	$(RM) $(BIN_DEBUG)/$(EXECUTABLE) $(OBJ_DEBUG)/*.o

clean_release:
	$(RM) $(BIN_RELEASE)/$(EXECUTABLE) $(OBJ_RELEASE)/*.o

clean:	clean_debug clean_release
	$(RM) $(DEP)/*.d $(DEP)/*.d.*


$(DEP)/%.d: $(SRC)%.cpp
	@set -e; \
	$(RM) $@; \
	$(CC) -MM -I$(INCLUDE) $< > $@.$$$$; \
	sed 's,^.*:,$@ $(OBJ_DEBUG)/$(patsubst $(SRC)/%.cpp,%,$<).o $(OBJ_RELEASE)/&,g' < $@.$$$$ > $@; \
	$(RM) $@.$$$$

-include $(DEPS)


$(BIN_DEBUG)/$(EXECUTABLE): $(OBJS_DEBUG)
	$(CC) $^ -o $@ $(LIBRARIES)

$(OBJ_DEBUG)/%.o: $(SRC)/%.cpp $(DEP)/%.d
	$(CC) $(FLAGS_DEBUG) -c -I$(INCLUDE) -L$(LIB) $< -o $@

build_debug0: $(BIN_DEBUG)/$(EXECUTABLE)
build_debug:
	make build_debug0 -j$(THREAD)

run_debug: build_debug
	./$(BIN_DEBUG)/$(EXECUTABLE)



$(BIN_RELEASE)/$(EXECUTABLE): $(OBJS_RELEASE)
	$(CC) $^ -o $@ $(LIBRARIES)

$(OBJ_RELEASE)/%.o: $(SRC)/%.cpp $(DEP)/%.d
	$(CC) $(FLAGS_RELEASE) -c -I$(INCLUDE) -L$(LIB) $< -o $@

build_release0: $(BIN_RELEASE)/$(EXECUTABLE)
build_release:
	make build_release0 -j$(THREAD)

run_release: build_release
	./$(RELEASE_BIN)/$(EXECUTABLE)

all0: build_debug0 build_release0
all:
	make all0 -j$(THREAD)

.PHONY: clean_debug clean_release clean build_debug build_debug0 run_debug build_release build_release0 run_release all0 all

