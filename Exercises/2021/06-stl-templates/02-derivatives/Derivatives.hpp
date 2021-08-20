#ifndef DERIVATIVES_HPP
#define DERIVATIVES_HPP

#include<functional>

template <unsigned int N>
class NthDerivative
{
public:

  NthDerivative(const NthDerivative<N-1>& f, const double& h)
    : previous_derivative(f), h(h)
  {}

  double
  operator()(const double& x)
  {
    return previous_derivative(x+h) - previous_derivative((x)) / h;
  }
private:
  NthDerivative<N-1> previous_derivative;
  double h;
};

// Specialization for N=1
template<>
class NthDerivative<1>
{
public:
  NthDerivative(const std::function<double(double)>& f, const double& h)
    : f(f), h(h)
  {};

  double
  operator()(const double& x)
  {
    return (f(x+h)-f(x)) / h;
  }

private:
  std::function<double(double)> f;
  double h;
};


#endif /* DERIVATIVES_HPP */
