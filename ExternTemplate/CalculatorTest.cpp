#include "Calculator.hpp"

int main(int argc, char* argv[])
{
    return Calculator_sum_default() !=
#if CLASS
    Calculator<SIZE>().sum();
#else
    Calculator_sum<SIZE>();
#endif
}
