#!/usr/bin/python2.7
#!-*- coding: utf8 -*-

import numpy as np
import matplotlib.pyplot as plt

# Loading data
A = np.fromfile('data/outputs/A.dat', dtype=float)
[x_points, x_ofst, xi, tt, t_points, n_tasks] = \
    np.loadtxt('data/outputs/pmts.dat')

# Preparing data for plotting
X = np.linspace(xi, xi + x_points / n_tasks * x_ofst, num=int(x_points / n_tasks))
T = np.linspace(0., tt, num=int(t_points))
A = A.reshape(int(x_points), int(t_points))

# TODO: remove this line
[B, C] = np.meshgrid(X, T)

# Preparing plot
for i in range(0, int(n_tasks)):
    M = max(abs(A[int(i * (x_points / n_tasks)):int((i + 1) * (x_points / n_tasks))].min()), 
            abs(A[int(i * (x_points / n_tasks)):int((i + 1) * (x_points / n_tasks))].max()))

    fig, ax = plt.subplots()
    ax.set_title('Wave in a string')
    CS = ax.contourf(C, B, A[int(i * (x_points / n_tasks)):int((i + 1) * (x_points / n_tasks))].transpose(), 
        52, cmap='seismic', vmin=-M, vmax=M)
    ax.clabel(CS, inline=False, fontsize=10)
    plt.xlabel('T')
    plt.ylabel('X')
    cbar = fig.colorbar(CS)

    ax.plot()
    plt.savefig('data/images/A' + str(i) + '.png')
