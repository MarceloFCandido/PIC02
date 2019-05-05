#!/bin/bash

clear
make
make run tasks=4 xp=100 xb=-5. xe=5. yp=100 yb=-5. ye=5.
make plot
