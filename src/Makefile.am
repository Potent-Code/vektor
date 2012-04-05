lib_LTLIBRARIES = libvektor.la
libvektor_la_SOURCES = image.h sdl.h ui.h log.h log.c engine.h engine.c texture.h texture.c input.h input.c event.h event.c net.h net.c sprite.h sprite.c draw.h draw.c font.h font.c textbox.h textbox.c scrollbar.h scrollbar.c camera.h camera.c skybox.h skybox.c window.h window.c console.h console.c button.h button.c tabbar.h tabbar.c clickable.h clickable.c model.h model.c draw_model.h draw_model.c keys.h keybind.h keybind.c glsl_shaders.h glsl_shaders.c ui_window.h ui_window.c
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
bin_PROGRAMS = maketexture makemodel
maketexture_SOURCES = image.h maketexture.h maketexture.c
maketexture_LDFLAGS = -lz -lpng
makemodel_SOURCES = log.h log.c model.h model.c makemodel.h makemodel.c
makemodel_CFLAGS = -I/usr/include/libxml2
makemodel_LDFLAGS = -lxml2 -lmathlib
SUBDIRS = shaders
