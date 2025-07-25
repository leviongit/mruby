/*
** proc.c - Proc class
**
** See Copyright Notice in mruby.h
*/

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/proc.h>
#include <mruby/opcode.h>
#include <mruby/data.h>
#include <mruby/array.h>
#include <mruby/hash.h>
#include <mruby/internal.h>
#include <mruby/presym.h>

static const mrb_code call_iseq[] = {
  OP_CALL,
};

static const mrb_irep call_irep = {
  0,                                   /* nlocals */
  2,                                   /* nregs */
  0,                                   /* clen */
  MRB_ISEQ_NO_FREE | MRB_IREP_NO_FREE, /* flags */
  call_iseq,                           /* iseq */
  NULL,                                /* pool */
  NULL,                                /* syms */
  NULL,                                /* reps */
  NULL,                                /* lv */
  NULL,                                /* debug_info */
  1,                                   /* ilen */
  0,                                   /* plen */
  0,                                   /* slen */
  1,                                   /* rlen */
  0,                                   /* refcnt */
};

mrb_alignas(8)
static const struct RProc call_proc = {
  NULL, NULL, MRB_TT_PROC, MRB_GC_RED, MRB_OBJ_IS_FROZEN, MRB_PROC_SCOPE | MRB_PROC_STRICT,
  { &call_irep }, NULL, { NULL }
};

struct RProc*
mrb_proc_new(mrb_state *mrb, const mrb_irep *irep)
{
  struct RProc *p;
  mrb_callinfo *ci = mrb->c->ci;

  p = MRB_OBJ_ALLOC(mrb, MRB_TT_PROC, mrb->proc_class);
  if (ci) {
    struct RClass *tc = NULL;

    if (ci->proc) {
      tc = MRB_PROC_TARGET_CLASS(ci->proc);
    }
    if (tc == NULL) {
      tc = mrb_vm_ci_target_class(ci);
    }
    p->upper = ci->proc;
    p->e.target_class = tc;
  }
  if (irep) {
    mrb_irep_incref(mrb, (mrb_irep*)irep);
  }
  p->body.irep = irep;

  return p;
}

struct REnv*
mrb_env_new(mrb_state *mrb, struct mrb_context *c, mrb_callinfo *ci, int nstacks, mrb_value *stack, struct RClass *tc)
{
  struct REnv *e;
  mrb_int bidx = 1;
  int n = ci->n;
  int nk = ci->nk;

  e = MRB_OBJ_ALLOC(mrb, MRB_TT_ENV, NULL);
  e->c = tc;
  MRB_ENV_SET_LEN(e, nstacks);
  bidx += (n == 15) ? 1 : n;
  bidx += (nk == 15) ? 1 : (2*nk);
  MRB_ENV_SET_BIDX(e, bidx);
  e->mid = ci->mid;
  e->stack = stack;
  e->cxt = c;
  MRB_ENV_COPY_FLAGS_FROM_CI(e, ci);

  return e;
}

static void
closure_setup(mrb_state *mrb, struct RProc *p)
{
  mrb_callinfo *ci = mrb->c->ci;
  const struct RProc *up = p->upper;
  struct REnv *e = NULL;

  mrb_assert(ci != NULL);
  if ((e = mrb_vm_ci_env(ci)) != NULL) {
    /* do nothing, because e is assigned already */
  }
  else if (up) {
    struct RClass *tc = ci->u.target_class;

    if (MRB_PROC_ALIAS_P(up)) { /* alias */
      up = up->upper;
    }
    e = mrb_env_new(mrb, mrb->c, ci, up->body.irep->nlocals, ci->stack, tc);
    ci->u.env = e;
    if (MRB_PROC_ENV_P(up) && MRB_PROC_ENV(up)->cxt == NULL) {
      e->mid = MRB_PROC_ENV(up)->mid;
    }
  }
  if (e) {
    p->e.env = e;
    p->flags |= MRB_PROC_ENVSET;
    mrb_field_write_barrier(mrb, (struct RBasic*)p, (struct RBasic*)e);
  }
}

struct RProc*
mrb_closure_new(mrb_state *mrb, const mrb_irep *irep)
{
  struct RProc *p = mrb_proc_new(mrb, irep);

  closure_setup(mrb, p);
  return p;
}

