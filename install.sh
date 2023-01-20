#!/bin/bash
cd ranging_api/libUWBranging/
make clean && make
cd ../..
sudo cp ranging_api/libUWBranging/libUWBranging.so /usr/local/lib/
sudo ldconfig
make
if [ "$#" -eq 1 ]; then
    echo input number: 1 
    sudo ./bin/main $1
fi
if [ "$#" -eq 2 ]; then 
    echo input number: 2
    sudo terminator -x sudo ./bin/main $1 & sudo terminator -x sudo ./bin/main $2
fi 