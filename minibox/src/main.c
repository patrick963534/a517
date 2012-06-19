#include <stdio.h>
#include <gtk/gtk.h>

enum list_type_t
{
    COLUMN_STRING,
    N_COLUMNS
};

char *names[] = {
    "hi",
    "good",
    "new"
};

static GtkTreeModel* get_list_model()
{
    GtkListStore *list;
    GtkTreeIter iter;
    int i;

    list = gtk_list_store_new(N_COLUMNS, G_TYPE_STRING);

    for (i = 0; i < 3; i++) {
        gtk_list_store_append(list, &iter);
        gtk_list_store_set(list, &iter, COLUMN_STRING, names[i], -1);
    }

    return GTK_TREE_MODEL(list);
}

static void add_columns(GtkTreeView *treeview)
{
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    //GtkTreeModel *model = gtk_tree_view_get_model(treeview);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes ("Description", renderer, "text", COLUMN_STRING, NULL);
    gtk_tree_view_column_set_sort_column_id(column, COLUMN_STRING);
    gtk_tree_view_append_column (treeview, column);
}

static GtkWidget* get_tree_view()
{
    GtkWidget *treeview;
    GtkTreeModel *model;

    model = get_list_model();
    treeview = gtk_tree_view_new_with_model(model);
    gtk_tree_view_set_rules_hint(GTK_TREE_VIEW(treeview), TRUE);
    gtk_tree_view_set_search_column (GTK_TREE_VIEW (treeview), COLUMN_STRING);

    g_object_unref (model);

    add_columns(GTK_TREE_VIEW (treeview));

    return treeview;
}

static void test_tree_view()
{
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *sw;
    GtkWidget *label;

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

    gtk_container_add(GTK_CONTAINER(sw), get_tree_view());

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_widget_destroyed), &window);

    gtk_widget_show(window);
    gtk_main();
}

static void test2()
{
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *sw;
    //GtkWidget *label;
    GtkWidget *button;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    //gtk_window_set_default_size(GTK_WINDOW(window), 280, 250);
    gtk_window_set_title(GTK_WINDOW(window), "minibox");

    //label = gtk_label_new ("this is a label");
    //gtk_container_add(GTK_CONTAINER(window), label);

    button = gtk_button_new_with_label("按我");
    gtk_container_add(GTK_CONTAINER(window), button);

    gtk_widget_show(window);
    gtk_main();
}

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    test2();
    return 0;
}