/*
 * Creates a new Proc object from a C function.
 *
 * mrb: The mruby state.
 * func: The C function to create the Proc from.
 *
 * Returns a pointer to the new Proc object.
 */
MRB_API struct RProc*
mrb_proc_new_cfunc(mrb_state *mrb, mrb_func_t func)
{
  struct RProc *p;

  p = MRB_OBJ_ALLOC(mrb, MRB_TT_PROC, mrb->proc_class);
  p->body.func = func;
  p->flags |= MRB_PROC_CFUNC_FL;
  p->upper = 0;
  p->e.target_class = 0;

  return p;
}

/*
 * Creates a new Proc object from a C function with a new environment.
 *
 * mrb: The mruby state.
 * func: The C function to create the Proc from.
 * argc: The number of arguments to be stored in the environment.
 * argv: The array of mrb_value to be stored in the environment.
 *       These values are copied into the environment.
 *
 * Returns a pointer to the new Proc object.
 */
MRB_API struct RProc*
mrb_proc_new_cfunc_with_env(mrb_state *mrb, mrb_func_t func, mrb_int argc, const mrb_value *argv)
{
  struct RProc *p = mrb_proc_new_cfunc(mrb, func);
  struct REnv *e;
  int i;

  p->e.env = e = mrb_env_new(mrb, mrb->c, mrb->c->ci, 0, NULL, NULL);
  p->flags |= MRB_PROC_ENVSET;
  mrb_field_write_barrier(mrb, (struct RBasic*)p, (struct RBasic*)e);
  MRB_ENV_CLOSE(e);

  e->stack = (mrb_value*)mrb_malloc(mrb, sizeof(mrb_value) * argc);
  MRB_ENV_SET_LEN(e, argc);

  if (argv) {
    for (i = 0; i < argc; i++) {
      e->stack[i] = argv[i];
    }
  }
  else {
    for (i = 0; i < argc; i++) {
      SET_NIL_VALUE(e->stack[i]);
    }
  }
  return p;
}

/*
 * Creates a new closure from a C function.
 *
 * This function creates a new Proc object that represents a C function
 * along with an environment for a specified number of local variables.
 * The local variables in the environment are initialized to nil.
 *
 * mrb: The mruby state.
 * func: The C function to create the closure from.
 * nlocals: The number of local variables to allocate space for in the
 *          closure's environment.
 *
 * Returns a pointer to the new Proc object representing the closure.
 */
MRB_API struct RProc*
mrb_closure_new_cfunc(mrb_state *mrb, mrb_func_t func, int nlocals)
{
  return mrb_proc_new_cfunc_with_env(mrb, func, nlocals, NULL);
}

/*
 * Retrieves a value from the environment of the currently executing C function Proc.
 *
 * This function is used within a C function that was wrapped into a Proc
 * (e.g., using mrb_closure_new_cfunc or mrb_proc_new_cfunc_with_env)
 * to access values stored in its associated environment.
 *
 * mrb: The mruby state.
 * idx: The index of the value to retrieve from the C function's environment.
 *      The index must be non-negative and less than the number of
 *      environment entries (argc passed during creation).
 *
 * Returns the mrb_value stored at the specified index in the environment.
 *
 * Raises E_TYPE_ERROR if the currently executing Proc is not a C function
 * or if it does not have an associated environment.
 * Raises E_INDEX_ERROR if the provided index is out of bounds.
 */
MRB_API mrb_value
mrb_proc_cfunc_env_get(mrb_state *mrb, mrb_int idx)
{
  const struct RProc *p = mrb->c->ci->proc;
  struct REnv *e;

  if (!p || !MRB_PROC_CFUNC_P(p)) {
    mrb_raise(mrb, E_TYPE_ERROR, "Can't get cfunc env from non-cfunc proc");
  }
  e = MRB_PROC_ENV(p);
  if (!e) {
    mrb_raise(mrb, E_TYPE_ERROR, "Can't get cfunc env from cfunc Proc without REnv");
  }
  if (idx < 0 || MRB_ENV_LEN(e) <= idx) {
    mrb_raisef(mrb, E_INDEX_ERROR, "Env index out of range: %i (expected: 0 <= index < %i)",
               idx, MRB_ENV_LEN(e));
  }

  return e->stack[idx];
}

