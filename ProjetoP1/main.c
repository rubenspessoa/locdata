#include <gtk/gtk.h>

/*janela_descrição_do_locdata*/
/*esta função abrirá uma caixa de dialogo e "printará" a string digitada*/
static void janela_descricao_do_locdata (GtkWidget *wid, GtkWidget *win)
{
  GtkWidget *dialog = NULL;

  dialog = gtk_message_dialog_new (GTK_WINDOW (win), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, "Este é o LocData!\nSeja bem-vindo usuário!\nEssa é sua primeira interação com o alpha do LocData.\nEm breve estaremos disponibilizando o programa completo e operacional.\nAguarde!\n");
  gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
  gtk_dialog_run (GTK_DIALOG (dialog));
  gtk_widget_destroy (dialog);
}

/*janela_equipe*/
/*esta função funciona da mesma forma que a função acima*/
/*abrirá uma caixa de dialogo e "pritará" a string digitada*/
static void janela_equipe (GtkWidget *wid, GtkWidget *win)
{
  GtkWidget *dialog = NULL;

  dialog = gtk_message_dialog_new (GTK_WINDOW (win), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, "Eduardo Lúcio\nFilipe Falcão\nGustavo Gobbi\nMatheus Sales\nRubens Pessoa\n");
  gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
  gtk_dialog_run (GTK_DIALOG (dialog));
  gtk_widget_destroy (dialog);
}

static void janela_descricao_do_gtk (GtkWidget *wid, GtkWidget *win)
{
  GtkWidget *dialog = NULL;

  dialog = gtk_message_dialog_new (GTK_WINDOW (win), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, "O GTK+ 2 é um toolkit multi-plataforma para a criação de interfaces gráficas.\nÉ licenciado sob a licença GNU LGPL, permitindo que software proprietários e livres o utilizem em sua construção.\nÉ software livre e integra o projeto GNU.\nFoi desenvolvido inicialmente para o GIMP, por isso foi batizado de GIMP toolkit, com abreviação GTK+.\nFoi desenvolvido originalmente por Peter Mattis, Spencer Kimball e Josh MacDonald2.\nO GTK+ é muito popular, sendo usado em um grande número de aplicações e no ambiente de desktop GNOME (que por sua vez também é muito popular).\n");
  gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
  gtk_dialog_run (GTK_DIALOG (dialog));
  gtk_widget_destroy (dialog);
}

static void janela_porque_o_gtk (GtkWidget *wid, GtkWidget *win)
{
  GtkWidget *dialog = NULL;

  dialog = gtk_message_dialog_new (GTK_WINDOW (win), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, "Além de se tratar de um software livre, o GTK é essencialmente uma interface de programação de aplicativos orientada a objetos.\nEmbora completamente escrita em C, é implementada usando a idéia de classes e funções callback (ponteiros para funções).\nImpressionante!\n");
  gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
  gtk_dialog_run (GTK_DIALOG (dialog));
  gtk_widget_destroy (dialog);
}

int main( int argc, char *argv[])
{
  GtkWidget *window;
  GtkWidget *fixed;
  GtkWidget *frame1;

  GtkWidget *button1;
  GtkWidget *button2;
  GtkWidget *button3;
  GtkWidget *button4;
  GtkWidget *button5;

  gtk_init(&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Projeto de P1");

  /* Here we connect the "destroy" event to a signal handler */
  g_signal_connect (window, "destroy",
		    G_CALLBACK (gtk_main_quit), NULL);

  gtk_widget_set_size_request (window, 450, 280);
  /* Sets the border width of the window. */
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);
  g_signal_connect (window, "destroy", gtk_main_quit, NULL);

  frame1 = gtk_frame_new(NULL);
  gtk_container_add (GTK_CONTAINER (window), frame1);

  /* Set the frame's label */
  gtk_frame_set_label (GTK_FRAME (frame1), "Primeira apresentação do projeto de P1\nAqui serão apresentadas informações sobre o LocData e o GTK\n\nO LocData:                                                         O GTK:");

  /* Align the label at the right of the frame */
  gtk_frame_set_label_align (GTK_FRAME (frame1), 0.0, 0.0);

  /* Set the style of the frame */
  gtk_frame_set_shadow_type (GTK_FRAME (frame1), GTK_SHADOW_ETCHED_OUT);


  fixed = gtk_fixed_new();
  gtk_container_add(GTK_CONTAINER(frame1), fixed);

  button1 = gtk_button_new_with_label("Sobre o LocData");
  g_signal_connect (G_OBJECT (button1), "clicked", G_CALLBACK (janela_descricao_do_locdata), (gpointer) window);
  gtk_fixed_put(GTK_FIXED(fixed), button1, 10, 30);
  gtk_widget_set_size_request(button1, 150, 35);

  button2 = gtk_button_new_with_label("Equipe desenvolvedora");
  g_signal_connect (G_OBJECT (button2), "clicked", G_CALLBACK (janela_equipe), (gpointer) window);
  gtk_fixed_put(GTK_FIXED(fixed), button2, 10, 80);
  gtk_widget_set_size_request(button2, 200, 35);

  button3 = gtk_button_new_with_label("Sobre o GTK");
  g_signal_connect (G_OBJECT (button3), "clicked", G_CALLBACK (janela_descricao_do_gtk), (gpointer) window);
  gtk_fixed_put(GTK_FIXED(fixed), button3, 260, 30);
  gtk_widget_set_size_request(button3, 120, 35);

  button4 = gtk_button_new_with_label("Porque o GTK?");
  g_signal_connect (G_OBJECT (button4), "clicked", G_CALLBACK (janela_porque_o_gtk), (gpointer) window);
  gtk_fixed_put(GTK_FIXED(fixed), button4, 260, 80);
  gtk_widget_set_size_request(button4, 135, 35);

  button5 = gtk_button_new_with_label("Sair");
  g_signal_connect (button5, "clicked", gtk_main_quit, NULL);
  gtk_fixed_put(GTK_FIXED(fixed), button5, 140, 140);
  gtk_widget_set_size_request(button5, 135, 35);

  g_signal_connect_swapped(G_OBJECT(window), "destroy",
      G_CALLBACK(gtk_main_quit), NULL);

  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}
