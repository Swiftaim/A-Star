#------------------------------------------------------------------------------
# Makefile
# Author: David Dalström
# Created: 2014-05-03
#------------------------------------------------------------------------------

SOURCE=Tile.cpp A_Star.cpp Game.cpp Main.cpp
DEPENDENCY=Game.h Tile.h A_Star.h
PROGRAM=astar
INCLUDES=./
LIBRARIES=
FRAMEWORKS=-framework OpenGL -framework GLUT
CC=g++

all: $(PROGRAM)

$(PROGRAM): $(SOURCE) $(DEPENDENCY)
	$(CC) -g -I$(INCLUDES) $(SOURCE) -o $(PROGRAM) $(FRAMEWORKS) -Wdeprecated-declarations

clean:
	rm -f $(PROGRAM)