mrb_value
mrb_proc_get_self(mrb_state *mrb, const struct RProc *p, struct RClass **target_class_p)
{
  if (MRB_PROC_CFUNC_P(p)) {
    *target_class_p = mrb->object_class;
    return mrb_nil_value();
  }
  else {
    struct REnv *e = p->e.env;

    if (!e || e->tt != MRB_TT_ENV) {
      *target_class_p = mrb->object_class;
      return mrb_top_self(mrb);
    }
    else if (MRB_ENV_LEN(e) < 1) {
      mrb_raise(mrb, E_ARGUMENT_ERROR, "self is lost (probably ran out of memory when the block became independent)");
    }

    *target_class_p = e->c;
    return e->stack[0];
  }
}

void
mrb_proc_copy(mrb_state *mrb, struct RProc *a, const struct RProc *b)
{
  if (a->body.irep) {
    /* already initialized proc */
    return;
  }
  if (!MRB_PROC_CFUNC_P(b) && b->body.irep) {
    mrb_irep_incref(mrb, (mrb_irep*)b->body.irep);
  }
  a->flags = b->flags;
  a->body = b->body;
  a->upper = b->upper;
  a->e.env = b->e.env;
  /* a->e.target_class = a->e.target_class; */
}

static mrb_value
mrb_proc_s_new(mrb_state *mrb, mrb_value proc_class)
{
  mrb_value blk;
  mrb_value proc;
  struct RProc *p;

  /* Calling Proc.new without a block is not implemented yet */
  mrb_get_args(mrb, "&!", &blk);
  p = MRB_OBJ_ALLOC(mrb, MRB_TT_PROC, mrb_class_ptr(proc_class));
  mrb_proc_copy(mrb, p, mrb_proc_ptr(blk));
  proc = mrb_obj_value(p);
  mrb_funcall_with_block(mrb, proc, MRB_SYM(initialize), 0, NULL, proc);
  if (!MRB_PROC_STRICT_P(p) &&
      mrb->c->ci > mrb->c->cibase && MRB_PROC_ENV(p) == mrb->c->ci[-1].u.env) {
    p->flags |= MRB_PROC_ORPHAN;
  }
  return proc;
}

static void
check_proc(mrb_state *mrb, mrb_value proc)
{
  if (!mrb_proc_p(proc)) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "not a proc");
  }
}

static mrb_value
mrb_proc_init_copy(mrb_state *mrb, mrb_value self)
{
  mrb_value proc = mrb_get_arg1(mrb);

  check_proc(mrb, proc);
  mrb_proc_copy(mrb, mrb_proc_ptr(self), mrb_proc_ptr(proc));
  return self;
}

static mrb_value
proc_arity(mrb_state *mrb, mrb_value self)
{
  return mrb_int_value(mrb, mrb_proc_arity(mrb_proc_ptr(self)));
}

mrb_bool
mrb_proc_eql(mrb_state *mrb, mrb_value self, mrb_value other)
{
  if (mrb_type(self) != MRB_TT_PROC) return FALSE;
  if (mrb_type(other) != MRB_TT_PROC) return FALSE;

  const struct RProc *p1 = mrb_proc_ptr(self);
  const struct RProc *p2 = mrb_proc_ptr(other);
  if (MRB_PROC_CFUNC_P(p1)) {
    if (!MRB_PROC_CFUNC_P(p1)) return FALSE;
    if (p1->body.func != p2->body.func) return FALSE;
  }
  else if (MRB_PROC_CFUNC_P(p2)) return FALSE;
  else if (p1->body.irep != p2->body.irep) return FALSE;
  return TRUE;
}

static mrb_value
proc_eql(mrb_state *mrb, mrb_value self)
{
  return mrb_bool_value(mrb_proc_eql(mrb, self, mrb_get_arg1(mrb)));
}

static mrb_value
proc_hash(mrb_state *mrb, mrb_value self)
{
  const struct RProc *p = mrb_proc_ptr(self);
  return mrb_int_value(mrb, (mrb_int)(((intptr_t)p->body.irep)^MRB_TT_PROC));
}

