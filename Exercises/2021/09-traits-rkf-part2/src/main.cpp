#include "RKF.hpp"

#include <cmath>
#include <fstream>
#include <iostream>
/* NOTE 1
class CustomRK45_t : public ButcherArray<...>
{
public:
  CustomRK45_t(); // assign coeff
};
*/
int
main(int argc, char **argv)
{
  // Model problem.
  {
    const auto f = [](const double &t, const double &y) { return -10 * y; };
    const auto sol_exact = [](const double &t) { return std::exp(-10 * t); };

    const double       t0          = 0;
    const double       tf          = 10;
    const double       y0          = 1;
    const double       h0          = 0.2;
    const double       tolerance   = 1e-4;
    const unsigned int n_max_steps = 1e4;

    RKF<RKFScheme::RK23_t, RKFType::Scalar> solver(f); // Now I can do this way (without passing the method)
    // The previous version was ugly since I was repeating RKF::RK23_t both in the template argument and in the contructor of solver.
    // Now it is sufficient to provide only the ODE f to solve.

    // For this version the user cannot pass a method anymore since the constructor accept only one argument.
    /// RKFScheme::RK23_t method; // or auto method = RKFScheme::RK23;
    /// RKF<RKFScheme::RK23_t, RKFType::Scalar> solver(f, method); // COMPILER ERROR

    // So what to do if I want to modify a method? I may implement a new class. See NOTE 1 (before the main)
    RKF<CustomRK45_t, RKFType::Scalar> solver1(f); // without second class


    // SO ALL THIS IS A WAY TO SOLVE THE POINT 1 OF THE LAB. BUT THERE IS A BETTER VERSION...SEE IN THE NEXT COMMIT

  //
  //   const auto solution = solver(t0, tf, y0, h0, tolerance, n_max_steps);
  //
  //   // Compute error.
  //   double       max_error = 0;
  //   unsigned int count     = 0;
  //
  //   for (const auto val : solution.y)
  //     max_error =
  //       std::max(max_error, std::abs(val - sol_exact(solution.time[count++])));
  //
  //   std::cout << std::boolalpha;
  //   std::cout << "*** Model problem ***" << std::endl
  //             << "  l_inf error: " << max_error << std::endl
  //             << "  Tolerance: " << tolerance << std::endl
  //             << "  Failed: " << solution.failed << std::endl
  //             << "  Error estimate: " << solution.error_estimate << std::endl;
  //   std::cout << std::endl;
  //
  //   std::ofstream file("results_exp.out");
  //   file << solution;
  // }
  //
  //
  // // Van der Pol oscillator problem with mu = 1.
  // {
  //   const auto f = [](const double &t, const Eigen::VectorXd &y) {
  //     const double mu = 1;
  //
  //     Eigen::VectorXd out(2);
  //     out(0) = y(1);
  //     out(1) = -y(0) + mu * (1 - y(0) * y(0)) * y(1);
  //
  //     return out;
  //   };
  //
  //   const double t0 = 0;
  //   const double tf = 40;
  //
  //   Eigen::VectorXd y0(2);
  //   y0[0] = 1;
  //   y0[1] = 1;
  //
  //   const double       h0          = 0.2;
  //   const double       tolerance   = 1e-4;
  //   const unsigned int n_max_steps = 5e3;
  //
  //   RKF<RKFScheme::RK45_t, RKFType::Vector> solver(RKFScheme::RK45, f);
  //
  //   const auto solution = solver(t0, tf, y0, h0, tolerance, n_max_steps);
  //
  //   std::cout << std::boolalpha;
  //   std::cout << "*** Van der Pol oscillator ***" << std::endl
  //             << "  Tolerance: " << tolerance << std::endl
  //             << "  Failed: " << solution.failed << std::endl
  //             << "  Error estimate: " << solution.error_estimate << std::endl;
  //   std::cout << std::endl;
  //
  //   std::ofstream file("results_VdP.out");
  //   file << solution;
  }

  return 0;
}
