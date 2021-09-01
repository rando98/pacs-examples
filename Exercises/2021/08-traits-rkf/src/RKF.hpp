#ifndef RKF_HPP
#define RKF_HPP

#include "RKFTraits.hpp"
#include "ButcherRKF.hpp"

#include <iostream>
#include <utility>

template<class Type>
class RKFResult
{
public:
  std::vector<double> time;
  std::vector<Type> y;

  double error_estimate;

  unsigned int n_iter;
  unsigned int n_expansions;
  unsigned int n_reductions;
};

template<class ButcherType, class Type>
class RKF
{
public:

  RKF() = default;

  RKF(const ButcherType& table_, const typename RKFTraits<Type>::FunctionType& function_)
    : table(table_) , function(function_)
  {
    static_assert(
      std::is_same_v<Type, ProblemType::Scalar> ||
      std::is_same_v<Type, ProblemType::Vector> ,
      "Wrong ProblemType specified"); // static_assert is evaluated at COMPILE TIME!

   static_assert(
     std::is_same_v<ButcherType, RKFScheme::RK45_t> ||
     std::is_same_v<ButcherType, RKFScheme::RK23_t> ||
     std::is_same_v<ButcherType, RKFScheme::RK12_t> ,
     "Wrong ButcherType specified");
  }

  void
  set_table(const ButcherType& table_)
  {
    table = table_;
  }

  void
  set_function(const typename RKFTraits<Type>::FunctionType& function_)
  {
    function = function_;
  }

  std::pair<Type, Type>
  step(
    const double& t,
    const Type& y,
    const double& h)
  {
    const auto& A   = table.A;
    const auto& b1  = table.b1;
    const auto& b2  = table.b2;
    const auto& c   = table.c;

    std::array<double, ButcherType::n_stages()> k;

    k[0] = function(t,y) * h; // because fot the RKF method c[0] = 0, A[0,:] = 0

    for(std::size_t i=1; i < k.size(); ++i)
    {
      double time = t + c[i]*h;

      Type yy{y};

      for(std::size_t j=0; j<i; ++j)
        yy += h*A[i][j]*k[j];

      k[i] = function(time, yy);
    }

    Type y_low = y;
    Type y_high = y;

    for(std::size_t i=0; i < k.size(); ++i)
    {
      y_low += h*k[i]*b1[i];
      y_high += h*k[i]*b2[i];
    }
    return std::make_pair(y_low, y_high);
  }


  RKFResult<Type>
    solve(
      const double& t0, const double& tf,
      const Type& y0,
      const double& h0, const double& tol, const unsigned int& n_max_steps)
  {

    // Structured binding (c++17)
    auto &[time, y, error_estimate, n_iter, n_expansions, n_reductions] = result;

    time.emplace_back(t0);
    y.emplace_back(y0);

    double time_curr = t0;

    Type y_curr = y0;
    double h = h0;

    bool rejected = false;

    for(n_iter = 0; n_iter < n_max_steps; ++n_iter)
    {
      const auto [y_low, y_high] = step(time_curr, y_curr, h);

      double error = norm(y_high - y_low);
      std::cout << error << std::endl;

      if(error < tol*h / (tf-t0))
      {
        rejected = false;

        time_curr += h;
        y_curr = y_high;

        time.emplace_back(time_curr);
        y.emplace_back(y_curr);

        error_estimate += error;

        h *= 1.2; // Can be generalized
        ++n_expansions;
      }
      else
      {
        rejected = true;

        h *= 0.8; // Can be generalized
        ++n_reductions;
      }

      if (time_curr >= tf)
        break;
    }

    // if(time_curr < tf && n_iter == n_max_steps)
    //   throw std::runtime_error("Final time not reached");

    return result;
  }

private:
  ButcherType table; // The specific RKF method to apply (e.g., RKF45)
  typename RKFTraits<Type>::FunctionType function; // THE ODE to solve
  RKFResult<Type> result;
};

// SKETCH OF SOLVER ALGORITHM
// for(timestep = 0; ...)
// {
//   1. compute y of low-order (using b)
//   2. compute y of high-order (using b*)
//
//   if(norm(y_high - y_low) < tol)
//     next_delta_t = delta_t * 1.2
//     move to next_timestep
//   else
//     delta_t = delta_t * 0.8
// }


//Output stream for gnuplot.
//Possible extension: export also an exact solution, if provided.
template <class Type>
std::ostream &
operator<<(std::ostream &out, const RKFResult<Type> &res)
{
  out << "# Number ot time steps: " << res.time.size() << std::endl
      << "# Number of reductions: " << res.n_reductions << std::endl
      << "# Number of expansions: " << res.n_expansions << std::endl
      << "# Error estimate: " << res.error_estimate << std::endl;

  double h_min = res.time[1] - res.time[0];
  double h_max = h_min;

  for (unsigned int i = 0; i < res.time.size() - 1; ++i)
    {
      const auto dt = res.time[i + 1] - res.time[i];
      h_max         = std::max(h_max, dt);
      h_min         = std::min(h_min, dt);
    }

  out << "# h_min: " << h_min << ", h_max: " << h_max << std::endl;

  out << "# t ";
  if constexpr (std::is_same_v<Type, ProblemType::Scalar>)
    out << "y";
  else // if constexpr (std::is_same_v<Type, RKFTraits<Type>::Vector>)
    out << "y[0] ... y[" << res.y[0].size() - 1 << "]";

  out << std::endl;

  size_t i = 0;
  for (const auto &t : res.time)
    {
      out << "  " << t << "\t";
      const auto &yy = res.y[i];

      if constexpr (std::is_same_v<Type, ProblemType::Scalar>)
        {
          out << res.y[i];
        }
      else // if constexpr (std::is_same_v<Type, ProblemType::Vector>)
        {
          for (int k = 0; k < yy.size(); ++k)
            out << yy[k] << "\t";
        }

      out << "\n";
      ++i;
    }
  return out;
}

#endif /* RKF_HPP */
