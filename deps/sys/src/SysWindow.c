#if defined(_WIN64)
    #include "SysWindowWin.c"
#elif defined(__unix)
    #include "SysWindowLinux.c"
#else
    #error "SysWindow not supported"
#endif
