#include "cc.h"

static const char * node_names[] = {
#define _ns(a)   "",
#define _n(a, b) b,
#include "node.def"
};

const char *nname(struct node * node)
{
    if (node == NULL)
        return "<NULL>";
    
    assert(node->id > BEGIN_NODE_ID && node->id < END_NODE_ID);
    
    return node_names[node->id];
}

struct expr * expr_node(int id, int op, struct expr *l, struct expr *r)
{
    assert(id > BEGIN_EXPR_ID && id < END_EXPR_ID);
    struct expr * expr = NEWS(expr);
    expr->node.id = id;
    expr->op = op;
    KID0(expr) = NODE(l);
    KID1(expr) = NODE(r);
    return expr;
}

struct stmt * stmt_node(int id, struct node *l, struct node *r)
{
    assert(id > BEGIN_STMT_ID && id < END_STMT_ID);
    struct stmt * stmt = NEWS(stmt);
    stmt->node.id = id;
    KID0(stmt) = l;
    KID1(stmt) = r;
    return stmt;
}

struct decl * decl_node(int id, int scope)
{
    assert(id > BEGIN_DECL_ID && id < END_DECL_ID);
    struct decl * decl = NEWS(decl);
    decl->node.id = id;
    decl->scope = scope;
    return decl;
}

struct field * new_field(char *id)
{
    struct field *field = NEWS(field);
    field->name = id;
    return field;
}
