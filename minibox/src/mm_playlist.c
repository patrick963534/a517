#include "mm_playlist.h"

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
static mm_playlist_t* singleton;

static void update_playlist()
{
    GtkTreeIter iter;
    char *file;
    int i = 1;

    gtk_list_store_clear(list_store);

    mz_list_foreach(file_list, file, char) {
        gtk_list_store_append(list_store, &iter);
        gtk_list_store_set(list_store, &iter, COLUMN_ID, i, COLUMN_FILENAME, file, -1); 
        i++;
    }
}

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

        sound_using_mad_play((const char*)name);

        g_free(name);
    }
}

static void process_GSList(gpointer data, gpointer user_data)
{
    mz_list_add(file_list, data);
}

void mm_playlist_add_files(mm_playlist_t *me)
{
    GtkWidget *dialog;
    GtkFileFilter *filter1, *filter2;

    dialog = gtk_file_chooser_dialog_new("Add files", 
                                         me->window, 
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
    gtk_file_filter_set_name(filter2, "All Music Files(*.mp3)");

    gtk_file_filter_add_pattern(filter1, "*.*");

    gtk_file_filter_add_pattern(filter2, "*.mp3");
    //gtk_file_filter_add_pattern(filter2, "*.wav");
    //gtk_file_filter_add_pattern(filter2, "*.ogg");

    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter2);
    //gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter1);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        GSList *filenames = gtk_file_chooser_get_filenames(GTK_FILE_CHOOSER(dialog));
        g_slist_foreach(filenames, process_GSList, NULL);
        g_slist_free(filenames);
        update_playlist();
    }

    gtk_widget_destroy(dialog);
}

static void treeview_destroy(GtkWidget *object, gpointer user_data) 
{
    sound_using_mad_stop();
}

void mm_playlist_init(GtkWindow *window)
{
    mm_playlist_t *me = mz_malloc(sizeof(*me));

    if (file_list == NULL)
        file_list = mz_list_new();

    init_sound_mad();

    me->sw = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(me->sw), GTK_SHADOW_ETCHED_IN);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(me->sw), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);

    me->treeview = get_tree_view();
    g_signal_connect(me->treeview, "row-activated", G_CALLBACK(view_row_activated), NULL);
    g_signal_connect(me->treeview, "destroy", G_CALLBACK(treeview_destroy), NULL);

    gtk_container_add(GTK_CONTAINER(me->sw), me->treeview);

    singleton = me;
}

mm_playlist_t* mm_playlist_singleton()
{
    return singleton;
}

void mm_playlist_pause_music(mm_playlist_t *me)
{
    sound_using_mad_stop();
}

GtkWidget* mm_playlist_component(mm_playlist_t *me)
{
    return me->sw;
}

