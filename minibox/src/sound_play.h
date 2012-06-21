#ifndef __SOUND_PLAY_H__
#define __SOUND_PLAY_H__

void play_sound_ogg(const char *file)
{
    char *uri;
    GstElement *sink, *play;

    sink = gst_element_factory_make("alsasink", "sink");
    play = gst_element_factory_make("playbin2", "play");
    uri = g_strdup_printf("file://%s", file);

    g_object_set(G_OBJECT(play), "uri", uri, "audio-sink", sink, NULL);

    if (!sink || !play || !uri) {
        g_warning("One element could not be created!! (%s, %d)", __FILE__, __LINE__);
        goto error;
    }

    g_print("start playing\n");
    gst_element_set_state(play,GST_STATE_PLAYING);
    mz_time_sleep(5000);
    gst_element_set_state(play,GST_STATE_NULL);
    g_print("stop playing\n");
    
error:
    if (play) {
        g_free(uri);
        gst_object_unref(GST_OBJECT(play));
    } 
}



#endif
