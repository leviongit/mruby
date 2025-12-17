/* A Bison parser, made by Lrama 0.7.0.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* First part of user prologue.  */
#line 7 "mrbgems/mruby-compiler/core/parse.y"

#undef PARSER_DEBUG
#ifdef PARSER_DEBUG
# define YYDEBUG 1
#endif
#define YYSTACK_USE_ALLOCA 1

#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <mruby.h>
#include <mruby/compile.h>
#include <mruby/proc.h>
#include <mruby/error.h>
#include <mruby/throw.h>
#include <mruby/string.h>
#include <mruby/dump.h>
#include <mruby/internal.h>
#include <mruby/presym.h>
#include "node.h"

#define YYLEX_PARAM p

#define mrbc_malloc(s) mrb_basic_alloc_func(NULL,(s))
#define mrbc_realloc(p,s) mrb_basic_alloc_func((p),(s))
#define mrbc_free(p) mrb_basic_alloc_func((p),0)

typedef mrb_ast_node node;
typedef struct mrb_parser_state parser_state;
typedef struct mrb_parser_heredoc_info parser_heredoc_info;

static int yyparse(parser_state *p);
static int yylex(void *lval, void *lp, parser_state *p);
static void yyerror(void *lp, parser_state *p, const char *s);
static void yywarning(parser_state *p, const char *s);
static void backref_error(parser_state *p, node *n);
static void void_expr_error(parser_state *p, node *n);
static void tokadd(parser_state *p, int32_t c);
static const char* tok(parser_state *p);
static int toklen(parser_state *p);

/* Forward declarations for variable-sized simple node functions */

/* Forward declarations for variable-sized advanced node functions */

/* Helper function to check node type for both traditional and variable-sized nodes */
static mrb_bool node_type_p(node *n, enum node_type type);

#define identchar(c) (ISALNUM(c) || (c) == '_' || !ISASCII(c))

typedef unsigned int stack_type;

#define BITSTACK_PUSH(stack, n) ((stack) = ((stack)<<1)|((n)&1))
#define BITSTACK_POP(stack)     ((stack) = (stack) >> 1)
#define BITSTACK_LEXPOP(stack)  ((stack) = ((stack) >> 1) | ((stack) & 1))
#define BITSTACK_SET_P(stack)   ((stack)&1)

#define COND_PUSH(n)    BITSTACK_PUSH(p->cond_stack, (n))
#define COND_POP()      BITSTACK_POP(p->cond_stack)
#define COND_LEXPOP()   BITSTACK_LEXPOP(p->cond_stack)
#define COND_P()        BITSTACK_SET_P(p->cond_stack)

#define CMDARG_PUSH(n)  BITSTACK_PUSH(p->cmdarg_stack, (n))
#define CMDARG_POP()    BITSTACK_POP(p->cmdarg_stack)
#define CMDARG_LEXPOP() BITSTACK_LEXPOP(p->cmdarg_stack)
#define CMDARG_P()      BITSTACK_SET_P(p->cmdarg_stack)

#define SET_LINENO(c,n) (((struct mrb_ast_var_header*)(c))->lineno = (n))

#define NUM_SUFFIX_R   (1<<0)
#define NUM_SUFFIX_I   (1<<1)

static inline mrb_sym
intern_cstr_gen(parser_state *p, const char *s)
{
  return mrb_intern_cstr(p->mrb, s);
}
#define intern_cstr(s) intern_cstr_gen(p,(s))

static inline mrb_sym
intern_gen(parser_state *p, const char *s, size_t len)
{
  return mrb_intern(p->mrb, s, len);
}
#define intern(s,len) intern_gen(p,(s),(len))

#define intern_op(op) MRB_OPSYM_2(p->mrb, op)

static mrb_sym
intern_numparam_gen(parser_state *p, int num)
{
  char buf[3];
  buf[0] = '_'; buf[1] = '0'+num; buf[2] = '\0';
  return intern(buf, 2);
}
#define intern_numparam(n) intern_numparam_gen(p,(n))

static void
cons_free_gen(parser_state *p, node *cons)
{
  cons->cdr = p->cells;
  p->cells = cons;
}
#define cons_free(c) cons_free_gen(p, (c))

static void*
parser_palloc(parser_state *p, size_t size)
{
  void *m = mempool_alloc(p->pool, size);

  if (!m) {
    MRB_THROW(p->mrb->jmp);
  }
  return m;
}

#define parser_pfree(ptr) do { if (sizeof(node) <= sizeof(*(ptr))) cons_free((node*)ptr);} while (0)

static node*
cons_gen(parser_state *p, node *car, node *cdr)
{
  struct mrb_ast_node *c;

  /* Try to reuse from free list first - only for 16-byte nodes */
  if (p->cells) {
    c = (struct mrb_ast_node*)p->cells;
    p->cells = p->cells->cdr;
  }
  else {
    c = (struct mrb_ast_node*)parser_palloc(p, sizeof(struct mrb_ast_node));
  }
  c->car = car;
  c->cdr = cdr;
  /* Don't initialize location fields for structure nodes - saves CPU */
  return (node*)c;
}

/* Head-only location optimization: separate functions for head vs structure nodes */
#define cons(a,b) cons_gen(p,(a),(b))           /* Structure nodes - no location */
/* Initialize variable node header */
static void
init_var_header(struct mrb_ast_var_header *header, parser_state *p, enum node_type type)
{
  header->lineno = p->lineno;
  header->filename_index = p->current_filename_index;
  header->node_type = (uint8_t)type;

  /* Handle file boundary edge case */
  if (p->lineno == 0 && p->current_filename_index > 0) {
    header->filename_index--;
  }
}

/* Combined allocate + init header helper */
static inline void*
new_node(parser_state *p, size_t size, enum node_type type)
{
  void *n = parser_palloc(p, size);
  init_var_header((struct mrb_ast_var_header*)n, p, type);
  return n;
}

/* Type-safe macro wrapper for node allocation */
#define NEW_NODE(type_name, node_type) \
  (struct mrb_ast_##type_name##_node*)new_node(p, sizeof(struct mrb_ast_##type_name##_node), node_type)

static node*
list1_gen(parser_state *p, node *a)
{
  return cons(a, 0);
}
#define list1(a) list1_gen(p, (a))

static node*
list2_gen(parser_state *p, node *a, node *b)
{
  return cons(a, cons(b, 0));
}
#define list2(a,b) list2_gen(p, (a),(b))

static node*
list3_gen(parser_state *p, node *a, node *b, node *c)
{
  return cons(a, cons(b, cons(c, 0)));
}
#define list3(a,b,c) list3_gen(p, (a),(b),(c))

static node*
append_gen(parser_state *p, node *a, node *b)
{
  node *c = a;

  if (!a) return b;
  if (!b) return a;
  while (c->cdr) {
    c = c->cdr;
  }
  c->cdr = b;
  return a;
}
#define append(a,b) append_gen(p,(a),(b))
#define push(a,b) append_gen(p,(a),list1(b))

static char*
parser_strndup(parser_state *p, const char *s, size_t len)
{
  char *b = (char*)parser_palloc(p, len+1);

  memcpy(b, s, len);
  b[len] = '\0';
  return b;
}
#undef strndup
#define strndup(s,len) parser_strndup(p, s, len)

static char*
parser_strdup(parser_state *p, const char *s)
{
  return parser_strndup(p, s, strlen(s));
}
#undef strdup
#define strdup(s) parser_strdup(p, s)

static void
dump_int(uint16_t i, char *s)
{
  char *p = s;
  char *t = s;

  while (i > 0) {
    *p++ = (i % 10)+'0';
    i /= 10;
  }
  if (p == s) *p++ = '0';
  *p = 0;
  p--;  /* point the last char */
  while (t < p) {
    char c = *t;
    *t++ = *p;
    *p-- = c;
  }
}

/* xxx ----------------------------- */

static node*
local_switch(parser_state *p)
{
  node *prev = p->locals;

  p->locals = cons(0, 0);
  return prev;
}

static void
local_resume(parser_state *p, node *prev)
{
  p->locals = prev;
}

static void
local_nest(parser_state *p)
{
  p->locals = cons(0, p->locals);
}

static void
local_unnest(parser_state *p)
{
  if (p->locals) {
    p->locals = p->locals->cdr;
  }
}

static mrb_bool
local_var_p(parser_state *p, mrb_sym sym)
{
  const struct RProc *u;
  node *l = p->locals;

  while (l) {
    node *n = l->car;
    while (n) {
      if (node_to_sym(n->car) == sym) return TRUE;
      n = n->cdr;
    }
    l = l->cdr;
  }

  u = p->upper;
  while (u && !MRB_PROC_CFUNC_P(u)) {
    const struct mrb_irep *ir = u->body.irep;
    const mrb_sym *v = ir->lv;
    int i;

    if (v) {
      for (i=0; i+1 < ir->nlocals; i++) {
        if (v[i] == sym) return TRUE;
      }
    }
    if (MRB_PROC_SCOPE_P(u)) break;
    u = u->upper;
  }
  return FALSE;
}

static void
local_add_f(parser_state *p, mrb_sym sym)
{
  if (p->locals) {
    node *n = p->locals->car;
    while (n) {
      if (node_to_sym(n->car) == sym) {
        mrb_int len;
        const char* name = mrb_sym_name_len(p->mrb, sym, &len);
        if (len > 0 && name[0] != '_') {
          yyerror(NULL, p, "duplicated argument name");
          return;
        }
      }
      n = n->cdr;
    }
    p->locals->car = push(p->locals->car, sym_to_node(sym));
  }
}

static void
local_add(parser_state *p, mrb_sym sym)
{
  if (!local_var_p(p, sym)) {
    local_add_f(p, sym);
  }
}

/* allocate register for block */
#define local_add_blk(p) local_add_f(p, 0)

static void
local_add_kw(parser_state *p, mrb_sym kwd)
{
  /* allocate register for keywords hash */
  local_add_f(p, kwd ? kwd : intern_op(pow));
}

static node*
locals_node(parser_state *p)
{
  return p->locals ? p->locals->car : NULL;
}

/* Helper function to check node type for both traditional and variable-sized nodes */
static mrb_bool
node_type_p(node *n, enum node_type type)
{
  if (!n) return FALSE;

  /* Check if this is a variable-sized node */
  struct mrb_ast_var_header *header = (struct mrb_ast_var_header*)n;
  return ((enum node_type)header->node_type == type);
}

/* Helper functions for variable-sized node detection */
static enum node_type
get_node_type(node *n)
{
  if (!n) return (enum node_type)0;

  /* Try to interpret as variable-sized node */
  struct mrb_ast_var_header *header = (struct mrb_ast_var_header*)n;
  enum node_type type = (enum node_type)header->node_type;

  /* Validate that the node type is within valid range for variable-sized nodes */
  if (type >= NODE_SCOPE && type < NODE_LAST) {
    return type;
  }

  /* If node type is invalid, this is likely a cons-list node */
  /* Return a special sentinel value to indicate cons-list fallback */
  return NODE_LAST; /* Use NODE_LAST as sentinel for cons-list nodes */
}

static void
nvars_nest(parser_state *p)
{
  p->nvars = cons(int_to_node(0), p->nvars);
}

static void
nvars_block(parser_state *p)
{
  p->nvars = cons(int_to_node(-2), p->nvars);
}

static void
nvars_unnest(parser_state *p)
{
  p->nvars = p->nvars->cdr;
}

/* struct: scope_node(locals, body) */
static node*
new_scope(parser_state *p, node *body)
{
  struct mrb_ast_scope_node *scope_node = NEW_NODE(scope, NODE_SCOPE);
  scope_node->locals = locals_node(p);
  scope_node->body = body;
  return (node*)scope_node;
}

/* struct: stmts_node(stmts) - uses cons list */
static node*
new_stmts(parser_state *p, node *body)
{
  struct mrb_ast_stmts_node *n = NEW_NODE(stmts, NODE_STMTS);
  n->stmts = body ? list1(body) : 0;  /* Wrap single statement in cons-list */

  return (node*)n;
}

/* struct: begin_node(body) */
static node*
new_begin(parser_state *p, node *body)
{
  struct mrb_ast_begin_node *begin_node = NEW_NODE(begin, NODE_BEGIN);
  begin_node->body = body;
  return (node*)begin_node;
}

#define newline_node(n) (n)

/* struct: rescue_node(body, rescue_clauses, else_clause) */
static node*
new_rescue(parser_state *p, node *body, node *resq, node *els)
{
  struct mrb_ast_rescue_node *n = NEW_NODE(rescue, NODE_RESCUE);
  n->body = body;
  n->rescue_clauses = resq;
  n->else_clause = els;

  return (node*)n;
}

static node*
new_mod_rescue(parser_state *p, node *body, node *resq)
{
  return new_rescue(p, body, list1(list3(0, 0, resq)), 0);
}

/* struct: ensure_node(body, ensure_clause) */
static node*
new_ensure(parser_state *p, node *a, node *b)
{
  struct mrb_ast_ensure_node *ensure_node = NEW_NODE(ensure, NODE_ENSURE);
  ensure_node->body = a;
  ensure_node->ensure_clause = b;
  return (node*)ensure_node;
}

/* struct: nil_node() */
static node*
new_nil(parser_state *p)
{
  struct mrb_ast_nil_node *n = NEW_NODE(nil, NODE_NIL);

  return (node*)n;
}

/* struct: true_node() */
static node*
new_true(parser_state *p)
{
  struct mrb_ast_true_node *n = NEW_NODE(true, NODE_TRUE);

  return (node*)n;
}

/* struct: false_node() */
static node*
new_false(parser_state *p)
{
  struct mrb_ast_false_node *n = NEW_NODE(false, NODE_FALSE);

  return (node*)n;
}

/* struct: alias_node(new_name, old_name) */
static node*
new_alias(parser_state *p, mrb_sym a, mrb_sym b)
{
  struct mrb_ast_alias_node *alias_node = NEW_NODE(alias, NODE_ALIAS);
  alias_node->new_name = a;
  alias_node->old_name = b;
  return (node*)alias_node;
}

/* struct: if_node(cond, then_body, else_body) */
static node*
new_if(parser_state *p, node *condition, node *then_body, node *else_body)
{
  void_expr_error(p, condition);

  struct mrb_ast_if_node *n = NEW_NODE(if, NODE_IF);
  n->condition = condition;
  n->then_body = then_body;
  n->else_body = else_body;

  return (node*)n;
}

/* struct: while_node(cond, body) */
static node*
new_while(parser_state *p, node *condition, node *body)
{
  void_expr_error(p, condition);

  struct mrb_ast_while_node *n = NEW_NODE(while, NODE_WHILE);
  n->condition = condition;
  n->body = body;

  return (node*)n;
}

/* struct: until_node(cond, body) */
static node*
new_until(parser_state *p, node *condition, node *body)
{
  void_expr_error(p, condition);

  struct mrb_ast_until_node *n = NEW_NODE(until, NODE_UNTIL);
  n->condition = condition;
  n->body = body;

  return (node*)n;
}

/* struct: while_node(cond, body) */
static node*
new_while_mod(parser_state *p, node *condition, node *body)
{
  node *while_node = new_while(p, condition, body);
  struct mrb_ast_while_node *n = (struct mrb_ast_while_node*)while_node;
  n->header.node_type = NODE_WHILE_MOD;
  return while_node;
}

/* struct: until_node(cond, body) */
static node*
new_until_mod(parser_state *p, node *a, node *b)
{
  node *until_node = new_until(p, a, b);
  struct mrb_ast_until_node *n = (struct mrb_ast_until_node*)until_node;
  n->header.node_type = NODE_UNTIL_MOD;
  return until_node;
}


/* struct: for_node(var, obj, body) */
static node*
new_for(parser_state *p, node *v, node *o, node *b)
{
  void_expr_error(p, o);

  struct mrb_ast_for_node *n = NEW_NODE(for, NODE_FOR);
  n->var = v;
  n->iterable = o;
  n->body = b;

  return (node*)n;
}

/* struct: case_node(expr, when_clauses) - uses cons list */
static node*
new_case(parser_state *p, node *a, node *b)
{
  void_expr_error(p, a);

  struct mrb_ast_case_node *n = NEW_NODE(case, NODE_CASE);
  n->value = a;
  n->body = b;

  return (node*)n;
}

/* struct: postexe_node(body) */
static node*
new_postexe(parser_state *p, node *a)
{
  struct mrb_ast_postexe_node *postexe_node = NEW_NODE(postexe, NODE_POSTEXE);
  postexe_node->body = a;
  return (node*)postexe_node;
}

/* struct: self_node() */
static node*
new_self(parser_state *p)
{
  struct mrb_ast_self_node *n = NEW_NODE(self, NODE_SELF);

  return (node*)n;
}

/* struct: call_node(receiver, method, args) */
static node*
new_call(parser_state *p, node *receiver, mrb_sym method, node *args, int pass)
{
  /* Calculate size needed (fixed size now) */  struct mrb_ast_call_node *n = NEW_NODE(call, NODE_CALL);
  n->receiver = receiver;
  n->method_name = method;
  n->safe_call = (pass == 0); /* pass == 0 means safe call (&.) */

  /* Store args pointer directly - no need to unpack and repack */
  n->args = args;

  void_expr_error(p, receiver);
  return (node*)n;
}

/* struct: fcall_node(method, args) */
static node*
new_fcall(parser_state *p, mrb_sym b, node *c)
{
  return new_call(p, NULL, b, c, '.');
}

/* (a b . c) */
static node*
new_callargs(parser_state *p, node *a, node *b, node *c)
{
  /* Allocate struct mrb_ast_callargs (fixed size, like new_args) */
  struct mrb_ast_callargs *callargs = (struct mrb_ast_callargs*)parser_palloc(p, sizeof(struct mrb_ast_callargs));

  /* Initialize members directly */
  callargs->regular_args = a;   /* Cons list of regular arguments (preserves splat compatibility) */
  callargs->keyword_args = b;   /* Keyword arguments hash node */
  callargs->block_arg = c;      /* Block argument node */

  /* Return direct cast to node (like new_args) */
  return (node*)callargs;
}

/* struct: super_node(args) */
static node*
new_super(parser_state *p, node *c)
{
  struct mrb_ast_super_node *n = NEW_NODE(super, NODE_SUPER);
  n->args = c;

  return (node*)n;
}

/* struct: zsuper_node() */
static node*
new_zsuper(parser_state *p)
{
  struct mrb_ast_super_node *n = NEW_NODE(super, NODE_ZSUPER);
  n->args = NULL;  /* zsuper initially has no args, but may be added by call_with_block */
  return (node*)n;
}

/* struct: yield_node(args) */
static node*
new_yield(parser_state *p, node *c)
{
  /* Handle callargs structure - direct casting like new_args() */
  if (c) {
    struct mrb_ast_callargs *callargs = (struct mrb_ast_callargs*)c;
    if (callargs->block_arg) {
      yyerror(NULL, p, "both block arg and actual block given");
    }
  }  struct mrb_ast_yield_node *n = NEW_NODE(yield, NODE_YIELD);
  n->args = c;

  return (node*)n;
}

/* struct: return_node(value) */
static node*
new_return(parser_state *p, node *c)
{
  struct mrb_ast_return_node *n = NEW_NODE(return, NODE_RETURN);
  n->args = c;

  return (node*)n;
}

/* struct: break_node(value) */
static node*
new_break(parser_state *p, node *c)
{
  struct mrb_ast_break_node *n = NEW_NODE(break, NODE_BREAK);
  n->value = c;
  return (node*)n;
}

/* struct: next_node(value) */
static node*
new_next(parser_state *p, node *c)
{
  struct mrb_ast_next_node *n = NEW_NODE(next, NODE_NEXT);
  n->value = c;
  return (node*)n;
}

/* struct: redo_node() */
static node*
new_redo(parser_state *p)
{
  struct mrb_ast_redo_node *n = NEW_NODE(redo, NODE_REDO);
  return (node*)n;
}

/* struct: retry_node() */
static node*
new_retry(parser_state *p)
{
  struct mrb_ast_retry_node *n = NEW_NODE(retry, NODE_RETRY);
  return (node*)n;
}

/* struct: dot2_node(beg, end) */
static node*
new_dot2(parser_state *p, node *a, node *b)
{
  struct mrb_ast_dot2_node *n = NEW_NODE(dot2, NODE_DOT2);
  n->left = a;
  n->right = b;

  return (node*)n;
}

/* struct: dot3_node(beg, end) */
static node*
new_dot3(parser_state *p, node *a, node *b)
{
  struct mrb_ast_dot3_node *n = NEW_NODE(dot3, NODE_DOT3);
  n->left = a;
  n->right = b;

  return (node*)n;
}

/* struct: colon2_node(base, name) */
static node*
new_colon2(parser_state *p, node *b, mrb_sym c)
{
  void_expr_error(p, b);

  struct mrb_ast_colon2_node *colon2_node = NEW_NODE(colon2, NODE_COLON2);
  colon2_node->base = b;
  colon2_node->name = c;
  return (node*)colon2_node;
}

/* struct: colon3_node(name) */
static node*
new_colon3(parser_state *p, mrb_sym c)
{
  struct mrb_ast_colon3_node *colon3_node = NEW_NODE(colon3, NODE_COLON3);
  colon3_node->name = c;
  return (node*)colon3_node;
}

/* struct: and_node(left, right) */
static node*
new_and(parser_state *p, node *a, node *b)
{
  void_expr_error(p, a);

  struct mrb_ast_and_node *n = NEW_NODE(and, NODE_AND);
  n->left = a;
  n->right = b;

  return (node*)n;
}

/* struct: or_node(left, right) */
static node*
new_or(parser_state *p, node *a, node *b)
{
  void_expr_error(p, a);

  struct mrb_ast_or_node *n = NEW_NODE(or, NODE_OR);
  n->left = a;
  n->right = b;

  return (node*)n;
}

/* struct: array_node(elements) - uses cons list */
static node*
new_array(parser_state *p, node *a)
{
  struct mrb_ast_array_node *n = NEW_NODE(array, NODE_ARRAY);
  n->elements = a;

  return (node*)n;
}

/* struct: splat_node(value) */
static node*
new_splat(parser_state *p, node *a)
{
  void_expr_error(p, a);

  struct mrb_ast_splat_node *splat_node = NEW_NODE(splat, NODE_SPLAT);
  splat_node->value = a;
  return (node*)splat_node;
}

/* struct: hash_node(pairs) - uses cons list */
static node*
new_hash(parser_state *p, node *a)
{
  struct mrb_ast_hash_node *n = NEW_NODE(hash, NODE_HASH);
  n->pairs = a;

  return (node*)n;
}

/* (:sym . a) */
/* Symbol node creation - supports both variable and legacy modes */
static node*
new_sym(parser_state *p, mrb_sym sym)
{
  struct mrb_ast_sym_node *n = NEW_NODE(sym, NODE_SYM);
  n->symbol = sym;

  return (node*)n;
}

static node*
new_xvar(parser_state *p, mrb_sym sym, enum node_type type)
{
  struct mrb_ast_var_node *n = NEW_NODE(var, type);
  n->symbol = sym;

  return (node*)n;
}

#define new_lvar(p, sym) new_xvar(p, sym, NODE_LVAR)
#define new_ivar(p, sym) new_xvar(p, sym, NODE_IVAR)
#define new_gvar(p, sym) new_xvar(p, sym, NODE_GVAR)
#define new_cvar(p, sym) new_xvar(p, sym, NODE_CVAR)

static mrb_sym
new_strsym(parser_state *p, node* str)
{
  size_t len = (size_t)str->car;
  const char *s = (const char*)str->cdr;

  return mrb_intern(p->mrb, s, len);
}

/* (:nvar . a) */
static node*
new_nvar(parser_state *p, int num)
{
  int nvar;
  node *nvars = p->nvars->cdr;
  while (nvars) {
    nvar = node_to_int(nvars->car);
    if (nvar == -2) break; /* top of the scope */
    if (nvar > 0) {
      yyerror(NULL, p, "numbered parameter used in outer block");
      break;
    }
    nvars->car = int_to_node(-1);
    nvars = nvars->cdr;
  }
  nvar = node_to_int(p->nvars->car);
  if (nvar == -1) {
    yyerror(NULL, p, "numbered parameter used in inner block");
  }
  else {
    p->nvars->car = int_to_node(nvar > num ? nvar : num);
  }
  struct mrb_ast_nvar_node *n = NEW_NODE(nvar, NODE_NVAR);
  n->num = num;
  return (node*)n;
}

/* struct: const_node(name) */
static node*
new_const(parser_state *p, mrb_sym sym)
{
  struct mrb_ast_const_node *n = NEW_NODE(const, NODE_CONST);
  n->symbol = sym;

  return (node*)n;
}

/* struct: undef_node(syms) - uses cons list */
static node*
new_undef(parser_state *p, node *syms)
{
  struct mrb_ast_undef_node *undef_node = NEW_NODE(undef, NODE_UNDEF);
  undef_node->syms = syms;
  return (node*)undef_node;
}

/* struct: class_node(path, super, body) */
static node*
new_class(parser_state *p, node *c, node *s, node *b)
{
  void_expr_error(p, s);

  struct mrb_ast_class_node *n = NEW_NODE(class, NODE_CLASS);
  n->name = c;
  n->superclass = s;
  n->body = cons(locals_node(p), b);

  return (node*)n;
}

/* struct: sclass_node(obj, body) */
static node*
new_sclass(parser_state *p, node *o, node *b)
{
  void_expr_error(p, o);

  struct mrb_ast_sclass_node *n = NEW_NODE(sclass, NODE_SCLASS);
  n->obj = o;
  n->body = cons(locals_node(p), b);

  return (node*)n;
}

/* struct: module_node(path, body) */
static node*
new_module(parser_state *p, node *m, node *b)
{
  struct mrb_ast_module_node *n = NEW_NODE(module, NODE_MODULE);
  n->name = m;
  n->body = cons(locals_node(p), b);

  return (node*)n;
}

/* struct: def_node(name, args, body) */
static node*
new_def(parser_state *p, mrb_sym name)
{
  struct mrb_ast_def_node *n = NEW_NODE(def, NODE_DEF);
  n->name = name;
  n->args = (struct mrb_ast_args *)int_to_node(p->cmdarg_stack);
  n->locals = local_switch(p);
  n->body = NULL;

  return (node*)n;
}

static void
defn_setup(parser_state *p, node *d, node *a, node *b)
{
  struct mrb_ast_def_node *n = def_node(d);
  node *locals = n->locals;

  n->locals = locals_node(p);
  p->cmdarg_stack = node_to_int(n->args);
  n->args = (struct mrb_ast_args *)a;
  n->body = b;
  local_resume(p, locals);
}

/* struct: sdef_node(obj, name, args, body) */
static node*
new_sdef(parser_state *p, node *o, mrb_sym name)
{
  void_expr_error(p, o);

  struct mrb_ast_sdef_node *sdef_node = NEW_NODE(sdef, NODE_SDEF);
  sdef_node->obj = o;
  sdef_node->name = name;
  sdef_node->args = (struct mrb_ast_args *)int_to_node(p->cmdarg_stack);
  sdef_node->locals = local_switch(p);
  sdef_node->body = NULL;
  return (node*)sdef_node;
}

static void
local_add_margs(parser_state *p, node *n)
{
  while (n) {
    if (get_node_type(n->car) == NODE_MARG) {
      struct mrb_ast_masgn_node *masgn_n = (struct mrb_ast_masgn_node*)n->car;
      node *rhs = masgn_n->rhs;

      /* For parameter destructuring, rhs contains the locals */
      if (rhs) {
        node *t = rhs;
        while (t) {
          local_add_f(p, node_to_sym(t->car));
          t = t->cdr;
        }
        /* Clear cons list RHS immediately after use */
        masgn_n->rhs = NULL;
      }

      /* Process nested destructuring in lhs components */
      if (masgn_n->pre) {
        local_add_margs(p, masgn_n->pre);
      }
      if (masgn_n->post) {
        local_add_margs(p, masgn_n->post);
      }
    }
    n = n->cdr;
  }
}


static void
local_add_lv(parser_state *p, node *lv)
{
  while (lv) {
    local_add_f(p, node_to_sym(lv->car));
    lv = lv->cdr;
  }
}

/* (m o r m2 tail) */
/* m: (a b c) */
/* o: ((a . e1) (b . e2)) */
/* r: a */
/* m2: (a b c) */
/* b: a */
static node*
new_args(parser_state *p, node *m, node *opt, mrb_sym rest, node *m2, node *tail)
{
  local_add_margs(p, m);
  local_add_margs(p, m2);

  /* Save original optional arguments before processing */
  node *orig_opt = opt;

  /* Process optional arguments (keep original side effects) */
  while (opt) {
    /* opt: (sym . (opt . lv)) -> (sym . opt) */
    local_add_lv(p, opt->car->cdr->cdr);
    opt->car->cdr = opt->car->cdr->car;
    opt = opt->cdr;
  }

  /* Allocate struct mrb_ast_args (no hdr) */
  struct mrb_ast_args *args = (struct mrb_ast_args*)parser_palloc(p, sizeof(struct mrb_ast_args));

  /* Initialize members */
  args->mandatory_args = m;
  args->optional_args = orig_opt;
  args->rest_arg = rest;
  args->post_mandatory_args = m2;

  /* Deconstruct tail cons list: (kws . (kwrest . blk)) */
  if (tail) {
    args->keyword_args = (node*)tail->car;          /* kws */
    args->kwrest_arg = (mrb_sym)(intptr_t)tail->cdr->car; /* kwrest */
    args->block_arg = (mrb_sym)(intptr_t)tail->cdr->cdr;  /* blk */
    cons_free(tail->cdr);
    cons_free(tail);
  }
  else {
    args->keyword_args = NULL;
    args->kwrest_arg = 0;
    args->block_arg = 0;
  }

  return (node*)args;
}

/* struct: args_tail_node(kwargs, kwrest, block) */
static node*
new_args_tail(parser_state *p, node *kws, mrb_sym kwrest, mrb_sym blk)
{
  node *k;

  if (kwrest) {
    local_add_kw(p, kwrest);
  }

  local_add_blk(p);
  if (blk) local_add_f(p, blk);

  /* allocate register for keywords arguments */
  /* order is for Proc#parameters */
  for (k = kws; k; k = k->cdr) {
    if (!k->car->cdr) { /* allocate required keywords - simplified structure: (key . NULL) */
      local_add_f(p, node_to_sym(k->car->car));
    }
  }
  for (k = kws; k; k = k->cdr) {
    if (k->car->cdr) { /* allocate keywords with default - simplified structure: (key . value) */
      local_add_lv(p, k->car->cdr->cdr);  /* value->cdr for default args */
      k->car->cdr = k->car->cdr->car;    /* value->car for default args */
      local_add_f(p, node_to_sym(k->car->car));
    }
  }

  /* Return cons list: (keyword . (kwrest . blk)) */
  return cons(kws, cons(sym_to_node(kwrest), sym_to_node(blk)));
}

/* (kw_sym . def_arg) - simplified from NODE_KW_ARG wrapper */
static node*
new_kw_arg(parser_state *p, mrb_sym kw, node *def_arg)
{
  mrb_assert(kw);
  return cons(sym_to_node(kw), def_arg);
}

/* (:kw_rest_args . a) */
static node*
new_kw_rest_args(parser_state *p, mrb_sym sym)
{
  return sym_to_node(intern_op(pow));  /* Use ** symbol as direct marker */
}

static node*
new_args_dots(parser_state *p, node *m)
{
  mrb_sym r = intern_op(mul);
  mrb_sym k = intern_op(pow);
  mrb_sym b = intern_op(and);
  local_add_f(p, r);
  return new_args(p, m, 0, r, 0, new_args_tail(p, NULL, k, b));
}

/* struct: block_arg_node(value) */
static node*
new_block_arg(parser_state *p, node *a)
{
  struct mrb_ast_block_arg_node *block_arg_node = NEW_NODE(block_arg, NODE_BLOCK_ARG);
  block_arg_node->value = a;
  return (node*)block_arg_node;
}

static node*
setup_numparams(parser_state *p, node *a)
{
  int nvars = node_to_int(p->nvars->car);
  if (nvars > 0) {
    int i;
    mrb_sym sym;
    // Check if any arguments are already defined
    struct mrb_ast_args *args = (struct mrb_ast_args *)a;
    if (a && (args->mandatory_args || args->optional_args || args->rest_arg ||
              args->post_mandatory_args || args->keyword_args || args->kwrest_arg)) {
      yyerror(NULL, p, "ordinary parameter is defined");
    }
    else if (p->locals) {
      /* p->locals should not be NULL unless error happens before the point */
      node* args = 0;
      for (i = nvars; i > 0; i--) {
        char buf[3];

        buf[0] = '_';
        buf[1] = i+'0';
        buf[2] = '\0';
        sym = intern_cstr(buf);
        args = cons(new_lvar(p, sym), args);
        p->locals->car = cons(sym_to_node(sym), p->locals->car);
      }
      a = new_args(p, args, 0, 0, 0, 0);
    }
  }
  return a;
}

/* struct: block_node(args, body) */
static node*
new_block(parser_state *p, node *a, node *b)
{
  a = setup_numparams(p, a);  struct mrb_ast_block_node *n = NEW_NODE(block, NODE_BLOCK);
  n->locals = locals_node(p);
  n->args = (struct mrb_ast_args *)a;
  n->body = b;

  return (node*)n;
}

/* struct: lambda_node(args, body) */
static node*
new_lambda(parser_state *p, node *a, node *b)
{
  a = setup_numparams(p, a);  struct mrb_ast_lambda_node *lambda_node = NEW_NODE(lambda, NODE_LAMBDA);
  lambda_node->locals = locals_node(p);
  lambda_node->args = (struct mrb_ast_args *)a;
  lambda_node->body = b;
  return (node*)lambda_node;
}

/* struct: asgn_node(lhs, rhs) */
static node*
new_asgn(parser_state *p, node *a, node *b)
{
  void_expr_error(p, b);

  struct mrb_ast_asgn_node *n = NEW_NODE(asgn, NODE_ASGN);
  n->lhs = a;
  n->rhs = b;

  return (node*)n;
}

/* Helper function to create MASGN/MARG nodes */
static node*
new_masgn_helper(parser_state *p, node *a, node *b, enum node_type node_type)
{
  struct mrb_ast_masgn_node *n = NEW_NODE(masgn, node_type);

  /* Extract pre, rest, post from cons list structure (a b c) */
  if (a) {
    n->pre = a->car;  /* Pre-splat variables */
    if (a->cdr) {
      n->rest = a->cdr->car;  /* Splat variable (or -1 for anonymous) */
      if (a->cdr->cdr) {
        n->post = a->cdr->cdr->car;  /* Post-splat variables */
        cons_free(a->cdr->cdr);
      }
      else {
        n->post = NULL;
      }
      cons_free(a->cdr);
    }
    else {
      n->rest = NULL;
      n->post = NULL;
    }
    cons_free(a);
  }
  else {
    n->pre = NULL;
    n->rest = NULL;
    n->post = NULL;
  }
  n->rhs = b;

  return (node*)n;
}

/* struct: masgn_node(lhs, rhs) */
static node*
new_masgn(parser_state *p, node *a, node *b)
{
  void_expr_error(p, b);
  return new_masgn_helper(p, a, b, NODE_MASGN);
}

/* (:marg mlhs mrhs) no check - for parameter destructuring */
static node*
new_marg(parser_state *p, node *a)
{
  return new_masgn_helper(p, a, p->locals->car, NODE_MARG);
}

/* struct: op_asgn_node(lhs, op, rhs) */
static node*
new_op_asgn(parser_state *p, node *a, mrb_sym op, node *b)
{
  void_expr_error(p, b);

  struct mrb_ast_op_asgn_node *n = NEW_NODE(op_asgn, NODE_OP_ASGN);
  n->lhs = a;
  n->op = op;
  n->rhs = b;
  return (node*)n;
}

static node*
new_int_n(parser_state *p, int32_t val)
{
  struct mrb_ast_int_node *n = NEW_NODE(int, NODE_INT);
  n->value = val;

  return (node*)n;
}

static node*
new_imaginary(parser_state *p, node *imaginary)
{
  return new_fcall(p, MRB_SYM_2(p->mrb, Complex),
                   new_callargs(p, list2(new_int_n(p, 0), imaginary), 0, 0));
}

static node*
new_rational(parser_state *p, node *rational)
{
  return new_fcall(p, MRB_SYM_2(p->mrb, Rational), new_callargs(p, list1(rational), 0, 0));
}

/* Read integer into int32_t with overflow detection */
static mrb_bool
read_int32(const char *p, int base, int32_t *result)
{
  const char *e = p + strlen(p);
  int32_t value = 0;
  mrb_bool neg = FALSE;

  if (base < 2 || base > 16) {
    return FALSE;
  }

  if (*p == '+') {
    p++;
  }
  else if (*p == '-') {
    neg = TRUE;
    p++;
  }

  while (p < e) {
    int n;
    char c = *p;

    /* Skip underscores */
    if (c == '_') {
      p++;
      continue;
    }

    /* Parse digit */
    if (c >= '0' && c <= '9') {
      n = c - '0';
    }
    else if (c >= 'a' && c <= 'f') {
      n = c - 'a' + 10;
    }
    else if (c >= 'A' && c <= 'F') {
      n = c - 'A' + 10;
    }
    else {
      /* Invalid character */
      return FALSE;
    }

    if (n >= base) {
      /* Digit not valid for this base */
      return FALSE;
    }

    /* Check for multiplication overflow */
    if (value > INT32_MAX / base) {
      return FALSE;
    }

    value *= base;

    /* Check for addition overflow */
    if (value > INT32_MAX - n) {
      /* Special case: -INT32_MIN is valid */
      if (neg && value == (INT32_MAX - n + 1) && p + 1 == e) {
        *result = INT32_MIN;
        return TRUE;
      }
      return FALSE;
    }

    value += n;
    p++;
  }

  *result = neg ? -value : value;
  return TRUE;
}

static node*
new_int(parser_state *p, const char *s, int base, int suffix)
{
  int32_t val;
  node* result;

  /* Try to parse as int32_t first */
  if (read_int32(s, base, &val)) {
    result = new_int_n(p, val);
  }
  else {
    /* Big integer - create NODE_BIGINT */
    struct mrb_ast_bigint_node *n = NEW_NODE(bigint, NODE_BIGINT);
    n->string = strdup(s);
    n->base = base;

    result = (node*)n;
  }

  /* Handle suffix modifiers */
  if (suffix & NUM_SUFFIX_R) {
    result = new_rational(p, result);
  }
  if (suffix & NUM_SUFFIX_I) {
    result = new_imaginary(p, result);
  }

  return result;
}

#ifndef MRB_NO_FLOAT
/* struct: float_node(value) */
static node*
new_float(parser_state *p, const char *s, int suffix)
{
  struct mrb_ast_float_node *n = NEW_NODE(float, NODE_FLOAT);
  n->value = strdup(s);

  node* result = (node*)n;

  if (suffix & NUM_SUFFIX_R) {
    result = new_rational(p, result);
  }
  if (suffix & NUM_SUFFIX_I) {
    result = new_imaginary(p, result);
  }
  return result;
}
#endif

/* Create string node from cons list */
/* struct: str_node(str) */
static node*
new_str(parser_state *p, node *a)
{
  struct mrb_ast_str_node *n = NEW_NODE(str, NODE_STR);
  n->list = a;

  return (node*)n;
}

/* struct: xstr_node(str) */
static node*
new_xstr(parser_state *p, node *a)
{
  struct mrb_ast_xstr_node *n = NEW_NODE(xstr, NODE_XSTR);
  n->list = a;
  return (node*)n;
}

/* struct: dsym_node(parts) - uses cons list */
static node*
new_dsym(parser_state *p, node *a)
{
  struct mrb_ast_str_node *n = NEW_NODE(str, NODE_DSYM);
  n->list = a;
  return (node*)n;
}

/* struct: regx_node(pattern, flags, encoding) */
static node*
new_regx(parser_state *p, node *list, const char *flags, const char *encoding)
{
  struct mrb_ast_regx_node *n = NEW_NODE(regx, NODE_REGX);
  n->list = list;
  n->flags = flags;
  n->encoding = encoding;
  return (node*)n;
}

/* struct: back_ref_node(n) */
static node*
new_back_ref(parser_state *p, int n)
{
  struct mrb_ast_back_ref_node *backref_node = NEW_NODE(back_ref, NODE_BACK_REF);
  backref_node->type = n;
  return (node*)backref_node;
}

/* struct: nth_ref_node(n) */
static node*
new_nth_ref(parser_state *p, int n)
{
  struct mrb_ast_nth_ref_node *nthref_node = NEW_NODE(nth_ref, NODE_NTH_REF);
  nthref_node->nth = n;
  return (node*)nthref_node;
}

/* struct: heredoc_node(str) */
static node*
new_heredoc(parser_state *p, struct mrb_parser_heredoc_info **infop)
{
  struct mrb_ast_heredoc_node *n = NEW_NODE(heredoc, NODE_HEREDOC);

  /* Initialize embedded heredoc info struct */
  n->info.allow_indent = FALSE;
  n->info.remove_indent = FALSE;
  n->info.line_head = FALSE;
  n->info.indent = 0;
  n->info.indented = NULL;
  n->info.type = str_not_parsing;  // Will be set by heredoc processing
  n->info.term = NULL;  // Will be set by heredoc processing
  n->info.term_len = 0;
  n->info.doc = NULL;

  /* Return pointer to embedded info if requested */
  *infop = &n->info;

  return (node*)n;
}

static void
new_bv(parser_state *p, mrb_sym id)
{
}

static node*
new_literal_delim(parser_state *p)
{
  return cons((node*)0, (node*)0);
}

/* Helper for creating string representation cons (length . string_ptr) */
static node*
new_str_rep(parser_state *p, const char *str, int len)
{
  return cons(int_to_node(len), (node*)strndup(str, len));
}

/* Helper for creating string representation from current token */
static node*
new_str_tok(parser_state *p)
{
  return new_str_rep(p, tok(p), toklen(p));
}

/* Helper for creating empty string representation */
static node*
new_str_empty(parser_state *p)
{
  return new_str_rep(p, "", 0);
}

/* (:words . a) */
static node*
new_words(parser_state *p, node *a)
{
  struct mrb_ast_words_node *words_node = NEW_NODE(words, NODE_WORDS);
  words_node->args = a;
  return (node*)words_node;
}

/* (:symbols . a) */
static node*
new_symbols(parser_state *p, node *a)
{
  struct mrb_ast_symbols_node *symbols_node = NEW_NODE(symbols, NODE_SYMBOLS);
  symbols_node->args = a;
  return (node*)symbols_node;
}

/* xxx ----------------------------- */

/* (:call a op) */
static node*
call_uni_op(parser_state *p, node *recv, const char *m)
{
  void_expr_error(p, recv);
  return new_call(p, recv, intern_cstr(m), 0, '.');
}

/* (:call a op b) */
static node*
call_bin_op(parser_state *p, node *recv, const char *m, node *arg1)
{
  return new_call(p, recv, intern_cstr(m), new_callargs(p, list1(arg1), 0, 0), '.');
}

static void
args_with_block(parser_state *p, node *a, node *b)
{
  if (b) {
    /* Handle callargs structure - direct casting like new_args() */
    struct mrb_ast_callargs *callargs = (struct mrb_ast_callargs*)a;
    if (callargs->block_arg) {
      yyerror(NULL, p, "both block arg and actual block given");
    }
    callargs->block_arg = b;
  }
}

static void
endless_method_name(parser_state *p, node *defn)
{
  struct mrb_ast_def_node *def = (struct mrb_ast_def_node*)defn;
  mrb_sym sym = def->name;
  mrb_int len;
  const char *name = mrb_sym_name_len(p->mrb, sym, &len);

  if (len > 1 && name[len-1] == '=') {
    for (int i=0; i<len-1; i++) {
      if (!identchar(name[i])) return;
    }
    yyerror(NULL, p, "setter method cannot be defined by endless method definition");
  }
}

static void
call_with_block(parser_state *p, node *a, node *b)
{
  if (!a) return;

  /* Handle direct variable-sized nodes */
  struct mrb_ast_var_header *header = (struct mrb_ast_var_header*)a;

  enum node_type var_type = (enum node_type)header->node_type;
  switch (var_type) {
  case NODE_SUPER:
  case NODE_ZSUPER:
    /* For variable-sized super/zsuper nodes, update the args field directly */
    {
      struct mrb_ast_super_node *super_n = super_node(a);
      if (!super_n->args) {
        super_n->args = new_callargs(p, 0, 0, b);
      }
      else {
        args_with_block(p, super_n->args, b);
      }
    }
    break;
  case NODE_YIELD:
    /* Variable-sized yield nodes should generate an error when given a block */
    yyerror(NULL, p, "block given to yield");
    break;
  case NODE_RETURN:
    /* Variable-sized return nodes - recursively call with args */
    {
      struct mrb_ast_return_node *return_n = return_node(a);
      if (return_n->args != NULL) {
        call_with_block(p, return_n->args, b);
      }
    }
    break;
  case NODE_BREAK:
    /* Variable-sized break nodes - recursively call with value */
    {
      struct mrb_ast_break_node *break_n = (struct mrb_ast_break_node*)a;
      if (break_n->value != NULL) {
        call_with_block(p, break_n->value, b);
      }
    }
    break;
  case NODE_NEXT:
    /* Variable-sized next nodes - recursively call with value */
    {
      struct mrb_ast_next_node *next_n = (struct mrb_ast_next_node*)a;
      if (next_n->value != NULL) {
        call_with_block(p, next_n->value, b);
      }
    }
    break;
  case NODE_CALL:
    /* Variable-sized call nodes - add block to existing args */
    {
      struct mrb_ast_call_node *call = call_node(a);

      if (call->args && callargs_node(call->args)->block_arg) {
        yyerror(NULL, p, "both block arg and actual block given");
        return;
      }

      /* Use existing args and add block */
      if (call->args) {
        /* Modify existing callargs structure to add block */
        args_with_block(p, call->args, b);
      }
      else {
        /* Create new callargs with just the block */
        call->args = new_callargs(p, NULL, NULL, b);
      }
    }
    break;
  default:
    /* For other variable-sized nodes, do nothing */
    break;
  }
}

static node*
new_negate(parser_state *p, node *n)
{
  struct mrb_ast_negate_node *negate_node = NEW_NODE(negate, NODE_NEGATE);
  negate_node->operand = n;
  return (node*)negate_node;
}

static node*
cond(node *n)
{
  return n;
}

static node*
ret_args(parser_state *p, node *n)
{
  /* Handle callargs structure - direct casting like new_args() */
  struct mrb_ast_callargs *callargs = (struct mrb_ast_callargs*)n;
  if (callargs->block_arg) {
    yyerror(NULL, p, "block argument should not be given");
    return NULL;
  }
  if (!callargs->regular_args) return NULL;
  if (!callargs->regular_args->cdr) return callargs->regular_args->car;
  return new_array(p, callargs->regular_args);
}

static void
assignable(parser_state *p, node *lhs)
{
  switch (get_node_type(lhs)) {
  case NODE_LVAR:
    local_add(p, var_node(lhs)->symbol);
    break;
  case NODE_CONST:
    if (p->in_def)
      yyerror(NULL, p, "dynamic constant assignment");
    break;
  default:
    /* Other node types don't need special handling in assignable */
    break;
  }
}

static node*
var_reference(parser_state *p, node *lhs)
{
  /* Check if this is a variable-sized node */
  if (node_type_p(lhs, NODE_LVAR)) {
    mrb_sym sym = var_node(lhs)->symbol;
    if (!local_var_p(p, sym)) {
      node *n = new_fcall(p, sym, 0);
      /* Don't free variable-sized nodes - they're managed by the parser allocator */
      return n;
    }
  }
  return lhs;
}

static node*
label_reference(parser_state *p, mrb_sym sym)
{
  const char *name = mrb_sym_name(p->mrb, sym);

  if (local_var_p(p, sym)) {
    return new_lvar(p, sym);
  }
  else if (ISUPPER(name[0])) {
    return new_const(p, sym);
  }
  else {
    return new_fcall(p, sym, 0);
  }
}

typedef enum mrb_string_type  string_type;

typedef struct parser_lex_strterm {
  int type;
  int level;
  int term;
  int paren;
  struct parser_lex_strterm *prev;
} parser_lex_strterm;

static parser_lex_strterm*
new_strterm(parser_state *p, string_type type, int term, int paren)
{
  parser_lex_strterm *lex = (parser_lex_strterm*)parser_palloc(p, sizeof(parser_lex_strterm));
  lex->type = type;
  lex->level = 0;
  lex->term = term;
  lex->paren = paren;
  lex->prev = p->lex_strterm;
  return lex;
}

static void
end_strterm(parser_state *p)
{
  parser_lex_strterm *term = p->lex_strterm->prev;
  parser_pfree(p->lex_strterm);
  p->lex_strterm = term;
}

static node*
push_strterm(parser_state *p)
{
  node *n = cons((node*)p->lex_strterm, p->parsing_heredoc);
  p->lex_strterm = NULL;
  return n;
}

static void
pop_strterm(parser_state *p, node *n)
{
  p->lex_strterm = (parser_lex_strterm*)n->car;
  p->parsing_heredoc = n->cdr;
  cons_free(n);
}

static parser_heredoc_info *
parsing_heredoc_info(parser_state *p)
{
  node *nd = p->parsing_heredoc;
  if (nd == NULL) return NULL;
  /* mrb_assert(nd->car->car == NODE_HEREDOC); */
  if (get_node_type(nd->car) == NODE_HEREDOC) {
    /* Variable-sized heredoc node - return address of embedded info struct */
    struct mrb_ast_heredoc_node *heredoc = (struct mrb_ast_heredoc_node*)nd->car;
    return &heredoc->info;
  }
  return (parser_heredoc_info*)nd->car->cdr;
}

static void
heredoc_treat_nextline(parser_state *p)
{
  if (p->heredocs_from_nextline == NULL) return;
  if (p->parsing_heredoc && p->lex_strterm) {
    append(p->heredocs_from_nextline, p->parsing_heredoc);
  }
  p->parsing_heredoc = p->heredocs_from_nextline;
  p->lex_strterm = new_strterm(p, parsing_heredoc_info(p)->type, 0, 0);
  p->heredocs_from_nextline = NULL;
}

static void
heredoc_end(parser_state *p)
{
  p->parsing_heredoc = p->parsing_heredoc->cdr;
  if (p->parsing_heredoc == NULL) {
    p->lstate = EXPR_BEG;
    end_strterm(p);
  }
  else {
    /* next heredoc */
    p->lex_strterm->type = parsing_heredoc_info(p)->type;
  }
}
#define is_strterm_type(p,str_func) ((p)->lex_strterm->type & (str_func))

static void
prohibit_literals(parser_state *p, node *n)
{
  if (n == 0) {
    yyerror(NULL, p, "can't define singleton method for ().");
  }
  else {
    enum node_type nt = get_node_type(n);
    switch (nt) {
    case NODE_INT:
    case NODE_STR:
    case NODE_XSTR:
    case NODE_REGX:
    case NODE_FLOAT:
    case NODE_ARRAY:
    case NODE_HEREDOC:
      yyerror(NULL, p, "can't define singleton method for literals");
    default:
      break;
    }
  }
}

/* xxx ----------------------------- */


#line 1932 "mrbgems/mruby-compiler/core/y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG && !defined(yydebug)
extern int yydebug;
#endif


/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    keyword_class = 258,           /* "'class'"  */
    keyword_module = 259,          /* "'module'"  */
    keyword_def = 260,             /* "'def'"  */
    keyword_begin = 261,           /* "'begin'"  */
    keyword_if = 262,              /* "'if'"  */
    keyword_unless = 263,          /* "'unless'"  */
    keyword_while = 264,           /* "'while'"  */
    keyword_until = 265,           /* "'until'"  */
    keyword_for = 266,             /* "'for'"  */
    keyword_undef = 267,           /* "'undef'"  */
    keyword_rescue = 268,          /* "'rescue'"  */
    keyword_ensure = 269,          /* "'ensure'"  */
    keyword_end = 270,             /* "'end'"  */
    keyword_then = 271,            /* "'then'"  */
    keyword_elsif = 272,           /* "'elsif'"  */
    keyword_else = 273,            /* "'else'"  */
    keyword_case = 274,            /* "'case'"  */
    keyword_when = 275,            /* "'when'"  */
    keyword_break = 276,           /* "'break'"  */
    keyword_next = 277,            /* "'next'"  */
    keyword_redo = 278,            /* "'redo'"  */
    keyword_retry = 279,           /* "'retry'"  */
    keyword_in = 280,              /* "'in'"  */
    keyword_do = 281,              /* "'do'"  */
    keyword_do_cond = 282,         /* "'do' for condition"  */
    keyword_do_block = 283,        /* "'do' for block"  */
    keyword_do_LAMBDA = 284,       /* "'do' for lambda"  */
    keyword_return = 285,          /* "'return'"  */
    keyword_yield = 286,           /* "'yield'"  */
    keyword_super = 287,           /* "'super'"  */
    keyword_self = 288,            /* "'self'"  */
    keyword_nil = 289,             /* "'nil'"  */
    keyword_true = 290,            /* "'true'"  */
    keyword_false = 291,           /* "'false'"  */
    keyword_and = 292,             /* "'and'"  */
    keyword_or = 293,              /* "'or'"  */
    keyword_not = 294,             /* "'not'"  */
    modifier_if = 295,             /* "'if' modifier"  */
    modifier_unless = 296,         /* "'unless' modifier"  */
    modifier_while = 297,          /* "'while' modifier"  */
    modifier_until = 298,          /* "'until' modifier"  */
    modifier_rescue = 299,         /* "'rescue' modifier"  */
    keyword_alias = 300,           /* "'alias'"  */
    keyword_BEGIN = 301,           /* "'BEGIN'"  */
    keyword_END = 302,             /* "'END'"  */
    keyword__LINE__ = 303,         /* "'__LINE__'"  */
    keyword__FILE__ = 304,         /* "'__FILE__'"  */
    keyword__ENCODING__ = 305,     /* "'__ENCODING__'"  */
    keyword_defined = 306,         /* "'defined?'"  */
    tIDENTIFIER = 307,             /* "local variable or method"  */
    tFID = 308,                    /* "method"  */
    tGVAR = 309,                   /* "global variable"  */
    tIVAR = 310,                   /* "instance variable"  */
    tCONSTANT = 311,               /* "constant"  */
    tCVAR = 312,                   /* "class variable"  */
    tLABEL_TAG = 313,              /* "label"  */
    tINTEGER = 314,                /* "integer literal"  */
    tFLOAT = 315,                  /* "float literal"  */
    tCHAR = 316,                   /* "character literal"  */
    tXSTRING = 317,                /* tXSTRING  */
    tREGEXP = 318,                 /* tREGEXP  */
    tSTRING = 319,                 /* tSTRING  */
    tSTRING_PART = 320,            /* tSTRING_PART  */
    tSTRING_MID = 321,             /* tSTRING_MID  */
    tNTH_REF = 322,                /* tNTH_REF  */
    tBACK_REF = 323,               /* tBACK_REF  */
    tREGEXP_END = 324,             /* tREGEXP_END  */
    tNUMPARAM = 325,               /* "numbered parameter"  */
    tUPLUS = 326,                  /* "unary plus"  */
    tUMINUS = 327,                 /* "unary minus"  */
    tCMP = 328,                    /* "<=>"  */
    tEQ = 329,                     /* "=="  */
    tEQQ = 330,                    /* "==="  */
    tNEQ = 331,                    /* "!="  */
    tGEQ = 332,                    /* ">="  */
    tLEQ = 333,                    /* "<="  */
    tANDOP = 334,                  /* "&&"  */
    tOROP = 335,                   /* "||"  */
    tMATCH = 336,                  /* "=~"  */
    tNMATCH = 337,                 /* "!~"  */
    tDOT2 = 338,                   /* ".."  */
    tDOT3 = 339,                   /* "..."  */
    tBDOT2 = 340,                  /* tBDOT2  */
    tBDOT3 = 341,                  /* tBDOT3  */
    tAREF = 342,                   /* tAREF  */
    tASET = 343,                   /* tASET  */
    tLSHFT = 344,                  /* "<<"  */
    tRSHFT = 345,                  /* ">>"  */
    tCOLON2 = 346,                 /* "::"  */
    tCOLON3 = 347,                 /* tCOLON3  */
    tOP_ASGN = 348,                /* tOP_ASGN  */
    tASSOC = 349,                  /* "=>"  */
    tLPAREN = 350,                 /* tLPAREN  */
    tLPAREN_ARG = 351,             /* "("  */
    tRPAREN = 352,                 /* ")"  */
    tLBRACK = 353,                 /* "["  */
    tLBRACE = 354,                 /* tLBRACE  */
    tLBRACE_ARG = 355,             /* "{"  */
    tSTAR = 356,                   /* "*"  */
    tPOW = 357,                    /* tPOW  */
    tDSTAR = 358,                  /* "**"  */
    tAMPER = 359,                  /* "&"  */
    tLAMBDA = 360,                 /* "->"  */
    tANDDOT = 361,                 /* "&."  */
    tSYMBEG = 362,                 /* "symbol"  */
    tSTRING_BEG = 363,             /* "string literal"  */
    tXSTRING_BEG = 364,            /* tXSTRING_BEG  */
    tSTRING_DVAR = 365,            /* tSTRING_DVAR  */
    tREGEXP_BEG = 366,             /* tREGEXP_BEG  */
    tWORDS_BEG = 367,              /* tWORDS_BEG  */
    tSYMBOLS_BEG = 368,            /* tSYMBOLS_BEG  */
    tLAMBEG = 369,                 /* tLAMBEG  */
    tHEREDOC_BEG = 370,            /* "here document"  */
    tHEREDOC_END = 371,            /* tHEREDOC_END  */
    tLITERAL_DELIM = 372,          /* tLITERAL_DELIM  */
    tHD_LITERAL_DELIM = 373,       /* tHD_LITERAL_DELIM  */
    tHD_STRING_PART = 374,         /* tHD_STRING_PART  */
    tHD_STRING_MID = 375,          /* tHD_STRING_MID  */
    tLOWEST = 376,                 /* tLOWEST  */
    tUMINUS_NUM = 377,             /* tUMINUS_NUM  */
    tLAST_TOKEN = 378              /* tLAST_TOKEN  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 1875 "mrbgems/mruby-compiler/core/parse.y"

    node *nd;
    mrb_sym id;
    int num;
    stack_type stack;
    const struct vtable *vars;

#line 2112 "mrbgems/mruby-compiler/core/y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif




int yyparse (parser_state *p);




/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_keyword_class = 3,              /* "'class'"  */
  YYSYMBOL_keyword_module = 4,             /* "'module'"  */
  YYSYMBOL_keyword_def = 5,                /* "'def'"  */
  YYSYMBOL_keyword_begin = 6,              /* "'begin'"  */
  YYSYMBOL_keyword_if = 7,                 /* "'if'"  */
  YYSYMBOL_keyword_unless = 8,             /* "'unless'"  */
  YYSYMBOL_keyword_while = 9,              /* "'while'"  */
  YYSYMBOL_keyword_until = 10,             /* "'until'"  */
  YYSYMBOL_keyword_for = 11,               /* "'for'"  */
  YYSYMBOL_keyword_undef = 12,             /* "'undef'"  */
  YYSYMBOL_keyword_rescue = 13,            /* "'rescue'"  */
  YYSYMBOL_keyword_ensure = 14,            /* "'ensure'"  */
  YYSYMBOL_keyword_end = 15,               /* "'end'"  */
  YYSYMBOL_keyword_then = 16,              /* "'then'"  */
  YYSYMBOL_keyword_elsif = 17,             /* "'elsif'"  */
  YYSYMBOL_keyword_else = 18,              /* "'else'"  */
  YYSYMBOL_keyword_case = 19,              /* "'case'"  */
  YYSYMBOL_keyword_when = 20,              /* "'when'"  */
  YYSYMBOL_keyword_break = 21,             /* "'break'"  */
  YYSYMBOL_keyword_next = 22,              /* "'next'"  */
  YYSYMBOL_keyword_redo = 23,              /* "'redo'"  */
  YYSYMBOL_keyword_retry = 24,             /* "'retry'"  */
  YYSYMBOL_keyword_in = 25,                /* "'in'"  */
  YYSYMBOL_keyword_do = 26,                /* "'do'"  */
  YYSYMBOL_keyword_do_cond = 27,           /* "'do' for condition"  */
  YYSYMBOL_keyword_do_block = 28,          /* "'do' for block"  */
  YYSYMBOL_keyword_do_LAMBDA = 29,         /* "'do' for lambda"  */
  YYSYMBOL_keyword_return = 30,            /* "'return'"  */
  YYSYMBOL_keyword_yield = 31,             /* "'yield'"  */
  YYSYMBOL_keyword_super = 32,             /* "'super'"  */
  YYSYMBOL_keyword_self = 33,              /* "'self'"  */
  YYSYMBOL_keyword_nil = 34,               /* "'nil'"  */
  YYSYMBOL_keyword_true = 35,              /* "'true'"  */
  YYSYMBOL_keyword_false = 36,             /* "'false'"  */
  YYSYMBOL_keyword_and = 37,               /* "'and'"  */
  YYSYMBOL_keyword_or = 38,                /* "'or'"  */
  YYSYMBOL_keyword_not = 39,               /* "'not'"  */
  YYSYMBOL_modifier_if = 40,               /* "'if' modifier"  */
  YYSYMBOL_modifier_unless = 41,           /* "'unless' modifier"  */
  YYSYMBOL_modifier_while = 42,            /* "'while' modifier"  */
  YYSYMBOL_modifier_until = 43,            /* "'until' modifier"  */
  YYSYMBOL_modifier_rescue = 44,           /* "'rescue' modifier"  */
  YYSYMBOL_keyword_alias = 45,             /* "'alias'"  */
  YYSYMBOL_keyword_BEGIN = 46,             /* "'BEGIN'"  */
  YYSYMBOL_keyword_END = 47,               /* "'END'"  */
  YYSYMBOL_keyword__LINE__ = 48,           /* "'__LINE__'"  */
  YYSYMBOL_keyword__FILE__ = 49,           /* "'__FILE__'"  */
  YYSYMBOL_keyword__ENCODING__ = 50,       /* "'__ENCODING__'"  */
  YYSYMBOL_keyword_defined = 51,           /* "'defined?'"  */
  YYSYMBOL_tIDENTIFIER = 52,               /* "local variable or method"  */
  YYSYMBOL_tFID = 53,                      /* "method"  */
  YYSYMBOL_tGVAR = 54,                     /* "global variable"  */
  YYSYMBOL_tIVAR = 55,                     /* "instance variable"  */
  YYSYMBOL_tCONSTANT = 56,                 /* "constant"  */
  YYSYMBOL_tCVAR = 57,                     /* "class variable"  */
  YYSYMBOL_tLABEL_TAG = 58,                /* "label"  */
  YYSYMBOL_tINTEGER = 59,                  /* "integer literal"  */
  YYSYMBOL_tFLOAT = 60,                    /* "float literal"  */
  YYSYMBOL_tCHAR = 61,                     /* "character literal"  */
  YYSYMBOL_tXSTRING = 62,                  /* tXSTRING  */
  YYSYMBOL_tREGEXP = 63,                   /* tREGEXP  */
  YYSYMBOL_tSTRING = 64,                   /* tSTRING  */
  YYSYMBOL_tSTRING_PART = 65,              /* tSTRING_PART  */
  YYSYMBOL_tSTRING_MID = 66,               /* tSTRING_MID  */
  YYSYMBOL_tNTH_REF = 67,                  /* tNTH_REF  */
  YYSYMBOL_tBACK_REF = 68,                 /* tBACK_REF  */
  YYSYMBOL_tREGEXP_END = 69,               /* tREGEXP_END  */
  YYSYMBOL_tNUMPARAM = 70,                 /* "numbered parameter"  */
  YYSYMBOL_tUPLUS = 71,                    /* "unary plus"  */
  YYSYMBOL_tUMINUS = 72,                   /* "unary minus"  */
  YYSYMBOL_tCMP = 73,                      /* "<=>"  */
  YYSYMBOL_tEQ = 74,                       /* "=="  */
  YYSYMBOL_tEQQ = 75,                      /* "==="  */
  YYSYMBOL_tNEQ = 76,                      /* "!="  */
  YYSYMBOL_tGEQ = 77,                      /* ">="  */
  YYSYMBOL_tLEQ = 78,                      /* "<="  */
  YYSYMBOL_tANDOP = 79,                    /* "&&"  */
  YYSYMBOL_tOROP = 80,                     /* "||"  */
  YYSYMBOL_tMATCH = 81,                    /* "=~"  */
  YYSYMBOL_tNMATCH = 82,                   /* "!~"  */
  YYSYMBOL_tDOT2 = 83,                     /* ".."  */
  YYSYMBOL_tDOT3 = 84,                     /* "..."  */
  YYSYMBOL_tBDOT2 = 85,                    /* tBDOT2  */
  YYSYMBOL_tBDOT3 = 86,                    /* tBDOT3  */
  YYSYMBOL_tAREF = 87,                     /* tAREF  */
  YYSYMBOL_tASET = 88,                     /* tASET  */
  YYSYMBOL_tLSHFT = 89,                    /* "<<"  */
  YYSYMBOL_tRSHFT = 90,                    /* ">>"  */
  YYSYMBOL_tCOLON2 = 91,                   /* "::"  */
  YYSYMBOL_tCOLON3 = 92,                   /* tCOLON3  */
  YYSYMBOL_tOP_ASGN = 93,                  /* tOP_ASGN  */
  YYSYMBOL_tASSOC = 94,                    /* "=>"  */
  YYSYMBOL_tLPAREN = 95,                   /* tLPAREN  */
  YYSYMBOL_tLPAREN_ARG = 96,               /* "("  */
  YYSYMBOL_tRPAREN = 97,                   /* ")"  */
  YYSYMBOL_tLBRACK = 98,                   /* "["  */
  YYSYMBOL_tLBRACE = 99,                   /* tLBRACE  */
  YYSYMBOL_tLBRACE_ARG = 100,              /* "{"  */
  YYSYMBOL_tSTAR = 101,                    /* "*"  */
  YYSYMBOL_tPOW = 102,                     /* tPOW  */
  YYSYMBOL_tDSTAR = 103,                   /* "**"  */
  YYSYMBOL_tAMPER = 104,                   /* "&"  */
  YYSYMBOL_tLAMBDA = 105,                  /* "->"  */
  YYSYMBOL_tANDDOT = 106,                  /* "&."  */
  YYSYMBOL_tSYMBEG = 107,                  /* "symbol"  */
  YYSYMBOL_tSTRING_BEG = 108,              /* "string literal"  */
  YYSYMBOL_tXSTRING_BEG = 109,             /* tXSTRING_BEG  */
  YYSYMBOL_tSTRING_DVAR = 110,             /* tSTRING_DVAR  */
  YYSYMBOL_tREGEXP_BEG = 111,              /* tREGEXP_BEG  */
  YYSYMBOL_tWORDS_BEG = 112,               /* tWORDS_BEG  */
  YYSYMBOL_tSYMBOLS_BEG = 113,             /* tSYMBOLS_BEG  */
  YYSYMBOL_tLAMBEG = 114,                  /* tLAMBEG  */
  YYSYMBOL_tHEREDOC_BEG = 115,             /* "here document"  */
  YYSYMBOL_tHEREDOC_END = 116,             /* tHEREDOC_END  */
  YYSYMBOL_tLITERAL_DELIM = 117,           /* tLITERAL_DELIM  */
  YYSYMBOL_tHD_LITERAL_DELIM = 118,        /* tHD_LITERAL_DELIM  */
  YYSYMBOL_tHD_STRING_PART = 119,          /* tHD_STRING_PART  */
  YYSYMBOL_tHD_STRING_MID = 120,           /* tHD_STRING_MID  */
  YYSYMBOL_tLOWEST = 121,                  /* tLOWEST  */
  YYSYMBOL_122_ = 122,                     /* '='  */
  YYSYMBOL_123_ = 123,                     /* '?'  */
  YYSYMBOL_124_ = 124,                     /* ':'  */
  YYSYMBOL_125_ = 125,                     /* '>'  */
  YYSYMBOL_126_ = 126,                     /* '<'  */
  YYSYMBOL_127_ = 127,                     /* '|'  */
  YYSYMBOL_128_ = 128,                     /* '^'  */
  YYSYMBOL_129_ = 129,                     /* '&'  */
  YYSYMBOL_130_ = 130,                     /* '+'  */
  YYSYMBOL_131_ = 131,                     /* '-'  */
  YYSYMBOL_132_ = 132,                     /* '*'  */
  YYSYMBOL_133_ = 133,                     /* '/'  */
  YYSYMBOL_134_ = 134,                     /* '%'  */
  YYSYMBOL_tUMINUS_NUM = 135,              /* tUMINUS_NUM  */
  YYSYMBOL_136_ = 136,                     /* '!'  */
  YYSYMBOL_137_ = 137,                     /* '~'  */
  YYSYMBOL_tLAST_TOKEN = 138,              /* tLAST_TOKEN  */
  YYSYMBOL_139_ = 139,                     /* '{'  */
  YYSYMBOL_140_ = 140,                     /* '}'  */
  YYSYMBOL_141_ = 141,                     /* '['  */
  YYSYMBOL_142_ = 142,                     /* ']'  */
  YYSYMBOL_143_ = 143,                     /* '('  */
  YYSYMBOL_144_ = 144,                     /* ')'  */
  YYSYMBOL_145_ = 145,                     /* ','  */
  YYSYMBOL_146_ = 146,                     /* '`'  */
  YYSYMBOL_147_ = 147,                     /* ';'  */
  YYSYMBOL_148_ = 148,                     /* '.'  */
  YYSYMBOL_149_n_ = 149,                   /* '\n'  */
  YYSYMBOL_YYACCEPT = 150,                 /* $accept  */
  YYSYMBOL_151_1 = 151,                    /* $@1  */
  YYSYMBOL_program = 152,                  /* program  */
  YYSYMBOL_top_compstmt = 153,             /* top_compstmt  */
  YYSYMBOL_top_stmts = 154,                /* top_stmts  */
  YYSYMBOL_top_stmt = 155,                 /* top_stmt  */
  YYSYMBOL_156_2 = 156,                    /* @2  */
  YYSYMBOL_bodystmt = 157,                 /* bodystmt  */
  YYSYMBOL_compstmt = 158,                 /* compstmt  */
  YYSYMBOL_stmts = 159,                    /* stmts  */
  YYSYMBOL_160_3 = 160,                    /* $@3  */
  YYSYMBOL_stmt = 161,                     /* stmt  */
  YYSYMBOL_command_asgn = 162,             /* command_asgn  */
  YYSYMBOL_command_rhs = 163,              /* command_rhs  */
  YYSYMBOL_expr = 164,                     /* expr  */
  YYSYMBOL_defined_with_parens = 165,      /* defined_with_parens  */
  YYSYMBOL_defined_without_parens = 166,   /* defined_without_parens  */
  YYSYMBOL_defined_expression = 167,       /* defined_expression  */
  YYSYMBOL_defn_head = 168,                /* defn_head  */
  YYSYMBOL_169_4 = 169,                    /* $@4  */
  YYSYMBOL_defs_head = 170,                /* defs_head  */
  YYSYMBOL_expr_value = 171,               /* expr_value  */
  YYSYMBOL_command_call = 172,             /* command_call  */
  YYSYMBOL_block_command = 173,            /* block_command  */
  YYSYMBOL_174_5 = 174,                    /* $@5  */
  YYSYMBOL_cmd_brace_block = 175,          /* cmd_brace_block  */
  YYSYMBOL_command = 176,                  /* command  */
  YYSYMBOL_mlhs = 177,                     /* mlhs  */
  YYSYMBOL_mlhs_inner = 178,               /* mlhs_inner  */
  YYSYMBOL_mlhs_basic = 179,               /* mlhs_basic  */
  YYSYMBOL_mlhs_item = 180,                /* mlhs_item  */
  YYSYMBOL_mlhs_list = 181,                /* mlhs_list  */
  YYSYMBOL_mlhs_post = 182,                /* mlhs_post  */
  YYSYMBOL_mlhs_node = 183,                /* mlhs_node  */
  YYSYMBOL_lhs = 184,                      /* lhs  */
  YYSYMBOL_cname = 185,                    /* cname  */
  YYSYMBOL_cpath = 186,                    /* cpath  */
  YYSYMBOL_fname = 187,                    /* fname  */
  YYSYMBOL_fsym = 188,                     /* fsym  */
  YYSYMBOL_undef_list = 189,               /* undef_list  */
  YYSYMBOL_190_6 = 190,                    /* $@6  */
  YYSYMBOL_op = 191,                       /* op  */
  YYSYMBOL_reswords = 192,                 /* reswords  */
  YYSYMBOL_arg = 193,                      /* arg  */
  YYSYMBOL_aref_args = 194,                /* aref_args  */
  YYSYMBOL_arg_rhs = 195,                  /* arg_rhs  */
  YYSYMBOL_paren_args = 196,               /* paren_args  */
  YYSYMBOL_opt_paren_args = 197,           /* opt_paren_args  */
  YYSYMBOL_opt_call_args = 198,            /* opt_call_args  */
  YYSYMBOL_call_args = 199,                /* call_args  */
  YYSYMBOL_200_7 = 200,                    /* @7  */
  YYSYMBOL_command_args = 201,             /* command_args  */
  YYSYMBOL_block_arg = 202,                /* block_arg  */
  YYSYMBOL_opt_block_arg = 203,            /* opt_block_arg  */
  YYSYMBOL_comma = 204,                    /* comma  */
  YYSYMBOL_args = 205,                     /* args  */
  YYSYMBOL_mrhs = 206,                     /* mrhs  */
  YYSYMBOL_primary = 207,                  /* primary  */
  YYSYMBOL_208_8 = 208,                    /* @8  */
  YYSYMBOL_209_9 = 209,                    /* @9  */
  YYSYMBOL_210_10 = 210,                   /* $@10  */
  YYSYMBOL_211_11 = 211,                   /* $@11  */
  YYSYMBOL_212_12 = 212,                   /* @12  */
  YYSYMBOL_213_13 = 213,                   /* @13  */
  YYSYMBOL_214_14 = 214,                   /* $@14  */
  YYSYMBOL_215_15 = 215,                   /* $@15  */
  YYSYMBOL_216_16 = 216,                   /* $@16  */
  YYSYMBOL_217_17 = 217,                   /* $@17  */
  YYSYMBOL_218_18 = 218,                   /* $@18  */
  YYSYMBOL_219_19 = 219,                   /* $@19  */
  YYSYMBOL_220_20 = 220,                   /* @20  */
  YYSYMBOL_221_21 = 221,                   /* @21  */
  YYSYMBOL_222_22 = 222,                   /* @22  */
  YYSYMBOL_223_23 = 223,                   /* @23  */
  YYSYMBOL_primary_value = 224,            /* primary_value  */
  YYSYMBOL_then = 225,                     /* then  */
  YYSYMBOL_do = 226,                       /* do  */
  YYSYMBOL_if_tail = 227,                  /* if_tail  */
  YYSYMBOL_opt_else = 228,                 /* opt_else  */
  YYSYMBOL_for_var = 229,                  /* for_var  */
  YYSYMBOL_f_margs = 230,                  /* f_margs  */
  YYSYMBOL_231_24 = 231,                   /* $@24  */
  YYSYMBOL_block_args_tail = 232,          /* block_args_tail  */
  YYSYMBOL_opt_block_args_tail = 233,      /* opt_block_args_tail  */
  YYSYMBOL_block_param = 234,              /* block_param  */
  YYSYMBOL_opt_block_param = 235,          /* opt_block_param  */
  YYSYMBOL_236_25 = 236,                   /* $@25  */
  YYSYMBOL_block_param_def = 237,          /* block_param_def  */
  YYSYMBOL_opt_bv_decl = 238,              /* opt_bv_decl  */
  YYSYMBOL_bv_decls = 239,                 /* bv_decls  */
  YYSYMBOL_bvar = 240,                     /* bvar  */
  YYSYMBOL_f_larglist = 241,               /* f_larglist  */
  YYSYMBOL_lambda_body = 242,              /* lambda_body  */
  YYSYMBOL_243_26 = 243,                   /* @26  */
  YYSYMBOL_do_block = 244,                 /* do_block  */
  YYSYMBOL_block_call = 245,               /* block_call  */
  YYSYMBOL_method_call = 246,              /* method_call  */
  YYSYMBOL_247_27 = 247,                   /* @27  */
  YYSYMBOL_brace_block = 248,              /* brace_block  */
  YYSYMBOL_249_28 = 249,                   /* @28  */
  YYSYMBOL_case_body = 250,                /* case_body  */
  YYSYMBOL_cases = 251,                    /* cases  */
  YYSYMBOL_opt_rescue = 252,               /* opt_rescue  */
  YYSYMBOL_exc_list = 253,                 /* exc_list  */
  YYSYMBOL_exc_var = 254,                  /* exc_var  */
  YYSYMBOL_opt_ensure = 255,               /* opt_ensure  */
  YYSYMBOL_literal = 256,                  /* literal  */
  YYSYMBOL_string = 257,                   /* string  */
  YYSYMBOL_string_fragment = 258,          /* string_fragment  */
  YYSYMBOL_string_rep = 259,               /* string_rep  */
  YYSYMBOL_string_interp = 260,            /* string_interp  */
  YYSYMBOL_261_29 = 261,                   /* @29  */
  YYSYMBOL_xstring = 262,                  /* xstring  */
  YYSYMBOL_regexp = 263,                   /* regexp  */
  YYSYMBOL_heredoc = 264,                  /* heredoc  */
  YYSYMBOL_heredoc_bodies = 265,           /* heredoc_bodies  */
  YYSYMBOL_heredoc_body = 266,             /* heredoc_body  */
  YYSYMBOL_heredoc_string_rep = 267,       /* heredoc_string_rep  */
  YYSYMBOL_heredoc_string_interp = 268,    /* heredoc_string_interp  */
  YYSYMBOL_269_30 = 269,                   /* @30  */
  YYSYMBOL_words = 270,                    /* words  */
  YYSYMBOL_symbol = 271,                   /* symbol  */
  YYSYMBOL_basic_symbol = 272,             /* basic_symbol  */
  YYSYMBOL_sym = 273,                      /* sym  */
  YYSYMBOL_symbols = 274,                  /* symbols  */
  YYSYMBOL_numeric = 275,                  /* numeric  */
  YYSYMBOL_variable = 276,                 /* variable  */
  YYSYMBOL_var_lhs = 277,                  /* var_lhs  */
  YYSYMBOL_var_ref = 278,                  /* var_ref  */
  YYSYMBOL_backref = 279,                  /* backref  */
  YYSYMBOL_superclass = 280,               /* superclass  */
  YYSYMBOL_281_31 = 281,                   /* $@31  */
  YYSYMBOL_f_opt_arglist_paren = 282,      /* f_opt_arglist_paren  */
  YYSYMBOL_f_arglist_paren = 283,          /* f_arglist_paren  */
  YYSYMBOL_f_arglist = 284,                /* f_arglist  */
  YYSYMBOL_f_label = 285,                  /* f_label  */
  YYSYMBOL_f_kw = 286,                     /* f_kw  */
  YYSYMBOL_f_block_kw = 287,               /* f_block_kw  */
  YYSYMBOL_f_block_kwarg = 288,            /* f_block_kwarg  */
  YYSYMBOL_f_kwarg = 289,                  /* f_kwarg  */
  YYSYMBOL_kwrest_mark = 290,              /* kwrest_mark  */
  YYSYMBOL_f_kwrest = 291,                 /* f_kwrest  */
  YYSYMBOL_args_tail = 292,                /* args_tail  */
  YYSYMBOL_opt_args_tail = 293,            /* opt_args_tail  */
  YYSYMBOL_f_args = 294,                   /* f_args  */
  YYSYMBOL_f_bad_arg = 295,                /* f_bad_arg  */
  YYSYMBOL_f_norm_arg = 296,               /* f_norm_arg  */
  YYSYMBOL_f_arg_item = 297,               /* f_arg_item  */
  YYSYMBOL_298_32 = 298,                   /* @32  */
  YYSYMBOL_f_arg = 299,                    /* f_arg  */
  YYSYMBOL_f_opt_asgn = 300,               /* f_opt_asgn  */
  YYSYMBOL_f_opt = 301,                    /* f_opt  */
  YYSYMBOL_f_block_opt = 302,              /* f_block_opt  */
  YYSYMBOL_f_block_optarg = 303,           /* f_block_optarg  */
  YYSYMBOL_f_optarg = 304,                 /* f_optarg  */
  YYSYMBOL_restarg_mark = 305,             /* restarg_mark  */
  YYSYMBOL_f_rest_arg = 306,               /* f_rest_arg  */
  YYSYMBOL_blkarg_mark = 307,              /* blkarg_mark  */
  YYSYMBOL_f_block_arg = 308,              /* f_block_arg  */
  YYSYMBOL_opt_f_block_arg = 309,          /* opt_f_block_arg  */
  YYSYMBOL_singleton = 310,                /* singleton  */
  YYSYMBOL_311_33 = 311,                   /* $@33  */
  YYSYMBOL_assoc_list = 312,               /* assoc_list  */
  YYSYMBOL_assocs = 313,                   /* assocs  */
  YYSYMBOL_assoc = 314,                    /* assoc  */
  YYSYMBOL_operation = 315,                /* operation  */
  YYSYMBOL_operation2 = 316,               /* operation2  */
  YYSYMBOL_operation3 = 317,               /* operation3  */
  YYSYMBOL_dot_or_colon = 318,             /* dot_or_colon  */
  YYSYMBOL_call_op = 319,                  /* call_op  */
  YYSYMBOL_call_op2 = 320,                 /* call_op2  */
  YYSYMBOL_opt_terms = 321,                /* opt_terms  */
  YYSYMBOL_opt_nl = 322,                   /* opt_nl  */
  YYSYMBOL_rparen = 323,                   /* rparen  */
  YYSYMBOL_trailer = 324,                  /* trailer  */
  YYSYMBOL_term = 325,                     /* term  */
  YYSYMBOL_nl = 326,                       /* nl  */
  YYSYMBOL_terms = 327,                    /* terms  */
  YYSYMBOL_none = 328                      /* none  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  110
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   13518

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  150
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  179
/* YYNRULES -- Number of rules.  */
#define YYNRULES  626
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  1095

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   378


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     149,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   136,     2,     2,     2,   134,   129,     2,
     143,   144,   132,   130,   145,   131,   148,   133,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   124,   147,
     126,   122,   125,   123,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   141,     2,   142,   128,     2,   146,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   139,   127,   140,   137,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   135,   138
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,  2047,  2047,  2047,  2057,  2063,  2067,  2071,  2075,  2081,
    2083,  2082,  2096,  2122,  2128,  2132,  2136,  2142,  2148,  2148,
    2152,  2156,  2160,  2164,  2173,  2182,  2186,  2191,  2192,  2196,
    2200,  2204,  2208,  2214,  2217,  2221,  2225,  2229,  2233,  2237,
    2242,  2246,  2255,  2264,  2273,  2282,  2289,  2290,  2294,  2297,
    2298,  2302,  2306,  2310,  2314,  2315,  2318,  2320,  2322,  2322,
    2325,  2335,  2334,  2349,  2358,  2359,  2362,  2363,  2370,  2369,
    2384,  2388,  2393,  2397,  2402,  2406,  2411,  2415,  2419,  2423,
    2427,  2433,  2437,  2443,  2444,  2450,  2454,  2458,  2462,  2466,
    2470,  2474,  2478,  2482,  2486,  2492,  2493,  2499,  2503,  2509,
    2513,  2519,  2523,  2527,  2531,  2535,  2539,  2545,  2551,  2558,
    2562,  2566,  2570,  2574,  2578,  2584,  2590,  2595,  2601,  2605,
    2608,  2612,  2616,  2623,  2624,  2625,  2626,  2631,  2638,  2639,
    2642,  2646,  2646,  2652,  2653,  2654,  2655,  2656,  2657,  2658,
    2659,  2660,  2661,  2662,  2663,  2664,  2665,  2666,  2667,  2668,
    2669,  2670,  2671,  2672,  2673,  2674,  2675,  2676,  2677,  2678,
    2679,  2680,  2681,  2684,  2684,  2684,  2685,  2685,  2686,  2686,
    2686,  2687,  2687,  2687,  2687,  2687,  2688,  2688,  2688,  2689,
    2689,  2689,  2690,  2690,  2690,  2690,  2691,  2691,  2691,  2691,
    2692,  2692,  2692,  2692,  2693,  2693,  2693,  2693,  2694,  2694,
    2694,  2694,  2695,  2695,  2698,  2702,  2706,  2710,  2714,  2718,
    2722,  2727,  2732,  2737,  2741,  2745,  2749,  2753,  2757,  2761,
    2765,  2769,  2773,  2777,  2781,  2785,  2789,  2793,  2797,  2801,
    2805,  2809,  2813,  2817,  2821,  2825,  2829,  2833,  2837,  2841,
    2845,  2849,  2853,  2857,  2861,  2865,  2869,  2873,  2877,  2881,
    2885,  2894,  2903,  2912,  2921,  2927,  2928,  2932,  2936,  2942,
    2946,  2953,  2957,  2966,  2983,  2984,  2987,  2988,  2989,  2993,
    2997,  3003,  3008,  3012,  3016,  3020,  3026,  3026,  3037,  3041,
    3047,  3051,  3057,  3060,  3065,  3069,  3073,  3078,  3082,  3088,
    3093,  3097,  3103,  3104,  3108,  3112,  3113,  3114,  3115,  3116,
    3121,  3120,  3132,  3136,  3131,  3141,  3141,  3145,  3149,  3153,
    3157,  3161,  3165,  3169,  3173,  3177,  3181,  3185,  3186,  3192,
    3199,  3191,  3212,  3220,  3228,  3228,  3228,  3235,  3235,  3235,
    3242,  3248,  3253,  3255,  3252,  3264,  3262,  3280,  3285,  3278,
    3302,  3300,  3316,  3326,  3337,  3341,  3345,  3349,  3355,  3362,
    3363,  3364,  3367,  3368,  3371,  3372,  3380,  3381,  3387,  3391,
    3394,  3398,  3402,  3406,  3411,  3415,  3419,  3423,  3429,  3428,
    3438,  3442,  3446,  3450,  3456,  3461,  3466,  3470,  3474,  3478,
    3482,  3486,  3490,  3494,  3498,  3502,  3506,  3510,  3514,  3518,
    3522,  3528,  3533,  3540,  3540,  3544,  3549,  3555,  3559,  3565,
    3566,  3569,  3574,  3577,  3581,  3587,  3591,  3598,  3597,  3614,
    3619,  3623,  3628,  3635,  3639,  3643,  3647,  3651,  3655,  3659,
    3663,  3667,  3674,  3673,  3688,  3687,  3703,  3711,  3720,  3723,
    3730,  3733,  3737,  3738,  3741,  3745,  3748,  3752,  3755,  3756,
    3757,  3758,  3761,  3762,  3768,  3773,  3778,  3783,  3789,  3790,
    3796,  3802,  3801,  3813,  3817,  3823,  3827,  3833,  3842,  3853,
    3856,  3857,  3860,  3866,  3872,  3873,  3876,  3883,  3882,  3897,
    3901,  3909,  3913,  3925,  3932,  3939,  3940,  3941,  3942,  3943,
    3947,  3953,  3957,  3965,  3966,  3967,  3971,  3977,  3981,  3985,
    3989,  3993,  3999,  4003,  4009,  4013,  4017,  4021,  4025,  4029,
    4033,  4041,  4048,  4054,  4055,  4059,  4063,  4062,  4079,  4080,
    4083,  4089,  4093,  4099,  4100,  4104,  4108,  4114,  4118,  4124,
    4130,  4137,  4143,  4150,  4154,  4160,  4164,  4170,  4171,  4174,
    4178,  4184,  4188,  4192,  4196,  4202,  4207,  4212,  4216,  4220,
    4224,  4228,  4232,  4236,  4240,  4244,  4248,  4252,  4256,  4260,
    4264,  4269,  4275,  4280,  4285,  4290,  4295,  4302,  4306,  4313,
    4318,  4317,  4329,  4333,  4339,  4347,  4355,  4363,  4367,  4373,
    4377,  4383,  4384,  4387,  4392,  4399,  4400,  4403,  4407,  4413,
    4417,  4423,  4429,  4429,  4436,  4437,  4443,  4447,  4453,  4459,
    4464,  4468,  4473,  4478,  4494,  4499,  4505,  4506,  4507,  4510,
    4511,  4512,  4513,  4516,  4517,  4518,  4521,  4522,  4525,  4529,
    4535,  4536,  4542,  4543,  4546,  4547,  4550,  4553,  4554,  4555,
    4558,  4559,  4562,  4567,  4570,  4571,  4575
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "\"'class'\"",
  "\"'module'\"", "\"'def'\"", "\"'begin'\"", "\"'if'\"", "\"'unless'\"",
  "\"'while'\"", "\"'until'\"", "\"'for'\"", "\"'undef'\"", "\"'rescue'\"",
  "\"'ensure'\"", "\"'end'\"", "\"'then'\"", "\"'elsif'\"", "\"'else'\"",
  "\"'case'\"", "\"'when'\"", "\"'break'\"", "\"'next'\"", "\"'redo'\"",
  "\"'retry'\"", "\"'in'\"", "\"'do'\"", "\"'do' for condition\"",
  "\"'do' for block\"", "\"'do' for lambda\"", "\"'return'\"",
  "\"'yield'\"", "\"'super'\"", "\"'self'\"", "\"'nil'\"", "\"'true'\"",
  "\"'false'\"", "\"'and'\"", "\"'or'\"", "\"'not'\"", "\"'if' modifier\"",
  "\"'unless' modifier\"", "\"'while' modifier\"", "\"'until' modifier\"",
  "\"'rescue' modifier\"", "\"'alias'\"", "\"'BEGIN'\"", "\"'END'\"",
  "\"'__LINE__'\"", "\"'__FILE__'\"", "\"'__ENCODING__'\"",
  "\"'defined?'\"", "\"local variable or method\"", "\"method\"",
  "\"global variable\"", "\"instance variable\"", "\"constant\"",
  "\"class variable\"", "\"label\"", "\"integer literal\"",
  "\"float literal\"", "\"character literal\"", "tXSTRING", "tREGEXP",
  "tSTRING", "tSTRING_PART", "tSTRING_MID", "tNTH_REF", "tBACK_REF",
  "tREGEXP_END", "\"numbered parameter\"", "\"unary plus\"",
  "\"unary minus\"", "\"<=>\"", "\"==\"", "\"===\"", "\"!=\"", "\">=\"",
  "\"<=\"", "\"&&\"", "\"||\"", "\"=~\"", "\"!~\"", "\"..\"", "\"...\"",
  "tBDOT2", "tBDOT3", "tAREF", "tASET", "\"<<\"", "\">>\"", "\"::\"",
  "tCOLON3", "tOP_ASGN", "\"=>\"", "tLPAREN", "\"(\"", "\")\"", "\"[\"",
  "tLBRACE", "\"{\"", "\"*\"", "tPOW", "\"**\"", "\"&\"", "\"->\"",
  "\"&.\"", "\"symbol\"", "\"string literal\"", "tXSTRING_BEG",
  "tSTRING_DVAR", "tREGEXP_BEG", "tWORDS_BEG", "tSYMBOLS_BEG", "tLAMBEG",
  "\"here document\"", "tHEREDOC_END", "tLITERAL_DELIM",
  "tHD_LITERAL_DELIM", "tHD_STRING_PART", "tHD_STRING_MID", "tLOWEST",
  "'='", "'?'", "':'", "'>'", "'<'", "'|'", "'^'", "'&'", "'+'", "'-'",
  "'*'", "'/'", "'%'", "tUMINUS_NUM", "'!'", "'~'", "tLAST_TOKEN", "'{'",
  "'}'", "'['", "']'", "'('", "')'", "','", "'`'", "';'", "'.'", "'\\n'",
  "$accept", "$@1", "program", "top_compstmt", "top_stmts", "top_stmt",
  "@2", "bodystmt", "compstmt", "stmts", "$@3", "stmt", "command_asgn",
  "command_rhs", "expr", "defined_with_parens", "defined_without_parens",
  "defined_expression", "defn_head", "$@4", "defs_head", "expr_value",
  "command_call", "block_command", "$@5", "cmd_brace_block", "command",
  "mlhs", "mlhs_inner", "mlhs_basic", "mlhs_item", "mlhs_list",
  "mlhs_post", "mlhs_node", "lhs", "cname", "cpath", "fname", "fsym",
  "undef_list", "$@6", "op", "reswords", "arg", "aref_args", "arg_rhs",
  "paren_args", "opt_paren_args", "opt_call_args", "call_args", "@7",
  "command_args", "block_arg", "opt_block_arg", "comma", "args", "mrhs",
  "primary", "@8", "@9", "$@10", "$@11", "@12", "@13", "$@14", "$@15",
  "$@16", "$@17", "$@18", "$@19", "@20", "@21", "@22", "@23",
  "primary_value", "then", "do", "if_tail", "opt_else", "for_var",
  "f_margs", "$@24", "block_args_tail", "opt_block_args_tail",
  "block_param", "opt_block_param", "$@25", "block_param_def",
  "opt_bv_decl", "bv_decls", "bvar", "f_larglist", "lambda_body", "@26",
  "do_block", "block_call", "method_call", "@27", "brace_block", "@28",
  "case_body", "cases", "opt_rescue", "exc_list", "exc_var", "opt_ensure",
  "literal", "string", "string_fragment", "string_rep", "string_interp",
  "@29", "xstring", "regexp", "heredoc", "heredoc_bodies", "heredoc_body",
  "heredoc_string_rep", "heredoc_string_interp", "@30", "words", "symbol",
  "basic_symbol", "sym", "symbols", "numeric", "variable", "var_lhs",
  "var_ref", "backref", "superclass", "$@31", "f_opt_arglist_paren",
  "f_arglist_paren", "f_arglist", "f_label", "f_kw", "f_block_kw",
  "f_block_kwarg", "f_kwarg", "kwrest_mark", "f_kwrest", "args_tail",
  "opt_args_tail", "f_args", "f_bad_arg", "f_norm_arg", "f_arg_item",
  "@32", "f_arg", "f_opt_asgn", "f_opt", "f_block_opt", "f_block_optarg",
  "f_optarg", "restarg_mark", "f_rest_arg", "blkarg_mark", "f_block_arg",
  "opt_f_block_arg", "singleton", "$@33", "assoc_list", "assocs", "assoc",
  "operation", "operation2", "operation3", "dot_or_colon", "call_op",
  "call_op2", "opt_terms", "opt_nl", "rparen", "trailer", "term", "nl",
  "terms", "none", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-878)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-627)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -878,  3440,    97,  8511, 10653, 10998,  6822,  -878,  9582,  9582,
    -878,  -878, 10768,  7110,  6291,  8749,  8749,  -878,  -878,  8749,
    3965,  3554,  -878,  -878,  -878,  -878,   -32,  7110,  -878,    26,
    -878,  -878,  -878,  8370,  7632,  3109,  -878,  -878,  7755,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,   202, 10415, 10415, 10415,
   10415,    81,  5490,  1101,  9225,  9701,  7398,  -878,  6678,   657,
     940,   773,  1013,  1097,  -878,   486, 10534, 10415,  -878,  1123,
    -878,  1375,  -878,   598,  -878,  -878,  -878,  1756,  1756,  -878,
    -878,   129,    55,  -878,    38, 10883,  -878,    66, 13118,   148,
     303,   177,    73,  -878,   105,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,   363,   154,  -878,   482,    84,  -878,
    -878,  -878,  -878,  -878,  -878,   109,   109,   -32,   166,   659,
    -878,  9582,    86,  5637,   611,  1896,  1896,  -878,   145,  -878,
     433,  -878,  -878,    84,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,    72,    88,   172,   201,  -878,  -878,  -878,  -878,
    -878,  -878,   203,   230,   247,  -878,   253,  -878,   254,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,   289,  4662,   221,   598,  1756,  1756,
     106,   164, 13242,   461,   204,   208,   270,   106,  9582,  9582,
     499,   252,  -878,  -878,   675,   288,    37,    56,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  6966,  -878,  -878,
     186,  -878,  -878,  -878,  -878,  -878,  -878,  1123,  -878,   308,
    -878,   297,  -878,  -878,  1123,  3691,   188, 10415, 10415, 10415,
   10415,  -878, 13180,  -878,  -878,   195,   290,   195,  -878,  -878,
    -878,  8868,  -878,  -878,  8749,  -878,  -878,  -878,  -878,  6291,
    6411,  -878,   216,  5784, 11113,  1725,  -878,   678,   262, 13304,
   13304,   519,  8630,  5490,   235,  1123,  1375,  1123,   269,  -878,
    8630,  1123,   232,   996,   996,  -878, 13180,   267,   996,  -878,
     354, 11228,   277,   764,   786,   789,  1242,  -878,  -878,  -878,
    -878,  -878,  1192,  -878,  -878,  -878,  -878,  -878,  -878,   501,
    1201,  -878,  -878,  1030,  -878,  1134,  -878,  1249,  -878,  1258,
     330,   333,  -878,  -878,  -878,  -878,  6051,  9582,  9582,  9582,
    9582,  8630,  9582,  9582,    63,  -878,  -878,  -878,  -878,   389,
    1123,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  1539,   344,
     374,  4662, 10415,  -878,   307,   454,   381,  -878,  1123,  -878,
    -878,  -878,   384, 10415,  -878,   392,   517,   428,   525,  -878,
    -878,   471,  4662,  -878,  -878,  9820,  -878,  5490,  7515,   463,
    9820, 10415, 10415, 10415, 10415, 10415, 10415, 10415, 10415, 10415,
   10415, 10415, 10415, 10415, 10415,   547, 10415, 10415, 10415, 10415,
   10415, 10415, 10415, 10415, 10415, 10415, 10415, 10415,  2365,  -878,
    8749,  -878, 11424,  -878,  -878, 12628,  -878,  -878,  -878,  -878,
   10534, 10534,  -878,   516,  -878,   598,  -878,   822,  -878,  -878,
    -878,  -878,  -878,  -878, 11510,  8749, 11596,  4662,  9582,  -878,
    -878,  -878,   603,   619,   296,   520,   526,  -878,  4809,   640,
   10415, 11682,  8749, 11768, 10415, 10415,  5103,   113,   113,    57,
   11854,  8749, 11940,  -878,   602,  -878,  5784,   297,  -878,  -878,
    9939,   677,  -878, 10415, 10415, 13242, 13242, 13242, 10415,  -878,
    -878,  8987,  -878, 10415,  -878,  9344,  6531,   563,  1123,   195,
     195,  -878,  -878,   864,   567,  -878,  -878,  -878,  7110,  5223,
     575,   661,   584,   830, 11682, 11768, 10415,  1375,  1123,  -878,
    -878,  6171,   592,  1375,  -878,  -878,  9463,  -878,  1123,  9701,
    -878,  -878,  -878,   822,    38, 11228,  -878, 11228, 12026,  8749,
   12112,  2065,  -878,  -878,   606,  -878,  1296,  5784,   501,  -878,
    -878,  -878,  -878,  -878,  -878,  -878, 10415, 10415,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    1562,  1123,  1123,   607, 10534,   738, 13242,   744,  -878,  -878,
    -878,    35,  -878,  -878,  1908,  -878, 13242,  2065,  -878,  -878,
    1342,  -878,  -878, 10534,   752,    44, 10415,  -878, 12826,   195,
    -878,  1123, 11228,   626,  -878,  -878,  -878,   729,   660, 11341,
    -878,  -878,   881,   345,  2764,  2764,  2764,  2764,  1658,  1658,
   13384, 13322,  2764,  2764, 13304, 13304,  1356,  1356,  -878,   262,
   13242,  1658,  1658,  1374,  1374,  1781,   777,   777,   262,   262,
     262,  4102,  8124,  4376,  8247,  -878,   109,  -878,   645,   195,
     582,  -878,   623,  -878,  -878,  3828,  -878,  -878,  3248,    44,
      44,  -878,  3300,  -878,  -878,  -878,  -878,  -878,  1123,  9582,
    4662,   792,   282,  -878,   109,   646,   109,   774,   864,  7254,
    -878, 10058,   772,  -878, 10415, 10415,   481,  -878,  7878,  8001,
     650,   347,   380,   772,  -878,  -878,  -878,  -878,    48,    61,
     653,    71,   116,  9582,  7110,   665,   782, 13242,   594,  -878,
   13242, 13242, 13242,   538, 10415, 13180,  -878,   195, 13242,  -878,
    -878,  -878,  -878,  9106,  9344,  -878,  -878,  -878,   672,  -878,
    -878,  -878, 12198,  -878,    28,  1375,  1123,   996,   463,  -878,
     792,   282,   685,   942,   978,  -878,   107,  2065,  -878,   690,
    -878,   262,   262,  -878,  -878,   104,  1123,   656,  -878,  -878,
    2043,   787, 12702,  -878,   759,   389,  -878,   381,  -878,  1123,
    -878,  -878,   688,   704,   707,  -878,   708,   759,   707,   812,
   12764,  -878,  -878,  2065,  4662,  -878,  -878, 12899, 10177,  -878,
    -878, 11228,  8630, 10534, 10415, 12284,  8749, 12370,  1036, 10534,
   10534,  -878,   516,   654,  8987, 10534, 10534,  -878,   516,    73,
     129,  4662,  5784,    44,  -878,  1123,   843,  -878,  -878,  -878,
    -878, 12826,  -878,   767,  -878,  5370,   848,  -878,  9582,   857,
    -878, 10415, 10415,   385, 10415, 10415,   861,  5931,  5931,   128,
     113,  -878,  -878,  -878, 10296,  4956, 13242,  -878,  6531,   195,
    -878,   739,   743,  -878,  -878,   302,   745,  1253,  4662,  5784,
    -878,  -878,  -878,   736,  -878,  1649,  1123, 10415, 10415,  -878,
    -878,  2065,  -878,  1342,  -878,  1342,  -878,  1342,  -878,  -878,
   10415, 10415,  -878,  -878,  -878, 11113,  -878,   755,   381,   758,
   11113,  -878,   763,   778,  -878,   917, 10415, 12972,  -878,  -878,
   13242,  4239,  4513,   799,   439,   450, 10415, 10415,  -878,  -878,
    -878,  -878,  -878, 10534,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,   928,   807,  5784,  4662,  -878,  -878, 11343,   106,  -878,
    -878,  5931,  -878,  -878,   106,  -878, 10415,  -878,   933,   935,
    -878, 13242,   127,  -878,  9344,  -878,  1507,   944,   815,  1661,
    1661,   754,  -878, 13242, 13242,   707,   817,   707,   707, 13242,
   13242,   838,   840,   830,   744,  -878,  -878,  1325,  -878,   830,
    2065,  -878,  1342,  -878,  -878, 13045,   485, 13242, 13242,  -878,
    -878,  -878,  -878,   829,   960,   920,  -878,   934,   786,   789,
    4662,  -878,  4809,  -878,  -878,  5931,  -878,  -878,  -878,  -878,
     832,  -878,  -878,  -878,  -878,   834,   834,  1661,   836,  -878,
    1342,  -878,  -878,  -878,  -878,  -878,  -878,   381,   744,  -878,
    -878,   841,   844,   846,  -878,   858,   846,  -878,  -878,   822,
   12456,  8749, 12542,   619,   481,   970,  1507,   538,  1661,   834,
    1661,   707,  -878,  2065,  -878,  1342,  -878,  1342,  -878,  1342,
    -878,  -878,   792,   282,   865,   284,   644,  -878,  -878,  -878,
    -878,   834,  -878,   846,   863,   846,   846,   302,  -878,  1342,
    -878,  -878,  -878,   846,  -878
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       2,     0,     0,     0,     0,     0,     0,   300,     0,     0,
     324,   327,     0,     0,   612,   344,   345,   346,   347,   312,
     276,   276,   497,   496,   498,   499,   614,     0,    10,     0,
     501,   500,   502,     0,   487,   598,   489,   488,   491,   490,
     483,   484,   444,   445,   503,   504,   495,     0,     0,     0,
       0,     0,     0,   302,   626,   626,    93,   319,     0,     0,
       0,     0,     0,     0,   459,     0,     0,     0,     3,   612,
       6,     9,    27,    33,    58,    59,    54,   551,   551,    49,
      65,    64,     0,    81,     0,    85,    95,     0,    55,   254,
       0,    66,   317,   292,   293,   442,   294,   295,   296,   440,
     439,   471,   441,   438,   494,     0,   297,   298,   276,     5,
       1,     8,   344,   345,   312,   626,   420,     0,   118,   119,
     495,     0,     0,     0,     0,   551,   551,   121,   505,   348,
       0,   494,   298,     0,   340,   173,   184,   174,   170,   200,
     201,   202,   203,   182,   197,   190,   180,   179,   195,   178,
     177,   172,   198,   171,   185,   189,   191,   183,   176,   192,
     199,   194,   193,   186,   196,   181,   169,   188,   187,   168,
     166,   167,   163,   164,   165,   175,   123,   125,   124,   158,
     159,   136,   137,   138,   145,   142,   144,   139,   140,   160,
     161,   146,   147,   151,   154,   155,   141,   143,   133,   134,
     135,   148,   149,   150,   152,   153,   156,   157,   582,   162,
      60,   126,   127,   581,     0,     0,     0,    63,   551,   551,
       0,     0,    55,     0,   494,     0,   298,     0,     0,     0,
     117,     0,   359,   358,     0,     0,   494,   298,   193,   186,
     196,   181,   163,   164,   165,   123,   124,     0,   128,   130,
      20,   129,   462,   467,   466,   620,   622,   612,   623,     0,
     464,     0,   624,   621,   613,   596,   495,   284,   595,   279,
       0,   271,   283,    79,   275,   626,   442,   626,   586,    80,
      78,   626,   265,   313,     0,    77,   264,   419,    76,   612,
       0,    18,     0,     0,     0,     0,   227,     0,   228,   215,
     218,   309,     0,     0,     0,   612,    15,   612,    83,    14,
       0,   612,     0,   617,   617,   255,     0,     0,   617,   584,
       0,     0,    91,     0,   101,   108,   551,   477,   476,   478,
     479,   473,     0,   475,   474,   446,   451,   450,   453,     0,
       0,   448,   455,     0,   457,     0,   469,     0,   481,     0,
     485,   486,    53,   242,   243,     4,   613,     0,     0,     0,
       0,     0,     0,     0,   558,   554,   553,   552,   555,   556,
       0,   560,   572,   527,   528,   576,   575,   571,   551,     0,
     513,     0,   520,   525,   626,   530,   626,   550,     0,   557,
     559,   562,   536,     0,   569,   536,   574,   536,   578,   534,
     509,     0,     0,   407,   409,     0,    97,     0,    89,    86,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   214,   217,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   609,
     626,   608,     0,   611,   610,     0,   424,   422,   318,   443,
       0,     0,   413,    70,   316,   337,   118,   119,   120,   485,
     486,   513,   506,   335,     0,   626,     0,     0,     0,   607,
     606,    61,     0,   626,   309,     0,     0,   350,     0,   349,
       0,     0,   626,     0,     0,     0,     0,     0,     0,   309,
       0,   626,     0,   332,     0,   131,     0,     0,   463,   465,
       0,     0,   625,   590,   591,   285,   594,   278,     0,   614,
     272,     0,   281,     0,   273,     0,   612,     0,   612,   626,
     626,   266,   277,   612,     0,   315,    52,   615,     0,     0,
       0,     0,   348,     0,     0,     0,     0,    17,   612,   307,
      13,   613,    82,   303,   306,   310,   619,   256,   618,   619,
     258,   311,   585,   107,    99,     0,    94,     0,     0,   626,
       0,   551,   320,   404,   536,   480,     0,     0,   454,   460,
     447,   449,   456,   458,   470,   482,     0,     0,     7,    21,
      22,    23,    24,    25,    50,    51,   517,   564,   518,   516,
       0,   612,   612,   536,     0,     0,   519,     0,   532,   580,
     529,     0,   533,   514,     0,   543,   565,     0,   546,   573,
       0,   548,   577,     0,     0,   626,   284,    28,    30,     0,
      31,   612,     0,    87,    98,    48,    34,    46,     0,   259,
     204,    29,     0,   298,   232,   237,   238,   239,   234,   236,
     246,   247,   240,   241,   213,   216,   244,   245,    32,   224,
     614,   233,   235,   229,   230,   231,   219,   220,   221,   222,
     223,   599,   604,   600,   605,   418,   276,   416,     0,   626,
     599,   601,   600,   602,   417,   276,   599,   600,   276,   626,
     626,    35,   259,   205,    45,   212,    68,    71,     0,     0,
       0,   118,   119,   122,     0,     0,   626,     0,   612,     0,
     301,   626,   626,   430,     0,     0,   626,   351,   603,   308,
       0,   599,   600,   626,   353,   325,   352,   328,   603,   308,
       0,   599,   600,     0,     0,     0,     0,   283,     0,   331,
     589,   592,   588,   282,   287,   286,   280,   626,   593,   587,
     263,   261,   267,   268,   270,   314,   616,    19,     0,    26,
     309,    56,     0,   211,    84,    16,   612,   617,   100,    92,
     104,   106,     0,   103,   105,   614,     0,     0,   472,     0,
     461,   225,   226,   558,   556,   367,   612,   360,   512,   510,
       0,    41,   250,   342,     0,     0,   526,   626,   579,     0,
     535,   563,   536,   536,   536,   570,   536,   558,   536,    43,
     252,   343,   395,   393,     0,   392,   391,   291,     0,    96,
      90,     0,     0,     0,     0,     0,   626,     0,     0,     0,
       0,   415,    74,   421,   268,     0,     0,   414,    72,   410,
      67,     0,     0,   626,   338,     0,     0,   421,   341,   583,
      62,   431,   432,   626,   433,     0,   626,   356,     0,     0,
     354,     0,     0,   421,     0,     0,     0,     0,     0,   421,
       0,   132,   468,   330,     0,     0,   288,   274,   612,   626,
      11,   603,   308,   304,   257,   102,     0,   397,     0,     0,
     321,   452,   368,   365,   561,     0,   612,     0,     0,   531,
     515,     0,   539,     0,   541,     0,   547,     0,   544,   549,
       0,     0,   390,   614,   614,   522,   523,   626,   626,   375,
       0,   567,   375,   375,   373,     0,   287,   289,    88,    47,
     260,   599,   600,     0,   599,   600,     0,     0,    40,   209,
      39,   210,    75,     0,    37,   207,    38,   208,    73,   411,
     412,     0,     0,     0,     0,   507,   336,     0,     0,   435,
     357,     0,    12,   437,     0,   322,     0,   323,     0,     0,
     333,   286,   626,   262,   269,   403,     0,     0,     0,     0,
       0,   363,   511,    42,   251,   536,   536,   536,   536,    44,
     253,     0,     0,   521,     0,   371,   372,   375,   383,   566,
       0,   386,     0,   388,   408,   290,   421,   249,   248,    36,
     206,   425,   423,     0,     0,     0,   434,     0,   109,   116,
       0,   436,     0,   326,   329,     0,   427,   428,   426,   401,
     614,   399,   402,   406,   405,   369,   366,     0,   361,   540,
       0,   537,   542,   545,   396,   394,   524,   626,     0,   374,
     381,   375,   375,   375,   568,   375,   375,    69,   339,   115,
       0,   626,     0,   626,   626,     0,     0,   398,     0,   364,
       0,   536,   370,     0,   378,     0,   380,     0,   387,     0,
     384,   389,   112,   114,     0,   599,   600,   429,   355,   334,
     400,   362,   538,   375,   375,   375,   375,   110,   379,     0,
     376,   382,   385,   375,   377
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -878,  -878,  -878,   459,  -878,    41,  -878,  -277,    39,  -878,
    -878,   132,  -200,  -420,   226,  -878,  -878,  -878,  1351,  -878,
    1771,     2,   -64,  -878,  -878,  -676,    69,  1002,  -223,   -25,
     -63,  -270,  -493,   -10,  2212,   -88,  1010,    -2,   -18,  -878,
    -878,    20,  -878,  1120,  -878,   409,   -13,  -321,  -348,    93,
    -878,    18,  -428,  -236,   -99,    53,  -362,   163,  -878,  -878,
    -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,  -878,
    -878,  -878,  -878,  -878,     9,  -224,  -448,   -36,  -639,  -878,
    -878,  -878,   220,   246,  -878,  -590,  -878,  -878,  -214,  -878,
     -28,  -878,  -878,  -878,   200,  -878,  -878,  -878,   -91,  -878,
    -482,  -878,   -22,  -878,  -878,  -878,  -878,  -878,   100,    -3,
    -140,  -878,  -878,  -878,  -878,  -878,  -289,  -878,   775,  -878,
    -878,  -878,    16,  -878,  -878,  -878,  2102,  2468,  1026,  1978,
    -878,  -878,   -23,   609,    23,   217,   438,    58,  -878,  -878,
    -878,   206,   405,  -198,  -255,  -848,  -696,  -424,  -878,   119,
    -705,  -558,  -877,    50,  -552,  -878,  -476,  -878,    75,  -351,
    -878,  -878,  -878,    51,  -422,   636,  -294,  -878,  -878,   -53,
    -878,    31,   -20,   435,  -282,   737,  -285,   -49,    -1
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,     2,    68,    69,    70,   292,   472,   473,   305,
     528,   306,    72,   626,    73,    74,    75,    76,   218,   699,
     219,   220,    79,    80,   833,   687,    81,    82,   307,    83,
      84,    85,   556,    86,   221,   127,   128,   248,   249,   250,
     724,   664,   212,    88,   312,   630,   665,   283,   517,   518,
     284,   285,   274,   510,   549,   669,   620,    89,   215,   310,
     756,   311,   326,   766,   228,   857,   229,   858,   723,  1015,
     690,   688,   944,   467,   297,   478,   715,   849,   850,   235,
     776,   969,  1039,   988,   903,   804,   904,   805,   876,  1020,
    1021,   562,   880,   615,   404,    91,    92,   680,   454,   679,
     501,  1018,   702,   843,   948,   952,    93,    94,    95,   340,
     341,   567,    96,    97,    98,   568,   258,   259,   260,   496,
      99,   100,   101,   334,   102,   103,   224,   225,   106,   226,
     463,   689,   379,   380,   381,   382,   383,   906,   907,   384,
     385,   386,   790,   605,   388,   389,   390,   391,   590,   392,
     393,   394,   911,   912,   395,   396,   397,   398,   399,   598,
     214,   468,   317,   520,   278,   133,   694,   667,   471,   466,
     445,   524,   877,   525,   547,   262,   263,   264,   309
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     109,   448,   352,   486,   210,   527,   290,   282,   287,   291,
      90,   227,    90,   130,   130,   726,   257,   223,   223,   286,
     356,   234,   409,   223,   223,   223,   211,   308,   223,   251,
     681,   684,   550,   211,   458,   602,   552,   442,   444,   288,
     717,   514,   223,   251,   111,   261,   322,   211,   631,   795,
     569,   555,   792,   315,   319,   401,   333,   343,   345,   347,
     349,    90,  -109,   846,   759,   323,   277,   277,   275,   275,
     277,   563,   275,  -112,   856,   223,   400,   400,   211,   883,
     538,  -116,  -115,   736,   271,   271,  -114,   736,   271,   831,
     832,   304,   668,   739,   323,   452,  -111,   110,   910,   446,
     355,   402,   282,   287,   595,   314,   318,   313,   273,   279,
     446,   289,   280,  1044,   286,   276,   276,   695,  1022,   276,
     452,   586,   477,   592,   802,   614,   453,   739,   793,   810,
     223,   796,    90,    71,   710,    71,   878,   301,   456,   375,
     714,  -113,   457,   720,   666,   845,   932,   500,   675,   402,
     -82,   678,   938,  -110,   276,   276,   773,   403,   365,   366,
     367,   368,   304,  -497,   376,   293,    42,   129,   129,    43,
     483,   803,   696,   -96,   774,   129,   511,   405,   515,  -496,
     791,   492,  -101,   406,   621,   587,  1044,   666,   410,   675,
     697,  -599,  -596,  -104,   449,   475,   476,   608,   696,   611,
     571,  -108,  -107,   571,  -600,   571,  -106,   571,  1022,   571,
     625,   762,   447,    59,   546,   792,  -103,   400,   400,   129,
    -497,   879,   252,   447,    90,   253,   254,   281,   792,   252,
     487,   488,   253,   254,   217,   217,  -496,   223,   223,  -348,
     217,   696,   402,   943,   535,   333,   504,   450,   129,   882,
     625,   625,   281,   255,  -348,   256,   541,  -487,   554,   295,
     255,  -105,   256,  -498,   548,   548,   696,   211,   443,   548,
     560,   462,  -487,  -102,   512,  1028,   512,   474,   308,   770,
     521,  -493,   910,   439,   514,   910,   480,   555,   497,  -348,
     223,   793,  -499,   223,  -501,  -493,  -348,  -492,   223,   223,
    -111,   484,    90,   533,   793,  -596,   765,  -487,   489,  -596,
    -117,    90,    90,   493,  -487,   736,   736,   500,   918,    90,
    -498,  -500,   739,  1016,  -117,   441,  -109,   913,  -421,   566,
     323,   495,   530,   795,   519,   277,   540,   275,  -502,   842,
     509,   617,   304,   791,  -487,  -491,   627,   455,   513,  -499,
     271,  -501,   555,   271,   827,   529,   791,   829,   910,   579,
     580,   581,   582,   485,   426,    90,   223,   223,   223,   223,
      90,   223,   223,  -308,   545,   827,   693,   522,  -500,   539,
     469,   276,   308,   599,   276,   599,   627,   627,  -308,   536,
      90,   -81,  -116,  -421,   438,  -502,   736,   578,   623,   928,
    -111,  -487,  -491,  -111,  -111,   934,   936,   551,  -421,   439,
     553,    90,   960,   836,   223,   976,    90,   323,  -115,   632,
     743,   744,   557,  -308,   498,  -600,   571,   253,   254,   674,
    -308,  -111,   576,  -111,   537,   577,   889,   470,   451,   521,
     854,  -421,   543,  -421,   440,   564,   304,   588,   527,   223,
    -421,   441,   597,   674,   217,   217,  -492,   532,   619,   632,
     632,   791,   673,   619,   521,   673,   594,  -116,   923,  -111,
     674,   791,   703,   855,   223,   874,    90,   223,   956,   674,
    1017,   521,   387,   387,   129,  -109,   673,    90,    71,   733,
     521,   223,   758,   583,   554,    90,  -508,   593,   848,   845,
     223,   867,  -113,   673,   865,    90,   600,  -110,  -101,   271,
     747,  1042,   673,   999,  1045,   523,   526,   706,   512,   512,
     808,   666,   674,   675,   464,   713,   601,   915,   109,   604,
     387,   387,   825,   527,   271,   725,   736,   607,    90,   439,
     276,   555,   739,   826,   251,   350,   351,   674,   211,   742,
      90,   271,   481,   728,   941,   673,   985,   986,   521,   554,
     271,  -111,   737,   791,   323,   276,   323,   439,   223,   609,
     824,   129,  -113,   610,   465,   451,    90,   612,   933,   817,
     673,   441,   276,   217,   217,   217,   217,  1084,   584,   585,
    -495,   276,   527,   613,   892,   894,   896,   757,   898,   648,
     899,   967,   482,   223,  -116,  -495,   769,  -110,   624,   441,
     477,   276,   536,   625,   806,   276,   686,   252,   700,   625,
     253,   254,   223,   387,   387,   625,   625,  -108,   271,   864,
     818,   323,   701,   867,   791,   362,   363,   108,   515,   108,
    -495,  -115,   704,   791,   108,   108,   276,  -495,   705,   276,
     108,   108,   108,   821,   252,   108,   707,   253,   254,   276,
    -113,    71,   282,   781,  -107,   282,   565,  1004,   512,   108,
     459,   460,   788,   755,   286,   825,   788,   286,   806,   806,
     564,   821,   799,   282,   822,  -597,  1062,   256,   108,   981,
     982,   835,   729,   828,   698,   286,   830,   840,   223,    90,
     844,   847,   108,  1074,  -111,   847,   861,   741,   548,   777,
     252,   746,   847,   253,   254,   749,   826,   750,   129,   211,
     129,   335,   336,   337,  1010,   860,   794,  -103,   751,   798,
    1012,   387,   223,   625,   461,   461,   512,   -96,   939,   509,
     251,   255,   542,   256,   211,  -113,   544,   933,   554,   627,
    -491,   767,   780,   783,   619,   627,   930,   108,   696,   108,
    -113,   627,   627,  -113,  -113,  -491,   490,   801,  -105,   534,
     964,   811,   527,   812,   338,   339,  -110,  1029,  1031,  1032,
    1033,   439,   813,   387,   439,   129,   599,   823,   837,   838,
     845,  -113,   853,  -113,   869,   859,   784,   863,  -597,  -102,
    -491,   885,  -597,   787,   674,   862,   773,  -491,   365,   366,
     367,   368,   870,    90,   785,   521,   491,   586,  -603,   482,
     323,    90,   632,   441,   774,   223,   441,   875,   632,   223,
     881,   887,   806,   891,   632,   632,   344,   673,   336,   337,
      90,    90,   949,   276,   276,   953,   373,   374,   375,   893,
     954,   108,   895,   897,    90,   558,   900,   223,   946,   683,
     685,   947,   951,  1082,   108,   108,    90,    90,   512,   627,
     439,   942,   955,   376,    90,   869,   957,  -494,   914,   426,
    -298,   970,  -599,  -603,   950,   271,  -600,    90,    90,   965,
     338,   339,  -494,   683,   685,  -298,   958,   959,  -603,  1027,
     984,   362,   363,   987,   962,   559,   599,   599,   990,   435,
     436,   437,   441,  -309,   983,   217,   276,   108,   968,   989,
     108,   752,   909,   992,   276,   108,   108,  -494,  -309,   108,
    -298,  -603,   994,  -603,  -494,  -599,   439,  -298,   108,   108,
    -603,   996,   632,  1001,   919,   753,   108,  1002,  1013,   217,
    1014,   740,    90,    90,  1052,  1024,  1007,   479,   745,  1023,
      90,   847,  1030,  -309,   479,  1034,   387,  1035,  -599,  1047,
    -309,   465,   815,   754,   129,  1048,  1049,  1056,   441,  1058,
     252,  1060,  1003,   253,   254,  1079,  1063,   439,   748,  1065,
    1011,  1067,   108,   108,   108,   108,   108,   108,   108,   108,
    1057,   502,   342,  1069,  -600,   336,   337,  1087,  1089,   908,
     975,   255,   977,   256,   232,   134,   978,   108,  1078,    90,
     905,    90,   816,   902,    90,  1050,   778,   779,  1080,   441,
     940,  1077,   213,  -599,   499,   786,   599,  1041,   108,   674,
     439,   108,  1036,   108,     0,     0,   108,     0,  -599,  1053,
     521,  1054,   703,   847,  1055,     0,   809,   338,   339,   788,
     223,     0,   914,     0,   276,   914,     0,   914,   129,  -600,
       0,     0,   673,   129,   217,  1051,   108,   346,   336,   337,
       0,  -599,   441,  -599,  -600,  -599,   108,   108,  1025,  1026,
    -599,     0,   572,   502,   926,   336,   337,     0,     0,     0,
       0,   108,     0,   108,   108,     0,     0,   589,     0,  1043,
     129,  1046,   252,   914,   108,   253,   254,  -600,   108,  -600,
     271,  -600,   108,     0,     0,   603,  -600,   108,   222,   222,
     338,   339,   108,   839,   222,   272,   272,     0,   914,   272,
     914,   509,   914,   255,   914,   256,  1059,   338,   339,  1061,
       0,   276,   252,   222,     0,   253,   254,     0,   991,   993,
     927,   348,   336,   337,   914,   108,     0,   296,   298,   299,
     300,     0,     0,     0,   272,   316,     0,   108,     0,  1081,
       0,     0,  1083,     0,  1085,   256,   353,   354,  1086,     0,
    1037,   873,     0,   908,     0,   108,   908,   573,   908,   336,
     337,   905,     0,   108,   905,     0,     0,   905,  1093,   905,
       0,   884,     0,     0,   338,   339,     0,  -305,     0,     0,
    -305,  -305,     0,     0,   716,   716,     0,     0,   929,   931,
     108,     0,     0,  1040,   935,   937,     0,     0,     0,   252,
       0,   222,   253,   254,   908,  -305,     0,     0,  -305,   108,
    -305,   338,   339,     0,     0,   905,   565,   336,   337,     0,
     929,   931,     0,   935,   937,   570,   336,   337,     0,   908,
     255,   908,   256,   908,     0,   908,     0,     0,   502,     0,
     905,     0,   905,     0,   905,   502,   905,  1064,  1066,  1068,
       0,  1070,  1071,     0,   364,   908,   365,   366,   367,   368,
       0,     0,     0,   963,     0,     0,   905,     0,     0,   338,
     339,     0,   369,   574,   336,   337,     0,     0,   338,   339,
       0,   972,   575,   336,   337,   108,   108,     0,     0,  1088,
    1090,  1091,  1092,     0,     0,     0,     0,   371,     0,  1094,
       0,     0,  1000,   372,   373,   374,   375,     0,   222,   222,
       0,     0,    77,     0,    77,   125,   125,     0,     0,   108,
     768,   336,   337,   125,     0,  1000,   338,   339,     0,   252,
       0,   376,   253,   254,   377,   338,   339,   364,     0,   365,
     366,   367,   368,     0,     0,   561,     0,   505,   506,   507,
     353,     0,     0,     0,   797,   369,   365,   366,   367,   368,
     966,   272,   256,    77,   272,     0,     0,   125,     0,   222,
     222,     0,   369,   338,   339,   357,   358,   359,   360,   361,
     371,     0,     0,     0,     0,   834,   372,   373,   374,   375,
       0,     0,     0,     0,     0,     0,   125,   371,     0,     0,
     108,     0,     0,     0,   373,   374,   375,     0,   108,   108,
       0,     0,   108,     0,   376,   108,   108,   377,   426,     0,
       0,   108,   108,   423,   424,   479,     0,   108,   108,     0,
    1038,   376,     0,     0,    77,     0,   426,   222,   222,   222,
     222,   108,   222,   222,   108,     0,   433,   434,   435,   436,
     437,     0,     0,   108,   108,     0,     0,     0,     0,     0,
       0,   108,   596,   432,   433,   434,   435,   436,   437,     0,
       0,     0,     0,   606,   108,   108,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   618,   890,     0,     0,     0,
     629,   634,   635,   636,   637,   638,   639,   640,   641,   642,
     643,   644,   645,   646,   647,     0,   649,   650,   651,   652,
     653,   654,   655,   656,   657,   658,   659,   660,     0,  1019,
     272,   365,   366,   367,   368,     0,    77,     0,     0,   108,
     682,   682,   945,     0,     0,     0,     0,   774,     0,   108,
     108,     0,     0,     0,     0,   272,     0,   108,   222,     0,
       0,   364,     0,   365,   366,   367,   368,   716,     0,     0,
     682,     0,   272,     0,   682,   682,     0,     0,     0,   369,
       0,   272,     0,     0,   773,     0,   365,   366,   367,   368,
     727,     0,     0,   730,   731,   591,     0,     0,   732,     0,
       0,   735,   774,   738,   371,   316,   300,     0,     0,     0,
     372,   373,   374,   375,    77,   125,   108,     0,   108,     0,
       0,   108,     0,    77,    77,     0,   682,   371,     0,     0,
       0,    77,     0,   775,     0,     0,   735,     0,   376,   316,
       0,   377,   125,     0,     0,     0,     0,     0,     0,   272,
       0,     0,     0,     0,     0,   479,     0,   108,     0,     0,
       0,   479,     0,     0,     0,     0,   771,   772,     0,     0,
       0,   773,     0,   365,   366,   367,   368,    77,     0,     0,
       0,     0,    77,   773,   782,   365,   366,   367,   368,   774,
       0,     0,     0,     0,     0,   -57,     0,     0,     0,     0,
       0,   774,    77,   800,     0,     0,   807,     0,   -57,   -57,
     -57,   -57,   -57,   -57,   371,   -57,     0,   423,   424,     0,
     971,     0,   -57,    77,     0,     0,   371,     0,    77,   125,
     426,    77,   362,   363,     0,   -57,   -57,   -57,   -57,   -57,
       0,     0,    78,     0,    78,   126,   126,     0,     0,     0,
       0,     0,     0,   126,     0,   430,   431,   432,   433,   434,
     435,   436,   437,     0,     0,     0,     0,     0,     0,     0,
       0,    77,    77,     0,     0,     0,     0,     0,   364,   222,
     365,   366,   367,   368,     0,     0,     0,     0,    77,     0,
       0,   841,     0,    78,   782,   800,   369,   126,     0,    77,
       0,     0,     0,     0,     0,     0,     0,    77,     0,     0,
     370,   -57,     0,   222,   -57,   -57,     0,    77,     0,     0,
       0,   371,     0,     0,   866,     0,   126,   372,   373,   374,
     375,     0,     0,   735,   316,   -57,     0,     0,     0,   -57,
     423,   424,   -57,     0,   -57,     0,     0,     0,  -626,     0,
      77,     0,     0,   426,     0,   376,     0,     0,   377,     0,
       0,     0,    77,     0,    78,     0,     0,     0,     0,   378,
       0,     0,     0,     0,     0,     0,   125,     0,   125,     0,
       0,   433,   434,   435,   436,   437,     0,     0,    77,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   917,     0,
       0,     0,     0,   682,   920,     0,   272,     0,     0,   682,
     682,     0,     0,     0,   735,   682,   682,     0,   364,     0,
     365,   366,   367,   368,     0,     0,     0,     0,     0,     0,
     364,     0,   365,   366,   367,   368,   369,     0,   222,     0,
       0,   682,   682,   125,   682,   682,     0,     0,   369,   107,
     370,   107,   132,   132,   961,     0,    78,     0,   300,     0,
     237,   371,     0,     0,   789,     0,     0,   372,   373,   374,
     375,     0,     0,   371,     0,     0,     0,   973,   974,   372,
     373,   374,   375,     0,     0,     0,     0,     0,     0,     0,
     979,   980,     0,     0,     0,   376,     0,     0,   377,     0,
     107,     0,     0,     0,   325,     0,   995,   376,     0,   378,
     377,    77,     0,     0,     0,     0,   997,   998,     0,     0,
       0,     0,     0,   682,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   325,    78,   126,     0,     0,     0,     0,
       0,     0,     0,    78,    78,     0,   682,     0,     0,     0,
       0,    78,     0,     0,   316,     0,     0,     0,     0,     0,
       0,     0,   126,     0,     0,   364,     0,   365,   366,   367,
     368,   107,     0,   104,     0,   104,   131,   131,   131,     0,
       0,     0,     0,   369,   236,     0,     0,   364,     0,   365,
     366,   367,   368,     0,     0,     0,     0,    78,     0,   886,
       0,     0,    78,     0,     0,   369,     0,     0,   371,     0,
       0,     0,     0,     0,   372,   373,   374,   375,     0,     0,
       0,     0,    78,     0,   104,    77,     0,     0,   324,     0,
     371,     0,   125,    77,    77,     0,   372,   373,   374,   375,
      77,   272,   376,    78,     0,   377,    77,    77,    78,   126,
       0,    78,    77,    77,     0,     0,     0,   324,     0,     0,
       0,     0,     0,   107,   376,     0,    77,   377,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    77,    77,
       0,     0,     0,    87,     0,    87,    77,     0,     0,     0,
       0,    78,    78,     0,   233,   104,     0,     0,     0,    77,
      77,     0,     0,     0,     0,     0,     0,     0,    78,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    78,
       0,     0,     0,     0,     0,     0,   125,    78,     0,     0,
       0,   125,     0,     0,    87,     0,     0,    78,     0,     0,
       0,   107,   132,     0,     0,     0,     0,     0,     0,     0,
     107,   107,     0,     0,    77,     0,     0,     0,   107,     0,
       0,     0,     0,     0,    77,    77,     0,     0,   125,   325,
      78,     0,    77,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    78,     0,     0,     0,     0,   104,     0,     0,
       0,     0,     0,     0,     0,     0,   126,     0,   126,     0,
       0,     0,     0,     0,   107,    87,     0,     0,    78,   107,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   107,
       0,    77,     0,    77,     0,     0,    77,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     107,     0,     0,     0,     0,   107,   325,     0,   633,     0,
       0,     0,     0,   126,     0,   104,   131,     0,     0,     0,
       0,     0,     0,     0,   104,   104,     0,     0,     0,     0,
       0,     0,   104,     0,     0,     0,     0,   661,   662,     0,
       0,   663,     0,   324,     0,     0,     0,    87,   633,   633,
       0,     0,     0,     0,     0,     0,   179,   180,   181,   182,
     183,   184,   185,   186,     0,   107,   187,   188,     0,     0,
       0,     0,   189,   190,   191,   192,   107,     0,   104,     0,
       0,    78,     0,   104,   107,     0,   193,   194,   195,   105,
       0,   105,     0,     0,   107,     0,     0,     0,     0,     0,
       0,     0,     0,   104,     0,     0,     0,     0,     0,     0,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
       0,   206,   207,     0,   104,    87,     0,   107,   281,   104,
     324,   209,     0,     0,    87,    87,     0,     0,     0,   107,
     105,     0,    87,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   325,     0,   325,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   107,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    87,   104,
       0,     0,     0,    87,     0,    78,     0,     0,     0,     0,
     104,     0,   126,    78,    78,     0,     0,     0,   104,     0,
      78,   105,     0,    87,     0,     0,    78,    78,   104,     0,
     325,     0,    78,    78,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    87,     0,    78,     0,     0,    87,
       0,     0,   628,     0,     0,     0,     0,     0,    78,    78,
       0,   104,     0,     0,     0,     0,    78,     0,     0,     0,
       0,     0,     0,   104,     0,     0,     0,     0,     0,    78,
      78,     0,     0,     0,     0,     0,     0,   324,     0,   324,
       0,     0,   628,   628,     0,     0,     0,     0,   107,   104,
       0,     0,     0,     0,     0,     0,   126,     0,     0,    87,
       0,   126,     0,   105,     0,     0,     0,     0,     0,     0,
      87,     0,     0,     0,     0,     0,     0,     0,    87,     0,
       0,     0,     0,     0,    78,     0,     0,     0,    87,     0,
       0,     0,     0,     0,    78,    78,     0,     0,   126,     0,
       0,     0,    78,     0,   324,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    87,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    87,     0,     0,     0,     0,     0,     0,
       0,   105,     0,     0,     0,     0,     0,     0,     0,     0,
     105,   105,     0,     0,     0,     0,     0,     0,   105,    87,
       0,    78,   107,    78,     0,     0,    78,     0,     0,   325,
     107,   633,   104,     0,     0,     0,     0,   633,     0,     0,
       0,     0,     0,   633,   633,     0,     0,     0,     0,   107,
     107,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   107,   105,     0,     0,     0,     0,   105,
       0,     0,     0,     0,     0,   107,   107,  -627,  -627,  -627,
    -627,   415,   416,   107,     0,  -627,  -627,     0,     0,   105,
       0,     0,     0,   423,   424,     0,   107,   107,     0,     0,
       0,     0,     0,     0,     0,     0,   426,     0,     0,     0,
     105,     0,     0,     0,     0,   105,     0,     0,   105,     0,
       0,     0,     0,   132,     0,     0,     0,     0,   132,   428,
     429,   430,   431,   432,   433,   434,   435,   436,   437,     0,
       0,     0,    87,     0,     0,     0,   104,     0,     0,     0,
       0,   633,     0,   324,   104,     0,     0,     0,   105,   105,
       0,   107,   107,     0,     0,  1009,     0,     0,     0,   107,
       0,     0,     0,   104,   104,   105,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   105,   104,     0,     0,
       0,     0,     0,     0,   105,     0,     0,     0,     0,   104,
     104,     0,     0,     0,   105,     0,     0,   104,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     104,   104,     0,     0,     0,     0,     0,     0,   107,     0,
     107,     0,     0,   107,     0,     0,     0,   105,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   131,     0,   105,
       0,     0,   131,     0,     0,     0,    87,     0,     0,     0,
       0,     0,     0,     0,    87,   628,     0,     0,     0,     0,
       0,   628,     0,     0,     0,   105,     0,   628,   628,     0,
       0,     0,     0,    87,    87,   104,   104,     0,     0,  1008,
       0,     0,     0,   104,     0,     0,     0,    87,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    87,
      87,     0,     0,     0,     0,     0,     0,    87,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      87,    87,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -299,
       0,     0,   104,     0,   104,     0,     0,   104,     0,     0,
       0,     0,  -299,  -299,  -299,  -299,  -299,  -299,     0,  -299,
       0,     0,     0,     0,     0,     0,  -299,  -299,  -299,     0,
       0,     0,     0,     0,     0,   628,  -299,  -299,     0,  -299,
    -299,  -299,  -299,  -299,     0,    87,    87,     0,   105,  1006,
       0,     0,     0,    87,     0,     0,     0,  -299,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,
    -299,  -299,  -299,  -299,     0,     0,     0,     0,  -299,  -299,
    -299,     0,     0,  -299,     0,     0,     0,     0,     0,  -299,
       0,  -299,     0,     0,     0,  -299,     0,     0,     0,     0,
       0,     0,    87,  -299,    87,  -299,     0,    87,  -299,  -299,
       0,     0,  -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,
    -299,  -299,  -299,  -299,     0,     0,     0,     0,  -626,  -299,
    -299,  -299,     0,  -299,  -299,     0,  -299,  -299,  -299,     0,
       0,  -626,  -626,  -626,  -626,  -626,  -626,     0,  -626,     0,
       0,     0,   105,     0,  -626,  -626,     0,     0,     0,     0,
     105,   105,     0,     0,     0,  -626,  -626,   105,  -626,  -626,
    -626,  -626,  -626,   105,   105,     0,     0,     0,     0,   105,
     105,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   105,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   105,   105,     0,     0,     0,
       0,     0,     0,   105,     0,     0,     0,     0,     0,  -626,
       0,     0,     0,     0,   814,     0,   105,   105,     0,     0,
       0,     0,     0,     0,  -626,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -626,     0,     0,  -626,  -626,     0,
       0,     0,     0,   411,   412,   413,   414,   415,   416,   417,
     418,   419,   420,   421,   422,     0,     0,  -626,  -626,   423,
     424,   281,  -626,     0,     0,  -626,  -626,  -626,     0,     0,
       0,   105,   426,     0,     0,     0,     0,     0,     0,     0,
       0,   105,   105,     0,     0,     0,     0,     0,     0,   105,
       0,     0,     0,   427,     0,   428,   429,   430,   431,   432,
     433,   434,   435,   436,   437,     0,     0,     0,     0,     0,
    -626,     3,     0,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,     0,     0,     0,     0,     0,     0,    14,
       0,    15,    16,    17,    18,     0,     0,     0,     0,     0,
      19,    20,    21,    22,    23,    24,    25,     0,   105,    26,
     105,     0,     0,   105,     0,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,     0,    40,
      41,    42,     0,     0,    43,     0,     0,    44,    45,     0,
      46,    47,    48,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    49,    50,     0,     0,     0,
       0,     0,    51,     0,     0,    52,    53,     0,    54,    55,
       0,    56,     0,     0,     0,    57,     0,    58,    59,    60,
       0,    61,    62,    63,  -420,    64,  -626,     0,     0,  -626,
    -626,     0,     0,     0,     0,     0,     0,  -420,  -420,  -420,
    -420,  -420,  -420,     0,  -420,    65,    66,    67,     0,     0,
    -420,  -420,  -420,     0,     0,     0,     0,  -626,     0,  -626,
       0,  -420,  -420,     0,  -420,  -420,  -420,  -420,  -420,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -420,  -420,  -420,
    -420,  -420,  -420,  -420,  -420,  -420,  -420,  -420,  -420,     0,
       0,     0,     0,  -420,  -420,  -420,     0,     0,  -420,     0,
       0,     0,     0,     0,  -420,     0,  -420,     0,     0,     0,
    -420,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -420,     0,     0,  -420,  -420,     0,     0,  -420,     0,  -420,
    -420,  -420,  -420,  -420,  -420,  -420,  -420,  -420,  -420,     0,
       0,  -487,     0,  -420,  -420,  -420,  -420,   281,  -420,  -420,
       0,  -420,  -420,  -420,  -487,  -487,  -487,  -487,  -487,  -487,
       0,  -487,     0,     0,     0,     0,     0,     0,  -487,  -487,
       0,     0,     0,     0,     0,     0,     0,     0,  -487,  -487,
       0,  -487,  -487,  -487,  -487,  -487,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   503,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -487,  -487,  -487,  -487,  -487,  -487,
    -487,  -487,  -487,  -487,  -487,  -487,     0,     0,     0,     0,
    -487,  -487,  -487,     0,  -487,  -487,     0,     0,     0,     0,
       0,  -487,     0,  -487,     0,     0,     0,  -487,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -487,     0,     0,
    -487,  -487,     0,  -487,  -487,     0,  -487,  -487,  -487,  -487,
    -487,  -487,  -487,  -487,  -487,  -487,     0,     0,  -626,     0,
       0,  -487,  -487,  -487,     0,  -487,  -487,     0,  -487,  -487,
    -487,  -626,  -626,  -626,  -626,  -626,  -626,     0,  -626,     0,
       0,     0,     0,     0,  -626,  -626,  -626,     0,     0,     0,
       0,     0,     0,     0,     0,  -626,  -626,     0,  -626,  -626,
    -626,  -626,  -626,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -626,  -626,  -626,  -626,  -626,  -626,  -626,  -626,  -626,
    -626,  -626,  -626,     0,     0,     0,     0,  -626,  -626,  -626,
       0,     0,  -626,     0,     0,     0,     0,     0,  -626,     0,
    -626,     0,     0,     0,  -626,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -626,     0,     0,  -626,  -626,     0,
       0,  -626,     0,  -626,  -626,  -626,  -626,  -626,  -626,  -626,
    -626,  -626,  -626,     0,     0,  -626,     0,  -626,  -626,  -626,
    -626,   281,  -626,  -626,     0,  -626,  -626,  -626,  -626,  -626,
    -626,  -626,  -626,  -626,     0,  -626,     0,     0,     0,     0,
       0,     0,  -626,  -626,     0,     0,     0,     0,     0,     0,
       0,     0,  -626,  -626,     0,  -626,  -626,  -626,  -626,  -626,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -626,  -626,
    -626,  -626,  -626,  -626,  -626,  -626,  -626,  -626,  -626,  -626,
       0,     0,     0,     0,  -626,  -626,  -626,     0,     0,  -626,
       0,     0,     0,     0,     0,  -626,     0,  -626,     0,     0,
       0,  -626,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -626,     0,     0,  -626,  -626,     0,     0,  -626,     0,
    -626,  -626,  -626,  -626,  -626,  -626,  -626,  -626,  -626,  -626,
       0,     0,  -603,     0,     0,  -626,  -626,  -626,   281,  -626,
    -626,     0,  -626,  -626,  -626,  -603,  -603,  -603,     0,  -603,
    -603,     0,  -603,     0,     0,     0,     0,     0,  -603,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -603,
    -603,     0,  -603,  -603,  -603,  -603,  -603,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -603,  -603,  -603,  -603,  -603,
    -603,  -603,  -603,  -603,  -603,  -603,  -603,     0,     0,     0,
       0,  -603,  -603,  -603,     0,   819,  -603,     0,     0,     0,
       0,     0,     0,     0,  -603,     0,     0,     0,  -603,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -603,     0,
       0,  -603,  -603,     0,  -112,  -603,     0,  -603,  -603,  -603,
    -603,  -603,  -603,  -603,  -603,  -603,  -603,     0,     0,  -603,
       0,  -603,  -603,  -603,     0,     0,  -603,  -104,     0,  -603,
    -603,  -603,  -603,  -603,  -603,     0,  -603,  -603,     0,  -603,
       0,     0,     0,     0,     0,  -603,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -603,  -603,     0,  -603,
    -603,  -603,  -603,  -603,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -603,  -603,  -603,  -603,  -603,  -603,  -603,  -603,
    -603,  -603,  -603,  -603,     0,     0,     0,     0,  -603,  -603,
    -603,     0,   819,  -603,     0,     0,     0,     0,     0,     0,
       0,  -603,     0,     0,     0,  -603,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -603,     0,     0,  -603,  -603,
       0,  -112,  -603,     0,  -603,  -603,  -603,  -603,  -603,  -603,
    -603,  -603,  -603,  -603,     0,     0,  -308,     0,  -603,  -603,
    -603,     0,     0,  -603,  -603,     0,  -603,  -603,  -603,  -308,
    -308,  -308,     0,  -308,  -308,     0,  -308,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -308,  -308,     0,  -308,  -308,  -308,  -308,
    -308,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -308,
    -308,  -308,  -308,  -308,  -308,  -308,  -308,  -308,  -308,  -308,
    -308,     0,     0,     0,     0,  -308,  -308,  -308,     0,   820,
    -308,     0,     0,     0,     0,     0,     0,     0,  -308,     0,
       0,     0,  -308,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -308,     0,     0,  -308,  -308,     0,  -114,  -308,
       0,  -308,  -308,  -308,  -308,  -308,  -308,  -308,  -308,  -308,
    -308,     0,     0,  -308,     0,     0,  -308,  -308,     0,     0,
    -308,  -106,     0,  -308,  -308,  -308,  -308,  -308,  -308,     0,
    -308,  -308,     0,  -308,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -308,  -308,     0,  -308,  -308,  -308,  -308,  -308,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -308,  -308,  -308,  -308,
    -308,  -308,  -308,  -308,  -308,  -308,  -308,  -308,     0,     0,
       0,     0,  -308,  -308,  -308,     0,   820,  -308,     0,     0,
       0,     0,     0,     0,     0,  -308,     0,     0,     0,  -308,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -308,
       0,     0,  -308,  -308,     0,  -114,  -308,     0,  -308,  -308,
    -308,  -308,  -308,  -308,  -308,  -308,  -308,  -308,     0,     0,
       0,     0,     0,  -308,  -308,     0,     0,  -308,  -308,     0,
    -308,  -308,  -308,   302,     0,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,  -626,  -626,  -626,     0,     0,
    -626,    14,     0,    15,    16,    17,    18,     0,     0,     0,
       0,     0,    19,    20,    21,    22,    23,    24,    25,     0,
       0,    26,     0,     0,     0,     0,     0,    27,     0,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
       0,    40,    41,    42,     0,     0,    43,     0,     0,    44,
      45,     0,    46,    47,    48,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    49,    50,     0,
       0,     0,     0,     0,    51,     0,     0,    52,    53,     0,
      54,    55,     0,    56,     0,     0,     0,    57,     0,    58,
      59,    60,     0,    61,    62,    63,     0,    64,  -626,     0,
       0,  -626,  -626,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    65,    66,    67,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -626,
     302,  -626,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,     0,     0,  -626,     0,  -626,  -626,    14,     0,
      15,    16,    17,    18,     0,     0,     0,     0,     0,    19,
      20,    21,    22,    23,    24,    25,     0,     0,    26,     0,
       0,     0,     0,     0,    27,     0,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,     0,    40,    41,
      42,     0,     0,    43,     0,     0,    44,    45,     0,    46,
      47,    48,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    49,    50,     0,     0,     0,     0,
       0,    51,     0,     0,    52,    53,     0,    54,    55,     0,
      56,     0,     0,     0,    57,     0,    58,    59,    60,     0,
      61,    62,    63,     0,    64,  -626,     0,     0,  -626,  -626,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    65,    66,    67,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -626,   302,  -626,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,     0,
       0,  -626,     0,     0,  -626,    14,  -626,    15,    16,    17,
      18,     0,     0,     0,     0,     0,    19,    20,    21,    22,
      23,    24,    25,     0,     0,    26,     0,     0,     0,     0,
       0,    27,     0,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,     0,    40,    41,    42,     0,     0,
      43,     0,     0,    44,    45,     0,    46,    47,    48,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    49,    50,     0,     0,     0,     0,     0,    51,     0,
       0,    52,    53,     0,    54,    55,     0,    56,     0,     0,
       0,    57,     0,    58,    59,    60,     0,    61,    62,    63,
       0,    64,  -626,     0,     0,  -626,  -626,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    65,    66,    67,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -626,   302,  -626,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,     0,     0,  -626,     0,
       0,  -626,    14,     0,    15,    16,    17,    18,     0,     0,
       0,     0,     0,    19,    20,    21,    22,    23,    24,    25,
       0,     0,    26,     0,     0,     0,     0,     0,    27,     0,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,     0,    40,    41,    42,     0,     0,    43,     0,     0,
      44,    45,     0,    46,    47,    48,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    49,    50,
       0,     0,     0,     0,     0,    51,     0,     0,    52,    53,
       0,    54,    55,     0,    56,     0,     0,     0,    57,     0,
      58,    59,    60,     0,    61,    62,    63,     0,    64,  -626,
       0,     0,  -626,  -626,     3,     0,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,     0,     0,    65,    66,
      67,     0,    14,     0,    15,    16,    17,    18,     0,     0,
    -626,     0,  -626,    19,    20,    21,    22,    23,    24,    25,
       0,     0,    26,     0,     0,     0,     0,     0,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,     0,    40,    41,    42,     0,     0,    43,     0,     0,
      44,    45,     0,    46,    47,    48,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    49,    50,
       0,     0,     0,     0,     0,    51,     0,     0,    52,    53,
       0,    54,    55,     0,    56,     0,     0,     0,    57,     0,
      58,    59,    60,     0,    61,    62,    63,     0,    64,  -626,
       0,     0,  -626,  -626,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    65,    66,
      67,     0,     0,  -626,     0,     0,     0,     0,     0,     0,
    -626,   302,  -626,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,     0,  -626,  -626,     0,     0,     0,    14,
       0,    15,    16,    17,    18,     0,     0,     0,     0,     0,
      19,    20,    21,    22,    23,    24,    25,     0,     0,    26,
       0,     0,     0,     0,     0,    27,     0,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,     0,    40,
      41,    42,     0,     0,    43,     0,     0,    44,    45,     0,
      46,    47,    48,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    49,    50,     0,     0,     0,
       0,     0,    51,     0,     0,    52,    53,     0,    54,    55,
       0,    56,     0,     0,     0,    57,     0,    58,    59,    60,
       0,    61,    62,    63,     0,    64,  -626,     0,     0,  -626,
    -626,   302,     0,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,     0,     0,    65,    66,    67,     0,    14,
       0,    15,    16,    17,    18,     0,     0,  -626,     0,  -626,
      19,    20,    21,    22,    23,    24,    25,     0,     0,    26,
       0,     0,     0,     0,     0,    27,     0,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,     0,    40,
      41,    42,     0,     0,    43,     0,     0,    44,    45,     0,
      46,    47,    48,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    49,    50,     0,     0,     0,
       0,     0,    51,     0,     0,   303,    53,     0,    54,    55,
       0,    56,     0,     0,     0,    57,     0,    58,    59,    60,
       0,    61,    62,    63,     0,    64,  -626,     0,     0,  -626,
    -626,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    65,    66,    67,     0,     0,
       0,     0,     0,     0,  -626,     0,     0,  -626,   302,  -626,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
       0,     0,     0,     0,     0,     0,    14,     0,    15,    16,
      17,    18,     0,     0,     0,     0,     0,    19,    20,    21,
      22,    23,    24,    25,     0,     0,    26,     0,     0,     0,
       0,     0,    27,     0,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,     0,    40,    41,    42,     0,
       0,    43,     0,     0,    44,    45,     0,    46,    47,    48,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    49,    50,     0,     0,     0,     0,     0,    51,
       0,     0,    52,    53,     0,    54,    55,     0,    56,     0,
       0,     0,    57,     0,    58,    59,    60,     0,    61,    62,
      63,     0,    64,  -626,     0,     0,  -626,  -626,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    65,    66,    67,     0,     0,     0,     0,     0,
       0,  -626,     0,     0,  -626,   302,  -626,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,     0,     0,     0,
       0,     0,     0,    14,     0,    15,    16,    17,    18,     0,
       0,     0,     0,     0,    19,    20,    21,    22,    23,    24,
      25,     0,     0,    26,     0,     0,     0,     0,     0,    27,
       0,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,     0,    40,    41,    42,     0,     0,    43,     0,
       0,    44,    45,     0,    46,    47,    48,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    49,
      50,     0,     0,     0,     0,     0,    51,     0,     0,    52,
      53,     0,    54,    55,     0,    56,     0,     0,     0,    57,
       0,    58,    59,    60,     0,    61,    62,    63,     0,    64,
    -626,     0,     0,  -626,  -626,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    65,
      66,    67,     0,     0,  -626,     0,     0,     0,     0,     0,
       0,  -626,   302,  -626,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,     0,     0,  -626,     0,     0,     0,
      14,     0,    15,    16,    17,    18,     0,     0,     0,     0,
       0,    19,    20,    21,    22,    23,    24,    25,     0,     0,
      26,     0,     0,     0,     0,     0,    27,     0,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,     0,
      40,    41,    42,     0,     0,    43,     0,     0,    44,    45,
       0,    46,    47,    48,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    49,    50,     0,     0,
       0,     0,     0,    51,     0,     0,    52,    53,     0,    54,
      55,     0,    56,     0,     0,     0,    57,     0,    58,    59,
      60,     0,    61,    62,    63,     0,    64,  -626,     0,     0,
    -626,  -626,     0,     0,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,     0,     0,    65,    66,    67,     0,
      14,     0,    15,    16,    17,    18,     0,     0,  -626,     0,
    -626,    19,    20,    21,    22,    23,    24,    25,     0,     0,
      26,     0,     0,     0,     0,     0,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,     0,
      40,    41,    42,     0,     0,    43,     0,     0,    44,    45,
       0,    46,    47,    48,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    49,    50,     0,     0,
       0,     0,     0,    51,     0,     0,    52,    53,     0,    54,
      55,     0,    56,     0,     0,     0,    57,     0,    58,    59,
      60,     0,    61,    62,    63,     0,    64,   252,     0,     0,
     253,   254,     0,     0,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,     0,     0,    65,    66,    67,     0,
      14,     0,    15,    16,    17,    18,     0,     0,   255,     0,
     256,    19,    20,    21,    22,    23,    24,    25,     0,     0,
      26,     0,     0,     0,     0,     0,    27,     0,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,     0,
      40,    41,    42,     0,     0,    43,     0,     0,    44,    45,
       0,    46,    47,    48,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    49,    50,     0,     0,
       0,     0,     0,    51,     0,     0,    52,    53,     0,    54,
      55,     0,    56,     0,     0,     0,    57,     0,    58,    59,
      60,     0,    61,    62,    63,     0,    64,   252,     0,     0,
     253,   254,     0,     0,     4,     5,     6,     7,     8,     9,
      10,    11,    12,     0,     0,     0,    65,    66,    67,     0,
      14,     0,    15,    16,    17,    18,     0,     0,   255,     0,
     256,    19,    20,    21,    22,    23,    24,    25,     0,     0,
      26,     0,     0,     0,     0,     0,     0,     0,     0,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,     0,
      40,    41,    42,     0,     0,    43,     0,     0,    44,    45,
       0,    46,    47,    48,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    49,    50,     0,     0,
       0,     0,     0,   216,     0,     0,   123,    53,     0,    54,
      55,     0,     0,     0,     0,     0,    57,     0,    58,    59,
      60,     0,    61,    62,    63,     0,    64,   252,     0,     0,
     253,   254,     0,     0,     4,     5,     6,     7,     8,     9,
      10,    11,    12,     0,     0,     0,    65,    66,    67,     0,
      14,     0,    15,    16,    17,    18,     0,     0,   255,     0,
     256,    19,    20,    21,    22,    23,    24,    25,     0,     0,
      26,     0,     0,     0,     0,     0,     0,     0,     0,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,     0,
      40,    41,    42,     0,     0,    43,     0,     0,    44,    45,
       0,    46,    47,    48,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    49,    50,     0,     0,
       0,     0,     0,   216,     0,     0,   123,    53,     0,    54,
      55,     0,     0,     0,     0,     0,    57,     0,    58,    59,
      60,     0,    61,    62,    63,     0,    64,   252,     0,     0,
     253,   254,     0,     0,     4,     5,     6,     7,     8,     9,
      10,    11,    12,     0,     0,     0,    65,    66,    67,     0,
      14,     0,   112,   113,    17,    18,     0,     0,     0,     0,
     256,   114,   115,   116,    22,    23,    24,    25,     0,     0,
     117,     0,     0,     0,     0,     0,     0,     0,     0,    30,
      31,    32,     0,    34,    35,    36,    37,    38,    39,     0,
      40,    41,    42,     0,     0,    43,     0,     0,    44,    45,
       0,    46,    47,    48,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    49,    50,     0,     0,
       0,     0,     0,   216,     0,     0,   123,    53,     0,    54,
      55,     0,     0,     0,     0,     0,    57,     0,    58,    59,
      60,     0,    61,    62,    63,     0,    64,   252,     0,     0,
     253,   254,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    65,   270,    67,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   255,     0,
     256,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,     0,     0,     0,   159,   160,
     161,   238,   239,   240,   241,   166,   167,   168,     0,     0,
       0,     0,     0,   169,   170,   171,   242,   243,   244,   175,
     245,   177,   327,   328,   246,   329,     0,     0,     0,     0,
       0,     0,   330,     0,     0,     0,     0,     0,   331,   179,
     180,   181,   182,   183,   184,   185,   186,     0,     0,   187,
     188,     0,     0,     0,     0,   189,   190,   191,   192,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   193,
     194,   195,     0,     0,     0,     0,   332,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,     0,   206,   207,     0,     0,     0,     0,
       0,     0,     0,     0,   209,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,     0,
       0,     0,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,     0,     0,     0,     0,     0,   169,   170,   171,
     172,   173,   174,   175,   176,   177,    36,    37,   178,    39,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   120,   179,   180,   181,   182,   183,   184,   185,
     186,     0,     0,   187,   188,     0,     0,     0,     0,   189,
     190,   191,   192,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   193,   194,   195,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,     0,   206,   207,
       0,     0,     0,     0,     0,   208,     0,     0,   209,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,     0,     0,     0,   159,   160,   161,   238,
     239,   240,   241,   166,   167,   168,     0,     0,     0,     0,
       0,   169,   170,   171,   242,   243,   244,   175,   245,   177,
     327,   328,   246,   329,     0,     0,     0,     0,     0,     0,
     330,     0,     0,     0,     0,     0,     0,   179,   180,   181,
     182,   183,   184,   185,   186,     0,     0,   187,   188,     0,
       0,     0,     0,   189,   190,   191,   192,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   193,   194,   195,
       0,     0,     0,     0,   494,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,     0,   206,   207,     0,     0,     0,     0,     0,     0,
       0,     0,   209,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,     0,     0,     0,
     159,   160,   161,   238,   239,   240,   241,   166,   167,   168,
       0,     0,     0,     0,     0,   169,   170,   171,   242,   243,
     244,   175,   245,   177,     0,     0,   246,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   179,   180,   181,   182,   183,   184,   185,   186,     0,
       0,   187,   188,     0,     0,     0,     0,   189,   190,   191,
     192,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   193,   194,   195,     0,     0,     0,   247,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,     0,   206,   207,     0,     0,
       0,     0,     0,     0,     0,     0,   209,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,     0,     0,     0,   159,   160,   161,   238,   239,   240,
     241,   166,   167,   168,     0,     0,     0,     0,     0,   169,
     170,   171,   242,   243,   244,   175,   245,   177,     0,     0,
     246,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   179,   180,   181,   182,   183,
     184,   185,   186,     0,     0,   187,   188,     0,     0,     0,
       0,   189,   190,   191,   192,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   193,   194,   195,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,     0,
     206,   207,     0,     0,     0,     0,     0,     0,     0,     0,
     209,     4,     5,     6,     7,     8,     9,    10,    11,    12,
       0,     0,     0,     0,     0,     0,     0,    14,     0,   112,
     113,    17,    18,     0,     0,     0,     0,     0,   114,   115,
     116,    22,    23,    24,    25,     0,     0,   117,     0,     0,
       0,     0,     0,     0,     0,     0,    30,    31,    32,     0,
      34,    35,    36,    37,    38,    39,     0,    40,    41,    42,
       0,     0,    43,     0,     0,    44,    45,     0,   120,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     320,     0,     0,   123,    53,     0,    54,    55,     0,     0,
       0,     0,     0,    57,     0,    58,    59,    60,     0,    61,
      62,    63,     0,    64,     0,     0,     0,     0,     4,     5,
       6,     7,     8,     9,    10,    11,    12,     0,     0,     0,
       0,     0,     0,   124,    14,     0,   112,   113,    17,    18,
       0,     0,     0,   321,     0,   114,   115,   116,    22,    23,
      24,    25,     0,     0,   117,     0,     0,     0,     0,     0,
       0,     0,     0,    30,    31,    32,     0,    34,    35,    36,
      37,    38,    39,     0,    40,    41,    42,     0,     0,    43,
       0,     0,    44,    45,     0,   120,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   320,     0,     0,
     123,    53,     0,    54,    55,     0,     0,     0,     0,     0,
      57,     0,    58,    59,    60,     0,    61,    62,    63,     0,
      64,     0,     0,     0,     0,  -596,  -596,  -596,  -596,  -596,
    -596,  -596,  -596,  -596,     0,     0,     0,     0,     0,     0,
     124,  -596,     0,  -596,  -596,  -596,  -596,     0,  -596,     0,
     622,     0,  -596,  -596,  -596,  -596,  -596,  -596,  -596,     0,
       0,  -596,     0,     0,     0,     0,     0,     0,     0,     0,
    -596,  -596,  -596,     0,  -596,  -596,  -596,  -596,  -596,  -596,
       0,  -596,  -596,  -596,     0,     0,  -596,     0,     0,  -596,
    -596,     0,  -596,  -596,  -596,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -596,  -596,     0,
       0,     0,     0,     0,  -596,     0,     0,  -596,  -596,     0,
    -596,  -596,     0,  -596,     0,  -596,  -596,  -596,     0,  -596,
    -596,  -596,     0,  -596,  -596,  -596,     0,  -596,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -597,  -597,
    -597,  -597,  -597,  -597,  -597,  -597,  -597,  -596,  -596,  -596,
       0,  -596,     0,     0,  -597,  -596,  -597,  -597,  -597,  -597,
       0,  -597,     0,     0,     0,  -597,  -597,  -597,  -597,  -597,
    -597,  -597,     0,     0,  -597,     0,     0,     0,     0,     0,
       0,     0,     0,  -597,  -597,  -597,     0,  -597,  -597,  -597,
    -597,  -597,  -597,     0,  -597,  -597,  -597,     0,     0,  -597,
       0,     0,  -597,  -597,     0,  -597,  -597,  -597,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -597,  -597,     0,     0,     0,     0,     0,  -597,     0,     0,
    -597,  -597,     0,  -597,  -597,     0,  -597,     0,  -597,  -597,
    -597,     0,  -597,  -597,  -597,     0,  -597,  -597,  -597,     0,
    -597,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -599,  -599,  -599,  -599,  -599,  -599,  -599,  -599,  -599,
    -597,  -597,  -597,     0,  -597,     0,     0,  -599,  -597,  -599,
    -599,  -599,  -599,     0,     0,     0,     0,     0,  -599,  -599,
    -599,  -599,  -599,  -599,  -599,     0,     0,  -599,     0,     0,
       0,     0,     0,     0,     0,     0,  -599,  -599,  -599,     0,
    -599,  -599,  -599,  -599,  -599,  -599,     0,  -599,  -599,  -599,
       0,     0,  -599,     0,     0,  -599,  -599,     0,  -599,  -599,
    -599,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -599,  -599,     0,     0,     0,     0,     0,
    -599,   851,     0,  -599,  -599,     0,  -599,  -599,     0,  -599,
       0,  -599,  -599,  -599,     0,  -599,  -599,  -599,     0,  -599,
    -599,  -599,     0,  -599,     0,     0,     0,     0,     0,     0,
    -112,     0,     0,     0,  -600,  -600,  -600,  -600,  -600,  -600,
    -600,  -600,  -600,  -599,  -599,  -599,     0,     0,     0,     0,
    -600,  -599,  -600,  -600,  -600,  -600,     0,     0,     0,     0,
       0,  -600,  -600,  -600,  -600,  -600,  -600,  -600,     0,     0,
    -600,     0,     0,     0,     0,     0,     0,     0,     0,  -600,
    -600,  -600,     0,  -600,  -600,  -600,  -600,  -600,  -600,     0,
    -600,  -600,  -600,     0,     0,  -600,     0,     0,  -600,  -600,
       0,  -600,  -600,  -600,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -600,  -600,     0,     0,
       0,     0,     0,  -600,   852,     0,  -600,  -600,     0,  -600,
    -600,     0,  -600,     0,  -600,  -600,  -600,     0,  -600,  -600,
    -600,     0,  -600,  -600,  -600,     0,  -600,     0,     0,     0,
       0,     0,     0,  -114,     0,     0,     0,  -601,  -601,  -601,
    -601,  -601,  -601,  -601,  -601,  -601,  -600,  -600,  -600,     0,
       0,     0,     0,  -601,  -600,  -601,  -601,  -601,  -601,     0,
       0,     0,     0,     0,  -601,  -601,  -601,  -601,  -601,  -601,
    -601,     0,     0,  -601,     0,     0,     0,     0,     0,     0,
       0,     0,  -601,  -601,  -601,     0,  -601,  -601,  -601,  -601,
    -601,  -601,     0,  -601,  -601,  -601,     0,     0,  -601,     0,
       0,  -601,  -601,     0,  -601,  -601,  -601,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -601,
    -601,     0,     0,     0,     0,     0,  -601,     0,     0,  -601,
    -601,     0,  -601,  -601,     0,  -601,     0,  -601,  -601,  -601,
       0,  -601,  -601,  -601,     0,  -601,  -601,  -601,     0,  -601,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -602,  -601,
    -601,  -601,     0,     0,     0,     0,  -602,  -601,  -602,  -602,
    -602,  -602,     0,     0,     0,     0,     0,  -602,  -602,  -602,
    -602,  -602,  -602,  -602,     0,     0,  -602,     0,     0,     0,
       0,     0,     0,     0,     0,  -602,  -602,  -602,     0,  -602,
    -602,  -602,  -602,  -602,  -602,     0,  -602,  -602,  -602,     0,
       0,  -602,     0,     0,  -602,  -602,     0,  -602,  -602,  -602,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -602,  -602,     0,     0,     0,     0,     0,  -602,
       0,     0,  -602,  -602,     0,  -602,  -602,     0,  -602,     0,
    -602,  -602,  -602,     0,  -602,  -602,  -602,     0,  -602,  -602,
    -602,     0,  -602,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     4,     5,     6,     7,     8,     9,    10,
      11,    12,  -602,  -602,  -602,     0,     0,     0,     0,    14,
    -602,    15,    16,    17,    18,     0,     0,     0,     0,     0,
      19,    20,    21,    22,    23,    24,    25,     0,     0,    26,
       0,     0,     0,     0,     0,     0,     0,     0,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,     0,    40,
      41,    42,     0,     0,    43,     0,     0,    44,    45,     0,
      46,    47,    48,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    49,    50,     0,     0,     0,
       0,     0,   216,     0,     0,   123,    53,     0,    54,    55,
       0,     0,     0,     0,     0,    57,     0,    58,    59,    60,
       0,    61,    62,    63,     0,    64,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    65,    66,    67,     0,     0,
       0,     0,     0,   294,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,     0,     0,     0,     0,     0,     0,
      14,     0,    15,    16,    17,    18,     0,     0,     0,     0,
       0,    19,    20,    21,    22,    23,    24,    25,     0,     0,
      26,     0,     0,     0,     0,     0,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,     0,
      40,    41,    42,     0,     0,    43,     0,     0,    44,    45,
       0,    46,    47,    48,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    49,    50,     0,     0,
       0,     0,     0,    51,     0,     0,    52,    53,     0,    54,
      55,     0,    56,     0,     0,     0,    57,     0,    58,    59,
      60,     0,    61,    62,    63,     0,    64,     0,     0,     0,
       0,     0,     0,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,     0,     0,     0,    65,    66,    67,    14,
       0,    15,    16,    17,    18,     0,     0,     0,     0,     0,
      19,    20,    21,    22,    23,    24,    25,     0,     0,    26,
       0,     0,     0,     0,     0,    27,     0,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,     0,    40,
      41,    42,     0,     0,    43,     0,     0,    44,    45,     0,
      46,    47,    48,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    49,    50,     0,     0,     0,
       0,     0,    51,     0,     0,    52,    53,     0,    54,    55,
       0,    56,     0,     0,     0,    57,     0,    58,    59,    60,
       0,    61,    62,    63,     0,    64,     0,     0,     0,     0,
       0,     0,     4,     5,     6,     7,     8,     9,    10,    11,
      12,     0,     0,     0,     0,    65,    66,    67,    14,     0,
      15,    16,    17,    18,     0,     0,     0,     0,     0,    19,
      20,    21,    22,    23,    24,    25,     0,     0,   117,     0,
       0,     0,     0,     0,     0,     0,     0,    30,    31,    32,
       0,   265,    35,    36,    37,    38,    39,     0,    40,    41,
      42,     0,     0,    43,     0,     0,    44,    45,     0,   266,
      47,    48,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    49,    50,     0,     0,     0,     0,
       0,   216,     0,     0,   123,    53,     0,    54,    55,     0,
     267,     0,   268,   269,    57,     0,    58,    59,    60,     0,
      61,    62,    63,     0,    64,     0,     0,     0,     0,     0,
       0,     4,     5,     6,     7,     8,     9,    10,    11,    12,
       0,     0,     0,     0,    65,   270,    67,    14,     0,    15,
      16,    17,    18,     0,     0,     0,     0,     0,    19,    20,
      21,    22,    23,    24,    25,     0,     0,   117,     0,     0,
       0,     0,     0,     0,     0,     0,    30,    31,    32,     0,
     265,    35,    36,    37,    38,    39,     0,    40,    41,    42,
       0,     0,    43,     0,     0,    44,    45,     0,   266,    47,
      48,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    49,   516,     0,     0,     0,     0,     0,
     216,     0,     0,   123,    53,     0,    54,    55,     0,   267,
       0,   268,   269,    57,     0,    58,    59,    60,     0,    61,
      62,    63,     0,    64,     0,     0,     0,     0,     0,     0,
       4,     5,     6,     7,     8,     9,    10,    11,    12,     0,
       0,     0,     0,    65,   270,    67,    14,     0,   112,   113,
      17,    18,     0,     0,     0,     0,     0,   114,   115,   116,
      22,    23,    24,    25,     0,     0,   117,     0,     0,     0,
       0,     0,     0,     0,     0,    30,    31,    32,     0,   265,
      35,    36,    37,    38,    39,     0,    40,    41,    42,     0,
       0,    43,     0,     0,    44,    45,     0,   266,    47,    48,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    49,    50,     0,     0,     0,     0,     0,   216,
       0,     0,   123,    53,     0,    54,    55,     0,   734,     0,
     268,   269,    57,     0,    58,    59,    60,     0,    61,    62,
      63,     0,    64,     0,     0,     0,     0,     0,     0,     4,
       5,     6,     7,     8,     9,    10,    11,    12,     0,     0,
       0,     0,    65,   270,    67,    14,     0,   112,   113,    17,
      18,     0,     0,     0,     0,     0,   114,   115,   116,    22,
      23,    24,    25,     0,     0,   117,     0,     0,     0,     0,
       0,     0,     0,     0,    30,    31,    32,     0,   265,    35,
      36,    37,    38,    39,     0,    40,    41,    42,     0,     0,
      43,     0,     0,    44,    45,     0,   266,    47,    48,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    49,   868,     0,     0,     0,     0,     0,   216,     0,
       0,   123,    53,     0,    54,    55,     0,   734,     0,   268,
     269,    57,     0,    58,    59,    60,     0,    61,    62,    63,
       0,    64,     0,     0,     0,     0,     0,     0,     4,     5,
       6,     7,     8,     9,    10,    11,    12,     0,     0,     0,
       0,    65,   270,    67,    14,     0,   112,   113,    17,    18,
       0,     0,     0,     0,     0,   114,   115,   116,    22,    23,
      24,    25,     0,     0,   117,     0,     0,     0,     0,     0,
       0,     0,     0,    30,    31,    32,     0,   265,    35,    36,
      37,    38,    39,     0,    40,    41,    42,     0,     0,    43,
       0,     0,    44,    45,     0,   266,    47,    48,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      49,    50,     0,     0,     0,     0,     0,   216,     0,     0,
     123,    53,     0,    54,    55,     0,   267,     0,   268,     0,
      57,     0,    58,    59,    60,     0,    61,    62,    63,     0,
      64,     0,     0,     0,     0,     0,     0,     4,     5,     6,
       7,     8,     9,    10,    11,    12,     0,     0,     0,     0,
      65,   270,    67,    14,     0,   112,   113,    17,    18,     0,
       0,     0,     0,     0,   114,   115,   116,    22,    23,    24,
      25,     0,     0,   117,     0,     0,     0,     0,     0,     0,
       0,     0,    30,    31,    32,     0,   265,    35,    36,    37,
      38,    39,     0,    40,    41,    42,     0,     0,    43,     0,
       0,    44,    45,     0,   266,    47,    48,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    49,
      50,     0,     0,     0,     0,     0,   216,     0,     0,   123,
      53,     0,    54,    55,     0,     0,     0,   268,   269,    57,
       0,    58,    59,    60,     0,    61,    62,    63,     0,    64,
       0,     0,     0,     0,     0,     0,     4,     5,     6,     7,
       8,     9,    10,    11,    12,     0,     0,     0,     0,    65,
     270,    67,    14,     0,   112,   113,    17,    18,     0,     0,
       0,     0,     0,   114,   115,   116,    22,    23,    24,    25,
       0,     0,   117,     0,     0,     0,     0,     0,     0,     0,
       0,    30,    31,    32,     0,   265,    35,    36,    37,    38,
      39,     0,    40,    41,    42,     0,     0,    43,     0,     0,
      44,    45,     0,   266,    47,    48,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    49,    50,
       0,     0,     0,     0,     0,   216,     0,     0,   123,    53,
       0,    54,    55,     0,   734,     0,   268,     0,    57,     0,
      58,    59,    60,     0,    61,    62,    63,     0,    64,     0,
       0,     0,     0,     0,     0,     4,     5,     6,     7,     8,
       9,    10,    11,    12,     0,     0,     0,     0,    65,   270,
      67,    14,     0,    15,    16,    17,    18,     0,     0,     0,
       0,     0,    19,    20,    21,    22,    23,    24,    25,     0,
       0,    26,     0,     0,     0,     0,     0,     0,     0,     0,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
       0,    40,    41,    42,     0,     0,    43,     0,     0,    44,
      45,     0,    46,    47,    48,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    49,    50,     0,
       0,     0,     0,     0,   216,     0,     0,   123,    53,     0,
      54,    55,     0,     0,     0,     0,     0,    57,     0,    58,
      59,    60,     0,    61,    62,    63,     0,    64,     0,     0,
       0,     0,     0,     0,     4,     5,     6,     7,     8,     9,
      10,    11,    12,     0,     0,     0,     0,    65,    66,    67,
      14,     0,   112,   113,    17,    18,     0,     0,     0,     0,
       0,   114,   115,   116,    22,    23,    24,    25,     0,     0,
     117,     0,     0,     0,     0,     0,     0,     0,     0,    30,
      31,    32,     0,   265,    35,    36,    37,    38,    39,     0,
      40,    41,    42,     0,     0,    43,     0,     0,    44,    45,
       0,   266,    47,    48,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    49,    50,     0,     0,
       0,     0,     0,   216,     0,     0,   123,    53,     0,    54,
      55,     0,     0,     0,   268,     0,    57,     0,    58,    59,
      60,     0,    61,    62,    63,     0,    64,     0,     0,     0,
       0,     0,     0,     4,     5,     6,     7,     8,     9,    10,
      11,    12,     0,     0,     0,     0,    65,   270,    67,    14,
       0,    15,    16,    17,    18,     0,     0,     0,     0,     0,
      19,    20,    21,    22,    23,    24,    25,     0,     0,   117,
       0,     0,     0,     0,     0,     0,     0,     0,    30,    31,
      32,     0,    34,    35,    36,    37,    38,    39,     0,    40,
      41,    42,     0,     0,    43,     0,     0,    44,    45,     0,
      46,    47,    48,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    49,    50,     0,     0,     0,
       0,     0,   216,     0,     0,   123,    53,     0,    54,    55,
       0,   616,     0,     0,     0,    57,     0,    58,    59,    60,
       0,    61,    62,    63,     0,    64,     0,     0,     0,     0,
       0,     0,     4,     5,     6,     7,     8,     9,    10,    11,
      12,     0,     0,     0,     0,    65,   270,    67,    14,     0,
     112,   113,    17,    18,     0,     0,     0,     0,     0,   114,
     115,   116,    22,    23,    24,    25,     0,     0,   117,     0,
       0,     0,     0,     0,     0,     0,     0,    30,    31,    32,
       0,    34,    35,    36,    37,    38,    39,     0,    40,    41,
      42,     0,     0,    43,     0,     0,    44,    45,     0,    46,
      47,    48,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    49,    50,     0,     0,     0,     0,
       0,   216,     0,     0,   123,    53,     0,    54,    55,     0,
     267,     0,     0,     0,    57,     0,    58,    59,    60,     0,
      61,    62,    63,     0,    64,     0,     0,     0,     0,     0,
       0,     4,     5,     6,     7,     8,     9,    10,    11,    12,
       0,     0,     0,     0,    65,   270,    67,    14,     0,   112,
     113,    17,    18,     0,     0,     0,     0,     0,   114,   115,
     116,    22,    23,    24,    25,     0,     0,   117,     0,     0,
       0,     0,     0,     0,     0,     0,    30,    31,    32,     0,
      34,    35,    36,    37,    38,    39,     0,    40,    41,    42,
       0,     0,    43,     0,     0,    44,    45,     0,    46,    47,
      48,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    49,    50,     0,     0,     0,     0,     0,
     216,     0,     0,   123,    53,     0,    54,    55,     0,   616,
       0,     0,     0,    57,     0,    58,    59,    60,     0,    61,
      62,    63,     0,    64,     0,     0,     0,     0,     0,     0,
       4,     5,     6,     7,     8,     9,    10,    11,    12,     0,
       0,     0,     0,    65,   270,    67,    14,     0,   112,   113,
      17,    18,     0,     0,     0,     0,     0,   114,   115,   116,
      22,    23,    24,    25,     0,     0,   117,     0,     0,     0,
       0,     0,     0,     0,     0,    30,    31,    32,     0,    34,
      35,    36,    37,    38,    39,     0,    40,    41,    42,     0,
       0,    43,     0,     0,    44,    45,     0,    46,    47,    48,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    49,    50,     0,     0,     0,     0,     0,   216,
       0,     0,   123,    53,     0,    54,    55,     0,   916,     0,
       0,     0,    57,     0,    58,    59,    60,     0,    61,    62,
      63,     0,    64,     0,     0,     0,     0,     0,     0,     4,
       5,     6,     7,     8,     9,    10,    11,    12,     0,     0,
       0,     0,    65,   270,    67,    14,     0,   112,   113,    17,
      18,     0,     0,     0,     0,     0,   114,   115,   116,    22,
      23,    24,    25,     0,     0,   117,     0,     0,     0,     0,
       0,     0,     0,     0,    30,    31,    32,     0,    34,    35,
      36,    37,    38,    39,     0,    40,    41,    42,     0,     0,
      43,     0,     0,    44,    45,     0,    46,    47,    48,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    49,    50,     0,     0,     0,     0,     0,   216,     0,
       0,   123,    53,     0,    54,    55,     0,   734,     0,     0,
       0,    57,     0,    58,    59,    60,     0,    61,    62,    63,
       0,    64,     0,     0,     0,     0,     0,     0,     4,     5,
       6,     7,     8,     9,    10,    11,    12,     0,     0,     0,
       0,    65,   270,    67,    14,     0,   112,   113,    17,    18,
       0,     0,     0,     0,     0,   114,   115,   116,    22,    23,
      24,    25,     0,     0,   117,     0,     0,     0,     0,     0,
       0,     0,     0,    30,    31,    32,     0,    34,    35,    36,
      37,    38,    39,     0,    40,    41,    42,     0,     0,    43,
       0,     0,    44,    45,     0,    46,    47,    48,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      49,    50,     0,     0,     0,     0,     0,   216,     0,     0,
     123,    53,     0,    54,    55,     0,     0,     0,     0,     0,
      57,     0,    58,    59,    60,     0,    61,    62,    63,     0,
      64,     0,     0,     0,     0,     0,     0,     4,     5,     6,
       7,     8,     9,    10,    11,    12,     0,     0,     0,     0,
      65,   270,    67,    14,     0,    15,    16,    17,    18,     0,
       0,     0,     0,     0,    19,    20,    21,    22,    23,    24,
      25,     0,     0,   117,     0,     0,     0,     0,     0,     0,
       0,     0,    30,    31,    32,     0,    34,    35,    36,    37,
      38,    39,     0,    40,    41,    42,     0,     0,    43,     0,
       0,    44,    45,     0,    46,    47,    48,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    49,
      50,     0,     0,     0,     0,     0,   216,     0,     0,   123,
      53,     0,    54,    55,     0,     0,     0,     0,     0,    57,
       0,    58,    59,    60,     0,    61,    62,    63,     0,    64,
       0,     0,     0,     0,     0,     0,     4,     5,     6,     7,
       8,     9,    10,    11,    12,     0,     0,     0,     0,    65,
     270,    67,    14,     0,   112,   113,    17,    18,     0,     0,
       0,     0,     0,   114,   115,   116,    22,    23,    24,    25,
       0,     0,   117,     0,     0,     0,     0,     0,     0,     0,
       0,    30,    31,    32,     0,   118,    35,    36,    37,   119,
      39,     0,    40,    41,    42,     0,     0,    43,     0,     0,
      44,    45,     0,   120,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   121,     0,     0,   122,     0,     0,   123,    53,
       0,    54,    55,     0,     0,     0,     0,     0,    57,     0,
      58,    59,    60,     0,    61,    62,    63,     0,    64,     0,
       0,     4,     5,     6,     7,     8,     9,    10,    11,    12,
       0,     0,     0,     0,     0,     0,     0,    14,   124,   112,
     113,    17,    18,     0,     0,     0,     0,     0,   114,   115,
     116,    22,    23,    24,    25,     0,     0,   117,     0,     0,
       0,     0,     0,     0,     0,     0,    30,    31,    32,     0,
      34,    35,    36,    37,    38,    39,     0,    40,    41,    42,
       0,     0,    43,     0,     0,    44,    45,     0,   230,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     231,     0,     0,    52,    53,     0,    54,    55,     0,    56,
       0,     0,     0,    57,     0,    58,    59,    60,     0,    61,
      62,    63,     0,    64,     0,     0,     4,     5,     6,     7,
       8,     9,    10,    11,    12,     0,     0,     0,     0,     0,
       0,     0,    14,   124,   112,   113,    17,    18,     0,     0,
       0,     0,     0,   114,   115,   116,    22,    23,    24,    25,
       0,     0,   117,     0,     0,     0,     0,     0,     0,     0,
       0,    30,    31,    32,     0,    34,    35,    36,    37,    38,
      39,     0,    40,    41,    42,     0,     0,    43,     0,     0,
      44,    45,     0,   120,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   320,     0,     0,   407,    53,
       0,    54,    55,     0,   408,     0,     0,     0,    57,     0,
      58,    59,    60,     0,    61,    62,    63,     0,    64,     0,
       0,     4,     5,     6,     7,     8,     9,    10,    11,    12,
       0,     0,     0,     0,     0,     0,     0,    14,   124,   112,
     113,    17,    18,     0,     0,     0,     0,     0,   114,   115,
     116,    22,    23,    24,    25,     0,     0,   117,     0,     0,
       0,     0,     0,     0,     0,     0,    30,    31,    32,     0,
     118,    35,    36,    37,   119,    39,     0,    40,    41,    42,
       0,     0,    43,     0,     0,    44,    45,     0,   120,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     122,     0,     0,   123,    53,     0,    54,    55,     0,     0,
       0,     0,     0,    57,     0,    58,    59,    60,     0,    61,
      62,    63,     0,    64,     0,     0,     4,     5,     6,     7,
       8,     9,    10,    11,    12,     0,     0,     0,     0,     0,
       0,     0,    14,   124,   112,   113,    17,    18,     0,     0,
       0,     0,     0,   114,   115,   116,    22,    23,    24,    25,
       0,     0,   117,     0,     0,     0,     0,     0,     0,     0,
       0,    30,    31,    32,     0,    34,    35,    36,    37,    38,
      39,     0,    40,    41,    42,     0,     0,    43,     0,     0,
      44,    45,     0,   120,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   531,     0,     0,   123,    53,
       0,    54,    55,     0,     0,     0,     0,     0,    57,     0,
      58,    59,    60,     0,    61,    62,    63,     0,    64,     0,
       0,     4,     5,     6,     7,     8,     9,    10,    11,    12,
       0,     0,     0,     0,     0,     0,     0,    14,   124,   112,
     113,    17,    18,     0,     0,     0,     0,     0,   114,   115,
     116,    22,    23,    24,    25,     0,     0,   117,     0,     0,
       0,     0,     0,     0,     0,     0,    30,    31,    32,     0,
      34,    35,    36,    37,    38,    39,     0,    40,    41,    42,
       0,     0,    43,     0,     0,    44,    45,     0,   120,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     320,     0,     0,   407,    53,     0,    54,    55,     0,     0,
       0,     0,     0,    57,     0,    58,    59,    60,     0,    61,
      62,    63,     0,    64,     0,     0,     4,     5,     6,     7,
       8,     9,    10,    11,    12,     0,     0,     0,     0,     0,
       0,     0,    14,   124,   112,   113,    17,    18,     0,     0,
       0,     0,     0,   114,   115,   116,    22,    23,    24,    25,
       0,     0,   117,     0,     0,   814,     0,     0,     0,     0,
       0,    30,    31,    32,     0,    34,    35,    36,    37,    38,
      39,     0,    40,    41,    42,     0,     0,    43,     0,     0,
      44,    45,     0,   230,   411,   412,   413,   414,   415,   416,
     417,   418,   419,   420,   421,   422,     0,     0,     0,     0,
     423,   424,     0,     0,     0,  1005,     0,     0,   123,    53,
       0,    54,    55,   426,     0,     0,     0,     0,    57,     0,
      58,    59,    60,     0,    61,    62,    63,     0,    64,     0,
       0,     0,     0,     0,   427,     0,   428,   429,   430,   431,
     432,   433,   434,   435,   436,   437,   670,   671,   124,     0,
     672,     0,     0,     0,     0,     0,  -283,     0,     0,     0,
       0,     0,     0,     0,     0,   179,   180,   181,   182,   183,
     184,   185,   186,     0,     0,   187,   188,     0,     0,     0,
       0,   189,   190,   191,   192,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   193,   194,   195,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,     0,
     206,   207,   691,   662,     0,     0,   692,   281,     0,     0,
     209,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   179,   180,   181,   182,   183,   184,   185,   186,     0,
       0,   187,   188,     0,     0,     0,     0,   189,   190,   191,
     192,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   193,   194,   195,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,     0,   206,   207,   676,   671,
       0,     0,   677,   281,     0,     0,   209,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   179,   180,   181,
     182,   183,   184,   185,   186,     0,     0,   187,   188,     0,
       0,     0,     0,   189,   190,   191,   192,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   193,   194,   195,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,     0,   206,   207,   708,   662,     0,     0,   709,   281,
       0,     0,   209,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   179,   180,   181,   182,   183,   184,   185,
     186,     0,     0,   187,   188,     0,     0,     0,     0,   189,
     190,   191,   192,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   193,   194,   195,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,     0,   206,   207,
     711,   671,     0,     0,   712,   281,     0,     0,   209,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   179,
     180,   181,   182,   183,   184,   185,   186,     0,     0,   187,
     188,     0,     0,     0,     0,   189,   190,   191,   192,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   193,
     194,   195,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,     0,   206,   207,   718,   662,     0,     0,
     719,   281,     0,     0,   209,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   179,   180,   181,   182,   183,
     184,   185,   186,     0,     0,   187,   188,     0,     0,     0,
       0,   189,   190,   191,   192,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   193,   194,   195,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,     0,
     206,   207,   721,   671,     0,     0,   722,   281,     0,     0,
     209,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   179,   180,   181,   182,   183,   184,   185,   186,     0,
       0,   187,   188,     0,     0,     0,     0,   189,   190,   191,
     192,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   193,   194,   195,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,     0,   206,   207,   760,   662,
       0,     0,   761,   281,     0,     0,   209,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   179,   180,   181,
     182,   183,   184,   185,   186,     0,     0,   187,   188,     0,
       0,     0,     0,   189,   190,   191,   192,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   193,   194,   195,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,     0,   206,   207,   763,   671,     0,     0,   764,   281,
       0,     0,   209,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   179,   180,   181,   182,   183,   184,   185,
     186,     0,     0,   187,   188,     0,     0,     0,     0,   189,
     190,   191,   192,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   193,   194,   195,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,     0,   206,   207,
     871,   662,     0,     0,   872,   281,     0,     0,   209,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   179,
     180,   181,   182,   183,   184,   185,   186,     0,     0,   187,
     188,     0,     0,     0,     0,   189,   190,   191,   192,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   193,
     194,   195,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,     0,   206,   207,   921,   662,     0,     0,
     922,   281,     0,     0,   209,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   179,   180,   181,   182,   183,
     184,   185,   186,     0,     0,   187,   188,     0,     0,     0,
       0,   189,   190,   191,   192,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   193,   194,   195,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,     0,
     206,   207,   924,   671,     0,     0,   925,   281,     0,     0,
     209,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   179,   180,   181,   182,   183,   184,   185,   186,     0,
       0,   187,   188,     0,     0,     0,     0,   189,   190,   191,
     192,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   193,   194,   195,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,     0,   206,   207,  1072,   662,
       0,     0,  1073,   281,     0,     0,   209,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   179,   180,   181,
     182,   183,   184,   185,   186,     0,     0,   187,   188,     0,
       0,     0,     0,   189,   190,   191,   192,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   193,   194,   195,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,     0,   206,   207,  1075,   671,     0,     0,  1076,   281,
       0,     0,   209,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   179,   180,   181,   182,   183,   184,   185,
     186,     0,     0,   187,   188,     0,     0,     0,     0,   189,
     190,   191,   192,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   193,   194,   195,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,     0,   206,   207,
     676,   671,     0,     0,   677,   281,     0,     0,   209,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   179,
     180,   181,   182,   183,   184,   185,   186,     0,     0,   187,
     188,     0,     0,     0,     0,   189,   190,   191,   192,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   193,
     194,   195,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   888,     0,     0,     0,
       0,     0,     0,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,     0,   206,   207,     0,     0,     0,     0,
       0,     0,     0,     0,   209,   411,   412,   413,   414,   415,
     416,   417,   418,   419,   420,   421,   422,     0,     0,     0,
       0,   423,   424,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   426,     0,     0,     0,   901,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   427,     0,   428,   429,   430,
     431,   432,   433,   434,   435,   436,   437,   411,   412,   413,
     414,   415,   416,   417,   418,   419,   420,   421,   422,     0,
       0,     0,     0,   423,   424,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   426,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   427,     0,   428,
     429,   430,   431,   432,   433,   434,   435,   436,   437,   411,
     412,   413,   414,   415,   416,   417,   418,   419,   420,   421,
     422,     0,     0,     0,     0,   423,   424,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   426,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   427,
       0,   428,   429,   430,   431,   432,   433,   434,   435,   436,
     437,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -283,   411,   412,   413,   414,   415,   416,   417,   418,
     419,   420,   421,   422,     0,     0,     0,     0,   423,   424,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   426,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   427,     0,   428,   429,   430,   431,   432,   433,
     434,   435,   436,   437,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -285,   411,   412,   413,   414,   415,
     416,   417,   418,   419,   420,   421,   422,     0,     0,     0,
       0,   423,   424,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   426,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   427,     0,   428,   429,   430,
     431,   432,   433,   434,   435,   436,   437,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -286,   411,   412,
     413,   414,   415,   416,   417,   418,   419,   420,   421,   422,
       0,     0,     0,     0,   423,   424,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   426,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   427,     0,
     428,   429,   430,   431,   432,   433,   434,   435,   436,   437,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -288,   411,   412,   413,   414,   415,   416,   417,   418,   419,
     420,   421,   422,     0,     0,     0,     0,   423,   424,     0,
       0,     0,   425,     0,     0,     0,     0,     0,     0,     0,
     426,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   427,     0,   428,   429,   430,   431,   432,   433,   434,
     435,   436,   437,   411,   412,   413,   414,   415,   416,   417,
     418,   419,   420,   421,   422,     0,     0,     0,     0,   423,
     424,     0,     0,     0,   508,     0,     0,     0,     0,     0,
       0,     0,   426,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   427,     0,   428,   429,   430,   431,   432,
     433,   434,   435,   436,   437,   411,   412,   413,   414,   415,
     416,   417,   418,   419,   420,   421,   422,     0,     0,     0,
       0,   423,   424,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   426,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   427,     0,   428,   429,   430,
     431,   432,   433,   434,   435,   436,   437,   411,   412,   413,
     414,   415,   416,   417,   418,   419,   420,  -627,  -627,     0,
       0,     0,     0,   423,   424,   411,   412,   413,   414,   415,
     416,   417,     0,   419,   420,     0,   426,     0,     0,     0,
       0,   423,   424,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   426,     0,     0,     0,     0,   428,
     429,   430,   431,   432,   433,   434,   435,   436,   437,     0,
       0,     0,     0,     0,     0,     0,     0,   428,   429,   430,
     431,   432,   433,   434,   435,   436,   437,   411,   412,   413,
     414,   415,   416,     0,     0,   419,   420,     0,     0,     0,
       0,     0,     0,   423,   424,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   426,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   428,
     429,   430,   431,   432,   433,   434,   435,   436,   437
};

static const yytype_int16 yycheck[] =
{
       1,    92,    66,   227,     6,   290,    26,    20,    21,    27,
       1,     9,     3,     4,     5,   497,    14,     8,     9,    20,
      69,    12,    85,    14,    15,    16,     6,    52,    19,    13,
     450,   451,   314,    13,   122,   386,   318,    90,    91,    21,
     488,   277,    33,    27,     3,    14,    56,    27,   410,   607,
     339,   321,   604,    54,    55,    78,    58,    60,    61,    62,
      63,    52,    25,   702,   557,    56,    15,    16,    15,    16,
      19,   326,    19,    25,   713,    66,    77,    78,    58,   775,
     303,    25,    25,   511,    15,    16,    25,   515,    19,   679,
     680,    52,   440,   515,    85,   108,    25,     0,   803,    26,
      69,    78,   115,   116,   381,    54,    55,    54,    15,    16,
      26,   143,    19,   990,   115,    15,    16,   465,   966,    19,
     133,    58,    16,   378,    80,   402,   108,   549,   604,   622,
     121,   607,   123,     1,   482,     3,    29,    56,    52,   104,
      27,    25,    56,   491,   438,    18,   822,    20,   442,   126,
     122,   445,   828,    25,    54,    55,    52,    28,    54,    55,
      56,    57,   123,    91,   129,   139,    61,     4,     5,    64,
     223,   127,   466,   145,    70,    12,   275,   122,   277,    91,
     604,   234,   145,   145,   407,   122,  1063,   481,   122,   483,
     467,   143,    26,   145,    94,   218,   219,   395,   492,   397,
     340,   145,   145,   343,   143,   345,   145,   347,  1056,   349,
     410,   559,   139,   108,   313,   767,   145,   218,   219,    56,
     148,   114,   116,   139,   215,   119,   120,   143,   780,   116,
     228,   229,   119,   120,     8,     9,   148,   228,   229,    91,
      14,   535,   219,   833,   297,   247,    58,    93,    85,   145,
     450,   451,   143,   147,   106,   149,   305,    91,   321,    33,
     147,   145,   149,    91,   313,   314,   560,   247,    91,   318,
     323,   126,   106,   145,   275,   971,   277,    56,   303,   568,
     281,    93,   987,   106,   520,   990,   122,   557,   257,   141,
     281,   767,    91,   284,    91,    93,   148,    93,   289,   290,
      16,    93,   293,   294,   780,   139,   561,   141,    56,   143,
     122,   302,   303,    25,   148,   743,   744,    20,   811,   310,
     148,    91,   744,   962,   122,   148,   122,   803,    26,   332,
     321,   145,   293,   891,   281,   284,   305,   284,    91,   701,
     145,   405,   303,   767,    91,    91,   410,   121,    58,   148,
     281,   148,   622,   284,   675,   139,   780,   678,  1063,   357,
     358,   359,   360,    93,   102,   356,   357,   358,   359,   360,
     361,   362,   363,    91,   142,   696,   464,   284,   148,   144,
      91,   281,   407,   384,   284,   386,   450,   451,   106,    93,
     381,   122,   122,    91,    91,   148,   824,   356,   408,   819,
     116,   148,   148,   119,   120,   825,   826,   140,   106,   106,
      56,   402,   860,   690,   405,   891,   407,   408,   122,   410,
     519,   520,   145,   141,   116,   143,   566,   119,   120,   442,
     148,   147,   102,   149,   302,   102,   787,   148,    93,   440,
      93,   139,   310,   141,   141,   326,   407,    58,   733,   440,
     148,   148,   145,   466,   228,   229,    93,   294,   405,   450,
     451,   885,   442,   410,   465,   445,   122,   122,   816,   122,
     483,   895,   473,    93,   465,   757,   467,   468,    93,   492,
     962,   482,    77,    78,   321,   122,   466,   478,   356,   509,
     491,   482,   555,   361,   557,   486,   122,   378,    17,    18,
     491,   737,   122,   483,   728,   496,    52,   122,   145,   440,
     528,   987,   492,   933,   990,   289,   290,   478,   519,   520,
     619,   815,   535,   817,    91,   486,   145,   804,   529,   145,
     125,   126,    93,   818,   465,   496,   964,   145,   529,   106,
     440,   811,   964,    93,   528,    59,    60,   560,   528,   518,
     541,   482,    91,   500,   831,   535,   907,   908,   559,   622,
     491,   122,   511,   987,   555,   465,   557,   106,   559,    52,
     669,   408,   122,   145,   141,    93,   567,    52,    93,   632,
     560,   148,   482,   357,   358,   359,   360,  1063,   362,   363,
      91,   491,   877,   122,   792,   793,   794,   546,   796,    52,
     798,   878,   141,   594,   122,   106,   567,   122,   145,   148,
      16,   511,    93,   813,   615,   515,   100,   116,    15,   819,
     119,   120,   613,   218,   219,   825,   826,   145,   559,   728,
     650,   622,    13,   869,  1058,    37,    38,     1,   737,     3,
     141,   122,   122,  1067,     8,     9,   546,   148,   122,   549,
      14,    15,    16,   666,   116,    19,    16,   119,   120,   559,
      16,   529,   675,   594,   145,   678,    64,   944,   669,    33,
      59,    60,   597,   541,   675,    93,   601,   678,   679,   680,
     561,   694,   613,   696,   666,    26,  1037,   149,    52,   903,
     904,   689,    15,   675,   468,   696,   678,   699,   689,   690,
     701,   702,    66,  1051,   122,   706,   724,   144,   757,   590,
     116,   144,   713,   119,   120,   140,    93,    56,   555,   699,
     557,    64,    65,    66,   948,   723,   607,   145,   144,   610,
     954,   326,   723,   933,   125,   126,   737,   145,   829,   145,
     724,   147,   307,   149,   724,   122,   311,    93,   811,   813,
      91,   145,   145,    15,   701,   819,   820,   121,  1052,   123,
     116,   825,   826,   119,   120,   106,    91,    15,   145,    91,
     869,   145,  1057,    44,   117,   118,   122,   975,   976,   977,
     978,   106,   122,   378,   106,   622,   787,   142,   142,    15,
      18,   147,   142,   149,   743,   142,    52,    15,   139,   145,
     141,   145,   143,   597,   817,   140,    52,   148,    54,    55,
      56,    57,   140,   804,    70,   816,   141,    58,    26,   141,
     811,   812,   813,   148,    70,   816,   148,   142,   819,   820,
     140,    44,   833,   145,   825,   826,    63,   817,    65,    66,
     831,   832,   843,   743,   744,   846,   102,   103,   104,   145,
     848,   215,   145,   145,   845,    91,    44,   848,    15,   450,
     451,    94,    14,  1061,   228,   229,   857,   858,   869,   933,
     106,   832,    15,   129,   865,   824,    15,    91,   803,   102,
      91,   145,   143,    91,   845,   816,   143,   878,   879,   144,
     117,   118,   106,   484,   485,   106,   857,   858,   106,   145,
     145,    37,    38,   145,   865,   141,   907,   908,   145,   132,
     133,   134,   148,    91,   905,   689,   816,   281,   879,   910,
     284,    91,   803,   145,   824,   289,   290,   141,   106,   293,
     141,   139,    15,   141,   148,   143,   106,   148,   302,   303,
     148,   142,   933,    15,   812,   536,   310,   140,    15,   723,
      15,   516,   943,   944,  1007,   140,   947,   220,   523,    15,
     951,   962,   145,   141,   227,   127,   561,   127,    26,   140,
     148,   141,    91,   538,   811,    15,    56,   145,   148,   145,
     116,   145,   943,   119,   120,    15,   145,   106,   529,   145,
     951,   145,   356,   357,   358,   359,   360,   361,   362,   363,
    1020,   264,    62,   145,    26,    65,    66,   142,   145,   803,
     891,   147,   893,   149,    12,     5,   897,   381,  1054,  1010,
     803,  1012,   141,   803,  1015,    91,   591,   592,  1056,   148,
     830,  1053,     6,    91,   259,   597,  1037,   987,   402,  1052,
     106,   405,   984,   407,    -1,    -1,   410,    -1,   106,  1010,
    1051,  1012,  1053,  1054,  1015,    -1,   621,   117,   118,   984,
    1051,    -1,   987,    -1,   964,   990,    -1,   992,   905,    91,
      -1,    -1,  1052,   910,   848,   141,   440,    64,    65,    66,
      -1,   139,   148,   141,   106,   143,   450,   451,   969,   970,
     148,    -1,    62,   356,    58,    65,    66,    -1,    -1,    -1,
      -1,   465,    -1,   467,   468,    -1,    -1,   370,    -1,   990,
     947,   992,   116,  1038,   478,   119,   120,   139,   482,   141,
    1051,   143,   486,    -1,    -1,   388,   148,   491,     8,     9,
     117,   118,   496,   698,    14,    15,    16,    -1,  1063,    19,
    1065,   145,  1067,   147,  1069,   149,  1027,   117,   118,  1030,
      -1,  1051,   116,    33,    -1,   119,   120,    -1,   912,   913,
     124,    64,    65,    66,  1089,   529,    -1,    47,    48,    49,
      50,    -1,    -1,    -1,    54,    55,    -1,   541,    -1,  1060,
      -1,    -1,  1063,    -1,  1065,   149,    66,    67,  1069,    -1,
     984,   756,    -1,   987,    -1,   559,   990,    63,   992,    65,
      66,   984,    -1,   567,   987,    -1,    -1,   990,  1089,   992,
      -1,   776,    -1,    -1,   117,   118,    -1,   116,    -1,    -1,
     119,   120,    -1,    -1,   487,   488,    -1,    -1,   819,   820,
     594,    -1,    -1,   987,   825,   826,    -1,    -1,    -1,   116,
      -1,   121,   119,   120,  1038,   144,    -1,    -1,   147,   613,
     149,   117,   118,    -1,    -1,  1038,    64,    65,    66,    -1,
     851,   852,    -1,   854,   855,    64,    65,    66,    -1,  1063,
     147,  1065,   149,  1067,    -1,  1069,    -1,    -1,   541,    -1,
    1063,    -1,  1065,    -1,  1067,   548,  1069,  1041,  1042,  1043,
      -1,  1045,  1046,    -1,    52,  1089,    54,    55,    56,    57,
      -1,    -1,    -1,   868,    -1,    -1,  1089,    -1,    -1,   117,
     118,    -1,    70,    64,    65,    66,    -1,    -1,   117,   118,
      -1,   886,    64,    65,    66,   689,   690,    -1,    -1,  1083,
    1084,  1085,  1086,    -1,    -1,    -1,    -1,    95,    -1,  1093,
      -1,    -1,   933,   101,   102,   103,   104,    -1,   228,   229,
      -1,    -1,     1,    -1,     3,     4,     5,    -1,    -1,   723,
      64,    65,    66,    12,    -1,   956,   117,   118,    -1,   116,
      -1,   129,   119,   120,   132,   117,   118,    52,    -1,    54,
      55,    56,    57,    -1,    -1,   143,    -1,   267,   268,   269,
     270,    -1,    -1,    -1,    52,    70,    54,    55,    56,    57,
     147,   281,   149,    52,   284,    -1,    -1,    56,    -1,   289,
     290,    -1,    70,   117,   118,    40,    41,    42,    43,    44,
      95,    -1,    -1,    -1,    -1,   688,   101,   102,   103,   104,
      -1,    -1,    -1,    -1,    -1,    -1,    85,    95,    -1,    -1,
     804,    -1,    -1,    -1,   102,   103,   104,    -1,   812,   813,
      -1,    -1,   816,    -1,   129,   819,   820,   132,   102,    -1,
      -1,   825,   826,    89,    90,   728,    -1,   831,   832,    -1,
     145,   129,    -1,    -1,   123,    -1,   102,   357,   358,   359,
     360,   845,   362,   363,   848,    -1,   130,   131,   132,   133,
     134,    -1,    -1,   857,   858,    -1,    -1,    -1,    -1,    -1,
      -1,   865,   382,   129,   130,   131,   132,   133,   134,    -1,
      -1,    -1,    -1,   393,   878,   879,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   405,   789,    -1,    -1,    -1,
     410,   411,   412,   413,   414,   415,   416,   417,   418,   419,
     420,   421,   422,   423,   424,    -1,   426,   427,   428,   429,
     430,   431,   432,   433,   434,   435,   436,   437,    -1,    52,
     440,    54,    55,    56,    57,    -1,   215,    -1,    -1,   933,
     450,   451,   835,    -1,    -1,    -1,    -1,    70,    -1,   943,
     944,    -1,    -1,    -1,    -1,   465,    -1,   951,   468,    -1,
      -1,    52,    -1,    54,    55,    56,    57,   860,    -1,    -1,
     480,    -1,   482,    -1,   484,   485,    -1,    -1,    -1,    70,
      -1,   491,    -1,    -1,    52,    -1,    54,    55,    56,    57,
     500,    -1,    -1,   503,   504,    86,    -1,    -1,   508,    -1,
      -1,   511,    70,   513,    95,   515,   516,    -1,    -1,    -1,
     101,   102,   103,   104,   293,   294,  1010,    -1,  1012,    -1,
      -1,  1015,    -1,   302,   303,    -1,   536,    95,    -1,    -1,
      -1,   310,    -1,   101,    -1,    -1,   546,    -1,   129,   549,
      -1,   132,   321,    -1,    -1,    -1,    -1,    -1,    -1,   559,
      -1,    -1,    -1,    -1,    -1,   948,    -1,  1051,    -1,    -1,
      -1,   954,    -1,    -1,    -1,    -1,   576,   577,    -1,    -1,
      -1,    52,    -1,    54,    55,    56,    57,   356,    -1,    -1,
      -1,    -1,   361,    52,   594,    54,    55,    56,    57,    70,
      -1,    -1,    -1,    -1,    -1,     0,    -1,    -1,    -1,    -1,
      -1,    70,   381,   613,    -1,    -1,   616,    -1,    13,    14,
      15,    16,    17,    18,    95,    20,    -1,    89,    90,    -1,
     101,    -1,    27,   402,    -1,    -1,    95,    -1,   407,   408,
     102,   410,    37,    38,    -1,    40,    41,    42,    43,    44,
      -1,    -1,     1,    -1,     3,     4,     5,    -1,    -1,    -1,
      -1,    -1,    -1,    12,    -1,   127,   128,   129,   130,   131,
     132,   133,   134,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   450,   451,    -1,    -1,    -1,    -1,    -1,    52,   689,
      54,    55,    56,    57,    -1,    -1,    -1,    -1,   467,    -1,
      -1,   701,    -1,    52,   704,   705,    70,    56,    -1,   478,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   486,    -1,    -1,
      84,   116,    -1,   723,   119,   120,    -1,   496,    -1,    -1,
      -1,    95,    -1,    -1,   734,    -1,    85,   101,   102,   103,
     104,    -1,    -1,   743,   744,   140,    -1,    -1,    -1,   144,
      89,    90,   147,    -1,   149,    -1,    -1,    -1,   122,    -1,
     529,    -1,    -1,   102,    -1,   129,    -1,    -1,   132,    -1,
      -1,    -1,   541,    -1,   123,    -1,    -1,    -1,    -1,   143,
      -1,    -1,    -1,    -1,    -1,    -1,   555,    -1,   557,    -1,
      -1,   130,   131,   132,   133,   134,    -1,    -1,   567,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   808,    -1,
      -1,    -1,    -1,   813,   814,    -1,   816,    -1,    -1,   819,
     820,    -1,    -1,    -1,   824,   825,   826,    -1,    52,    -1,
      54,    55,    56,    57,    -1,    -1,    -1,    -1,    -1,    -1,
      52,    -1,    54,    55,    56,    57,    70,    -1,   848,    -1,
      -1,   851,   852,   622,   854,   855,    -1,    -1,    70,     1,
      84,     3,     4,     5,   864,    -1,   215,    -1,   868,    -1,
      12,    95,    -1,    -1,    86,    -1,    -1,   101,   102,   103,
     104,    -1,    -1,    95,    -1,    -1,    -1,   887,   888,   101,
     102,   103,   104,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     900,   901,    -1,    -1,    -1,   129,    -1,    -1,   132,    -1,
      52,    -1,    -1,    -1,    56,    -1,   916,   129,    -1,   143,
     132,   690,    -1,    -1,    -1,    -1,   926,   927,    -1,    -1,
      -1,    -1,    -1,   933,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    85,   293,   294,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   302,   303,    -1,   956,    -1,    -1,    -1,
      -1,   310,    -1,    -1,   964,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   321,    -1,    -1,    52,    -1,    54,    55,    56,
      57,   123,    -1,     1,    -1,     3,     4,     5,     6,    -1,
      -1,    -1,    -1,    70,    12,    -1,    -1,    52,    -1,    54,
      55,    56,    57,    -1,    -1,    -1,    -1,   356,    -1,    86,
      -1,    -1,   361,    -1,    -1,    70,    -1,    -1,    95,    -1,
      -1,    -1,    -1,    -1,   101,   102,   103,   104,    -1,    -1,
      -1,    -1,   381,    -1,    52,   804,    -1,    -1,    56,    -1,
      95,    -1,   811,   812,   813,    -1,   101,   102,   103,   104,
     819,  1051,   129,   402,    -1,   132,   825,   826,   407,   408,
      -1,   410,   831,   832,    -1,    -1,    -1,    85,    -1,    -1,
      -1,    -1,    -1,   215,   129,    -1,   845,   132,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   857,   858,
      -1,    -1,    -1,     1,    -1,     3,   865,    -1,    -1,    -1,
      -1,   450,   451,    -1,    12,   123,    -1,    -1,    -1,   878,
     879,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   467,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   478,
      -1,    -1,    -1,    -1,    -1,    -1,   905,   486,    -1,    -1,
      -1,   910,    -1,    -1,    52,    -1,    -1,   496,    -1,    -1,
      -1,   293,   294,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     302,   303,    -1,    -1,   933,    -1,    -1,    -1,   310,    -1,
      -1,    -1,    -1,    -1,   943,   944,    -1,    -1,   947,   321,
     529,    -1,   951,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   541,    -1,    -1,    -1,    -1,   215,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   555,    -1,   557,    -1,
      -1,    -1,    -1,    -1,   356,   123,    -1,    -1,   567,   361,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   381,
      -1,  1010,    -1,  1012,    -1,    -1,  1015,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     402,    -1,    -1,    -1,    -1,   407,   408,    -1,   410,    -1,
      -1,    -1,    -1,   622,    -1,   293,   294,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   302,   303,    -1,    -1,    -1,    -1,
      -1,    -1,   310,    -1,    -1,    -1,    -1,    52,    53,    -1,
      -1,    56,    -1,   321,    -1,    -1,    -1,   215,   450,   451,
      -1,    -1,    -1,    -1,    -1,    -1,    71,    72,    73,    74,
      75,    76,    77,    78,    -1,   467,    81,    82,    -1,    -1,
      -1,    -1,    87,    88,    89,    90,   478,    -1,   356,    -1,
      -1,   690,    -1,   361,   486,    -1,   101,   102,   103,     1,
      -1,     3,    -1,    -1,   496,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   381,    -1,    -1,    -1,    -1,    -1,    -1,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
      -1,   136,   137,    -1,   402,   293,    -1,   529,   143,   407,
     408,   146,    -1,    -1,   302,   303,    -1,    -1,    -1,   541,
      52,    -1,   310,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   555,    -1,   557,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   567,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   356,   467,
      -1,    -1,    -1,   361,    -1,   804,    -1,    -1,    -1,    -1,
     478,    -1,   811,   812,   813,    -1,    -1,    -1,   486,    -1,
     819,   123,    -1,   381,    -1,    -1,   825,   826,   496,    -1,
     622,    -1,   831,   832,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   402,    -1,   845,    -1,    -1,   407,
      -1,    -1,   410,    -1,    -1,    -1,    -1,    -1,   857,   858,
      -1,   529,    -1,    -1,    -1,    -1,   865,    -1,    -1,    -1,
      -1,    -1,    -1,   541,    -1,    -1,    -1,    -1,    -1,   878,
     879,    -1,    -1,    -1,    -1,    -1,    -1,   555,    -1,   557,
      -1,    -1,   450,   451,    -1,    -1,    -1,    -1,   690,   567,
      -1,    -1,    -1,    -1,    -1,    -1,   905,    -1,    -1,   467,
      -1,   910,    -1,   215,    -1,    -1,    -1,    -1,    -1,    -1,
     478,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   486,    -1,
      -1,    -1,    -1,    -1,   933,    -1,    -1,    -1,   496,    -1,
      -1,    -1,    -1,    -1,   943,   944,    -1,    -1,   947,    -1,
      -1,    -1,   951,    -1,   622,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   529,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   541,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   293,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     302,   303,    -1,    -1,    -1,    -1,    -1,    -1,   310,   567,
      -1,  1010,   804,  1012,    -1,    -1,  1015,    -1,    -1,   811,
     812,   813,   690,    -1,    -1,    -1,    -1,   819,    -1,    -1,
      -1,    -1,    -1,   825,   826,    -1,    -1,    -1,    -1,   831,
     832,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   845,   356,    -1,    -1,    -1,    -1,   361,
      -1,    -1,    -1,    -1,    -1,   857,   858,    73,    74,    75,
      76,    77,    78,   865,    -1,    81,    82,    -1,    -1,   381,
      -1,    -1,    -1,    89,    90,    -1,   878,   879,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   102,    -1,    -1,    -1,
     402,    -1,    -1,    -1,    -1,   407,    -1,    -1,   410,    -1,
      -1,    -1,    -1,   905,    -1,    -1,    -1,    -1,   910,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,    -1,
      -1,    -1,   690,    -1,    -1,    -1,   804,    -1,    -1,    -1,
      -1,   933,    -1,   811,   812,    -1,    -1,    -1,   450,   451,
      -1,   943,   944,    -1,    -1,   947,    -1,    -1,    -1,   951,
      -1,    -1,    -1,   831,   832,   467,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   478,   845,    -1,    -1,
      -1,    -1,    -1,    -1,   486,    -1,    -1,    -1,    -1,   857,
     858,    -1,    -1,    -1,   496,    -1,    -1,   865,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     878,   879,    -1,    -1,    -1,    -1,    -1,    -1,  1010,    -1,
    1012,    -1,    -1,  1015,    -1,    -1,    -1,   529,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   905,    -1,   541,
      -1,    -1,   910,    -1,    -1,    -1,   804,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   812,   813,    -1,    -1,    -1,    -1,
      -1,   819,    -1,    -1,    -1,   567,    -1,   825,   826,    -1,
      -1,    -1,    -1,   831,   832,   943,   944,    -1,    -1,   947,
      -1,    -1,    -1,   951,    -1,    -1,    -1,   845,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   857,
     858,    -1,    -1,    -1,    -1,    -1,    -1,   865,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     878,   879,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     0,
      -1,    -1,  1010,    -1,  1012,    -1,    -1,  1015,    -1,    -1,
      -1,    -1,    13,    14,    15,    16,    17,    18,    -1,    20,
      -1,    -1,    -1,    -1,    -1,    -1,    27,    28,    29,    -1,
      -1,    -1,    -1,    -1,    -1,   933,    37,    38,    -1,    40,
      41,    42,    43,    44,    -1,   943,   944,    -1,   690,   947,
      -1,    -1,    -1,   951,    -1,    -1,    -1,    58,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    -1,    -1,    -1,    -1,    89,    90,
      91,    -1,    -1,    94,    -1,    -1,    -1,    -1,    -1,   100,
      -1,   102,    -1,    -1,    -1,   106,    -1,    -1,    -1,    -1,
      -1,    -1,  1010,   114,  1012,   116,    -1,  1015,   119,   120,
      -1,    -1,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,    -1,    -1,    -1,    -1,     0,   140,
     141,   142,    -1,   144,   145,    -1,   147,   148,   149,    -1,
      -1,    13,    14,    15,    16,    17,    18,    -1,    20,    -1,
      -1,    -1,   804,    -1,    26,    27,    -1,    -1,    -1,    -1,
     812,   813,    -1,    -1,    -1,    37,    38,   819,    40,    41,
      42,    43,    44,   825,   826,    -1,    -1,    -1,    -1,   831,
     832,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   845,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   857,   858,    -1,    -1,    -1,
      -1,    -1,    -1,   865,    -1,    -1,    -1,    -1,    -1,    91,
      -1,    -1,    -1,    -1,    44,    -1,   878,   879,    -1,    -1,
      -1,    -1,    -1,    -1,   106,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   116,    -1,    -1,   119,   120,    -1,
      -1,    -1,    -1,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    -1,    -1,   139,   140,    89,
      90,   143,   144,    -1,    -1,   147,   148,   149,    -1,    -1,
      -1,   933,   102,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   943,   944,    -1,    -1,    -1,    -1,    -1,    -1,   951,
      -1,    -1,    -1,   123,    -1,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,    -1,    -1,    -1,    -1,    -1,
       0,     1,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    -1,    -1,    -1,    -1,    -1,    -1,    19,
      -1,    21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    36,    -1,  1010,    39,
    1012,    -1,    -1,  1015,    -1,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    -1,    59,
      60,    61,    -1,    -1,    64,    -1,    -1,    67,    68,    -1,
      70,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    85,    86,    -1,    -1,    -1,
      -1,    -1,    92,    -1,    -1,    95,    96,    -1,    98,    99,
      -1,   101,    -1,    -1,    -1,   105,    -1,   107,   108,   109,
      -1,   111,   112,   113,     0,   115,   116,    -1,    -1,   119,
     120,    -1,    -1,    -1,    -1,    -1,    -1,    13,    14,    15,
      16,    17,    18,    -1,    20,   135,   136,   137,    -1,    -1,
      26,    27,    28,    -1,    -1,    -1,    -1,   147,    -1,   149,
      -1,    37,    38,    -1,    40,    41,    42,    43,    44,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    -1,
      -1,    -1,    -1,    89,    90,    91,    -1,    -1,    94,    -1,
      -1,    -1,    -1,    -1,   100,    -1,   102,    -1,    -1,    -1,
     106,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     116,    -1,    -1,   119,   120,    -1,    -1,   123,    -1,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,    -1,
      -1,     0,    -1,   139,   140,   141,   142,   143,   144,   145,
      -1,   147,   148,   149,    13,    14,    15,    16,    17,    18,
      -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,    27,    28,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,    38,
      -1,    40,    41,    42,    43,    44,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    -1,    -1,    -1,    -1,
      89,    90,    91,    -1,    93,    94,    -1,    -1,    -1,    -1,
      -1,   100,    -1,   102,    -1,    -1,    -1,   106,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   116,    -1,    -1,
     119,   120,    -1,   122,   123,    -1,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,    -1,    -1,     0,    -1,
      -1,   140,   141,   142,    -1,   144,   145,    -1,   147,   148,
     149,    13,    14,    15,    16,    17,    18,    -1,    20,    -1,
      -1,    -1,    -1,    -1,    26,    27,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    37,    38,    -1,    40,    41,
      42,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    -1,    -1,    -1,    -1,    89,    90,    91,
      -1,    -1,    94,    -1,    -1,    -1,    -1,    -1,   100,    -1,
     102,    -1,    -1,    -1,   106,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   116,    -1,    -1,   119,   120,    -1,
      -1,   123,    -1,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,    -1,    -1,     0,    -1,   139,   140,   141,
     142,   143,   144,   145,    -1,   147,   148,   149,    13,    14,
      15,    16,    17,    18,    -1,    20,    -1,    -1,    -1,    -1,
      -1,    -1,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    37,    38,    -1,    40,    41,    42,    43,    44,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      -1,    -1,    -1,    -1,    89,    90,    91,    -1,    -1,    94,
      -1,    -1,    -1,    -1,    -1,   100,    -1,   102,    -1,    -1,
      -1,   106,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   116,    -1,    -1,   119,   120,    -1,    -1,   123,    -1,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
      -1,    -1,     0,    -1,    -1,   140,   141,   142,   143,   144,
     145,    -1,   147,   148,   149,    13,    14,    15,    -1,    17,
      18,    -1,    20,    -1,    -1,    -1,    -1,    -1,    26,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,
      38,    -1,    40,    41,    42,    43,    44,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    -1,    -1,    -1,
      -1,    89,    90,    91,    -1,    93,    94,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   102,    -1,    -1,    -1,   106,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   116,    -1,
      -1,   119,   120,    -1,   122,   123,    -1,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,    -1,    -1,     0,
      -1,   139,   140,   141,    -1,    -1,   144,   145,    -1,   147,
     148,   149,    13,    14,    15,    -1,    17,    18,    -1,    20,
      -1,    -1,    -1,    -1,    -1,    26,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    37,    38,    -1,    40,
      41,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    -1,    -1,    -1,    -1,    89,    90,
      91,    -1,    93,    94,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   102,    -1,    -1,    -1,   106,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   116,    -1,    -1,   119,   120,
      -1,   122,   123,    -1,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,    -1,    -1,     0,    -1,   139,   140,
     141,    -1,    -1,   144,   145,    -1,   147,   148,   149,    13,
      14,    15,    -1,    17,    18,    -1,    20,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    37,    38,    -1,    40,    41,    42,    43,
      44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    -1,    -1,    -1,    -1,    89,    90,    91,    -1,    93,
      94,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,    -1,
      -1,    -1,   106,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   116,    -1,    -1,   119,   120,    -1,   122,   123,
      -1,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,    -1,    -1,     0,    -1,    -1,   140,   141,    -1,    -1,
     144,   145,    -1,   147,   148,   149,    13,    14,    15,    -1,
      17,    18,    -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      37,    38,    -1,    40,    41,    42,    43,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    -1,    -1,
      -1,    -1,    89,    90,    91,    -1,    93,    94,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   102,    -1,    -1,    -1,   106,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   116,
      -1,    -1,   119,   120,    -1,   122,   123,    -1,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,    -1,    -1,
      -1,    -1,    -1,   140,   141,    -1,    -1,   144,   145,    -1,
     147,   148,   149,     1,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    -1,    -1,
      18,    19,    -1,    21,    22,    23,    24,    -1,    -1,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    36,    -1,
      -1,    39,    -1,    -1,    -1,    -1,    -1,    45,    -1,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      -1,    59,    60,    61,    -1,    -1,    64,    -1,    -1,    67,
      68,    -1,    70,    71,    72,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,    86,    -1,
      -1,    -1,    -1,    -1,    92,    -1,    -1,    95,    96,    -1,
      98,    99,    -1,   101,    -1,    -1,    -1,   105,    -1,   107,
     108,   109,    -1,   111,   112,   113,    -1,   115,   116,    -1,
      -1,   119,   120,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   135,   136,   137,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   147,
       1,   149,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    -1,    -1,    15,    -1,    17,    18,    19,    -1,
      21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,    30,
      31,    32,    33,    34,    35,    36,    -1,    -1,    39,    -1,
      -1,    -1,    -1,    -1,    45,    -1,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    -1,    59,    60,
      61,    -1,    -1,    64,    -1,    -1,    67,    68,    -1,    70,
      71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    85,    86,    -1,    -1,    -1,    -1,
      -1,    92,    -1,    -1,    95,    96,    -1,    98,    99,    -1,
     101,    -1,    -1,    -1,   105,    -1,   107,   108,   109,    -1,
     111,   112,   113,    -1,   115,   116,    -1,    -1,   119,   120,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   135,   136,   137,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   147,     1,   149,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    -1,
      -1,    15,    -1,    -1,    18,    19,    20,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,
      34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,
      -1,    45,    -1,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    -1,    59,    60,    61,    -1,    -1,
      64,    -1,    -1,    67,    68,    -1,    70,    71,    72,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    85,    86,    -1,    -1,    -1,    -1,    -1,    92,    -1,
      -1,    95,    96,    -1,    98,    99,    -1,   101,    -1,    -1,
      -1,   105,    -1,   107,   108,   109,    -1,   111,   112,   113,
      -1,   115,   116,    -1,    -1,   119,   120,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   135,   136,   137,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   147,     1,   149,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    -1,    -1,    15,    -1,
      -1,    18,    19,    -1,    21,    22,    23,    24,    -1,    -1,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    45,    -1,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    -1,    59,    60,    61,    -1,    -1,    64,    -1,    -1,
      67,    68,    -1,    70,    71,    72,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,    86,
      -1,    -1,    -1,    -1,    -1,    92,    -1,    -1,    95,    96,
      -1,    98,    99,    -1,   101,    -1,    -1,    -1,   105,    -1,
     107,   108,   109,    -1,   111,   112,   113,    -1,   115,   116,
      -1,    -1,   119,   120,     1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    -1,    -1,   135,   136,
     137,    -1,    19,    -1,    21,    22,    23,    24,    -1,    -1,
     147,    -1,   149,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    -1,    59,    60,    61,    -1,    -1,    64,    -1,    -1,
      67,    68,    -1,    70,    71,    72,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,    86,
      -1,    -1,    -1,    -1,    -1,    92,    -1,    -1,    95,    96,
      -1,    98,    99,    -1,   101,    -1,    -1,    -1,   105,    -1,
     107,   108,   109,    -1,   111,   112,   113,    -1,   115,   116,
      -1,    -1,   119,   120,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   135,   136,
     137,    -1,    -1,   140,    -1,    -1,    -1,    -1,    -1,    -1,
     147,     1,   149,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    -1,    14,    15,    -1,    -1,    -1,    19,
      -1,    21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    -1,    45,    -1,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    -1,    59,
      60,    61,    -1,    -1,    64,    -1,    -1,    67,    68,    -1,
      70,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    85,    86,    -1,    -1,    -1,
      -1,    -1,    92,    -1,    -1,    95,    96,    -1,    98,    99,
      -1,   101,    -1,    -1,    -1,   105,    -1,   107,   108,   109,
      -1,   111,   112,   113,    -1,   115,   116,    -1,    -1,   119,
     120,     1,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    -1,    -1,   135,   136,   137,    -1,    19,
      -1,    21,    22,    23,    24,    -1,    -1,   147,    -1,   149,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    -1,    45,    -1,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    -1,    59,
      60,    61,    -1,    -1,    64,    -1,    -1,    67,    68,    -1,
      70,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    85,    86,    -1,    -1,    -1,
      -1,    -1,    92,    -1,    -1,    95,    96,    -1,    98,    99,
      -1,   101,    -1,    -1,    -1,   105,    -1,   107,   108,   109,
      -1,   111,   112,   113,    -1,   115,   116,    -1,    -1,   119,
     120,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   135,   136,   137,    -1,    -1,
      -1,    -1,    -1,    -1,   144,    -1,    -1,   147,     1,   149,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    19,    -1,    21,    22,
      23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    45,    -1,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    -1,    59,    60,    61,    -1,
      -1,    64,    -1,    -1,    67,    68,    -1,    70,    71,    72,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    85,    86,    -1,    -1,    -1,    -1,    -1,    92,
      -1,    -1,    95,    96,    -1,    98,    99,    -1,   101,    -1,
      -1,    -1,   105,    -1,   107,   108,   109,    -1,   111,   112,
     113,    -1,   115,   116,    -1,    -1,   119,   120,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   135,   136,   137,    -1,    -1,    -1,    -1,    -1,
      -1,   144,    -1,    -1,   147,     1,   149,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    -1,    -1,    -1,
      -1,    -1,    -1,    19,    -1,    21,    22,    23,    24,    -1,
      -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    45,
      -1,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    -1,    59,    60,    61,    -1,    -1,    64,    -1,
      -1,    67,    68,    -1,    70,    71,    72,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,
      86,    -1,    -1,    -1,    -1,    -1,    92,    -1,    -1,    95,
      96,    -1,    98,    99,    -1,   101,    -1,    -1,    -1,   105,
      -1,   107,   108,   109,    -1,   111,   112,   113,    -1,   115,
     116,    -1,    -1,   119,   120,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   135,
     136,   137,    -1,    -1,   140,    -1,    -1,    -1,    -1,    -1,
      -1,   147,     1,   149,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    -1,    -1,    15,    -1,    -1,    -1,
      19,    -1,    21,    22,    23,    24,    -1,    -1,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    45,    -1,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    -1,
      59,    60,    61,    -1,    -1,    64,    -1,    -1,    67,    68,
      -1,    70,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    85,    86,    -1,    -1,
      -1,    -1,    -1,    92,    -1,    -1,    95,    96,    -1,    98,
      99,    -1,   101,    -1,    -1,    -1,   105,    -1,   107,   108,
     109,    -1,   111,   112,   113,    -1,   115,   116,    -1,    -1,
     119,   120,    -1,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    -1,    -1,   135,   136,   137,    -1,
      19,    -1,    21,    22,    23,    24,    -1,    -1,   147,    -1,
     149,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    -1,
      59,    60,    61,    -1,    -1,    64,    -1,    -1,    67,    68,
      -1,    70,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    85,    86,    -1,    -1,
      -1,    -1,    -1,    92,    -1,    -1,    95,    96,    -1,    98,
      99,    -1,   101,    -1,    -1,    -1,   105,    -1,   107,   108,
     109,    -1,   111,   112,   113,    -1,   115,   116,    -1,    -1,
     119,   120,    -1,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    -1,    -1,   135,   136,   137,    -1,
      19,    -1,    21,    22,    23,    24,    -1,    -1,   147,    -1,
     149,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    45,    -1,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    -1,
      59,    60,    61,    -1,    -1,    64,    -1,    -1,    67,    68,
      -1,    70,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    85,    86,    -1,    -1,
      -1,    -1,    -1,    92,    -1,    -1,    95,    96,    -1,    98,
      99,    -1,   101,    -1,    -1,    -1,   105,    -1,   107,   108,
     109,    -1,   111,   112,   113,    -1,   115,   116,    -1,    -1,
     119,   120,    -1,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    -1,    -1,    -1,   135,   136,   137,    -1,
      19,    -1,    21,    22,    23,    24,    -1,    -1,   147,    -1,
     149,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    -1,
      59,    60,    61,    -1,    -1,    64,    -1,    -1,    67,    68,
      -1,    70,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    85,    86,    -1,    -1,
      -1,    -1,    -1,    92,    -1,    -1,    95,    96,    -1,    98,
      99,    -1,    -1,    -1,    -1,    -1,   105,    -1,   107,   108,
     109,    -1,   111,   112,   113,    -1,   115,   116,    -1,    -1,
     119,   120,    -1,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    -1,    -1,    -1,   135,   136,   137,    -1,
      19,    -1,    21,    22,    23,    24,    -1,    -1,   147,    -1,
     149,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    -1,
      59,    60,    61,    -1,    -1,    64,    -1,    -1,    67,    68,
      -1,    70,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    85,    86,    -1,    -1,
      -1,    -1,    -1,    92,    -1,    -1,    95,    96,    -1,    98,
      99,    -1,    -1,    -1,    -1,    -1,   105,    -1,   107,   108,
     109,    -1,   111,   112,   113,    -1,   115,   116,    -1,    -1,
     119,   120,    -1,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    -1,    -1,    -1,   135,   136,   137,    -1,
      19,    -1,    21,    22,    23,    24,    -1,    -1,    -1,    -1,
     149,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,
      49,    50,    -1,    52,    53,    54,    55,    56,    57,    -1,
      59,    60,    61,    -1,    -1,    64,    -1,    -1,    67,    68,
      -1,    70,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    85,    86,    -1,    -1,
      -1,    -1,    -1,    92,    -1,    -1,    95,    96,    -1,    98,
      99,    -1,    -1,    -1,    -1,    -1,   105,    -1,   107,   108,
     109,    -1,   111,   112,   113,    -1,   115,   116,    -1,    -1,
     119,   120,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   135,   136,   137,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   147,    -1,
     149,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    -1,    -1,    -1,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    -1,    -1,
      -1,    -1,    -1,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    -1,    -1,    -1,    -1,
      -1,    -1,    64,    -1,    -1,    -1,    -1,    -1,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    -1,    -1,    81,
      82,    -1,    -1,    -1,    -1,    87,    88,    89,    90,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,
     102,   103,    -1,    -1,    -1,    -1,   108,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,    -1,   136,   137,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   146,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    -1,    -1,    -1,    -1,    -1,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    -1,    -1,    81,    82,    -1,    -1,    -1,    -1,    87,
      88,    89,    90,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   101,   102,   103,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,    -1,   136,   137,
      -1,    -1,    -1,    -1,    -1,   143,    -1,    -1,   146,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    -1,    -1,    -1,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    -1,    -1,    -1,    -1,
      -1,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    -1,    -1,    -1,    -1,    -1,    -1,
      64,    -1,    -1,    -1,    -1,    -1,    -1,    71,    72,    73,
      74,    75,    76,    77,    78,    -1,    -1,    81,    82,    -1,
      -1,    -1,    -1,    87,    88,    89,    90,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,   102,   103,
      -1,    -1,    -1,    -1,   108,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,    -1,   136,   137,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   146,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      -1,    -1,    -1,    -1,    -1,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    -1,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    71,    72,    73,    74,    75,    76,    77,    78,    -1,
      -1,    81,    82,    -1,    -1,    -1,    -1,    87,    88,    89,
      90,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   101,   102,   103,    -1,    -1,    -1,   107,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,    -1,   136,   137,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   146,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    -1,    -1,    -1,    -1,    -1,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    -1,    -1,
      56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    71,    72,    73,    74,    75,
      76,    77,    78,    -1,    -1,    81,    82,    -1,    -1,    -1,
      -1,    87,    88,    89,    90,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   101,   102,   103,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,    -1,
     136,   137,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     146,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    19,    -1,    21,
      22,    23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,
      32,    33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    50,    -1,
      52,    53,    54,    55,    56,    57,    -1,    59,    60,    61,
      -1,    -1,    64,    -1,    -1,    67,    68,    -1,    70,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      92,    -1,    -1,    95,    96,    -1,    98,    99,    -1,    -1,
      -1,    -1,    -1,   105,    -1,   107,   108,   109,    -1,   111,
     112,   113,    -1,   115,    -1,    -1,    -1,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    -1,    -1,    -1,
      -1,    -1,    -1,   135,    19,    -1,    21,    22,    23,    24,
      -1,    -1,    -1,   145,    -1,    30,    31,    32,    33,    34,
      35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    49,    50,    -1,    52,    53,    54,
      55,    56,    57,    -1,    59,    60,    61,    -1,    -1,    64,
      -1,    -1,    67,    68,    -1,    70,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    92,    -1,    -1,
      95,    96,    -1,    98,    99,    -1,    -1,    -1,    -1,    -1,
     105,    -1,   107,   108,   109,    -1,   111,   112,   113,    -1,
     115,    -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,
     135,    19,    -1,    21,    22,    23,    24,    -1,    26,    -1,
     145,    -1,    30,    31,    32,    33,    34,    35,    36,    -1,
      -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      48,    49,    50,    -1,    52,    53,    54,    55,    56,    57,
      -1,    59,    60,    61,    -1,    -1,    64,    -1,    -1,    67,
      68,    -1,    70,    71,    72,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,    86,    -1,
      -1,    -1,    -1,    -1,    92,    -1,    -1,    95,    96,    -1,
      98,    99,    -1,   101,    -1,   103,   104,   105,    -1,   107,
     108,   109,    -1,   111,   112,   113,    -1,   115,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    11,   135,   136,   137,
      -1,   139,    -1,    -1,    19,   143,    21,    22,    23,    24,
      -1,    26,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    49,    50,    -1,    52,    53,    54,
      55,    56,    57,    -1,    59,    60,    61,    -1,    -1,    64,
      -1,    -1,    67,    68,    -1,    70,    71,    72,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      85,    86,    -1,    -1,    -1,    -1,    -1,    92,    -1,    -1,
      95,    96,    -1,    98,    99,    -1,   101,    -1,   103,   104,
     105,    -1,   107,   108,   109,    -1,   111,   112,   113,    -1,
     115,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    11,
     135,   136,   137,    -1,   139,    -1,    -1,    19,   143,    21,
      22,    23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,
      32,    33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    50,    -1,
      52,    53,    54,    55,    56,    57,    -1,    59,    60,    61,
      -1,    -1,    64,    -1,    -1,    67,    68,    -1,    70,    71,
      72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    85,    86,    -1,    -1,    -1,    -1,    -1,
      92,    93,    -1,    95,    96,    -1,    98,    99,    -1,   101,
      -1,   103,   104,   105,    -1,   107,   108,   109,    -1,   111,
     112,   113,    -1,   115,    -1,    -1,    -1,    -1,    -1,    -1,
     122,    -1,    -1,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    11,   135,   136,   137,    -1,    -1,    -1,    -1,
      19,   143,    21,    22,    23,    24,    -1,    -1,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,
      49,    50,    -1,    52,    53,    54,    55,    56,    57,    -1,
      59,    60,    61,    -1,    -1,    64,    -1,    -1,    67,    68,
      -1,    70,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    85,    86,    -1,    -1,
      -1,    -1,    -1,    92,    93,    -1,    95,    96,    -1,    98,
      99,    -1,   101,    -1,   103,   104,   105,    -1,   107,   108,
     109,    -1,   111,   112,   113,    -1,   115,    -1,    -1,    -1,
      -1,    -1,    -1,   122,    -1,    -1,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,   135,   136,   137,    -1,
      -1,    -1,    -1,    19,   143,    21,    22,    23,    24,    -1,
      -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    48,    49,    50,    -1,    52,    53,    54,    55,
      56,    57,    -1,    59,    60,    61,    -1,    -1,    64,    -1,
      -1,    67,    68,    -1,    70,    71,    72,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,
      86,    -1,    -1,    -1,    -1,    -1,    92,    -1,    -1,    95,
      96,    -1,    98,    99,    -1,   101,    -1,   103,   104,   105,
      -1,   107,   108,   109,    -1,   111,   112,   113,    -1,   115,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    11,   135,
     136,   137,    -1,    -1,    -1,    -1,    19,   143,    21,    22,
      23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    48,    49,    50,    -1,    52,
      53,    54,    55,    56,    57,    -1,    59,    60,    61,    -1,
      -1,    64,    -1,    -1,    67,    68,    -1,    70,    71,    72,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    85,    86,    -1,    -1,    -1,    -1,    -1,    92,
      -1,    -1,    95,    96,    -1,    98,    99,    -1,   101,    -1,
     103,   104,   105,    -1,   107,   108,   109,    -1,   111,   112,
     113,    -1,   115,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    11,   135,   136,   137,    -1,    -1,    -1,    -1,    19,
     143,    21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    -1,    59,
      60,    61,    -1,    -1,    64,    -1,    -1,    67,    68,    -1,
      70,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    85,    86,    -1,    -1,    -1,
      -1,    -1,    92,    -1,    -1,    95,    96,    -1,    98,    99,
      -1,    -1,    -1,    -1,    -1,   105,    -1,   107,   108,   109,
      -1,   111,   112,   113,    -1,   115,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   135,   136,   137,    -1,    -1,
      -1,    -1,    -1,   143,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    -1,    -1,    -1,    -1,    -1,    -1,
      19,    -1,    21,    22,    23,    24,    -1,    -1,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    -1,
      59,    60,    61,    -1,    -1,    64,    -1,    -1,    67,    68,
      -1,    70,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    85,    86,    -1,    -1,
      -1,    -1,    -1,    92,    -1,    -1,    95,    96,    -1,    98,
      99,    -1,   101,    -1,    -1,    -1,   105,    -1,   107,   108,
     109,    -1,   111,   112,   113,    -1,   115,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    -1,    -1,    -1,   135,   136,   137,    19,
      -1,    21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    -1,    45,    -1,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    -1,    59,
      60,    61,    -1,    -1,    64,    -1,    -1,    67,    68,    -1,
      70,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    85,    86,    -1,    -1,    -1,
      -1,    -1,    92,    -1,    -1,    95,    96,    -1,    98,    99,
      -1,   101,    -1,    -1,    -1,   105,    -1,   107,   108,   109,
      -1,   111,   112,   113,    -1,   115,    -1,    -1,    -1,    -1,
      -1,    -1,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    -1,    -1,    -1,    -1,   135,   136,   137,    19,    -1,
      21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,    30,
      31,    32,    33,    34,    35,    36,    -1,    -1,    39,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    50,
      -1,    52,    53,    54,    55,    56,    57,    -1,    59,    60,
      61,    -1,    -1,    64,    -1,    -1,    67,    68,    -1,    70,
      71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    85,    86,    -1,    -1,    -1,    -1,
      -1,    92,    -1,    -1,    95,    96,    -1,    98,    99,    -1,
     101,    -1,   103,   104,   105,    -1,   107,   108,   109,    -1,
     111,   112,   113,    -1,   115,    -1,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      -1,    -1,    -1,    -1,   135,   136,   137,    19,    -1,    21,
      22,    23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,
      32,    33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    50,    -1,
      52,    53,    54,    55,    56,    57,    -1,    59,    60,    61,
      -1,    -1,    64,    -1,    -1,    67,    68,    -1,    70,    71,
      72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    85,    86,    -1,    -1,    -1,    -1,    -1,
      92,    -1,    -1,    95,    96,    -1,    98,    99,    -1,   101,
      -1,   103,   104,   105,    -1,   107,   108,   109,    -1,   111,
     112,   113,    -1,   115,    -1,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    -1,
      -1,    -1,    -1,   135,   136,   137,    19,    -1,    21,    22,
      23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    48,    49,    50,    -1,    52,
      53,    54,    55,    56,    57,    -1,    59,    60,    61,    -1,
      -1,    64,    -1,    -1,    67,    68,    -1,    70,    71,    72,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    85,    86,    -1,    -1,    -1,    -1,    -1,    92,
      -1,    -1,    95,    96,    -1,    98,    99,    -1,   101,    -1,
     103,   104,   105,    -1,   107,   108,   109,    -1,   111,   112,
     113,    -1,   115,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    -1,    -1,
      -1,    -1,   135,   136,   137,    19,    -1,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,
      34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    48,    49,    50,    -1,    52,    53,
      54,    55,    56,    57,    -1,    59,    60,    61,    -1,    -1,
      64,    -1,    -1,    67,    68,    -1,    70,    71,    72,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    85,    86,    -1,    -1,    -1,    -1,    -1,    92,    -1,
      -1,    95,    96,    -1,    98,    99,    -1,   101,    -1,   103,
     104,   105,    -1,   107,   108,   109,    -1,   111,   112,   113,
      -1,   115,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    -1,    -1,    -1,
      -1,   135,   136,   137,    19,    -1,    21,    22,    23,    24,
      -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    49,    50,    -1,    52,    53,    54,
      55,    56,    57,    -1,    59,    60,    61,    -1,    -1,    64,
      -1,    -1,    67,    68,    -1,    70,    71,    72,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      85,    86,    -1,    -1,    -1,    -1,    -1,    92,    -1,    -1,
      95,    96,    -1,    98,    99,    -1,   101,    -1,   103,    -1,
     105,    -1,   107,   108,   109,    -1,   111,   112,   113,    -1,
     115,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,
     135,   136,   137,    19,    -1,    21,    22,    23,    24,    -1,
      -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    48,    49,    50,    -1,    52,    53,    54,    55,
      56,    57,    -1,    59,    60,    61,    -1,    -1,    64,    -1,
      -1,    67,    68,    -1,    70,    71,    72,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,
      86,    -1,    -1,    -1,    -1,    -1,    92,    -1,    -1,    95,
      96,    -1,    98,    99,    -1,    -1,    -1,   103,   104,   105,
      -1,   107,   108,   109,    -1,   111,   112,   113,    -1,   115,
      -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,   135,
     136,   137,    19,    -1,    21,    22,    23,    24,    -1,    -1,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    49,    50,    -1,    52,    53,    54,    55,    56,
      57,    -1,    59,    60,    61,    -1,    -1,    64,    -1,    -1,
      67,    68,    -1,    70,    71,    72,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,    86,
      -1,    -1,    -1,    -1,    -1,    92,    -1,    -1,    95,    96,
      -1,    98,    99,    -1,   101,    -1,   103,    -1,   105,    -1,
     107,   108,   109,    -1,   111,   112,   113,    -1,   115,    -1,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    -1,    -1,    -1,    -1,   135,   136,
     137,    19,    -1,    21,    22,    23,    24,    -1,    -1,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    36,    -1,
      -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      -1,    59,    60,    61,    -1,    -1,    64,    -1,    -1,    67,
      68,    -1,    70,    71,    72,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,    86,    -1,
      -1,    -1,    -1,    -1,    92,    -1,    -1,    95,    96,    -1,
      98,    99,    -1,    -1,    -1,    -1,    -1,   105,    -1,   107,
     108,   109,    -1,   111,   112,   113,    -1,   115,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    -1,    -1,    -1,    -1,   135,   136,   137,
      19,    -1,    21,    22,    23,    24,    -1,    -1,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,
      49,    50,    -1,    52,    53,    54,    55,    56,    57,    -1,
      59,    60,    61,    -1,    -1,    64,    -1,    -1,    67,    68,
      -1,    70,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    85,    86,    -1,    -1,
      -1,    -1,    -1,    92,    -1,    -1,    95,    96,    -1,    98,
      99,    -1,    -1,    -1,   103,    -1,   105,    -1,   107,   108,
     109,    -1,   111,   112,   113,    -1,   115,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    -1,    -1,    -1,    -1,   135,   136,   137,    19,
      -1,    21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,
      50,    -1,    52,    53,    54,    55,    56,    57,    -1,    59,
      60,    61,    -1,    -1,    64,    -1,    -1,    67,    68,    -1,
      70,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    85,    86,    -1,    -1,    -1,
      -1,    -1,    92,    -1,    -1,    95,    96,    -1,    98,    99,
      -1,   101,    -1,    -1,    -1,   105,    -1,   107,   108,   109,
      -1,   111,   112,   113,    -1,   115,    -1,    -1,    -1,    -1,
      -1,    -1,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    -1,    -1,    -1,    -1,   135,   136,   137,    19,    -1,
      21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,    30,
      31,    32,    33,    34,    35,    36,    -1,    -1,    39,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    50,
      -1,    52,    53,    54,    55,    56,    57,    -1,    59,    60,
      61,    -1,    -1,    64,    -1,    -1,    67,    68,    -1,    70,
      71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    85,    86,    -1,    -1,    -1,    -1,
      -1,    92,    -1,    -1,    95,    96,    -1,    98,    99,    -1,
     101,    -1,    -1,    -1,   105,    -1,   107,   108,   109,    -1,
     111,   112,   113,    -1,   115,    -1,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      -1,    -1,    -1,    -1,   135,   136,   137,    19,    -1,    21,
      22,    23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,
      32,    33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    50,    -1,
      52,    53,    54,    55,    56,    57,    -1,    59,    60,    61,
      -1,    -1,    64,    -1,    -1,    67,    68,    -1,    70,    71,
      72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    85,    86,    -1,    -1,    -1,    -1,    -1,
      92,    -1,    -1,    95,    96,    -1,    98,    99,    -1,   101,
      -1,    -1,    -1,   105,    -1,   107,   108,   109,    -1,   111,
     112,   113,    -1,   115,    -1,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    -1,
      -1,    -1,    -1,   135,   136,   137,    19,    -1,    21,    22,
      23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    48,    49,    50,    -1,    52,
      53,    54,    55,    56,    57,    -1,    59,    60,    61,    -1,
      -1,    64,    -1,    -1,    67,    68,    -1,    70,    71,    72,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    85,    86,    -1,    -1,    -1,    -1,    -1,    92,
      -1,    -1,    95,    96,    -1,    98,    99,    -1,   101,    -1,
      -1,    -1,   105,    -1,   107,   108,   109,    -1,   111,   112,
     113,    -1,   115,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    -1,    -1,
      -1,    -1,   135,   136,   137,    19,    -1,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,
      34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    48,    49,    50,    -1,    52,    53,
      54,    55,    56,    57,    -1,    59,    60,    61,    -1,    -1,
      64,    -1,    -1,    67,    68,    -1,    70,    71,    72,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    85,    86,    -1,    -1,    -1,    -1,    -1,    92,    -1,
      -1,    95,    96,    -1,    98,    99,    -1,   101,    -1,    -1,
      -1,   105,    -1,   107,   108,   109,    -1,   111,   112,   113,
      -1,   115,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    -1,    -1,    -1,
      -1,   135,   136,   137,    19,    -1,    21,    22,    23,    24,
      -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    49,    50,    -1,    52,    53,    54,
      55,    56,    57,    -1,    59,    60,    61,    -1,    -1,    64,
      -1,    -1,    67,    68,    -1,    70,    71,    72,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      85,    86,    -1,    -1,    -1,    -1,    -1,    92,    -1,    -1,
      95,    96,    -1,    98,    99,    -1,    -1,    -1,    -1,    -1,
     105,    -1,   107,   108,   109,    -1,   111,   112,   113,    -1,
     115,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,
     135,   136,   137,    19,    -1,    21,    22,    23,    24,    -1,
      -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    48,    49,    50,    -1,    52,    53,    54,    55,
      56,    57,    -1,    59,    60,    61,    -1,    -1,    64,    -1,
      -1,    67,    68,    -1,    70,    71,    72,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,
      86,    -1,    -1,    -1,    -1,    -1,    92,    -1,    -1,    95,
      96,    -1,    98,    99,    -1,    -1,    -1,    -1,    -1,   105,
      -1,   107,   108,   109,    -1,   111,   112,   113,    -1,   115,
      -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,   135,
     136,   137,    19,    -1,    21,    22,    23,    24,    -1,    -1,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    49,    50,    -1,    52,    53,    54,    55,    56,
      57,    -1,    59,    60,    61,    -1,    -1,    64,    -1,    -1,
      67,    68,    -1,    70,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    89,    -1,    -1,    92,    -1,    -1,    95,    96,
      -1,    98,    99,    -1,    -1,    -1,    -1,    -1,   105,    -1,
     107,   108,   109,    -1,   111,   112,   113,    -1,   115,    -1,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    19,   135,    21,
      22,    23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,
      32,    33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    50,    -1,
      52,    53,    54,    55,    56,    57,    -1,    59,    60,    61,
      -1,    -1,    64,    -1,    -1,    67,    68,    -1,    70,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      92,    -1,    -1,    95,    96,    -1,    98,    99,    -1,   101,
      -1,    -1,    -1,   105,    -1,   107,   108,   109,    -1,   111,
     112,   113,    -1,   115,    -1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    19,   135,    21,    22,    23,    24,    -1,    -1,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    49,    50,    -1,    52,    53,    54,    55,    56,
      57,    -1,    59,    60,    61,    -1,    -1,    64,    -1,    -1,
      67,    68,    -1,    70,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    92,    -1,    -1,    95,    96,
      -1,    98,    99,    -1,   101,    -1,    -1,    -1,   105,    -1,
     107,   108,   109,    -1,   111,   112,   113,    -1,   115,    -1,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    19,   135,    21,
      22,    23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,
      32,    33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    50,    -1,
      52,    53,    54,    55,    56,    57,    -1,    59,    60,    61,
      -1,    -1,    64,    -1,    -1,    67,    68,    -1,    70,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      92,    -1,    -1,    95,    96,    -1,    98,    99,    -1,    -1,
      -1,    -1,    -1,   105,    -1,   107,   108,   109,    -1,   111,
     112,   113,    -1,   115,    -1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    19,   135,    21,    22,    23,    24,    -1,    -1,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    49,    50,    -1,    52,    53,    54,    55,    56,
      57,    -1,    59,    60,    61,    -1,    -1,    64,    -1,    -1,
      67,    68,    -1,    70,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    92,    -1,    -1,    95,    96,
      -1,    98,    99,    -1,    -1,    -1,    -1,    -1,   105,    -1,
     107,   108,   109,    -1,   111,   112,   113,    -1,   115,    -1,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    19,   135,    21,
      22,    23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,
      32,    33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    50,    -1,
      52,    53,    54,    55,    56,    57,    -1,    59,    60,    61,
      -1,    -1,    64,    -1,    -1,    67,    68,    -1,    70,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      92,    -1,    -1,    95,    96,    -1,    98,    99,    -1,    -1,
      -1,    -1,    -1,   105,    -1,   107,   108,   109,    -1,   111,
     112,   113,    -1,   115,    -1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    19,   135,    21,    22,    23,    24,    -1,    -1,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    39,    -1,    -1,    44,    -1,    -1,    -1,    -1,
      -1,    48,    49,    50,    -1,    52,    53,    54,    55,    56,
      57,    -1,    59,    60,    61,    -1,    -1,    64,    -1,    -1,
      67,    68,    -1,    70,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    -1,    -1,    -1,    -1,
      89,    90,    -1,    -1,    -1,    92,    -1,    -1,    95,    96,
      -1,    98,    99,   102,    -1,    -1,    -1,    -1,   105,    -1,
     107,   108,   109,    -1,   111,   112,   113,    -1,   115,    -1,
      -1,    -1,    -1,    -1,   123,    -1,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,    52,    53,   135,    -1,
      56,    -1,    -1,    -1,    -1,    -1,   145,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    71,    72,    73,    74,    75,
      76,    77,    78,    -1,    -1,    81,    82,    -1,    -1,    -1,
      -1,    87,    88,    89,    90,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   101,   102,   103,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,    -1,
     136,   137,    52,    53,    -1,    -1,    56,   143,    -1,    -1,
     146,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    71,    72,    73,    74,    75,    76,    77,    78,    -1,
      -1,    81,    82,    -1,    -1,    -1,    -1,    87,    88,    89,
      90,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   101,   102,   103,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,    -1,   136,   137,    52,    53,
      -1,    -1,    56,   143,    -1,    -1,   146,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,    72,    73,
      74,    75,    76,    77,    78,    -1,    -1,    81,    82,    -1,
      -1,    -1,    -1,    87,    88,    89,    90,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,   102,   103,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,    -1,   136,   137,    52,    53,    -1,    -1,    56,   143,
      -1,    -1,   146,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    71,    72,    73,    74,    75,    76,    77,
      78,    -1,    -1,    81,    82,    -1,    -1,    -1,    -1,    87,
      88,    89,    90,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   101,   102,   103,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,    -1,   136,   137,
      52,    53,    -1,    -1,    56,   143,    -1,    -1,   146,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,
      72,    73,    74,    75,    76,    77,    78,    -1,    -1,    81,
      82,    -1,    -1,    -1,    -1,    87,    88,    89,    90,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,
     102,   103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,    -1,   136,   137,    52,    53,    -1,    -1,
      56,   143,    -1,    -1,   146,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    71,    72,    73,    74,    75,
      76,    77,    78,    -1,    -1,    81,    82,    -1,    -1,    -1,
      -1,    87,    88,    89,    90,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   101,   102,   103,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,    -1,
     136,   137,    52,    53,    -1,    -1,    56,   143,    -1,    -1,
     146,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    71,    72,    73,    74,    75,    76,    77,    78,    -1,
      -1,    81,    82,    -1,    -1,    -1,    -1,    87,    88,    89,
      90,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   101,   102,   103,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,    -1,   136,   137,    52,    53,
      -1,    -1,    56,   143,    -1,    -1,   146,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,    72,    73,
      74,    75,    76,    77,    78,    -1,    -1,    81,    82,    -1,
      -1,    -1,    -1,    87,    88,    89,    90,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,   102,   103,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,    -1,   136,   137,    52,    53,    -1,    -1,    56,   143,
      -1,    -1,   146,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    71,    72,    73,    74,    75,    76,    77,
      78,    -1,    -1,    81,    82,    -1,    -1,    -1,    -1,    87,
      88,    89,    90,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   101,   102,   103,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,    -1,   136,   137,
      52,    53,    -1,    -1,    56,   143,    -1,    -1,   146,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,
      72,    73,    74,    75,    76,    77,    78,    -1,    -1,    81,
      82,    -1,    -1,    -1,    -1,    87,    88,    89,    90,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,
     102,   103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,    -1,   136,   137,    52,    53,    -1,    -1,
      56,   143,    -1,    -1,   146,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    71,    72,    73,    74,    75,
      76,    77,    78,    -1,    -1,    81,    82,    -1,    -1,    -1,
      -1,    87,    88,    89,    90,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   101,   102,   103,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,    -1,
     136,   137,    52,    53,    -1,    -1,    56,   143,    -1,    -1,
     146,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    71,    72,    73,    74,    75,    76,    77,    78,    -1,
      -1,    81,    82,    -1,    -1,    -1,    -1,    87,    88,    89,
      90,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   101,   102,   103,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,    -1,   136,   137,    52,    53,
      -1,    -1,    56,   143,    -1,    -1,   146,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,    72,    73,
      74,    75,    76,    77,    78,    -1,    -1,    81,    82,    -1,
      -1,    -1,    -1,    87,    88,    89,    90,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,   102,   103,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,    -1,   136,   137,    52,    53,    -1,    -1,    56,   143,
      -1,    -1,   146,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    71,    72,    73,    74,    75,    76,    77,
      78,    -1,    -1,    81,    82,    -1,    -1,    -1,    -1,    87,
      88,    89,    90,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   101,   102,   103,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,    -1,   136,   137,
      52,    53,    -1,    -1,    56,   143,    -1,    -1,   146,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,
      72,    73,    74,    75,    76,    77,    78,    -1,    -1,    81,
      82,    -1,    -1,    -1,    -1,    87,    88,    89,    90,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,
     102,   103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    44,    -1,    -1,    -1,
      -1,    -1,    -1,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,    -1,   136,   137,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   146,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    -1,    -1,    -1,
      -1,    89,    90,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   102,    -1,    -1,    -1,    44,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   123,    -1,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    -1,
      -1,    -1,    -1,    89,    90,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   102,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   123,    -1,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    -1,    -1,    -1,    -1,    89,    90,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   123,
      -1,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   145,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    -1,    -1,    -1,    -1,    89,    90,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   102,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   123,    -1,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   145,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    -1,    -1,    -1,
      -1,    89,    90,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   102,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   123,    -1,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   145,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      -1,    -1,    -1,    -1,    89,    90,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   123,    -1,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     145,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    -1,    -1,    -1,    -1,    89,    90,    -1,
      -1,    -1,    94,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     102,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   123,    -1,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    -1,    -1,    -1,    -1,    89,
      90,    -1,    -1,    -1,    94,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   102,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   123,    -1,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    -1,    -1,    -1,
      -1,    89,    90,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   102,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   123,    -1,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    -1,
      -1,    -1,    -1,    89,    90,    73,    74,    75,    76,    77,
      78,    79,    -1,    81,    82,    -1,   102,    -1,    -1,    -1,
      -1,    89,    90,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   102,    -1,    -1,    -1,    -1,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,    73,    74,    75,
      76,    77,    78,    -1,    -1,    81,    82,    -1,    -1,    -1,
      -1,    -1,    -1,    89,    90,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   102,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int16 yystos[] =
{
       0,   151,   152,     1,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    19,    21,    22,    23,    24,    30,
      31,    32,    33,    34,    35,    36,    39,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      59,    60,    61,    64,    67,    68,    70,    71,    72,    85,
      86,    92,    95,    96,    98,    99,   101,   105,   107,   108,
     109,   111,   112,   113,   115,   135,   136,   137,   153,   154,
     155,   161,   162,   164,   165,   166,   167,   168,   170,   172,
     173,   176,   177,   179,   180,   181,   183,   184,   193,   207,
     224,   245,   246,   256,   257,   258,   262,   263,   264,   270,
     271,   272,   274,   275,   276,   277,   278,   279,   315,   328,
       0,   155,    21,    22,    30,    31,    32,    39,    52,    56,
      70,    89,    92,    95,   135,   168,   170,   185,   186,   207,
     224,   276,   279,   315,   186,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    56,    71,
      72,    73,    74,    75,    76,    77,    78,    81,    82,    87,
      88,    89,    90,   101,   102,   103,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   136,   137,   143,   146,
     187,   191,   192,   278,   310,   208,    92,   164,   168,   170,
     171,   184,   193,   224,   276,   277,   279,   171,   214,   216,
      70,    92,   177,   184,   224,   229,   276,   279,    33,    34,
      35,    36,    48,    49,    50,    52,    56,   107,   187,   188,
     189,   272,   116,   119,   120,   147,   149,   171,   266,   267,
     268,   321,   325,   326,   327,    52,    70,   101,   103,   104,
     136,   176,   193,   199,   202,   205,   258,   313,   314,   199,
     199,   143,   196,   197,   200,   201,   328,   196,   201,   143,
     322,   188,   156,   139,   143,   164,   193,   224,   193,   193,
     193,    56,     1,    95,   158,   159,   161,   178,   179,   328,
     209,   211,   194,   205,   313,   328,   193,   312,   313,   328,
      92,   145,   183,   224,   276,   279,   212,    54,    55,    57,
      64,    70,   108,   187,   273,    64,    65,    66,   117,   118,
     259,   260,    62,   259,    63,   259,    64,   259,    64,   259,
      59,    60,   172,   193,   193,   321,   327,    40,    41,    42,
      43,    44,    37,    38,    52,    54,    55,    56,    57,    70,
      84,    95,   101,   102,   103,   104,   129,   132,   143,   282,
     283,   284,   285,   286,   289,   290,   291,   292,   294,   295,
     296,   297,   299,   300,   301,   304,   305,   306,   307,   308,
     328,   282,   284,    28,   244,   122,   145,    95,   101,   180,
     122,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    89,    90,    94,   102,   123,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,    91,   106,
     141,   148,   319,    91,   319,   320,    26,   139,   248,   258,
      93,    93,   196,   201,   248,   164,    52,    56,   185,    59,
      60,   283,   126,   280,    91,   141,   319,   223,   311,    91,
     148,   318,   157,   158,    56,   282,   282,    16,   225,   325,
     122,    91,   141,   319,    93,    93,   225,   171,   171,    56,
      91,   141,   319,    25,   108,   145,   269,   321,   116,   268,
      20,   250,   325,    58,    58,   193,   193,   193,    94,   145,
     203,   204,   328,    58,   203,   204,    86,   198,   199,   205,
     313,   328,   199,   164,   321,   323,   164,   326,   160,   139,
     158,    92,   207,   224,    91,   319,    93,   161,   178,   144,
     321,   327,   323,   161,   323,   142,   204,   324,   327,   204,
     324,   140,   324,    56,   180,   181,   182,   145,    91,   141,
     319,   143,   241,   294,   299,    64,   259,   261,   265,   266,
      64,   260,    62,    63,    64,    64,   102,   102,   155,   171,
     171,   171,   171,   161,   164,   164,    58,   122,    58,   325,
     298,    86,   294,   299,   122,   157,   193,   145,   309,   328,
      52,   145,   309,   325,   145,   293,   193,   145,   293,    52,
     145,   293,    52,   122,   157,   243,   101,   172,   193,   205,
     206,   178,   145,   183,   145,   162,   163,   172,   184,   193,
     195,   206,   224,   279,   193,   193,   193,   193,   193,   193,
     193,   193,   193,   193,   193,   193,   193,   193,    52,   193,
     193,   193,   193,   193,   193,   193,   193,   193,   193,   193,
     193,    52,    53,    56,   191,   196,   316,   317,   198,   205,
      52,    53,    56,   191,   196,   316,    52,    56,   316,   249,
     247,   163,   193,   195,   163,   195,   100,   175,   221,   281,
     220,    52,    56,   185,   316,   198,   316,   157,   164,   169,
      15,    13,   252,   328,   122,   122,   158,    16,    52,    56,
     198,    52,    56,   158,    27,   226,   325,   226,    52,    56,
     198,    52,    56,   218,   190,   158,   250,   193,   205,    15,
     193,   193,   193,   322,   101,   193,   202,   313,   193,   314,
     323,   144,   321,   204,   204,   323,   144,   188,   153,   140,
      56,   144,    91,   195,   323,   161,   210,   313,   180,   182,
      52,    56,   198,    52,    56,   294,   213,   145,    64,   158,
     266,   193,   193,    52,    70,   101,   230,   299,   323,   323,
     145,   176,   193,    15,    52,    70,   286,   291,   308,    86,
     292,   297,   304,   306,   299,   301,   306,    52,   299,   176,
     193,    15,    80,   127,   235,   237,   328,   193,   204,   323,
     182,   145,    44,   122,    44,    91,   141,   319,   322,    93,
      93,   196,   201,   142,   204,    93,    93,   197,   201,   197,
     201,   235,   235,   174,   325,   171,   157,   142,    15,   323,
     187,   193,   206,   253,   328,    18,   228,   328,    17,   227,
     228,    93,    93,   142,    93,    93,   228,   215,   217,   142,
     171,   188,   140,    15,   204,   225,   193,   203,    86,   313,
     140,    52,    56,   323,   324,   142,   238,   322,    29,   114,
     242,   140,   145,   296,   323,   145,    86,    44,    44,   309,
     325,   145,   293,   145,   293,   145,   293,   145,   293,   293,
      44,    44,   232,   234,   236,   285,   287,   288,   291,   299,
     300,   302,   303,   306,   308,   157,   101,   193,   182,   161,
     193,    52,    56,   198,    52,    56,    58,   124,   163,   195,
     172,   195,   175,    93,   163,   195,   163,   195,   175,   248,
     244,   157,   158,   235,   222,   325,    15,    94,   254,   328,
     158,    14,   255,   328,   171,    15,    93,    15,   158,   158,
     226,   193,   158,   323,   204,   144,   147,   157,   158,   231,
     145,   101,   323,   193,   193,   299,   306,   299,   299,   193,
     193,   238,   238,   224,   145,   309,   309,   145,   233,   224,
     145,   233,   145,   233,    15,   193,   142,   193,   193,   163,
     195,    15,   140,   158,   157,    92,   184,   224,   276,   279,
     225,   158,   225,    15,    15,   219,   228,   250,   251,    52,
     239,   240,   295,    15,   140,   299,   299,   145,   296,   293,
     145,   293,   293,   293,   127,   127,   287,   291,   145,   232,
     233,   303,   306,   299,   302,   306,   299,   140,    15,    56,
      91,   141,   319,   158,   158,   158,   145,   322,   145,   299,
     145,   299,   309,   145,   233,   145,   233,   145,   233,   145,
     233,   233,    52,    56,   198,    52,    56,   252,   227,    15,
     240,   299,   293,   299,   306,   299,   299,   142,   233,   145,
     233,   233,   233,   299,   233
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int16 yyr1[] =
{
       0,   150,   151,   152,   153,   154,   154,   154,   154,   155,
     156,   155,   157,   158,   159,   159,   159,   159,   160,   161,
     161,   161,   161,   161,   161,   161,   161,   161,   161,   161,
     161,   161,   161,   161,   162,   162,   162,   162,   162,   162,
     162,   162,   162,   162,   162,   162,   163,   163,   163,   164,
     164,   164,   164,   164,   164,   164,   165,   166,   167,   167,
     168,   169,   170,   171,   172,   172,   173,   173,   174,   175,
     176,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   177,   177,   178,   178,   179,   179,   179,   179,   179,
     179,   179,   179,   179,   179,   180,   180,   181,   181,   182,
     182,   183,   183,   183,   183,   183,   183,   183,   183,   184,
     184,   184,   184,   184,   184,   184,   184,   184,   185,   185,
     186,   186,   186,   187,   187,   187,   187,   187,   188,   188,
     189,   190,   189,   191,   191,   191,   191,   191,   191,   191,
     191,   191,   191,   191,   191,   191,   191,   191,   191,   191,
     191,   191,   191,   191,   191,   191,   191,   191,   191,   191,
     191,   191,   191,   192,   192,   192,   192,   192,   192,   192,
     192,   192,   192,   192,   192,   192,   192,   192,   192,   192,
     192,   192,   192,   192,   192,   192,   192,   192,   192,   192,
     192,   192,   192,   192,   192,   192,   192,   192,   192,   192,
     192,   192,   192,   192,   193,   193,   193,   193,   193,   193,
     193,   193,   193,   193,   193,   193,   193,   193,   193,   193,
     193,   193,   193,   193,   193,   193,   193,   193,   193,   193,
     193,   193,   193,   193,   193,   193,   193,   193,   193,   193,
     193,   193,   193,   193,   193,   193,   193,   193,   193,   193,
     193,   193,   193,   193,   193,   194,   194,   194,   194,   195,
     195,   196,   196,   196,   197,   197,   198,   198,   198,   198,
     198,   199,   199,   199,   199,   199,   200,   201,   202,   202,
     203,   203,   204,   205,   205,   205,   205,   205,   205,   206,
     206,   206,   207,   207,   207,   207,   207,   207,   207,   207,
     208,   207,   209,   210,   207,   211,   207,   207,   207,   207,
     207,   207,   207,   207,   207,   207,   207,   207,   207,   212,
     213,   207,   207,   207,   214,   215,   207,   216,   217,   207,
     207,   207,   218,   219,   207,   220,   207,   221,   222,   207,
     223,   207,   207,   207,   207,   207,   207,   207,   224,   225,
     225,   225,   226,   226,   227,   227,   228,   228,   229,   229,
     230,   230,   230,   230,   230,   230,   230,   230,   231,   230,
     232,   232,   232,   232,   233,   233,   234,   234,   234,   234,
     234,   234,   234,   234,   234,   234,   234,   234,   234,   234,
     234,   235,   235,   236,   237,   237,   237,   238,   238,   239,
     239,   240,   240,   241,   241,   242,   242,   243,   244,   245,
     245,   245,   245,   246,   246,   246,   246,   246,   246,   246,
     246,   246,   247,   248,   249,   248,   250,   251,   251,   252,
     252,   253,   253,   253,   254,   254,   255,   255,   256,   256,
     256,   256,   257,   257,   258,   258,   258,   258,   259,   259,
     260,   261,   260,   260,   260,   262,   262,   263,   263,   264,
     265,   265,   266,   266,   267,   267,   268,   269,   268,   270,
     270,   271,   271,   271,   272,   273,   273,   273,   273,   273,
     273,   274,   274,   275,   275,   275,   275,   276,   276,   276,
     276,   276,   277,   277,   278,   278,   278,   278,   278,   278,
     278,   278,   278,   279,   279,   280,   281,   280,   282,   282,
     283,   283,   283,   284,   284,   284,   284,   285,   285,   286,
     286,   287,   287,   288,   288,   289,   289,   290,   290,   291,
     291,   292,   292,   292,   292,   293,   293,   294,   294,   294,
     294,   294,   294,   294,   294,   294,   294,   294,   294,   294,
     294,   294,   295,   295,   295,   295,   295,   296,   296,   297,
     298,   297,   299,   299,   300,   301,   302,   303,   303,   304,
     304,   305,   305,   306,   306,   307,   307,   308,   308,   309,
     309,   310,   311,   310,   312,   312,   313,   313,   314,   314,
     314,   314,   314,   314,   314,   314,   315,   315,   315,   316,
     316,   316,   316,   317,   317,   317,   318,   318,   319,   319,
     320,   320,   321,   321,   322,   322,   323,   324,   324,   324,
     325,   325,   326,   326,   327,   327,   328
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     2,     1,     1,     3,     2,     1,
       0,     5,     4,     2,     1,     1,     3,     2,     0,     4,
       2,     3,     3,     3,     3,     3,     4,     1,     3,     3,
       3,     3,     3,     1,     3,     3,     6,     5,     5,     5,
       5,     4,     6,     4,     6,     3,     1,     3,     1,     1,
       3,     3,     3,     2,     1,     1,     4,     2,     1,     1,
       2,     0,     5,     1,     1,     1,     1,     4,     0,     5,
       2,     3,     4,     5,     4,     5,     2,     2,     2,     2,
       2,     1,     3,     1,     3,     1,     2,     3,     5,     2,
       4,     2,     4,     1,     3,     1,     3,     2,     3,     1,
       2,     1,     4,     3,     3,     3,     3,     2,     1,     1,
       4,     3,     3,     3,     3,     2,     1,     1,     1,     1,
       2,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     6,     5,     5,     5,
       5,     4,     3,     3,     2,     2,     3,     2,     2,     3,
       3,     3,     3,     3,     3,     4,     4,     2,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     3,     3,     3,     3,     6,     6,
       4,     6,     4,     6,     1,     1,     2,     4,     2,     1,
       3,     3,     5,     3,     1,     1,     1,     2,     2,     4,
       2,     1,     2,     2,     4,     1,     0,     2,     2,     1,
       2,     1,     2,     1,     1,     2,     3,     3,     4,     3,
       4,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     0,     5,     0,     3,     3,     3,     2,
       3,     3,     1,     2,     4,     3,     2,     1,     2,     0,
       0,     5,     6,     6,     0,     0,     7,     0,     0,     7,
       5,     4,     0,     0,     9,     0,     6,     0,     0,     8,
       0,     5,     4,     4,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     1,     1,     5,     1,     2,     1,     1,
       1,     4,     6,     3,     5,     2,     4,     1,     0,     4,
       4,     2,     2,     1,     2,     0,     6,     8,     4,     6,
       4,     3,     6,     2,     4,     6,     2,     4,     2,     4,
       1,     1,     1,     0,     4,     1,     4,     1,     4,     1,
       3,     1,     1,     4,     1,     3,     3,     0,     5,     2,
       4,     5,     5,     2,     4,     4,     3,     3,     3,     2,
       1,     4,     0,     5,     0,     5,     5,     1,     1,     6,
       1,     1,     1,     1,     2,     1,     2,     1,     1,     1,
       1,     1,     1,     2,     1,     1,     2,     3,     1,     2,
       1,     0,     4,     1,     2,     2,     3,     2,     3,     1,
       1,     2,     1,     2,     1,     2,     1,     0,     4,     2,
       3,     1,     4,     2,     2,     1,     1,     1,     1,     1,
       2,     2,     3,     1,     1,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     0,     4,     1,     1,
       3,     5,     3,     1,     2,     4,     2,     2,     2,     2,
       1,     2,     1,     1,     3,     1,     3,     1,     1,     2,
       1,     4,     2,     2,     1,     2,     0,     6,     8,     4,
       6,     4,     6,     2,     4,     6,     2,     4,     2,     4,
       1,     0,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     3,     2,     2,     2,     1,     3,     1,
       3,     1,     1,     2,     1,     1,     1,     2,     1,     2,
       1,     1,     0,     4,     1,     2,     1,     3,     3,     3,
       2,     2,     3,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     1,     0,     2,     2,     0,     1,     1,
       1,     1,     1,     1,     1,     2,     0
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (&yylloc, p, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc, p)  YY_LOCATION_PRINT(File, *(Loc), p)

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc, p)  YYLOCATION_PRINT(File, &(Loc), p)

#  else

#   define YYLOCATION_PRINT(File, Loc, p) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location, p) \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, p);          \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, parser_state *p)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (p);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
switch (yykind)
    {
      default:
        break;
    }
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, parser_state *p)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp, p);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, p);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop, parser_state *p)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top, p)     \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top), p);    \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, parser_state *p)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), p);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule, p) \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, p); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
#ifndef yydebug
int yydebug;
#endif
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location, p)
# define YY_STACK_PRINT(Bottom, Top, p)
# define YY_REDUCE_PRINT(Rule, p)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx, parser_state *p)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, parser_state *p)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (p);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp, p);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yykind)
    {
      default:
        break;
    }
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (parser_state *p)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
#ifdef __cplusplus
static const YYSTYPE yyval_default = {};
(void) yyval_default;
#else
YY_INITIAL_VALUE (static const YYSTYPE yyval_default;)
#endif
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static const YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs = 0;
    YY_USE (yynerrs); /* Silence compiler warning.  */

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */



#line 6944 "mrbgems/mruby-compiler/core/y.tab.c"

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp, p);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, &yylloc, p);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc, p);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc, p);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;


  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn, p);
  switch (yyn)
    {
  case 2: /* $@1: %empty  */
#line 2047 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      p->lstate = EXPR_BEG;
                      if (!p->locals) p->locals = cons(0,0);
                    }
#line 7162 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 3: /* program: $@1 top_compstmt  */
#line 2052 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      p->tree = new_scope(p, (yyvsp[0].nd));
                    }
#line 7170 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 4: /* top_compstmt: top_stmts opt_terms  */
#line 2058 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[-1].nd);
                    }
#line 7178 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 5: /* top_stmts: none  */
#line 2064 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_stmts(p, 0);
                    }
#line 7186 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 6: /* top_stmts: top_stmt  */
#line 2068 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_stmts(p, (yyvsp[0].nd));
                    }
#line 7194 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 7: /* top_stmts: top_stmts terms top_stmt  */
#line 2072 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = push((yyvsp[-2].nd), newline_node((yyvsp[0].nd)));
                    }
#line 7202 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 8: /* top_stmts: error top_stmt  */
#line 2076 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_stmts(p, 0);
                    }
#line 7210 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 10: /* @2: %empty  */
#line 2083 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = local_switch(p);
                      nvars_block(p);
                    }
#line 7219 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 11: /* top_stmt: "'BEGIN'" @2 '{' top_compstmt '}'  */
#line 2088 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      yyerror(&(yylsp[-4]), p, "BEGIN not supported");
                      local_resume(p, (yyvsp[-3].nd));
                      nvars_unnest(p);
                      (yyval.nd) = 0;
                    }
#line 7230 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 12: /* bodystmt: compstmt opt_rescue opt_else opt_ensure  */
#line 2100 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      if ((yyvsp[-2].nd)) {
                        (yyval.nd) = new_rescue(p, (yyvsp[-3].nd), (yyvsp[-2].nd), (yyvsp[-1].nd));
                      }
                      else if ((yyvsp[-1].nd)) {
                        yywarning(p, "else without rescue is useless");
                        (yyval.nd) = push((yyvsp[-3].nd), (yyvsp[-1].nd));
                      }
                      else {
                        (yyval.nd) = (yyvsp[-3].nd);
                      }
                      if ((yyvsp[0].nd)) {
                        if ((yyval.nd)) {
                          (yyval.nd) = new_ensure(p, (yyval.nd), (yyvsp[0].nd));
                        }
                        else {
                          (yyval.nd) = push((yyvsp[0].nd), new_nil(p));
                        }
                      }
                    }
#line 7255 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 13: /* compstmt: stmts opt_terms  */
#line 2123 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[-1].nd);
                    }
#line 7263 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 14: /* stmts: none  */
#line 2129 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_stmts(p, 0);
                    }
#line 7271 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 15: /* stmts: stmt  */
#line 2133 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_stmts(p, (yyvsp[0].nd));
                    }
#line 7279 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 16: /* stmts: stmts terms stmt  */
#line 2137 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      /* Update the cons-list inside the existing variable-sized node */
                      stmts_node((yyvsp[-2].nd))->stmts = push(stmts_node((yyvsp[-2].nd))->stmts, newline_node((yyvsp[0].nd)));
                      (yyval.nd) = (yyvsp[-2].nd);
                    }
#line 7289 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 17: /* stmts: error stmt  */
#line 2143 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_stmts(p, (yyvsp[0].nd));
                    }
#line 7297 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 18: /* $@3: %empty  */
#line 2148 "mrbgems/mruby-compiler/core/parse.y"
                                     {p->lstate = EXPR_FNAME;}
#line 7303 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 19: /* stmt: "'alias'" fsym $@3 fsym  */
#line 2149 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_alias(p, (yyvsp[-2].id), (yyvsp[0].id));
                    }
#line 7311 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 20: /* stmt: "'undef'" undef_list  */
#line 2153 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_undef(p, (yyvsp[0].nd));
                    }
#line 7319 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 21: /* stmt: stmt "'if' modifier" expr_value  */
#line 2157 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_if(p, cond((yyvsp[0].nd)), (yyvsp[-2].nd), 0);
                    }
#line 7327 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 22: /* stmt: stmt "'unless' modifier" expr_value  */
#line 2161 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_if(p, cond((yyvsp[0].nd)), 0, (yyvsp[-2].nd));
                    }
#line 7335 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 23: /* stmt: stmt "'while' modifier" expr_value  */
#line 2165 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      if ((yyvsp[-2].nd) && node_type_p((yyvsp[-2].nd), NODE_BEGIN)) {
                        (yyval.nd) = new_while_mod(p, cond((yyvsp[0].nd)), (yyvsp[-2].nd));
                      }
                      else {
                        (yyval.nd) = new_while(p, cond((yyvsp[0].nd)), (yyvsp[-2].nd));
                      }
                    }
#line 7348 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 24: /* stmt: stmt "'until' modifier" expr_value  */
#line 2174 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      if ((yyvsp[-2].nd) && node_type_p((yyvsp[-2].nd), NODE_BEGIN)) {
                        (yyval.nd) = new_until_mod(p, cond((yyvsp[0].nd)), (yyvsp[-2].nd));
                      }
                      else {
                        (yyval.nd) = new_until(p, cond((yyvsp[0].nd)), (yyvsp[-2].nd));
                      }
                    }
#line 7361 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 25: /* stmt: stmt "'rescue' modifier" stmt  */
#line 2183 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_mod_rescue(p, (yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 7369 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 26: /* stmt: "'END'" '{' compstmt '}'  */
#line 2187 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      yyerror(&(yylsp[-3]), p, "END not supported");
                      (yyval.nd) = new_postexe(p, (yyvsp[-1].nd));
                    }
#line 7378 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 28: /* stmt: mlhs '=' command_call  */
#line 2193 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_masgn(p, (yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 7386 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 29: /* stmt: lhs '=' mrhs  */
#line 2197 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_asgn(p, (yyvsp[-2].nd), new_array(p, (yyvsp[0].nd)));
                    }
#line 7394 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 30: /* stmt: mlhs '=' arg  */
#line 2201 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_masgn(p, (yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 7402 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 31: /* stmt: mlhs '=' mrhs  */
#line 2205 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_masgn(p, (yyvsp[-2].nd), new_array(p, (yyvsp[0].nd)));
                    }
#line 7410 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 32: /* stmt: arg "=>" "local variable or method"  */
#line 2209 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      node *lhs = new_lvar(p, (yyvsp[0].id));
                      assignable(p, lhs);
                      (yyval.nd) = new_asgn(p, lhs, (yyvsp[-2].nd));
                    }
#line 7420 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 34: /* command_asgn: lhs '=' command_rhs  */
#line 2218 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_asgn(p, (yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 7428 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 35: /* command_asgn: var_lhs tOP_ASGN command_rhs  */
#line 2222 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_op_asgn(p, (yyvsp[-2].nd), (yyvsp[-1].id), (yyvsp[0].nd));
                    }
#line 7436 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 36: /* command_asgn: primary_value '[' opt_call_args ']' tOP_ASGN command_rhs  */
#line 2226 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_op_asgn(p, new_call(p, (yyvsp[-5].nd), intern_op(aref), (yyvsp[-3].nd), '.'), (yyvsp[-1].id), (yyvsp[0].nd));
                    }
#line 7444 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 37: /* command_asgn: primary_value call_op "local variable or method" tOP_ASGN command_rhs  */
#line 2230 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_op_asgn(p, new_call(p, (yyvsp[-4].nd), (yyvsp[-2].id), 0, (yyvsp[-3].num)), (yyvsp[-1].id), (yyvsp[0].nd));
                    }
#line 7452 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 38: /* command_asgn: primary_value call_op "constant" tOP_ASGN command_rhs  */
#line 2234 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_op_asgn(p, new_call(p, (yyvsp[-4].nd), (yyvsp[-2].id), 0, (yyvsp[-3].num)), (yyvsp[-1].id), (yyvsp[0].nd));
                    }
#line 7460 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 39: /* command_asgn: primary_value "::" "constant" tOP_ASGN command_call  */
#line 2238 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      yyerror(&(yylsp[-4]), p, "constant re-assignment");
                      (yyval.nd) = 0;
                    }
#line 7469 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 40: /* command_asgn: primary_value "::" "local variable or method" tOP_ASGN command_rhs  */
#line 2243 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_op_asgn(p, new_call(p, (yyvsp[-4].nd), (yyvsp[-2].id), 0, tCOLON2), (yyvsp[-1].id), (yyvsp[0].nd));
                    }
#line 7477 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 41: /* command_asgn: defn_head f_opt_arglist_paren '=' command  */
#line 2247 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[-3].nd);
                      endless_method_name(p, (yyvsp[-3].nd));
                      void_expr_error(p, (yyvsp[0].nd));
                      defn_setup(p, (yyval.nd), (yyvsp[-2].nd), (yyvsp[0].nd));
                      nvars_unnest(p);
                      p->in_def--;
                    }
#line 7490 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 42: /* command_asgn: defn_head f_opt_arglist_paren '=' command "'rescue' modifier" arg  */
#line 2256 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[-5].nd);
                      endless_method_name(p, (yyvsp[-5].nd));
                      void_expr_error(p, (yyvsp[-2].nd));
                      defn_setup(p, (yyval.nd), (yyvsp[-4].nd), new_mod_rescue(p, (yyvsp[-2].nd), (yyvsp[0].nd)));
                      nvars_unnest(p);
                      p->in_def--;
                    }
#line 7503 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 43: /* command_asgn: defs_head f_opt_arglist_paren '=' command  */
#line 2265 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[-3].nd);
                      void_expr_error(p, (yyvsp[0].nd));
                      defn_setup(p, (yyval.nd), (yyvsp[-2].nd), (yyvsp[0].nd));
                      nvars_unnest(p);
                      p->in_def--;
                      p->in_single--;
                    }
#line 7516 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 44: /* command_asgn: defs_head f_opt_arglist_paren '=' command "'rescue' modifier" arg  */
#line 2274 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[-5].nd);
                      void_expr_error(p, (yyvsp[-2].nd));
                      defn_setup(p, (yyval.nd), (yyvsp[-4].nd), new_mod_rescue(p, (yyvsp[-2].nd), (yyvsp[0].nd)));
                      nvars_unnest(p);
                      p->in_def--;
                      p->in_single--;
                    }
#line 7529 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 45: /* command_asgn: backref tOP_ASGN command_rhs  */
#line 2283 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      backref_error(p, (yyvsp[-2].nd));
                      (yyval.nd) = new_stmts(p, 0);
                    }
#line 7538 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 47: /* command_rhs: command_call "'rescue' modifier" stmt  */
#line 2291 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_mod_rescue(p, (yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 7546 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 50: /* expr: expr "'and'" expr  */
#line 2299 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_and(p, (yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 7554 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 51: /* expr: expr "'or'" expr  */
#line 2303 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_or(p, (yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 7562 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 52: /* expr: "'not'" opt_nl expr  */
#line 2307 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_uni_op(p, cond((yyvsp[0].nd)), "!");
                    }
#line 7570 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 53: /* expr: '!' command_call  */
#line 2311 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_uni_op(p, cond((yyvsp[0].nd)), "!");
                    }
#line 7578 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 60: /* defn_head: "'def'" fname  */
#line 2326 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_def(p, (yyvsp[0].id));
                      p->cmdarg_stack = 0;
                      p->in_def++;
                      nvars_block(p);
                    }
#line 7589 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 61: /* $@4: %empty  */
#line 2335 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      p->lstate = EXPR_FNAME;
                    }
#line 7597 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 62: /* defs_head: "'def'" singleton dot_or_colon $@4 fname  */
#line 2339 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_sdef(p, (yyvsp[-3].nd), (yyvsp[0].id));
                      p->cmdarg_stack = 0;
                      p->in_def++;
                      p->in_single++;
                      nvars_block(p);
                      p->lstate = EXPR_ENDFN; /* force for args */
                    }
#line 7610 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 63: /* expr_value: expr  */
#line 2350 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      if (!(yyvsp[0].nd)) (yyval.nd) = new_nil(p);
                      else {
                        (yyval.nd) = (yyvsp[0].nd);
                      }
                    }
#line 7621 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 67: /* block_command: block_call call_op2 operation2 command_args  */
#line 2364 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_call(p, (yyvsp[-3].nd), (yyvsp[-1].id), (yyvsp[0].nd), (yyvsp[-2].num));
                    }
#line 7629 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 68: /* $@5: %empty  */
#line 2370 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      local_nest(p);
                      nvars_nest(p);
                    }
#line 7638 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 69: /* cmd_brace_block: "{" $@5 opt_block_param compstmt '}'  */
#line 2377 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_block(p, (yyvsp[-2].nd), (yyvsp[-1].nd));
                      local_unnest(p);
                      nvars_unnest(p);
                    }
#line 7648 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 70: /* command: operation command_args  */
#line 2385 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_fcall(p, (yyvsp[-1].id), (yyvsp[0].nd));
                    }
#line 7656 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 71: /* command: operation command_args cmd_brace_block  */
#line 2389 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      args_with_block(p, (yyvsp[-1].nd), (yyvsp[0].nd));
                      (yyval.nd) = new_fcall(p, (yyvsp[-2].id), (yyvsp[-1].nd));
                    }
#line 7665 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 72: /* command: primary_value call_op operation2 command_args  */
#line 2394 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_call(p, (yyvsp[-3].nd), (yyvsp[-1].id), (yyvsp[0].nd), (yyvsp[-2].num));
                    }
#line 7673 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 73: /* command: primary_value call_op operation2 command_args cmd_brace_block  */
#line 2398 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      args_with_block(p, (yyvsp[-1].nd), (yyvsp[0].nd));
                      (yyval.nd) = new_call(p, (yyvsp[-4].nd), (yyvsp[-2].id), (yyvsp[-1].nd), (yyvsp[-3].num));
                   }
#line 7682 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 74: /* command: primary_value "::" operation2 command_args  */
#line 2403 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_call(p, (yyvsp[-3].nd), (yyvsp[-1].id), (yyvsp[0].nd), tCOLON2);
                    }
#line 7690 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 75: /* command: primary_value "::" operation2 command_args cmd_brace_block  */
#line 2407 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      args_with_block(p, (yyvsp[-1].nd), (yyvsp[0].nd));
                      (yyval.nd) = new_call(p, (yyvsp[-4].nd), (yyvsp[-2].id), (yyvsp[-1].nd), tCOLON2);
                    }
#line 7699 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 76: /* command: "'super'" command_args  */
#line 2412 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_super(p, (yyvsp[0].nd));
                    }
#line 7707 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 77: /* command: "'yield'" command_args  */
#line 2416 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_yield(p, (yyvsp[0].nd));
                    }
#line 7715 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 78: /* command: "'return'" call_args  */
#line 2420 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_return(p, ret_args(p, (yyvsp[0].nd)));
                    }
#line 7723 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 79: /* command: "'break'" call_args  */
#line 2424 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_break(p, ret_args(p, (yyvsp[0].nd)));
                    }
#line 7731 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 80: /* command: "'next'" call_args  */
#line 2428 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_next(p, ret_args(p, (yyvsp[0].nd)));
                    }
#line 7739 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 81: /* mlhs: mlhs_basic  */
#line 2434 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[0].nd);
                    }
#line 7747 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 82: /* mlhs: tLPAREN mlhs_inner rparen  */
#line 2438 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[-1].nd);
                    }
#line 7755 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 84: /* mlhs_inner: tLPAREN mlhs_inner rparen  */
#line 2445 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[-1].nd);
                    }
#line 7763 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 85: /* mlhs_basic: mlhs_list  */
#line 2451 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list1((yyvsp[0].nd));
                    }
#line 7771 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 86: /* mlhs_basic: mlhs_list mlhs_item  */
#line 2455 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list1(push((yyvsp[-1].nd),(yyvsp[0].nd)));
                    }
#line 7779 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 87: /* mlhs_basic: mlhs_list "*" mlhs_node  */
#line 2459 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list2((yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 7787 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 88: /* mlhs_basic: mlhs_list "*" mlhs_node ',' mlhs_post  */
#line 2463 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list3((yyvsp[-4].nd), (yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 7795 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 89: /* mlhs_basic: mlhs_list "*"  */
#line 2467 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list2((yyvsp[-1].nd), new_nil(p));
                    }
#line 7803 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 90: /* mlhs_basic: mlhs_list "*" ',' mlhs_post  */
#line 2471 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list3((yyvsp[-3].nd), new_nil(p), (yyvsp[0].nd));
                    }
#line 7811 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 91: /* mlhs_basic: "*" mlhs_node  */
#line 2475 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list2(0, (yyvsp[0].nd));
                    }
#line 7819 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 92: /* mlhs_basic: "*" mlhs_node ',' mlhs_post  */
#line 2479 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list3(0, (yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 7827 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 93: /* mlhs_basic: "*"  */
#line 2483 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list2(0, new_nil(p));
                    }
#line 7835 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 94: /* mlhs_basic: "*" ',' mlhs_post  */
#line 2487 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list3(0, new_nil(p), (yyvsp[0].nd));
                    }
#line 7843 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 96: /* mlhs_item: tLPAREN mlhs_inner rparen  */
#line 2494 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_masgn(p, (yyvsp[-1].nd), NULL);
                    }
#line 7851 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 97: /* mlhs_list: mlhs_item ','  */
#line 2500 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list1((yyvsp[-1].nd));
                    }
#line 7859 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 98: /* mlhs_list: mlhs_list mlhs_item ','  */
#line 2504 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = push((yyvsp[-2].nd), (yyvsp[-1].nd));
                    }
#line 7867 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 99: /* mlhs_post: mlhs_item  */
#line 2510 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list1((yyvsp[0].nd));
                    }
#line 7875 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 100: /* mlhs_post: mlhs_list mlhs_item  */
#line 2514 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = push((yyvsp[-1].nd), (yyvsp[0].nd));
                    }
#line 7883 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 101: /* mlhs_node: variable  */
#line 2520 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      assignable(p, (yyvsp[0].nd));
                    }
#line 7891 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 102: /* mlhs_node: primary_value '[' opt_call_args ']'  */
#line 2524 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_call(p, (yyvsp[-3].nd), intern_op(aref), (yyvsp[-1].nd), '.');
                    }
#line 7899 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 103: /* mlhs_node: primary_value call_op "local variable or method"  */
#line 2528 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_call(p, (yyvsp[-2].nd), (yyvsp[0].id), 0, (yyvsp[-1].num));
                    }
#line 7907 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 104: /* mlhs_node: primary_value "::" "local variable or method"  */
#line 2532 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_call(p, (yyvsp[-2].nd), (yyvsp[0].id), 0, tCOLON2);
                    }
#line 7915 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 105: /* mlhs_node: primary_value call_op "constant"  */
#line 2536 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_call(p, (yyvsp[-2].nd), (yyvsp[0].id), 0, (yyvsp[-1].num));
                    }
#line 7923 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 106: /* mlhs_node: primary_value "::" "constant"  */
#line 2540 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      if (p->in_def || p->in_single)
                        yyerror(&(yylsp[-2]), p, "dynamic constant assignment");
                      (yyval.nd) = new_colon2(p, (yyvsp[-2].nd), (yyvsp[0].id));
                    }
#line 7933 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 107: /* mlhs_node: tCOLON3 "constant"  */
#line 2546 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      if (p->in_def || p->in_single)
                        yyerror(&(yylsp[-1]), p, "dynamic constant assignment");
                      (yyval.nd) = new_colon3(p, (yyvsp[0].id));
                    }
#line 7943 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 108: /* mlhs_node: backref  */
#line 2552 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      backref_error(p, (yyvsp[0].nd));
                      (yyval.nd) = 0;
                    }
#line 7952 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 109: /* lhs: variable  */
#line 2559 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      assignable(p, (yyvsp[0].nd));
                    }
#line 7960 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 110: /* lhs: primary_value '[' opt_call_args ']'  */
#line 2563 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_call(p, (yyvsp[-3].nd), intern_op(aref), (yyvsp[-1].nd), '.');
                    }
#line 7968 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 111: /* lhs: primary_value call_op "local variable or method"  */
#line 2567 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_call(p, (yyvsp[-2].nd), (yyvsp[0].id), 0, (yyvsp[-1].num));
                    }
#line 7976 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 112: /* lhs: primary_value "::" "local variable or method"  */
#line 2571 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_call(p, (yyvsp[-2].nd), (yyvsp[0].id), 0, tCOLON2);
                    }
#line 7984 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 113: /* lhs: primary_value call_op "constant"  */
#line 2575 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_call(p, (yyvsp[-2].nd), (yyvsp[0].id), 0, (yyvsp[-1].num));
                    }
#line 7992 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 114: /* lhs: primary_value "::" "constant"  */
#line 2579 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      if (p->in_def || p->in_single)
                        yyerror(&(yylsp[-2]), p, "dynamic constant assignment");
                      (yyval.nd) = new_colon2(p, (yyvsp[-2].nd), (yyvsp[0].id));
                    }
#line 8002 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 115: /* lhs: tCOLON3 "constant"  */
#line 2585 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      if (p->in_def || p->in_single)
                        yyerror(&(yylsp[-1]), p, "dynamic constant assignment");
                      (yyval.nd) = new_colon3(p, (yyvsp[0].id));
                    }
#line 8012 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 116: /* lhs: backref  */
#line 2591 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      backref_error(p, (yyvsp[0].nd));
                      (yyval.nd) = 0;
                    }
#line 8021 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 117: /* lhs: "numbered parameter"  */
#line 2596 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      yyerror(&(yylsp[0]), p, "can't assign to numbered parameter");
                    }
#line 8029 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 118: /* cname: "local variable or method"  */
#line 2602 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      yyerror(&(yylsp[0]), p, "class/module name must be CONSTANT");
                    }
#line 8037 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 120: /* cpath: tCOLON3 cname  */
#line 2609 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = cons(int_to_node(1), sym_to_node((yyvsp[0].id)));
                    }
#line 8045 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 121: /* cpath: cname  */
#line 2613 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = cons(int_to_node(0), sym_to_node((yyvsp[0].id)));
                    }
#line 8053 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 122: /* cpath: primary_value "::" cname  */
#line 2617 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      void_expr_error(p, (yyvsp[-2].nd));
                      (yyval.nd) = cons((yyvsp[-2].nd), sym_to_node((yyvsp[0].id)));
                    }
#line 8062 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 126: /* fname: op  */
#line 2627 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      p->lstate = EXPR_ENDFN;
                      (yyval.id) = (yyvsp[0].id);
                    }
#line 8071 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 127: /* fname: reswords  */
#line 2632 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      p->lstate = EXPR_ENDFN;
                      (yyval.id) = (yyvsp[0].id);
                    }
#line 8080 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 130: /* undef_list: fsym  */
#line 2643 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = cons(sym_to_node((yyvsp[0].id)), 0);
                    }
#line 8088 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 131: /* $@6: %empty  */
#line 2646 "mrbgems/mruby-compiler/core/parse.y"
                                 {p->lstate = EXPR_FNAME;}
#line 8094 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 132: /* undef_list: undef_list ',' $@6 fsym  */
#line 2647 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = push((yyvsp[-3].nd), sym_to_node((yyvsp[0].id)));
                    }
#line 8102 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 133: /* op: '|'  */
#line 2652 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(or);     }
#line 8108 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 134: /* op: '^'  */
#line 2653 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(xor);    }
#line 8114 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 135: /* op: '&'  */
#line 2654 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(and);    }
#line 8120 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 136: /* op: "<=>"  */
#line 2655 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(cmp);    }
#line 8126 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 137: /* op: "=="  */
#line 2656 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(eq);     }
#line 8132 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 138: /* op: "==="  */
#line 2657 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(eqq);    }
#line 8138 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 139: /* op: "=~"  */
#line 2658 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(match);  }
#line 8144 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 140: /* op: "!~"  */
#line 2659 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(nmatch); }
#line 8150 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 141: /* op: '>'  */
#line 2660 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(gt);     }
#line 8156 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 142: /* op: ">="  */
#line 2661 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(ge);     }
#line 8162 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 143: /* op: '<'  */
#line 2662 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(lt);     }
#line 8168 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 144: /* op: "<="  */
#line 2663 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(le);     }
#line 8174 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 145: /* op: "!="  */
#line 2664 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(neq);    }
#line 8180 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 146: /* op: "<<"  */
#line 2665 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(lshift); }
#line 8186 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 147: /* op: ">>"  */
#line 2666 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(rshift); }
#line 8192 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 148: /* op: '+'  */
#line 2667 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(add);    }
#line 8198 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 149: /* op: '-'  */
#line 2668 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(sub);    }
#line 8204 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 150: /* op: '*'  */
#line 2669 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(mul);    }
#line 8210 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 151: /* op: "*"  */
#line 2670 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(mul);    }
#line 8216 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 152: /* op: '/'  */
#line 2671 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(div);    }
#line 8222 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 153: /* op: '%'  */
#line 2672 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(mod);    }
#line 8228 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 154: /* op: tPOW  */
#line 2673 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(pow);    }
#line 8234 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 155: /* op: "**"  */
#line 2674 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(pow);    }
#line 8240 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 156: /* op: '!'  */
#line 2675 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(not);    }
#line 8246 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 157: /* op: '~'  */
#line 2676 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(neg);    }
#line 8252 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 158: /* op: "unary plus"  */
#line 2677 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(plus);   }
#line 8258 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 159: /* op: "unary minus"  */
#line 2678 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(minus);  }
#line 8264 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 160: /* op: tAREF  */
#line 2679 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(aref);   }
#line 8270 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 161: /* op: tASET  */
#line 2680 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(aset);   }
#line 8276 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 162: /* op: '`'  */
#line 2681 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(tick);   }
#line 8282 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 204: /* arg: lhs '=' arg_rhs  */
#line 2699 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_asgn(p, (yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 8290 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 205: /* arg: var_lhs tOP_ASGN arg_rhs  */
#line 2703 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_op_asgn(p, (yyvsp[-2].nd), (yyvsp[-1].id), (yyvsp[0].nd));
                    }
#line 8298 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 206: /* arg: primary_value '[' opt_call_args ']' tOP_ASGN arg_rhs  */
#line 2707 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_op_asgn(p, new_call(p, (yyvsp[-5].nd), intern_op(aref), (yyvsp[-3].nd), '.'), (yyvsp[-1].id), (yyvsp[0].nd));
                    }
#line 8306 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 207: /* arg: primary_value call_op "local variable or method" tOP_ASGN arg_rhs  */
#line 2711 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_op_asgn(p, new_call(p, (yyvsp[-4].nd), (yyvsp[-2].id), 0, (yyvsp[-3].num)), (yyvsp[-1].id), (yyvsp[0].nd));
                    }
#line 8314 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 208: /* arg: primary_value call_op "constant" tOP_ASGN arg_rhs  */
#line 2715 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_op_asgn(p, new_call(p, (yyvsp[-4].nd), (yyvsp[-2].id), 0, (yyvsp[-3].num)), (yyvsp[-1].id), (yyvsp[0].nd));
                    }
#line 8322 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 209: /* arg: primary_value "::" "local variable or method" tOP_ASGN arg_rhs  */
#line 2719 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_op_asgn(p, new_call(p, (yyvsp[-4].nd), (yyvsp[-2].id), 0, tCOLON2), (yyvsp[-1].id), (yyvsp[0].nd));
                    }
#line 8330 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 210: /* arg: primary_value "::" "constant" tOP_ASGN arg_rhs  */
#line 2723 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      yyerror(&(yylsp[-4]), p, "constant re-assignment");
                      (yyval.nd) = new_stmts(p, 0);
                    }
#line 8339 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 211: /* arg: tCOLON3 "constant" tOP_ASGN arg_rhs  */
#line 2728 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      yyerror(&(yylsp[-3]), p, "constant re-assignment");
                      (yyval.nd) = new_stmts(p, 0);
                    }
#line 8348 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 212: /* arg: backref tOP_ASGN arg_rhs  */
#line 2733 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      backref_error(p, (yyvsp[-2].nd));
                      (yyval.nd) = new_stmts(p, 0);
                    }
#line 8357 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 213: /* arg: arg ".." arg  */
#line 2738 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_dot2(p, (yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 8365 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 214: /* arg: arg ".."  */
#line 2742 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_dot2(p, (yyvsp[-1].nd), new_nil(p));
                    }
#line 8373 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 215: /* arg: tBDOT2 arg  */
#line 2746 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_dot2(p, new_nil(p), (yyvsp[0].nd));
                    }
#line 8381 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 216: /* arg: arg "..." arg  */
#line 2750 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_dot3(p, (yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 8389 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 217: /* arg: arg "..."  */
#line 2754 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_dot3(p, (yyvsp[-1].nd), new_nil(p));
                    }
#line 8397 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 218: /* arg: tBDOT3 arg  */
#line 2758 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_dot3(p, new_nil(p), (yyvsp[0].nd));
                    }
#line 8405 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 219: /* arg: arg '+' arg  */
#line 2762 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "+", (yyvsp[0].nd));
                    }
#line 8413 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 220: /* arg: arg '-' arg  */
#line 2766 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "-", (yyvsp[0].nd));
                    }
#line 8421 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 221: /* arg: arg '*' arg  */
#line 2770 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "*", (yyvsp[0].nd));
                    }
#line 8429 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 222: /* arg: arg '/' arg  */
#line 2774 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "/", (yyvsp[0].nd));
                    }
#line 8437 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 223: /* arg: arg '%' arg  */
#line 2778 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "%", (yyvsp[0].nd));
                    }
#line 8445 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 224: /* arg: arg tPOW arg  */
#line 2782 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "**", (yyvsp[0].nd));
                    }
#line 8453 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 225: /* arg: tUMINUS_NUM "integer literal" tPOW arg  */
#line 2786 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_negate(p, call_bin_op(p, (yyvsp[-2].nd), "**", (yyvsp[0].nd)));
                    }
#line 8461 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 226: /* arg: tUMINUS_NUM "float literal" tPOW arg  */
#line 2790 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_negate(p, call_bin_op(p, (yyvsp[-2].nd), "**", (yyvsp[0].nd)));
                    }
#line 8469 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 227: /* arg: "unary plus" arg  */
#line 2794 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_uni_op(p, (yyvsp[0].nd), "+@");
                    }
#line 8477 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 228: /* arg: "unary minus" arg  */
#line 2798 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_negate(p, (yyvsp[0].nd));
                    }
#line 8485 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 229: /* arg: arg '|' arg  */
#line 2802 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "|", (yyvsp[0].nd));
                    }
#line 8493 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 230: /* arg: arg '^' arg  */
#line 2806 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "^", (yyvsp[0].nd));
                    }
#line 8501 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 231: /* arg: arg '&' arg  */
#line 2810 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "&", (yyvsp[0].nd));
                    }
#line 8509 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 232: /* arg: arg "<=>" arg  */
#line 2814 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "<=>", (yyvsp[0].nd));
                    }
#line 8517 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 233: /* arg: arg '>' arg  */
#line 2818 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), ">", (yyvsp[0].nd));
                    }
#line 8525 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 234: /* arg: arg ">=" arg  */
#line 2822 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), ">=", (yyvsp[0].nd));
                    }
#line 8533 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 235: /* arg: arg '<' arg  */
#line 2826 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "<", (yyvsp[0].nd));
                    }
#line 8541 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 236: /* arg: arg "<=" arg  */
#line 2830 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "<=", (yyvsp[0].nd));
                    }
#line 8549 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 237: /* arg: arg "==" arg  */
#line 2834 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "==", (yyvsp[0].nd));
                    }
#line 8557 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 238: /* arg: arg "===" arg  */
#line 2838 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "===", (yyvsp[0].nd));
                    }
#line 8565 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 239: /* arg: arg "!=" arg  */
#line 2842 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "!=", (yyvsp[0].nd));
                    }
#line 8573 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 240: /* arg: arg "=~" arg  */
#line 2846 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "=~", (yyvsp[0].nd));
                    }
#line 8581 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 241: /* arg: arg "!~" arg  */
#line 2850 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "!~", (yyvsp[0].nd));
                    }
#line 8589 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 242: /* arg: '!' arg  */
#line 2854 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_uni_op(p, cond((yyvsp[0].nd)), "!");
                    }
#line 8597 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 243: /* arg: '~' arg  */
#line 2858 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_uni_op(p, cond((yyvsp[0].nd)), "~");
                    }
#line 8605 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 244: /* arg: arg "<<" arg  */
#line 2862 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "<<", (yyvsp[0].nd));
                    }
#line 8613 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 245: /* arg: arg ">>" arg  */
#line 2866 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), ">>", (yyvsp[0].nd));
                    }
#line 8621 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 246: /* arg: arg "&&" arg  */
#line 2870 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_and(p, (yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 8629 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 247: /* arg: arg "||" arg  */
#line 2874 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_or(p, (yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 8637 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 248: /* arg: arg '?' arg opt_nl ':' arg  */
#line 2878 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_if(p, cond((yyvsp[-5].nd)), (yyvsp[-3].nd), (yyvsp[0].nd));
                    }
#line 8645 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 249: /* arg: arg '?' arg opt_nl "label" arg  */
#line 2882 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_if(p, cond((yyvsp[-5].nd)), (yyvsp[-3].nd), (yyvsp[0].nd));
                    }
#line 8653 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 250: /* arg: defn_head f_opt_arglist_paren '=' arg  */
#line 2886 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[-3].nd);
                      endless_method_name(p, (yyvsp[-3].nd));
                      void_expr_error(p, (yyvsp[0].nd));
                      defn_setup(p, (yyval.nd), (yyvsp[-2].nd), (yyvsp[0].nd));
                      nvars_unnest(p);
                      p->in_def--;
                    }
#line 8666 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 251: /* arg: defn_head f_opt_arglist_paren '=' arg "'rescue' modifier" arg  */
#line 2895 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[-5].nd);
                      endless_method_name(p, (yyvsp[-5].nd));
                      void_expr_error(p, (yyvsp[-2].nd));
                      defn_setup(p, (yyval.nd), (yyvsp[-4].nd), new_mod_rescue(p, (yyvsp[-2].nd), (yyvsp[0].nd)));
                      nvars_unnest(p);
                      p->in_def--;
                    }
#line 8679 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 252: /* arg: defs_head f_opt_arglist_paren '=' arg  */
#line 2904 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[-3].nd);
                      void_expr_error(p, (yyvsp[0].nd));
                      defn_setup(p, (yyval.nd), (yyvsp[-2].nd), (yyvsp[0].nd));
                      nvars_unnest(p);
                      p->in_def--;
                      p->in_single--;
                    }
#line 8692 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 253: /* arg: defs_head f_opt_arglist_paren '=' arg "'rescue' modifier" arg  */
#line 2913 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[-5].nd);
                      void_expr_error(p, (yyvsp[-2].nd));
                      defn_setup(p, (yyval.nd), (yyvsp[-4].nd), new_mod_rescue(p, (yyvsp[-2].nd), (yyvsp[0].nd)));
                      nvars_unnest(p);
                      p->in_def--;
                      p->in_single--;
                    }
#line 8705 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 254: /* arg: primary  */
#line 2922 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[0].nd);
                    }
#line 8713 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 256: /* aref_args: args trailer  */
#line 2929 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[-1].nd);
                    }
#line 8721 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 257: /* aref_args: args comma assocs trailer  */
#line 2933 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = push((yyvsp[-3].nd), new_hash(p, (yyvsp[-1].nd)));
                    }
#line 8729 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 258: /* aref_args: assocs trailer  */
#line 2937 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = cons(new_hash(p, (yyvsp[-1].nd)), 0);
                    }
#line 8737 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 259: /* arg_rhs: arg  */
#line 2943 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[0].nd);
                    }
#line 8745 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 260: /* arg_rhs: arg "'rescue' modifier" arg  */
#line 2947 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      void_expr_error(p, (yyvsp[-2].nd));
                      (yyval.nd) = new_mod_rescue(p, (yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 8754 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 261: /* paren_args: '(' opt_call_args ')'  */
#line 2954 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[-1].nd);
                    }
#line 8762 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 262: /* paren_args: '(' args comma tBDOT3 rparen  */
#line 2958 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      mrb_sym r = intern_op(mul);
                      mrb_sym k = intern_op(pow);
                      mrb_sym b = intern_op(and);
                      (yyval.nd) = new_callargs(p, push((yyvsp[-3].nd), new_splat(p, new_lvar(p, r))),
                                        list1(cons(new_kw_rest_args(p, 0), new_lvar(p, k))),
                                        new_block_arg(p, new_lvar(p, b)));
                    }
#line 8775 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 263: /* paren_args: '(' tBDOT3 rparen  */
#line 2967 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      mrb_sym r = intern_op(mul);
                      mrb_sym k = intern_op(pow);
                      mrb_sym b = intern_op(and);
                      if (local_var_p(p, r) && local_var_p(p, k) && local_var_p(p, b)) {
                        (yyval.nd) = new_callargs(p, list1(new_splat(p, new_lvar(p, r))),
                                          list1(cons(new_kw_rest_args(p, 0), new_lvar(p, k))),
                                          new_block_arg(p, new_lvar(p, b)));
                      }
                      else {
                        yyerror(&(yylsp[-2]), p, "unexpected argument forwarding ...");
                        (yyval.nd) = 0;
                      }
                    }
#line 8794 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 268: /* opt_call_args: args comma  */
#line 2990 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_callargs(p,(yyvsp[-1].nd),0,0);
                    }
#line 8802 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 269: /* opt_call_args: args comma assocs comma  */
#line 2994 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_callargs(p,(yyvsp[-3].nd),(yyvsp[-1].nd),0);
                    }
#line 8810 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 270: /* opt_call_args: assocs comma  */
#line 2998 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_callargs(p,0,(yyvsp[-1].nd),0);
                    }
#line 8818 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 271: /* call_args: command  */
#line 3004 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      void_expr_error(p, (yyvsp[0].nd));
                      (yyval.nd) = new_callargs(p, list1((yyvsp[0].nd)), 0, 0);
                    }
#line 8827 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 272: /* call_args: args opt_block_arg  */
#line 3009 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_callargs(p, (yyvsp[-1].nd), 0, (yyvsp[0].nd));
                    }
#line 8835 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 273: /* call_args: assocs opt_block_arg  */
#line 3013 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_callargs(p, 0, (yyvsp[-1].nd), (yyvsp[0].nd));
                    }
#line 8843 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 274: /* call_args: args comma assocs opt_block_arg  */
#line 3017 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_callargs(p, (yyvsp[-3].nd), (yyvsp[-1].nd), (yyvsp[0].nd));
                    }
#line 8851 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 275: /* call_args: block_arg  */
#line 3021 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_callargs(p, 0, 0, (yyvsp[0].nd));
                    }
#line 8859 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 276: /* @7: %empty  */
#line 3026 "mrbgems/mruby-compiler/core/parse.y"
                   {
                      (yyval.stack) = p->cmdarg_stack;
                      CMDARG_PUSH(1);
                    }
#line 8868 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 277: /* command_args: @7 call_args  */
#line 3031 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      p->cmdarg_stack = (yyvsp[-1].stack);
                      (yyval.nd) = (yyvsp[0].nd);
                    }
#line 8877 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 278: /* block_arg: "&" arg  */
#line 3038 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_block_arg(p, (yyvsp[0].nd));
                    }
#line 8885 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 279: /* block_arg: "&"  */
#line 3042 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_block_arg(p, 0);
                    }
#line 8893 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 280: /* opt_block_arg: comma block_arg  */
#line 3048 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[0].nd);
                    }
#line 8901 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 281: /* opt_block_arg: none  */
#line 3052 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = 0;
                    }
#line 8909 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 283: /* args: arg  */
#line 3061 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      void_expr_error(p, (yyvsp[0].nd));
                      (yyval.nd) = list1((yyvsp[0].nd));
                    }
#line 8918 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 284: /* args: "*"  */
#line 3066 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list1(new_splat(p, new_lvar(p, intern_op(mul))));
                    }
#line 8926 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 285: /* args: "*" arg  */
#line 3070 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list1(new_splat(p, (yyvsp[0].nd)));
                    }
#line 8934 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 286: /* args: args comma arg  */
#line 3074 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      void_expr_error(p, (yyvsp[0].nd));
                      (yyval.nd) = push((yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 8943 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 287: /* args: args comma "*"  */
#line 3079 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = push((yyvsp[-2].nd), new_splat(p, new_lvar(p, intern_op(mul))));
                    }
#line 8951 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 288: /* args: args comma "*" arg  */
#line 3083 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = push((yyvsp[-3].nd), new_splat(p, (yyvsp[0].nd)));
                    }
#line 8959 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 289: /* mrhs: args comma arg  */
#line 3089 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      void_expr_error(p, (yyvsp[0].nd));
                      (yyval.nd) = push((yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 8968 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 290: /* mrhs: args comma "*" arg  */
#line 3094 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = push((yyvsp[-3].nd), new_splat(p, (yyvsp[0].nd)));
                    }
#line 8976 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 291: /* mrhs: "*" arg  */
#line 3098 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list1(new_splat(p, (yyvsp[0].nd)));
                    }
#line 8984 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 293: /* primary: string  */
#line 3105 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_str(p, (yyvsp[0].nd));
                    }
#line 8992 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 294: /* primary: xstring  */
#line 3109 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_xstr(p, (yyvsp[0].nd));
                    }
#line 9000 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 299: /* primary: "method"  */
#line 3117 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_fcall(p, (yyvsp[0].id), 0);
                    }
#line 9008 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 300: /* @8: %empty  */
#line 3121 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.stack) = p->cmdarg_stack;
                      p->cmdarg_stack = 0;
                    }
#line 9017 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 301: /* primary: "'begin'" @8 bodystmt "'end'"  */
#line 3127 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      p->cmdarg_stack = (yyvsp[-2].stack);
                      (yyval.nd) = new_begin(p, (yyvsp[-1].nd));
                    }
#line 9026 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 302: /* @9: %empty  */
#line 3132 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.stack) = p->cmdarg_stack;
                      p->cmdarg_stack = 0;
                    }
#line 9035 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 303: /* $@10: %empty  */
#line 3136 "mrbgems/mruby-compiler/core/parse.y"
                       {p->lstate = EXPR_ENDARG;}
#line 9041 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 304: /* primary: "(" @9 stmt $@10 rparen  */
#line 3137 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      p->cmdarg_stack = (yyvsp[-3].stack);
                      (yyval.nd) = (yyvsp[-2].nd);
                    }
#line 9050 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 305: /* $@11: %empty  */
#line 3141 "mrbgems/mruby-compiler/core/parse.y"
                              {p->lstate = EXPR_ENDARG;}
#line 9056 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 306: /* primary: "(" $@11 rparen  */
#line 3142 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_nil(p);
                    }
#line 9064 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 307: /* primary: tLPAREN compstmt ')'  */
#line 3146 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[-1].nd);
                    }
#line 9072 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 308: /* primary: primary_value "::" "constant"  */
#line 3150 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_colon2(p, (yyvsp[-2].nd), (yyvsp[0].id));
                    }
#line 9080 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 309: /* primary: tCOLON3 "constant"  */
#line 3154 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_colon3(p, (yyvsp[0].id));
                    }
#line 9088 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 310: /* primary: "[" aref_args ']'  */
#line 3158 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_array(p, (yyvsp[-1].nd));
                    }
#line 9096 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 311: /* primary: tLBRACE assoc_list '}'  */
#line 3162 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_hash(p, (yyvsp[-1].nd));
                    }
#line 9104 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 312: /* primary: "'return'"  */
#line 3166 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_return(p, 0);
                    }
#line 9112 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 313: /* primary: "'yield'" opt_paren_args  */
#line 3170 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_yield(p, (yyvsp[0].nd));
                    }
#line 9120 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 314: /* primary: "'not'" '(' expr rparen  */
#line 3174 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_uni_op(p, cond((yyvsp[-1].nd)), "!");
                    }
#line 9128 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 315: /* primary: "'not'" '(' rparen  */
#line 3178 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_uni_op(p, new_nil(p), "!");
                    }
#line 9136 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 316: /* primary: operation brace_block  */
#line 3182 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_fcall(p, (yyvsp[-1].id), new_callargs(p, 0, 0, (yyvsp[0].nd)));
                    }
#line 9144 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 318: /* primary: method_call brace_block  */
#line 3187 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      call_with_block(p, (yyvsp[-1].nd), (yyvsp[0].nd));
                      (yyval.nd) = (yyvsp[-1].nd);
                    }
#line 9153 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 319: /* @12: %empty  */
#line 3192 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      local_nest(p);
                      nvars_nest(p);
                      (yyval.num) = p->lpar_beg;
                      p->lpar_beg = ++p->paren_nest;
                    }
#line 9164 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 320: /* @13: %empty  */
#line 3199 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.stack) = p->cmdarg_stack;
                      p->cmdarg_stack = 0;
                    }
#line 9173 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 321: /* primary: "->" @12 f_larglist @13 lambda_body  */
#line 3204 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      p->lpar_beg = (yyvsp[-3].num);
                      (yyval.nd) = new_lambda(p, (yyvsp[-2].nd), (yyvsp[0].nd));
                      local_unnest(p);
                      nvars_unnest(p);
                      p->cmdarg_stack = (yyvsp[-1].stack);
                      CMDARG_LEXPOP();
                    }
#line 9186 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 322: /* primary: "'if'" expr_value then compstmt if_tail "'end'"  */
#line 3216 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_if(p, cond((yyvsp[-4].nd)), (yyvsp[-2].nd), (yyvsp[-1].nd));
                      SET_LINENO((yyval.nd), (yyvsp[-5].num));
                    }
#line 9195 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 323: /* primary: "'unless'" expr_value then compstmt opt_else "'end'"  */
#line 3224 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_if(p, cond((yyvsp[-4].nd)), (yyvsp[-1].nd), (yyvsp[-2].nd));
                      SET_LINENO((yyval.nd), (yyvsp[-5].num));
                    }
#line 9204 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 324: /* $@14: %empty  */
#line 3228 "mrbgems/mruby-compiler/core/parse.y"
                                {COND_PUSH(1);}
#line 9210 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 325: /* $@15: %empty  */
#line 3228 "mrbgems/mruby-compiler/core/parse.y"
                                                              {COND_POP();}
#line 9216 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 326: /* primary: "'while'" $@14 expr_value do $@15 compstmt "'end'"  */
#line 3231 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_while(p, cond((yyvsp[-4].nd)), (yyvsp[-1].nd));
                      SET_LINENO((yyval.nd), (yyvsp[-6].num));
                    }
#line 9225 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 327: /* $@16: %empty  */
#line 3235 "mrbgems/mruby-compiler/core/parse.y"
                                {COND_PUSH(1);}
#line 9231 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 328: /* $@17: %empty  */
#line 3235 "mrbgems/mruby-compiler/core/parse.y"
                                                              {COND_POP();}
#line 9237 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 329: /* primary: "'until'" $@16 expr_value do $@17 compstmt "'end'"  */
#line 3238 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_until(p, cond((yyvsp[-4].nd)), (yyvsp[-1].nd));
                      SET_LINENO((yyval.nd), (yyvsp[-6].num));
                    }
#line 9246 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 330: /* primary: "'case'" expr_value opt_terms case_body "'end'"  */
#line 3245 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_case(p, (yyvsp[-3].nd), (yyvsp[-1].nd));
                    }
#line 9254 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 331: /* primary: "'case'" opt_terms case_body "'end'"  */
#line 3249 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_case(p, 0, (yyvsp[-1].nd));
                    }
#line 9262 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 332: /* $@18: %empty  */
#line 3253 "mrbgems/mruby-compiler/core/parse.y"
                  {COND_PUSH(1);}
#line 9268 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 333: /* $@19: %empty  */
#line 3255 "mrbgems/mruby-compiler/core/parse.y"
                  {COND_POP();}
#line 9274 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 334: /* primary: "'for'" for_var "'in'" $@18 expr_value do $@19 compstmt "'end'"  */
#line 3258 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_for(p, (yyvsp[-7].nd), (yyvsp[-4].nd), (yyvsp[-1].nd));
                      SET_LINENO((yyval.nd), (yyvsp[-8].num));
                    }
#line 9283 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 335: /* @20: %empty  */
#line 3264 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      if (p->in_def || p->in_single)
                        yyerror(&(yylsp[-2]), p, "class definition in method body");
                      (yyval.nd) = local_switch(p);
                      nvars_block(p);
                    }
#line 9294 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 336: /* primary: "'class'" cpath superclass @20 bodystmt "'end'"  */
#line 3272 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_class(p, (yyvsp[-4].nd), (yyvsp[-3].nd), (yyvsp[-1].nd));
                      SET_LINENO((yyval.nd), (yyvsp[-5].num));
                      local_resume(p, (yyvsp[-2].nd));
                      nvars_unnest(p);
                    }
#line 9305 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 337: /* @21: %empty  */
#line 3280 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.num) = p->in_def;
                      p->in_def = 0;
                    }
#line 9314 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 338: /* @22: %empty  */
#line 3285 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = cons(local_switch(p), int_to_node(p->in_single));
                      nvars_block(p);
                      p->in_single = 0;
                    }
#line 9324 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 339: /* primary: "'class'" "<<" expr @21 term @22 bodystmt "'end'"  */
#line 3292 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_sclass(p, (yyvsp[-5].nd), (yyvsp[-1].nd));
                      SET_LINENO((yyval.nd), (yyvsp[-7].num));
                      local_resume(p, (yyvsp[-2].nd)->car);
                      nvars_unnest(p);
                      p->in_def = (yyvsp[-4].num);
                      p->in_single = node_to_int((yyvsp[-2].nd)->cdr);
                    }
#line 9337 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 340: /* @23: %empty  */
#line 3302 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      if (p->in_def || p->in_single)
                        yyerror(&(yylsp[-1]), p, "module definition in method body");
                      (yyval.nd) = local_switch(p);
                      nvars_block(p);
                    }
#line 9348 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 341: /* primary: "'module'" cpath @23 bodystmt "'end'"  */
#line 3310 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_module(p, (yyvsp[-3].nd), (yyvsp[-1].nd));
                      SET_LINENO((yyval.nd), (yyvsp[-4].num));
                      local_resume(p, (yyvsp[-2].nd));
                      nvars_unnest(p);
                    }
#line 9359 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 342: /* primary: defn_head f_arglist bodystmt "'end'"  */
#line 3320 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[-3].nd);
                      defn_setup(p, (yyval.nd), (yyvsp[-2].nd), (yyvsp[-1].nd));
                      nvars_unnest(p);
                      p->in_def--;
                    }
#line 9370 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 343: /* primary: defs_head f_arglist bodystmt "'end'"  */
#line 3330 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[-3].nd);
                      defn_setup(p, (yyval.nd), (yyvsp[-2].nd), (yyvsp[-1].nd));
                      nvars_unnest(p);
                      p->in_def--;
                      p->in_single--;
                    }
#line 9382 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 344: /* primary: "'break'"  */
#line 3338 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_break(p, 0);
                    }
#line 9390 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 345: /* primary: "'next'"  */
#line 3342 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_next(p, 0);
                    }
#line 9398 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 346: /* primary: "'redo'"  */
#line 3346 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_redo(p);
                    }
#line 9406 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 347: /* primary: "'retry'"  */
#line 3350 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_retry(p);
                    }
#line 9414 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 348: /* primary_value: primary  */
#line 3356 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[0].nd);
                      if (!(yyval.nd)) (yyval.nd) = new_nil(p);
                    }
#line 9423 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 355: /* if_tail: "'elsif'" expr_value then compstmt if_tail  */
#line 3375 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_if(p, cond((yyvsp[-3].nd)), (yyvsp[-1].nd), (yyvsp[0].nd));
                    }
#line 9431 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 357: /* opt_else: "'else'" compstmt  */
#line 3382 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[0].nd);
                    }
#line 9439 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 358: /* for_var: lhs  */
#line 3388 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list1(list1((yyvsp[0].nd)));
                    }
#line 9447 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 360: /* f_margs: f_arg  */
#line 3395 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list3((yyvsp[0].nd),0,0);
                    }
#line 9455 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 361: /* f_margs: f_arg ',' "*" f_norm_arg  */
#line 3399 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list3((yyvsp[-3].nd), new_lvar(p, (yyvsp[0].id)), 0);
                    }
#line 9463 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 362: /* f_margs: f_arg ',' "*" f_norm_arg ',' f_arg  */
#line 3403 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list3((yyvsp[-5].nd), new_lvar(p, (yyvsp[-2].id)), (yyvsp[0].nd));
                    }
#line 9471 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 363: /* f_margs: f_arg ',' "*"  */
#line 3407 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      local_add_f(p, intern_op(mul));
                      (yyval.nd) = list3((yyvsp[-2].nd), int_to_node(-1), 0);
                    }
#line 9480 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 364: /* f_margs: f_arg ',' "*" ',' f_arg  */
#line 3412 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list3((yyvsp[-4].nd), int_to_node(-1), (yyvsp[0].nd));
                    }
#line 9488 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 365: /* f_margs: "*" f_norm_arg  */
#line 3416 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list3(0, new_lvar(p, (yyvsp[0].id)), 0);
                    }
#line 9496 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 366: /* f_margs: "*" f_norm_arg ',' f_arg  */
#line 3420 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list3(0, new_lvar(p, (yyvsp[-2].id)), (yyvsp[0].nd));
                    }
#line 9504 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 367: /* f_margs: "*"  */
#line 3424 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      local_add_f(p, intern_op(mul));
                      (yyval.nd) = list3(0, int_to_node(-1), 0);
                    }
#line 9513 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 368: /* $@24: %empty  */
#line 3429 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      local_add_f(p, intern_op(mul));
                    }
#line 9521 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 369: /* f_margs: "*" ',' $@24 f_arg  */
#line 3433 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list3(0, int_to_node(-1), (yyvsp[0].nd));
                    }
#line 9529 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 370: /* block_args_tail: f_block_kwarg ',' f_kwrest opt_f_block_arg  */
#line 3439 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args_tail(p, (yyvsp[-3].nd), (yyvsp[-1].id), (yyvsp[0].id));
                    }
#line 9537 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 371: /* block_args_tail: f_block_kwarg opt_f_block_arg  */
#line 3443 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args_tail(p, (yyvsp[-1].nd), 0, (yyvsp[0].id));
                    }
#line 9545 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 372: /* block_args_tail: f_kwrest opt_f_block_arg  */
#line 3447 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args_tail(p, 0, (yyvsp[-1].id), (yyvsp[0].id));
                    }
#line 9553 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 373: /* block_args_tail: f_block_arg  */
#line 3451 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args_tail(p, 0, 0, (yyvsp[0].id));
                    }
#line 9561 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 374: /* opt_block_args_tail: ',' block_args_tail  */
#line 3457 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[0].nd);
                    }
#line 9569 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 375: /* opt_block_args_tail: %empty  */
#line 3461 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args_tail(p, 0, 0, 0);
                    }
#line 9577 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 376: /* block_param: f_arg ',' f_block_optarg ',' f_rest_arg opt_block_args_tail  */
#line 3467 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, (yyvsp[-5].nd), (yyvsp[-3].nd), (yyvsp[-1].id), 0, (yyvsp[0].nd));
                    }
#line 9585 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 377: /* block_param: f_arg ',' f_block_optarg ',' f_rest_arg ',' f_arg opt_block_args_tail  */
#line 3471 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, (yyvsp[-7].nd), (yyvsp[-5].nd), (yyvsp[-3].id), (yyvsp[-1].nd), (yyvsp[0].nd));
                    }
#line 9593 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 378: /* block_param: f_arg ',' f_block_optarg opt_block_args_tail  */
#line 3475 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, (yyvsp[-3].nd), (yyvsp[-1].nd), 0, 0, (yyvsp[0].nd));
                    }
#line 9601 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 379: /* block_param: f_arg ',' f_block_optarg ',' f_arg opt_block_args_tail  */
#line 3479 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, (yyvsp[-5].nd), (yyvsp[-3].nd), 0, (yyvsp[-1].nd), (yyvsp[0].nd));
                    }
#line 9609 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 380: /* block_param: f_arg ',' f_rest_arg opt_block_args_tail  */
#line 3483 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, (yyvsp[-3].nd), 0, (yyvsp[-1].id), 0, (yyvsp[0].nd));
                    }
#line 9617 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 381: /* block_param: f_arg ',' opt_block_args_tail  */
#line 3487 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, (yyvsp[-2].nd), 0, 0, 0, (yyvsp[0].nd));
                    }
#line 9625 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 382: /* block_param: f_arg ',' f_rest_arg ',' f_arg opt_block_args_tail  */
#line 3491 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, (yyvsp[-5].nd), 0, (yyvsp[-3].id), (yyvsp[-1].nd), (yyvsp[0].nd));
                    }
#line 9633 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 383: /* block_param: f_arg opt_block_args_tail  */
#line 3495 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, (yyvsp[-1].nd), 0, 0, 0, (yyvsp[0].nd));
                    }
#line 9641 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 384: /* block_param: f_block_optarg ',' f_rest_arg opt_block_args_tail  */
#line 3499 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, 0, (yyvsp[-3].nd), (yyvsp[-1].id), 0, (yyvsp[0].nd));
                    }
#line 9649 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 385: /* block_param: f_block_optarg ',' f_rest_arg ',' f_arg opt_block_args_tail  */
#line 3503 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, 0, (yyvsp[-5].nd), (yyvsp[-3].id), (yyvsp[-1].nd), (yyvsp[0].nd));
                    }
#line 9657 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 386: /* block_param: f_block_optarg opt_block_args_tail  */
#line 3507 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, 0, (yyvsp[-1].nd), 0, 0, (yyvsp[0].nd));
                    }
#line 9665 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 387: /* block_param: f_block_optarg ',' f_arg opt_block_args_tail  */
#line 3511 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, 0, (yyvsp[-3].nd), 0, (yyvsp[-1].nd), (yyvsp[0].nd));
                    }
#line 9673 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 388: /* block_param: f_rest_arg opt_block_args_tail  */
#line 3515 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, 0, 0, (yyvsp[-1].id), 0, (yyvsp[0].nd));
                    }
#line 9681 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 389: /* block_param: f_rest_arg ',' f_arg opt_block_args_tail  */
#line 3519 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, 0, 0, (yyvsp[-3].id), (yyvsp[-1].nd), (yyvsp[0].nd));
                    }
#line 9689 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 390: /* block_param: block_args_tail  */
#line 3523 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, 0, 0, 0, 0, (yyvsp[0].nd));
                    }
#line 9697 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 391: /* opt_block_param: none  */
#line 3529 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      local_add_blk(p);
                      (yyval.nd) = 0;
                    }
#line 9706 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 392: /* opt_block_param: block_param_def  */
#line 3534 "mrbgems/mruby-compiler/core/parse.y"
                   {
                      p->cmd_start = TRUE;
                      (yyval.nd) = (yyvsp[0].nd);
                    }
#line 9715 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 393: /* $@25: %empty  */
#line 3540 "mrbgems/mruby-compiler/core/parse.y"
                      {local_add_blk(p);}
#line 9721 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 394: /* block_param_def: '|' $@25 opt_bv_decl '|'  */
#line 3541 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = 0;
                    }
#line 9729 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 395: /* block_param_def: "||"  */
#line 3545 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      local_add_blk(p);
                      (yyval.nd) = 0;
                    }
#line 9738 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 396: /* block_param_def: '|' block_param opt_bv_decl '|'  */
#line 3550 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[-2].nd);
                    }
#line 9746 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 397: /* opt_bv_decl: opt_nl  */
#line 3556 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = 0;
                    }
#line 9754 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 398: /* opt_bv_decl: opt_nl ';' bv_decls opt_nl  */
#line 3560 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = 0;
                    }
#line 9762 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 401: /* bvar: "local variable or method"  */
#line 3570 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      local_add_f(p, (yyvsp[0].id));
                      new_bv(p, (yyvsp[0].id));
                    }
#line 9771 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 403: /* f_larglist: '(' f_args opt_bv_decl ')'  */
#line 3578 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[-2].nd);
                    }
#line 9779 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 404: /* f_larglist: f_args  */
#line 3582 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[0].nd);
                    }
#line 9787 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 405: /* lambda_body: tLAMBEG compstmt '}'  */
#line 3588 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[-1].nd);
                    }
#line 9795 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 406: /* lambda_body: "'do' for lambda" bodystmt "'end'"  */
#line 3592 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[-1].nd);
                    }
#line 9803 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 407: /* @26: %empty  */
#line 3598 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      local_nest(p);
                      nvars_nest(p);
                      (yyval.num) = p->lineno;
                    }
#line 9813 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 408: /* do_block: "'do' for block" @26 opt_block_param bodystmt "'end'"  */
#line 3606 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_block(p,(yyvsp[-2].nd),(yyvsp[-1].nd));
                      SET_LINENO((yyval.nd), (yyvsp[-3].num));
                      local_unnest(p);
                      nvars_unnest(p);
                    }
#line 9824 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 409: /* block_call: command do_block  */
#line 3615 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      call_with_block(p, (yyvsp[-1].nd), (yyvsp[0].nd));
                      (yyval.nd) = (yyvsp[-1].nd);
                    }
#line 9833 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 410: /* block_call: block_call call_op2 operation2 opt_paren_args  */
#line 3620 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_call(p, (yyvsp[-3].nd), (yyvsp[-1].id), (yyvsp[0].nd), (yyvsp[-2].num));
                    }
#line 9841 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 411: /* block_call: block_call call_op2 operation2 opt_paren_args brace_block  */
#line 3624 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_call(p, (yyvsp[-4].nd), (yyvsp[-2].id), (yyvsp[-1].nd), (yyvsp[-3].num));
                      call_with_block(p, (yyval.nd), (yyvsp[0].nd));
                    }
#line 9850 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 412: /* block_call: block_call call_op2 operation2 command_args do_block  */
#line 3629 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_call(p, (yyvsp[-4].nd), (yyvsp[-2].id), (yyvsp[-1].nd), (yyvsp[-3].num));
                      call_with_block(p, (yyval.nd), (yyvsp[0].nd));
                    }
#line 9859 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 413: /* method_call: operation paren_args  */
#line 3636 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_fcall(p, (yyvsp[-1].id), (yyvsp[0].nd));
                    }
#line 9867 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 414: /* method_call: primary_value call_op operation2 opt_paren_args  */
#line 3640 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_call(p, (yyvsp[-3].nd), (yyvsp[-1].id), (yyvsp[0].nd), (yyvsp[-2].num));
                    }
#line 9875 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 415: /* method_call: primary_value "::" operation2 paren_args  */
#line 3644 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_call(p, (yyvsp[-3].nd), (yyvsp[-1].id), (yyvsp[0].nd), tCOLON2);
                    }
#line 9883 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 416: /* method_call: primary_value "::" operation3  */
#line 3648 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_call(p, (yyvsp[-2].nd), (yyvsp[0].id), 0, tCOLON2);
                    }
#line 9891 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 417: /* method_call: primary_value call_op paren_args  */
#line 3652 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_call(p, (yyvsp[-2].nd), MRB_SYM_2(p->mrb, call), (yyvsp[0].nd), (yyvsp[-1].num));
                    }
#line 9899 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 418: /* method_call: primary_value "::" paren_args  */
#line 3656 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_call(p, (yyvsp[-2].nd), MRB_SYM_2(p->mrb, call), (yyvsp[0].nd), tCOLON2);
                    }
#line 9907 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 419: /* method_call: "'super'" paren_args  */
#line 3660 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_super(p, (yyvsp[0].nd));
                    }
#line 9915 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 420: /* method_call: "'super'"  */
#line 3664 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_zsuper(p);
                    }
#line 9923 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 421: /* method_call: primary_value '[' opt_call_args ']'  */
#line 3668 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_call(p, (yyvsp[-3].nd), intern_op(aref), (yyvsp[-1].nd), '.');
                    }
#line 9931 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 422: /* @27: %empty  */
#line 3674 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      local_nest(p);
                      nvars_nest(p);
                      (yyval.num) = p->lineno;
                    }
#line 9941 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 423: /* brace_block: '{' @27 opt_block_param compstmt '}'  */
#line 3681 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_block(p,(yyvsp[-2].nd),(yyvsp[-1].nd));
                      SET_LINENO((yyval.nd), (yyvsp[-3].num));
                      local_unnest(p);
                      nvars_unnest(p);
                    }
#line 9952 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 424: /* @28: %empty  */
#line 3688 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      local_nest(p);
                      nvars_nest(p);
                      (yyval.num) = p->lineno;
                    }
#line 9962 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 425: /* brace_block: "'do'" @28 opt_block_param bodystmt "'end'"  */
#line 3695 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_block(p,(yyvsp[-2].nd),(yyvsp[-1].nd));
                      SET_LINENO((yyval.nd), (yyvsp[-3].num));
                      local_unnest(p);
                      nvars_unnest(p);
                    }
#line 9973 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 426: /* case_body: "'when'" args then compstmt cases  */
#line 3706 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = cons(cons((yyvsp[-3].nd), (yyvsp[-1].nd)), (yyvsp[0].nd));
                    }
#line 9981 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 427: /* cases: opt_else  */
#line 3712 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      if ((yyvsp[0].nd)) {
                        (yyval.nd) = cons(cons(0, (yyvsp[0].nd)), 0);
                      }
                      else {
                        (yyval.nd) = 0;
                      }
                    }
#line 9994 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 429: /* opt_rescue: "'rescue'" exc_list exc_var then compstmt opt_rescue  */
#line 3726 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list1(list3((yyvsp[-4].nd), (yyvsp[-3].nd), (yyvsp[-1].nd)));
                      if ((yyvsp[0].nd)) (yyval.nd) = append((yyval.nd), (yyvsp[0].nd));
                    }
#line 10003 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 431: /* exc_list: arg  */
#line 3734 "mrbgems/mruby-compiler/core/parse.y"
                    {
                        (yyval.nd) = list1((yyvsp[0].nd));
                    }
#line 10011 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 434: /* exc_var: "=>" lhs  */
#line 3742 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[0].nd);
                    }
#line 10019 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 436: /* opt_ensure: "'ensure'" compstmt  */
#line 3749 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[0].nd);
                    }
#line 10027 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 443: /* string: string string_fragment  */
#line 3763 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = append((yyvsp[-1].nd), (yyvsp[0].nd));
                    }
#line 10035 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 444: /* string_fragment: "character literal"  */
#line 3769 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      /* tCHAR is (len . str), wrap as cons list */
                      (yyval.nd) = list1((yyvsp[0].nd));
                    }
#line 10044 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 445: /* string_fragment: tSTRING  */
#line 3774 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      /* tSTRING is (len . str), wrap as cons list */
                      (yyval.nd) = list1((yyvsp[0].nd));
                    }
#line 10053 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 446: /* string_fragment: "string literal" tSTRING  */
#line 3779 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      /* $2 is (len . str), wrap as cons list */
                      (yyval.nd) = list1((yyvsp[0].nd));
                    }
#line 10062 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 447: /* string_fragment: "string literal" string_rep tSTRING  */
#line 3784 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = push((yyvsp[-1].nd), (yyvsp[0].nd));
                    }
#line 10070 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 449: /* string_rep: string_rep string_interp  */
#line 3791 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = append((yyvsp[-1].nd), (yyvsp[0].nd));
                    }
#line 10078 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 450: /* string_interp: tSTRING_MID  */
#line 3797 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      /* $1 is already in (len . str) format */
                      (yyval.nd) = list1((yyvsp[0].nd));
                    }
#line 10087 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 451: /* @29: %empty  */
#line 3802 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = push_strterm(p);
                    }
#line 10095 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 452: /* string_interp: tSTRING_PART @29 compstmt '}'  */
#line 3807 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      pop_strterm(p,(yyvsp[-2].nd));
                      /* $1 is already in (len . str) format, create (-1 . node) for expression */
                      node *expr_elem = cons(int_to_node(-1), (yyvsp[-1].nd));
                      (yyval.nd) = list2((yyvsp[-3].nd), expr_elem);
                    }
#line 10106 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 453: /* string_interp: tLITERAL_DELIM  */
#line 3814 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list1(new_literal_delim(p));
                    }
#line 10114 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 454: /* string_interp: tHD_LITERAL_DELIM heredoc_bodies  */
#line 3818 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list1(new_literal_delim(p));
                    }
#line 10122 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 455: /* xstring: tXSTRING_BEG tXSTRING  */
#line 3824 "mrbgems/mruby-compiler/core/parse.y"
                    {
                        (yyval.nd) = cons((yyvsp[0].nd), (node*)NULL);
                    }
#line 10130 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 456: /* xstring: tXSTRING_BEG string_rep tXSTRING  */
#line 3828 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = push((yyvsp[-1].nd), (yyvsp[0].nd));
                    }
#line 10138 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 457: /* regexp: tREGEXP_BEG tREGEXP  */
#line 3834 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      node *data = (yyvsp[0].nd);  /* ((len . pattern) . (flags . encoding)) */
                      const char *flags = (const char*)data->cdr->car;
                      const char *encoding = (const char*)data->cdr->cdr;
                      /* Use data->car directly as pattern_list: (len . pattern) */
                      node *pattern_list = cons(data->car, (node*)NULL);
                      (yyval.nd) = new_regx(p, pattern_list, flags, encoding);
                    }
#line 10151 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 458: /* regexp: tREGEXP_BEG string_rep tREGEXP  */
#line 3843 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      node *data = (yyvsp[0].nd);  /* ((len . pattern) . (flags . encoding)) */
                      const char *flags = (const char*)data->cdr->car;
                      const char *encoding = (const char*)data->cdr->cdr;
                      /* Append the pattern from $3->car to the string list $2 */
                      node *complete_list = push((yyvsp[-1].nd), data->car);
                      (yyval.nd) = new_regx(p, complete_list, flags, encoding);
                    }
#line 10164 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 462: /* heredoc_body: tHEREDOC_END  */
#line 3861 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      parser_heredoc_info *info = parsing_heredoc_info(p);
                      info->doc = push(info->doc, new_str_empty(p));
                      heredoc_end(p);
                    }
#line 10174 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 463: /* heredoc_body: heredoc_string_rep tHEREDOC_END  */
#line 3867 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      heredoc_end(p);
                    }
#line 10182 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 466: /* heredoc_string_interp: tHD_STRING_MID  */
#line 3877 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      parser_heredoc_info *info = parsing_heredoc_info(p);
                      info->doc = push(info->doc, (yyvsp[0].nd));
                      heredoc_treat_nextline(p);
                    }
#line 10192 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 467: /* @30: %empty  */
#line 3883 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = push_strterm(p);
                    }
#line 10200 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 468: /* heredoc_string_interp: tHD_STRING_PART @30 compstmt '}'  */
#line 3888 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      pop_strterm(p, (yyvsp[-2].nd));
                      parser_heredoc_info *info = parsing_heredoc_info(p);
                      /* $1 is already in (len . str) format, create (-1 . node) for expression */
                      node *expr_elem = cons(int_to_node(-1), (yyvsp[-1].nd));
                      info->doc = push(push(info->doc, (yyvsp[-3].nd)), expr_elem);
                    }
#line 10212 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 469: /* words: tWORDS_BEG tSTRING  */
#line 3898 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_words(p, list1((yyvsp[0].nd)));
                    }
#line 10220 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 470: /* words: tWORDS_BEG string_rep tSTRING  */
#line 3902 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      node *n = (yyvsp[-1].nd);
                      n = push(n, (yyvsp[0].nd));
                      (yyval.nd) = new_words(p, n);
                    }
#line 10230 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 471: /* symbol: basic_symbol  */
#line 3910 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_sym(p, (yyvsp[0].id));
                    }
#line 10238 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 472: /* symbol: "symbol" "string literal" string_rep tSTRING  */
#line 3914 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      node *n = (yyvsp[-1].nd);
                      p->lstate = EXPR_ENDARG;
                      if (node_to_int((yyvsp[0].nd)->car) > 0) {
                        n = push(n, (yyvsp[0].nd));
                      }
                      else {
                        cons_free((yyvsp[0].nd));
                      }
                      (yyval.nd) = new_dsym(p, n);
                    }
#line 10254 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 473: /* symbol: "symbol" "numbered parameter"  */
#line 3926 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      mrb_sym sym = intern_numparam((yyvsp[0].num));
                      (yyval.nd) = new_sym(p, sym);
                    }
#line 10263 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 474: /* basic_symbol: "symbol" sym  */
#line 3933 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      p->lstate = EXPR_END;
                      (yyval.id) = (yyvsp[0].id);
                    }
#line 10272 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 479: /* sym: tSTRING  */
#line 3944 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.id) = new_strsym(p, (yyvsp[0].nd));
                    }
#line 10280 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 480: /* sym: "string literal" tSTRING  */
#line 3948 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.id) = new_strsym(p, (yyvsp[0].nd));
                    }
#line 10288 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 481: /* symbols: tSYMBOLS_BEG tSTRING  */
#line 3954 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_symbols(p, list1((yyvsp[0].nd)));
                    }
#line 10296 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 482: /* symbols: tSYMBOLS_BEG string_rep tSTRING  */
#line 3958 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      node *n = (yyvsp[-1].nd);
                      n = push(n, (yyvsp[0].nd));
                      (yyval.nd) = new_symbols(p, n);
                    }
#line 10306 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 485: /* numeric: tUMINUS_NUM "integer literal"  */
#line 3968 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_negate(p, (yyvsp[0].nd));
                    }
#line 10314 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 486: /* numeric: tUMINUS_NUM "float literal"  */
#line 3972 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_negate(p, (yyvsp[0].nd));
                    }
#line 10322 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 487: /* variable: "local variable or method"  */
#line 3978 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_lvar(p, (yyvsp[0].id));
                    }
#line 10330 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 488: /* variable: "instance variable"  */
#line 3982 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_ivar(p, (yyvsp[0].id));
                    }
#line 10338 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 489: /* variable: "global variable"  */
#line 3986 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_gvar(p, (yyvsp[0].id));
                    }
#line 10346 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 490: /* variable: "class variable"  */
#line 3990 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_cvar(p, (yyvsp[0].id));
                    }
#line 10354 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 491: /* variable: "constant"  */
#line 3994 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_const(p, (yyvsp[0].id));
                    }
#line 10362 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 492: /* var_lhs: variable  */
#line 4000 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      assignable(p, (yyvsp[0].nd));
                    }
#line 10370 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 493: /* var_lhs: "numbered parameter"  */
#line 4004 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      yyerror(&(yylsp[0]), p, "can't assign to numbered parameter");
                    }
#line 10378 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 494: /* var_ref: variable  */
#line 4010 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = var_reference(p, (yyvsp[0].nd));
                    }
#line 10386 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 495: /* var_ref: "numbered parameter"  */
#line 4014 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_nvar(p, (yyvsp[0].num));
                    }
#line 10394 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 496: /* var_ref: "'nil'"  */
#line 4018 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_nil(p);
                    }
#line 10402 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 497: /* var_ref: "'self'"  */
#line 4022 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_self(p);
                    }
#line 10410 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 498: /* var_ref: "'true'"  */
#line 4026 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_true(p);
                    }
#line 10418 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 499: /* var_ref: "'false'"  */
#line 4030 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_false(p);
                    }
#line 10426 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 500: /* var_ref: "'__FILE__'"  */
#line 4034 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      const char *fn = mrb_sym_name_len(p->mrb, p->filename_sym, NULL);
                      if (!fn) {
                        fn = "(null)";
                      }
                      (yyval.nd) = new_str(p, cons(cons(int_to_node(strlen(fn)), (node*)fn), (node*)NULL));
                    }
#line 10438 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 501: /* var_ref: "'__LINE__'"  */
#line 4042 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      char buf[16];

                      dump_int(p->lineno, buf);
                      (yyval.nd) = new_int(p, buf, 10, 0);
                    }
#line 10449 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 502: /* var_ref: "'__ENCODING__'"  */
#line 4049 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_fcall(p, MRB_SYM_2(p->mrb, __ENCODING__), 0);
                    }
#line 10457 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 505: /* superclass: %empty  */
#line 4059 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = 0;
                    }
#line 10465 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 506: /* $@31: %empty  */
#line 4063 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      p->lstate = EXPR_BEG;
                      p->cmd_start = TRUE;
                    }
#line 10474 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 507: /* superclass: '<' $@31 expr_value term  */
#line 4068 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[-1].nd);
                    }
#line 10482 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 510: /* f_arglist_paren: '(' f_args rparen  */
#line 4084 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[-1].nd);
                      p->lstate = EXPR_BEG;
                      p->cmd_start = TRUE;
                    }
#line 10492 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 511: /* f_arglist_paren: '(' f_arg ',' tBDOT3 rparen  */
#line 4090 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args_dots(p, (yyvsp[-3].nd));
                    }
#line 10500 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 512: /* f_arglist_paren: '(' tBDOT3 rparen  */
#line 4094 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args_dots(p, 0);
                    }
#line 10508 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 514: /* f_arglist: f_args term  */
#line 4101 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[-1].nd);
                    }
#line 10516 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 515: /* f_arglist: f_arg ',' tBDOT3 term  */
#line 4105 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args_dots(p, (yyvsp[-3].nd));
                    }
#line 10524 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 516: /* f_arglist: "..." term  */
#line 4109 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args_dots(p, 0);
                    }
#line 10532 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 517: /* f_label: "local variable or method" "label"  */
#line 4115 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      local_nest(p);
                    }
#line 10540 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 518: /* f_label: "numbered parameter" "label"  */
#line 4119 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      local_nest(p);
                    }
#line 10548 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 519: /* f_kw: f_label arg  */
#line 4125 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      void_expr_error(p, (yyvsp[0].nd));
                      (yyval.nd) = new_kw_arg(p, (yyvsp[-1].id), cons((yyvsp[0].nd), locals_node(p)));
                      local_unnest(p);
                    }
#line 10558 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 520: /* f_kw: f_label  */
#line 4131 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_kw_arg(p, (yyvsp[0].id), 0);
                      local_unnest(p);
                    }
#line 10567 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 521: /* f_block_kw: f_label primary_value  */
#line 4138 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      void_expr_error(p, (yyvsp[0].nd));
                      (yyval.nd) = new_kw_arg(p, (yyvsp[-1].id), cons((yyvsp[0].nd), locals_node(p)));
                      local_unnest(p);
                    }
#line 10577 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 522: /* f_block_kw: f_label  */
#line 4144 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_kw_arg(p, (yyvsp[0].id), 0);
                      local_unnest(p);
                    }
#line 10586 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 523: /* f_block_kwarg: f_block_kw  */
#line 4151 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list1((yyvsp[0].nd));
                    }
#line 10594 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 524: /* f_block_kwarg: f_block_kwarg ',' f_block_kw  */
#line 4155 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = push((yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 10602 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 525: /* f_kwarg: f_kw  */
#line 4161 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list1((yyvsp[0].nd));
                    }
#line 10610 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 526: /* f_kwarg: f_kwarg ',' f_kw  */
#line 4165 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = push((yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 10618 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 529: /* f_kwrest: kwrest_mark "local variable or method"  */
#line 4175 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.id) = (yyvsp[0].id);
                    }
#line 10626 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 530: /* f_kwrest: kwrest_mark  */
#line 4179 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.id) = intern_op(pow);
                    }
#line 10634 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 531: /* args_tail: f_kwarg ',' f_kwrest opt_f_block_arg  */
#line 4185 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args_tail(p, (yyvsp[-3].nd), (yyvsp[-1].id), (yyvsp[0].id));
                    }
#line 10642 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 532: /* args_tail: f_kwarg opt_f_block_arg  */
#line 4189 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args_tail(p, (yyvsp[-1].nd), 0, (yyvsp[0].id));
                    }
#line 10650 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 533: /* args_tail: f_kwrest opt_f_block_arg  */
#line 4193 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args_tail(p, 0, (yyvsp[-1].id), (yyvsp[0].id));
                    }
#line 10658 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 534: /* args_tail: f_block_arg  */
#line 4197 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args_tail(p, 0, 0, (yyvsp[0].id));
                    }
#line 10666 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 535: /* opt_args_tail: ',' args_tail  */
#line 4203 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[0].nd);
                    }
#line 10674 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 536: /* opt_args_tail: %empty  */
#line 4207 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args_tail(p, 0, 0, 0);
                    }
#line 10682 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 537: /* f_args: f_arg ',' f_optarg ',' f_rest_arg opt_args_tail  */
#line 4213 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, (yyvsp[-5].nd), (yyvsp[-3].nd), (yyvsp[-1].id), 0, (yyvsp[0].nd));
                    }
#line 10690 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 538: /* f_args: f_arg ',' f_optarg ',' f_rest_arg ',' f_arg opt_args_tail  */
#line 4217 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, (yyvsp[-7].nd), (yyvsp[-5].nd), (yyvsp[-3].id), (yyvsp[-1].nd), (yyvsp[0].nd));
                    }
#line 10698 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 539: /* f_args: f_arg ',' f_optarg opt_args_tail  */
#line 4221 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, (yyvsp[-3].nd), (yyvsp[-1].nd), 0, 0, (yyvsp[0].nd));
                    }
#line 10706 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 540: /* f_args: f_arg ',' f_optarg ',' f_arg opt_args_tail  */
#line 4225 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, (yyvsp[-5].nd), (yyvsp[-3].nd), 0, (yyvsp[-1].nd), (yyvsp[0].nd));
                    }
#line 10714 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 541: /* f_args: f_arg ',' f_rest_arg opt_args_tail  */
#line 4229 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, (yyvsp[-3].nd), 0, (yyvsp[-1].id), 0, (yyvsp[0].nd));
                    }
#line 10722 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 542: /* f_args: f_arg ',' f_rest_arg ',' f_arg opt_args_tail  */
#line 4233 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, (yyvsp[-5].nd), 0, (yyvsp[-3].id), (yyvsp[-1].nd), (yyvsp[0].nd));
                    }
#line 10730 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 543: /* f_args: f_arg opt_args_tail  */
#line 4237 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, (yyvsp[-1].nd), 0, 0, 0, (yyvsp[0].nd));
                    }
#line 10738 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 544: /* f_args: f_optarg ',' f_rest_arg opt_args_tail  */
#line 4241 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, 0, (yyvsp[-3].nd), (yyvsp[-1].id), 0, (yyvsp[0].nd));
                    }
#line 10746 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 545: /* f_args: f_optarg ',' f_rest_arg ',' f_arg opt_args_tail  */
#line 4245 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, 0, (yyvsp[-5].nd), (yyvsp[-3].id), (yyvsp[-1].nd), (yyvsp[0].nd));
                    }
#line 10754 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 546: /* f_args: f_optarg opt_args_tail  */
#line 4249 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, 0, (yyvsp[-1].nd), 0, 0, (yyvsp[0].nd));
                    }
#line 10762 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 547: /* f_args: f_optarg ',' f_arg opt_args_tail  */
#line 4253 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, 0, (yyvsp[-3].nd), 0, (yyvsp[-1].nd), (yyvsp[0].nd));
                    }
#line 10770 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 548: /* f_args: f_rest_arg opt_args_tail  */
#line 4257 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, 0, 0, (yyvsp[-1].id), 0, (yyvsp[0].nd));
                    }
#line 10778 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 549: /* f_args: f_rest_arg ',' f_arg opt_args_tail  */
#line 4261 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, 0, 0, (yyvsp[-3].id), (yyvsp[-1].nd), (yyvsp[0].nd));
                    }
#line 10786 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 550: /* f_args: args_tail  */
#line 4265 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, 0, 0, 0, 0, (yyvsp[0].nd));
                    }
#line 10794 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 551: /* f_args: %empty  */
#line 4269 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      local_add_f(p, 0);
                      (yyval.nd) = new_args(p, 0, 0, 0, 0, 0);
                    }
#line 10803 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 552: /* f_bad_arg: "constant"  */
#line 4276 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      yyerror(&(yylsp[0]), p, "formal argument cannot be a constant");
                      (yyval.nd) = 0;
                    }
#line 10812 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 553: /* f_bad_arg: "instance variable"  */
#line 4281 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      yyerror(&(yylsp[0]), p, "formal argument cannot be an instance variable");
                      (yyval.nd) = 0;
                    }
#line 10821 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 554: /* f_bad_arg: "global variable"  */
#line 4286 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      yyerror(&(yylsp[0]), p, "formal argument cannot be a global variable");
                      (yyval.nd) = 0;
                    }
#line 10830 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 555: /* f_bad_arg: "class variable"  */
#line 4291 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      yyerror(&(yylsp[0]), p, "formal argument cannot be a class variable");
                      (yyval.nd) = 0;
                    }
#line 10839 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 556: /* f_bad_arg: "numbered parameter"  */
#line 4296 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      yyerror(&(yylsp[0]), p, "formal argument cannot be a numbered parameter");
                      (yyval.nd) = 0;
                    }
#line 10848 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 557: /* f_norm_arg: f_bad_arg  */
#line 4303 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.id) = 0;
                    }
#line 10856 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 558: /* f_norm_arg: "local variable or method"  */
#line 4307 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      local_add_f(p, (yyvsp[0].id));
                      (yyval.id) = (yyvsp[0].id);
                    }
#line 10865 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 559: /* f_arg_item: f_norm_arg  */
#line 4314 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_lvar(p, (yyvsp[0].id));
                    }
#line 10873 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 560: /* @32: %empty  */
#line 4318 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = local_switch(p);
                    }
#line 10881 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 561: /* f_arg_item: tLPAREN @32 f_margs rparen  */
#line 4322 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_marg(p, (yyvsp[-1].nd));
                      local_resume(p, (yyvsp[-2].nd));
                      local_add_f(p, 0);
                    }
#line 10891 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 562: /* f_arg: f_arg_item  */
#line 4330 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list1((yyvsp[0].nd));
                    }
#line 10899 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 563: /* f_arg: f_arg ',' f_arg_item  */
#line 4334 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = push((yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 10907 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 564: /* f_opt_asgn: "local variable or method" '='  */
#line 4340 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      local_add_f(p, (yyvsp[-1].id));
                      local_nest(p);
                      (yyval.id) = (yyvsp[-1].id);
                    }
#line 10917 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 565: /* f_opt: f_opt_asgn arg  */
#line 4348 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      void_expr_error(p, (yyvsp[0].nd));
                      (yyval.nd) = cons(sym_to_node((yyvsp[-1].id)), cons((yyvsp[0].nd), locals_node(p)));
                      local_unnest(p);
                    }
#line 10927 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 566: /* f_block_opt: f_opt_asgn primary_value  */
#line 4356 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      void_expr_error(p, (yyvsp[0].nd));
                      (yyval.nd) = cons(sym_to_node((yyvsp[-1].id)), cons((yyvsp[0].nd), locals_node(p)));
                      local_unnest(p);
                    }
#line 10937 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 567: /* f_block_optarg: f_block_opt  */
#line 4364 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list1((yyvsp[0].nd));
                    }
#line 10945 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 568: /* f_block_optarg: f_block_optarg ',' f_block_opt  */
#line 4368 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = push((yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 10953 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 569: /* f_optarg: f_opt  */
#line 4374 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list1((yyvsp[0].nd));
                    }
#line 10961 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 570: /* f_optarg: f_optarg ',' f_opt  */
#line 4378 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = push((yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 10969 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 573: /* f_rest_arg: restarg_mark "local variable or method"  */
#line 4388 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      local_add_f(p, (yyvsp[0].id));
                      (yyval.id) = (yyvsp[0].id);
                    }
#line 10978 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 574: /* f_rest_arg: restarg_mark  */
#line 4393 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.id) = intern_op(mul);
                      local_add_f(p, (yyval.id));
                    }
#line 10987 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 577: /* f_block_arg: blkarg_mark "local variable or method"  */
#line 4404 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.id) = (yyvsp[0].id);
                    }
#line 10995 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 578: /* f_block_arg: blkarg_mark  */
#line 4408 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.id) = intern_op(and);
                    }
#line 11003 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 579: /* opt_f_block_arg: ',' f_block_arg  */
#line 4414 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.id) = (yyvsp[0].id);
                    }
#line 11011 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 580: /* opt_f_block_arg: none  */
#line 4418 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.id) = 0;
                    }
#line 11019 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 581: /* singleton: var_ref  */
#line 4424 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      prohibit_literals(p, (yyvsp[0].nd));
                      (yyval.nd) = (yyvsp[0].nd);
                      if (!(yyval.nd)) (yyval.nd) = new_nil(p);
                    }
#line 11029 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 582: /* $@33: %empty  */
#line 4429 "mrbgems/mruby-compiler/core/parse.y"
                      {p->lstate = EXPR_BEG;}
#line 11035 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 583: /* singleton: '(' $@33 expr rparen  */
#line 4430 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      prohibit_literals(p, (yyvsp[-1].nd));
                      (yyval.nd) = (yyvsp[-1].nd);
                    }
#line 11044 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 585: /* assoc_list: assocs trailer  */
#line 4438 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[-1].nd);
                    }
#line 11052 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 586: /* assocs: assoc  */
#line 4444 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list1((yyvsp[0].nd));
                    }
#line 11060 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 587: /* assocs: assocs comma assoc  */
#line 4448 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = push((yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 11068 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 588: /* assoc: arg "=>" arg  */
#line 4454 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      void_expr_error(p, (yyvsp[-2].nd));
                      void_expr_error(p, (yyvsp[0].nd));
                      (yyval.nd) = cons((yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 11078 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 589: /* assoc: "local variable or method" "label" arg  */
#line 4460 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      void_expr_error(p, (yyvsp[0].nd));
                      (yyval.nd) = cons(new_sym(p, (yyvsp[-2].id)), (yyvsp[0].nd));
                    }
#line 11087 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 590: /* assoc: "local variable or method" "label"  */
#line 4465 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = cons(new_sym(p, (yyvsp[-1].id)), label_reference(p, (yyvsp[-1].id)));
                    }
#line 11095 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 591: /* assoc: "numbered parameter" "label"  */
#line 4469 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      mrb_sym sym = intern_numparam((yyvsp[-1].num));
                      (yyval.nd) = cons(new_sym(p, sym), label_reference(p, sym));
                    }
#line 11104 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 592: /* assoc: "numbered parameter" "label" arg  */
#line 4474 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      void_expr_error(p, (yyvsp[0].nd));
                      (yyval.nd) = cons(new_sym(p, intern_numparam((yyvsp[-2].num))), (yyvsp[0].nd));
                    }
#line 11113 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 593: /* assoc: string_fragment "label" arg  */
#line 4479 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      void_expr_error(p, (yyvsp[0].nd));
                      if ((yyvsp[-2].nd)->cdr) {
                        /* Multiple fragments - create dynamic symbol */
                        (yyval.nd) = cons(new_dsym(p, (yyvsp[-2].nd)), (yyvsp[0].nd));
                      }
                      else if (node_to_int((yyvsp[-2].nd)->car->car) < 0) {
                        /* Single fragment but it's an expression (-1 . node) - create dynamic symbol */
                        (yyval.nd) = cons(new_dsym(p, (yyvsp[-2].nd)), (yyvsp[0].nd));
                      }
                      else {
                        /* Single string fragment - create simple symbol */
                        (yyval.nd) = cons(new_sym(p, new_strsym(p, (yyvsp[-2].nd)->car)), (yyvsp[0].nd));
                      }
                    }
#line 11133 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 594: /* assoc: "**" arg  */
#line 4495 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      void_expr_error(p, (yyvsp[0].nd));
                      (yyval.nd) = cons(new_kw_rest_args(p, 0), (yyvsp[0].nd));
                    }
#line 11142 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 595: /* assoc: "**"  */
#line 4500 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = cons(new_kw_rest_args(p, 0), new_lvar(p, intern_op(pow)));
                    }
#line 11150 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 608: /* call_op: '.'  */
#line 4526 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.num) = '.';
                    }
#line 11158 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 609: /* call_op: "&."  */
#line 4530 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.num) = 0;
                    }
#line 11166 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 611: /* call_op2: "::"  */
#line 4537 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.num) = tCOLON2;
                    }
#line 11174 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 620: /* term: ';'  */
#line 4558 "mrbgems/mruby-compiler/core/parse.y"
                      {yyerrok;}
#line 11180 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 622: /* nl: '\n'  */
#line 4563 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      p->lineno += (yyvsp[0].num);
                      p->column = 0;
                    }
#line 11189 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 626: /* none: %empty  */
#line 4575 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = 0;
                    }
#line 11197 "mrbgems/mruby-compiler/core/y.tab.c"
    break;


#line 11201 "mrbgems/mruby-compiler/core/y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc, p);

  YYPOPSTACK (yylen);

  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx, p);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx, p);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (&yylloc, p, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc, p);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);

  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp, p);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, p);
      YYPOPSTACK (1);

      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp, p);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp, p);


  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, p, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, p);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp, p);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, p);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 4579 "mrbgems/mruby-compiler/core/parse.y"

#define pylval  (*((YYSTYPE*)(p->ylval)))

static void
yyerror(void *lp, parser_state *p, const char *s)
{
  char* c;
  size_t n;

  if (! p->capture_errors) {
#ifndef MRB_NO_STDIO
    if (p->filename_sym) {
      const char *filename = mrb_sym_name_len(p->mrb, p->filename_sym, NULL);
      fprintf(stderr, "%s:%d:%d: %s\n", filename, p->lineno, p->column, s);
    }
    else {
      fprintf(stderr, "line %d:%d: %s\n", p->lineno, p->column, s);
    }
#endif
  }
  else if (p->nerr < sizeof(p->error_buffer) / sizeof(p->error_buffer[0])) {
    n = strlen(s);
    c = (char*)parser_palloc(p, n + 1);
    memcpy(c, s, n + 1);
    p->error_buffer[p->nerr].message = c;
    p->error_buffer[p->nerr].lineno = p->lineno;
    p->error_buffer[p->nerr].column = p->column;
  }
  p->nerr++;
}

static void
yyerror_c(parser_state *p, const char *msg, char c)
{
  char buf[256];

  strncpy(buf, msg, sizeof(buf) - 2);
  buf[sizeof(buf) - 2] = '\0';
  strncat(buf, &c, 1);
  yyerror(NULL, p, buf);
}

static void
yywarning(parser_state *p, const char *s)
{
  char* c;
  size_t n;

  if (! p->capture_errors) {
#ifndef MRB_NO_STDIO
    if (p->filename_sym) {
      const char *filename = mrb_sym_name_len(p->mrb, p->filename_sym, NULL);
      fprintf(stderr, "%s:%d:%d: warning: %s\n", filename, p->lineno, p->column, s);
    }
    else {
      fprintf(stderr, "line %d:%d: warning: %s\n", p->lineno, p->column, s);
    }
#endif
  }
  else if (p->nwarn < sizeof(p->warn_buffer) / sizeof(p->warn_buffer[0])) {
    n = strlen(s);
    c = (char*)parser_palloc(p, n + 1);
    memcpy(c, s, n + 1);
    p->warn_buffer[p->nwarn].message = c;
    p->warn_buffer[p->nwarn].lineno = p->lineno;
    p->warn_buffer[p->nwarn].column = p->column;
  }
  p->nwarn++;
}

static void
yywarning_s(parser_state *p, const char *msg, const char *s)
{
  char buf[256];

  strncpy(buf, msg, sizeof(buf) - 1);
  buf[sizeof(buf) - 1] = '\0';
  strncat(buf, ": ", sizeof(buf) - strlen(buf) - 1);
  strncat(buf, s, sizeof(buf) - strlen(buf) - 1);
  yywarning(p, buf);
}

static void
backref_error(parser_state *p, node *n)
{
  int c;

  c = node_to_int(n->car);

  if (c == NODE_NTH_REF) {
    yyerror_c(p, "can't set variable $", (char)node_to_int(n->cdr)+'0');
  }
  else if (c == NODE_BACK_REF) {
    yyerror_c(p, "can't set variable $", (char)node_to_int(n->cdr));
  }
  else {
    yyerror(NULL, p, "Internal error in backref_error()");
  }
}

static void
void_expr_error(parser_state *p, node *n)
{
  if (n == NULL) return;

  /* Check if this is a variable-sized node first */
  struct mrb_ast_var_header *header = (struct mrb_ast_var_header*)n;
  if (header) {
    /* Handle variable-sized nodes */
    switch ((enum node_type)header->node_type) {
    case NODE_BREAK:
    case NODE_RETURN:
    case NODE_NEXT:
    case NODE_REDO:
    case NODE_RETRY:
      yyerror(NULL, p, "void value expression");
      return;
    case NODE_AND:
    case NODE_OR:
      {
        struct mrb_ast_and_node *and_n = (struct mrb_ast_and_node*)n;
        void_expr_error(p, (node*)and_n->left);
        void_expr_error(p, (node*)and_n->right);
      }
      return;
    case NODE_STMTS:
      {
        struct mrb_ast_stmts_node *stmts = (struct mrb_ast_stmts_node*)n;
        node *last = stmts->stmts;
        if (last) {
          /* Find the last statement in the cons list */
          while (last->cdr) {
            last = last->cdr;
          }
          void_expr_error(p, last->car);
        }
      }
      return;
    case NODE_BEGIN:
      {
        struct mrb_ast_begin_node *begin_n = (struct mrb_ast_begin_node*)n;
        if (begin_n->body) {
          void_expr_error(p, (node*)begin_n->body);
        }
      }
      return;
    default:
      /* Other variable-sized nodes are OK */
      return;
    }
  }

  /* Should not reach here - all nodes should be variable-sized now */
}

static void pushback(parser_state *p, int c);
static mrb_bool peeks(parser_state *p, const char *s);
static mrb_bool skips(parser_state *p, const char *s);

static inline int
nextc0(parser_state *p)
{
  if (p->s && p->s < p->send) {
    return (unsigned char)*p->s++;
  }
  else {
#ifndef MRB_NO_STDIO
    int c;

    if (p->f) {
      c = fgetc(p->f);
      if (!feof(p->f)) return c;
    }
#endif
    return -1;
  }
}

static inline int
nextc(parser_state *p)
{
  int c;

  if (p->pb) {
    node *tmp;

    c = node_to_int(p->pb->car);
    tmp = p->pb;
    p->pb = p->pb->cdr;
    cons_free(tmp);
  }
  else {
    c = nextc0(p);
    if (c < 0) goto eof;
  }
  if (c >= 0) {
    p->column++;
  }
  if (c == '\r') {
    const int lf = nextc0(p);
    if (lf == '\n') {
      return '\n';
    }
    if (lf > 0) pushback(p, lf);
  }
  return c;

  eof:
  if (!p->cxt) return -1;
  else {
    if (p->cxt->partial_hook(p) < 0)
      return -1;                /* end of program(s) */
    return -2;                  /* end of a file in the program files */
  }
}

static void
pushback(parser_state *p, int c)
{
  if (c >= 0) {
    p->column--;
  }
  p->pb = cons(int_to_node(c), p->pb);
}

static void
skip(parser_state *p, char term)
{
  int c;

  for (;;) {
    c = nextc(p);
    if (c < 0) break;
    if (c == term) break;
  }
}

static int
peekc_n(parser_state *p, int n)
{
  node *list = 0;
  int c0;

  do {
    c0 = nextc(p);
    if (c0 == -1) return c0;    /* do not skip partial EOF */
    if (c0 >= 0) --p->column;
    list = push(list, int_to_node(c0));
  } while(n--);
  if (p->pb) {
    p->pb = append(list, p->pb);
  }
  else {
    p->pb = list;
  }
  return c0;
}

static mrb_bool
peek_n(parser_state *p, int c, int n)
{
  return peekc_n(p, n) == c && c >= 0;
}
#define peek(p,c) peek_n((p), (c), 0)

static mrb_bool
peeks(parser_state *p, const char *s)
{
  size_t len = strlen(s);

#ifndef MRB_NO_STDIO
  if (p->f) {
    int n = 0;
    while (*s) {
      if (!peek_n(p, *s++, n++)) return FALSE;
    }
    return TRUE;
  }
  else
#endif
    if (p->s && p->s + len <= p->send) {
      if (memcmp(p->s, s, len) == 0) return TRUE;
    }
  return FALSE;
}

static mrb_bool
skips(parser_state *p, const char *s)
{
  int c;

  for (;;) {
    /* skip until first char */
    for (;;) {
      c = nextc(p);
      if (c < 0) return FALSE;
      if (c == '\n') {
        p->lineno++;
        p->column = 0;
      }
      if (c == *s) break;
    }
    s++;
    if (peeks(p, s)) {
      size_t len = strlen(s);

      while (len--) {
        if (nextc(p) == '\n') {
          p->lineno++;
          p->column = 0;
        }
      }
      return TRUE;
    }
    else {
      s--;
    }
  }
  return FALSE;
}

static int
newtok(parser_state *p)
{
  if (p->tokbuf != p->buf) {
    mrbc_free(p->tokbuf);
    p->tokbuf = p->buf;
    p->tsiz = MRB_PARSER_TOKBUF_SIZE;
  }
  p->tidx = 0;
  return p->column - 1;
}

static void
tokadd(parser_state *p, int32_t c)
{
  char utf8[4];
  int i, len;

  /* mrb_assert(-0x10FFFF <= c && c <= 0xFF); */
  if (c >= 0) {
    /* Single byte from source or non-Unicode escape */
    utf8[0] = (char)c;
    len = 1;
  }
  else {
    /* Unicode character */
    c = -c;
    if (c < 0x80) {
      utf8[0] = (char)c;
      len = 1;
    }
    else if (c < 0x800) {
      utf8[0] = (char)(0xC0 | (c >> 6));
      utf8[1] = (char)(0x80 | (c & 0x3F));
      len = 2;
    }
    else if (c < 0x10000) {
      utf8[0] = (char)(0xE0 |  (c >> 12)        );
      utf8[1] = (char)(0x80 | ((c >>  6) & 0x3F));
      utf8[2] = (char)(0x80 | ( c        & 0x3F));
      len = 3;
    }
    else {
      utf8[0] = (char)(0xF0 |  (c >> 18)        );
      utf8[1] = (char)(0x80 | ((c >> 12) & 0x3F));
      utf8[2] = (char)(0x80 | ((c >>  6) & 0x3F));
      utf8[3] = (char)(0x80 | ( c        & 0x3F));
      len = 4;
    }
  }
  if (p->tidx+len >= p->tsiz) {
    if (p->tsiz >= MRB_PARSER_TOKBUF_MAX) {
      p->tidx += len;
      return;
    }
    p->tsiz *= 2;
    if (p->tokbuf == p->buf) {
      p->tokbuf = (char*)mrbc_malloc(p->tsiz);
      memcpy(p->tokbuf, p->buf, MRB_PARSER_TOKBUF_SIZE);
    }
    else {
      p->tokbuf = (char*)mrbc_realloc(p->tokbuf, p->tsiz);
    }
  }
  for (i = 0; i < len; i++) {
    p->tokbuf[p->tidx++] = utf8[i];
  }
}

static int
toklast(parser_state *p)
{
  return p->tokbuf[p->tidx-1];
}

static void
tokfix(parser_state *p)
{
  if (p->tidx >= MRB_PARSER_TOKBUF_MAX) {
    p->tidx = MRB_PARSER_TOKBUF_MAX-1;
    yyerror(NULL, p, "string too long (truncated)");
  }
  p->tokbuf[p->tidx] = '\0';
}

static const char*
tok(parser_state *p)
{
  return p->tokbuf;
}

static int
toklen(parser_state *p)
{
  return p->tidx;
}

#define IS_ARG() (p->lstate == EXPR_ARG || p->lstate == EXPR_CMDARG)
#define IS_END() (p->lstate == EXPR_END || p->lstate == EXPR_ENDARG || p->lstate == EXPR_ENDFN)
#define IS_BEG() (p->lstate == EXPR_BEG || p->lstate == EXPR_MID || p->lstate == EXPR_VALUE || p->lstate == EXPR_CLASS)
#define IS_SPCARG(c) (IS_ARG() && space_seen && !ISSPACE(c))
#define IS_LABEL_POSSIBLE() ((p->lstate == EXPR_BEG && !cmd_state) || IS_ARG())
#define IS_LABEL_SUFFIX(n) (peek_n(p, ':',(n)) && !peek_n(p, ':', (n)+1))

static int32_t
scan_oct(const int *start, int len, int *retlen)
{
  const int *s = start;
  int32_t retval = 0;

  /* mrb_assert(len <= 3) */
  while (len-- && *s >= '0' && *s <= '7') {
    retval <<= 3;
    retval |= *s++ - '0';
  }
  *retlen = (int)(s - start);

  return retval;
}

static int32_t
scan_hex(parser_state *p, const int *start, int len, int *retlen)
{
  static const char hexdigit[] = "0123456789abcdef0123456789ABCDEF";
  const int *s = start;
  uint32_t retval = 0;
  char *tmp;

  /* mrb_assert(len <= 8) */
  while (len-- && *s && (tmp = (char*)strchr(hexdigit, *s))) {
    retval <<= 4;
    retval |= (tmp - hexdigit) & 15;
    s++;
  }
  *retlen = (int)(s - start);

  return (int32_t)retval;
}

static int32_t
read_escape_unicode(parser_state *p, int limit)
{
  int buf[9];
  int i;
  int32_t hex;

  /* Look for opening brace */
  i = 0;
  buf[0] = nextc(p);
  if (buf[0] < 0) {
  eof:
    yyerror(NULL, p, "invalid escape character syntax");
    return -1;
  }
  if (ISXDIGIT(buf[0])) {
    /* \uxxxx form */
    for (i=1; i<limit; i++) {
      buf[i] = nextc(p);
      if (buf[i] < 0) goto eof;
      if (!ISXDIGIT(buf[i])) {
        pushback(p, buf[i]);
        break;
      }
    }
  }
  else {
    pushback(p, buf[0]);
  }
  hex = scan_hex(p, buf, i, &i);
  if (i == 0 || hex > 0x10FFFF || (hex & 0xFFFFF800) == 0xD800) {
    yyerror(NULL, p, "invalid Unicode code point");
    return -1;
  }
  return hex;
}

/* Return negative to indicate Unicode code point */
static int32_t
read_escape(parser_state *p)
{
  int32_t c;

  switch (c = nextc(p)) {
  case '\\':/* Backslash */
    return c;

  case 'n':/* newline */
    return '\n';

  case 't':/* horizontal tab */
    return '\t';

  case 'r':/* carriage-return */
    return '\r';

  case 'f':/* form-feed */
    return '\f';

  case 'v':/* vertical tab */
    return '\13';

  case 'a':/* alarm(bell) */
    return '\007';

  case 'e':/* escape */
    return 033;

  case '0': case '1': case '2': case '3': /* octal constant */
  case '4': case '5': case '6': case '7':
  {
    int buf[3];
    int i;

    buf[0] = c;
    for (i=1; i<3; i++) {
      buf[i] = nextc(p);
      if (buf[i] < 0) goto eof;
      if (buf[i] < '0' || '7' < buf[i]) {
        pushback(p, buf[i]);
        break;
      }
    }
    c = scan_oct(buf, i, &i);
  }
  return c;

  case 'x':     /* hex constant */
  {
    int buf[2];
    int i;

    for (i=0; i<2; i++) {
      buf[i] = nextc(p);
      if (buf[i] < 0) goto eof;
      if (!ISXDIGIT(buf[i])) {
        pushback(p, buf[i]);
        break;
      }
    }
    if (i == 0) {
      yyerror(NULL, p, "invalid hex escape");
      return -1;
    }
    return scan_hex(p, buf, i, &i);
  }

  case 'u':     /* Unicode */
    if (peek(p, '{')) {
      /* \u{xxxxxxxx} form */
      nextc(p);
      c = read_escape_unicode(p, 8);
      if (c < 0) return 0;
      if (nextc(p) != '}') goto eof;
    }
    else {
      c = read_escape_unicode(p, 4);
      if (c < 0) return 0;
    }
    return -c;

  case 'b':/* backspace */
    return '\010';

  case 's':/* space */
    return ' ';

  case 'M':
    if ((c = nextc(p)) != '-') {
      yyerror(NULL, p, "Invalid escape character syntax");
      pushback(p, c);
      return '\0';
    }
    if ((c = nextc(p)) == '\\') {
      return read_escape(p) | 0x80;
    }
    else if (c < 0) goto eof;
    else {
      return ((c & 0xff) | 0x80);
    }

  case 'C':
    if ((c = nextc(p)) != '-') {
      yyerror(NULL, p, "Invalid escape character syntax");
      pushback(p, c);
      return '\0';
    }
  case 'c':
    if ((c = nextc(p))== '\\') {
      c = read_escape(p);
    }
    else if (c == '?')
      return 0177;
    else if (c < 0) goto eof;
    return c & 0x9f;

    eof:
  case -1:
  case -2:                      /* end of a file */
    yyerror(NULL, p, "Invalid escape character syntax");
    return '\0';

  default:
    return c;
  }
}

static void
heredoc_count_indent(parser_heredoc_info *hinfo, const char *str, size_t len, size_t spaces, size_t *offset)
{
  size_t indent = 0;
  *offset = 0;
  for (size_t i = 0; i < len; i++) {
    size_t size;
    if (str[i] == '\n')
      break;
    else if (str[i] == '\t')
      size = 8;
    else if (ISSPACE(str[i]))
      size = 1;
    else
      break;
    size_t nindent = indent + size;
    if (nindent > spaces || nindent > hinfo->indent)
      break;
    indent = nindent;
    *offset += 1;
  }
}

static void
heredoc_remove_indent(parser_state *p, parser_heredoc_info *hinfo)
{
  if (!hinfo->remove_indent || hinfo->indent == 0)
    return;
  node *indented, *n, *pair, *escaped, *nspaces;
  const char *str;
  size_t len, spaces, offset, start, end;
  indented = hinfo->indented;
  while (indented) {
    n = indented->car;
    pair = n->car;
    len = (size_t)pair->car;
    str = (char*)pair->cdr;
    escaped = n->cdr->car;
    nspaces = n->cdr->cdr;
    if (escaped) {
      char *newstr = strndup(str, len);
      size_t newlen = 0;
      start = 0;
      while (start < len) {
        end = escaped ? (size_t)escaped->car : len;
        if (end > len) end = len;
        spaces = (size_t)nspaces->car;
        size_t esclen = end - start;
        heredoc_count_indent(hinfo, str + start, esclen, spaces, &offset);
        esclen -= offset;
        memcpy(newstr + newlen, str + start + offset, esclen);
        newlen += esclen;
        start = end;
        if (escaped)
          escaped = escaped->cdr;
        nspaces = nspaces->cdr;
      }
      if (newlen < len)
        newstr[newlen] = '\0';
      pair->car = (node*)newlen;
      pair->cdr = (node*)newstr;
    }
    else {
      spaces = (size_t)nspaces->car;
      heredoc_count_indent(hinfo, str, len, spaces, &offset);
      pair->car = (node*)(len - offset);
      pair->cdr = (node*)(str + offset);
    }
    indented = indented->cdr;
  }
}

static void
heredoc_push_indented(parser_state *p, parser_heredoc_info *hinfo, node *pair, node *escaped, node *nspaces, mrb_bool empty_line)
{
  hinfo->indented = push(hinfo->indented, cons(pair, cons(escaped, nspaces)));
  while (nspaces) {
    size_t tspaces = (size_t)nspaces->car;
    if ((hinfo->indent == ~0U || tspaces < hinfo->indent) && !empty_line)
      hinfo->indent = tspaces;
    nspaces = nspaces->cdr;
  }
}

static int
parse_string(parser_state *p)
{
  int c;
  string_type type = (string_type)p->lex_strterm->type;
  int nest_level = p->lex_strterm->level;
  int beg = p->lex_strterm->paren;
  int end = p->lex_strterm->term;
  parser_heredoc_info *hinfo = (type & STR_FUNC_HEREDOC) ? parsing_heredoc_info(p) : NULL;

  mrb_bool unindent = hinfo && hinfo->remove_indent;
  mrb_bool head = hinfo && hinfo->line_head;
  mrb_bool empty = TRUE;
  size_t spaces = 0;
  size_t pos = -1;
  node *escaped = NULL;
  node *nspaces = NULL;

  if (beg == 0) beg = -3;       /* should never happen */
  if (end == 0) end = -3;
  newtok(p);
  while ((c = nextc(p)) != end || nest_level != 0) {
    pos++;
    if (hinfo && (c == '\n' || c < 0)) {
      mrb_bool line_head;
      tokadd(p, '\n');
      tokfix(p);
      p->lineno++;
      p->column = 0;
      line_head = hinfo->line_head;
      hinfo->line_head = TRUE;
      if (line_head) {
        /* check whether end of heredoc */
        const char *s = tok(p);
        int len = toklen(p);
        if (hinfo->allow_indent) {
          while (ISSPACE(*s) && len > 0) {
            s++;
            len--;
          }
        }
        if (hinfo->term_len > 0 && len-1 == hinfo->term_len && strncmp(s, hinfo->term, len-1) == 0) {
          heredoc_remove_indent(p, hinfo);
          return tHEREDOC_END;
        }
      }
      if (c < 0) {
        char buf[256];
        const char s1[] = "can't find heredoc delimiter \"";
        const char s2[] = "\" anywhere before EOF";

        if (sizeof(s1)+sizeof(s2)+strlen(hinfo->term)+1 >= sizeof(buf)) {
          yyerror(NULL, p, "can't find heredoc delimiter anywhere before EOF");
        }
        else {
          strcpy(buf, s1);
          strcat(buf, hinfo->term);
          strcat(buf, s2);
          yyerror(NULL, p, buf);
        }
        return 0;
      }
      pylval.nd = new_str_tok(p);
      if (unindent && head) {
        nspaces = push(nspaces, int_to_node(spaces));
        heredoc_push_indented(p, hinfo, pylval.nd, escaped, nspaces, empty && line_head);
      }
      return tHD_STRING_MID;
    }
    if (unindent && empty) {
      if (c == '\t')
        spaces += 8;
      else if (ISSPACE(c))
        spaces++;
      else
        empty = FALSE;
    }
    if (c < 0) {
      yyerror(NULL, p, "unterminated string meets end of file");
      return 0;
    }
    else if (c == beg) {
      nest_level++;
      p->lex_strterm->level = nest_level;
    }
    else if (c == end) {
      nest_level--;
      p->lex_strterm->level = nest_level;
    }
    else if (c == '\\') {
      c = nextc(p);
      if (type & STR_FUNC_EXPAND) {
        if (c == end || c == beg) {
          tokadd(p, c);
        }
        else if (c == '\n') {
          p->lineno++;
          p->column = 0;
          if (unindent) {
            nspaces = push(nspaces, int_to_node(spaces));
            escaped = push(escaped, int_to_node(pos));
            pos--;
            empty = TRUE;
            spaces = 0;
          }
          if (type & STR_FUNC_ARRAY) {
            tokadd(p, '\n');
          }
        }
        else if (type & STR_FUNC_REGEXP) {
          tokadd(p, '\\');
          tokadd(p, c);
        }
        else if (c == 'u' && peek(p, '{')) {
          /* \u{xxxx xxxx xxxx} form */
          nextc(p);
          while (1) {
            do c = nextc(p); while (ISSPACE(c));
            if (c == '}') break;
            pushback(p, c);
            c = read_escape_unicode(p, 8);
            if (c < 0) break;
            tokadd(p, -c);
          }
          if (hinfo)
            hinfo->line_head = FALSE;
        }
        else {
          pushback(p, c);
          tokadd(p, read_escape(p));
          if (hinfo)
            hinfo->line_head = FALSE;
        }
      }
      else {
        if (c != beg && c != end) {
          if (c == '\n') {
            p->lineno++;
            p->column = 0;
          }
          if (!(c == '\\' || ((type & STR_FUNC_ARRAY) && ISSPACE(c)))) {
            tokadd(p, '\\');
          }
        }
        tokadd(p, c);
      }
      continue;
    }
    else if ((c == '#') && (type & STR_FUNC_EXPAND)) {
      c = nextc(p);
      if (c == '{') {
        tokfix(p);
        p->lstate = EXPR_BEG;
        p->cmd_start = TRUE;
        pylval.nd = new_str_tok(p);
        if (hinfo) {
          if (unindent && head) {
            nspaces = push(nspaces, int_to_node(spaces));
            heredoc_push_indented(p, hinfo, pylval.nd, escaped, nspaces, FALSE);
          }
          hinfo->line_head = FALSE;
          return tHD_STRING_PART;
        }
        return tSTRING_PART;
      }
      tokadd(p, '#');
      pushback(p, c);
      continue;
    }
    if ((type & STR_FUNC_ARRAY) && ISSPACE(c)) {
      if (toklen(p) == 0) {
        do {
          if (c == '\n') {
            p->lineno++;
            p->column = 0;
            heredoc_treat_nextline(p);
            if (p->parsing_heredoc != NULL) {
              return tHD_LITERAL_DELIM;
            }
          }
          c = nextc(p);
        } while (ISSPACE(c));
        pushback(p, c);
        return tLITERAL_DELIM;
      }
      else {
        pushback(p, c);
        tokfix(p);
        pylval.nd = new_str_tok(p);
        return tSTRING_MID;
      }
    }
    if (c == '\n') {
      p->lineno++;
      p->column = 0;
    }
    tokadd(p, c);
  }

  tokfix(p);
  p->lstate = EXPR_END;
  end_strterm(p);

  if (type & STR_FUNC_XQUOTE) {
    pylval.nd = new_str_tok(p);
    return tXSTRING;
  }

  if (type & STR_FUNC_REGEXP) {
    int f = 0;
    int re_opt;
    int pattern_len = toklen(p);
    char *s = strndup(tok(p), pattern_len);
    char flags[3];
    char *flag = flags;
    char enc = '\0';
    char *encp;
    char *dup;

    newtok(p);
    while (re_opt = nextc(p), re_opt >= 0 && ISALPHA(re_opt)) {
      switch (re_opt) {
      case 'i': f |= 1; break;
      case 'x': f |= 2; break;
      case 'm': f |= 4; break;
      case 'u': f |= 16; break;
      case 'n': f |= 32; break;
      case 'o': break;
      default: tokadd(p, re_opt); break;
      }
    }
    pushback(p, re_opt);
    if (toklen(p)) {
      char msg[128];

      strcpy(msg, "unknown regexp option");
      tokfix(p);
      if (toklen(p) > 1) {
        strcat(msg, "s");
      }
      strcat(msg, " - ");
      strncat(msg, tok(p), sizeof(msg) - strlen(msg) - 1);
      yyerror(NULL, p, msg);
    }
    if (f != 0) {
      if (f & 1) *flag++ = 'i';
      if (f & 2) *flag++ = 'x';
      if (f & 4) *flag++ = 'm';
      if (f & 16) enc = 'u';
      if (f & 32) enc = 'n';
    }
    if (flag > flags) {
      dup = strndup(flags, (size_t)(flag - flags));
    }
    else {
      dup = NULL;
    }
    if (enc) {
      encp = strndup(&enc, 1);
    }
    else {
      encp = NULL;
    }
    pylval.nd = cons(cons(int_to_node(pattern_len), (node*)s), cons((node*)dup, (node*)encp));

    return tREGEXP;
  }
  pylval.nd = new_str_tok(p);

  return tSTRING;
}

static int
number_literal_suffix(parser_state *p)
{
  int c, result = 0;
  node *list = 0;
  int column = p->column;
  int mask = NUM_SUFFIX_R|NUM_SUFFIX_I;

  while ((c = nextc(p)) != -1) {
    list = push(list, int_to_node(c));

    if ((mask & NUM_SUFFIX_I) && c == 'i') {
      result |= (mask & NUM_SUFFIX_I);
      mask &= ~NUM_SUFFIX_I;
      /* r after i, rational of complex is disallowed */
      mask &= ~NUM_SUFFIX_R;
      continue;
    }
    if ((mask & NUM_SUFFIX_R) && c == 'r') {
      result |= (mask & NUM_SUFFIX_R);
      mask &= ~NUM_SUFFIX_R;
      continue;
    }
    if (!ISASCII(c) || ISALPHA(c) || c == '_') {
      p->column = column;
      if (p->pb) {
        p->pb = append(list, p->pb);
      }
      else {
        p->pb = list;
      }
      return 0;
    }
    pushback(p, c);
    break;
  }
  return result;
}

static int
heredoc_identifier(parser_state *p)
{
  int c;
  int type = str_heredoc;
  mrb_bool indent = FALSE;
  mrb_bool squiggly = FALSE;
  mrb_bool quote = FALSE;
  node *newnode;
  parser_heredoc_info *info;

  c = nextc(p);
  if (ISSPACE(c) || c == '=') {
    pushback(p, c);
    return 0;
  }
  if (c == '-' || c == '~') {
    if (c == '-')
      indent = TRUE;
    if (c == '~')
      squiggly = TRUE;
    c = nextc(p);
  }
  if (c == '\'' || c == '"') {
    int term = c;
    if (c == '\'')
      quote = TRUE;
    newtok(p);
    while ((c = nextc(p)) >= 0 && c != term) {
      if (c == '\n') {
        c = -1;
        break;
      }
      tokadd(p, c);
    }
    if (c < 0) {
      yyerror(NULL, p, "unterminated here document identifier");
      return 0;
    }
  }
  else {
    if (c < 0) {
      return 0;                 /* missing here document identifier */
    }
    if (! identchar(c)) {
      pushback(p, c);
      if (indent) pushback(p, '-');
      if (squiggly) pushback(p, '~');
      return 0;
    }
    newtok(p);
    do {
      tokadd(p, c);
    } while ((c = nextc(p)) >= 0 && identchar(c));
    pushback(p, c);
  }
  tokfix(p);
  newnode = new_heredoc(p, &info);
  info->term = strndup(tok(p), toklen(p));
  info->term_len = toklen(p);
  if (! quote)
    type |= STR_FUNC_EXPAND;
  info->type = (string_type)type;
  info->allow_indent = indent || squiggly;
  info->remove_indent = squiggly;
  info->indent = ~0U;
  info->indented = NULL;
  info->line_head = TRUE;
  info->doc = NULL;
  p->heredocs_from_nextline = push(p->heredocs_from_nextline, newnode);
  p->lstate = EXPR_END;

  pylval.nd = newnode;
  return tHEREDOC_BEG;
}

static int
arg_ambiguous(parser_state *p)
{
  yywarning(p, "ambiguous first argument; put parentheses or even spaces");
  return 1;
}

#include "lex.def"

static int
parser_yylex(parser_state *p)
{
  int32_t c;
  int nlines = 1;
  int space_seen = 0;
  int cmd_state;
  enum mrb_lex_state_enum last_state;
  int token_column;

  if (p->lex_strterm) {
    if (is_strterm_type(p, STR_FUNC_HEREDOC)) {
      if (p->parsing_heredoc != NULL)
        return parse_string(p);
    }
    else
      return parse_string(p);
  }
  cmd_state = p->cmd_start;
  p->cmd_start = FALSE;
  retry:
  last_state = p->lstate;
  switch (c = nextc(p)) {
  case '\004':  /* ^D */
  case '\032':  /* ^Z */
  case '\0':    /* NUL */
  case -1:      /* end of script. */
    if (p->heredocs_from_nextline)
      goto maybe_heredoc;
    return 0;

  /* white spaces */
  case ' ': case '\t': case '\f': case '\r':
  case '\13':   /* '\v' */
    space_seen = 1;
    goto retry;

  case '#':     /* it's a comment */
    skip(p, '\n');
    /* fall through */
  case -2:      /* end of a file */
  case '\n':
  maybe_heredoc:
    heredoc_treat_nextline(p);
    p->column = 0;
    switch (p->lstate) {
    case EXPR_BEG:
    case EXPR_FNAME:
    case EXPR_DOT:
    case EXPR_CLASS:
    case EXPR_VALUE:
      p->lineno++;
      if (p->parsing_heredoc != NULL) {
        if (p->lex_strterm) {
          return parse_string(p);
        }
      }
      goto retry;
    default:
      break;
    }
    if (p->parsing_heredoc != NULL) {
      pylval.num = nlines;
      return '\n';
    }
    while ((c = nextc(p))) {
      switch (c) {
      case ' ': case '\t': case '\f': case '\r':
      case '\13': /* '\v' */
        space_seen = 1;
        break;
      case '#': /* comment as a whitespace */
        skip(p, '\n');
        nlines++;
        break;
      case '.':
        if (!peek(p, '.')) {
          pushback(p, '.');
          p->lineno+=nlines; nlines=1;
          goto retry;
        }
        pushback(p, c);
        goto normal_newline;
      case '&':
        if (peek(p, '.')) {
          pushback(p, '&');
          p->lineno+=nlines; nlines=1;
          goto retry;
        }
        pushback(p, c);
        goto normal_newline;
      case -1:                  /* EOF */
      case -2:                  /* end of a file */
        goto normal_newline;
      default:
        pushback(p, c);
        goto normal_newline;
      }
    }
  normal_newline:
    p->cmd_start = TRUE;
    p->lstate = EXPR_BEG;
    pylval.num = nlines;
    return '\n';

  case '*':
    if ((c = nextc(p)) == '*') {
      if ((c = nextc(p)) == '=') {
        pylval.id = intern_op(pow);
        p->lstate = EXPR_BEG;
        return tOP_ASGN;
      }
      pushback(p, c);
      if (IS_SPCARG(c)) {
        yywarning(p, "'**' interpreted as argument prefix");
        c = tDSTAR;
      }
      else if (IS_BEG()) {
        c = tDSTAR;
      }
      else {
        c = tPOW; /* "**", "argument prefix" */
      }
    }
    else {
      if (c == '=') {
        pylval.id = intern_op(mul);
        p->lstate = EXPR_BEG;
        return tOP_ASGN;
      }
      pushback(p, c);
      if (IS_SPCARG(c)) {
        yywarning(p, "'*' interpreted as argument prefix");
        c = tSTAR;
      }
      else if (IS_BEG()) {
        c = tSTAR;
      }
      else {
        c = '*';
      }
    }
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
    }
    else {
      p->lstate = EXPR_BEG;
    }
    return c;

  case '!':
    c = nextc(p);
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
      if (c == '@') {
        return '!';
      }
    }
    else {
      p->lstate = EXPR_BEG;
    }
    if (c == '=') {
      return tNEQ;
    }
    if (c == '~') {
      return tNMATCH;
    }
    pushback(p, c);
    return '!';

  case '=':
    if (p->column == 1) {
      static const char begin[] = "begin";
      static const char end[] = "\n=end";
      if (peeks(p, begin)) {
        c = peekc_n(p, sizeof(begin)-1);
        if (c < 0 || ISSPACE(c)) {
          do {
            if (!skips(p, end)) {
              yyerror(NULL, p, "embedded document meets end of file");
              return 0;
            }
            c = nextc(p);
          } while (!(c < 0 || ISSPACE(c)));
          if (c != '\n') skip(p, '\n');
          p->lineno+=nlines; nlines=1;
          p->column = 0;
          goto retry;
        }
      }
    }
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
    }
    else {
      p->lstate = EXPR_BEG;
    }
    if ((c = nextc(p)) == '=') {
      if ((c = nextc(p)) == '=') {
        return tEQQ;
      }
      pushback(p, c);
      return tEQ;
    }
    if (c == '~') {
      return tMATCH;
    }
    else if (c == '>') {
      return tASSOC;
    }
    pushback(p, c);
    return '=';

  case '<':
    c = nextc(p);
    if (c == '<' &&
        p->lstate != EXPR_DOT &&
        p->lstate != EXPR_CLASS &&
        !IS_END() &&
        (!IS_ARG() || space_seen)) {
      int token = heredoc_identifier(p);
      if (token)
        return token;
    }
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
    }
    else {
      p->lstate = EXPR_BEG;
      if (p->lstate == EXPR_CLASS) {
        p->cmd_start = TRUE;
      }
    }
    if (c == '=') {
      if ((c = nextc(p)) == '>') {
        return tCMP;
      }
      pushback(p, c);
      return tLEQ;
    }
    if (c == '<') {
      if ((c = nextc(p)) == '=') {
        pylval.id = intern_op(lshift);
        p->lstate = EXPR_BEG;
        return tOP_ASGN;
      }
      pushback(p, c);
      return tLSHFT;
    }
    pushback(p, c);
    return '<';

  case '>':
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
    }
    else {
      p->lstate = EXPR_BEG;
    }
    if ((c = nextc(p)) == '=') {
      return tGEQ;
    }
    if (c == '>') {
      if ((c = nextc(p)) == '=') {
        pylval.id = intern_op(rshift);
        p->lstate = EXPR_BEG;
        return tOP_ASGN;
      }
      pushback(p, c);
      return tRSHFT;
    }
    pushback(p, c);
    return '>';

  case '"':
    p->lex_strterm = new_strterm(p, str_dquote, '"', 0);
    return tSTRING_BEG;

  case '\'':
    p->lex_strterm = new_strterm(p, str_squote, '\'', 0);
    return parse_string(p);

  case '`':
    if (p->lstate == EXPR_FNAME) {
      p->lstate = EXPR_ENDFN;
      return '`';
    }
    if (p->lstate == EXPR_DOT) {
      if (cmd_state)
        p->lstate = EXPR_CMDARG;
      else
        p->lstate = EXPR_ARG;
      return '`';
    }
    p->lex_strterm = new_strterm(p, str_xquote, '`', 0);
    return tXSTRING_BEG;

  case '?':
    if (IS_END()) {
      p->lstate = EXPR_VALUE;
      return '?';
    }
    c = nextc(p);
    if (c < 0) {
      yyerror(NULL, p, "incomplete character syntax");
      return 0;
    }
    if (ISSPACE(c)) {
      if (!IS_ARG()) {
        int c2;
        switch (c) {
        case ' ':
          c2 = 's';
          break;
        case '\n':
          c2 = 'n';
          break;
        case '\t':
          c2 = 't';
          break;
        case '\v':
          c2 = 'v';
          break;
        case '\r':
          c2 = 'r';
          break;
        case '\f':
          c2 = 'f';
          break;
        default:
          c2 = 0;
          break;
        }
        if (c2) {
          char buf[256];
          char cc[] = { (char)c2, '\0' };

          strcpy(buf, "invalid character syntax; use ?\\");
          strncat(buf, cc, 2);
          yyerror(NULL, p, buf);
        }
      }
      ternary:
      pushback(p, c);
      p->lstate = EXPR_VALUE;
      return '?';
    }
    newtok(p);
    /* need support UTF-8 if configured */
    if ((ISALNUM(c) || c == '_')) {
      int c2 = nextc(p);
      pushback(p, c2);
      if ((ISALNUM(c2) || c2 == '_')) {
        goto ternary;
      }
    }
    if (c == '\\') {
      c = read_escape(p);
      tokadd(p, c);
    }
    else {
      tokadd(p, c);
    }
    tokfix(p);
    pylval.nd = new_str_tok(p);
    p->lstate = EXPR_END;
    return tCHAR;

  case '&':
    if ((c = nextc(p)) == '&') {
      p->lstate = EXPR_BEG;
      if ((c = nextc(p)) == '=') {
        pylval.id = intern_op(andand);
        p->lstate = EXPR_BEG;
        return tOP_ASGN;
      }
      pushback(p, c);
      return tANDOP;
    }
    else if (c == '.') {
      p->lstate = EXPR_DOT;
      return tANDDOT;
    }
    else if (c == '=') {
      pylval.id = intern_op(and);
      p->lstate = EXPR_BEG;
      return tOP_ASGN;
    }
    pushback(p, c);
    if (IS_SPCARG(c)) {
      yywarning(p, "'&' interpreted as argument prefix");
      c = tAMPER;
    }
    else if (IS_BEG()) {
      c = tAMPER;
    }
    else {
      c = '&';
    }
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
    }
    else {
      p->lstate = EXPR_BEG;
    }
    return c;

  case '|':
    if ((c = nextc(p)) == '|') {
      p->lstate = EXPR_BEG;
      if ((c = nextc(p)) == '=') {
        pylval.id = intern_op(oror);
        p->lstate = EXPR_BEG;
        return tOP_ASGN;
      }
      pushback(p, c);
      return tOROP;
    }
    if (c == '=') {
      pylval.id = intern_op(or);
      p->lstate = EXPR_BEG;
      return tOP_ASGN;
    }
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
    }
    else {
      p->lstate = EXPR_BEG;
    }
    pushback(p, c);
    return '|';

  case '+':
    c = nextc(p);
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
      if (c == '@') {
        return tUPLUS;
      }
      pushback(p, c);
      return '+';
    }
    if (c == '=') {
      pylval.id = intern_op(add);
      p->lstate = EXPR_BEG;
      return tOP_ASGN;
    }
    if (IS_BEG() || (IS_SPCARG(c) && arg_ambiguous(p))) {
      p->lstate = EXPR_BEG;
      pushback(p, c);
      if (c >= 0 && ISDIGIT(c)) {
        c = '+';
        goto start_num;
      }
      return tUPLUS;
    }
    p->lstate = EXPR_BEG;
    pushback(p, c);
    return '+';

  case '-':
    c = nextc(p);
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
      if (c == '@') {
        return tUMINUS;
      }
      pushback(p, c);
      return '-';
    }
    if (c == '=') {
      pylval.id = intern_op(sub);
      p->lstate = EXPR_BEG;
      return tOP_ASGN;
    }
    if (c == '>') {
      p->lstate = EXPR_ENDFN;
      return tLAMBDA;
    }
    if (IS_BEG() || (IS_SPCARG(c) && arg_ambiguous(p))) {
      p->lstate = EXPR_BEG;
      pushback(p, c);
      if (c >= 0 && ISDIGIT(c)) {
        return tUMINUS_NUM;
      }
      return tUMINUS;
    }
    p->lstate = EXPR_BEG;
    pushback(p, c);
    return '-';

  case '.':
    {
      int is_beg = IS_BEG();
      p->lstate = EXPR_MID;
      if ((c = nextc(p)) == '.') {
        if ((c = nextc(p)) == '.') {
          return is_beg ? tBDOT3 : tDOT3;
        }
        pushback(p, c);
        return is_beg ? tBDOT2 : tDOT2;
      }
      pushback(p, c);
      p->lstate = EXPR_BEG;
      if (c >= 0 && ISDIGIT(c)) {
        yyerror(NULL, p, "no .<digit> floating literal anymore; put 0 before dot");
      }
      p->lstate = EXPR_DOT;
      return '.';
    }

    start_num:
  case '0': case '1': case '2': case '3': case '4':
  case '5': case '6': case '7': case '8': case '9':
  {
    int is_float, seen_point, seen_e, nondigit;
    int suffix = 0;

    is_float = seen_point = seen_e = nondigit = 0;
    p->lstate = EXPR_END;
    newtok(p);
    if (c == '-') {
      tokadd(p, c);
      c = nextc(p);
    }
    else if (c == '+') {
      c = nextc(p);
    }
    if (c == '0') {
#define no_digits() do {yyerror(NULL, p,"numeric literal without digits"); return 0;} while (0)
      int start = toklen(p);
      c = nextc(p);
      if (c == 'x' || c == 'X') {
        /* hexadecimal */
        c = nextc(p);
        if (c >= 0 && ISXDIGIT(c)) {
          do {
            if (c == '_') {
              if (nondigit) break;
              nondigit = c;
              continue;
            }
            if (!ISXDIGIT(c)) break;
            nondigit = 0;
            tokadd(p, tolower(c));
          } while ((c = nextc(p)) >= 0);
        }
        pushback(p, c);
        tokfix(p);
        if (toklen(p) == start) {
          no_digits();
        }
        else if (nondigit) goto trailing_uc;
        suffix = number_literal_suffix(p);
        pylval.nd = new_int(p, tok(p), 16, suffix);
        return tINTEGER;
      }
      if (c == 'b' || c == 'B') {
        /* binary */
        c = nextc(p);
        if (c == '0' || c == '1') {
          do {
            if (c == '_') {
              if (nondigit) break;
              nondigit = c;
              continue;
            }
            if (c != '0' && c != '1') break;
            nondigit = 0;
            tokadd(p, c);
          } while ((c = nextc(p)) >= 0);
        }
        pushback(p, c);
        tokfix(p);
        if (toklen(p) == start) {
          no_digits();
        }
        else if (nondigit) goto trailing_uc;
        suffix = number_literal_suffix(p);
        pylval.nd = new_int(p, tok(p), 2, suffix);
        return tINTEGER;
      }
      if (c == 'd' || c == 'D') {
        /* decimal */
        c = nextc(p);
        if (c >= 0 && ISDIGIT(c)) {
          do {
            if (c == '_') {
              if (nondigit) break;
              nondigit = c;
              continue;
            }
            if (!ISDIGIT(c)) break;
            nondigit = 0;
            tokadd(p, c);
          } while ((c = nextc(p)) >= 0);
        }
        pushback(p, c);
        tokfix(p);
        if (toklen(p) == start) {
          no_digits();
        }
        else if (nondigit) goto trailing_uc;
        suffix = number_literal_suffix(p);
        pylval.nd = new_int(p, tok(p), 10, suffix);
        return tINTEGER;
      }
      if (c == '_') {
        /* 0_0 */
        goto octal_number;
      }
      if (c == 'o' || c == 'O') {
        /* prefixed octal */
        c = nextc(p);
        if (c < 0 || c == '_' || !ISDIGIT(c)) {
          no_digits();
        }
      }
      if (c >= '0' && c <= '7') {
        /* octal */
        octal_number:
        do {
          if (c == '_') {
            if (nondigit) break;
            nondigit = c;
            continue;
          }
          if (c < '0' || c > '9') break;
          if (c > '7') goto invalid_octal;
          nondigit = 0;
          tokadd(p, c);
        } while ((c = nextc(p)) >= 0);

        if (toklen(p) > start) {
          pushback(p, c);
          tokfix(p);
          if (nondigit) goto trailing_uc;
          suffix = number_literal_suffix(p);
          pylval.nd = new_int(p, tok(p), 8, suffix);
          return tINTEGER;
        }
        if (nondigit) {
          pushback(p, c);
          goto trailing_uc;
        }
      }
      if (c > '7' && c <= '9') {
        invalid_octal:
        yyerror(NULL, p, "Invalid octal digit");
      }
      else if (c == '.' || c == 'e' || c == 'E') {
        tokadd(p, '0');
      }
      else {
        pushback(p, c);
        suffix = number_literal_suffix(p);
        pylval.nd = new_int(p, "0", 10, suffix);
        return tINTEGER;
      }
    }

    for (;;) {
      switch (c) {
      case '0': case '1': case '2': case '3': case '4':
      case '5': case '6': case '7': case '8': case '9':
        nondigit = 0;
        tokadd(p, c);
        break;

      case '.':
        if (nondigit) goto trailing_uc;
        if (seen_point || seen_e) {
          goto decode_num;
        }
        else {
          int c0 = nextc(p);
          if (c0 < 0 || !ISDIGIT(c0)) {
            pushback(p, c0);
            goto decode_num;
          }
          c = c0;
        }
        tokadd(p, '.');
        tokadd(p, c);
        is_float++;
        seen_point++;
        nondigit = 0;
        break;

      case 'e':
      case 'E':
        if (nondigit) {
          pushback(p, c);
          c = nondigit;
          goto decode_num;
        }
        if (seen_e) {
          goto decode_num;
        }
        tokadd(p, c);
        seen_e++;
        is_float++;
        nondigit = c;
        c = nextc(p);
        if (c != '-' && c != '+') continue;
        tokadd(p, c);
        nondigit = c;
        break;

      case '_':       /* '_' in number just ignored */
        if (nondigit) goto decode_num;
        nondigit = c;
        break;

      default:
        goto decode_num;
      }
      c = nextc(p);
    }

    decode_num:
    pushback(p, c);
    if (nondigit) {
      trailing_uc:
      yyerror_c(p, "trailing non digit in number: ", (char)nondigit);
    }
    tokfix(p);
    if (is_float) {
#ifdef MRB_NO_FLOAT
      yywarning_s(p, "floating-point numbers are not supported", tok(p));
      pylval.nd = new_int(p, "0", 10, 0);
      return tINTEGER;
#else
      double d;

      if (!mrb_read_float(tok(p), NULL, &d)) {
        yywarning_s(p, "corrupted float value", tok(p));
      }
      suffix = number_literal_suffix(p);
      if (seen_e && (suffix & NUM_SUFFIX_R)) {
        pushback(p, 'r');
        suffix &= ~NUM_SUFFIX_R;
      }
      pylval.nd = new_float(p, tok(p), suffix);
      return tFLOAT;
#endif
    }
    suffix = number_literal_suffix(p);
    pylval.nd = new_int(p, tok(p), 10, suffix);
    return tINTEGER;
  }

  case ')':
  case ']':
    p->paren_nest--;
    /* fall through */
  case '}':
    COND_LEXPOP();
    CMDARG_LEXPOP();
    if (c == ')')
      p->lstate = EXPR_ENDFN;
    else
      p->lstate = EXPR_END;
    return c;

  case ':':
    c = nextc(p);
    if (c == ':') {
      if (IS_BEG() || p->lstate == EXPR_CLASS || IS_SPCARG(-1)) {
        p->lstate = EXPR_BEG;
        return tCOLON3;
      }
      p->lstate = EXPR_DOT;
      return tCOLON2;
    }
    if (!space_seen && IS_END()) {
      pushback(p, c);
      p->lstate = EXPR_BEG;
      return tLABEL_TAG;
    }
    if (IS_END() || ISSPACE(c) || c == '#') {
      pushback(p, c);
      p->lstate = EXPR_BEG;
      return ':';
    }
    pushback(p, c);
    p->lstate = EXPR_FNAME;
    return tSYMBEG;

  case '/':
    if (IS_BEG()) {
      p->lex_strterm = new_strterm(p, str_regexp, '/', 0);
      return tREGEXP_BEG;
    }
    if ((c = nextc(p)) == '=') {
      pylval.id = intern_op(div);
      p->lstate = EXPR_BEG;
      return tOP_ASGN;
    }
    pushback(p, c);
    if (IS_SPCARG(c)) {
      p->lex_strterm = new_strterm(p, str_regexp, '/', 0);
      return tREGEXP_BEG;
    }
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
    }
    else {
      p->lstate = EXPR_BEG;
    }
    return '/';

  case '^':
    if ((c = nextc(p)) == '=') {
      pylval.id = intern_op(xor);
      p->lstate = EXPR_BEG;
      return tOP_ASGN;
    }
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
    }
    else {
      p->lstate = EXPR_BEG;
    }
    pushback(p, c);
    return '^';

  case ';':
    p->lstate = EXPR_BEG;
    return ';';

  case ',':
    p->lstate = EXPR_BEG;
    return ',';

  case '~':
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      if ((c = nextc(p)) != '@') {
        pushback(p, c);
      }
      p->lstate = EXPR_ARG;
    }
    else {
      p->lstate = EXPR_BEG;
    }
    return '~';

  case '(':
    if (IS_BEG()) {
      c = tLPAREN;
    }
    else if (IS_SPCARG(-1)) {
      c = tLPAREN_ARG;
    }
    else if (p->lstate == EXPR_END && space_seen) {
      c = tLPAREN_ARG;
    }
    p->paren_nest++;
    COND_PUSH(0);
    CMDARG_PUSH(0);
    p->lstate = EXPR_BEG;
    return c;

  case '[':
    p->paren_nest++;
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
      p->paren_nest--;
      if ((c = nextc(p)) == ']') {
        if ((c = nextc(p)) == '=') {
          return tASET;
        }
        pushback(p, c);
        return tAREF;
      }
      pushback(p, c);
      return '[';
    }
    else if (IS_BEG()) {
      c = tLBRACK;
    }
    else if (IS_ARG() && space_seen) {
      c = tLBRACK;
    }
    p->lstate = EXPR_BEG;
    COND_PUSH(0);
    CMDARG_PUSH(0);
    return c;

  case '{':
    if (p->lpar_beg && p->lpar_beg == p->paren_nest) {
      p->lstate = EXPR_BEG;
      p->lpar_beg = 0;
      p->paren_nest--;
      COND_PUSH(0);
      CMDARG_PUSH(0);
      return tLAMBEG;
    }
    if (IS_ARG() || p->lstate == EXPR_END || p->lstate == EXPR_ENDFN)
      c = '{';          /* block (primary) */
    else if (p->lstate == EXPR_ENDARG)
      c = tLBRACE_ARG;  /* block (expr) */
    else
      c = tLBRACE;      /* hash */
    COND_PUSH(0);
    CMDARG_PUSH(0);
    p->lstate = EXPR_BEG;
    return c;

  case '\\':
    c = nextc(p);
    if (c == '\n') {
      p->lineno+=nlines; nlines=1;
      p->column = 0;
      space_seen = 1;
      goto retry; /* skip \\n */
    }
    pushback(p, c);
    return '\\';

  case '%':
    if (IS_BEG()) {
      int term;
      int paren;

      c = nextc(p);
      quotation:
      if (c < 0 || !ISALNUM(c)) {
        term = c;
        c = 'Q';
      }
      else {
        term = nextc(p);
        if (ISALNUM(term)) {
          yyerror(NULL, p, "unknown type of %string");
          return 0;
        }
      }
      if (c < 0 || term < 0) {
        yyerror(NULL, p, "unterminated quoted string meets end of file");
        return 0;
      }
      paren = term;
      if (term == '(') term = ')';
      else if (term == '[') term = ']';
      else if (term == '{') term = '}';
      else if (term == '<') term = '>';
      else paren = 0;

      switch (c) {
      case 'Q':
        p->lex_strterm = new_strterm(p, str_dquote, term, paren);
        return tSTRING_BEG;

      case 'q':
        p->lex_strterm = new_strterm(p, str_squote, term, paren);
        return parse_string(p);

      case 'W':
        p->lex_strterm = new_strterm(p, str_dword, term, paren);
        return tWORDS_BEG;

      case 'w':
        p->lex_strterm = new_strterm(p, str_sword, term, paren);
        return tWORDS_BEG;

      case 'x':
        p->lex_strterm = new_strterm(p, str_xquote, term, paren);
        return tXSTRING_BEG;

      case 'r':
        p->lex_strterm = new_strterm(p, str_regexp, term, paren);
        return tREGEXP_BEG;

      case 's':
        p->lex_strterm = new_strterm(p, str_ssym, term, paren);
        return tSYMBEG;

      case 'I':
        p->lex_strterm = new_strterm(p, str_dsymbols, term, paren);
        return tSYMBOLS_BEG;

      case 'i':
        p->lex_strterm = new_strterm(p, str_ssymbols, term, paren);
        return tSYMBOLS_BEG;

      default:
        yyerror(NULL, p, "unknown type of %string");
        return 0;
      }
    }
    if ((c = nextc(p)) == '=') {
      pylval.id = intern_op(mod);
      p->lstate = EXPR_BEG;
      return tOP_ASGN;
    }
    if (IS_SPCARG(c)) {
      goto quotation;
    }
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
    }
    else {
      p->lstate = EXPR_BEG;
    }
    pushback(p, c);
    return '%';

  case '$':
    p->lstate = EXPR_END;
    token_column = newtok(p);
    c = nextc(p);
    if (c < 0) {
      yyerror(NULL, p, "incomplete global variable syntax");
      return 0;
    }
    switch (c) {
    case '_':     /* $_: last read line string */
      c = nextc(p);
      if (c >= 0 && identchar(c)) { /* if there is more after _ it is a variable */
        tokadd(p, '$');
        tokadd(p, c);
        break;
      }
      pushback(p, c);
      c = '_';
      /* fall through */
    case '~':     /* $~: match-data */
    case '*':     /* $*: argv */
    case '$':     /* $$: pid */
    case '?':     /* $?: last status */
    case '!':     /* $!: error string */
    case '@':     /* $@: error position */
    case '/':     /* $/: input record separator */
    case '\\':    /* $\: output record separator */
    case ';':     /* $;: field separator */
    case ',':     /* $,: output field separator */
    case '.':     /* $.: last read line number */
    case '=':     /* $=: ignorecase */
    case ':':     /* $:: load path */
    case '<':     /* $<: reading filename */
    case '>':     /* $>: default output handle */
    case '\"':    /* $": already loaded files */
      tokadd(p, '$');
      tokadd(p, c);
      tokfix(p);
      pylval.id = intern(tok(p), toklen(p));
      return tGVAR;

    case '-':
      tokadd(p, '$');
      tokadd(p, c);
      c = nextc(p);
      pushback(p, c);
      gvar:
      tokfix(p);
      pylval.id = intern(tok(p), toklen(p));
      return tGVAR;

    case '&':     /* $&: last match */
    case '`':     /* $`: string before last match */
    case '\'':    /* $': string after last match */
    case '+':     /* $+: string matches last pattern */
      if (last_state == EXPR_FNAME) {
        tokadd(p, '$');
        tokadd(p, c);
        goto gvar;
      }
      pylval.nd = new_back_ref(p, c);
      return tBACK_REF;

    case '1': case '2': case '3':
    case '4': case '5': case '6':
    case '7': case '8': case '9':
      do {
        tokadd(p, c);
        c = nextc(p);
      } while (c >= 0 && ISDIGIT(c));
      pushback(p, c);
      if (last_state == EXPR_FNAME) goto gvar;
      tokfix(p);
      {
        mrb_int n;
        if (!mrb_read_int(tok(p), NULL, NULL, &n)) {
          yywarning(p, "capture group index too big; always nil");
          return keyword_nil;
        }
        pylval.nd = new_nth_ref(p, (int)n);
      }
      return tNTH_REF;

    default:
      if (!identchar(c)) {
        pushback(p,  c);
        return '$';
      }
      /* fall through */
    case '0':
      tokadd(p, '$');
    }
    break;

    case '@':
      c = nextc(p);
      token_column = newtok(p);
      tokadd(p, '@');
      if (c == '@') {
        tokadd(p, '@');
        c = nextc(p);
      }
      if (c < 0) {
        if (p->tidx == 1) {
          yyerror(NULL, p, "incomplete instance variable syntax");
        }
        else {
          yyerror(NULL, p, "incomplete class variable syntax");
        }
        return 0;
      }
      else if (ISDIGIT(c)) {
        if (p->tidx == 1) {
          yyerror_c(p, "wrong instance variable name: @", c);
        }
        else {
          yyerror_c(p, "wrong class variable name: @@", c);
        }
        return 0;
      }
      if (!identchar(c)) {
        pushback(p, c);
        return '@';
      }
      break;

    case '_':
      token_column = newtok(p);
      break;

    default:
      if (!identchar(c)) {
        char buf[36];
        const char s[] = "Invalid char in expression: 0x";
        const char hexdigits[] = "0123456789ABCDEF";

        strcpy(buf, s);
        buf[sizeof(s)-1] = hexdigits[(c & 0xf0) >> 4];
        buf[sizeof(s)]   = hexdigits[(c & 0x0f)];
        buf[sizeof(s)+1] = 0;
        yyerror(NULL, p, buf);
        goto retry;
      }

      token_column = newtok(p);
      break;
  }

  do {
    tokadd(p, c);
    c = nextc(p);
    if (c < 0) break;
  } while (identchar(c));
  if (token_column == 0 && toklen(p) == 7 && (c < 0 || c == '\n') &&
      strncmp(tok(p), "__END__", toklen(p)) == 0)
    return -1;

  switch (tok(p)[0]) {
  case '@': case '$':
    pushback(p, c);
    break;
  default:
    if ((c == '!' || c == '?') && !peek(p, '=')) {
      tokadd(p, c);
    }
    else {
      pushback(p, c);
    }
  }
  tokfix(p);
  {
    int result = 0;

    switch (tok(p)[0]) {
    case '$':
      p->lstate = EXPR_END;
      result = tGVAR;
      break;
    case '@':
      p->lstate = EXPR_END;
      if (tok(p)[1] == '@')
        result = tCVAR;
      else
        result = tIVAR;
      break;

    case '_':
      if (toklen(p) == 2 && ISDIGIT(tok(p)[1]) && p->nvars) {
        int n = tok(p)[1] - '0';
        int nvar;

        if (n > 0) {
          nvar = node_to_int(p->nvars->car);
          if (nvar != -2) {     /* numbered parameters never appear on toplevel */
            pylval.num = n;
            p->lstate = EXPR_END;
            return tNUMPARAM;
          }
        }
      }
      /* fall through */
    default:
      if (toklast(p) == '!' || toklast(p) == '?') {
        result = tFID;
      }
      else {
        if (p->lstate == EXPR_FNAME) {
          if ((c = nextc(p)) == '=' && !peek(p, '~') && !peek(p, '>') &&
              (!peek(p, '=') || (peek_n(p, '>', 1)))) {
            result = tIDENTIFIER;
            tokadd(p, c);
            tokfix(p);
          }
          else {
            pushback(p, c);
          }
          if ((c = nextc(p)) == '=' && !peek(p, '~') && !peek(p, '>') &&
              (!peek(p, '=') || (peek_n(p, '>', 1)))) {
            result = tIDENTIFIER;
            tokadd(p, c);
            tokfix(p);
          }
          else {
            pushback(p, c);
          }
        }
        if (result == 0 && ISUPPER(tok(p)[0])) {
          result = tCONSTANT;
        }
        else {
          result = tIDENTIFIER;
        }
      }

      if (IS_LABEL_POSSIBLE()) {
        if (IS_LABEL_SUFFIX(0)) {
          p->lstate = EXPR_END;
          tokfix(p);
          pylval.id = intern(tok(p), toklen(p));
          return tIDENTIFIER;
        }
      }
      if (p->lstate != EXPR_DOT) {
        const struct kwtable *kw;

        /* See if it is a reserved word.  */
        kw = mrb_reserved_word(tok(p), toklen(p));
        if (kw) {
          enum mrb_lex_state_enum state = p->lstate;
          pylval.num = p->lineno;
          p->lstate = kw->state;
          if (state == EXPR_FNAME) {
            pylval.id = intern_cstr(kw->name);
            return kw->id[0];
          }
          if (p->lstate == EXPR_BEG) {
            p->cmd_start = TRUE;
          }
          if (kw->id[0] == keyword_do) {
            if (p->lpar_beg && p->lpar_beg == p->paren_nest) {
              p->lpar_beg = 0;
              p->paren_nest--;
              return keyword_do_LAMBDA;
            }
            if (COND_P()) return keyword_do_cond;
            if (CMDARG_P() && state != EXPR_CMDARG)
              return keyword_do_block;
            if (state == EXPR_ENDARG || state == EXPR_BEG)
              return keyword_do_block;
            return keyword_do;
          }
          if (state == EXPR_BEG || state == EXPR_VALUE || state == EXPR_CLASS)
            return kw->id[0];
          else {
            if (kw->id[0] != kw->id[1])
              p->lstate = EXPR_BEG;
            return kw->id[1];
          }
        }
      }

      if (IS_BEG() || p->lstate == EXPR_DOT || IS_ARG()) {
        if (cmd_state) {
          p->lstate = EXPR_CMDARG;
        }
        else {
          p->lstate = EXPR_ARG;
        }
      }
      else if (p->lstate == EXPR_FNAME) {
        p->lstate = EXPR_ENDFN;
      }
      else {
        p->lstate = EXPR_END;
      }
    }
    {
      mrb_sym ident = intern(tok(p), toklen(p));

      pylval.id = ident;
      if (last_state != EXPR_DOT && ISLOWER(tok(p)[0]) && local_var_p(p, ident)) {
        p->lstate = EXPR_END;
      }
    }
    return result;
  }
}

static int
yylex(void *lval, void *lp, parser_state *p)
{
  p->ylval = lval;
  return parser_yylex(p);
}

static void
parser_init_cxt(parser_state *p, mrb_ccontext *cxt)
{
  if (!cxt) return;
  if (cxt->filename) mrb_parser_set_filename(p, cxt->filename);
  if (cxt->lineno) p->lineno = cxt->lineno;
  if (cxt->syms) {
    int i;

    p->locals = cons(0,0);
    for (i=0; i<cxt->slen; i++) {
      local_add_f(p, cxt->syms[i]);
    }
  }
  p->capture_errors = cxt->capture_errors;
  p->no_optimize = cxt->no_optimize;
  p->no_ext_ops = cxt->no_ext_ops;
  p->upper = cxt->upper;
  if (cxt->partial_hook) {
    p->cxt = cxt;
  }
}

static void
parser_update_cxt(parser_state *p, mrb_ccontext *cxt)
{
  node *n, *n0;
  int i = 0;

  if (!cxt) return;
  if (!p->tree) return;
  if (!node_type_p(p->tree, NODE_SCOPE)) return;

  /* Extract locals from variable-sized NODE_SCOPE */
  struct mrb_ast_scope_node *scope = scope_node(p->tree);
  n0 = n = scope->locals;
  while (n) {
    i++;
    n = n->cdr;
  }
  cxt->syms = (mrb_sym*)mrbc_realloc(cxt->syms, i*sizeof(mrb_sym));
  cxt->slen = i;
  for (i=0, n=n0; n; i++,n=n->cdr) {
    cxt->syms[i] = node_to_sym(n->car);
  }
}

static void dump_node(mrb_state *mrb, node *tree, int offset);

MRB_API void
mrb_parser_parse(parser_state *p, mrb_ccontext *c)
{
  struct mrb_jmpbuf buf1;
  struct mrb_jmpbuf *prev = p->mrb->jmp;
  p->mrb->jmp = &buf1;

  MRB_TRY(p->mrb->jmp) {
    int n = 1;

    p->cmd_start = TRUE;
    p->in_def = p->in_single = 0;
    p->nerr = p->nwarn = 0;
    p->lex_strterm = NULL;
    parser_init_cxt(p, c);

    n = yyparse(p);
    if (n != 0 || p->nerr > 0) {
      p->tree = 0;
      p->mrb->jmp = prev;
      return;
    }
    parser_update_cxt(p, c);
    if (c && c->dump_result) {
      dump_node(p->mrb, p->tree, 0);
    }
  }
  MRB_CATCH(p->mrb->jmp) {
    p->nerr++;
    if (p->mrb->exc == NULL) {
      yyerror(NULL, p, "memory allocation error");
      p->nerr++;
      p->tree = 0;
    }
  }
  MRB_END_EXC(p->jmp);
  p->mrb->jmp = prev;
}

MRB_API parser_state*
mrb_parser_new(mrb_state *mrb)
{
  mempool *pool;
  parser_state *p;
  static const parser_state parser_state_zero = { 0 };

  pool = mempool_open();
  if (!pool) return NULL;
  p = (parser_state*)mempool_alloc(pool, sizeof(parser_state));
  if (!p) return NULL;

  *p = parser_state_zero;
  p->mrb = mrb;
  p->pool = pool;

  p->s = p->send = NULL;
#ifndef MRB_NO_STDIO
  p->f = NULL;
#endif

  p->cmd_start = TRUE;
  p->in_def = p->in_single = 0;

  p->capture_errors = FALSE;
  p->lineno = 1;
  p->column = 0;
#if defined(PARSER_TEST) || defined(PARSER_DEBUG)
  yydebug = 1;
#endif
  p->tsiz = MRB_PARSER_TOKBUF_SIZE;
  p->tokbuf = p->buf;

  p->lex_strterm = NULL;

  p->current_filename_index = -1;
  p->filename_table = NULL;
  p->filename_table_length = 0;

  return p;
}

MRB_API void
mrb_parser_free(parser_state *p) {
  if (p->tokbuf != p->buf) {
    mrbc_free(p->tokbuf);
  }
  mempool_close(p->pool);
}

MRB_API mrb_ccontext*
mrb_ccontext_new(mrb_state *mrb)
{
  static const mrb_ccontext cc_zero = { 0 };
  mrb_ccontext *cc = (mrb_ccontext*)mrbc_malloc(sizeof(mrb_ccontext));
  *cc = cc_zero;
  return cc;
}

MRB_API void
mrb_ccontext_free(mrb_state *mrb, mrb_ccontext *cxt)
{
  mrbc_free(cxt->filename);
  mrbc_free(cxt->syms);
  mrbc_free(cxt);
}

MRB_API const char*
mrb_ccontext_filename(mrb_state *mrb, mrb_ccontext *c, const char *s)
{
  if (s) {
    size_t len = strlen(s);
    char *p = (char*)mrbc_malloc(len + 1);

    if (p == NULL) return NULL;
    memcpy(p, s, len + 1);
    if (c->filename) {
      mrbc_free(c->filename);
    }
    c->filename = p;
  }
  return c->filename;
}

MRB_API void
mrb_ccontext_partial_hook(mrb_ccontext *c, int (*func)(struct mrb_parser_state*), void *data)
{
  c->partial_hook = func;
  c->partial_data = data;
}

MRB_API void
mrb_ccontext_cleanup_local_variables(mrb_ccontext *c)
{
  if (c->syms) {
    mrbc_free(c->syms);
    c->syms = NULL;
    c->slen = 0;
  }
  c->keep_lv = FALSE;
}

MRB_API void
mrb_parser_set_filename(struct mrb_parser_state *p, const char *f)
{
  mrb_sym sym;
  uint16_t i;
  mrb_sym* new_table;

  sym = mrb_intern_cstr(p->mrb, f);
  p->filename_sym = sym;
  p->lineno = (p->filename_table_length > 0)? 0 : 1;

  for (i = 0; i < p->filename_table_length; i++) {
    if (p->filename_table[i] == sym) {
      p->current_filename_index = i;
      return;
    }
  }

  if (p->filename_table_length == UINT16_MAX) {
    yyerror(NULL, p, "too many files to compile");
    return;
  }
  p->current_filename_index = p->filename_table_length++;

  new_table = (mrb_sym*)parser_palloc(p, sizeof(mrb_sym) * p->filename_table_length);
  if (p->filename_table) {
    memmove(new_table, p->filename_table, sizeof(mrb_sym) * p->current_filename_index);
  }
  p->filename_table = new_table;
  p->filename_table[p->filename_table_length - 1] = sym;
}

MRB_API mrb_sym
mrb_parser_get_filename(struct mrb_parser_state* p, uint16_t idx) {
  if (idx >= p->filename_table_length) return 0;
  else {
    return p->filename_table[idx];
  }
}

#ifndef MRB_NO_STDIO
static struct mrb_parser_state *
mrb_parse_file_continue(mrb_state *mrb, FILE *f, const void *prebuf, size_t prebufsize, mrb_ccontext *c)
{
  parser_state *p;

  p = mrb_parser_new(mrb);
  if (!p) return NULL;
  if (prebuf) {
    p->s = (const char*)prebuf;
    p->send = (const char*)prebuf + prebufsize;
  }
  else {
    p->s = p->send = NULL;
  }
  p->f = f;

  mrb_parser_parse(p, c);
  return p;
}

MRB_API parser_state*
mrb_parse_file(mrb_state *mrb, FILE *f, mrb_ccontext *c)
{
  return mrb_parse_file_continue(mrb, f, NULL, 0, c);
}
#endif

MRB_API parser_state*
mrb_parse_nstring(mrb_state *mrb, const char *s, size_t len, mrb_ccontext *c)
{
  parser_state *p;

  p = mrb_parser_new(mrb);
  if (!p) return NULL;
  p->s = s;
  p->send = s + len;

  mrb_parser_parse(p, c);
  return p;
}

MRB_API parser_state*
mrb_parse_string(mrb_state *mrb, const char *s, mrb_ccontext *c)
{
  return mrb_parse_nstring(mrb, s, strlen(s), c);
}

MRB_API mrb_value
mrb_load_exec(mrb_state *mrb, struct mrb_parser_state *p, mrb_ccontext *c)
{
  struct RClass *target = mrb->object_class;
  struct RProc *proc;
  mrb_value v;
  mrb_int keep = 0;

  if (!p) {
    return mrb_undef_value();
  }
  if (!p->tree || p->nerr) {
    if (c) c->parser_nerr = p->nerr;
    if (p->capture_errors) {
      char buf[256];

      strcpy(buf, "line ");
      dump_int(p->error_buffer[0].lineno, buf+5);
      strcat(buf, ": ");
      strncat(buf, p->error_buffer[0].message, sizeof(buf) - strlen(buf) - 1);
      mrb->exc = mrb_obj_ptr(mrb_exc_new(mrb, E_SYNTAX_ERROR, buf, strlen(buf)));
      mrb_parser_free(p);
      return mrb_undef_value();
    }
    else {
      if (mrb->exc == NULL) {
        mrb->exc = mrb_obj_ptr(mrb_exc_new_lit(mrb, E_SYNTAX_ERROR, "syntax error"));
      }
      mrb_parser_free(p);
      return mrb_undef_value();
    }
  }
  proc = mrb_generate_code(mrb, p);
  mrb_parser_free(p);
  if (proc == NULL) {
    if (mrb->exc == NULL) {
      mrb->exc = mrb_obj_ptr(mrb_exc_new_lit(mrb, E_SCRIPT_ERROR, "codegen error"));
    }
    return mrb_undef_value();
  }
  if (c) {
    if (c->dump_result) mrb_codedump_all(mrb, proc);
    if (c->no_exec) return mrb_obj_value(proc);
    if (c->target_class) {
      target = c->target_class;
    }
    if (c->keep_lv) {
      keep = c->slen + 1;
    }
    else {
      c->keep_lv = TRUE;
    }
  }
  MRB_PROC_SET_TARGET_CLASS(proc, target);
  if (mrb->c->ci) {
    mrb_vm_ci_target_class_set(mrb->c->ci, target);
  }
  v = mrb_top_run(mrb, proc, mrb_top_self(mrb), keep);
  if (mrb->exc) return mrb_nil_value();
  return v;
}

#ifndef MRB_NO_STDIO
MRB_API mrb_value
mrb_load_file_cxt(mrb_state *mrb, FILE *f, mrb_ccontext *c)
{
  return mrb_load_exec(mrb, mrb_parse_file(mrb, f, c), c);
}

MRB_API mrb_value
mrb_load_file(mrb_state *mrb, FILE *f)
{
  return mrb_load_file_cxt(mrb, f, NULL);
}

#define DETECT_SIZE 64

/*
 * In order to be recognized as a `.mrb` file, the following three points must be satisfied:
 * - File starts with "RITE"
 * - At least `sizeof(struct rite_binary_header)` bytes can be read
 * - `NUL` is included in the first 64 bytes of the file
 */
MRB_API mrb_value
mrb_load_detect_file_cxt(mrb_state *mrb, FILE *fp, mrb_ccontext *c)
{
  union {
    char b[DETECT_SIZE];
    struct rite_binary_header h;
  } leading;
  size_t bufsize;

  if (mrb == NULL || fp == NULL) {
    return mrb_nil_value();
  }

  bufsize = fread(leading.b, sizeof(char), sizeof(leading), fp);
  if (bufsize < sizeof(leading.h) ||
      memcmp(leading.h.binary_ident, RITE_BINARY_IDENT, sizeof(leading.h.binary_ident)) != 0 ||
      memchr(leading.b, '\0', bufsize) == NULL) {
    return mrb_load_exec(mrb, mrb_parse_file_continue(mrb, fp, leading.b, bufsize, c), c);
  }
  else {
    mrb_int binsize;
    uint8_t *bin;
    mrb_value bin_obj = mrb_nil_value(); /* temporary string object */
    mrb_value result;

    binsize = bin_to_uint32(leading.h.binary_size);
    bin_obj = mrb_str_new(mrb, NULL, binsize);
    bin = (uint8_t*)RSTRING_PTR(bin_obj);
    if ((size_t)binsize > bufsize) {
      memcpy(bin, leading.b, bufsize);
      if (fread(bin + bufsize, binsize - bufsize, 1, fp) == 0) {
        binsize = bufsize;
        /* The error is reported by mrb_load_irep_buf_cxt() */
      }
    }

    result = mrb_load_irep_buf_cxt(mrb, bin, binsize, c);
    if (mrb_string_p(bin_obj)) mrb_str_resize(mrb, bin_obj, 0);
    return result;
  }
}
#endif

MRB_API mrb_value
mrb_load_nstring_cxt(mrb_state *mrb, const char *s, size_t len, mrb_ccontext *c)
{
  return mrb_load_exec(mrb, mrb_parse_nstring(mrb, s, len, c), c);
}

MRB_API mrb_value
mrb_load_nstring(mrb_state *mrb, const char *s, size_t len)
{
  return mrb_load_nstring_cxt(mrb, s, len, NULL);
}

MRB_API mrb_value
mrb_load_string_cxt(mrb_state *mrb, const char *s, mrb_ccontext *c)
{
  return mrb_load_nstring_cxt(mrb, s, strlen(s), c);
}

MRB_API mrb_value
mrb_load_string(mrb_state *mrb, const char *s)
{
  return mrb_load_string_cxt(mrb, s, NULL);
}

#ifndef MRB_NO_STDIO

static void
dump_prefix(int offset, uint16_t lineno)
{
  printf("%05d ", lineno);
  while (offset--) {
    putc(' ', stdout);
    putc(' ', stdout);
  }
}

static void
dump_recur(mrb_state *mrb, node *tree, int offset)
{
  while (tree) {
    dump_node(mrb, tree->car, offset);
    tree = tree->cdr;
  }
}

static void
dump_locals(mrb_state *mrb, node *tree, int offset, uint16_t lineno)
{
  if (!tree || (!tree->car && !tree->cdr)) return;

  dump_prefix(offset, lineno);
  printf("locals:\n");
  dump_prefix(offset+1, lineno);
  while (tree) {
    if (tree->car) {
      mrb_sym sym = node_to_sym(tree->car);
      if (sym != 0) {
        const char *name = mrb_sym_name(mrb, sym);
        if (name && strlen(name) > 0 && name[0] != '!' && name[0] != '@' && name[0] != '$') {
          printf(" %s", mrb_sym_dump(mrb, sym));
        }
        else {
          printf(" (invalid symbol: %s)", name ? name : "(null)");
        }
      }
      else {
        printf(" (anonymous)");
      }
    }
    tree = tree->cdr;
  }
  printf("\n");
}

static void
dump_cpath(mrb_state *mrb, node *tree, int offset, uint16_t lineno)
{
  dump_prefix(offset, lineno);
  printf("cpath: ");
  if (!tree) {
    printf("(null)\n");
  }
  else if (node_to_int(tree->car) == 0) {
    printf("(null)\n");
  }
  else if (node_to_int(tree->car) == 1) {
    printf("Object\n");
  }
  else {
    printf("\n");
    dump_node(mrb, tree->car, offset+1);
  }
  dump_prefix(offset, lineno);
  printf("name: %s\n", mrb_sym_dump(mrb, node_to_sym(tree->cdr)));
}

/*
 * This function restores the GC arena on return.
 * For this reason, if a process that further generates an object is
 * performed at the caller, the string pointer returned as the return
 * value may become invalid.
 */
static const char*
str_dump(mrb_state *mrb, const char *str, int len)
{
  int ai = mrb_gc_arena_save(mrb);
  mrb_value s = mrb_str_new(mrb, str, (mrb_int)len);
  s = mrb_str_dump(mrb, s);
  mrb_gc_arena_restore(mrb, ai);
  return RSTRING_PTR(s);
}

static void
dump_str(mrb_state *mrb, node *n, int offset, uint16_t lineno)
{
  while (n) {
    dump_prefix(offset, lineno);
    int len = node_to_int(n->car->car);
    if (len >= 0) {
      printf("str: %s\n", str_dump(mrb, (char*)n->car->cdr, len));
    }
    else {
      printf("interpolation:\n");
      dump_node(mrb, n->car->cdr, offset+1);
    }
    n = n->cdr;
  }
}

static void
dump_args(mrb_state *mrb, struct mrb_ast_args *args, int offset, uint16_t lineno)
{
  if (args->mandatory_args) {
    dump_prefix(offset, lineno);
    printf("mandatory args:\n");
    dump_recur(mrb, args->mandatory_args, offset+1);
  }
  if (args->optional_args) {
    dump_prefix(offset, lineno);
    printf("optional args:\n");
    {
      node *n = args->optional_args;
      while (n) {
        dump_prefix(offset+1, lineno);
        printf("%s=\n", mrb_sym_name(mrb, node_to_sym(n->car->car)));
        dump_node(mrb, n->car->cdr, offset+2);
        n = n->cdr;
      }
    }
  }
  if (args->rest_arg) {
    mrb_sym rest = args->rest_arg;

    dump_prefix(offset, lineno);
    if (rest == MRB_OPSYM(mul))
      printf("rest=*\n");
    else
      printf("rest=*%s\n", mrb_sym_name(mrb, rest));
  }
  if (args->post_mandatory_args) {
    dump_prefix(offset, lineno);
    printf("post mandatory args:\n");
    dump_recur(mrb, args->post_mandatory_args, offset+1);
  }
  if (args->keyword_args) {
    dump_prefix(offset, lineno);
    printf("keyword args:\n");
    {
      node *n = args->keyword_args;
      while (n) {
        dump_prefix(offset+1, lineno);
        printf("%s:\n", mrb_sym_name(mrb, node_to_sym(n->car->car)));
        dump_node(mrb, n->car->cdr, offset+2);
        n = n->cdr;
      }
    }
  }
  if (args->kwrest_arg) {
    mrb_sym rest = args->kwrest_arg;

    dump_prefix(offset, lineno);
    if (rest == MRB_OPSYM(pow))
      printf("kwrest=**\n");
    else
      printf("kwrest=**%s\n", mrb_sym_name(mrb, rest));
  }
  if (args->block_arg) {
    mrb_sym blk = args->block_arg;

    dump_prefix(offset, lineno);
    if (blk == MRB_OPSYM(and))
      printf("blk=&\n");
    else
      printf("blk=&%s\n", mrb_sym_name(mrb, blk));
  }
}

static void
dump_callargs(mrb_state *mrb, node *n, int offset, uint16_t lineno)
{
  if (!n) return;

  struct mrb_ast_callargs *args = (struct mrb_ast_callargs*)n;
  if (args->regular_args) {
    dump_prefix(offset+1, lineno);
    printf("args:\n");
    dump_recur(mrb, args->regular_args, offset+2);
  }
  if (args->keyword_args) {
    dump_prefix(offset+1, lineno);
    printf("kw_args:\n");
    node *kw = args->keyword_args;
    while (kw) {
      dump_prefix(offset+2, lineno);
      printf("key:\n");
      if (node_to_sym(kw->car->car) == MRB_OPSYM(pow)) {
        dump_prefix(offset+3, lineno);
        printf("**:\n");
      }
      else {
        dump_node(mrb, kw->car->car, offset+3);
      }
      dump_prefix(offset+2, lineno);
      printf("value:\n");
      dump_node(mrb, kw->car->cdr, offset+3);
      kw = kw->cdr;
    }
  }
  if (args->block_arg) {
    dump_prefix(offset+1, lineno);
    printf("block:\n");
    dump_node(mrb, args->block_arg, offset+2);
  }
}

#endif

void
dump_node(mrb_state *mrb, node *tree, int offset)
{
#ifndef MRB_NO_STDIO
  enum node_type nodetype;
  uint16_t lineno = 0;

  if (!tree) return;

  /* Extract line number from variable-sized node header */
  if (get_node_type(tree) != NODE_LAST) {
    lineno = ((struct mrb_ast_var_header*)tree)->lineno;
  }

  dump_prefix(offset, lineno);

  /* All nodes are now variable-sized nodes with headers */
  nodetype = get_node_type(tree);

  switch (nodetype) {
  /* Variable-sized node cases */
  case NODE_SCOPE:
    printf("NODE_SCOPE:\n");
    if (scope_node(tree)->locals) {
      dump_locals(mrb, scope_node(tree)->locals, offset+1, lineno);
    }
    if (scope_node(tree)->body) {
      dump_prefix(offset+1, lineno);
      printf("body:\n");
      dump_node(mrb, scope_node(tree)->body, offset+2);
    }
    break;

  case NODE_INT:
    printf("NODE_INT: %d\n", int_node(tree)->value);
    break;

  case NODE_BIGINT:
    printf("NODE_BIGINT: %s (base %d)\n", bigint_node(tree)->string, bigint_node(tree)->base);
    break;

  case NODE_FLOAT:
    printf("NODE_FLOAT: %s\n", float_node(tree)->value);
    break;

  case NODE_STR:
    printf("NODE_STR:\n");
    dump_str(mrb, str_node(tree)->list, offset+1, lineno);
    break;

  case NODE_XSTR:
    printf("NODE_XSTR:\n");
    dump_str(mrb, xstr_node(tree)->list, offset+1, lineno);
    break;

  case NODE_SYM:
    printf("NODE_SYM: %s\n", mrb_sym_dump(mrb, sym_node(tree)->symbol));
    break;

  case NODE_DSYM:
    printf("NODE_DSYM:\n");
    dump_str(mrb, str_node(tree)->list, offset+1, lineno);
    break;

  case NODE_LVAR:
    printf("NODE_LVAR: %s\n", mrb_sym_dump(mrb, var_node(tree)->symbol));
    break;

  case NODE_GVAR:
    printf("NODE_GVAR: %s\n", mrb_sym_dump(mrb, var_node(tree)->symbol));
    break;

  case NODE_IVAR:
    printf("NODE_IVAR: %s\n", mrb_sym_dump(mrb, var_node(tree)->symbol));
    break;

  case NODE_CVAR:
    printf("NODE_CVAR: %s\n", mrb_sym_dump(mrb, var_node(tree)->symbol));
    break;

  case NODE_NVAR:
    printf("NODE_NVAR: %d\n", nvar_node(tree)->num);
    break;

  case NODE_CONST:
    printf("NODE_CONST: %s\n", mrb_sym_dump(mrb, var_node(tree)->symbol));
    break;

  case NODE_CALL:
    printf("NODE_CALL: %s\n", mrb_sym_dump(mrb, call_node(tree)->method_name));
    if (call_node(tree)->receiver) {
      dump_prefix(offset+1, lineno);
      printf("receiver:\n");
      dump_node(mrb, call_node(tree)->receiver, offset+2);
    }
    if (call_node(tree)->args) {
      dump_callargs(mrb, call_node(tree)->args, offset, lineno);
    }
    break;

  case NODE_ARRAY:
    printf("NODE_ARRAY:\n");
    if (array_node(tree)->elements) {
      dump_recur(mrb, array_node(tree)->elements, offset+1);
    }
    break;

  case NODE_TRUE:
    printf("NODE_TRUE\n");
    break;

  case NODE_FALSE:
    printf("NODE_FALSE\n");
    break;

  case NODE_NIL:
    printf("NODE_NIL\n");
    break;

  case NODE_SELF:
    printf("NODE_SELF\n");
    break;

  case NODE_IF:
    printf("NODE_IF:\n");
    if (if_node(tree)->condition) {
      dump_prefix(offset+1, lineno);
      printf("cond:\n");
      dump_node(mrb, if_node(tree)->condition, offset+2);
    }
    if (if_node(tree)->then_body) {
      dump_prefix(offset+1, lineno);
      printf("then:\n");
      dump_node(mrb, if_node(tree)->then_body, offset+2);
    }
    if (if_node(tree)->else_body) {
      dump_prefix(offset+1, lineno);
      printf("else:\n");
      dump_node(mrb, if_node(tree)->else_body, offset+2);
    }
    break;

  case NODE_DEF:
    printf("NODE_DEF: %s\n", mrb_sym_dump(mrb, def_node(tree)->name));
    if (def_node(tree)->args) {
      dump_args(mrb, sdef_node(tree)->args, offset+1, lineno);
    }
    if (def_node(tree)->locals) {
      dump_locals(mrb, def_node(tree)->locals, offset+1, lineno);
    }
    if (def_node(tree)->body) {
      dump_prefix(offset+1, lineno);
      printf("body:\n");
      dump_node(mrb, def_node(tree)->body, offset+2);
    }
    break;

  case NODE_ASGN:
    printf("NODE_ASGN:\n");
    if (asgn_node(tree)->lhs) {
      dump_prefix(offset+1, lineno);
      printf("lhs:\n");
      dump_node(mrb, asgn_node(tree)->lhs, offset+2);
    }
    if (asgn_node(tree)->rhs) {
      dump_prefix(offset+1, lineno);
      printf("rhs:\n");
      dump_node(mrb, asgn_node(tree)->rhs, offset+2);
    }
    break;

  case NODE_MASGN:
  case NODE_MARG:
    printf("%s:\n", get_node_type(tree) == NODE_MASGN ? "NODE_MASGN" : "NODE_MARG");
    /* Handle pre-splat variables */
    if (masgn_node(tree)->pre) {
      dump_prefix(offset+1, lineno);
      printf("pre:\n");
      dump_recur(mrb, masgn_node(tree)->pre, offset+2);
    }
    /* Handle splat variable (can be -1 sentinel for anonymous splat) */
    if (masgn_node(tree)->rest) {
      if ((intptr_t)masgn_node(tree)->rest == -1) {
        dump_prefix(offset+1, lineno);
        printf("rest: *<anonymous>\n");
      }
      else {
        dump_prefix(offset+1, lineno);
        printf("rest:\n");
        dump_node(mrb, masgn_node(tree)->rest, offset+2);
      }
    }
    /* Handle post-splat variables */
    if (masgn_node(tree)->post) {
      dump_prefix(offset+1, lineno);
      printf("post:\n");
      dump_recur(mrb, masgn_node(tree)->post, offset+2);
    }
    if (masgn_node(tree)->rhs) {
      dump_prefix(offset+1, lineno);
      printf("rhs:\n");
      dump_node(mrb, masgn_node(tree)->rhs, offset+2);
    }
    break;

  case NODE_RETURN:
    printf("NODE_RETURN:\n");
    if (return_node(tree)->args) {
      dump_node(mrb, return_node(tree)->args, offset);
    }
    break;

  case NODE_BREAK:
    printf("NODE_BREAK:\n");
    if (break_node(tree)->value) {
      dump_prefix(offset+1, lineno);
      printf("value:\n");
      dump_node(mrb, break_node(tree)->value, offset+2);
    }
    break;

  case NODE_NEXT:
    printf("NODE_NEXT:\n");
    if (next_node(tree)->value) {
      dump_prefix(offset+1, lineno);
      printf("value:\n");
      dump_node(mrb, next_node(tree)->value, offset+2);
    }
    break;

  case NODE_NEGATE:
    printf("NODE_NEGATE:\n");
    if (negate_node(tree)->operand) {
      dump_prefix(offset+1, lineno);
      printf("operand:\n");
      dump_node(mrb, negate_node(tree)->operand, offset+2);
    }
    break;

  case NODE_STMTS:
    printf("NODE_STMTS:\n");
    if (stmts_node(tree)->stmts) {
      dump_recur(mrb, stmts_node(tree)->stmts, offset+1);
    }
    break;

  case NODE_BEGIN:
    printf("NODE_BEGIN:\n");
    if (begin_node(tree)->body) {
      dump_node(mrb, begin_node(tree)->body, offset+1);
    }
    break;

  case NODE_RESCUE:
    printf("NODE_RESCUE:\n");
    if (rescue_node(tree)->body) {
      dump_prefix(offset+1, lineno);
      printf("body:\n");
      dump_node(mrb, rescue_node(tree)->body, offset+2);
    }
    if (rescue_node(tree)->rescue_clauses) {
      node *n2 = rescue_node(tree)->rescue_clauses;
      dump_prefix(offset+1, lineno);
      printf("rescue:\n");
      while (n2) {
        node *n3 = n2->car;
        if (n3->car) {
          dump_prefix(offset+2, lineno);
          printf("handle classes:\n");
          dump_recur(mrb, n3->car, offset+3);
        }
        if (n3->cdr->car) {
          dump_prefix(offset+2, lineno);
          printf("exc_var:\n");
          dump_node(mrb, n3->cdr->car, offset+3);
        }
        if (n3->cdr->cdr->car) {
          dump_prefix(offset+2, lineno);
          printf("rescue body:\n");
          dump_node(mrb, n3->cdr->cdr->car, offset+3);
        }
        n2 = n2->cdr;
      }
    }
    if (rescue_node(tree)->else_clause) {
      dump_prefix(offset+1, lineno);
      printf("else:\n");
      dump_node(mrb, rescue_node(tree)->else_clause, offset+2);
    }
    break;

  case NODE_ENSURE:
    printf("NODE_ENSURE:\n");
    if (ensure_node(tree)->body) {
      dump_prefix(offset+1, lineno);
      printf("body:\n");
      dump_node(mrb, ensure_node(tree)->body, offset+2);
    }
    if (ensure_node(tree)->ensure_clause) {
      dump_prefix(offset+1, lineno);
      printf("ensure:\n");
      dump_node(mrb, ensure_node(tree)->ensure_clause, offset+2);
    }
    break;

  case NODE_LAMBDA:
    printf("NODE_LAMBDA:\n");
    goto block;

  case NODE_BLOCK:
    printf("NODE_BLOCK:\n");
  block:
    if (block_node(tree)->locals) {
      dump_locals(mrb, block_node(tree)->locals, offset+1, lineno);
    }
    if (block_node(tree)->args) {
      dump_args(mrb, block_node(tree)->args, offset+1, lineno);
    }
    dump_prefix(offset+1, lineno);
    printf("body:\n");
    dump_node(mrb, block_node(tree)->body, offset+2);
    break;

  case NODE_AND:
    printf("NODE_AND:\n");
    dump_node(mrb, and_node(tree)->left, offset+1);
    dump_node(mrb, and_node(tree)->right, offset+1);
    break;

  case NODE_OR:
    printf("NODE_OR:\n");
    dump_node(mrb, or_node(tree)->left, offset+1);
    dump_node(mrb, or_node(tree)->right, offset+1);
    break;

  case NODE_CASE:
    printf("NODE_CASE:\n");
    if (case_node(tree)->value) {
      dump_prefix(offset+1, lineno);
      printf("value:\n");
      dump_node(mrb, case_node(tree)->value, offset+2);
    }
    if (case_node(tree)->body) {
      node *when_node = case_node(tree)->body;
      while (when_node) {
        dump_prefix(offset+1, lineno);
        printf("when:\n");
        node *when_clause = when_node->car;
        if (when_clause && when_clause->car) {
          dump_prefix(offset+2, lineno);
          printf("cond:\n");
          dump_recur(mrb, when_clause->car, offset+3);
        }
        if (when_clause && when_clause->cdr) {
          dump_prefix(offset+2, lineno);
          printf("body:\n");
          dump_node(mrb, when_clause->cdr, offset+3);
        }
        when_node = when_node->cdr;
      }
    }
    break;

  case NODE_WHILE:
    printf("NODE_WHILE:\n");
    goto dump_loop_node;
  case NODE_UNTIL:
    printf("NODE_UNTIL:\n");
    goto dump_loop_node;
  case NODE_WHILE_MOD:
    printf("NODE_WHILE_MOD:\n");
    goto dump_loop_node;
  case NODE_UNTIL_MOD:
    printf("NODE_UNTIL_MOD:\n");

  dump_loop_node:
    dump_prefix(offset+1, lineno);
    printf("cond:\n");
    dump_node(mrb, while_node(tree)->condition, offset+2);
    dump_prefix(offset+1, lineno);
    printf("body:\n");
    dump_node(mrb, while_node(tree)->body, offset+2);
    break;

  case NODE_FOR:
    printf("NODE_FOR:\n");
    if (for_node(tree)->var) {
      dump_prefix(offset+1, lineno);
      printf("var:\n");
      /* FOR_NODE_VAR structure:
       * var_list->car: cons-list of pre-splat variables
       * var_list->cdr->car: splat varnode (not a cons-list)
       * var_list->cdr->cdr->car: cons-list of post-splat variables */
      node *var_list = for_node(tree)->var;
      if (var_list) {
        dump_recur(mrb, var_list->car, offset+2);
        if (var_list && var_list->cdr) {
          /* Second element is a varnode, not a cons-list */
          dump_prefix(offset+1, lineno);
          printf("splat var:\n");
          dump_node(mrb, var_list->cdr->car, offset+2);
          if (var_list->cdr->cdr) {
           /* Third element is a cons-list of post-splat variables */
           dump_prefix(offset+1, lineno);
           printf("post var:\n");
           dump_recur(mrb, var_list->cdr->cdr->car, offset+2);
          }
        }
      }
    }
    if (for_node(tree)->iterable) {
      dump_prefix(offset+1, lineno);
      printf("iterable:\n");
      dump_node(mrb, for_node(tree)->iterable, offset+2);
    }
    if (for_node(tree)->body) {
      dump_prefix(offset+1, lineno);
      printf("body:\n");
      dump_node(mrb, for_node(tree)->body, offset+2);
    }
    break;

  case NODE_DOT2:
    printf("NODE_DOT2:\n");
    {
      if (dot2_node(tree)->left) {
        dump_prefix(offset+1, lineno);
        printf("left:\n");
        dump_node(mrb, dot2_node(tree)->left, offset+2);
      }
      if (dot2_node(tree)->right) {
        dump_prefix(offset+1, lineno);
        printf("right:\n");
        dump_node(mrb, dot2_node(tree)->right, offset+2);
      }
    }
    break;

  case NODE_DOT3:
    printf("NODE_DOT3:\n");
    {
      if (dot3_node(tree)->left) {
        dump_prefix(offset+1, lineno);
        printf("left:\n");
        dump_node(mrb, dot3_node(tree)->left, offset+2);
      }
      if (dot3_node(tree)->right) {
        dump_prefix(offset+1, lineno);
        printf("right:\n");
        dump_node(mrb, dot3_node(tree)->right, offset+2);
      }
    }
    break;

  case NODE_COLON2:
    printf("NODE_COLON2:\n");
    if (colon2_node(tree)->base) {
      dump_prefix(offset+1, lineno);
      printf("base:\n");
      dump_node(mrb, colon2_node(tree)->base, offset+2);
    }
    dump_prefix(offset+1, lineno);
    printf("name: %s\n", mrb_sym_name(mrb, colon2_node(tree)->name));
    break;

  case NODE_COLON3:
    printf("NODE_COLON3: ::%s\n", mrb_sym_name(mrb, colon3_node(tree)->name));
    break;

  case NODE_HASH:
    printf("NODE_HASH:\n");
    {
      node *pairs = hash_node(tree)->pairs;
      while (pairs) {
        dump_prefix(offset+1, lineno);
        printf("key:\n");
        if (node_to_sym(pairs->car->car) == MRB_OPSYM(pow)) {
          dump_prefix(offset+2, lineno);
          printf("**\n");
        }
        else {
          dump_node(mrb, pairs->car->car, offset+2);
        }
        dump_prefix(offset+1, lineno);
        printf("value:\n");
        dump_node(mrb, pairs->car->cdr, offset+2);
        pairs = pairs->cdr;
      }
    }
    break;

  case NODE_SPLAT:
    printf("NODE_SPLAT:\n");
    dump_node(mrb, splat_node(tree)->value, offset+1);
    break;

  case NODE_OP_ASGN:
    printf("NODE_OP_ASGN:\n");
    dump_prefix(offset+1, lineno);
    printf("lhs:\n");
    dump_node(mrb, op_asgn_node(tree)->lhs, offset+2);
    dump_prefix(offset+1, lineno);
    printf("op='%s' (%d)\n", mrb_sym_name(mrb, op_asgn_node(tree)->op), (int)op_asgn_node(tree)->op);
    dump_node(mrb, op_asgn_node(tree)->rhs, offset+1);
    break;

  case NODE_SUPER:
    printf("NODE_SUPER:\n");
    if (super_node(tree)->args) {
      dump_callargs(mrb, super_node(tree)->args, offset, lineno);
    }
    break;

  case NODE_ZSUPER:
    printf("NODE_ZSUPER:\n");
    if (super_node(tree)->args) {
      dump_callargs(mrb, super_node(tree)->args, offset, lineno);
    }
    break;

  case NODE_YIELD:
    printf("NODE_YIELD:\n");
    if (yield_node(tree)->args) {
      dump_callargs(mrb, yield_node(tree)->args, offset, lineno);
    }
    break;

  case NODE_REDO:
    printf("NODE_REDO\n");
    break;

  case NODE_RETRY:
    printf("NODE_RETRY\n");
    break;

  case NODE_BACK_REF:
    printf("NODE_BACK_REF: $%c\n", node_to_int(tree));
    break;

  case NODE_NTH_REF:
    printf("NODE_NTH_REF: $%d\n", node_to_int(tree));
    break;

  case NODE_BLOCK_ARG:
    printf("NODE_BLOCK_ARG:\n");
    dump_node(mrb, block_arg_node(tree)->value, offset+1);
    break;

  case NODE_REGX:
    printf("NODE_REGX:\n");
    if (regx_node(tree)->list) {
      dump_str(mrb, regx_node(tree)->list, offset+1, lineno);
    }
    if (regx_node(tree)->flags) {
      dump_prefix(offset+1, lineno);
      printf("flags: %s\n", regx_node(tree)->flags);
    }
    if (regx_node(tree)->encoding) {
      dump_prefix(offset+1, lineno);
      printf("encoding: %s\n", regx_node(tree)->encoding);
    }
    break;

  case NODE_WORDS:
    printf("NODE_WORDS:\n");
    if (words_node(tree)->args) {
      node *list = words_node(tree)->args;
      while (list && list->car) {
        node *item = list->car;
        if (item->car == 0 && item->cdr == 0) {
          /* Skip separator (0 . 0) */
        }
        else if (item->car && item->cdr) {
          /* String item: (len . str) */
          dump_prefix(offset+1, lineno);
          int len = node_to_int(item->car);
          if (len >= 0 && len < 1000 && item->cdr) {
            printf("word: \"%.*s\"\n", len, (char*)item->cdr);
          }
        }
        list = list->cdr;
      }
    }
    break;

  case NODE_SYMBOLS:
    printf("NODE_SYMBOLS:\n");
    if (symbols_node(tree)->args) {
      node *list = symbols_node(tree)->args;
      while (list && list->car) {
        node *item = list->car;
        if (item->car == 0 && item->cdr == 0) {
          /* Skip separator (0 . 0) */
        } else if (item->car && item->cdr) {
          /* String item: (len . str) */
          dump_prefix(offset+1, lineno);
          int len = node_to_int(item->car);
          if (len >= 0 && len < 1000 && item->cdr) {
            printf("symbol: \"%.*s\"\n", len, (char*)item->cdr);
          }
        }
        list = list->cdr;
      }
    }
    break;

  case NODE_ALIAS:
    printf("NODE_ALIAS %s %s:\n",
           mrb_sym_dump(mrb, node_to_sym(tree->car)),
           mrb_sym_dump(mrb, node_to_sym(tree->cdr)));
    break;

  case NODE_UNDEF:
    printf("NODE_UNDEF");
    {
      node *t = tree;
      while (t) {
        printf(" %s", mrb_sym_dump(mrb, node_to_sym(t->car)));
        t = t->cdr;
      }
    }
    printf(":\n");
    break;

  case NODE_CLASS:
    printf("NODE_CLASS:\n");
    if (class_node(tree)->name) {
      dump_cpath(mrb, module_node(tree)->name, offset+1, lineno);
    }
    if (class_node(tree)->superclass) {
      dump_prefix(offset+1, lineno);
      printf("super:\n");
      dump_node(mrb, class_node(tree)->superclass, offset+2);
    }
    if (class_node(tree)->body) {
      dump_prefix(offset+1, lineno);
      printf("body:\n");
      dump_node(mrb, class_node(tree)->body->cdr, offset+2);
    }
    break;

  case NODE_MODULE:
    printf("NODE_MODULE:\n");
    if (module_node(tree)->name) {
      dump_cpath(mrb, module_node(tree)->name, offset+1, lineno);
    }
    if (module_node(tree)->body) {
      dump_prefix(offset+1, lineno);
      printf("body:\n");
      dump_node(mrb, module_node(tree)->body->cdr, offset+2);
    }
    break;

  case NODE_SCLASS:
    printf("NODE_SCLASS:\n");
    if (sclass_node(tree)->obj) {
      dump_prefix(offset+1, lineno);
      printf("obj:\n");
      dump_node(mrb, sclass_node(tree)->obj, offset+2);
    }
    if (sclass_node(tree)->body) {
      dump_prefix(offset+1, lineno);
      printf("body:\n");
      dump_node(mrb, sclass_node(tree)->body->cdr, offset+2);
    }
    break;

  case NODE_SDEF:
    printf("NODE_SDEF: %s\n", mrb_sym_dump(mrb, def_node(tree)->name));
    if (sdef_node(tree)->obj) {
      dump_prefix(offset+1, lineno);
      printf("recv:\n");
      dump_node(mrb, sdef_node(tree)->obj, offset+2);
    }
    if (sdef_node(tree)->args) {
      dump_args(mrb, sdef_node(tree)->args, offset+1, lineno);
    }
    if (sdef_node(tree)->locals) {
      dump_locals(mrb, sdef_node(tree)->locals, offset+1, lineno);
    }
    if (sdef_node(tree)->body) {
      dump_prefix(offset+1, lineno);
      printf("body:\n");
      dump_node(mrb, sdef_node(tree)->body, offset+2);
    }
    break;

  case NODE_POSTEXE:
    printf("NODE_POSTEXE:\n");
    dump_node(mrb, tree, offset+1);
    break;

  case NODE_HEREDOC:
    printf("NODE_HEREDOC:\n");
    if (heredoc_node(tree)->info.term) {
      dump_prefix(offset+1, lineno);
      printf("terminator: \"%s\"\n", heredoc_node(tree)->info.term);
    }
    if (heredoc_node(tree)->info.doc) {
      dump_prefix(offset+1, lineno);
      printf("body:\n");
      dump_str(mrb, heredoc_node(tree)->info.doc, offset+2, lineno);
    }
    if (heredoc_node(tree)->info.allow_indent) {
      dump_prefix(offset+1, lineno);
      printf("allow_indent: true\n");
    }
    if (heredoc_node(tree)->info.remove_indent) {
      dump_prefix(offset+1, lineno);
      printf("remove_indent: true\n");
    }
    break;

  default:
    /* Fallback: unknown node type - skip like codegen.c does */
    printf("unknown node type %d (0x%x)\n", nodetype, (unsigned)nodetype);
    break;
  }
#endif
}

void
mrb_parser_dump(mrb_state *mrb, node *tree, int offset)
{
  dump_node(mrb, tree, offset);
}

typedef mrb_bool mrb_parser_foreach_top_variable_func(mrb_state *mrb, mrb_sym sym, void *user);
void mrb_parser_foreach_top_variable(mrb_state *mrb, struct mrb_parser_state *p, mrb_parser_foreach_top_variable_func *func, void *user);

void
mrb_parser_foreach_top_variable(mrb_state *mrb, struct mrb_parser_state *p, mrb_parser_foreach_top_variable_func *func, void *user)
{
  const mrb_ast_node *n = p->tree;
  if (node_type_p((node*)n, NODE_SCOPE)) {
    /* Extract locals from variable-sized NODE_SCOPE */
    struct mrb_ast_scope_node *scope = scope_node(n);
    n = scope->locals;
    for (; n; n = n->cdr) {
      mrb_sym sym = node_to_sym(n->car);
      if (sym != 0) {
        if (!func(mrb, sym, user)) break;
      }
    }
  }
}
