namespace Geneous {

template<uint n>
Vector<n>::Vector(std::initializer_list<double> data) : Matrix<n, 1>(data) {

}

template<uint n>
Vector<n>::Vector(uint n_, std::initializer_list<double> data) : Matrix<n, 1>(n_, 1, data) {

}

template<uint n>
Vector<n>::Vector(uint n_) : Matrix<n, 1>(n_, 1) {

}

template<uint n>
Vector<n>::Vector() : Matrix<n, 1>() {

}

template<uint n>
double Vector<n>::operator()(uint i) const {
	return ((Matrix<n, 1>) *this)(i, 1);
}

template<uint n>
double& Vector<n>::operator()(uint i) {
	return ((Matrix<n, 1>) *this)(i, 1);
}

} // namespace Geneous
