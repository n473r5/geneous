# Geneous
![ubuntu](https://github.com/n473r5/geneous/workflows/ubuntu/badge.svg)

A linear algebra and computational mathematics library by [Nathan Tresham](http://ntresham.com) and [Kai Nakamura](https://github.com/KaiNakamura).

## Building
To build the main library, run the following commands from the root directory (`geneous/`):
```
mkdir build
cd build
cmake ..
make
```
To build tests, append `-DBUILD_TESTING=ON` to the `cmake` command. An executable that runs all tests will be placed in a folder called `test` in your build directory.

Note: if building on Windows with MinGW Makefiles, append `-G "MinGW Makefiles"` to the `cmake` command.

## Documentation
Geneous uses [Doxygen](https://doxygen.nl) for documentation. To build the documentation files, run `doxygen Doxyfile` in the root directory of this project. The documentation files can be viewed in `build/html`.