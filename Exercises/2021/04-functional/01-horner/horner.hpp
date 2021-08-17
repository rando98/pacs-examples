#ifndef HORNER_HPP
#define HORNER_HPP
#include <vector>
#include <string>

//! Evaluates polynomial in a set of points.
/*!
  @param points  Vector of points to compute the polynomial.
  @param a       Polynomial coefficients.
  @result        A vector with the evaluated points
  @param method  Method to evaluate the polynomial
 */
std::vector<double>
evaluate_poly(const std::vector<double> &points,
              const std::vector<double> &a,
              std::string                method);

#endif /* HORNER_HPP */
