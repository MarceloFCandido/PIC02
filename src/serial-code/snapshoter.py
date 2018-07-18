#!/usr/bin/python2.7
#!-*- coding: utf8 -*-

import numpy as np
import matplotlib.pyplot as plt

# TODO: traduzir para o ingles

# Carregando arrays a partir de arquivos
X = np.loadtxt('data/specs/X.dat')
Y = np.loadtxt('data/specs/Y.dat')
U = np.loadtxt('data/outputs/U.dat')
params = np.loadtxt('data/outputs/d.dat')

counter = 0

# Criando figura
fig = plt.figure()

# Adicionando eixos
fig.add_axes()

# Criando eixo para plotagem
ax = fig.add_subplot(111)

# Formando base para o plot (?)
[Y, X] = np.meshgrid(Y, X)

Z = np.zeros((int(params[0]), int(params[1]), int(params[2])))
tamX = int(params[0])
j = 0
for i in range(0, int(params[3])):
    Z[:, :, i] = U[(j * tamX):((j + 1) * tamX), :]
    j += 1

# TODO: os marcadores devem ser passados por parametro
# markers = np.array([(0., 0.), (1.5, 1.9), (3., 2.3), (4., 3.8), (6.5, 8.)], dtype=(float, 2))

# Colocando limites no plot
plt.xlim(0., params[4])
plt.ylim(0., params[5])

# Invertendo o eixo y
plt.gca().invert_yaxis()

# Cria as imagens de N em N quadros
for i in range(0, int(params[3])):
    # Buscando o maior valor de U para fixar o eixo em z
    M = max(abs(U.min()), abs(U.max()))
    # Criando plot
    ax.contourf(X, Y, Z[:,:,i], 20, cmap=plt.cm.seismic, vmin=-M, vmax=M)
    # Plotando as Camadas
    # for i in range(0, markers.size / 2):
    #     # TODO: Trocar o 15. por uma variavel passada por parametro (uI.py)
    #     ax.plot((0., params[0]), (markers[i][0], markers[i][1]), '-k')
    # Configurando o titulo do grafico e suas legendas
    ax.set(title='Onda em 2D', ylabel='Y', xlabel='X')

    # Definindo titulo da plotagem
    titulo = "Teste 0%d - MDF - 1D" % counter

    # Definindo caminho da plotagem
    caminho = 'data/images/Teste0%d.png' % counter

    # Incrementando o contador
    counter += 1

    # Salvando a imagem
    plt.savefig(caminho)
