/*
** node.h - nodes of abstract syntax tree
**
** See Copyright Notice in mruby.h
*/

#ifndef MRUBY_COMPILER_NODE_H
#define MRUBY_COMPILER_NODE_H

enum node_type {
  NODE_METHOD,
  NODE_SCOPE,
  NODE_BLOCK,
  NODE_IF,
  NODE_CASE,
  NODE_WHEN,
  NODE_WHILE,
  NODE_UNTIL,
  NODE_WHILE_MOD,
  NODE_UNTIL_MOD,
  NODE_ITER,
  NODE_FOR,
  NODE_BREAK,
  NODE_NEXT,
  NODE_REDO,
  NODE_RETRY,
  NODE_STMTS,
  NODE_BEGIN,
  NODE_RESCUE,
  NODE_ENSURE,
  NODE_AND,
  NODE_OR,
  NODE_NOT,
  NODE_MASGN,
  NODE_ASGN,
  NODE_CDECL,
  NODE_CVASGN,
  NODE_CVDECL,
  NODE_OP_ASGN,
  NODE_CALL,
  NODE_SCALL,
  NODE_FCALL,
  NODE_SUPER,
  NODE_ZSUPER,
  NODE_ARRAY,
  NODE_ZARRAY,
  NODE_HASH,
  NODE_KW_HASH,
  NODE_RETURN,
  NODE_YIELD,
  NODE_LVAR,
  NODE_DVAR,
  NODE_GVAR,
  NODE_IVAR,
  NODE_CONST,
  NODE_CVAR,
  NODE_NVAR,
  NODE_NTH_REF,
  NODE_BACK_REF,
  NODE_MATCH,
  NODE_INT,
  NODE_FLOAT,
  NODE_NEGATE,
  NODE_LAMBDA,
  NODE_SYM,
  NODE_STR,
  NODE_DSTR,
  NODE_XSTR,
  NODE_DXSTR,
  NODE_REGX,
  NODE_DREGX,
  NODE_DREGX_ONCE,
  NODE_ARG,
  NODE_ARGS_TAIL,
  NODE_KW_ARG,
  NODE_KW_REST_ARGS,
  NODE_SPLAT,
  NODE_TO_ARY,
  NODE_SVALUE,
  NODE_BLOCK_ARG,
  NODE_DEF,
  NODE_SDEF,
  NODE_ALIAS,
  NODE_UNDEF,
  NODE_CLASS,
  NODE_MODULE,
  NODE_SCLASS,
  NODE_COLON2,
  NODE_COLON3,
  NODE_DOT2,
  NODE_DOT3,
  NODE_SELF,
  NODE_NIL,
  NODE_TRUE,
  NODE_FALSE,
  NODE_DEFINED,
  NODE_POSTEXE,
  NODE_DSYM,
  NODE_HEREDOC,
  NODE_LITERAL_DELIM,
  NODE_WORDS,
  NODE_SYMBOLS,
  NODE_LAST
};

#define STR_FUNC_PARSING 0x01
#define STR_FUNC_EXPAND  0x02
#define STR_FUNC_REGEXP  0x04
#define STR_FUNC_WORD    0x08
#define STR_FUNC_SYMBOL  0x10
#define STR_FUNC_ARRAY   0x20
#define STR_FUNC_HEREDOC 0x40
#define STR_FUNC_XQUOTE  0x80

enum mrb_string_type {
  str_not_parsing  = (0),
  str_squote   = (STR_FUNC_PARSING),
  str_dquote   = (STR_FUNC_PARSING|STR_FUNC_EXPAND),
  str_regexp   = (STR_FUNC_PARSING|STR_FUNC_REGEXP|STR_FUNC_EXPAND),
  str_sword    = (STR_FUNC_PARSING|STR_FUNC_WORD|STR_FUNC_ARRAY),
  str_dword    = (STR_FUNC_PARSING|STR_FUNC_WORD|STR_FUNC_ARRAY|STR_FUNC_EXPAND),
  str_ssym     = (STR_FUNC_PARSING|STR_FUNC_SYMBOL),
  str_ssymbols = (STR_FUNC_PARSING|STR_FUNC_SYMBOL|STR_FUNC_ARRAY),
  str_dsymbols = (STR_FUNC_PARSING|STR_FUNC_SYMBOL|STR_FUNC_ARRAY|STR_FUNC_EXPAND),
  str_heredoc  = (STR_FUNC_PARSING|STR_FUNC_HEREDOC),
  str_xquote   = (STR_FUNC_PARSING|STR_FUNC_XQUOTE|STR_FUNC_EXPAND),
};

/* heredoc structure */
struct mrb_parser_heredoc_info {
  mrb_bool allow_indent:1;
  mrb_bool remove_indent:1;
  mrb_bool line_head:1;
  size_t indent;
  mrb_ast_node *indented;
  enum mrb_string_type type;
  const char *term;
  int term_len;
  mrb_ast_node *doc;
};

/* AST node structures - Head-only location optimization */

/* Structure nodes - only car/cdr, ignores location fields */
struct mrb_ast_node {
  struct mrb_ast_node *car, *cdr;
  /* No location fields - saves 4 bytes per structure node */
};

/* Head nodes - with location info, used by cons_head() */
struct mrb_ast_head_node {
  struct mrb_ast_node *car, *cdr;
  uint16_t lineno, filename_index;
};

#endif  /* MRUBY_COMPILER_NODE_H */
