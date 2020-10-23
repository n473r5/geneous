namespace Geneous {

/**
 *
 */
MATRIX_TEMPLATE
Matrix<m, n, etype>::Matrix(std::initializer_list<etype> data) {
	if(is_fixed_size && data.size() != m * n) {
		throw std::invalid_argument("Data size does not match matrix size");
	}
	for(etype value : data) {
		this->data.push_back(value);
	}
}

/**
 * 
 */
MATRIX_TEMPLATE
Matrix<m, n, etype>::Matrix(uint m_, uint n_, std::initializer_list<etype> data) {
	if(m_ == 0 || n_ == 0) {
		throw std::invalid_argument("Size arguments must not be zero");
	}
	if(is_fixed_size) {
		if(m_ != m || n_ != n) {
			throw std::invalid_argument("Size arguments do not match template parameters");
		}
	} else {
		if((m_ != m && m != Dynamic) || (n_ != n && n != Dynamic)) {
			throw std::invalid_argument("Size arguments do not match template parameters");
		} else {
			row_count = m_;
			column_count = n_;
		}
	}
	for(etype value : data) {
		this->data.push_back(value);
	}
}

/**
 * 
 */
MATRIX_TEMPLATE
Matrix<m, n, etype>::Matrix(uint m_, uint n_) {
	if(is_fixed_size && (m_ != m || n_ != n)) {
		throw std::invalid_argument("Size arguments do not match template parameters");
	}
	for(int i = 0; i < m_ * n_; i++) {
		data.push_back(0);
	}
}

/**
 * 
 */
MATRIX_TEMPLATE
Matrix<m, n, etype>::Matrix() {
	for(int i = 0; i < m * n; i++) {
		data.push_back(0);
	}
}

/**
 * 
 */
MATRIX_TEMPLATE
MATRIX_OTHER_TEMPLATE
Matrix<m, n, etype>::Matrix(const Matrix<m_, n_, etype_>& other) {
	uint other_row_count = other.get_row_count();
	uint other_column_count = other.get_column_count();
	if(row_count != other_row_count || column_count != other_column_count) {
		if(row_count != 0 && column_count != 0) {
			throw std::invalid_argument("Cannot copy matrix of different size");
		}
	}
	row_count = other.get_row_count();
	column_count = other.get_column_count();
	for(etype_ value : other.get_data()) {
		data.push_back((etype) value);
	}
}

/**
 * 
 */
MATRIX_TEMPLATE
etype Matrix<m, n, etype>::operator()(uint i, uint j) const {
	if((1 > i || i > row_count) || (1 > j || j > column_count)) {
		throw std::invalid_argument("Attempt to index matrix outside of bounds");
	}
	return this->data[(i - 1) * column_count + (j - 1)];
}

/**
 * 
 */
MATRIX_TEMPLATE
etype& Matrix<m, n, etype>::operator()(uint i, uint j) {
	if((1 > i || i > row_count) || (1 > j || j > column_count)) {
		throw std::invalid_argument("Attempt to index matrix outside of bounds");
	}
	return this->data[(i - 1) * column_count + (j - 1)];
}

/**
 * 
 */
MATRIX_TEMPLATE
void Matrix<m, n, etype>::set_size(uint m_, uint n_) {
	if(is_fixed_size) {
		if(m != m_ || n != n_) {
			throw std::invalid_argument("Tried to resize fixed size matrix");
		}
	} else {
		for(int i = row_count * column_count; i < m_ * n_; i++) {
			data.push_back(0);
		}
		row_count = m_;
		column_count = n_;
	}
}

/**
 * 
 */
MATRIX_TEMPLATE
void Matrix<m, n, etype>::set_size(std::pair<uint, uint> size) {
	set_size(size.first, size.second);
}

/**
 * 
 */
MATRIX_TEMPLATE
Matrix<1, n, etype> Matrix<m, n, etype>::get_row(uint i) const {
	if(1 > i || i > row_count) {
		throw std::invalid_argument("Attempted to get row outside of range");
	}
	Matrix<1, n, etype> row;
	row.set_size(1, column_count);
	for(int j = 1; j <= column_count; j++) {
		row(1, j) = (*this)(i, j);
	}
	return row;
}

/**
 * 
 */
MATRIX_TEMPLATE
Matrix<m, 1, etype> Matrix<m, n, etype>::get_column(uint j) const {
	if(1 > j || j > column_count) {
		throw std::invalid_argument("Attempted to get column outside of range");
	}
	Matrix<m, 1, etype> column;
	column.set_size(row_count, 1);
	for(int i = 1; i <= row_count; i++) {
		column(i, 1) = (*this)(i, j);
	}
	return column;
}

/**
 * 
 */
MATRIX_TEMPLATE
template<uint n_>
void Matrix<m, n, etype>::add_row(Matrix<1, n_, etype> row, uint i) {
	if(is_fixed_size || m != Dynamic) {
		throw std::invalid_argument("Cannot add new row to fixed size matrix");
	}
	if(1 > i || i > row_count + 1) {
		throw std::invalid_argument("Attempted to add new row outside of range");
	}
	if(row.get_column_count() != column_count) {
		throw std::invalid_argument("Attempted to add row with incorrect size");
	}
	std::vector<etype> row_data = row.get_data();
	data.insert(data.begin() + (i - 1) * column_count, row_data.begin(), row_data.end());
	row_count++;
}

/**
 * 
 */
MATRIX_TEMPLATE
template<uint n_>
void Matrix<m, n, etype>::add_row(Matrix<1, n_, etype> row) {
	add_row(row, row_count + 1);
}

/**
 * 
 */
MATRIX_TEMPLATE
void Matrix<m, n, etype>::add_row(std::initializer_list<etype> row_data, uint i) {
	if(row_data.size() != column_count) {
		throw std::invalid_argument("Attempted to add row with incorrect size");
	}
	Matrix<1, n, etype> row;
	row.set_size(1, column_count);
	int j = 1;
	for(etype value : row_data) {
		row(1, j) = value;
		j++;
	}
	add_row(row, i);
}

/**
 * 
 */
MATRIX_TEMPLATE
void Matrix<m, n, etype>::add_row(std::initializer_list<etype> row_data) {
	add_row(row_data, row_count + 1);
}

/**
 * 
 */
MATRIX_TEMPLATE
template<uint m_>
void Matrix<m, n, etype>::add_column(Matrix<m_, 1, etype> column, uint j) {
	if(is_fixed_size || n != Dynamic) {
		throw std::invalid_argument("Cannot add new column to fixed size matrix");
	}
	if(1 > j || j > column_count + 1) {
		throw std::invalid_argument("Attempted to add new column outside of range");
	}
	if(column.get_row_count() != row_count) {
		throw std::invalid_argument("Attempted to add column with incorrect size");
	}
	int i = 0;
	for(etype value : column.get_data()) {
		data.insert(data.begin() + (j - 1) + (i * (column_count + 1)), value);
		i++;
	}
	column_count++;
}

/**
 * 
 */
MATRIX_TEMPLATE
template<uint m_>
void Matrix<m, n, etype>::add_column(Matrix<m_, 1, etype> column) {
	add_column(column, column_count + 1);
}

/**
 * 
 */
MATRIX_TEMPLATE
void Matrix<m, n, etype>::add_column(std::initializer_list<etype> column_data, uint j) {
	if(column_data.size() != row_count) {
		throw std::invalid_argument("Attempted to add column with incorrect size");
	}
	Matrix<m, 1, etype> column;
	column.set_size(row_count, 1);
	int i = 1;
	for(etype value : column_data) {
		column(i, 1) = value;
		i++;
	}
	add_column(column, j);
}

/**
 * 
 */
MATRIX_TEMPLATE
void Matrix<m, n, etype>::add_column(std::initializer_list<etype> column_data) {
	add_column(column_data, column_count + 1);
}

/**
 * 
 */
MATRIX_TEMPLATE
void Matrix<m, n, etype>::remove_row(uint i) {
	if(is_fixed_size || m != Dynamic) {
		throw std::invalid_argument("Cannot remove row from fixed size matrix");
	}
	if(1 > i || i > column_count) {
		return;
	}
	MatrixDataIterator iterator = data.begin() + (i - 1) * column_count;
	data.erase(iterator, iterator + column_count);
	row_count--;
}

/**
 * 
 */
MATRIX_TEMPLATE
void Matrix<m, n, etype>::remove_column(uint j) {
	if(is_fixed_size || n != Dynamic) {
		throw std::invalid_argument("Cannot remove column from fixed size matrix");
	}
	if(1 > j || j > column_count) {
		return;
	}
	for(int i = 1; i <= row_count; i++) {
		data.erase(data.begin() + (i - 1) * (column_count - 1) + (j - 1));
	}
	column_count--;
}

/**
 * 
 */
MATRIX_TEMPLATE
Matrix<m, n, etype>::operator std::string() const {
	std::string string = "[";
	for(int i = 1; i <= row_count; i++) {
		string += "[";
		for(int j = 1; j <= column_count; j++) {
			string += std::to_string((*this)(i, j)) + (j < column_count ? " " : "");
		}
		string += "]";
	}
	return string + "]";
}

/**
 *
 */
MATRIX_TEMPLATE
MATRIX_OTHER_TEMPLATE
bool Matrix<m, n, etype>::operator==(const Matrix<m_, n_, etype_>& other) const {
	if(row_count != other.get_row_count() || column_count != other.get_column_count()) {
		return false;
	}
	for(int i = 1; i <= row_count; i++) {
		for(int j = 1; j <= column_count; j++) {
			if((*this)(i, j) != other(i, j)) {
				return false;
			}
		}
	}
	return true;
}

MATRIX_TEMPLATE
MATRIX_OTHER_TEMPLATE
bool Matrix<m, n, etype>::operator!=(const Matrix<m_, n_, etype_>& other) const {
	return (!this == other);
}

/**
 * 
 */
MATRIX_TEMPLATE
void Matrix<m, n, etype>::operator=(std::initializer_list<etype> data) {
	if(data.size() != row_count * column_count) {
		throw std::invalid_argument("Invalid data size");
	}
	this->data = data;
}

/**
 * 
 */
MATRIX_TEMPLATE
Matrix<m, n, etype> Matrix<m, n, etype>::operator-() const {
	Matrix<m, n, etype> unm(*this);
	unm *= -1;
	return unm;
}

/**
 * 
 */
MATRIX_TEMPLATE
template<typename scalartype>
void Matrix<m, n, etype>::operator*=(scalartype scalar) {
	for(etype& value : data) {
		value *= scalar;
	}
}

/**
 * 
 */
MATRIX_TEMPLATE
MATRIX_OTHER_TEMPLATE
void Matrix<m, n, etype>::operator+=(const Matrix<m_, n_, etype_>& other) {
	if(row_count != other.get_row_count() || column_count != other.get_column_count()) {
		throw std::invalid_argument("Cannot add matrices of different sizes");
	}
	std::vector<etype_> other_data = other.get_data();
	for(int i = 0; i < other_data.size(); i++) {
		this->data[i] += other_data[i];
	}
}

/**
 * 
 */
MATRIX_TEMPLATE
MATRIX_OTHER_TEMPLATE
void Matrix<m, n, etype>::operator-=(const Matrix<m_, n_, etype_>& other) {
	this += -other;
}

} // namespace Geneous

