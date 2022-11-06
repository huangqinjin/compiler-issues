#include "Calculator.hpp"


// Implicit instantiation
unsigned Calculator_sum_default()
{
#if CLASS
    return Calculator<SIZE>().sum();
#else
    return Calculator_sum<SIZE>();
#endif
}
