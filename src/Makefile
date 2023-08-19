# Author: Michael Bopp
# Date Created: 07/05/23
# Last Modified: 08/08/23

# Detect OS & build dir/dir/Makefile path.
ifeq ($(OS),Windows_NT)
    PATH_COMPONENTS = $(subst \, ,$(subst /, ,$(CURDIR)))
    CURRENT_DIR_NAME = $(lastword $(PATH_COMPONENTS))
    PATH_WITHOUT_LAST_DIR = $(filter-out $(CURRENT_DIR_NAME),$(PATH_COMPONENTS))
    PARENT_DIR_NAME = $(lastword $(PATH_WITHOUT_LAST_DIR))
    CUR_DIR = $(PARENT_DIR_NAME)\\$(CURRENT_DIR_NAME)\\Makefile
else
    CURRENT_DIR_NAME = $(notdir $(CURDIR))
    PARENT_DIR_FULL_PATH = $(dir $(CURDIR))
    PARENT_DIR_NAME = $(notdir $(patsubst %/,%,$(PARENT_DIR_FULL_PATH)))
    CUR_DIR = $(PARENT_DIR_NAME)/$(CURRENT_DIR_NAME)/Makefile
endif

# Variables
CXX = g++
CXXFLAGS = -Wall -g -std=c++20
LIBS = -lncursesw
OBJS = main.o board.o pieces.o

# Text Coloring
BLUE=\033[34m
GREEN=\033[32m
YELLOW=\033[33m
RESET=\033[0m

# Target
chess: $(OBJS)
	$(CXX) $(CXXFLAGS) -o chess $(OBJS) $(LIBS)
	rm *.o
	
# Object Files
main.o: main.h main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

board.o: board.h board.cpp
	$(CXX) $(CXXFLAGS) -c board.cpp

pieces.o: pieces.h pieces.cpp
	$(CXX) $(CXXFLAGS) -c pieces.cpp

# Clean
clean:
	rm *.o chess

# List the labels of the Makefile.
list:
	@echo -e "$(GREEN)Directory: $(YELLOW)$(CUR_DIR)$(RESET)"
	@echo -e "$(GREEN)Available targets in Makefile:$(RESET)"
	@GREP_COLORS="mt=01;96" grep --color=always '^[a-zA-Z0-9_-]*:' Makefile | cut -d':' -f1 | grep -vE 'list|listc'

# List the labels & commands of them in the Makefile.
listc:
	@echo -e "$(GREEN)Directory: $(YELLOW)$(CUR_DIR)$(RESET)"
	@echo -e "$(GREEN)Available targets in Makefile:$(RESET)"
	@GREP_COLORS="mt=01;96" grep --color=always -A1 '^[a-zA-Z0-9_-]*:' Makefile | grep -v -- '--' | grep -vE 'list:|@echo'