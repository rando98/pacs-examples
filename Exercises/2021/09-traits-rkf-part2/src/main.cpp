#include "RKF.hpp"

#include <cmath>
#include <fstream>
#include <iostream>


int
main(int argc, char **argv)
{
  // Model problem.
  {
    const auto f = [](const double &t, const double &y) { return -10 * y; };
    const auto sol_exact = [](const double &t) { return std::exp(-10 * t); };

    std::shared_ptr<ButcherArray> table;

    std::string type{argv[1]};

    if(type == "RK23")
      table = std::make_shared<RKFScheme::RK23_t>();
    else if(type == "RK45")
      table = std::make_shared<RKFScheme::RK45_t>();
    else if(type == "RK12")
      table = std::make_shared<RKFScheme::RK12_t>();


    RKF<RKFType::Scalar> solver(f, table);

    RKFOptions<RKFType::Scalar> options; // WE could even pass to the contructor option, declaring before
    options.parse_from_file("data_ex.pot");
    solver.set_options(options);

    const auto solution = solver();

    // Compute error.
    double       max_error = 0;
    unsigned int count     = 0;

    for (const auto val : solution.y)
      max_error =
        std::max(max_error, std::abs(val - sol_exact(solution.time[count++])));

    std::cout << std::boolalpha;
    std::cout << "*** Model problem ***" << std::endl
              << "  l_inf error: " << max_error << std::endl
              << "  Tolerance: " << options.tolerance << std::endl
              << "  Failed: " << solution.failed << std::endl
              << "  Error estimate: " << solution.error_estimate << std::endl;
    std::cout << std::endl;

    std::ofstream file("results_exp.out");
    file << solution;
  }


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
  //   RKFOptions<RKFType::Vector> options2;
  //   // WE can parse from file or even hard-code the parameters!
  //   // options2.t0 = 0;
  //   // options2.tf = 40;
  //   //
  //   // options2.y0.resize(2);
  //   // options2.y0[0] = 1;
  //   // options2.y0[1] = 1;
  //   //
  //   // options2.h0          = 0.2;
  //   // options2.tolerance   = 1e-4;
  //   // options2.n_max_steps = 5e3;
  //
  //   options2.parse_from_file("data_VdP.pot", 2);
  //   RKF<RKFScheme::RK45_t, RKFType::Vector> solver(f, options2);
  //
  //   const auto solution = solver();
  //
  //   std::cout << std::boolalpha;
  //   std::cout << "*** Van der Pol oscillator ***" << std::endl
  //             << "  Tolerance: " << options2.tolerance << std::endl
  //             << "  Failed: " << solution.failed << std::endl
  //             << "  Error estimate: " << solution.error_estimate << std::endl;
  //   std::cout << std::endl;
  //
  //   std::ofstream file("results_VdP.out");
  //   file << solution;
  // }

  return 0;
}
