#include "cc.h"

/**
 *  Intermediate Representation
 *
 *  three address code
 */

static struct vector *firs;

static void set_func_context(void)
{
    firs = vec_new();
}

static void restore_func_context(void)
{
    firs = NULL;
}

static void ir_decl(node_t *n)
{
}

static void ir_bop(node_t *n)
{
    
}

static void ir_uop(node_t *n)
{
    
}

static void ir_cond(node_t *n)
{
    
}

static void ir_member(node_t *n)
{
    
}

static void ir_subscript(node_t *n)
{
    
}

static void ir_conv(node_t *n)
{
    
}

static void ir_funcall(node_t *n)
{
    
}

static void ir_ref_expr(node_t *n)
{
    
}

static void ir_integer_literal(node_t *n)
{
    
}

static void ir_float_literal(node_t *n)
{
    
}

static void ir_string_literal(node_t *n)
{
    
}

static void ir_compound_literal(node_t *n)
{
    
}

static void ir_expr(node_t *n)
{
    switch (AST_ID(n)) {
    case BINARY_OPERATOR:
        ir_bop(n);
        break;
    case UNARY_OPERATOR:
        ir_uop(n);
        break;
    case PAREN_EXPR:
        ir_expr(EXPR_OPERAND(n, 0));
        break;
    case COND_EXPR:
        ir_cond(n);
        break;
    case MEMBER_EXPR:
        ir_member(n);
        break;
    case SUBSCRIPT_EXPR:
        ir_subscript(n);
        break;
    case CAST_EXPR:
    case CONV_EXPR:
        ir_conv(n);
        break;
    case CALL_EXPR:
        ir_funcall(n);
        break;
    case REF_EXPR:
        if (EXPR_OP(n) == ENUM)
            ir_integer_literal(n);
        else
            ir_ref_expr(n);
        break;
    case INTEGER_LITERAL:
        ir_integer_literal(n);
        break;
    case FLOAT_LITERAL:
        ir_float_literal(n);
        break;
    case STRING_LITERAL:
        ir_string_literal(n);
        break;
    case COMPOUND_LITERAL:
        ir_compound_literal(n);
        break;
    case INITS_EXPR:
    case VINIT_EXPR:
    default:
        die("unexpected node '%s'", nname(n));
    }
}

static void ir_jmp(node_t *n)
{
    
}

static void ir_label(node_t *n)
{
    
}

static void ir_return(node_t *n)
{
    
}

static void ir_if(node_t *n)
{
    
}

static void ir_compound(node_t *n)
{
    
}

static void ir_gen(node_t *n)
{
    switch (AST_ID(n)) {
    case AST_IF:
        ir_if(n);
        break;
    case AST_COMPOUND:
        ir_compound(n);
        break;
    case AST_RETURN:
        ir_return(n);
        break;
    case AST_LABEL:
        ir_label(n);
        break;
    case AST_JUMP:
        ir_jmp(n);
        break;
    case NULL_STMT:
        break;
    default:
        die("unexpected node '%s'", nname(n));
    }
}

static void ir_stmt(node_t *n)
{
    if (isexpr(n))
        ir_expr(n);
    else if (isdecl(n))
        ir_decl(n);
    else
        ir_gen(n);
}

static void ir_function(node_t *decl)
{
    node_t *stmt = DECL_BODY(decl);

    set_func_context();
    
    ir_stmt(stmt);
    DECL_X_IRS(decl) = firs;

    restore_func_context();
}

static void ir_globalvar(node_t *decl)
{
    
}

node_t * ir(node_t *tree)
{
    cc_assert(istudecl(tree) && errors == 0);

    for (int i = 0; i < LIST_LEN(DECL_EXTS(tree)); i++) {
        node_t *decl = DECL_EXTS(tree)[i];
        if (isfuncdef(decl))
            ir_function(decl);
        else if (isvardecl(decl))
            ir_globalvar(decl);
    }
    
    return tree;
}
