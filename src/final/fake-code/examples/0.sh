#!/bin/bash

clear
make main && \
make run tasks=4 xp=5000 xb=1. xt=8. xw=2. tt=10. tw=.1 freq=25. && \
make plot
