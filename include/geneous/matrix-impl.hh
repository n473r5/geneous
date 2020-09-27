namespace Geneous {

template<uint m, uint n>
Matrix<m, n>::Matrix(std::initializer_list<double> data) {
	assert(this->is_fixed_size);
	assert(m * n == data.size());
	for(double value : data) {
		this->data.push_back(value);
	}
}

template<uint m, uint n>
Matrix<m, n>::Matrix(uint m_, uint n_, std::initializer_list<double> data) {
	assert(this->is_dynamic_size);
	assert(m_ * n_ == data.size());
	this->row_count = m_;
	this->column_count = n_;
	for(double value : data) {
		this->data.push_back(value);
	}
}

template<uint m, uint n>
Matrix<m, n>::Matrix(uint m_, uint n_) {
	assert(this->is_dynamic_size);
	assert(m_ != 0 && n_ != 0);
	for(int i = 0; i < m_ * n_; i++) {
		this->data.push_back(0);
	}
}

template<uint m, uint n>
Matrix<m, n>::Matrix() {
	if(this->is_fixed_size) {
		for(int i = 0; i < m * n; i++) {
			this->data.push_back(0);
		}
	}
}

template<uint m, uint n>
void Matrix<m, n>::set_to_zero() {
	for(double& value : this->data) {
		value = 0;
	}
}

template<uint m, uint n>
Matrix<n, m> Matrix<m, n>::get_transpose() const {
	Matrix<n, m> transpose;
	if(m == 0 || n == 0) {
		transpose.set_size(this->column_count, this->row_count);
	}
	for(uint i = 1; i <= this->row_count; i++) {
		for(uint j = 1; j <= this->column_count; j++) {
			transpose(j, i) = (*this)(i, j);
		}
	}
	return transpose;
}

template<uint m, uint n>
template<uint m_, uint n_>
Matrix<m, n>::Matrix(const Matrix<m_, n_>& other) {
	std::pair<uint, uint> other_size = other.get_size();
	assert(m == 0 || m == other_size.first);
	assert(n == 0 || n == other_size.second);
	this->row_count = other_size.first;
	this->column_count = other_size.second;
	for(int i = 1; i <= other_size.first; i++) {
		for(int j = 1; j <= other_size.first; j++) {
			this->data.push_back(other(i, j));
		}
	}
}

template<uint m, uint n>
std::pair<uint, uint> Matrix<m, n>::get_size() const {
	return std::pair<uint, uint> { row_count, column_count };
}

template<uint m, uint n>
void Matrix<m, n>::set_size(std::pair<uint, uint> size) {
	assert(this->is_dynamic_size);
	assert(this->data.size() == 0);
	this->row_count = size.first;
	this->column_count = size.second;
	for(int i = 0; i < size.first * size.second; i++) {
		this->data.push_back(0);
	}
}

template<uint m, uint n>
void Matrix<m, n>::set_size(uint m_, uint n_) {
	this->set_size(std::pair<uint, uint> { m_, n_ });
}

template<uint m, uint n>
Matrix<m, n>::operator std::string() const {
	assert(this->row_count != 0 && this->column_count != 0);
	std::string s = "";
	for(int i = 0; i < this->row_count; i++) {
		s += "[ ";
		for(int j = 0; j < this->column_count; ++j) {
			s += std::to_string(this->data[i * this->column_count + j]) + " ";
		
		}
		s += "]";
	}
	return "[" + s + "]";
}

template<uint m, uint n>
double Matrix<m, n>::operator()(uint i, uint j) const {
	assert(i <= this->row_count);
	assert(j <= this->column_count);
	return this->data[(i - 1) * this->column_count + (j - 1)];
}

template<uint m, uint n>
double& Matrix<m, n>::operator()(uint i, uint j) {
	assert(1 <= i && i <= this->row_count);
	assert(1 <= j && j <= this->column_count);
	return this->data[(i - 1) * this->column_count + (j - 1)];
}

template<uint m, uint n>
void Matrix<m, n>::operator=(std::initializer_list<double> data) {
	assert(this->row_count * this->column_count == data.size());
	this->data.clear();
	for(double value : data) {
		this->data.push_back(value);
	}
}

template<uint m, uint n>
template<uint m_, uint n_>
bool Matrix<m, n>::operator==(const Matrix<m_, n_>& other) const {
	if(this->get_size() != other.get_size()) {
		return false;
	}
	for(int i = 1; i < this->row_count; i++) {
		for(int j = 1; j < this->column_count; j++) {
			if((*this)(i, j) != other(i, j)) {
				return false;
			}
		}
	}
	return true;
}

template<uint m, uint n>
template<uint m_, uint n_>
bool Matrix<m, n>::operator!=(const Matrix<m_, n_>& other) const {
	return !((*this) == other);
}

template<uint m, uint n>
Matrix<m, n> Matrix<m, n>::operator-() const {
	Matrix<m, n> unm(*this);
	unm *= -1;
	return unm;
}

template<uint m, uint n>
template<uint m_, uint n_>
void Matrix<m, n>::operator+=(const Matrix<m_, n_>& other) {
	assert(this->get_size() == other.get_size());
	for(int i = 1; i <= this->row_count; i++) {
		for(int j = 1; j <= this->column_count; j++) {
			(*this)(i, j) += other(i, j);
		}
	}
}

template<uint m, uint n>
template<uint m_, uint n_>
void Matrix<m, n>::operator-=(const Matrix<m_, n_>& other) {
	(*this) += -other;
}

template<uint m, uint n>
void Matrix<m, n>::operator*=(double scalar) {
	assert(this->row_count != 0 && this->column_count != 0);
	for(int i = 0; i < this->data.size(); i++) {
		this->data[i] *= scalar;
	}
}

} // namespace Geneous

template<uint m, uint n> 
std::ostream& operator<<(std::ostream& stream, const Geneous::Matrix<m,n>& matrix) { 
	return stream << (std::string) matrix << std::endl; 
}

template<uint m, uint n, uint m_, uint n_>
Geneous::Matrix<m, n> operator+(const Geneous::Matrix<m, n>& left, const Geneous::Matrix<m_, n_>& right) {
	Geneous::Matrix<m, n> sum(left);
	sum += right;
	return sum;
}

template<uint m, uint n, uint m_, uint n_>
Geneous::Matrix<m, n> operator-(const Geneous::Matrix<m, n>& left, const Geneous::Matrix<m_, n_>& right) {
	Geneous::Matrix<m, n> difference(left);
	difference -= right;
	return difference;
}

template<uint m, uint n>
Geneous::Matrix<m, n> operator*(const Geneous::Matrix<m, n>& matrix, double scalar) {
	Geneous::Matrix<m, n> scaled(matrix);
	scaled *= scalar;
	return scaled;
}

template<uint m, uint n, uint m_, uint n_>
Geneous::Matrix<m, n_> operator*(const Geneous::Matrix<m, n>& left, const Geneous::Matrix<m_, n_>& right) {
	assert(left.get_column_count() == right.get_row_count());
	Geneous::Matrix<m, n_> product;
	if(m == 0 || n == 0) {
		product.set_size(left.get_row_count(), right.get_column_count());
	}
	for(int i = 1; i <= left.get_row_count(); i++) {
		for(int j = 1; j <= right.get_column_count(); j++) {
			for(int k = 1; k <= left.get_column_count(); k++) {
				product(i, j) += left(i, k) * right(k, j);
			}
		}
	}
	return product; 
}
