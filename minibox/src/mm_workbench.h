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

static mm_workbench_t *workbench_singleton;

void mm_workbench_init()
{
    mm_workbench_t *me = mz_malloc(sizeof(*me));

    me->window = GTK_WINDOW(get_object_from_glade("res/gui/main_window.glade", 
                                                  "main_window"));

    mm_menu_init(me->window);
    mm_playlist_init(me->window);
    mm_toolbar_init(me->window, mm_playlist_singleton());

    me->vbox = GTK_BOX(gtk_box_new(GTK_ORIENTATION_VERTICAL, 5));

    gtk_box_pack_start(me->vbox, mm_menu_component(mm_menu_singleton()), FALSE, FALSE, 0);
    gtk_box_pack_start(me->vbox, mm_toolbar_component(mm_toolbar_singleton()), FALSE, FALSE, 0);
    gtk_box_pack_start(me->vbox, mm_playlist_component(mm_playlist_singleton()), TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(me->window), GTK_WIDGET(me->vbox));

    g_signal_connect(me->window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(GTK_WIDGET(me->window));

    workbench_singleton = me;
}

mm_workbench_t* mm_workbench_singleton()
{
    return workbench_singleton;
}

#endif
