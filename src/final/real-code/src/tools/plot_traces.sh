#!/bin/bash

# Produces wiggle plot of traces

for ((i = 0; i < $1; i++)); do
	cat ./traces/$i-traces.rsf
	sfwiggle <./traces/$i-traces.rsf \
		transp=y \
		yreverse=y \
		plotcol=7 \
		zplot=.15 \
		poly=y \
		xmax=10 \
		title='' \
		n1tic=0 \
		>./traces/traces.vpl

	# Convert vpl to png
	vpconvert ./traces/traces.vpl \
		format=png \
		>./traces/$i-traces.png
done
