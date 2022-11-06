#if MODULE
module Calculator;
#else
#include "Calculator.hpp"
#endif


// Implicit instantiation
unsigned Calculator_sum_default()
{
#if CLASS
    return Calculator<SIZE>().sum();
#else
    return Calculator_sum<SIZE>();
#endif
}
