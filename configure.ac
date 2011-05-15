#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.65])
AC_INIT([vektor], [0.1], [ryan.lucchese@gmail.com])
AM_INIT_AUTOMAKE([vektor], [0.1])
AC_CONFIG_SRCDIR([draw.h])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_LIBTOOL

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h netdb.h stdlib.h string.h sys/param.h sys/socket.h sys/time.h unistd.h SDL/SDL.h])
AC_CHECK_HEADERS([GL/gl.h GL/glu.h],[cat "#include <GL/gl.h>
#include <GL/glu.h>
" >> sdl.h])
AC_CHECK_HEADERS([OpenGL/gl.h OpenGL/glu.h],[cat "#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
" >> sdl.h])
AC_CHECK_HEADERS([SDL/SDL.h],[cat "#include <SDL/SDL.h>
#endif" >> sdl.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([gethostbyname memmove memset select socket])
AC_CONFIG_FILES([vektor.pc])
AC_OUTPUT(Makefile)
