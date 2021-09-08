# main_openmp_helloWorld.cpp
To compile the code
g++ -fopenmp main_openmp.cpp -o main_openmp

To set the number of threads
OMP_NUM_THREADS = *something* ./main_openmp
or
export OMP_NUM_THREADS = *something* (in this case the variable is changed permanently in the bash, until the terminal is on)


Remember that variables instructions defined outside the #pragma are run only by the master thread (which is typycally the thread number 0)

Note the difference beetween shared and private variables. By default in openmp all variables are SHARED!

Note that usually the printed output of the program is strange (righe attacate, numeri stampati di qua e di la). This because std::cout is
buffered, and the thread can write to the buffer at same time. Use #pragma omp critical to print on the screen in a nice way.


# main_openmp_forLoops.cpp

See #pragma omp (parallel) for schedule on the site http://jakascorner.com/blog/2016/06/omp-for-scheduling.html
