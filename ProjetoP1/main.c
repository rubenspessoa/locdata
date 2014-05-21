#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "janela_cadastro_de_empresas.h"
#include "janela_login_empresa.h"

void sobre_o_locdata (GtkWidget *wid, GtkWidget *win)
{
    GtkWidget *dialog = NULL;

    dialog = gtk_message_dialog_new (GTK_WINDOW (win), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, "O LocData nasceu de uma necessidade: tornar a busca pelo seu filme predileto mais simples.\n\nPensando nisso, Eduardo Lúcio, Filipe Falcão, Gustavo Gobbi, Matheus Sales e Rubens Pessoa se encarregaram deste desafio como nosso projeto de Programação 1 orientado pelo professor Rodrigo Paes.\n\nEnjoy!\n");
    gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
    gtk_dialog_run (GTK_DIALOG (dialog));
    gtk_widget_destroy (dialog);
}

int main (int argc, char *argv [])
{

    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *vbox;
    GtkWidget *image, *image2;
    GtkWidget *fixed;
    GtkWidget *label;

    /*iniciando o GTK*/
    gtk_init (&argc, &argv);

    /*criando janela*/
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
    gtk_widget_set_size_request (GTK_WIDGET (window), 800, 500);
    gtk_window_set_title (GTK_WINDOW (window), "LocData");
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
    g_signal_connect_swapped (window, "delete-event", G_CALLBACK (gtk_widget_destroy), window);

    /*criando caixa vertical*/
    vbox = gtk_vbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (window), vbox);

    /*inserindo imagem: logo do LocData*/
    image = gtk_image_new_from_file ("/home/filipe/Documentos/projeto/locdatalogonobg130x130.png");
    gtk_box_pack_start (GTK_BOX (vbox), image, TRUE, TRUE, 0);

    /*inserindo imagem: nome colorido do LocData*/
    image2 = gtk_image_new_from_file("/home/filipe/Documentos/projeto/locdataname.png");
    gtk_box_pack_start (GTK_BOX (vbox), image2, TRUE, TRUE, 0);

    /*criando widget fixed*/
    fixed = gtk_fixed_new ();
    gtk_container_add (GTK_CONTAINER(vbox), fixed);

    /*criando botão "registre-se"*/
    button = gtk_button_new_with_label ("Registre-se");
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (janela_cadastro_de_empresas), (gpointer) window);
    gtk_fixed_put (GTK_FIXED (fixed), button, 290, 50);
    gtk_widget_set_size_request (button, 200, 35);

    /*criando botão "já sou registrado"*/
    button = gtk_button_new_with_label ("Já sou registrado");
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (janela_login), (gpointer) window);
    gtk_fixed_put (GTK_FIXED (fixed), button, 290, 100);
    gtk_widget_set_size_request (button, 200, 35);

    button = gtk_button_new_with_label ("Sobre o LocData");
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (sobre_o_locdata), (gpointer) window);
    gtk_fixed_put (GTK_FIXED (fixed), button, 290, 150);
    gtk_widget_set_size_request (button, 200, 35);

    /*mostrando todos os widgets dentro de janela*/
    gtk_widget_show_all(window);

    /*entrando no loop main. esperando sinais do usuário*/
    gtk_main();

    return 0;

}
