# Class Template Explicit Instantiation

| MODULE | EXTERN | CLASS | INLINE | SHARED | Times of Instantiation |
|:------:|:------:|:-----:|:------:|:------:|:----------------------:|
| OFF    | OFF    |       |        |        | Three |
| OFF    | ON     | OFF   |        |        | One |
| OFF    | ON     | ON    | OFF    | OFF    | One |
| OFF    | ON     | ON    | ON     | OFF    | **BUG(wonfix): Three** |
| OFF    | ON     | ON    |        | ON     | **BUG: Two with C4910** |
| ON     | ON     | ON    | OFF    | ON     | **Two with C4910** |

## References

- [C4910](https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4910):
`__declspec(dllexport)` and `extern` are incompatible on an explicit instantiation.
- [Explicit instantiation declaration with dllexport behaves differently for function template and class template](
https://developercommunity.visualstudio.com/content/problem/1006968/explicit-template-instantiation-and-dllexport.html).
- [wonfix: c++11 extern templates doesn't work for class templates](https://developercommunity.visualstudio.com/t/c11-extern-templates-doesnt-work-for-class-templat/157868).
- [The extern keyword only applies to member functions defined outside of the body of the class](https://learn.microsoft.com/en-us/cpp/cpp/explicit-instantiation).
