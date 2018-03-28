#ifndef MAIA_UI_H
#define MAIA_UI_H

#include <gtk/gtk.h>

void enable_styles(const gchar*);
GtkWidget* new_open_button();
GtkWidget* new_toolbar(GtkWidget* const*);
GtkWidget* new_empty_document(GtkApplication*, GtkWidget*, const gchar*, const gchar*);

#endif
