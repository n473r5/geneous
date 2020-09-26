#ifndef VECTOR_HH
#define VECTOR_HH

#include "matrix.hh"

namespace Geneous {

template<uint n>
class Vector : public Matrix<n, 1> {
	public:
		Vector(std::initializer_list<double>);

		double operator()(uint) const;
		double& operator()(uint);
};

typedef Vector<2> Vector2;
typedef Vector<3> Vector3;
typedef Vector<4> Vector4;
typedef Vector<0> DVector;

} // namespace Geneous

#include "vector-impl.hh"

#endif
