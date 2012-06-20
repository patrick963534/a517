#include <gtk/gtk.h>
#include <mz/mz_path.h>
#include <mz/mz_list.h>

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

static row_value_t rows[] = {
    { 1, "hi", "./hi" },
    { 2, "good", "./good" },
    { 3, "new", "./new" },
    { 1, "hi", "./hi" },
    { 2, "good", "./good" },
    { 3, "new", "./new" },
    { 1, "hi", "./hi" },
    { 2, "good", "./good" },
    { 3, "new", "./new" },
    { 1, "hi", "./hi" },
    { 2, "good", "./good" },
    { 3, "new", "./new" },
    { 1, "hi", "./hi" },
    { 2, "good", "./good" },
    { 3, "new", "./new" },
    { 1, "hi", "./hi" },
    { 2, "good", "./good" },
    { 3, "new", "./new" },
    { 1, "hi", "./hi" },
    { 2, "good", "./good" },
    { 3, "new", "./new" },
};

static GtkTreeModel* get_list_model()
{
    GtkListStore *list;
    GtkTreeIter iter;
    int i;
    int count = sizeof(rows) / sizeof(rows[0]);

    list = gtk_list_store_new(N_COLUMNS, 
                              G_TYPE_INT,
                              G_TYPE_STRING);

    for (i = 0; i < count; i++) {
        gtk_list_store_append(list, &iter);
        gtk_list_store_set(list, &iter, 
                           COLUMN_ID, rows[i].id, 
                           COLUMN_FILENAME, rows[i].filename, 
                           -1);
    }

    return GTK_TREE_MODEL(list);
}

static void add_columns(GtkTreeView *treeview)
{
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", COLUMN_ID, NULL);
    gtk_tree_view_column_set_sort_column_id(column, COLUMN_ID);
    gtk_tree_view_append_column (treeview, column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes ("Filename", renderer, "text", COLUMN_FILENAME, NULL);
    gtk_tree_view_column_set_sort_column_id(column, COLUMN_FILENAME);
    gtk_tree_view_append_column (treeview, column);
}

static GtkWidget* get_tree_view()
{
    GtkWidget *treeview;
    GtkTreeModel *model;

    model = get_list_model();
    treeview = gtk_tree_view_new_with_model(model);
    gtk_tree_view_set_rules_hint(GTK_TREE_VIEW(treeview), TRUE);
    gtk_tree_view_set_search_column (GTK_TREE_VIEW (treeview), COLUMN_FILENAME);

    g_object_unref (model);

    add_columns(GTK_TREE_VIEW (treeview));

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
        g_free(name);
    }
}

static GObject* get_object_from_glade(const char *filepath, const char *obj_name)
{
    GtkBuilder *builder;
    GObject    *obj;
    GError     *err = NULL;

    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, filepath, &err);

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

static void load_gui()
{
    GtkWidget *vbox; 
    GObject *window;
    GObject *menu;
    GObject *toolbar;

    window = get_object_from_glade("res/gui/main_window.glade", "main_window");
    menu = get_object_from_glade("res/gui/main_menu.glade", "main_menu");
    toolbar = get_object_from_glade("res/gui/main_toolbar.glade", "main_toolbar");

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(vbox), GTK_WIDGET(menu), FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), GTK_WIDGET(toolbar), FALSE, FALSE, 0);

    append_tree_view(vbox);

    gtk_container_add(GTK_CONTAINER(window), vbox);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(GTK_WIDGET(window));
}

int main(int argc, char *argv[])
{
    mz_list_t *list = mz_list_new();
    mz_path_all_files(list, "/home/patrick/pluto/project/yard_chat", 0);

    mz_list_iterator_begin(list);
    while (!mz_list_iterator_eof(list)) {
        g_print("%s\n", (char*)mz_list_iterator_current(list));
        mz_list_iterator_next(list);
    }

    gtk_init(&argc, &argv);

    load_gui();

    gtk_main();
    return 0;
}
