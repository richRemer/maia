#include <gtk/gtk.h>
#include <gtksourceview/gtksource.h>

static GtkWidget* window_new(GtkApplication* app, gpointer data) {
	GtkWidget* window;
	GtkWidget* vbox;
	GtkWidget* source_view;
	GtkSourceBuffer* buffer;

	window = gtk_application_window_new(app);

	gtk_window_set_title(GTK_WINDOW(window), "Example");
	gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);

	vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
	gtk_container_add(GTK_CONTAINER(window), vbox);

	source_view = gtk_source_view_new();
	gtk_box_pack_start(GTK_BOX(vbox), source_view, 1, 1, 0);

	buffer = GTK_SOURCE_BUFFER(gtk_text_view_get_buffer(GTK_TEXT_VIEW(source_view)));
	gtk_text_buffer_set_text(GTK_TEXT_BUFFER(buffer), "Hello.  I am an example.", -1);

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