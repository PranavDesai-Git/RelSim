#!/bin/bash
rm -rf out
mkdir out
cmake --build build
./out/RelSym
