#ifndef _CC_H
#define _CC_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <stdarg.h>
#include <errno.h>
#include <limits.h>
#include <float.h>
#include <wchar.h>
#include <stdbool.h>

#include "config.h"

#define TWOS(size)  (size)>=sizeof(unsigned long long) ? ~0ULL : ~((~0ULL)<<(CHAR_BIT*size))

#define ARRAY_SIZE(array)    (sizeof(array) / sizeof((array)[0]))

#define FIELD_SIZEOF(st, f)  (sizeof(((st*)0)->f))

#include "alloc.h"
#include "str.h"
#include "vector.h"
#include "map.h"

// lex.c
#define EOI  -1

enum {
#define _a(a, b, c, d)  a,
#define _x(a, b, c, d)  a=d,
#define _t(a, b, c)     a,
#include "token.def"
    TOKEND
};

struct source {
    const char *file;
    unsigned line;
    unsigned column;
};

struct token {
    int id;
    const char *name;
    int kind;
};

extern struct source source;
extern struct token  *token;

extern bool is_digit(char c);
extern bool is_hex(char c);
extern bool is_digithex(char c);

extern void input_init();
extern int  gettok();
extern struct token *  lookahead();
extern void expect(int t);
extern void match(int t, int follow[]);
extern const char *tname(int t);

// value

union value {
    long long i;
    unsigned long long u;
    double d;
    long double ld;
    void *p;
    void (*g) ();
};

#define is_assign_op(op)    ((op == '=') || (op >= MULEQ && op <= RSHIFTEQ))

// ast.h
#include "ast.h"

// expr.c
extern struct node * expression();
extern struct node * assign_expr();
extern int intexpr();

// decl.c
extern struct node * initializer_list(struct type *ty);
extern bool istypename(struct token *t);
extern struct node ** declaration();
extern struct node * translation_unit();
extern struct type * typename();
extern int firstdecl(struct token *t);
extern int firststmt(struct token *t);
extern int firstexpr(struct token *t);

// stmt.c
extern struct node * compound_stmt();

#define LEFT(n)    (n->kids[0])
#define RIGHT(n)    (n->kids[1])

#define isexpr(n)  (n->id > BEGIN_EXPR_ID && n->id < END_EXPR_ID)
#define isdecl(n)  (n->id > BEGIN_DECL_ID && n->id < END_DECL_ID)
#define isstmt(n)  (n->id > BEGIN_STMT_ID && n->id < END_STMT_ID)
#define isfuncdecl(n) (n->id == FUNC_DECL)
#define isfuncdef(n) (isfuncdecl(n) && KID0(n) && KID0(n)->id == COMPOUND_STMT)
#define isliteral(n) (n->id > BEGIN_LITERAL_ID && n->id < END_LITERAL_ID)
#define is_switch_stmt(n) (n && n->id == SWITCH_STMT)
#define is_iteration_stmt(n) (n && (n->id == FOR_STMT || n->id == WHILE_STMT || n->id == DO_WHILE_STMT))

struct field {
    const char *name;
    struct type *type;
    int offset;
    int bitsize;
};

// type.c
struct type {
    int kind;
    const char *name;
    size_t size;
    unsigned rank;
    bool inlined;
    struct type *type;
    const char *tag;
    union {
        // function
        struct {
            struct symbol **params;
            unsigned oldstyle : 1;
        }f;
        // array
        struct {
            struct node *assign;
            unsigned is_const : 1;
            unsigned is_volatile : 1;
            unsigned is_restrict : 1;
            unsigned is_static : 1;
            unsigned wildcard : 1;
        }a;
        // enum/struct/union
        struct {
            struct symbol **ids;
            struct field **fields;
        }s;
    }u;
    struct {
        union value max;
        union value min;
    }limits;
};

extern void type_init();
extern int op(struct type *type);
extern void prepend_type(struct type **typelist, struct type *type);
extern void attach_type(struct type **typelist, struct type *type);
extern struct type * qual(int t, struct type *ty);
extern bool eqtype(struct type *ty1, struct type *ty2);
extern bool eqarith(struct type *ty1, struct type * ty2);
extern struct type * lookup_typedef_name(const char *id);
extern bool is_typedef_name(const char *id);
extern struct field * new_field(char *id);
extern struct type * array_type();
extern struct type * ptr_type(struct type *ty);
extern struct type * func_type();
extern struct symbol * tag_type(int t, const char *tag, struct source src);
extern struct symbol * tag_sym(struct type *ty);
extern const char *type2s(struct type *ty);

