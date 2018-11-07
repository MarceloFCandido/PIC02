#!/usr/bin/python2.7
#!-*- coding: utf8 -*-

import numpy as np;
import matplotlib.pyplot as plt;

# Loading data
A = np.fromfile('data/outputs/A.dat', dtype=float);
[x_points, x_ofst, xi, y_points, y_ofst, yi] = np.loadtxt('data/outputs/pmts.dat');


# Preparing data for plotting
X = np.linspace(xi, xi + x_points * x_ofst, num=int(x_points));
Y = np.linspace(yi, yi + y_points * y_ofst, num=int(y_points));
# print X.shape;
# print Y.shape;
# print A.shape;
A = A.reshape(int(x_points), int(y_points));


# Preparing plot
fig, ax = plt.subplots();
CS = ax.contourf(X, Y, A.transpose(), vmin=-A.max(), vmax=A.max());
ax.clabel(CS, inline=1, fontsize=10);
ax.set_title('z = x ^ 3 + y ^ 2');

# plt.xlim(-2, 2);
# plt.ylim(-2, 2);
ax.plot();
plt.savefig("data/images/A.png");
