#!/usr/bin/python2.7
#!-*- coding: utf8 -*-

import numpy as np;
import matplotlib.pyplot as plt;

# Loading data
A = np.fromfile('A.dat', dtype=float);
[x_points, x_ofst, y_points, y_ofst] = np.loadtxt('pmts.dat');

# print x_points;
# print x_ofst;
# print y_points;
# print y_ofst;

# Preparing data for plotting
X = np.linspace(0., x_points * x_ofst, num=int(x_points));
Y = np.linspace(0., y_points * y_ofst, num=int(y_points));
A = A.reshape(int(x_points), int(y_points));

# Preparing plot
fig, ax = plt.subplots();
CS = ax.contour(X, Y, A);
ax.clabel(CS, inline=1, fontsize=10);
ax.set_title('z = x ^ 3 + y ^ 2');

ax.plot();
plt.savefig("A.png");
