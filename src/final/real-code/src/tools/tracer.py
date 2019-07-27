#!/usr/bin/python2.7
#!-*- coding: utf8 -*-

import numpy as np;
import matplotlib.pyplot as plt;

# Loading arrays from files
traces = np.loadtxt('./traces/traces.dat');
T      = np.loadtxt('./specs/T.dat');
params = np.loadtxt('./output.dat');

traces = traces.transpose();

# Criando figura
fig = plt.figure();

# Adicionando eixos
fig.add_axes();

# Creating axis for ploting
ax = fig.add_subplot(111);

# Editing details of ploting
title = 'Traces';
ax.set(title=title, ylabel='T', xlabel='Trace');

plt.hold(1);

for i in range(int(params[6])):
    ax.plot(T, traces[i, :]);
    plt.savefig('./traces/' + str(i));
    ax.clear();

