#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "janela_login_empresa.h"
#include "janela_principal.h"

const gchar *entry_text_login_usuario = NULL;
const gchar *entry_text_login_senha = NULL;
char usuario_login [30];
char senha_login [15];

void enter_callback4 (GtkWidget *widget, GtkWidget *entry1)
{

    entry_text_login_usuario = gtk_entry_get_text (GTK_ENTRY (entry1));
    printf ("Usuario: %s\n", entry_text_login_usuario);

}

void enter_callback5 (GtkWidget *widget, GtkWidget *entry2)
{

    entry_text_login_senha = gtk_entry_get_text (GTK_ENTRY (entry2));
    printf ("Senha: %s\n", entry_text_login_senha);

}

void janela_login ()
{
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *fixed;
    GtkWidget *button;
    GtkWidget *label;
    GtkWidget *entry1, *entry2;
    gint tmp_pos;

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
    gtk_widget_set_size_request (GTK_WIDGET (window), 280, 210);
    gtk_window_set_title (GTK_WINDOW (window), "Login de Admin LocData");
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);

    vbox = gtk_vbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (window), vbox);
    gtk_widget_show (vbox);

    label = gtk_label_new ("Usuário:");
    gtk_label_set_justify (GTK_LABEL (label), GTK_JUSTIFY_LEFT);
    gtk_box_pack_start (GTK_BOX (vbox), label, TRUE, TRUE, 0);

    entry1 = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (entry1), 100);
    g_signal_connect (entry1, "changed", G_CALLBACK (enter_callback4), entry1);
    tmp_pos = GTK_ENTRY (entry1)->text_length;
    gtk_editable_select_region (GTK_EDITABLE (entry1), 0, GTK_ENTRY (entry1)->text_length);
    gtk_box_pack_start (GTK_BOX (vbox), entry1, TRUE, TRUE, 0);
    gtk_widget_show (entry1);

    label = gtk_label_new ("Senha:");
    gtk_label_set_justify (GTK_LABEL (label), GTK_JUSTIFY_LEFT);
    gtk_box_pack_start (GTK_BOX (vbox), label, TRUE, TRUE, 0);

    entry2 = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (entry2), 50);
    g_signal_connect (entry2, "changed", G_CALLBACK (enter_callback5), entry2);
    tmp_pos = GTK_ENTRY (entry2)->text_length;
    gtk_editable_select_region (GTK_EDITABLE (entry2), 0, GTK_ENTRY (entry2)->text_length);
    gtk_box_pack_start (GTK_BOX (vbox), entry2, TRUE, TRUE, 0);
    gtk_widget_show (entry2);

    fixed = gtk_fixed_new ();
    gtk_container_add (GTK_CONTAINER (vbox), fixed);

    button = gtk_button_new_with_label ("Entrar");
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (janela_principal), (gpointer) window);
    gtk_fixed_put (GTK_FIXED (fixed), button, 160, 10);
    gtk_widget_set_size_request (button, 100, 35);

    gtk_widget_show_all (window);
}
