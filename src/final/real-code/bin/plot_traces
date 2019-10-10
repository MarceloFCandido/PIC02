#!/bin/bash

# Produces wiggle plot of traces
FILES=`ls traces/*-traces.rsf`
sfcat axis=2 $FILES > ./traces/traces.rsf

# cat ./traces/0-traces.rsf@ ./traces/1-traces.rsf@ > ./traces/traces.rsf@
# echo 'tracer
# data_format="native_float"
# in="./traces/traces.rsf@"
# n1=236
# n2=40' > ./traces/traces.rsf

sfwiggle <./traces/traces.rsf \
	transp=y \
	yreverse=y \
	plotcol=7 \
	zplot=.15 \
	poly=y \
	title='' \
	n1tic=0 \
	>./traces/traces.vpl

# Convert vpl to png
vpconvert ./traces/traces.vpl \
	format=pdf > /dev/null
