//*****************************************************************************
// Copyright 1986-2010 by mental images GmbH, Fasanenstr. 81, D-10623 Berlin,
// Germany. All rights reserved.
//*****************************************************************************
/// \file mi/base/config.h
/// \brief Configuration of the Base API, see \ref mi_base_config.
///
//*****************************************************************************

#ifndef MI_BASE_CONFIG_H
#define MI_BASE_CONFIG_H

/** \defgroup mi_base_config Configuration of the Base API
    \ingroup mi_base
    \brief

       \par Include File:
       <tt> \#include <mi/base/base.h></tt>

    @{
 */

// These are config settings for deprecated features carried over from RS
#if defined(MI_ENABLE_DEPRECATED_2_2) || ! defined(MI_DISABLE_DEPRECATED_2_2)
// This macro is finally defined if names and features deprecated with RealityServer 2.2
// shall be available, which is the default for RealityServer 2.2 itself.
#define MI_DEPRECATED_2_2
#endif
// By default 2.1 deprecated features are disabled.
#if defined(MI_ENABLE_DEPRECATED_2_1)
// This macro is finally defined if names and features deprecated with RealityServer 2.1
// shall be available, which is the default for RealityServer 2.2 itself.
#define MI_DEPRECATED_2_1
#endif


// The preprocessor defines MI_DLL_EXPORT and MI_DLL_LOCAL provide access to
// the compiler-dependent declaration directives for managing symbol
// visibility. The default for any symbol is to be invisible unless specified
// otherwise. Visibility concerns shared libraries, mostly, which means that
// every symbol you'd like to be accessible when building a DLL must be
// declared as MI_DLL_EXPORT. The syntax is as follows:
//
//   MI_DLL_EXPORT void visible_function();
//
//   class MI_DLL_EXPORT visible_class
//   {
//   public:
//      visible_class();        /* these functions have external linkage */
//      ~visible_class();
//      void do_stuff();
//
//   private:
//     MI_DLL_LOCAL do_invisible_stuff();       /* no external linkage */
//   };
//
// On Windows, the preprocessor symbol MI_DLL_BUILD must be defined while
// compiling the shared object. Other platforms typically don't need that
// define, but it won't hurt either, so it should probably be defined anyway.
// The GCC compiler needs the command line switch "-fvisibility=hidden" for
// these declarations to take any effect.
//
// A general introduction to the topic can be found in Ulrich Drepper's paper
// "How To Write Shared Libraries" <http://people.redhat.com/~drepper/> and on
// the GCC web site <http://gcc.gnu.org/wiki/Visibility>.

#ifdef _WIN32
#  ifdef MI_DLL_BUILD
#    define MI_DLL_EXPORT __declspec(dllexport)
#  else
#    define MI_DLL_EXPORT __declspec(dllimport)
#  endif
#  define MI_DLL_LOCAL
#elif defined(__GNUC__) && !defined(__ICC)
#  define MI_DLL_EXPORT __attribute__ ((visibility("default")))
#  define MI_DLL_LOCAL  __attribute__ ((visibility("hidden")))
#else
#  define MI_DLL_EXPORT
#  define MI_DLL_LOCAL
#endif

// CIL cannot handle dllexport/dllimport.
#ifdef MI_CIL
#  undef MI_DLL_EXPORT
#  define MI_DLL_EXPORT
#endif

/// Creates an identifier from concatenating the values of \p X and \p Y,
/// possibly expanding macros in \p X and \p Y.
#define MI_BASE_JOIN( X, Y ) MI_BASE_DO_JOIN( X, Y )
#define MI_BASE_DO_JOIN( X, Y ) MI_BASE_DO_JOIN2(X,Y)
#define MI_BASE_DO_JOIN2( X, Y ) X##Y

/// Creates a string from the value of \p X, possibly expanding macros in \p X.
#define MI_BASE_STRINGIZE( X ) MI_BASE_DO_STRINGIZE( X )
#define MI_BASE_DO_STRINGIZE( X ) MI_BASE_DO_STRINGIZE2(X)
#define MI_BASE_DO_STRINGIZE2( X ) #X

/// Empty macro that can be used after function names to prevent
/// macro expansion that happen to have the same name, for example,
/// \c min or \c max functions.
#define MI_PREVENT_MACRO_EXPAND

#if defined(__cplusplus)

