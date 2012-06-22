#include "mm_builder.h"

static mz_dictionary_t *builders;

GObject* get_object_from_glade(const char *filepath, const char *obj_name)
{
    GtkBuilder *builder;
    GObject    *obj;
    GError     *err = NULL;

    if (builders == NULL)
        builders = mz_dictionary_new();

    builder = (GtkBuilder*)mz_dictionary_contains(builders, filepath);

    if (!builder) {
        builder = gtk_builder_new();
        gtk_builder_add_from_file(builder, filepath, &err);
        mz_dictionary_add(builders, filepath, builder);
    }

    obj = gtk_builder_get_object(builder, obj_name);

    if (obj == NULL)
        g_print("failed to load [%s] from file [%s].\n", obj_name, filepath);

    return obj;
}


