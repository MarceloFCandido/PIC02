#!/bin/bash

clear
make main
time make run xp=5000 xb=0. xt=10. xw=4.5 tt=10. tw=.1 f=25.
make plot
