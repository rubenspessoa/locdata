#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "janela_cadastro_de_clientes.h"
#include "janela_cadastro_de_empresas.h"

void janela_cadastro_de_clientes ()
{
    GtkWidget *window;
    GtkWidget *vbox, *hbox;
    GtkWidget *entry1, *entry2, *entry3, *entry4, *entry5;
    GtkWidget *button;
    GtkWidget *check;
    GtkWidget *fixed;
    GtkWidget *label;
    gint tmp_pos;

    /*criando janela*/
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
    gtk_widget_set_size_request (GTK_WIDGET (window), 600, 400);
    gtk_window_set_title (GTK_WINDOW (window), "Registro de clientes LocData");
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);

    /*criando caixa vertical*/
    vbox = gtk_vbox_new (FALSE, 10);
    gtk_container_add (GTK_CONTAINER (window), vbox);
    gtk_widget_show (vbox);

    label = gtk_label_new ("Insira abaixo o CPF do cliente");
    gtk_label_set_justify (GTK_LABEL (label), GTK_JUSTIFY_LEFT);
    gtk_box_pack_start (GTK_BOX (vbox), label, TRUE, TRUE, 0);

    entry1 = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (entry1), 100);
    g_signal_connect (entry1, "changed", G_CALLBACK (enter_callback1), entry1);
    tmp_pos = GTK_ENTRY (entry1)->text_length;
    gtk_editable_select_region (GTK_EDITABLE (entry1), 0, GTK_ENTRY (entry1)->text_length);
    gtk_box_pack_start (GTK_BOX (vbox), entry1, TRUE, TRUE, 0);
    gtk_widget_show (entry1);

    label = gtk_label_new ("Insira abaixo o nome do cliente");
    gtk_label_set_justify (GTK_LABEL (label), GTK_JUSTIFY_LEFT);
    gtk_box_pack_start (GTK_BOX (vbox), label, TRUE, TRUE, 0);

    entry2 = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (entry2), 50);
    g_signal_connect (entry2, "changed", G_CALLBACK (enter_callback2), entry2);
    tmp_pos = GTK_ENTRY (entry2)->text_length;
    gtk_editable_select_region (GTK_EDITABLE (entry2), 0, GTK_ENTRY (entry2)->text_length);
    gtk_box_pack_start (GTK_BOX (vbox), entry2, TRUE, TRUE, 0);
    gtk_widget_show (entry2);

    label = gtk_label_new ("Insira abaixo o email do cliente");
    gtk_label_set_justify (GTK_LABEL (label), GTK_JUSTIFY_LEFT);
    gtk_box_pack_start (GTK_BOX (vbox), label, TRUE, TRUE, 0);

    entry3 = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (entry3), 15);
    g_signal_connect (entry3, "changed", G_CALLBACK (enter_callback3), entry3);
    tmp_pos = GTK_ENTRY (entry3)->text_length;
    gtk_editable_select_region (GTK_EDITABLE (entry3), 0, GTK_ENTRY (entry3)->text_length);
    gtk_box_pack_start (GTK_BOX (vbox), entry3, TRUE, TRUE, 0);
    gtk_widget_show (entry3);

    label = gtk_label_new ("Insira abaixo o endereço do cliente");
    gtk_label_set_justify (GTK_LABEL (label), GTK_JUSTIFY_LEFT);
    gtk_box_pack_start (GTK_BOX (vbox), label, TRUE, TRUE, 0);

    entry4 = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (entry4), 15);
    g_signal_connect (entry4, "changed", G_CALLBACK (enter_callback3), entry4);
    tmp_pos = GTK_ENTRY (entry4)->text_length;
    gtk_editable_select_region (GTK_EDITABLE (entry4), 0, GTK_ENTRY (entry4)->text_length);
    gtk_box_pack_start (GTK_BOX (vbox), entry4, TRUE, TRUE, 0);
    gtk_widget_show (entry4);

    label = gtk_label_new ("Insira abaixo o telefone do cliente");
    gtk_label_set_justify (GTK_LABEL (label), GTK_JUSTIFY_LEFT);
    gtk_box_pack_start (GTK_BOX (vbox), label, TRUE, TRUE, 0);

    entry5 = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (entry5), 15);
    g_signal_connect (entry5, "changed", G_CALLBACK (enter_callback3), entry5);
    tmp_pos = GTK_ENTRY (entry5)->text_length;
    gtk_editable_select_region (GTK_EDITABLE (entry5), 0, GTK_ENTRY (entry5)->text_length);
    gtk_box_pack_start (GTK_BOX (vbox), entry5, TRUE, TRUE, 0);
    gtk_widget_show (entry5);

    /*criando um widget fixed*/
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(vbox), fixed);
    gtk_widget_show (fixed);

    /*criando um botão de "salvar"*/
    button = gtk_button_new_with_label ("Salvar");
    g_signal_connect (button, "clicked", G_CALLBACK (janela_cadastro), window);
    gtk_fixed_put(GTK_FIXED(fixed), button, 1, 15);
    gtk_widget_set_size_request(button, 150, 35);
    gtk_widget_show(button);

    /*mostrando todos os widgets dentro da janela*/
    gtk_widget_show_all (window);
}
