#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

static void enter_callback (GtkWidget *widget, GtkWidget *entry)
{

  const gchar *entry_text;
  entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
  printf ("Digitado: %s\n", entry_text);

}

static void entry_toggle_visibility (GtkWidget *checkbutton, GtkWidget *entry)
{

  gtk_entry_set_visibility (GTK_ENTRY (entry), GTK_TOGGLE_BUTTON (checkbutton)->active);

}

void janela_descricao_login (GtkWidget *wid, GtkWidget *win)
{
    GtkWidget *dialog = NULL;

    dialog = gtk_message_dialog_new (GTK_WINDOW (win), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, "Em breve, login de administrador!\n");
    gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
    gtk_dialog_run (GTK_DIALOG (dialog));
    gtk_widget_destroy (dialog);
}

void janela_cadastro_de_empresas ()
{

    GtkWidget *window;
    GtkWidget *vbox, *hbox;
    GtkWidget *entry;
    GtkWidget *button;
    GtkWidget *check;
    GtkWidget *fixed;
    gint tmp_pos;

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request (GTK_WIDGET (window), 500, 300);
    gtk_window_set_title (GTK_WINDOW (window), "Registro de empresa LocData");
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);

    vbox = gtk_vbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (window), vbox);
    gtk_widget_show (vbox);

    entry = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (entry), 50);
    g_signal_connect (entry, "activate", G_CALLBACK (enter_callback), entry);
    gtk_entry_set_text (GTK_ENTRY (entry), "Digite aqui");
    tmp_pos = GTK_ENTRY (entry)->text_length;
    gtk_editable_insert_text (GTK_EDITABLE (entry), " o nome da sua empresa", -1, &tmp_pos);
    gtk_editable_select_region (GTK_EDITABLE (entry), 0, GTK_ENTRY (entry)->text_length);
    gtk_box_pack_start (GTK_BOX (vbox), entry, TRUE, TRUE, 0);
    gtk_widget_show (entry);

    entry = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (entry), 50);
    g_signal_connect (entry, "activate", G_CALLBACK (enter_callback), entry);
    gtk_entry_set_text (GTK_ENTRY (entry), "Digite aqui");
    tmp_pos = GTK_ENTRY (entry)->text_length;
    gtk_editable_insert_text (GTK_EDITABLE (entry), " o nome do seu usuário Admin", -1, &tmp_pos);
    gtk_editable_select_region (GTK_EDITABLE (entry), 0, GTK_ENTRY (entry)->text_length);
    gtk_box_pack_start (GTK_BOX (vbox), entry, TRUE, TRUE, 0);
    gtk_widget_show (entry);

    entry = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (entry), 50);
    g_signal_connect (entry, "activate", G_CALLBACK (enter_callback), entry);
    gtk_entry_set_text (GTK_ENTRY (entry), "Digite aqui");
    tmp_pos = GTK_ENTRY (entry)->text_length;
    gtk_editable_insert_text (GTK_EDITABLE (entry), " a sua senha Admin", -1, &tmp_pos);
    gtk_editable_select_region (GTK_EDITABLE (entry), 0, GTK_ENTRY (entry)->text_length);
    gtk_box_pack_start (GTK_BOX (vbox), entry, TRUE, TRUE, 0);
    gtk_widget_show (entry);

    hbox = gtk_hbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (vbox), hbox);
    gtk_widget_show (hbox);

    check = gtk_check_button_new_with_label ("Visualizar senha");
    gtk_box_pack_start (GTK_BOX (hbox), check, TRUE, TRUE, 0);
    g_signal_connect (check, "toggled", G_CALLBACK (entry_toggle_visibility), entry);
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (check), TRUE);
    gtk_widget_show (check);

    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(vbox), fixed);
    gtk_widget_show(fixed);

    button = gtk_button_new_from_stock (GTK_STOCK_CLOSE);
    g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
    gtk_fixed_put(GTK_FIXED(fixed), button, 1, 15);
    gtk_widget_set_size_request(button, 150, 35);
    gtk_widget_show(button);

    gtk_widget_show (window);
}

int main (int argc, char *argv [])
{
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *button2;
    GtkWidget *vbox;
    GtkWidget *image;
    GtkWidget *image2;
    GtkWidget *fixed;

    gtk_init (&argc, &argv);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request (GTK_WIDGET (window), 800, 500);
    gtk_window_set_title (GTK_WINDOW (window), "LocData");
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
    g_signal_connect_swapped (window, "delete-event", G_CALLBACK (gtk_widget_destroy), window);

    vbox = gtk_vbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (window), vbox);

    image = gtk_image_new_from_file ("/home/filipe/Documentos/projeto/locdatalogonobg130x130.png");
    gtk_box_pack_start (GTK_BOX (vbox), image, TRUE, TRUE, 0);


    image2 = gtk_image_new_from_file("/home/filipe/Documentos/projeto/locdataname.png");
    gtk_box_pack_start (GTK_BOX (vbox), image2, TRUE, TRUE, 0);

    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(vbox), fixed);

    button = gtk_button_new_with_label ("Registre-se");
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (janela_cadastro_de_empresas), (gpointer) window);
    gtk_fixed_put(GTK_FIXED (fixed), button, 290, 50);
    gtk_widget_set_size_request (button, 200, 35);

    button2 = gtk_button_new_with_label ("Já sou registrado");
    g_signal_connect (G_OBJECT (button2), "clicked", G_CALLBACK (janela_descricao_login), (gpointer) window);
    gtk_fixed_put(GTK_FIXED (fixed), button2, 290, 100);
    gtk_widget_set_size_request (button2, 200, 35);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;

}
