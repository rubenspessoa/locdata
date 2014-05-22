#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "cadastros.h"
#include "gtkLocData.h"

const gchar *entry_text_busca = NULL;
char busca [50];

void enter_callback_busca (GtkWidget *widget, GtkWidget *entry_busca) {

    entry_text_busca = gtk_entry_get_text (GTK_ENTRY (entry_busca));
    printf ("Buscando: %s\n", entry_text_busca);

}

void janela_principal () {
    GtkWidget *window = NULL;
    GtkWidget *hbox;
    GtkWidget *vbox, *vbox2, *vbox3;
    GtkWidget *frame;
    GtkWidget *label;
    GtkWidget *button;
    GtkWidget *fixed;
    GtkWidget *entry_busca;
    gint tmp_pos;

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Pesquisa");
    gtk_widget_set_size_request (GTK_WIDGET (window), 600, 310);
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);

    vbox = gtk_vbox_new (FALSE, 5);

    hbox = gtk_hbox_new (FALSE, 5);
    gtk_container_add (GTK_CONTAINER (window), hbox);
    gtk_box_pack_start (GTK_BOX (hbox), vbox, FALSE, FALSE, 0);
    gtk_container_set_border_width (GTK_CONTAINER (window), 5);

    frame = gtk_frame_new ("Administrador");
    gtk_box_pack_start (GTK_BOX (vbox), frame, FALSE, FALSE, 0);

    vbox2 = gtk_vbox_new (FALSE, 15);
    gtk_container_add (GTK_CONTAINER (frame), vbox2);

    label = gtk_label_new ("\n  Registre filmes e clientes, efetue \n  locações e devoluções!  ");
    gtk_container_add (GTK_CONTAINER (vbox2), label);

    fixed = gtk_fixed_new ();
    gtk_container_add (GTK_CONTAINER(vbox2), fixed);

    button = button = gtk_button_new_with_label ("Locação");
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (janela_cadastro_de_empresas), (gpointer) window);
    gtk_fixed_put (GTK_FIXED (fixed), button, 10, 17);
    gtk_widget_set_size_request (button, 200, 42);

    button = button = gtk_button_new_with_label ("Devolução");
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (janela_cadastro_de_empresas), (gpointer) window);
    gtk_fixed_put (GTK_FIXED (fixed), button, 10, 77);
    gtk_widget_set_size_request (button, 200, 42);

    button = button = gtk_button_new_with_label ("Cadastros");
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (janela_cadastro_de_clientes), (gpointer) window);
    gtk_fixed_put (GTK_FIXED (fixed), button, 10, 137);
    gtk_widget_set_size_request (button, 200, 42);

    label = gtk_label_new ("");
    gtk_container_add (GTK_CONTAINER (vbox2), label);

    vbox = gtk_vbox_new (FALSE, 25);
    gtk_box_pack_start (GTK_BOX (hbox), vbox, FALSE, FALSE, 0);
    frame = gtk_frame_new ("Pesquisa");
    gtk_box_pack_start (GTK_BOX (vbox), frame, FALSE, FALSE, 0);

    vbox2 = gtk_vbox_new (FALSE, 15);
    gtk_container_add (GTK_CONTAINER (frame), vbox2);

    label = gtk_label_new ("\n  Encontre aqui de maneira rápida e precisa o que \n  você busca!  \n");
    gtk_container_add (GTK_CONTAINER (vbox2), label);

    entry_busca = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (entry_busca), 100);
    g_signal_connect (entry_busca, "changed", G_CALLBACK (enter_callback_busca), entry_busca);
    tmp_pos = GTK_ENTRY (entry_busca)->text_length;
    gtk_editable_select_region (GTK_EDITABLE (entry_busca), 0, GTK_ENTRY (entry_busca)->text_length);
    gtk_box_pack_start (GTK_BOX (vbox2), entry_busca, TRUE, TRUE, 0);
    gtk_widget_show (entry_busca);

    label = gtk_label_new ("\n\n\n\n\n\n\n\n");
    gtk_container_add (GTK_CONTAINER (vbox2), label);

    gtk_widget_show_all (window);

}
