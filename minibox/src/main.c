#include <gtk/gtk.h>
#include <gst/gst.h>
#include "mm_workbench.h"

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    gst_init(&argc, &argv);

    mm_workbench_init();

    gtk_main();

    return 0;
}
