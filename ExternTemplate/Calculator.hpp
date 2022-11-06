#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#ifdef _MSC_VER
# define CALCULATOR_EXPORT __declspec(dllexport)
# define CALCULATOR_IMPORT __declspec(dllimport)
#else
# define CALCULATOR_EXPORT __attribute__((visibility("default")))
# define CALCULATOR_IMPORT __attribute__((visibility("default")))
#endif

#if !Calculator_SHARED_LIBRARY
# define CALCULATOR_API
#elif Calculator_EXPORTS
# define CALCULATOR_API CALCULATOR_EXPORT
#else
# define CALCULATOR_API CALCULATOR_IMPORT
#endif

#ifndef SIZE
# define SIZE 400
#endif

// List is used to make generated object files big enough.
template<unsigned N>
struct List
{
    List<N - 1> next;
    unsigned sum() { return N + next.sum(); }
};

template<>
struct List<0>
{
    unsigned sum() { return 0; }
};


// Class template
#if INLINE
template<unsigned N>
struct Calculator
{
    unsigned sum() { return List<N>().sum(); }
};
#else
template<unsigned N>
struct Calculator
{
    unsigned sum();
};

template<unsigned N>
unsigned Calculator<N>::sum()
{
    return List<N>().sum();
}
#endif

// Function template
template<unsigned N>
unsigned Calculator_sum()
{
    return List<N>().sum();
}

extern CALCULATOR_API unsigned Calculator_sum_default();


//Explicit instantiation declaration
#if EXTERN
# if CLASS
    extern template struct CALCULATOR_API Calculator<SIZE>;
# else
    extern template CALCULATOR_API unsigned Calculator_sum<SIZE>();
# endif
#endif

#endif
