#ifndef __MM_WORKBENCH_H__
#define __MM_WORKBENCH_H__

#include <gtk/gtk.h>
#include <gst/gst.h>
#include "mm_builder.h"
#include "mm_playlist.h"
#include "mm_toolbar.h"
#include "mm_menu.h"

typedef struct mm_workbench_t
{
    GtkBox *vbox; 
    GtkWindow *window;
} mm_workbench_t;

void mm_workbench_init();
mm_workbench_t* mm_workbench_singleton();

#endif
