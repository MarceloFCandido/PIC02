
# Rules for main and cli
#------------------------------------------------------------------------------#

mainly: main
cli-terminal: cli

main: main-reflect-bound.cpp interface.o velocity.o _2DWave.o
	g++ main-reflect-bound.cpp interface.o velocity.o _2DWave.o -o main.exe -O2 -larmadillo

cli: cli-main.cpp interface.o velocity.o _2DWave.o
	g++ cli-main.cpp interface.o velocity.o _2DWave.o -o cli.exe -O2 -larmadillo

interface.o: interface/interface.cpp interface/interface.h
	g++ -c interface/interface.cpp -o interface.o

velocity.o: velocity/velocity.cpp velocity/velocity.h
	g++ -c velocity/velocity.cpp -o velocity.o

_2DWave.o: wave/_2DWave.cpp wave/_2DWave.h velocity/velocity.h interface/interface.h
	g++ -c wave/_2DWave.cpp -o _2DWave.o

# Cleaning
#------------------------------------------------------------------------------#

.PHONY: clean
clean:
	-@ rm -fv *~
	-@ rm -fv *.o
	-@ rm -fv *.a

.PHONY: distclean
distclean: clean
	-@ rm -fv *.exe
	-@ rm -fv *.dat

#------------------------------------------------------------------------------#