extern struct type    *chartype;               // char
extern struct type    *unsignedchartype;       // unsigned char
extern struct type    *signedchartype;         // signed char
extern struct type    *wchartype;              // wchar_t
extern struct type    *shorttype;              // short (int)
extern struct type    *unsignedshorttype;      // unsigned short (int)
extern struct type    *inttype;                // int
extern struct type    *unsignedinttype;        // unsigned (int)
extern struct type    *longtype;               // long
extern struct type    *unsignedlongtype;       // unsigned long (int)
extern struct type    *longlongtype;           // long long (int)
extern struct type    *unsignedlonglongtype;   // unsigned long long (int)
extern struct type    *floattype;              // float
extern struct type    *doubletype;             // double
extern struct type    *longdoubletype;         // long double
extern struct type    *voidtype;               // void
extern struct type    *booltype;	       // bool
extern struct type    *vartype;		       // variable type

#define BITS(type)      (CHAR_BIT * (type)->size)

extern bool isconst(struct type *ty);
extern bool isvolatile(struct type *ty);
extern bool isrestrict(struct type *ty);
#define isinline(ty)    ((ty)->inlined)
#define isqual(ty)      (isconst(ty) || isvolatile(ty) || isrestrict(ty))
#define unqual(ty)      (isqual(ty) ? (ty)->type : (ty))

#define kind(ty)        (unqual(ty)->kind)
#define rtype(ty)       (unqual(ty)->type)
#define size(ty)        (unqual(ty)->size)
#define rank(ty)        (unqual(ty)->rank)

extern bool isfunc(struct type *type);
extern bool isarray(struct type *type);
extern bool isptr(struct type *type);
extern bool isvoid(struct type *type);
extern bool isenum(struct type *type);
extern bool isstruct(struct type *type);
extern bool isunion(struct type *type);

extern bool isint(struct type *ty);
extern bool isfloat(struct type *ty);
extern bool isarith(struct type *ty);
extern bool isscalar(struct type *ty);

// sym.c
// scope level
enum {
    CONSTANT,
    GLOBAL,
    PARAM,
    LOCAL,
};

struct symbol {
    int scope;
    const char *name;
    int sclass;
    struct type  *type;
    bool defined;
    struct source src;
    union value value;
    unsigned refs;
};

struct table {
    int scope;
    struct table *up;
    struct map *map;
};

// sym
extern int scopelevel();
extern void enter_scope();
extern void exit_scope();

// create an anonymous symbol
extern struct symbol * anonymous(struct table **tpp, int scope);

// look up a symbol from this table to previous one, and so on
extern struct symbol * lookup(const char *name, struct table *table);

// install a symbol with specified scope
extern struct symbol * install(const char *name, struct table **tpp, int scope);

// sym->name is NULL or anynomous
extern bool issymnamed(struct symbol *sym);

extern struct table * identifiers;
extern struct table * constants;
extern struct table * tags;

#define SCOPE  scopelevel()

#define currentscope(sym)   (sym->scope == SCOPE || (sym->scope == PARAM && SCOPE == LOCAL))

// error.c
extern unsigned errors;
extern unsigned warnings;
extern void warning(const char *fmt, ...);
extern void error(const char *fmt, ...);
extern void fatal(const char *fmt, ...);
extern void warningf(struct source src, const char *fmt, ...);
extern void errorf(struct source src, const char *fmt, ...);

extern void begin_call(const char *funcname);
extern void end_call(const char *funcname);

extern void redefinition_error(struct source src, struct symbol *sym);
extern void conflicting_types_error(struct source src, struct symbol *sym);

extern void die(const char *fmt, ...);
extern void println(const char *fmt, ...);

// gen.c
void walk(struct node *tree);

// print.c
extern void print_tree(struct node *tree);

#endif
