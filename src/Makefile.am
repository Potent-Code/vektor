lib_LTLIBRARIES = libvektor.la
libvektor_la_SOURCES = image.h sdl.h sdl_window.h sdl_window.c texture.h texture.c input.h input.c net.h net.c sprite.h sprite.c player.h player.c draw.h draw.c
libvektor_la_CFLAGS = $(GL_CFLAGS) $(GLU_CFLAGS)
libvektor_la_LDFLAGS = $(GL_LIBS) $(GLU_LIBS)
if DARWIN
libvektor_la_SOURCES += SDLMain.m
libvektor_la_LDFLAGS += -framework Cocoa -framework SDL
else
libvektor_la_LDFLAGS += -lSDL
endif
include_HEADERS = vektor.h
bin_PROGRAMS = maketexture
maketexture_SOURCES = image.h maketexture.h maketexture.c
maketexture_LDFLAGS = -lpng
