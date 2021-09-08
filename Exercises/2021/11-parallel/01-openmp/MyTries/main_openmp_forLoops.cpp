#include <omp.h>
#include <iostream>
#include <vector>

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
#pragma omp parallel shared(n_threads) private(thread_id)
	{
		thread_id = omp_get_thread_num(); //!< SHOULD BE DECLARED PRIVATE!

// #pragma omp master
#pragma omp single
		{
			n_threads = omp_get_num_threads();

		}


	std::vector<int> a(10);

#pragma omp for schedule(static,2) // Note that the #pragma omp for directive must be used in a pragma omp parallel scope.
	for (int i=0; i<a.size(); ++i)
	{
		a[i]=i;

#pragma omp critical
		std::cout << "thread: " << thread_id << ", i=" << i << std::endl;

	}

	}

	return 0;

}

