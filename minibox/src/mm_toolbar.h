#ifndef __MM_TOOLBAR_H__
#define __MM_TOOLBAR_H__

#include <gtk/gtk.h>
#include <gst/gst.h>
#include "mm_playlist.h"
#include "mm_builder.h"

typedef struct mm_toolbar_t
{
    GtkWidget *window;
    GObject *toolbar;
    GObject *add_files;
    GObject *pause_music;

    mm_playlist_t *playlist;
} mm_toolbar_t;

void mm_toolbar_init(GtkWindow *window, mm_playlist_t *playlist);
mm_toolbar_t* mm_toolbar_singleton();
mm_toolbar_t* mm_toolbar_new(GtkWindow *window, mm_playlist_t *playlist);
GtkWidget* mm_toolbar_component(mm_toolbar_t *me);

#endif
