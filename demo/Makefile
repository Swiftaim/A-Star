#------------------------------------------------------------------------------
# Makefile
# Author: David Dalström
# Created: 2014-05-03
#------------------------------------------------------------------------------

# The sample app utilising libastar.a
SOURCE=Game.cpp main.cpp Pathfinder.cpp
OBJS=$(SOURCE:%.cpp=./obj/%.o)

PROGRAM=astar
INCLUDE= \
	-I./ \
	-I../include/

LIBRARIES=-L../lib -lastar
FRAMEWORKS=-framework OpenGL -framework GLUT
CC=g++
CCFLAGS=-Wall -g -Wno-deprecated-declarations

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CC) -o $@ $^ $(LIBRARIES) $(FRAMEWORKS)

./obj/%.o: %.cpp
	$(CC) -c $< -o $@ $(CCFLAGS) $(INCLUDE) 

clean:
	rm -f $(OBJS)
	rm -f $(PROGRAM)
