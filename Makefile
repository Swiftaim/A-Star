#------------------------------------------------------------------------------
# Makefile
# Author: David Dalström
# Created: 2014-05-03
#------------------------------------------------------------------------------

# The A* library itself
LIB_SOURCE=Tile.cpp A_Star.cpp
LIB_DEPENDENCY=Tile.h A_Star.h

# The sample app utilising libastar.a
APP_SOURCE=Game.cpp Main.cpp
APP_DEPENDENCY=Game.h

ASTAR_LIB=libastar.a
PROGRAM=astar
INCLUDES=./
LIBRARIES=
FRAMEWORKS=-framework OpenGL -framework GLUT
CC=g++
CCFLAGS=-Wall -g

all: $(PROGRAM)

$(PROGRAM): $(SOURCE) $(DEPENDENCY)
	$(CC) -g $(CCFLAGS) -I$(INCLUDES) $(SOURCE) -o $(PROGRAM) $(FRAMEWORKS) -Wdeprecated-declarations

clean:
	rm -f $(PROGRAM)
