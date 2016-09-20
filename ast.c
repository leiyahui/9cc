#include <assert.h>
#include "cc.h"

static const char *node_names[] = {
#define _ns(a)   "",
#define _n(a, b) b,
#include "node.def"
};

const char *nname(int id)
{
    assert(id > BEGIN_NODE_ID && id < END_NODE_ID);

    return node_names[id];
}

struct expr *ast_expr(int id, struct type *ty, struct expr *l, struct expr *r)
{
    assert(id > BEGIN_EXPR_ID && id < END_EXPR_ID);
    struct expr *expr = NEWS0(struct expr, FUNC);
    EXPR_ID(expr) = id;
    EXPR_TYPE(expr) = ty;
    EXPR_OPERAND(expr, 0) = l;
    EXPR_OPERAND(expr, 1) = r;
    return expr;
}

struct expr *ast_uop(int op, struct type *ty, struct expr *l)
{
    struct expr *expr = ast_expr(UNARY_OPERATOR, ty, l, NULL);
    EXPR_OP(expr) = op;
    return expr;
}

struct expr *ast_bop(int op, struct type *ty, struct expr *l, struct expr *r)
{
    struct expr *expr = ast_expr(BINARY_OPERATOR, ty, l, r);
    EXPR_OP(expr) = op;
    return expr;
}

struct expr *ast_conv(struct type *ty, struct expr *l, const char *name)
{
    struct expr *expr = ast_expr(CONV_EXPR, ty, l, NULL);
    EXPR_NAME(expr) = name;
    EXPR_SRC(expr) = EXPR_SRC(l);
    return expr;
}

struct expr *ast_inits(struct type *ty, struct source src)
{
    struct expr *expr = ast_expr(INITS_EXPR, NULL, NULL, NULL);
    EXPR_SRC(expr) = src;
    EXPR_TYPE(expr) = ty;
    return expr;
}

struct expr *ast_vinit(void)
{
    struct expr *vinit = ast_expr(VINIT_EXPR, NULL, NULL, NULL);
    return vinit;
}

struct stmt *ast_stmt(int id, struct source src)
{
    assert(id > BEGIN_STMT_ID && id < END_STMT_ID);
    struct stmt *stmt = NEWS0(struct stmt, FUNC);
    STMT_ID(stmt) = id;
    STMT_SRC(stmt) = src;
    return stmt;
}

const char *gen_label(void)
{
    static size_t i;
    return format(".L%llu", i++);
}

const char *gen_tmpname(void)
{
    static size_t i;
    return format(".T%llu", i++);
}

const char *gen_tmpname_r(void)
{
    static size_t i;
    return format(".t%llu", i++);
}

const char *gen_static_label(void)
{
    static size_t i;
    return format(".S%llu", i++);
}

const char *gen_compound_label(void)
{
    static size_t i;
    return format("__compound_literal.%llu", i++);
}

const char *gen_sliteral_label(void)
{
    static size_t i;
    return format(".LC%llu", i++);
}

const char *gen_block_label(void)
{
    static size_t i;
    return format(".LBB_%llu", i++);
}
