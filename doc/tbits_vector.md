Tbits vector contains multiple tbits, each with a single value among {-1; 0; 1}. 

## Construction
- Can be contructed empty, with an integer indicating the initial number of tbits to hold, or from an array or vector of values.

## Getting the values
- `print()` prints the values on screen, where the values `{0, 1, -1, nan}` are mapped to the characters`{0,+,-,N}`.
- `to_vector<type>()` returns a vector of value of the type you specify. 
- `to_vector(v)` overwrite the vector `v` with the values. 
- Individual tbits can be indexed `[index]`. All the operations that are mentionned in the [tbits](tbits.md) doc are supported. 

## Counting
The functions `count_zero`, `count_positive`, and `count_negative` return the number of zeros, +1, and -1 in the array, respectively. 

## Size
- Size can be obtained with the function `size()`.
- `tbits_vector` can be resized using the `resize(newsize)` function. This function is not available for `tbits_array`.

## Loops
- Iteration through the container can be done as usual using for loops, ie. `for(size_t i=0 ; i<array.size() ; i++)`. 
- Iterators are not provided. 
- Range base for loops are not provided.

### Full iteration
This provides a way to iterate through the whole range of value of the array. For example, repeatedely incrementing the whole tbits array will provide the following values: {0,0,0}->{0,0,1}->{0,0,-1}->{0,1,0}->{0,1,1}->{0,1,-1}->{0,-1,0}->... etc. until {-1,-1,-1}. Such iteration is obtained using the following instruction on the tbits vector `t`: `for(t; !t.overflow() ; t++) `.
Please note that the `overflow()` function returns `true` only when the tbits vector went from {-1,-1,...,-1} to {0,0,...,0} on the previous use of `++`, or from {0,0,...,0} to {-1,-1,...,-1} on the previous use of `--`. 

## NaN handling
Similar to what is indicated in [tbits](tbits.md), the support for nan value is very limited. While individual ternaries can be set or clear with nan, the only function that the vector of tbits provides is `count_nan()`. All other functions have undefined behaviour on encountering nan. 
