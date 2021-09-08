#include <omp.h>
#include <iostream>

/*! \brief HOW TO COMPILE THE CODE
*
*	g++ -fopnemp main_openmp.cpp -o main
*	Note what happens in this cases!
*/
int
main(int argc, char** argv)
{
		int thread_id = omp_get_thread_num();
		int n_threads = omp_get_num_threads(); //!< Total number of threads

/*! A better thing to do is to declare thread_id
*	and n_threads as locale variable inside the
*	scope of the #pragma, bur sometimes you anyway
*	need global variables for the different threads.
*
*/
#pragma omp parallel shared(n_threads)
	{
		thread_id = omp_get_thread_num(); //!< SHOULD BE DECLARED PRIVATE!

#pragma omp master //better to use #pragma omp single since n_threads are eqaul for all the threads!
		{
			n_threads = omp_get_num_threads();

		}
// better to use #pragma omp critical
		std::cout << "Hello world from thread " << thread_id << " out of" << n_threads << std::endl;

	}

	return 0;

}

