#if MODULE
import Calculator;
#else
#include "Calculator.hpp"
#endif

int main(int argc, char* argv[])
{
    return Calculator_sum_default() !=
#if CLASS
    Calculator<SIZE>().sum();
#else
    Calculator_sum<SIZE>();
#endif
}
