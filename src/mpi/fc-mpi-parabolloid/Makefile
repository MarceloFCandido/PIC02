
# Rules for compiling the code #
#------------------------------------------------------------------------------#
main: src/solver.cpp
	mpic++ src/solver.cpp -o bin/solver.out -O2 -larmadillo

# Rules for running the code #
#------------------------------------------------------------------------------#
run: bin/solver.out
	mpirun -n $(tasks) ./bin/solver.out $(xp) $(xb) $(xe) $(yp) $(yb) $(ye)

# Rules for doing the plot #
#------------------------------------------------------------------------------#
plot: src/viewer.py
	-@ python src/viewer.py
	-@ eog data/images/A.png

# Cleaning #
#------------------------------------------------------------------------------#
.PHONY: clean
clean:
	-@ rm -fv *~

.PHONY: clean-data
clean-data:
	-@ rm -fv data/outputs/*.dat
	-@ rm -fv data/images/*.png

.PHONY: distclean
distclean: clean
	-@ rm -fv bin/*.exe
	-@ rm -fv src/outputs/*.dat
	-@ rm -fv src/images/*.png
