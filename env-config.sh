clear;
while [[ ((1)) ]]; do
    echo "What do you want to install?"
    read INSTALL
    if [[ $INSTALL = $"armadillo" ]]; then
        # Installing armadillo and this requirements
        sudo apt -y install liblapack-dev;
        sudo apt -y install libblas-dev;
        sudo apt -y install libboost-dev;
        sudo apt -y install libarmadillo-dev;
    elif [[ $INSTALL = $"python-libraries" ]]; then
        sudo apt -y install python-pip;
        sudo apt -y install python-tk;
        sudo pip install numpy matplotlib;
    else
        echo "Invalid option";
    fi
done
