#!/usr/bin/python2.7
#!-*- coding: utf8 -*-

import numpy as np;
import matplotlib.pyplot as plt;

# Loading data
A = np.fromfile('data/outputs/A.dat', dtype=float);
[x_points, x_ofst, xi, y_points, y_ofst, yi] = np.loadtxt('data/outputs/pmts.dat');

# Preparing data for plotting
X = np.linspace(xi, xi + x_points * x_ofst, x_points);
Y = np.linspace(0., 0. + y_points * y_ofst, y_points);
# print X
# print Y
# print A.shape;
A = A.reshape(int(x_points), int(y_points));

[B, C] = np.meshgrid(X, Y);

# Preparing plot
fig, ax = plt.subplots();
CS = ax.contourf(B, C, A.transpose(), 20, cmap='RdGy');
ax.clabel(CS, inline=False, fontsize=10);
ax.set_title('z = x^2 + y^2');

# plt.xlim(-2, 2);
# plt.ylim(-2, 2);
ax.plot();
plt.savefig("data/images/A.png");
