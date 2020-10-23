# Overview
Geneous provides classes for matrices and vectors.

## Matrices
### Instantiation
Geneous distinguishes between two kinds of matrices: ones that are fixed-size (i.e. size known at compile time), and ones that are dynamic-size (i.e. size unknown at compile time). Fixed size matrices may not change size, and any operations that attempt to modify the size of the matrix throw an exception except in the case where the operation would have been a no-op (setting a Matrix3's size to 3x3). Dynamic matrices, however, do not have such a limitation, and certain operations are available that resize the matrix with new values, add and remove rows and columns, etc.

Matrix instantiation can be done as follows:
```
using namespace Geneous; // or use Geneous::...

// valid fixed-size matrix, instantiate with values
Matrix<2, 2> a {1, 2, 3, 4}; // [[1 2][3 4]]

// valid dynamic-size matrix, instantiate with values and size
Matrix<0, 0> b(2, 2, {1, 2, 3, 4}); // [[1 2][3 4]]

```

Dynamic matrices can also be fixed in either dimension:
```
// Fixed number of rows, but dynamic number of columns
Matrix<2, 0> c(2, 1, {1, 2}); // [[1][2]]
```

### Dynamic-size operations