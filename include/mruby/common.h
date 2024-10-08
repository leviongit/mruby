/**
** @file common.h - mruby common platform definition"
**
** See Copyright Notice in mruby.h
*/

#ifndef MRUBY_COMMON_H
#define MRUBY_COMMON_H

#ifdef __APPLE__
  #ifndef __TARGETCONDITIONALS__
  #include "TargetConditionals.h"
  #endif
#endif

#ifdef __cplusplus
#ifdef MRB_USE_CXX_ABI
#define MRB_BEGIN_DECL
#define MRB_END_DECL
#else
# define MRB_BEGIN_DECL extern "C" {
# define MRB_END_DECL }
#endif
#else
/** Start declarations in C mode */
# define MRB_BEGIN_DECL
/** End declarations in C mode */
# define MRB_END_DECL
#endif

#include <sys/types.h>
#if defined _MSC_VER
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif

/**
 * Shared compiler macros
 */
MRB_BEGIN_DECL

/** Declare a function that never returns. */
#if defined __STDC_VERSION__ && __STDC_VERSION__ >= 201112L
# define mrb_noreturn _Noreturn
#elif defined __GNUC__ && !defined __STRICT_ANSI__
# define mrb_noreturn __attribute__((noreturn))
#elif defined _MSC_VER
# define mrb_noreturn __declspec(noreturn)
#else
# define mrb_noreturn
#endif

/** Mark a function as deprecated. */
#if defined __GNUC__ && !defined __STRICT_ANSI__
# define mrb_deprecated __attribute__((deprecated))
#elif defined _MSC_VER
# define mrb_deprecated __declspec(deprecated)
#else
# define mrb_deprecated
#endif

/** Declare a type or object as an alignment requirement. */
#ifndef mrb_alignas
# if defined(__cplusplus) && __cplusplus >= 201103L
#  // https://en.cppreference.com/w/cpp/language/alignas
#  define mrb_alignas(n) alignas(n)
# elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
#  // https://en.cppreference.com/w/c/language/_Alignas
#  define mrb_alignas(n) _Alignas(n)
# elif defined(_MSC_VER) || defined(__INTEL_COMPILER)
#  // https://learn.microsoft.com/en-us/cpp/cpp/align-cpp?view=msvc-170
#  define mrb_alignas(n) __declspec(align(n))
# elif defined(__GNUC__) || defined(__clang__)
#  // https://gcc.gnu.org/onlinedocs/gcc/Common-Type-Attributes.html#index-aligned-type-attribute
#  define mrb_alignas(n) __attribute__((aligned(n)))
# else
#  // `mrb_alignas` defined as dummy. If necessary, send issues to https://github.com/mruby/mruby .
#  define mrb_alignas(n)
# endif
#endif

/** Declare a function as always inlined. */
#if defined _MSC_VER && _MSC_VER < 1900
# ifndef __cplusplus
#  define inline __inline
# endif
#endif
#define MRB_INLINE static inline

/** Declare a public mruby API function. */
#ifndef MRB_API
#if defined(MRB_BUILD_AS_DLL)
#if defined(MRB_CORE) || defined(MRB_LIB)
# define MRB_API __declspec(dllexport)
#else
# define MRB_API __declspec(dllimport)
#endif
#else
# define MRB_API extern
#endif
#endif

/** Declare mingw versions */
#if defined(__MINGW32__) || defined(__MINGW64__)
# include <_mingw.h>
# if defined(__MINGW64_VERSION_MAJOR)
#  define MRB_MINGW64_VERSION  (__MINGW64_VERSION_MAJOR * 1000 + __MINGW64_VERSION_MINOR)
# elif defined(__MINGW32_MAJOR_VERSION)
#  define MRB_MINGW32_VERSION  (__MINGW32_MAJOR_VERSION * 1000 + __MINGW32_MINOR_VERSION)
# endif
# if defined(__MINGW32__) && !defined(__MINGW64__)
#   define MRB_MINGW32_LEGACY
# endif
#endif

MRB_END_DECL

#endif  /* MRUBY_COMMON_H */