/**
 * 
 */
MATRIX_TEMPLATE
std::ostream& operator<<(std::ostream& stream, const Geneous::Matrix<m, n, etype>& matrix) {
	return stream << (std::string) matrix << std::endl;
}

/**
 * 
 */
MATRIX_DOUBLE_TEMPLATE
Geneous::Matrix<m, n, etype> operator+(const Geneous::Matrix<m, n, etype>& left, const Geneous::Matrix<m_, n_, etype_>& right) {
	Geneous::Matrix<m, n, etype> sum(left);
	sum += right;
	return sum;
}

/**
 * 
 */
MATRIX_DOUBLE_TEMPLATE
Geneous::Matrix<m, n, etype> operator-(const Geneous::Matrix<m, n, etype>& left, const Geneous::Matrix<m_, n_, etype_>& right) {
	return left + -right;
}

/**
 * 
 */
template<uint m, uint n, typename etype, typename scalartype>
Geneous::Matrix<m, n, etype> operator*(const Geneous::Matrix<m, n, etype>& left, scalartype scalar) {
	Geneous::Matrix<m, n, etype> product(left);
	product *= scalar;
	return product;
}

/**
 * 
 */
MATRIX_DOUBLE_TEMPLATE
Geneous::Matrix<m, n_, etype> operator*(const Geneous::Matrix<m, n, etype>& left, const Geneous::Matrix<m_, n_, etype_>& right) {
	if(left.get_column_count() != right.get_row_count()) {
		throw std::invalid_argument("Cannot multiply matrices of incorrect size");
	}
	Geneous::Matrix<m, n_, etype> product;
	product.set_size(left.get_row_count(), right.get_column_count());
	for(int i = 1; i <= product.get_row_count(); i++) {
		for(int j = 1; j <= product.get_column_count(); j++) {
			for(int k = 1; k <= left.get_column_count(); k++) {
				product(i, j) += left(i, k) * right(k, j);
			}
		}
	}
	return product;
}