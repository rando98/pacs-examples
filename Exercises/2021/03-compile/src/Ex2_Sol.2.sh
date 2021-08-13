#!/bin/bash

# ESERCIZIO 2 - Versione 2
# We can improve the quality of the bash script.
# It is safer to load all the things at the begginig of the script.
# Moreover I create some variables to simplify things

set -x # Prints all the command being executed

module load gcc-glibc
module load eigen suitesparse

EXEC_NAME=test
LIB_NAME=liblinearalgebra.so

INCLUDE_FLAGS="-I../include -I${mkEigenInc} -I${mkSuitesparseInc}"
LIB_FLAGS="-L${mkSuitesparseLib} -lumfpack -L./ -llinearalgebra -Wl,-rpath,./"

CXX="g++ -fPIC"

#Step 0: clean up
rm -f Utilities.o test.o ${LIB_NAME} ${EXEC_NAME}

#Step1: Generate object file Utilities.o from Utilities.cpp
${CXX} -c ${INCLUDE_FLAGS} Utilities.cpp -c

#Step2: generate shared library liblinearalgebra.so strating from Utilities.o
${CXX} -shared -Wl,-soname,${LIB_NAME} Utilities.o -o ${LIB_NAME}

#Step3: generate test.o from test.cpp
${CXX} -c  ${INCLUDE_FLAGS} test.cpp

#Step4: link linearalgebra.so and test.o to generate the executable "test"
${CXX} ${LIB_FLAGS} test.o -o ${EXEC_NAME}

set +x # Reset x variable
