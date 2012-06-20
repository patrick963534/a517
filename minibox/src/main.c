#include <gtk/gtk.h>

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
    column = gtk_tree_view_column_new_with_attributes ("Description", renderer, "text", COLUMN_FILENAME, NULL);
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

void view_row_activated (GtkTreeView        *treeview,
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

static void test_tree_view()
{
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *sw;
    GtkWidget *label;
    GtkWidget *treeview;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size (GTK_WINDOW(window), 280, 250);
    gtk_window_set_title(GTK_WINDOW(window), "minibox");

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    label = gtk_label_new ("this is a label.");
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);

    sw = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(sw), GTK_SHADOW_ETCHED_IN);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(sw), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
    gtk_box_pack_start(GTK_BOX(vbox), sw, TRUE, TRUE, 0);

    treeview = get_tree_view();
    gtk_container_add(GTK_CONTAINER(sw), treeview);
    g_signal_connect(treeview, "row-activated", G_CALLBACK(view_row_activated), NULL);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), &window);

    gtk_widget_show_all(window);
    gtk_main();
}

static void test2()
{
    GtkWidget *window;
    GtkWidget *button;

    g_print("test2");
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 480, 320);
    gtk_window_set_title(GTK_WINDOW(window), "minibox");

    button = gtk_button_new_with_label("Press Me!");
    gtk_container_add(GTK_CONTAINER(window), button);
    gtk_widget_show(button);

    g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

    gtk_widget_show_all(window);
    gtk_main();
}

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    test_tree_view();
    return 0;
}
