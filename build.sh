#!/bin/bash

cd build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_MAKE_PROGRAM=ninja -G Ninja .
ninja
cd ..
./output/learning_factory
ls