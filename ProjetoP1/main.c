#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "cadastros.h"
#include "gtkLocData.h"
#include "login.h"

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
    gtk_window_set_resizable (window, FALSE);
    gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
    gtk_widget_set_size_request (GTK_WIDGET (window), 800, 500);
    gtk_window_set_title (GTK_WINDOW (window), "LocData");
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
    g_signal_connect_swapped (window, "delete-event", G_CALLBACK (gtk_widget_destroy), window);

    fixed = gtk_fixed_new ();
    gtk_container_add (GTK_CONTAINER(window), fixed);

    image = gtk_image_new_from_file ("ldlogo4.png");
    gtk_fixed_put (GTK_FIXED (fixed), image, 288, 70);

    /*criando botão "registre-se"*/
    button = gtk_button_new_with_label ("Registre-se");
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (janela_cadastro_de_empresas), (gpointer) window);
    gtk_fixed_put (GTK_FIXED (fixed), button, 290, 300);
    gtk_widget_set_size_request (button, 200, 35);

    /*criando botão "já sou registrado"*/
    button = gtk_button_new_with_label ("Já sou registrado");
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (janela_login), (gpointer) window);
    gtk_fixed_put (GTK_FIXED (fixed), button, 290, 350);
    gtk_widget_set_size_request (button, 200, 35);

    button = gtk_button_new_with_label ("Sobre o LocData");
    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (sobre_o_locdata), (gpointer) window);
    gtk_fixed_put (GTK_FIXED (fixed), button, 290, 400);
    gtk_widget_set_size_request (button, 200, 35);

    /*mostrando todos os widgets dentro de janela*/
    gtk_widget_show_all(window);

    /*entrando no loop main. esperando sinais do usuário*/
    gtk_main();

    return 0;

}
