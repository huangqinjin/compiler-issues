# Class Template Explicit Instantiation

| EXTERN | CLASS | INLINE | SHARED | Times of Instantiation |
|:------:|:-----:|:------:|:------:|:----------------------:|
| OFF    |       |        |        | Three |
| ON     | OFF   |        |        | One |
| ON     | ON    | OFF    | OFF    | One |
| ON     | ON    | ON     | OFF    | **BUG: Three** |
| ON     | ON    |        | ON     | **BUG: Two with C4910** |

## References

- [C4910](https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4910):
`__declspec(dllexport)` and `extern` are incompatible on an explicit instantiation.
- [Explicit instantiation declaration with dllexport behaves differently for function template and class template](
https://developercommunity.visualstudio.com/content/problem/1006968/explicit-template-instantiation-and-dllexport.html).
