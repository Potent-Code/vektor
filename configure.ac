#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.60])
AC_INIT([vektor], [0.1], [ryan.lucchese@gmail.com])
AM_INIT_AUTOMAKE([vektor], [0.1])
AC_CONFIG_SRCDIR([src/draw.h])
AC_CONFIG_HEADERS([src/config.h])
AC_CONFIG_MACRO_DIR([m4])

# save CFLAGS for after AC_PROG_CC
test ".$CFLAGS" = "." && CFLAGS=" "

# Checks for programs.
AC_PROG_CC
AC_PROG_OBJC
LT_INIT

AM_PROG_CC_C_O

CFLAGS="-O0 -g3 -Wall -Wextra -Werror"
AC_ARG_ENABLE([nodebug], [AC_HELP_STRING([--enable-nodebug],
	          [build without debugging information (default NO)])],
		      [test "$enableval" = "yes" && CFLAGS="-O3 -Wall -Wextra -Werror"])

# Checks for libraries.
AC_PROG_CXX
#AX_CHECK_GL
#AX_CHECK_GLU

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h netdb.h stdlib.h string.h sys/param.h sys/socket.h sys/time.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([gethostbyname2 memmove memset select socket])
AC_CONFIG_FILES([vektor.pc])

# Check for running OS X
AC_MSG_CHECKING([if running Darwin])
UNAME=`uname -s`
if test "${UNAME}" = "Darwin"; then
	AC_MSG_RESULT(yes)
	AM_CONDITIONAL([DARWIN],true)
else
	AC_MSG_RESULT(no)
	AM_CONDITIONAL([DARWIN],false)
fi

AC_OUTPUT(Makefile src/Makefile share/Makefile)
