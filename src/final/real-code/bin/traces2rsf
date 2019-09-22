#!/usr/bin/python2.7
#!-*- coding: utf8 -*-

import numpy as np

# Loading arrays from files
pmts = np.loadtxt('./specs/output.dat')
N = int(pmts[7])
for i in range(0, N):
    traces = np.loadtxt('./traces/' + str(i) + '-traces.dat')

    # Number of traces and samples
    Nt = traces.shape[0]
    Ns = traces.shape[1]

    # Writing the RSF header file

    header = open('./traces/' + str(i) + '-traces.rsf', "w+")

    header.write('tracer\n')
    header.write('data_format="native_float"\n')
    header.write('in="./traces/' + str(i) + '-traces.rsf@"\n')
    header.write('n1=%d\n' % (Nt))
    header.write('n2=%d\n' % (Ns))

    header.close()

    np.transpose(traces.astype('float32')).tofile('./traces/' + str(i) + '-traces.rsf@')
print N