#ifndef MAIA_MIME_H
#define MAIA_MIME_H

#include <gtk/gtk.h>
#include <gtksourceview/gtksource.h>

GtkSourceLanguage* source_language_for_mime_type(const gchar*);

#endif