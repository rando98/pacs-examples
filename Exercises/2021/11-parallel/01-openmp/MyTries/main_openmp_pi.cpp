#include <omp.h>

#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

/*! \brief pi = \int_{0}^{4} 4/(1+x^2) dx
*
*		We can compute the value of pi by aproximating the integral above,
*		for example, composite midpoint rule. THIS IS THE PARALLEL VERSION.
* 	As you can see
*/
int
main(int argc, char **argv)
{
	const int n = 1e+8;
	const double h = 1.0/n;

	double sum = 0;

#pragma omp parallel
{

#pragma omp for reduction(+ : sum) // The reduction is needed to sum all the values of the variable sum coming from the different threads!
	for (unsigned int i=0; i<n; i++)
	{
		double x= h*(i+0.5);
		sum += 4.0/(1+x*x);

	}

	double pi = h*sum;


#pragma omp critical
{
	std::cout << std::setprecision(16) << "Computed " << pi << std::endl;
	std::cout << std::setprecision(16) << "Exact " << M_PI << std::endl;
}
}
	return 0;

}
