
#include <gtk/gtk.h>
#include "gtkimageview.h"

GtkWidget *stack;
GtkWidget *image_view;
GtkWidget *spinner;
GtkWidget *scrolled_window;
GtkWidget *angle_scale;




static void
file_loaded_cb (GObject      *source_object,
                GAsyncResult *result,
                gpointer      user_data)
{
  gtk_image_view_load_from_file_finish (GTK_IMAGE_VIEW (image_view),
                                        result,
                                        NULL);

  gtk_spinner_stop (GTK_SPINNER (spinner));

  /* Show the loaded image */
  gtk_stack_set_visible_child (GTK_STACK (stack), scrolled_window);
}

static void
file_set_cb (GtkFileChooserButton *button)
{
  char *uri = gtk_file_chooser_get_uri (GTK_FILE_CHOOSER (button));
  GFile *file = g_file_new_for_uri (uri);

  /* Go into Loading Mode */
  gtk_stack_set_visible_child (GTK_STACK (stack), spinner);
  gtk_spinner_start (GTK_SPINNER (spinner));

  /* Set our default values */
  gtk_image_view_set_angle (GTK_IMAGE_VIEW (image_view), 0);
  gtk_image_view_set_fit_allocation (GTK_IMAGE_VIEW (image_view), TRUE);

  gtk_image_view_load_from_file_async (GTK_IMAGE_VIEW (image_view),
                                       file,
                                       0, /* scale factor */
                                       NULL, /* No cancellable */
                                       file_loaded_cb,
                                       NULL);
}

static void
reset_button_clicked_cb ()
{
  gtk_image_view_set_scale (GTK_IMAGE_VIEW (image_view), 1.0);
  gtk_image_view_set_angle (GTK_IMAGE_VIEW (image_view), 0.0);
}


void
main (int argc, char **argv)
{
  gtk_init (&argc, &argv);
  GtkWidget *window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  GtkWidget *box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 12);
  GtkWidget *bottom_box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 6);
  GtkWidget *top_box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 6);
  GtkWidget *file_chooser = gtk_file_chooser_button_new ("Choose image", GTK_FILE_CHOOSER_ACTION_OPEN);
  GtkWidget *reset_button = gtk_button_new_with_label ("Reset");
  GtkAdjustment *angle_adjustment = gtk_adjustment_new (1, 0, 360, 1, 10, 0);

  g_signal_connect (G_OBJECT (file_chooser), "file-set",
                    G_CALLBACK (file_set_cb), NULL);

  scrolled_window = gtk_scrolled_window_new (NULL, NULL);
  image_view = gtk_image_view_new ();
  stack = gtk_stack_new ();
  spinner = gtk_spinner_new ();
  angle_scale = gtk_scale_new (GTK_ORIENTATION_VERTICAL, angle_adjustment);


  gtk_widget_set_vexpand (image_view, TRUE);
  gtk_widget_set_vexpand (scrolled_window, TRUE);
  gtk_widget_set_hexpand (scrolled_window, TRUE);
  gtk_container_add (GTK_CONTAINER (scrolled_window), image_view);
  gtk_container_add (GTK_CONTAINER (stack), scrolled_window);
  gtk_container_add (GTK_CONTAINER (stack), spinner);

  gtk_stack_set_visible_child (GTK_STACK (stack), scrolled_window);

  g_signal_connect (G_OBJECT (reset_button), "clicked", G_CALLBACK (reset_button_clicked_cb), NULL);

  gtk_widget_set_hexpand (file_chooser, TRUE);
  gtk_container_add (GTK_CONTAINER (bottom_box), file_chooser);
  gtk_container_add (GTK_CONTAINER (bottom_box), reset_button);


  g_object_bind_property (angle_adjustment, "value", image_view, "angle", G_BINDING_BIDIRECTIONAL | G_BINDING_SYNC_CREATE);


  gtk_container_add (GTK_CONTAINER (top_box), stack);
  gtk_container_add (GTK_CONTAINER (top_box), angle_scale);

  gtk_container_add (GTK_CONTAINER (box), top_box);
  gtk_container_add (GTK_CONTAINER (box), bottom_box);

  gtk_container_add (GTK_CONTAINER (window), box);

  gtk_window_set_default_size (GTK_WINDOW (window), 500, 500);
  gtk_widget_show_all (window);
  gtk_main ();
}
