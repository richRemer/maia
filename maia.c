#include <gtk/gtk.h>
#include <gtksourceview/gtksource.h>

static GtkSourceLanguage* source_language_for_mime_type(GtkSourceLanguageManager* lang_mgr, const gchar* mime) {
	GtkSourceLanguage* lang;
	const gchar* const* ids;
	const gchar* const* id;
	gchar** types;
	gchar** type;

	id = ids = gtk_source_language_manager_get_language_ids(lang_mgr);

	for (; *id != NULL; id++) {
		lang = gtk_source_language_manager_get_language(lang_mgr, *id);
		type = types = gtk_source_language_get_mime_types(lang);

		if (types != NULL) for (; *type != NULL; type++) {
			if (0 == g_strcmp0(mime, *type)) {
				return lang;
			}
		}
	}

	return NULL;
}

static GtkWidget* window_new(GtkApplication* app, gpointer data) {
	GtkWidget* window;
	GtkWidget* vbox;
	GtkWidget* source_view;
	GtkSourceBuffer* buffer;
	GtkSourceLanguageManager* lang_mgr;
	GtkSourceLanguage* lang;
	PangoFontDescription* font;

	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "Example");
	gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);

	vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
	gtk_container_add(GTK_CONTAINER(window), vbox);

	lang_mgr = gtk_source_language_manager_get_default();
	lang = source_language_for_mime_type(lang_mgr, "application/javascript");
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

static void app_activated(GtkApplication* app, gpointer data) {
	gtk_widget_show_all(window_new(app, data));
}

int main(int argc, char** argv) {
	GtkApplication* app;
	int status;

	app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(app_activated), NULL);

	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);

	return status;
}