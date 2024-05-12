#include "glib.h"
#include <gtk/gtk.h>

static void applyChanges() {
    g_print("button clicked\n");
}

static void onSliderChanged(GtkRange *range) {
    g_print("%f", gtk_range_get_value(range));
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *label;
    GtkWidget *box;
    GtkWidget *slider;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Brightness");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 200);

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    label = gtk_label_new("Value");

    slider = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 1, 100, 1);
    g_signal_connect(slider, "value_changed", G_CALLBACK(onSliderChanged),
                     NULL);

    button = gtk_button_new_with_label("Apply");
    g_signal_connect(button, "clicked", G_CALLBACK(applyChanges), NULL);

    gtk_box_append(GTK_BOX(box), label);
    gtk_box_append(GTK_BOX(box), slider);
    gtk_box_append(GTK_BOX(box), button);

    gtk_window_set_child(GTK_WINDOW(window), box);

    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {
    GtkApplication *app = gtk_application_new("org.mvn.brightnessui",
                                              G_APPLICATION_DEFAULT_FLAGS);
    int status;

    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
