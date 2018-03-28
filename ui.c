#include "ui.h"
#include "mime.h"

static GdkPixbuf* open_image(const gchar* file) {
	GdkPixbuf* pixbuf;
	GError* error = NULL;

	pixbuf = gdk_pixbuf_new_from_file(file, &error);

	if (!pixbuf) {
		fprintf(stderr, "%s\n", error->message);
		g_error_free(error);
	}

	return pixbuf;
}

void enable_styles(const gchar* path) {
	GtkCssProvider* provider = gtk_css_provider_new();
	GdkDisplay* display = gdk_display_get_default();
	GdkScreen* screen = gdk_display_get_default_screen(display);

	gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
	gtk_css_provider_load_from_path(GTK_CSS_PROVIDER(provider), path, NULL);
}

GtkWidget* new_open_button() {
	GtkWidget* button;

	button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(button), gtk_image_new_from_file("folder-open.svg"));

	return button;
}

GtkWidget* new_toolbar(GtkWidget* const* buttons) {
	GtkWidget* toolbar;
	GtkWidget* const* button = buttons;
	GtkStyleContext* style;

	toolbar = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
	gtk_button_box_set_layout(GTK_BUTTON_BOX(toolbar), GTK_BUTTONBOX_START);

	style = gtk_widget_get_style_context(toolbar);
	gtk_style_context_add_class(style, "toolbar");

	if (*button != NULL) {
		gtk_container_add(GTK_CONTAINER(toolbar), GTK_WIDGET(*button));
		gtk_button_box_set_child_non_homogeneous(GTK_BUTTON_BOX(toolbar), GTK_WIDGET(*button), TRUE);
	}

	return toolbar;
}

GtkWidget* new_empty_document(GtkApplication* app, GtkWidget* toolbar, const gchar* mime, const gchar* scheme_id) {
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
	gtk_window_set_icon(GTK_WINDOW(window), open_image("maia.svg"));

	vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
	gtk_container_add(GTK_CONTAINER(window), vbox);
	gtk_box_set_spacing(GTK_BOX(vbox), 0);
	gtk_box_pack_start(GTK_BOX(vbox), toolbar, 0, 0, 0);

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
