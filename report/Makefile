#!/bin/bash

# Rules for compiling the code #
#------------------------------------------------------------------------------#
report: report.tex 
	pdflatex report.tex
	makeglossaries report
	biber report
	pdflatex report.tex
	pdflatex report.tex
	mv report.pdf bin/report.pdf
	#evince bin/report.pdf

# Cleaning #
#------------------------------------------------------------------------------#
.PHONY: clean
clean:
	-@ rm -fv *~

.PHONY: distclean
distclean: clean
	-@ rm -fv bin/*.out
