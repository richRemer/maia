#ifndef MAIA_UI_H
#define MAIA_UI_H

#include <gtk/gtk.h>

void enable_styles(const gchar*);
GtkWidget* new_empty_document(GtkApplication*, const gchar*, const gchar*);

#endif