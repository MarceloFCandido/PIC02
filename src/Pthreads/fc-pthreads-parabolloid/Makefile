
# Rules for compiling the code #
#------------------------------------------------------------------------------#
main: src/function-solver.cpp
	-@ g++ src/function-solver.cpp -o bin/function-solver.exe -O2 -larmadillo -lpthread

# Rules for running the code #
#------------------------------------------------------------------------------#
run: bin/function-solver.exe
	-@ ./bin/function-solver.exe $(0) $(1) $(2) $(3) $(4) $(5)

# Rules for doing the plot #
#------------------------------------------------------------------------------#
plot: src/function-viewer.py
	-@ python src/function-viewer.py

# Cleaning #
#------------------------------------------------------------------------------#
.PHONY: clean
clean:
	-@ rm -fv *~

.PHONY: clean-data
clean-data:
	-@ rm -fv data/*.dat

.PHONY: distclean
distclean: clean
	-@ rm -fv bin/*.exe
	-@ rm -fv src/*.dat
