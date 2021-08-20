/*
PIAZZA NOTE #42
HERE I ALSO LEARN HOW TO PRINT THE TYPE OF A VARIBALE, USING BOOST LIBRARY!
*/

#include <iostream>
#include <complex>
#include <tuple>
#include <boost/type_index.hpp>

// a trick to make it working for complex is to use template functions
template <class T>
std::tuple<T,unsigned int> Sqrt(T const & x)
{
  using Scalar =decltype(std::abs(x)); //PERCHE' DIAVOLO FA COSI'?? TANTO SCALAR SARA' SEMPRE UN DOUBLE (O FLOAT, O QUALSIASI COSA USO NEL MAIN)!
  unsigned int counter = 0u;
  constexpr unsigned int max_iter=100;
  if (x==0.0 || x==1.0)return {x,counter};
  Scalar tol = 10.0*std::numeric_limits<Scalar>::epsilon();
  std::cout << "\n Readable type name: " << boost::typeindex::type_id<decltype(tol)>().pretty_name() << std::endl;
  // Starting point (it can be bettered)
  T result = 0.5*(std::abs(x)> 1.0? x: T{1.0});
  T prevresult=0.0;
  while (std::abs(result-prevresult)>tol && counter++<max_iter)
  {
    prevresult=result;
    result = (result + x/result)*0.5;
  }
  return {result,counter};
}

int main(int argc, char *argv[])
{
    double x0=9;
    std::complex<double> z(0,1);

    std::cout << "\n Readable type name: " << boost::typeindex::type_id<decltype(x0)>().pretty_name() << std::endl;
    std::cout << "\n Readable type name: " << boost::typeindex::type_id<decltype(z)>().pretty_name() << std::endl;


    auto [sol, iter] = Sqrt(x0);
    auto [solz, iterz] = Sqrt(z);

    std::cout << "Real Solution: " << sol << "\tIter: " << iter << std::endl;

    std::cout << "Complex Solution: " << solz << "\tIter: " << iterz << std::endl;

    return 0;
}


