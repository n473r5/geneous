#ifndef VECTOR_HH
#define VECTOR_HH

#include "matrix.hh"

namespace Geneous {

template<uint n, typename etype = double>
class Vector : public Matrix<n, 1, etype> {

};

typedef Vector<2> Vector2;
typedef Vector<3> Vector3;
typedef Vector<4> Vector4;
typedef Vector<Dynamic> DVector;

} // namespace Geneous

#include "impl/vector-impl.hh"

#endif