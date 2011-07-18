vektordir = $(datadir)/@PACKAGE@/
vektor_DATA = logo.texture
fontsdir = $(datadir)/@PACKAGE@/fonts/
fonts_DATA = fonts/default.font
uidir = $(datadir)/@PACKAGE@/ui/
ui_DATA = ui/scroll_bar.texture ui/ui_window.texture ui/ui_content.texture ui/ui_menu_bg.texture ui/chat_button_up.texture ui/chat_button_down.texture ui/console_button_up.texture ui/console_button_down.texture ui/log_button_up.texture ui/log_button_down.texture

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

ui/chat_button_up.texture: $(MAKETEXTURE)
	$(MAKETEXTURE) png/ui/chat_button_up.png ui/chat_button_up.texture

ui/chat_button_down.texture: $(MAKETEXTURE)
	$(MAKETEXTURE) png/ui/chat_button_down.png ui/chat_button_down.texture

ui/console_button_up.texture: $(MAKETEXTURE)
	$(MAKETEXTURE) png/ui/console_button_up.png ui/console_button_up.texture

ui/console_button_down.texture: $(MAKETEXTURE)
	$(MAKETEXTURE) png/ui/console_button_down.png ui/console_button_down.texture

ui/log_button_up.texture: $(MAKETEXTURE)
	$(MAKETEXTURE) png/ui/log_button_up.png ui/log_button_up.texture

ui/log_button_down.texture: $(MAKETEXTURE)
	$(MAKETEXTURE) png/ui/log_button_down.png ui/log_button_down.texture

logo.texture: $(MAKETEXTURE)
	$(MAKETEXTURE) png/logo.png logo.texture

clean-local:
	rm -fR logo.texture fonts/* ui/*
