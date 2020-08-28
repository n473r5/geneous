#ifndef MATRIX_HH
#define MATRIX_HH

#include <vector>
#include <initializer_list>
#include <utility>

typedef unsigned int uint;

namespace Geneous {

template<uint n, uint m>
class Matrix {
	protected:
		bool is_fixed_size = n != 0 && m != 0;
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

		double operator()(uint, uint) const;
		double& operator()(uint, uint);
		void operator=(std::initializer_list<double>);
		template<uint m_, uint n_> bool operator==(const Matrix<m_, n_>&) const;
		template<uint m_, uint n_> bool operator!=(const Matrix<m_, n_>&) const;

		Matrix operator-() const;
		template<uint m_, uint n_> void operator+=(const Matrix<m_, n_>&);
		template<uint m_, uint n_> void operator-=(const Matrix<m_, n_>&);
		void operator*=(double);
};

} // namespace Geneous

#include "matrix-impl.hh"

#endif