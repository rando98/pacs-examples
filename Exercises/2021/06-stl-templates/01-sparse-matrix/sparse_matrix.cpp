#include "sparse_matrix.hpp"

sparse_matrix::sparse_matrix()
  :nnz(0), m(0)
{}

void
sparse_matrix::update_properties()
{
  nnz=0;
  m=0;;

  // vector::size() is the number of rows ()
  for(size_t r=0; r<size(); ++r)
  {
    if(!(*this)[r].empty())
    {
      nnz+=(*this)[r].size(); // map::size()

      // m = max(m, highest-index column in this row)
      size_t tmp=(*this)[r].crbegin()->first + 1;
      m=std::max(m, tmp);
    }
  }
}

void
sparse_matrix::aij( std::vector<double>&        a,
                    std::vector<unsigned int>&  i,
                    std::vector<unsigned int>&  j)
{
  update_properties();

  a.clear();
  i.clear();
  j.clear();

  a.reserve(nnz);
  i.reserve(nnz);
  j.reserve(nnz);

  for(size_t r=0; r<size(); ++r)
  {
    if(!(*this)[r].empty())
    {
      for(auto c=(*this)[r].cbegin(); c!=(*this)[r].cend(); ++c)
      {
        a.emplace_back(c->second);
        i.emplace_back(r);
        j.emplace_back(c->first);
      }
    }
  }
}

void
sparse_matrix::csr( std::vector<double>&        a,
                    std::vector<unsigned int>&  col_idx,
                    std::vector<unsigned int>&  row_ptr)

{
  update_properties();

  a.clear();
  col_idx.clear();
  row_ptr.clear();

  a.reserve(nnz);
  col_idx.reserve(nnz);
  row_ptr.reserve(size()+1);

  row_ptr.emplace_back(0);

  for(size_t r=0; r<size(); ++r)
  {
    if(!(*this)[r].empty())
    {
      row_ptr.emplace_back(row_ptr.back() + (*this)[r].size());

      for(auto c=(*this)[r].cbegin(); c!=(*this)[r].cend(); ++c)
      {
        a.emplace_back(c->second);
        col_idx.emplace_back(c->first);
      }
    }
  }
}

std::ostream&
operator<<(std::ostream& stream, sparse_matrix& M)
{
  stream << "No. nonzero elements: " << M.nnz << std::endl; // Here I Am using the classical operator<< for std::cout
  stream << "No. columns: " << M.m;

  for (std::size_t r=0; r < M.size(); ++r)
  {
    for(const auto& [c, val] : M[r])
    {
      stream << r << ", " << c << ", " << val << std::endl;
    }
  }
  return stream;
}

std::vector<double>
operator*(const sparse_matrix& M, const std::vector<double>& x)
{
  std::vector<doube> y(M.size(), 0.0);

  for (size_t r=0; r<M.size(); ++r)
  {
    for(const auto& [c, val]: M[r])
    {
      y[r] += val*x[c];
    }
  }
  return y;
}
