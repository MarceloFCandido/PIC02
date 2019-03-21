#!/bin/bash

clear
make main
make run xp=1000 xb=0. xt=10. xw=5.5 tt=10. tw=.1 f=10.
make plot
