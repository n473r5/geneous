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
		bool is_dynamic_size = !is_fixed_size;
		uint row_count = m, column_count = n;
		std::vector<double> data;
	public:
		// fixed size constructor
		Matrix(std::initializer_list<double>);

		// dynamic size constructors
		Matrix(uint, uint, std::initializer_list<double>);
		Matrix(uint, uint);

		// empty constructor
		Matrix();

		double get_row_count() const { return row_count; }
		double get_column_count() const { return column_count; }

		void set_to_zero();

		// copy constructor
		template<uint m_, uint n_> Matrix(const Matrix<m_, n_>&);

		std::pair<uint, uint> get_size() const;
		void set_size(std::pair<uint, uint>);
		void set_size(uint, uint);

		operator std::string() const;

		// getter
		double operator()(uint, uint) const;
		// setter
		double& operator()(uint, uint);
		
		void operator=(std::initializer_list<double>);
		template<uint m_, uint n_> bool operator==(const Matrix<m_, n_>&) const;
		template<uint m_, uint n_> bool operator!=(const Matrix<m_, n_>&) const;

		// unary minus
		Matrix operator-() const;
		template<uint m_, uint n_> void operator+=(const Matrix<m_, n_>&);
		template<uint m_, uint n_> void operator-=(const Matrix<m_, n_>&);
		void operator*=(double);

		// void row_reduce();
		// Matrix get_row_reduced() const;
};

} // namespace Geneous

#include "matrix-impl.hh"

#endif