clear;
while [[ ((1)) ]]; do
    echo "What do you want to install?"
    read INSTALL
    if [[ $INSTALL = $"armadillo" ]]; then
        # Installing armadillo and this requirements
        sudo apt-get install liblapack-dev;
        sudo apt-get install libblas-dev;
        sudo apt-get install libboost-dev;
        sudo apt-get install libarmadillo-dev;
    elif [[ $INSTALL = $"python-libraries" ]]; then
        sudo apt install python-pip;
        sudo apt install python-tk;
        sudo pip install numpy matplotlib;
    else
        echo "Invalid option";
    fi
done