/* 15.3.1.2.6  */
/* 15.3.1.3.27 */
/*
 * call-seq:
 *   lambda { |...| block }  -> a_proc
 *
 * Equivalent to <code>Proc.new</code>, except the resulting Proc objects
 * check the number of parameters passed when called.
 */
static mrb_value
proc_lambda(mrb_state *mrb, mrb_value self)
{
  mrb_value blk;
  const struct RProc *p;

  mrb_get_args(mrb, "&", &blk);
  if (mrb_nil_p(blk)) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "tried to create Proc object without a block");
  }
  check_proc(mrb, blk);
  p = mrb_proc_ptr(blk);
  if (!MRB_PROC_STRICT_P(p)) {
    struct RProc *p2 = MRB_OBJ_ALLOC(mrb, MRB_TT_PROC, p->c);
    mrb_proc_copy(mrb, p2, p);
    p2->flags |= MRB_PROC_STRICT;
    return mrb_obj_value(p2);
  }
  return blk;
}

mrb_int
mrb_proc_arity(const struct RProc *p)
{
  const mrb_irep *irep;
  const mrb_code *pc;
  mrb_aspec aspec;
  int ma, op, ra, pa, arity;

  if (MRB_PROC_CFUNC_P(p)) {
    /* TODO cfunc aspec not implemented yet */
    return -1;
  }

  irep = p->body.irep;
  if (!irep) {
    return 0;
  }

  pc = irep->iseq;
  /* arity is depend on OP_ENTER */
  if (*pc != OP_ENTER) {
    return 0;
  }

  aspec = PEEK_W(pc+1);
  ma = MRB_ASPEC_REQ(aspec);
  op = MRB_ASPEC_OPT(aspec);
  ra = MRB_ASPEC_REST(aspec);
  pa = MRB_ASPEC_POST(aspec);
  arity = ra || (MRB_PROC_STRICT_P(p) && op) ? -(ma + pa + 1) : ma + pa;

  return arity;
}

mrb_value
mrb_proc_local_variables(mrb_state *mrb, const struct RProc *proc)
{
  const mrb_irep *irep;
  mrb_value vars;
  size_t i;

  if (proc == NULL || MRB_PROC_CFUNC_P(proc)) {
    return mrb_ary_new(mrb);
  }
  vars = mrb_hash_new(mrb);
  while (proc) {
    if (MRB_PROC_CFUNC_P(proc)) break;
    irep = proc->body.irep;
    if (irep->lv) {
      for (i = 0; i + 1 < irep->nlocals; i++) {
        if (irep->lv[i]) {
          mrb_sym sym = irep->lv[i];
          const char *name = mrb_sym_name(mrb, sym);
          switch (name[0]) {
          case '*': case '&':
            break;
          default:
            mrb_hash_set(mrb, vars, mrb_symbol_value(sym), mrb_true_value());
            break;
          }
        }
      }
    }
    if (MRB_PROC_SCOPE_P(proc)) break;
    proc = proc->upper;
  }

  return mrb_hash_keys(mrb, vars);
}

const struct RProc *
mrb_proc_get_caller(mrb_state *mrb, struct REnv **envp)
{
  struct mrb_context *c = mrb->c;
  mrb_callinfo *ci = (c->ci > c->cibase) ? c->ci - 1 : c->cibase;
  const struct RProc *proc = ci->proc;

  if (!proc || MRB_PROC_CFUNC_P(proc)) {
    if (envp) *envp = NULL;
  }
  else {
    struct REnv *e = mrb_vm_ci_env(ci);

    if (e == NULL) {
      int nstacks = proc->body.irep->nlocals;
      e = mrb_env_new(mrb, c, ci, nstacks, ci->stack, mrb_vm_ci_target_class(ci));
      ci->u.env = e;
    }
    if (envp) *envp = e;
  }

  return proc;
}

#define IREP_LVAR_MERGE_DEFAULT  50
#define IREP_LVAR_MERGE_MINIMUM   8
#define IREP_LVAR_MERGE_MAXIMUM 240

