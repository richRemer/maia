#include <gtk/gtk.h>
#include <gtksourceview/gtksource.h>
#include <stdlib.h>
#include "ui.h"

static void app_activated(GtkApplication* app, gpointer data) {
	const char* theme = getenv("MAIA_THEME");
	gtk_widget_show_all(new_document_window(app, "application/javascript", theme));
}

int main(int argc, char** argv) {
	GtkApplication* app;
	int status;

	gdk_init(&argc, &argv);
	enable_styles("style/maia.css");

	app = gtk_application_new("us.remer.maia", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(app_activated), NULL);

	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);

	return status;
}