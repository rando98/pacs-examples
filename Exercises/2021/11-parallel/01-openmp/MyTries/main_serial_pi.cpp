#include <omp.h>

#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

// NOTE THAT YOU CAN RUN THE SERIAL VERSION ALSO FROM main_openmp_pi.cpp SETTING OMP_NUM_THREADS=1

/*! \brief pi = \int_{0}^{4} 4/(1+x^2) dx
*
*		We can compute the value of pi by aproximating the integral above,
*		for example, composite midpoint rule.
*		This is the SERIAL VERSION. As you can verifu usig te time function of linux
*		(write *time ./main_serial_pi* on command line, the operation take a very high time to perform)
*		In the nexy code we will parallelize using openmp
*/
int
main(int argc, char **argv)
{
	const int n = 1e+8;
	const double h = 1.0/n;

	double sum = 0;
	for (unsigned int i=0; i<n; i++)
	{
		double x= h*(i+0.5);
		sum += 4.0/(1+x*x);

	}

	double pi = h*sum;


	std::cout << std::setprecision(16) << pi << std::endl;
	std::cout << std::setprecision(16) << M_PI << std::endl;

	return 0;

}
