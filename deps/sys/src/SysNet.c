#if defined(_WIN64)
    #include "SysNetWin.c"
#elif defined(__unix)
    #include "SysNetLinux.c"
#else
    #error "SysNet not supported"
#endif
