#include <stdio.h>   // _fileno, printf, wprintf
#include <io.h>      // _setmode
#include <fcntl.h>   // _O_WTEXT

extern "C" int setup();
extern "C" void sized();

int main()
{
    printf("setup default locale: %d\n", setup());

    sized();

#ifdef _CRT_STDIO_ISO_WIDE_SPECIFIERS  

    fflush(stdout);
    _setmode(_fileno(stdout), _O_TEXT);
    puts("_CRT_STDIO_ISO_WIDE_SPECIFIERS");
    printf(" printf: [%s][%c][%ls][%lc]\n", "你好", ',', L"世界", L'！');

    fflush(stdout);
    _setmode(_fileno(stdout), _O_WTEXT);
    wprintf(L"wprintf: [%s][%c][%ls][%lc]\n", "你好", ',', L"世界", L'！');

#else   // _CRT_STDIO_LEGACY_WIDE_SPECIFIERS (default)

    fflush(stdout);
    _setmode(_fileno(stdout), _O_TEXT);
    puts("_CRT_STDIO_LEGACY_WIDE_SPECIFIERS");
    printf(" printf: [%s][%c][%ls][%lc]\n", "你好", ',', L"世界", L'！');

    fflush(stdout);
    _setmode(_fileno(stdout), _O_WTEXT);
    wprintf(L"wprintf: [%hs][%hc][%s][%c]\n", "你好", ',', L"世界", L'！');

#endif
}
