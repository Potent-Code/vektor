lib_LTLIBRARIES = libvektor.la
libvektor_la_SOURCES = image.h sdl.h ui.h sdl_window.h sdl_window.c texture.h texture.c input.h input.c event.h event.c net.h net.c sprite.h sprite.c player.h player.c draw.h draw.c bitmap.h bitmap.c font.h font.c textbox.h textbox.c scrollbar.h scrollbar.c plant.h plant.c ground.h ground.c camera.h camera.c pyramid.h pyramid.c skybox.h skybox.c window.h window.c console.h console.c button.h button.c
#libvektor_la_CFLAGS = $(GL_CFLAGS) $(GLU_CFLAGS)
#libvektor_la_LDFLAGS = $(GL_LIBS) $(GLU_LIBS)
if DARWIN
libvektor_la_SOURCES += SDLMain.m
libvektor_la_LDFLAGS = -framework SDL -framework OpenGL
else
libvektor_la_LDFLAGS = -lSDL -lGL -lGLU
endif
libvektor_la_LDFLAGS += -lmathlib
include_HEADERS = vektor.h
bin_PROGRAMS = maketexture
maketexture_SOURCES = image.h maketexture.h maketexture.c
maketexture_LDFLAGS = -lpng
