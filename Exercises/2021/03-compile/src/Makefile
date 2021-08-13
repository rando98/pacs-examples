EXEC_NAME=test
LIB_NAME=liblinearalgebra.so

INCLUDE_FLAGS=-I../include -I${mkEigenInc} -I${mkSuitesparseInc}
LIB_FLAGS=-L${mkSuitesparseLib} -lumfpack -L./ -llinearalgebra \
-Wl,-rpath,./

CXX=g++ -fPIC

all: test
	echo "This is the defualt target!"

print:
	echo "Hello world!"
	echo "Hello world!"
clean:
	rm -f Utilities.o test.o $(LIB_NAME) test

Utilities.o: Utilities.cpp
	$(CXX) -c $(INCLUDE_FLAGS) Utilities.cpp -c

liblinearalgebra.so: Utilities.o
	g++ -shared -Wl,-soname,$(LIB_NAME) Utilities.o -o $(LIB_NAME)


test.o: test.cpp
	$(CXX) -c $(INCLUDE_FLAGS) test.cpp

$(EXEC_NAME): test.o liblinearalgebra.so
	$(CXX) $(LIB_FLAGS) test.o -o $(EXEC_NAME)