// STL Customization start

// If defined, the namespace alias definition for \c MISTD is suppressed.
// This can be used if the standard library classes and functions have
// been configured to live already in the \c MISTD namespace.
#ifndef MI_BASE_NO_MISTD_ALIAS

// If defined it expands to a valid namespace scope that contains the
// standard library classes and functions. It is used for the namespace
// alias \c MISTD instead of the default <code>::std</code>.
#ifdef MI_BASE_STD_NAMESPACE
namespace MISTD = MI_BASE_STD_NAMESPACE;
#else  // MI_BASE_STD_NAMESPACE
namespace std {}
namespace MISTD = ::std;
#if defined(_WIN32) && !defined(_USE_MATH_DEFINES)
#define _USE_MATH_DEFINES  // for M_PI
#endif
#endif // MI_BASE_STD_NAMESPACE

#endif // MI_BASE_NO_MISTD_ALIAS

// STL Customization end

#endif // __cplusplus

// Platform detection start

#if defined(_WIN32)

#if !defined(MI_PLATFORM_WINDOWS)
#define MI_PLATFORM_WINDOWS
#endif // !defined(MI_PLATFORM_WINDOWS)

#if defined(_WIN64)

#if !defined(MI_PLATFORM_WIN64)
#define MI_PLATFORM_WIN64
#endif // !defined(MI_PLATFORM_WIN64)

#else // defined(_WIN64)

#if !defined(MI_PLATFORM_WIN32)
#define MI_PLATFORM_WIN32
#endif // !defined(MI_PLATFORM_WIN32)

#endif // defined(_WIN64)

#elif defined(__APPLE__) // defined(_WIN32)

#if !defined(MI_PLATFORM_MACOSX)
#define MI_PLATFORM_MACOSX
#endif // !defined(MI_PLATFORM_MACOSX)

#elif defined(__unix__)  // defined(__APPLE__)

#if !defined(MI_PLATFORM_UNIX)
#define MI_PLATFORM_UNIX
#endif // !defined(MI_PLATFORM_UNIX)

#if defined(__x86_64__)

#if !defined(MI_PLATFORM_UNIX64)
#define MI_PLATFORM_UNIX64
#endif // !defined(MI_PLATFORM_UNIX64)

#else // defined(__x86_64__)

#if !defined(MI_PLATFORM_UNIX32)
#define MI_PLATFORM_UNIX32
#endif // !defined(MI_PLATFORM_UNIX32)

#endif // defined(__x86_64__)

#if defined(__linux__)

#if !defined(MI_PLATFORM_LINUX)
#define MI_PLATFORM_LINUX
#endif // !defined(MI_PLATFORM_LINUX)

#endif // defined(__linux__)

#endif // defined(__unix__)

// Platform detection end

// Compiler detection start

#if defined(_MSC_VER)

#ifndef MI_SKIP_COMPILER_VERSION_CHECK
#if (_MSC_VER < 1400)
#error Microsoft Visual C++ compiler version is unsupported (smaller than 1400).
#endif
#endif // MI_SKIP_COMPILER_VERSION_CHECK

#if !defined(MI_COMPILER_MSC)
#define MI_COMPILER_MSC _MSC_VER
#endif // !defined(MI_COMPILER_MSC)

#elif defined(__ICC) // defined(_MSC_VER)

#ifndef MI_SKIP_COMPILER_VERSION_CHECK
#if (__ICC < 900)
#error Intel C++ compiler version is unsupported (smaller than 900).
#endif
#endif // MI_SKIP_COMPILER_VERSION_CHECK

#if !defined(MI_COMPILER_ICC)
#define MI_COMPILER_ICC __ICC
#endif // !defined(MI_COMPILER_ICC)

#elif defined(__GNUC__) && !defined(__ICC) // #elif defined(__ICC)

#ifndef MI_SKIP_COMPILER_VERSION_CHECK
#if ((__GNUC__ < 3) || ((__GNUC__ == 3) && (__GNUC_MINOR__ < 3)))
#error GNU C++ compiler version is unsupported (smaller than 3.3).
#endif

#if ((__GNUC__ < 3) || ((__GNUC__ == 3) && (__GNUC_MINOR__ < 4)))
#warning GNU C++ compiler version is unsupported (smaller than 3.4).
#endif
#endif // MI_SKIP_COMPILER_VERSION_CHECK

