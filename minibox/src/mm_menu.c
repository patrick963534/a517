#include "mm_menu.h"

static mm_menu_t *singleton;

void mm_menu_init(GtkWindow *window)
{
    mm_menu_t *me = mz_malloc(sizeof(*me));

    me->menu = get_object_from_glade("res/gui/main_menu.glade", "main_menu");
    me->window = window;

    singleton = me;
}

mm_menu_t* mm_menu_singleton()
{
    return singleton;
}

GtkWidget* mm_menu_component(mm_menu_t *me)
{
    return GTK_WIDGET(me->menu);
}


