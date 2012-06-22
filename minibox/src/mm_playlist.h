#ifndef __MM_PLAYLIST_H__
#define __MM_PLAYLIST_H__

#include <gtk/gtk.h>
#include <gst/gst.h>
#include <mz/mz_libs.h>
#include <mz/mz_path.h>
#include <mz/mz_list.h>
#include <mz/mz_dictionary.h>
#include "mm_sound.h"

typedef struct mm_playlist_t
{
    GtkWindow *window;

    GtkWidget *sw;
    GtkWidget *treeview;

} mm_playlist_t;

void mm_playlist_init(GtkWindow *window);
mm_playlist_t* mm_playlist_singleton();
void mm_playlist_add_files(mm_playlist_t *me);
void mm_playlist_pause_music(mm_playlist_t *me);
GtkWidget* mm_playlist_component(mm_playlist_t *me);

#endif
