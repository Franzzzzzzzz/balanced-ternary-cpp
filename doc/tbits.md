Tbits contain a single value among {-1; 0; 1}. 

## Construction
- Default initialisation to 0.
- Allows direct assignment from an integer equal to 0, -1, or 1. Assignment from any other integer sets the tbits to 0 (zero). 
- use the member `tbits.sign(number)` function to set the tbits to hold the sign of the number.

## Increment and decrement
Pre- and post- increment and decrement are supported with `++` and `--`. The overflow and underflow behavior is as expected. The graph below shows how the tbits changes state based on those operator. 

![Graph showing the change of tbits state upon using the increment and decrement operators](Sketch.png "Increment and decrement")

## Not a Number support
Internally, the tbits is coded as two bits, and can therefore hold 4 value. The fourth value is considered as "Not a Number" (nan), and is given limited support in the library. Note that most functions consider that this state cannot happen, have undefined behavior when encountering them, and should never set this state. Only functions which have `nan` in their name can handle them, so if you do use this state you should test for it before any operation.

Three functions are provided to handle nans. Use the `set_nan` and `clear_nan` function to set and clear nans, the latter always set the tbits to zero. Use the `is_nan` function to check for a nan. 


