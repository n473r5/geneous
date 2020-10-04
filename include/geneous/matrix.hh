#ifndef MATRIX_HH
#define MATRIX_HH

#include <string>
#include <ostream>
#include <vector>
#include <initializer_list>
#include <utility>
#include <cassert>

typedef unsigned int uint;

namespace Geneous {

template<uint m, uint n>
class Matrix {
	protected:
		const bool is_fixed_size = n != 0 && m != 0;
		const bool is_dynamic_size = !is_fixed_size;
		uint row_count = m, column_count = n;
		std::vector<double> data;
	public:
		Matrix(std::initializer_list<double>);
		Matrix(uint, uint, std::initializer_list<double>);
		Matrix(uint, uint);
		template<uint m_, uint n_> Matrix(const Matrix<m_, n_>&);
		Matrix();

		// from string constructor

		double get_row_count() const { return this->row_count; }
		double get_column_count() const { return this->column_count; }
		
		std::pair<uint, uint> get_size() const;
		void set_size(std::pair<uint, uint>);
		void set_size(uint, uint);

		Matrix<1, n> get_row(int) const;
		Matrix<m, 1> get_column(int) const;

		// add_row
		// add_column

		// get_submatrix
		// get_identity
	
		void set_to_zero();
		Matrix<n, m> get_transpose() const;

		operator std::string() const;
		template<uint m_, uint n_> operator Matrix<m_, n_>() const;

		double operator()(uint, uint) const;
		double& operator()(uint, uint);
		
		void operator=(std::initializer_list<double>);
		template<uint m_, uint n_> bool operator==(const Matrix<m_, n_>&) const;
		template<uint m_, uint n_> bool operator!=(const Matrix<m_, n_>&) const;

		Matrix operator-() const;
		template<uint m_, uint n_> void operator+=(const Matrix<m_, n_>&);
		template<uint m_, uint n_> void operator-=(const Matrix<m_, n_>&);
		void operator*=(double);

		// get_trace
		// get_rank
		// get_nullity
		// get_determinant

		// get_inverse

		// row_reduce
		// get_row_reduced

		// get_row_space
		// get_column_space
		// get_null_space

		// get_eigenvalues
		// get_eigenvectors
};

typedef Matrix<2, 2> Matrix2;
typedef Matrix<3, 3> Matrix3;
typedef Matrix<4, 4> Matrix4;
typedef Matrix<0, 0> DMatrix;

} // namespace Geneous

#include "matrix-impl.hh"

#endif
