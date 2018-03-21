#include "ui.h"
#include "mime.h"

GtkWidget* new_document_window(GtkApplication* app, const gchar* mime) {
	GtkWidget* window;
	GtkWidget* vbox;
	GtkWidget* source_view;
	GtkSourceBuffer* buffer;
	GtkSourceLanguage* lang;
	PangoFontDescription* font;

	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "Example");
	gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);

	vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
	gtk_container_add(GTK_CONTAINER(window), vbox);

	lang = source_language_for_mime_type(mime);
	buffer = lang == NULL
		? gtk_source_buffer_new(NULL)
		: gtk_source_buffer_new_with_language(lang);
	gtk_text_buffer_set_text(GTK_TEXT_BUFFER(buffer), "// example", -1);

	source_view = gtk_source_view_new_with_buffer(buffer);
	gtk_box_pack_start(GTK_BOX(vbox), source_view, 1, 1, 0);

	font = pango_font_description_from_string("mono 12");
	gtk_widget_override_font(source_view, font);
	pango_font_description_free(font);

	return window;
}
