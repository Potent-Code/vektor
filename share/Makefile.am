vektordir = $(datadir)/@PACKAGE@/
vektor_DATA = logo.texture
fontsdir = $(datadir)/@PACKAGE@/fonts/
fonts_DATA = fonts/default.font

MAKETEXTURE = $(abs_top_srcdir)/src/maketexture
fonts/default.font: $(MAKETEXTURE)
	$(MAKETEXTURE) png/fonts/default.png fonts/default.font

logo.texture: $(MAKETEXTURE)
	$(MAKETEXTURE) png/logo.png logo.texture

clean-local:
	rm -rf logo.texture fonts/default.font
