#!/bin/bash

clear
make main
make run xp=500 xb=0. xt=10. xw=5. tt=10. tw=.1 f=.25
make plot
