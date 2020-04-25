#include "Calculator.hpp"


//Explicit instantiation definition
#if CLASS
template struct CALCULATOR_API Calculator<SIZE>;
#else
template CALCULATOR_API unsigned Calculator_sum<SIZE>();
#endif
