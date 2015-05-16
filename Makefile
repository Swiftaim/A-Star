#------------------------------------------------------------------------------
# Makefile
# Author: David Dalström
# Created: 2014-05-03
#------------------------------------------------------------------------------

all:
	make -C src
	make -C demo

clean:
	make -C src clean
	make -C demo clean
	