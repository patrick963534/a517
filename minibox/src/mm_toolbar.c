#include "mm_toolbar.h"

static mm_toolbar_t *singleton;

static void toolbar_add_files(GtkWidget *button, gpointer userdata)
{
    mm_playlist_add_files(((mm_toolbar_t*)userdata)->playlist);
}

static void toolbar_pause_music(GtkWidget *button, gpointer userdata)
{
    mm_playlist_pause_music(((mm_toolbar_t*)userdata)->playlist);
}

void mm_toolbar_init(GtkWindow *window, mm_playlist_t *playlist)
{
    mm_toolbar_t *me = mz_malloc(sizeof(*me));

    me->toolbar = get_object_from_glade("res/gui/main_toolbar.glade", "main_toolbar");
    me->add_files = get_object_from_glade("res/gui/main_toolbar.glade", "add_files");
    me->pause_music = get_object_from_glade("res/gui/main_toolbar.glade", "pause_music");

    me->playlist = playlist;

    g_signal_connect(me->add_files, "clicked", G_CALLBACK(toolbar_add_files), me);
    g_signal_connect(me->pause_music, "clicked", G_CALLBACK(toolbar_pause_music), me);

    singleton = me;
}

mm_toolbar_t* mm_toolbar_singleton()
{
    return singleton;
}

GtkWidget* mm_toolbar_component(mm_toolbar_t *me)
{
    return GTK_WIDGET(me->toolbar);
}


