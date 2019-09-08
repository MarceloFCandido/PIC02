#!/usr/bin/python2.7
#!-*- coding: utf8 -*-

import numpy as np
import matplotlib.pyplot as plt
import re

# TODO: traduzir para o ingles

# Carregando arrays a partir de arquivos
X      = np.loadtxt('./specs/X.dat')
Y      = np.loadtxt('./specs/Y.dat')
params = np.loadtxt('./specs/output.dat')

counter = 0

# Criando figura
fig = plt.figure()

# Adicionando eixos
fig.add_axes()

# Criando eixo para plotagem
ax = fig.add_subplot(111)

# Formando base para o plot (?)
[Y, X] = np.meshgrid(Y, X)

# TODO: os marcadores devem ser passados por parametro
# markers = np.array([(0., 0.), (1.5, 1.9), (3., 2.3), (4., 3.8), (6.5, 8.)], dtype=(float, 2))

# Colocando limites no plot
plt.xlim(0., params[4])
plt.ylim(0., params[5])

# Invertendo o eixo y
plt.gca().invert_yaxis()

# Cria as imagens de N em N quadros
ans = 1
while ans == 1:
    print 'Which snapshot do you want to see?'
    name = str(raw_input())
    Z = np.loadtxt('./snaps/' + name + '.dat')

    # M = max(abs(Z.min()), abs(Z.max()))
    M = abs(Z.mean())
    # Buscando o maior valor de U para fixar o eixo em z
    # Criando plot
    ax.contourf(X, Y, Z, 20, cmap=plt.cm.seismic, vmin=-M, vmax=M)
    # Plotando as Camadas
    # for i in range(0, markers.size / 2):
    #     # TODO: Trocar o 15. por uma variavel passada por parametro (uI.py)
    #     ax.plot((0., params[0]), (markers[i][0], markers[i][1]), '-k')

    # Configurando o titulo do grafico e suas legendas
    m = re.search(r'\d+', name)
    title = "Time " + str(m.group()) + " - FDM - 2D"
    ax.set(title=title, ylabel='Y', xlabel='X')

    # Definindo caminho da plotagem
    caminho = './snaps/Time' + str(m.group()) + '.png'

    # Incrementando o contador
    counter += 1

    # Salvando a imagem
    plt.savefig(caminho)

    # Asking the user if he/she wants another snapshot
    print 'Do you want to see another snapshot? (1/0)'
    ans = input()
