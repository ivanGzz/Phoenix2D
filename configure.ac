#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([Phoenix], [1.0], [nigm2005@gmail.com])
AC_CONFIG_SRCDIR([main.cpp])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
AM_PROG_AR
LT_INIT([disable-shared])

# Checks for programs.
AC_LANG(C++)
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.
AX_BOOST_BASE([1.45.0], [], [AC_MSG_ERROR([boost base not found])])
AX_BOOST_REGEX

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h netdb.h string.h sys/socket.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_CHECK_FUNCS([bzero gethostbyname inet_ntoa pow socket sqrt])

AC_CONFIG_FILES([utils/Makefile
				 base/Makefile
                 tests/Makefile
                 ai/Makefile
                 Makefile])
AC_OUTPUT
