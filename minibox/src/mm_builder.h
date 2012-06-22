#ifndef __MM_BUILDER_H__
#define __MM_BUILDER_H__

#include <gtk/gtk.h>
#include <gst/gst.h>
#include <mz/mz_libs.h>
#include <mz/mz_path.h>
#include <mz/mz_list.h>
#include <mz/mz_dictionary.h>

GObject* get_object_from_glade(const char *filepath, const char *obj_name);

#endif
