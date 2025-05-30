#if defined(_WIN64)
    #include "SysHelperWin.c"
#elif defined(__unix)
    #include "SysHelperLinux.c"
#else
    #error "SysHelper not supported"
#endif
