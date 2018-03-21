#include "ui.h"
#include "mime.h"

void enable_styles(const gchar* path) {
	GtkCssProvider* provider = gtk_css_provider_new();
	GdkDisplay* display = gdk_display_get_default();
	GdkScreen* screen = gdk_display_get_default_screen(display);

	gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
	gtk_css_provider_load_from_path(GTK_CSS_PROVIDER(provider), path, NULL);
}

GtkWidget* new_document_window(GtkApplication* app, const gchar* mime, const gchar* scheme_id) {
	GtkWidget* window;
	GtkWidget* vbox;
	GtkWidget* source_view;
	GtkSourceBuffer* buffer;
	GtkSourceLanguage* lang;
	GtkStyleContext* style;
	GtkSourceStyleSchemeManager* scheme_mgr;
	GtkSourceStyleScheme* scheme;

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

	if (scheme_id != NULL) {
		scheme_mgr = gtk_source_style_scheme_manager_get_default();
		scheme = gtk_source_style_scheme_manager_get_scheme(scheme_mgr, scheme_id);

		if (scheme != NULL) {
			gtk_source_buffer_set_style_scheme(buffer, scheme);
		}
	}

	source_view = gtk_source_view_new_with_buffer(buffer);
	gtk_source_view_set_tab_width(GTK_SOURCE_VIEW(source_view), 4);
	gtk_source_view_set_insert_spaces_instead_of_tabs(GTK_SOURCE_VIEW(source_view), TRUE);
	gtk_box_pack_start(GTK_BOX(vbox), source_view, 1, 1, 0);

	style = gtk_widget_get_style_context(source_view);
	gtk_style_context_add_class(style, "source");

	return window;
}
