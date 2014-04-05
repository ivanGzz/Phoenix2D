#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([Phoenix2D-base], [1.0], [nigm2005@gmail.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_CONFIG_SRCDIR([include/Actions.h])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.
AX_PTHREAD([], [AC_MSG_ERROR([Pthread library not found. Please set PTHREAD_CFLAGS and PTHREAD_LIBS correctly for your setup])])
AX_BOOST_BASE([1.55.0],[],[AC_MSG_ERROR([Boost base not found])])
AX_BOOST_REGEX

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h netdb.h string.h sys/socket.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_CHECK_FUNCS([bzero gethostbyname inet_ntoa pow socket sqrt])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
