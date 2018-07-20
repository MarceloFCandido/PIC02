#!/bin/bash

./cli.exe < $("data/inputs/$1")
./velocities.exe
./main.exe
python snapshoter.py
shotwell "data/images/*" &
