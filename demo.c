
#include <gtk/gtk.h>
#include "gtkimageview.h"

GtkWidget *stack;
GtkWidget *image_view;
GtkWidget *spinner;
GtkWidget *scrolled_window;




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


void
main (int argc, char **argv)
{
  gtk_init (&argc, &argv);
  GtkWidget *window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  GtkWidget *box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 12);
  GtkWidget *file_chooser = gtk_file_chooser_button_new ("Choose image", GTK_FILE_CHOOSER_ACTION_OPEN);

  g_signal_connect (G_OBJECT (file_chooser), "file-set",
                    G_CALLBACK (file_set_cb), NULL);

  scrolled_window = gtk_scrolled_window_new (NULL, NULL);
  image_view = gtk_image_view_new ();
  stack = gtk_stack_new ();
  spinner = gtk_spinner_new ();


  gtk_widget_set_vexpand (image_view, TRUE);
  gtk_widget_set_vexpand (scrolled_window, TRUE);
  gtk_widget_set_hexpand (scrolled_window, TRUE);
  gtk_container_add (GTK_CONTAINER (scrolled_window), image_view);
  gtk_container_add (GTK_CONTAINER (stack), scrolled_window);
  gtk_container_add (GTK_CONTAINER (stack), spinner);

  gtk_stack_set_visible_child (GTK_STACK (stack), scrolled_window);

  gtk_container_add (GTK_CONTAINER (box), stack);
  gtk_container_add (GTK_CONTAINER (box), file_chooser);
  gtk_container_add (GTK_CONTAINER (window), box);

  gtk_window_set_default_size (GTK_WINDOW (window), 500, 500);
  gtk_widget_show_all (window);
  gtk_main ();
}
