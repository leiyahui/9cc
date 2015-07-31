#ifndef _sym_h
#define _sym_h

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
    unsigned defined : 1;
    struct source src;
    union value value;
    unsigned refs;
    struct symbol *up;
};

// sym
extern void symbol_init();
extern int scopelevel();
extern void enter_scope();
extern void exit_scope();
extern struct table * new_table(struct table *up, int scope);

// create an anonymous symbol
extern struct symbol * anonymous_symbol(struct table **tpp, int scope);

// basic function
struct symbol * find_symbol(const char *name, struct table *table, int scope);

// look up a symbol only in current table
extern struct symbol * locate_symbol(const char *name , struct table *table, int scope);

// look up a symbol from this table to previous one, and so on
extern struct symbol * lookup_symbol(const char *name, struct table *table);

// install a symbol with specified scope
extern struct symbol * install_symbol(const char *name, struct table **tpp, int scope);

extern struct table * identifiers;
extern struct table * constants;
extern struct table * tags;

#define SCOPE  scopelevel()

#endif