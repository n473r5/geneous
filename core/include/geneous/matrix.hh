#ifndef MATRIX_HH
#define MATRIX_HH

#include <iostream> // debug
#include <vector>
#include <initializer_list>
#include <string>
#include <ostream>
#include <utility>

#define MATRIX_TEMPLATE template<uint m, uint n, typename etype>
#define MATRIX_OTHER_TEMPLATE template<uint m_, uint n_, typename etype_>
#define MATRIX_DOUBLE_TEMPLATE template<uint m, uint n, typename etype, uint m_, uint n_, typename etype_>

typedef unsigned int uint;

namespace Geneous {

const uint Dynamic = 0;

template<uint m, uint n, typename etype = double>
class Matrix {
	protected:
		const bool is_fixed_size = m != Dynamic && n != Dynamic;
		const bool is_dynamic_size = !is_fixed_size;
		uint row_count = m, column_count = n;
		std::vector<etype> data;
		
		typedef typename std::vector<etype>::iterator MatrixDataIterator;
	public:
		/// Filled matrix constructor
		Matrix(std::initializer_list<etype>);
		/// Dynamic size filled matrix constructor
		Matrix(uint, uint, std::initializer_list<etype>);
		/// Dynamic size empty constructor
		Matrix(uint, uint);
		/// Empty constructor
		Matrix();
		/// Copy constructor
		MATRIX_OTHER_TEMPLATE 
		Matrix(const Matrix<m_, n_, etype_>&);
		/// Cast (for fixed size <-> dynamic size)
		MATRIX_OTHER_TEMPLATE 
		operator Matrix<m_, n_, etype_>() const;

		std::vector<etype> get_data() const { return data; };

		/// Getter
		etype operator()(uint, uint) const;
		/// Setter
		etype& operator()(uint, uint);

		uint get_row_count() const { return this->row_count; };
		uint get_column_count() const { return this->column_count; };
		std::pair<uint, uint> get_size() const { return { this->row_count, this->column_count }; };
		void set_size(uint, uint);
		void set_size(std::pair<uint, uint>);

		Matrix<1, n, etype> get_row(uint row) const;
		Matrix<m, 1, etype> get_column(uint column) const;

		/// Add row matrix at index
		template<uint n_> 
		void add_row(Matrix<1, n_, etype>, uint);
		/// Append row matrix after the last row
		template<uint n_> 
		void add_row(Matrix<1, n_, etype>);
		/// Add a list of entries to a new row at index
		void add_row(std::initializer_list<etype>, uint);
		/// Add a list of entries to a new row after the last row
		void add_row(std::initializer_list<etype>);
		/// Add a column matrix at index
		template<uint m_>
		void add_column(Matrix<m_, 1, etype>, uint);
		/// Add a column matrix after the last column
		template<uint m_>
		void add_column(Matrix<m_, 1, etype>);
		/// Add a list of entries to a new column at index
		void add_column(std::initializer_list<etype>, uint);
		/// Add a list of entries to a new column after the last column
		void add_column(std::initializer_list<etype>);
		
		/// Remove row at index
		void remove_row(uint);
		/// Remove column at index
		void remove_column(uint);

		/// To string operator
		operator std::string() const;

		///
		MATRIX_OTHER_TEMPLATE
		bool operator==(const Matrix<m_, n_, etype_>&) const;
		///
		MATRIX_OTHER_TEMPLATE
		bool operator!=(const Matrix<m_, n_, etype_>&) const;
		///
		void operator=(std::initializer_list<etype>);
		
		///
		Matrix operator-() const;

		///
		template<typename scalartype> 
		void operator*=(scalartype scalar);
		///
		MATRIX_OTHER_TEMPLATE
		void operator+=(const Matrix<m_, n_, etype_>&);
		///
		MATRIX_OTHER_TEMPLATE
		void operator-=(const Matrix<m_, n_, etype_>&);

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
typedef Matrix<Dynamic, Dynamic> DMatrix;

} // namespace Geneous

#include "impl/matrix-impl.hh"

#endif