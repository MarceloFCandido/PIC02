#!/usr/bin/python2.7
#!-*- coding: utf8 -*-

import numpy as np;

# Loading arrays from files
traces = np.loadtxt('./traces/traces.dat');

# Number of traces and samples 
Nt = traces.shape[0];
Ns = traces.shape[1];

# Writing the RSF header file

header = open( "./traces/traces.rsf", "w+" )

header.write( 'tracer\n'                     )
header.write( 'data_format="native_float"\n' )
header.write( 'in="./traces/traces.rsf@"\n'  )
header.write( 'n1=%d\n'%( Nt )               )
header.write( 'n2=%d\n'%( Ns )               )

header.close()

np.transpose(traces.astype('float32')).tofile( './traces/traces.rsf@' );
