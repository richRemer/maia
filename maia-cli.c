#include "ui.h"

#include <unistd.h>
#include <libgen.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtksourceview/gtksource.h>
#include <stdlib.h>

static void app_activated(GtkApplication* app, gpointer data) {
	const char* theme = getenv("MAIA_THEME");
	const GtkWidget* buttons[1];
	GtkWidget* open_button;
	GtkWidget* toolbar;
	GtkWidget* window;

	open_button = new_open_button();
	buttons[0] = open_button;
	toolbar = new_toolbar(buttons);
	window = new_empty_document(app, toolbar, "application/javascript", theme);

	g_signal_connect_swapped(open_button, "clicked", G_CALLBACK(gtk_widget_destroy), window);

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
