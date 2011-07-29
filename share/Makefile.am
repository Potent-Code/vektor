vektordir = $(datadir)/@PACKAGE@/
vektor_DATA = logo.texture
fontsdir = $(datadir)/@PACKAGE@/fonts/
fonts_DATA = fonts fonts/default.font
uidir = $(datadir)/@PACKAGE@/ui/
ui_DATA = ui ui/scroll_bar.texture ui/ui_window.texture ui/ui_content.texture ui/ui_menu_bg.texture ui/chat_button.texture ui/console_button.texture ui/log_button.texture ui/ui_input_bar.texture ui/ui_scrollbar.texture

fonts:
	mkdir -p fonts

ui:
	mkdir -p ui

MAKETEXTURE = $(abs_top_srcdir)/src/maketexture
fonts/default.font: $(MAKETEXTURE)
	$(MAKETEXTURE) png/fonts/default.png fonts/default.font

ui/scroll_bar.texture: $(MAKETEXTURE)
	$(MAKETEXTURE) png/ui/scroll_bar.png ui/scroll_bar.texture

ui/ui_window.texture: $(MAKETEXTURE)
	$(MAKETEXTURE) png/ui/ui_window.png ui/ui_window.texture

ui/ui_content.texture: $(MAKETEXTURE)
	$(MAKETEXTURE) png/ui/ui_content.png ui/ui_content.texture

ui/ui_menu_bg.texture: $(MAKETEXTURE)
	$(MAKETEXTURE) png/ui/ui_menu_bg.png ui/ui_menu_bg.texture

ui/chat_button.texture: $(MAKETEXTURE)
	$(MAKETEXTURE) png/ui/chat_button.png ui/chat_button.texture

ui/console_button.texture: $(MAKETEXTURE)
	$(MAKETEXTURE) png/ui/console_button.png ui/console_button.texture

ui/log_button.texture: $(MAKETEXTURE)
	$(MAKETEXTURE) png/ui/log_button.png ui/log_button.texture

ui/ui_input_bar.texture: $(MAKETEXTURE)
	$(MAKETEXTURE) png/ui/ui_input_bar.png ui/ui_input_bar.texture

ui/ui_scrollbar.texture: $(MAKETEXTURE)
	$(MAKETEXTURE) png/ui/ui_scrollbar.png ui/ui_scrollbar.texture

logo.texture: $(MAKETEXTURE)
	$(MAKETEXTURE) png/logo.png logo.texture

clean-local:
	rm -fR logo.texture fonts ui
