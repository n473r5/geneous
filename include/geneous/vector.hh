#ifndef VECTOR_HH
#define VECTOR_HH

#include "matrix.hh"

namespace Geneous {

template<uint n>
class Vector : public Matrix<n, 1> {
	public:
		double operator()(uint) const;
		double& operator()(uint);
};

} // namespace Geneous

#include "vector-impl.hh"

#endif
