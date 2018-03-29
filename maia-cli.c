#include "ui.h"

#include <unistd.h>
#include <libgen.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtksourceview/gtksource.h>
#include <stdlib.h>

static void open_button_clicked(GtkButton* button, gpointer data) {
	GtkSourceBuffer* buffer = data;
	GtkWidget* window;
	GtkWidget* dialog;
	gint res;

	window = gtk_widget_get_toplevel(GTK_WIDGET(button));

	if (!GTK_IS_WINDOW(window)) {
		fprintf(stderr, "cannot find top-level window\n");
		return;
	}

	dialog = gtk_file_chooser_dialog_new(
		"Open File", GTK_WINDOW(window), GTK_FILE_CHOOSER_ACTION_OPEN,
		"_Cancel", GTK_RESPONSE_CANCEL,
		"_Open", GTK_RESPONSE_ACCEPT,
		NULL);

	res = gtk_dialog_run(GTK_DIALOG(dialog));

	if (res == GTK_RESPONSE_ACCEPT) {
		char* filename;
		gchar* contents;
		GError* error = NULL;

		filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));

		if (g_file_get_contents(filename, &contents, NULL, &error)) {
			gtk_source_buffer_begin_not_undoable_action(buffer);
			gtk_text_buffer_set_text(GTK_TEXT_BUFFER(buffer), contents, -1);
			gtk_source_buffer_end_not_undoable_action(buffer);
			g_free(contents);
		} else {
			fprintf(stderr, "%s\n", error->message);
			g_error_free(error);
		}

		g_free(filename);
	}

	gtk_widget_destroy(dialog);
}

static void app_activated(GtkApplication* app, gpointer data) {
	const char* theme = getenv("MAIA_THEME");
	GtkWidget* buttons[1];
	GtkWidget* open_button;
	GtkWidget* toolbar;
	GtkWidget* window;
	GtkSourceBuffer* buffer;

	open_button = new_open_button();
	buttons[0] = open_button;
	toolbar = new_toolbar(buttons);
	buffer = new_buffer("application/javascript");
	window = new_empty_document(app, toolbar, buffer, theme);

	g_signal_connect(open_button, "clicked", G_CALLBACK(open_button_clicked), buffer);

	gtk_widget_show_all(window);
}

void chdir_bin(const char* bin) {
	char* bin_path = malloc(strlen(bin) + 1);
	strcpy(bin_path, bin);
	chdir(dirname(bin_path));
	free(bin_path);
}

int main(int argc, char** argv) {
	GtkApplication* app;
	int status;

	gdk_init(&argc, &argv);
	chdir_bin(argv[0]);
	enable_styles("maia.css");

	app = gtk_application_new("us.remer.maia", G_APPLICATION_NON_UNIQUE);
	g_signal_connect(app, "activate", G_CALLBACK(app_activated), NULL);

	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);

	return status;
}
