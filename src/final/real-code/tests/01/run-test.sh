#!/bin/bash
#------------------------------------------------------------------------------#
# Wave propagation
#
# run-test test01
#------------------------------------------------------------------------------#

# exit when any command fails
set -e

# Remove previos files
make clean

# Path to executables (Works only inside the script)
PATH="../../bin:${PATH}"

# Create directories if necessary
mkdir -p specs velocity snaps traces

# Run test
#------------------------------------------------------------------------------#

# Specs
#  SIZE_X      Tamanho em x
#  SIZE_Y      Tamanho em y
#  TMAX        Tempo maximo de animacao
#  NX          Numero de pontos em x
#  NY          Numero de pontos em y
#  OMEGA       Omega
#  AMPLITUDE   Amplitude da onda
#  SOURCE_X    Posicao em x do pico do pulso da onda
#  SOURCE_Y    Posicao em y do pico do pulso da onda
#  SOURCE_T    Tempo de pico do pulso da fonte
#  N_INTER     Numero de interfaces/velocidades (interfaces + 1)
#
#  Para cada camada:
#     VEL_i    Coeficientes da funcao de velocidade            (a,b,c)  na função v = ax + by + c
#     INTER_i  Coeficientes da reta que descreve a interface   (a,b)    na funçao y = ax + b
#
#  SNAPS      Write snapshots (1:yes 0:no)
#     N_SNAPS  If yes, how many
#
#  N_SOURCES  How many sources
#  S_OFFSET   Offset between sources

echo Create the specs
cli.out <<EOF
SIZE_X      4
SIZE_Y      4
TMAX        8.
NX          60
NY          60
OMEGA       50
AMPLITUDE   100.0
SOURCE_X    1.0
SOURCE_Y    0.5
SOURCE_T    0.1
SOURCE_DX   .5
N_INTER     3
VEL_0       0.0   0.0   2.0
INTER_0     0.1   1.0
VEL_1       0.0   0.0   3.0
INTER_1     0.2   2.0
VEL_2       0.0   0.0   4.0
INTER_2    -0.1   3.6
VEL_F       0.0   0.0   5.0
SNAPS       1
N_SNAPS     21
N_REC       20
REC_OFFSET  .2
N_THREADS   12
EOF

echo 'Create the velocity model'
velocities.out

echo Run the modeling
mpirun -n $1 main.out

echo 'Convert dat (ascii) to rsf (binary)'
ARG1=$(traces2rsf)
echo 'Create images'
plot_traces $ARG1
plot_velocity
plot_snapshots 0.01

#------------------------------------------------------------------------------#
