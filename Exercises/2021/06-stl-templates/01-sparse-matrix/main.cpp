#include "sparse_matrix.hpp"

#include <iomanip>
#include <iostream>
#include <map>
#include <vector>

int
main(int argc, char **argv)
{
  const unsigned int n = 10;

  sparse_matrix A;
  A.resize(n);

  for (unsigned int ii = 0; ii < n; ++ii)
    {
      if (ii > 0)
        A[ii][ii - 1] = -1;

      if (ii < n - 1)
        A[ii][ii + 1] = -1;

      A[ii][ii] = 4;
    }

  std::vector<unsigned int> i,j;
  std::vector<double> a;

  A.csr(a,i,j);

  // for(auto aa : a)
  //   std::cout << aa << " ";
  // std::cout << std::endl;
  //
  // for(auto ii : i)
  //   std::cout << ii << " ";
  // std::cout << std::endl;
  //
  // for(auto jj : j)
  //   std::cout << jj << " ";
  // std::cout << std::endl;

  // std::cout << "Loop through matrix entries:" << std::endl;
  // for (unsigned int ii = 0; ii < n; ++ii)
  //   for (const auto &[jj, val] : A[ii])
  //     std::cout << "A[" << ii << "][" << jj << "] = " << val << std::endl;
  // std::cout << std::endl << std::endl;

  //std::cout << "Stream operator:" << std::endl;
  //std::cout << A;
  operator << (operator<<(std::cout, "Stream operator:"), "\n"); //std::cout << "Stream operator:" << "\n";
  operator << (std::cout, A); // std::cout << A (uses the overloaded operator)
  std::cout << std::endl; // NOT EQUAL TO operator<<(std::cout, std::endl) Don't know why.
  //
  // std::vector<unsigned int> irow, jcol;
  // std::vector<double>       v;
  //
  // A.csr(v, jcol, irow);
  //
  // std::cout << "CSR vectors:" << std::endl;
  // for (auto ii : irow)
    //   std::cout << ii << " ";
  // std::cout << std::endl;
  //
  // for (auto ii : jcol)
  //   std::cout << ii << " ";
  // std::cout << std::endl;
  //
  // for (auto ii : v)
  //   std::cout << ii << " ";
  // std::cout << std::endl << std::endl;
  //
  // std::cout << "Matrix entries from CSR:" << std::endl;
  // for (unsigned int ii = 0; ii < n; ++ii)
  //   for (unsigned int jj = irow[ii]; jj < irow[ii + 1]; ++jj)
  //     std::cout << "A[" << ii << "][" << jcol[jj] << "] = " << v[jj]
  //               << std::endl;
  // std::cout << std::endl;
  //
  // std::cout << "Matrix-vector product:" << std::endl;
  // const std::vector<double> x(n, 1.0);
  // const std::vector<double> y = A * x;
  // for (const auto ii : y)
  //   std::cout << ii << " ";
  // std::cout << std::endl << std::endl;
}
