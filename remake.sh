#!/bin/bash

mkdir build

mkdir build/debug
cd build/debug
cmake -DCMAKE_BUILD_TYPE=DEBUG ../..
cd ../..

mkdir build/release
cd build/release
cmake -DCMAKE_BUILD_TYPE=RELEASE ../..
cd ../..
