vektordir = $(datadir)/@PACKAGE@/
vektor_DATA = logo.texture
fontsdir = $(datadir)/@PACKAGE@/fonts/
fonts_DATA = fonts/default.font
uidir = $(datadir)/@PACKAGE@/ui/
ui_DATA = ui/scroll_bar.texture

MAKETEXTURE = $(abs_top_srcdir)/src/maketexture
fonts/default.font: $(MAKETEXTURE)
	mkdir fonts
	$(MAKETEXTURE) png/fonts/default.png fonts/default.font

ui/scroll_bar.texture: $(MAKETEXTURE)
	mkdir ui
	$(MAKETEXTURE) png/ui/scroll_bar.png ui/scroll_bar.texture

logo.texture: $(MAKETEXTURE)
	$(MAKETEXTURE) png/logo.png logo.texture

clean-local:
	rm -fR logo.texture fonts ui
