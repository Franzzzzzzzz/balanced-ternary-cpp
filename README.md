This header-only C++ library provides support for variable that can take three distinct value, called "ternary" in the following document. Each ternary can hold the value 0, +1, or -1. Support for array and vectors of ternary value are also provided. 

# Install
Simply `#include "headerfile.h"` the relevent file that covers your use case.

# Libraries and documentation
## ternary.h
This provide support for a single ternary value. Documentation is [here]{doc/ternary.md}.

## ternary_vector.h
This provide support for an arbitrary, dynamically allocated, array of ternary value. Documentation is [here]{doc/ternary_vector.md}.

## ternary_array.h
Similar to `ternary_vector`, however the data is stored internally on the stack rather than on the heap, so the number of ternaries that can be stored cannot change. This should be prefered over `ternary_vector` in most cases when the number of ternaries is small, say ≲100. Documentation is [here]{doc/ternary_vector.md}







