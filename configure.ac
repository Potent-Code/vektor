#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.60])
AC_INIT([vektor], [0.1], [ryan.lucchese@gmail.com])
AM_INIT_AUTOMAKE([vektor], [0.1])
AC_CONFIG_SRCDIR([src/draw.h])
AC_CONFIG_HEADERS([src/config.h])
AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CC
AC_PROG_LIBTOOL

# Checks for libraries.
AC_PROG_CXX
AX_CHECK_GL
AX_CHECK_GLU

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h netdb.h stdlib.h string.h sys/param.h sys/socket.h sys/time.h unistd.h])
#AC_CHECK_HEADERS([GL/gl.h GL/glu.h],[echo "#ifndef SDL_H
#define SDL_H

#include <GL/gl.h>
#include <GL/glu.h>
#" > sdl.h])
#AC_CHECK_HEADERS([OpenGL/gl.h OpenGL/glu.h],[echo "#ifndef SDL_H
#define SDL_H

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#" > sdl.h])
#AC_CHECK_HEADERS([SDL/SDL.h],[echo "#include <SDL/SDL.h>
#endif" >> sdl.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([gethostbyname memmove memset select socket])
AC_CONFIG_FILES([vektor.pc])
AC_OUTPUT(Makefile src/Makefile)
