#include "ui.h"

#include <unistd.h>
#include <libgen.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtksourceview/gtksource.h>
#include <stdlib.h>

static void app_activated(GtkApplication* app, gpointer data) {
	const char* theme = getenv("MAIA_THEME");
	gtk_widget_show_all(new_empty_document(app, "application/javascript", theme));
}

int chdir_bin(const char* bin) {
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
