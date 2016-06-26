#ifndef _CPP_INTERNAL_H
#define _CPP_INTERNAL_H

#include <stddef.h>
#include <stdbool.h>
#include <time.h>
#include <locale.h>
#include <assert.h>

#include "lex.h"
#include "../utils/utils.h"
#include "../sys/sys.h"

extern void *alloc_macro(void);
extern void *alloc_hideset(void);
extern void *alloc_cpp_ident(void);
extern bool eval_cpp_cond(void);

#include "../error.h"

#endif
