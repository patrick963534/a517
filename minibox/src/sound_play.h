#ifndef __SOUND_PLAY_H__
#define __SOUND_PLAY_H__
/*
 * http://apps.hi.baidu.com/share/detail/448753
 * http://wangjiajun53880.blog.163.com/blog/static/1170013942010102221224798/
 */

#include <gst/gst.h>
#include <mz/mz_libs.h>

static GstElement *pipeline, *filesrc;
static GMainLoop *loop;

static gboolean bus_watch(GstBus *bus , GstMessage *msg , gpointer data)
{
    GMainLoop *loop = (GMainLoop *) data;
    if(GST_MESSAGE_TYPE(msg) == GST_MESSAGE_EOS){
        g_main_loop_quit(loop);
    }
    return TRUE;
}

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

void init_sound_mad()
{
    GstElement *decoder,*convert,*audiosink;
    GstBus *bus;

    loop = g_main_loop_new(NULL, TRUE);
    pipeline=gst_pipeline_new("pipeline");

    if(!pipeline) {
        g_print("Maybe pipeline cann't be created!\n");
        exit(-1);
    }

    filesrc = element_load("filesrc","disk_source");
    decoder = element_load("mad","decoder-audio");
    convert = element_load("audioconvert", "a-convert");
    audiosink = element_load("alsasink","sink");

    bus = gst_pipeline_get_bus(GST_PIPELINE(pipeline));
    gst_bus_add_watch(bus , bus_watch , loop);
    g_object_unref(bus);

    gst_bin_add_many(GST_BIN(pipeline),filesrc,decoder,convert,audiosink,NULL);

    gst_element_link_many(filesrc, decoder, convert, audiosink, NULL);
}

void sound_using_mad_stop()
{
    g_main_loop_quit(loop);
    gst_element_set_state(pipeline, GST_STATE_NULL);
}

/*
 *  need to install gstreamer0.10-ugly-plugins and libmad.
 */
void sound_using_mad_play(const char *file)
{
    g_main_loop_quit(loop);
    gst_element_set_state(pipeline, GST_STATE_NULL);

    g_object_set(G_OBJECT(filesrc), "location", file, NULL);

    gst_element_set_state(pipeline,GST_STATE_PLAYING);
    g_print("start playing\n");

    g_main_loop_run(loop);

    g_print("stop play.\n");
    gst_element_set_state(pipeline, GST_STATE_NULL);

    //gst_object_unref(GST_OBJECT(pipeline));

    g_print("exit play sound.\n");
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
