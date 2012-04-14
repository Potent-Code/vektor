lib_LTLIBRARIES = libvektor.la
libvektor_la_SOURCES = image.h sdl.h log.h log.c engine.h engine.c texture.h texture.c input.h input.c event.h event.c net.h net.c sprite.h sprite.c draw.h draw.c camera.h camera.c skybox.h skybox.c window.h window.c model.h model.c draw_model.h draw_model.c keys.h keybind.h keybind.c keystates.h keystates.c glsl_shaders.h glsl_shaders.c
if DARWIN
libvektor_la_SOURCES += SDLMain.m
libvektor_la_LDFLAGS = -framework SDL -framework OpenGL
else
libvektor_la_LDFLAGS = -lSDL -lGL -lGLU
endif
libvektor_la_LDFLAGS += -lmathlib
libvektor_la_LIBADD = ui/libvektorui.la
include_HEADERS = vektor.h

if HAVE_INDENT
vektor.h: vektor_out_1.h vektor_in.h vektor_out_3.h
	${CC} -E vektor_in.h | sed '/^\#/d' | indent -st -ut -ts2 -sob > vektor_out_2.h && cat vektor_out_1.h vektor_out_2.h vektor_out_3.h >> vektor.h
else
vektor.h: vektor_out_1.h vektor_in.h vektor_out_3.h
	${CC} -E vektor_in.h | sed '/^\#/d' > vektor_out_2.h && cat vektor_out_1.h vektor_out_2.h vektor_out_3.h >> vektor.h
endif

clean-local:
	rm -rf vektor_out_2.h vektor.h

bin_PROGRAMS = maketexture makemodel
maketexture_SOURCES = image.h maketexture.h maketexture.c
maketexture_LDFLAGS = -lz -lpng
makemodel_SOURCES = log.h log.c model.h model.c makemodel.h makemodel.c
makemodel_CFLAGS = -I/usr/include/libxml2
makemodel_LDFLAGS = -lxml2 -lmathlib
SUBDIRS = ui shaders
