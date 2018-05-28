
# Rules
#------------------------------------------------------------------------------#

all: main

main: main-reflect-bound.cpp interface.o velocity.o _2DWave.o
	gcc main-reflect-bound.cpp interface.o velocity.o _2DWave.o -o main.exe

interface.o: interface/interface.cpp interface/interface.h
	gcc -c interface/interface.cpp -o interface.o

velocity.o: velocity/velocity.cpp velocity/velocity.h
	gcc -c velocity.cpp -o velocity.o

_2DWave.o: wave/_2DWave.cpp wave/_2DWave.h velocity/velocity.h interface/interface.h
	gcc -c _2DWave.cpp -o _2DWave.o

# Cleaning
#------------------------------------------------------------------------------#

.PHONY: clean
clean:
	-@ rm -fv *~
	-@ rm -fv *.o
	-@ rm -fv *.a

.PHONY: distclean
distclean: clean
	-@ rm -fv main

#------------------------------------------------------------------------------#
