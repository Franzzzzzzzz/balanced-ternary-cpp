This header-only C++ library provides support for variable that can take three distinct value, called balanced ternaries, or "tbits" in the following document. Each ternary can hold the value 0, +1, or -1. Support for array and vectors of tbits value are also provided. 

Bug report and feature requests are welcome. 

# Install
Simply `#include "headerfile.h"` the relevent file that covers your use case.

# Libraries and documentation
## tbits.h
This provide support for a single tbits value. Documentation is [here]{doc/tbits.md}.

## tbits_vector.h
This provide support for an arbitrary, dynamically allocated, array of tbits value. Documentation is [here]{doc/tbits_vector.md}.

## tbits_array.h [not implemented yet]
Similar to `tbits_vector`, however the data is stored internally on the stack rather than on the heap, so the number of ternaries that can be stored cannot change. This should be prefered over `tbits_vector` in most cases when the number of ternaries is small, say ≲100. Documentation is [here]{doc/tbits_vector.md}







