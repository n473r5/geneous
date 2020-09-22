namespace Geneous {

template<uint n>
double Vector<n>::operator()(uint i) const {
	return (*this)(i, 1);
}

template<uint n>
double& Vector<n>::operator()(uint i) {
	return (*this)(i, 1);
}

} // namespace Geneous
