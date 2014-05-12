#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

static void enter_callback( GtkWidget *widget,
                            GtkWidget *entry )
{
  const gchar *entry_text;
  entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
  printf ("Entry contents: %s\n", entry_text);
}

static void entry_toggle_visibility( GtkWidget *checkbutton,
                                     GtkWidget *entry )
{
  gtk_entry_set_visibility (GTK_ENTRY (entry),
			    GTK_TOGGLE_BUTTON (checkbutton)->active);
}

int i( int   argc,
          char *argv[] )
{

    GtkWidget *window;
    GtkWidget *table;
    GtkWidget *entry;
    GtkWidget *button;
    GtkWidget *check;
    gint tmp_pos;

    gtk_init (&argc, &argv);

    /* create a new window */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request (GTK_WIDGET (window), 200, 100);
    gtk_window_set_title (GTK_WINDOW (window), "GTK Entry");
    g_signal_connect (window, "destroy",
                      G_CALLBACK (gtk_main_quit), NULL);
    g_signal_connect_swapped (window, "delete-event",
                              G_CALLBACK (gtk_widget_destroy),
                              window);
    gtk_container_set_border_width (GTK_CONTAINER (window), 20);

    table = gtk_table_new (10, 10, TRUE);
    gtk_container_add (GTK_CONTAINER (window), table);

    entry = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (entry), 50);
    g_signal_connect (entry, "activate",
		      G_CALLBACK (enter_callback),
		      entry);
    gtk_entry_set_text (GTK_ENTRY (entry), "hello");
    tmp_pos = GTK_ENTRY (entry)->text_length;
    gtk_editable_insert_text (GTK_EDITABLE (entry), " world", -1, &tmp_pos);
    gtk_editable_select_region (GTK_EDITABLE (entry),
			        0, GTK_ENTRY (entry)->text_length);
    gtk_table_attach_defaults (GTK_TABLE (table), button, 0, 10, 0, 10);
    gtk_widget_show (entry);



    check = gtk_check_button_new_with_label ("Visible");
    gtk_table_attach_defaults (GTK_TABLE (table), button, 1, 10, 1, 10);
    g_signal_connect (check, "toggled",
	              G_CALLBACK (entry_toggle_visibility), entry);
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (check), TRUE);
    gtk_widget_show (check);

    button = gtk_button_new_from_stock (GTK_STOCK_CLOSE);
    g_signal_connect_swapped (button, "clicked",
			      G_CALLBACK (gtk_widget_destroy),
			      window);
    gtk_table_attach_defaults (GTK_TABLE (table), button, 2, 10, 2, 10);
    gtk_widget_set_can_default (button, TRUE);
    gtk_widget_grab_default (button);
    gtk_widget_show (button);

    gtk_widget_show (window);

    gtk_main();

    return 0;
}

