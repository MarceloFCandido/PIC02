
# Rules for compiling the code #
#------------------------------------------------------------------------------#
main: src/solver.cpp
	-@ g++ src/solver.cpp -o bin/solver.exe -O2 -larmadillo -lpthread

# Rules for running the code #
#------------------------------------------------------------------------------#
run: bin/solver.exe
	-@ ./bin/solver.exe $(xp) $(xb) $(xt) $(xw) $(tt) $(tw) $(f)

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
