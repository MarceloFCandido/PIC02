#!/usr/bin/python2.7
#!-*- coding: utf8 -*-

import numpy as np;
import matplotlib.pyplot as plt;

# Loading data
A = np.fromfile('data/outputs/A.dat', dtype=float);
[x_points, x_ofst, xi, tt, t_points] = np.loadtxt('data/outputs/pmts.dat');


# Preparing data for plotting
X = np.linspace(xi, xi + x_points * x_ofst, num=int(x_points));
T = np.linspace(0., tt, num=int(t_points));
A = A.reshape(int(t_points), int(x_points));

# print X.shape;
# print Y.shape;
# print A.shape;

[B, C] = np.meshgrid(X, T)

# Preparing plot
fig, ax = plt.subplots();
ax.set_title('Wave in a string');
CS = ax.contourf(B, C, A, 20, cmap='RdGy');
ax.clabel(CS, inline=False, fontsize=10);
plt.xlabel('X')
plt.ylabel('T')

# plt.xlim(-2, 2);
# plt.ylim(-2, 2);
ax.plot();
plt.savefig("data/images/A.png");
