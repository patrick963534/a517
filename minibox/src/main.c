#include <gtk/gtk.h>
#include <gst/gst.h>
#include <mz/mz_libs.h>
#include <mz/mz_path.h>
#include <mz/mz_list.h>
#include <mz/mz_dictionary.h>
#include "sound_play.h"

enum list_type_t
{
    COLUMN_ID,
    COLUMN_FILENAME,
    N_COLUMNS
};

typedef struct row_value_t
{
    int  id;
    char *filename;
    char *filepath;
} row_value_t;

static GtkListStore *list_store;
static GtkWidget *treeview;
static mz_list_t *file_list;
static mz_dictionary_t *builders;

static GtkWidget* get_tree_view()
{
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;

    list_store = gtk_list_store_new(N_COLUMNS, 
                                    G_TYPE_INT,
                                    G_TYPE_STRING);

    treeview = gtk_tree_view_new_with_model(GTK_TREE_MODEL(list_store));

    gtk_tree_view_set_rules_hint(GTK_TREE_VIEW(treeview), TRUE);
    gtk_tree_view_set_search_column (GTK_TREE_VIEW (treeview), COLUMN_FILENAME);

    g_object_unref(GTK_TREE_MODEL(list_store));

    {
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", COLUMN_ID, NULL);
        gtk_tree_view_column_set_sort_column_id(column, COLUMN_ID);
        gtk_tree_view_append_column (GTK_TREE_VIEW(treeview), column);
    }

    {
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes ("Filename", renderer, "text", COLUMN_FILENAME, NULL);
        gtk_tree_view_column_set_sort_column_id(column, COLUMN_FILENAME);
        gtk_tree_view_append_column (GTK_TREE_VIEW(treeview), column);
    }

    return treeview;
}

static void view_row_activated (GtkTreeView        *treeview,
                         GtkTreePath        *path,
                         GtkTreeViewColumn  *col,
                         gpointer            userdata)
{
    GtkTreeModel *model;
    GtkTreeIter   iter;

    model = gtk_tree_view_get_model(treeview);

    if (gtk_tree_model_get_iter(model, &iter, path))
    {
        gchar *name;
        gtk_tree_model_get(model, &iter, COLUMN_FILENAME, &name, -1);

        g_print("Double-clicked row contains string: %s\n", name);

        play_sound_use_mad((const char*)name);

        g_free(name);
    }
}

static GObject* get_object_from_glade(const char *filepath, const char *obj_name)
{
    GtkBuilder *builder;
    GObject    *obj;
    GError     *err = NULL;

    builder = (GtkBuilder*)mz_dictionary_contains(builders, filepath);

    if (!builder) {
        builder = gtk_builder_new();
        gtk_builder_add_from_file(builder, filepath, &err);
        mz_dictionary_add(builders, filepath, builder);
    }

    obj = gtk_builder_get_object(builder, obj_name);

    if (obj == NULL)
        g_print("failed to load [%s] from file [%s].\n", obj_name, filepath);

    return obj;
}

static void append_tree_view(GtkWidget *vbox)
{
    GtkWidget *sw;
    GtkWidget *treeview;

    sw = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(sw), GTK_SHADOW_ETCHED_IN);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(sw), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
    gtk_box_pack_start(GTK_BOX(vbox), sw, TRUE, TRUE, 0);

    treeview = get_tree_view();
    gtk_container_add(GTK_CONTAINER(sw), treeview);
    g_signal_connect(treeview, "row-activated", G_CALLBACK(view_row_activated), NULL);
}

static void update_playlist()
{
    GtkTreeIter iter;
    int i = 1;

    gtk_list_store_clear(list_store);

    mz_list_iterator_begin(file_list);
    
    while (!mz_list_iterator_eof(file_list)) {

        char *file = (char*)mz_list_iterator_current(file_list);

        gtk_list_store_append(list_store, &iter);
        gtk_list_store_set(list_store, &iter, 
                           COLUMN_ID, i, 
                           COLUMN_FILENAME, file, 
                           -1);

        i++;
        mz_list_iterator_next(file_list);
    }
}


static void process_GSList(gpointer data, gpointer user_data)
{
    mz_list_add(file_list, data);
}

static void add_single_file(GtkWindow *window)
{
    GtkWidget *dialog;
    GtkFileFilter *filter1, *filter2;

    dialog = gtk_file_chooser_dialog_new("Add files", 
                                         window, 
                                         GTK_FILE_CHOOSER_ACTION_OPEN,
                                         GTK_STOCK_CANCEL,
                                         GTK_RESPONSE_CANCEL,
                                         GTK_STOCK_OPEN,
                                         GTK_RESPONSE_ACCEPT,
                                         NULL);

    gtk_file_chooser_set_select_multiple(GTK_FILE_CHOOSER(dialog), 1);

    filter1 = gtk_file_filter_new();
    filter2 = gtk_file_filter_new();

    gtk_file_filter_set_name(filter1, "All Files");
    gtk_file_filter_set_name(filter2, "All Music Files");

    gtk_file_filter_add_pattern(filter1, "*.*");

    gtk_file_filter_add_pattern(filter2, "*.mp3");
    gtk_file_filter_add_pattern(filter2, "*.wav");
    gtk_file_filter_add_pattern(filter2, "*.ogg");

    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter2);
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter1);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        GSList *filenames = gtk_file_chooser_get_filenames(GTK_FILE_CHOOSER(dialog));
        g_slist_foreach(filenames, process_GSList, NULL);
        g_slist_free(filenames);
        update_playlist();
    }

    gtk_widget_destroy(dialog);
}

static void toolbar_add_files(GtkWidget *button, gpointer userdata)
{
    add_single_file(GTK_WINDOW(userdata));
}

static void load_gui()
{
    GtkWidget *vbox; 
    GObject *window;
    GObject *menu;
    GObject *toolbar;
    GObject *add_file_tool_button;

    window = get_object_from_glade("res/gui/main_window.glade", "main_window");
    menu = get_object_from_glade("res/gui/main_menu.glade", "main_menu");
    toolbar = get_object_from_glade("res/gui/main_toolbar.glade", "main_toolbar");
    add_file_tool_button = get_object_from_glade("res/gui/main_toolbar.glade", "add_files");

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(vbox), GTK_WIDGET(menu), FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), GTK_WIDGET(toolbar), FALSE, FALSE, 0);

    append_tree_view(vbox);

    gtk_container_add(GTK_CONTAINER(window), vbox);

    g_signal_connect(add_file_tool_button, "clicked", G_CALLBACK(toolbar_add_files), window);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(GTK_WIDGET(window));
}

int main(int argc, char *argv[])
{
    file_list = mz_list_new();
    builders = mz_dictionary_new();

    gtk_init(&argc, &argv);
    gst_init(&argc, &argv);

    load_gui();

    gtk_main();
    return 0;
}
