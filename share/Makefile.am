vektordir = $(datadir)/@PACKAGE@/
vektor_DATA = logo.texture
fontsdir = $(datadir)/@PACKAGE@/fonts/
fonts_DATA = fonts/default.font

MAKETEXTURE = $(abs_top_srcdir)/src/maketexture
fonts/default.font: $(MAKETEXTURE)
	mkdir fonts
	$(MAKETEXTURE) png/fonts/default.png fonts/default.font

logo.texture: $(MAKETEXTURE)
	$(MAKETEXTURE) png/logo.png logo.texture

clean-local:
	rm -fR logo.texture fonts
