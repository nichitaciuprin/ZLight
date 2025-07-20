#pragma once

#if defined(_WIN64)
    #include "SysWindowWin.h"
#elif defined(__unix)
    #include "SysWindowLin.h"
#else
    #error "SysWindow not supported"
#endif
