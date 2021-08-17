#include "horner.hpp"
#include <algorithm>
#include <execution>
#include <cmath>

double
eval(const std::vector<double> &a, const double &x)
{
  double result{0.0};
  for(std::size_t i = 0; i < a.size(); ++i)
    result += a[i] * std::pow(x,i);

  return result;
}

double
eval_horner(const std::vector<double> &a, const double &x)
{
  double result{a.back()}; // a[n]

  for(std::size_t i = a.size()-1; i > 0; --i)
    result += a[i-1] + x*result;

  return result;

}

std::vector<double>
evaluate_poly(const std::vector<double> &points,
              const std::vector<double> &a,
              std::string method)
{
  std::vector<double> results(points.size());

  auto eval = [&a](double x) -> double
  // I can also say " std::function<double (const std::vector <double> &a, double x)> eval =
                //                                                            [](const std::vector<double> &a, double x) -> double"
  {
    double result{0.0};
    for(std::size_t i = 0; i < a.size(); ++i)
      result += a[i] * std::pow(x,i);

      return result;
  };

  auto eval_horner = [&a](double x) -> double
  {
    double result{a.back()}; // a[n]

    for(std::size_t i = a.size()-1; i > 0; --i)
      result += a[i-1] + x*result;

      return result;
  };

  if (method == "Standard")
    std::transform(std::execution::par, points.cbegin(), points.cend(),
                  results.begin(),
                  eval);
  else if (method == "Horner")
    std::transform(std::execution::par, points.cbegin(), points.cend(),
                  results.begin(),
                  eval_horner);


  return results;


}