#ifdef MRB_IREP_LVAR_MERGE_LIMIT
# define IREP_LVAR_MERGE_LIMIT \
  ((MRB_IREP_LVAR_MERGE_LIMIT) < IREP_LVAR_MERGE_MINIMUM ? IREP_LVAR_MERGE_MINIMUM : \
   (MRB_IREP_LVAR_MERGE_LIMIT) > IREP_LVAR_MERGE_MAXIMUM ? IREP_LVAR_MERGE_MAXIMUM : \
   (MRB_IREP_LVAR_MERGE_LIMIT))
#else
# define IREP_LVAR_MERGE_LIMIT IREP_LVAR_MERGE_DEFAULT
#endif

void
mrb_proc_merge_lvar(mrb_state *mrb, mrb_irep *irep, struct REnv *env, int num, const mrb_sym *lv, const mrb_value *stack)
{
  mrb_assert(!(irep->flags & MRB_IREP_NO_FREE));

  if ((irep->nlocals + num) > IREP_LVAR_MERGE_LIMIT) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "too many local variables for binding (mruby limitation)");
  }

  if (!lv) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "unavailable local variable names");
  }

  irep->lv = (mrb_sym*)mrb_realloc(mrb, (mrb_sym*)irep->lv, sizeof(mrb_sym) * (irep->nlocals - 1 /* self */ + num));
  env->stack = (mrb_value*)mrb_realloc(mrb, env->stack, sizeof(mrb_value) * (irep->nlocals + num));

  mrb_sym *destlv = (mrb_sym*)irep->lv + irep->nlocals - 1 /* self */;
  mrb_value *destst = env->stack + irep->nlocals;
  memmove(destlv, lv, sizeof(mrb_sym) * num);
  if (stack) {
    memmove(destst, stack, sizeof(mrb_value) * num);
    for (int i = 0; i < num; i++) {
      if (!mrb_immediate_p(stack[i])) {
        mrb_field_write_barrier(mrb, (struct RBasic*)env, (struct RBasic*)mrb_obj_ptr(stack[i]));
      }
    }
  }
  else {
    for (int i = num; i > 0; i--, destst++) {
      *destst = mrb_nil_value();
    }
  }
  irep->nlocals += num;
  irep->nregs = irep->nlocals;
  MRB_ENV_SET_LEN(env, irep->nlocals);
}

void
mrb_init_proc(mrb_state *mrb)
{
  mrb_method_t m;
  struct RClass *pc = mrb->proc_class = mrb_define_class_id(mrb, MRB_SYM(Proc), mrb->object_class); /* 15.2.17 */

  MRB_SET_INSTANCE_TT(pc, MRB_TT_PROC);
  MRB_UNDEF_ALLOCATOR(pc);
  mrb_define_class_method_id(mrb, pc, MRB_SYM(new), mrb_proc_s_new, MRB_ARGS_NONE()|MRB_ARGS_BLOCK());
  mrb_define_private_method_id(mrb, pc, MRB_SYM(initialize_copy), mrb_proc_init_copy, MRB_ARGS_REQ(1));
  mrb_define_method_id(mrb, pc, MRB_SYM(arity), proc_arity, MRB_ARGS_NONE()); /* 15.2.17.4.2 */
  mrb_define_method_id(mrb, pc, MRB_OPSYM(eq), proc_eql, MRB_ARGS_REQ(1));
  mrb_define_method_id(mrb, pc, MRB_SYM_Q(eql), proc_eql, MRB_ARGS_REQ(1));
  mrb_define_method_id(mrb, pc, MRB_SYM(hash), proc_hash, MRB_ARGS_NONE()); /* 15.2.17.4.2 */

  MRB_METHOD_FROM_PROC(m, &call_proc);
  mrb_define_method_raw(mrb, pc, MRB_SYM(call), m);   /* 15.2.17.4.3 */
  mrb_define_method_raw(mrb, pc, MRB_OPSYM(aref), m); /* 15.2.17.4.1 */

  mrb_define_private_method_id(mrb, mrb->kernel_module, MRB_SYM(lambda), proc_lambda, MRB_ARGS_NONE()|MRB_ARGS_BLOCK()); /* 15.3.1.3.27 */
}
