#!/bin/bash

# ESERCIZIO 2 - Version 1
# It is really inconventient to do all the command in exercise 1 singularly in the terminal. Let'write a script.

module load eigen
module load suitesparse

rm -f Utilities.o liblinearalgebra.so test.o test

#Step1: Generate object file Utilities.o from Utilities.cpp
g++ -fPIC -c -I../include/ -I${mkEigenInc} Utilities.cpp -c

#Step2: generate shared library liblinearalgebra.so strating from Utilities.o
g++ -shared -Wl,-soname,liblinearalgebra.so Utilities.o -o liblinearalgebra.so

#Step3: generate test.o from test.cpp
module load suitesparse
g++ -c  -I../include -I${mkEigenInc} -I${mkSuitesparseInc} test.cpp

#Step4: link linearalgebra.so and test.o to generate the executable test
g++ -L${mkSuitesparseLib} -lumfpack -L./ -llinearalgebra -Wl,-rpath,./ test.o -o test
