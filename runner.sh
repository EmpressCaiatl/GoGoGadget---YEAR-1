#!/bin/bash
#Do 'chmod u+x runner.sh' before running (one time and it's good forever)
g++ skynet.cpp -std=c++11
./a.out gadgets.source gadgets.h
g++ ast5.cpp -std=c++11
./a.out
