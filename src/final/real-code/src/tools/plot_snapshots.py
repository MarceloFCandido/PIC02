#!/usr/bin/python2.7
#!-*- coding: utf8 -*-
 
import sys
import numpy as np
import matplotlib.pyplot as plt
import re
import glob

M = -1

# Set fized amplitude value 
if( len(sys.argv) > 1 ):
    M = float(sys.argv[1])

# Carregando arrays a partir de arquivos
X      = np.loadtxt('./specs/X.dat')
Y      = np.loadtxt('./specs/Y.dat')
params = np.loadtxt('./specs/output.dat')
inter  = np.loadtxt('./specs/interfaces.dat', ndmin=2 )
    
xx = X[([0,-1])]

# Criando figura
fig = plt.figure()

# Adicionando eixos
fig.add_axes()

# Criando eixo para plotagem
ax = fig.add_subplot(111)

# Formando base para o plot (?)
[Y, X] = np.meshgrid(Y, X)

# Colocando limites no plot
plt.xlim(0., params[4])
plt.ylim(0., params[5])

# Invertendo o eixo y
plt.gca().invert_yaxis()

# Search for all snapshot files
dat_files = sorted( glob.glob( "./snaps/*.dat" ) )

add_colorbar = True

# Create an image for each snapshot
for dat_file in dat_files:

    Z = np.loadtxt( dat_file )

    # Amplitude for ploting 
    if( M < 0 ):
       M = 0.8 * max( abs(Z.min()), abs(Z.max()) )

    png_file = dat_file.replace( ".dat", ".png" ).replace( "snaps/", "snaps/snap_" )

    print "Creating file %s"%( png_file )

    # Criando plot
    plot = ax.contourf( X, Y, Z, np.linspace(-M,M,51), cmap=plt.cm.seismic, vmin=-M, vmax=M )

    # Desenhando a barra de cores
    if( add_colorbar ):
        plt.colorbar(plot)
        add_colorbar = False

    # Draw interfaces

    for ii in range(inter.shape[0]):
        plt.plot( xx, inter[ii,0]*xx+inter[ii,1] , '-k' )


    # Salvando a imagem
    plt.savefig( png_file )

