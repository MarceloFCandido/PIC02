#!/bin/bash

clear;
make;
make run 0=150 1=.2 2=0. 3=1500 4=.5 5=0.;
make plot;
eog data/images/A.png;
