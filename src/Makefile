#------------------------------------------------------------------------------
# Makefile
# Author: David Dalström
# Created: 2014-05-03
#------------------------------------------------------------------------------

# The A* library itself
SOURCE=Tile.cpp A_Star.cpp
OBJS=$(SOURCE:%.cpp=./obj/%.o)
ASTAR_LIB=../lib/libastar.a

# Compiler
CC=g++
CCFLAGS=-Wall -g
INCLUDE=./include

# Archiver
ARCHIVER=ar


all: $(ASTAR_LIB)

$(ASTAR_LIB): $(OBJS)
	$(ARCHIVER) ruv $@ $^
	ranlib $(ASTAR_LIB)

./obj/%.o: %.cpp
	$(CC) -c $< -o $@ $(CCFLAGS) -I$(INCLUDE)

clean:
	rm -f $(OBJS)
	rm -f $(ASTAR_LIB)
