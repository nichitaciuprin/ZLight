#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <memory.h>
#include <time.h>
#include <math.h>
#include <assert.h>

#define STATIC_INIT __attribute__((constructor))

#define GUARD(x) static bool x ## Guard = false; if (x ## Guard) return; x ## Guard = !(x ## Guard);
#define GUARDX static bool guard = false; if (guard) return; guard = true;

#define CALLON(c, x)   static int skip = c; skip--; if (skip == 0) { skip = c; x; }
#define CALLONI(c, x)  static int skip = 0; if (skip == 0) { skip = c; x; } skip--;
