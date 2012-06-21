#ifndef __SOUND_PLAY_H__
#define __SOUND_PLAY_H__
/*
 * http://apps.hi.baidu.com/share/detail/448753
 */

#include <gst/gst.h>
#include <mz/mz_libs.h>

/*
 *  need to install gstreamer0.10-ugly-plugins
 */
static GstElement* element_load(const char *factory, const char *name)
{
    GstElement *element;

    element = gst_element_factory_make(factory, name);

    if (!element) {
        g_print("Element [%s]:[%s] cann't be created", factory, name);
        exit(-1);
    }

    return element;
}

void play_sound_use_mad(const char *file)
{
    GstElement *pipeline,*filesrc,*decoder,*convert,*audiosink;

    pipeline=gst_pipeline_new("pipeline");

    if(!pipeline) {
        g_print("Maybe pipeline cann't be created!\n");
        exit(-1);
    }

    filesrc = element_load("filesrc","disk_source");
    decoder = element_load("mad","decoder-audio");
    convert = element_load("audioconvert", "a-convert");
    audiosink = element_load("alsasink","sink");

    g_object_set(G_OBJECT(filesrc), "location", file, NULL);

    gst_bin_add_many(GST_BIN(pipeline),filesrc,decoder,convert,audiosink,NULL);

    gst_element_link_many(filesrc, decoder, convert, audiosink, NULL);

    gst_element_set_state(pipeline,GST_STATE_PLAYING);

    while(gst_bin_iterate_recurse(GST_BIN(pipeline))) {
        mz_time_sleep(256);
    }

    gst_element_set_state(pipeline, GST_STATE_NULL);

    gst_object_unref(GST_OBJECT(pipeline));
}

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
