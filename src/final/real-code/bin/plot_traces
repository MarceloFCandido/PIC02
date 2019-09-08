#!/bin/bash

# Produces wiggle plot of traces
sfwiggle < ./traces/traces.rsf \
           transp=y   \
	   yreverse=y \
	   plotcol=7  \
	   zplot=.15  \
	   poly=y \
	   xmax=10 \
	   title='' \
	   n1tic=0 \
	   > ./traces/traces.vpl

# Convert vpl to png
vpconvert ./traces/traces.vpl \
          format=png \
	  > ./traces/traces.png

