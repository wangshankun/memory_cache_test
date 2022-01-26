#!/bin/sh
rm -rf test test_false sample
g++  test.cpp  -std=gnu++11 -pthread -o test
g++  test_false.cpp  -std=gnu++11 -pthread -o test_false
g++  sample.cpp  -std=gnu++11 -pthread -o sample
