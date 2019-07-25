#!/usr/bin/python2.7
#!-*- coding: utf8 -*-

import numpy as np;
import matplotlib.pyplot as plt;

# Loading data
A = np.fromfile('data/outputs/A.dat', dtype=float);
[x_points, x_ofst, xi, tt, n_tasks] = np.loadtxt('data/outputs/pmts.dat');

# Preparing data for plotting
X = np.linspace(xi, xi + x_points * x_ofst, num=int(x_points));
T = np.linspace(0., tt, num=int(t_points));
A = A.reshape(int(x_points), int(t_points)).transpose();

# TODO: remove this line
[B, C] = np.meshgrid(X, T)

# Preparing plot
M = max(abs(A.min()), abs(A.max()))
fig, ax = plt.subplots();
ax.set_title('Wave in a string');
CS = ax.contourf(B, C, A, 52, cmap='seismic', vmin=-M, vmax=M);
ax.clabel(CS, inline=False, fontsize=10);
plt.xlabel('X')
plt.ylabel('T')

cbar = fig.colorbar(CS)

ax.plot();
# plt.show();
plt.savefig("data/images/A.png");
