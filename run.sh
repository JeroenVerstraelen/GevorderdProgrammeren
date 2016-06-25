#!/bin/bash

cd build
cmake ..
make install
cd ../bin
./space
