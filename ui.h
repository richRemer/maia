#ifndef MAIA_UI_H
#define MAIA_UI_H

#include <gtk/gtk.h>
#include <gtksourceview/gtksource.h>

void enable_styles(const gchar*);
GtkWidget* new_open_button();
GtkWidget* new_toolbar(GtkWidget* const*);
GtkWidget* new_empty_document(GtkApplication*, GtkWidget*, GtkSourceBuffer*, const gchar*);
GtkSourceBuffer* new_buffer(const gchar*);

#endif
