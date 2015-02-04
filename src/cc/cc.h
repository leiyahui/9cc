#ifndef cc_cc_h
#define cc_cc_h

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <stdarg.h>
#include <errno.h>
#include <limits.h>
#include <locale.h>
#include <float.h>

#include "config.h"

#define TWOS(size)  (size)>=sizeof(unsigned long long) ? ~0ULL : ~((~0ULL)<<(CHAR_BIT*size))
#define BITS(type)  (CHAR_BIT * (type)->size)
#define ARRAY_SIZE(array)    (sizeof(array) / sizeof((array)[0]))
#define FIELD_SIZEOF(st, f)  (sizeof(((st*)0)->f))

union value {
    long long i;
    unsigned long long u;
    double d;
    long double ld;
    void *p;
    void (*g) ();
};

// print
extern void print(const char *fmt, ...);
extern void fprint(FILE *f, const char *fmt, ...);
extern void vfprint(FILE *f, const char *fmt, va_list ap);
extern void register_print_function(char c, const char * (*g) (void *data));
extern void die(const char *fmt, ...);

// alloc
extern void * cc_malloc(size_t size);
extern void cc_free(void *p);
extern void * alloc_expr_node();
extern void * alloc_stmt_node();
extern void * alloc_decl_node();
extern void * alloc_type_node();
extern void * alloc_symbol_node();
extern void * alloc_table(size_t size);
extern void drop_table(void *table);
extern void * alloc_table_entry(void *table, size_t size);

// string
extern const char *strings(const char *str);
extern const char *stringn(const char *src, int len);
extern const char *stringd(long n);

struct string {
    char     *str;
    unsigned size;
    unsigned capelems;
    unsigned reserve;
};
extern struct string * new_string();
extern unsigned string_length(struct string *s);
extern void string_concats(struct string *s, char *src);
extern void string_concatn(struct string *s, char *src, int len);
extern void string_concatd(struct string *s, long d);
extern char * string_to_array(struct string *s);
extern void free_string(struct string *s);

// vector (container of pointers)
struct vector {
    void        **mem;
    unsigned    elemsize;
    unsigned    elems;
    unsigned    capelems;
    unsigned    reserve;
};
extern struct vector *new_vector();
extern void * vector_at(struct vector *v, unsigned index);
extern void vector_push(struct vector *v, void *elem);
extern void *vector_pop(struct vector *v);
extern void vector_insert(struct vector *v, unsigned index, void *elem);
extern void free_vector(struct vector *v);
extern void purge_vector(struct vector *v);
extern unsigned vector_length(struct vector *v);
extern void *vector_front(struct vector *v);
extern void *vector_back(struct vector *v);
extern void vector_foreach(struct vector *v, void (*func) (void *elem));
extern void ** vector_to_array(struct vector *v);
extern void vector_add_from_array(struct vector *v, void **array);
extern void vector_add_from_vector(struct vector *v, struct vector *v2);

// cc modules
#include "type.h"
#include "lex.h"
#include "sym.h"
#include "ast.h"
#include "error.h"

//kind
enum {
    SCLASS_SPEC = 01, TYPE_QUAL = 02, TYPE_SPEC = 04,
    FUNC_SPEC = 010,
};

#endif
