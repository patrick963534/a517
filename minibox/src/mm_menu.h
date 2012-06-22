#ifndef __MM_MENU_H__
#define __MM_MENU_H__

#include <gtk/gtk.h>
#include <gst/gst.h>
#include "mm_builder.h"

typedef struct mm_memu_t
{
    GtkWindow *window;
    GObject *menu;
} mm_menu_t;

void mm_menu_init(GtkWindow *window);
mm_menu_t* mm_menu_singleton();
GtkWidget* mm_menu_component(mm_menu_t *me);

#endif
