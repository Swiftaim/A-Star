#------------------------------------------------------------------------------
# Makefile
# Author: David Dalström
# Created: 2014-05-03
#------------------------------------------------------------------------------

# The A* library itself
SOURCE=Tile.cpp A_Star.cpp
OBJS=$(SOURCE:%.cpp=./obj/%.o)
ASTAR_LIB=../lib/libastar.so

# Compiler
CC=g++
CCFLAGS=-Wall -g -fPIC -Wno-c++11-extensions
INCLUDE=../include


all: $(ASTAR_LIB)

$(ASTAR_LIB): $(OBJS)
	$(CC) -v -shared -o $@ $^

./obj/%.o: %.cpp
	$(CC) -c $< -o $@ $(CCFLAGS) -I$(INCLUDE)

clean:
	rm -f $(OBJS)
	rm -f $(ASTAR_LIB)
