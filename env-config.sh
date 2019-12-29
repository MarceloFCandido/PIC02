#!/bin/bash

clear;

# For installing required packages
while [[ ((1)) ]]; do
    echo "What do you want to install?"
    read INSTALL
    if [[ $INSTALL = $"armadillo" ]]; then
        # Installing armadillo and this requirements
        sudo apt -y install liblapack-dev;
        sudo apt -y install libblas-dev;
        sudo apt -y install libboost-dev;
        sudo apt -y install libarmadillo-dev;
    elif [[ $INSTALL = $"python" ]]; then
        sudo apt -y install python-pip;
        sudo apt -y install python-tk;
	    sudo pip install --upgrade pip
        sudo pip install numpy matplotlib;
    elif [[ $INSTALL = $"latex" ]]; then
    	sudo apt -y install biber;
    	sudo apt -y install texlive-lang-portuguese;
    elif [[ $INSTALL = $"mpi" ]]; then
    	sudo apt -y install libopenmpi-dev openmpi-bin openmpi-doc;
    else
        echo "Invalid option";
    fi
done