#if !defined(MI_COMPILER_GCC)
#define MI_COMPILER_GCC __GNUC__
#endif // !defined(MI_COMPILER_GCC)

#endif // defined(__GNUC__)

// Compiler detection end

// Processor architecture detection start

#if defined(_M_IX86) || defined(__i386__) || defined(__x86_64__) || defined(_M_X64)

#if !defined(MI_ARCH_X86)
#define MI_ARCH_X86
#endif // !defined(MI_ARCH_X86)

#if (defined(__x86_64__) || defined(_M_X64) ) && !defined(MI_ARCH_X86_64)
#define MI_ARCH_X86_64
#endif // defined(__x86_64__) && !defined(MI_ARCH_X86_64)

#if !defined(MI_ARCH_LITTLE_ENDIAN)
#define MI_ARCH_LITTLE_ENDIAN
#endif // !defined(MI_ARCH_LITTLE_ENDIAN)

#elif defined(MI_PLATFORM_MACOSX) // defined(_M_IX86) || defined(__i386__)

#if !defined(MI_ARCH_PPC)
#define MI_ARCH_PPC
#endif // !defined(MI_ARCH_PPC)

#if defined(__ppc64__)
#define MI_ARCH_PPC_64
#endif // defined(__ppc64__)

#if !defined(MI_ARCH_BIG_ENDIAN)
#define MI_ARCH_BIG_ENDIAN
#endif // !defined(MI_ARCH_BIG_ENDIAN)

#elif defined(MI_CELL)  // defined(MI_PLATFORM_MACOSX)

#if ! defined( MI_ARCH_CELL)
#define MI_ARCH_CELL
#endif // !defined( MI_ARCH_CELL)

#ifdef __SPU__

#else // __SPU__

#if ! defined( MI_ARCH_CELL_64)
#define MI_ARCH_CELL_64
#endif // !defined( MI_ARCH_CELL_64)

#endif // __SPU__

#if !defined(MI_ARCH_BIG_ENDIAN)
#define MI_ARCH_BIG_ENDIAN
#endif // !defined(MI_ARCH_BIG_ENDIAN)

#elif defined(__sparcv9) // defined(MI_CELL)

#if ! defined( MI_ARCH_SPARC_64)
#define MI_ARCH_SPARC_64
#endif // !defined( MI_ARCH_SPARC_64)

#if !defined(MI_ARCH_BIG_ENDIAN)
#define MI_ARCH_BIG_ENDIAN
#endif // !defined(MI_ARCH_BIG_ENDIAN)

#endif

#if defined(MI_ARCH_X86_64) || defined(MI_ARCH_PPC_64) || defined(MI_ARCH_CELL_64) \
    || defined(MI_ARCH_SPARC_64)
#define MI_ARCH_64BIT
#endif // defined(MI_ARCH_X86_64) ...

// Check that we detected one architecture
#if ! defined(MI_ARCH_BIG_ENDIAN) && ! defined(MI_ARCH_LITTLE_ENDIAN)
#error Architecture unknown, neither big-endian nor little-endian detected.
#endif

// Processor architecture detection end

/** \def   MI_FORCE_INLINE
    The compiler-specific, strong \c inline keyword.

    The C++ language keyword \c inline is a recommendation to the compiler.
    Whether an inline function is actually inlined or not depends on the
    optimizer. In some cases, the developer knows better than the optimizer.
    This is why many compilers offer a separate, stronger inline statement.
    This define gives portable access to the compiler-specific keyword.

    Pre-define \c MI_FORCE_INLINE to override the setting in this file.
 */
#if defined(__cplusplus) && !defined(MI_FORCE_INLINE)
#  if   defined(_MSC_VER)               /* Microsoft Visual C++ */
#    define MI_FORCE_INLINE __forceinline
#  elif defined(__GNUC__)               /* GNU C/C++ Compiler */
#    if defined(DEBUG)
       /* Known bug in some g++ compiler versions: forced inlining produces
        * buggy code when compiling without optimization.
        */
#      define MI_FORCE_INLINE inline
#    else
#      define MI_FORCE_INLINE __attribute__ ((always_inline)) inline
#    endif
#  else
#    define MI_FORCE_INLINE inline
#  endif
#endif

/*@}*/ // end group mi_base_config

#endif // MI_BASE_CONFIG_H
