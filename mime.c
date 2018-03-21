#include "mime.h"

static GtkSourceLanguageManager* lang_mgr = NULL;

GtkSourceLanguage* source_language_for_mime_type(const gchar* mime) {
	GtkSourceLanguage* lang;
	const gchar* const* ids;
	const gchar* const* id;
	gchar** types;
	gchar** type;

	if (lang_mgr == NULL) {
		lang_mgr = gtk_source_language_manager_get_default();
	}

	id = ids = gtk_source_language_manager_get_language_ids(lang_mgr);

	for (; *id != NULL; id++) {
		lang = gtk_source_language_manager_get_language(lang_mgr, *id);
		type = types = gtk_source_language_get_mime_types(lang);

		if (types != NULL) for (; *type != NULL; type++) {
			if (0 == g_strcmp0(mime, *type)) {
				return lang;
			}
		}
	}

	return NULL;
}
