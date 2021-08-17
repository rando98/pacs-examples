#ifndef NEWTON_HPP
#define NEWTON_HPP

#include <functional>
#include <utility>

class newton_solver
{
public:
  // contructor
  newton_solver(std::function<double (double)> f,
                std::function<double (double)> df,
                unsigned int n_max, double tol);

  //solver
  std::pair<double, std::size_t>
  solve(double x0);

private:
  std::function<double (double)> fun;
  std::function<double (double)> fun_prime;

  unsigned int n_max_iter;
  double tolerance;


};




#endif // NEWTON_HPP
