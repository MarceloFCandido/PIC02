#------------------------------------------------------------------------------#
# Wave propagation 
#
# Makefile ./src/libs
#------------------------------------------------------------------------------#

# Build and install
#------------------------------------------------------------------------------#

src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)

default: ${obj}

interface.o: interface.cpp interface.h
	g++ -c interface.cpp -o interface.o

velocity.o: velocity.cpp velocity.h
	g++ -c velocity.cpp -o velocity.o

_2DWave.o: _2DWave.cpp _2DWave.h velocity.h interface.h util.h
	g++ -c _2DWave.cpp -o _2DWave.o

install:

# Cleaning
#------------------------------------------------------------------------------#

# Files to be removed from this directory at cleaning
CLEAN_FILES= *~ *.o *.a 

# Files to be removed from this directory at distribution cleaning
DISTCLEAN_FILES= ${CLEAN_FILES} .*sw?

.PHONY: clean
clean:
	-@ rm -vf ${CLEAN_FILES}


.PHONY: distclean
distclean: 
	-@ rm -vf ${DISTCLEAN_FILES}

#------------------------------------------------------------------------------#
