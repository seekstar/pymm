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
else
EXECUTABLE	:= main
RM 			:= rm -f
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


build_debug: $(BIN_DEBUG)/$(EXECUTABLE)
$(BIN_DEBUG)/$(EXECUTABLE): $(OBJS_DEBUG)
	$(CC) $^ -o $@ $(LIBRARIES)

$(OBJ_DEBUG)/%.o: $(SRC)/%.cpp $(DEP)/%.d
	$(CC) $(FLAGS_DEBUG) -c -I$(INCLUDE) -L$(LIB) $< -o $@

run_debug: build_debug
	./$(BIN_DEBUG)/$(EXECUTABLE)



build_release: $(BIN_RELEASE)/$(EXECUTABLE)
$(BIN_RELEASE)/$(EXECUTABLE): $(OBJS_RELEASE)
	$(CC) $^ -o $@ $(LIBRARIES)

$(OBJ_RELEASE)/%.o: $(SRC)/%.cpp $(DEP)/%.d
	$(CC) $(FLAGS_RELEASE) -c -I$(INCLUDE) -L$(LIB) $< -o $@

run_release: build_release
	./$(RELEASE_BIN)/$(EXECUTABLE)

all: build_debug build_release

.PHONY: clean_debug clean_release clean build_debug run_debug build_release run_release all

