#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT(Phoenix2D Library, 0.1, claudio.rdgz@gmail.com)
AC_CONFIG_AUX_DIR(config)
AC_CONFIG_HEADERS([communications.hpp])
AC_CONFIG_MACRO_DIR([m4])
m4_pattern_allow([AM_PROG_AR])
AM_PROG_AR
AC_CONFIG_SRCDIR(communications/Actions.cpp)

AM_INIT_AUTOMAKE([-Wall])

# Checks for programs.
AC_LANG(C++)
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.
LT_INIT

# Check for Boost libraries
AC_LANG_PUSH([C++])
AC_CHECK_HEADERS([boost/regex.hpp], [],
    [AC_MSG_ERROR(You need the Boost libraries.)])
AC_LANG_POP([C++])

AC_SUBST([PHOENIX_API_VERSION], [0.1])

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h netdb.h string.h sys/socket.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_CHECK_FUNCS([bzero gethostbyname inet_ntoa pow socket sqrt])

AC_OUTPUT(Makefile communications/Makefile)