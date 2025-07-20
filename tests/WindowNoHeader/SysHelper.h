#pragma once

#if defined(_WIN64)
    #include "SysHelperWin.h"
#elif defined(__unix)
    #include "SysHelperLin.h"
#else
    #error "SysHelper not supported"
#endif
