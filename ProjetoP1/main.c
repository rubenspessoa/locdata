#include <stdlib.h>
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

int main (int argc, char *argv[])
{

  /*declarando os widgets que serão utilizados*/
  GtkWidget *button = NULL;
  GtkWidget *win = NULL;
  GtkWidget *vbox = NULL;

  /*iniciando o GTK*/
  /*a função gtk_init (&argc, &argv) é essencial para o funcionamente de qualquer aplicação GTK*/
  g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, (GLogFunc) gtk_false, NULL);
  gtk_init (&argc, &argv);
  g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, g_log_default_handler, NULL);

  /*criando a janela*/
  win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_container_set_border_width (GTK_CONTAINER (win), 100);
  gtk_window_set_title (GTK_WINDOW (win), "LocData");
  gtk_window_set_position (GTK_WINDOW (win), GTK_WIN_POS_CENTER);
  gtk_widget_realize (win);
  g_signal_connect (win, "destroy", gtk_main_quit, NULL);

  /*criando uma caixa vertical com botões*/
  vbox = gtk_vbox_new (TRUE, 6);
  gtk_container_add (GTK_CONTAINER (win), vbox);

  /*criando os botões e atribuindo funções a eles*/
  button = gtk_button_new_with_label ("Descição do LocData");
  g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (janela_descricao_do_locdata), (gpointer) win);
  gtk_box_pack_start (GTK_BOX (vbox), button, TRUE, TRUE, 0);

  button = gtk_button_new_with_label ("Equipe");
  g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (janela_equipe), (gpointer) win);
  gtk_box_pack_start (GTK_BOX (vbox), button, TRUE, TRUE, 0);

  button = gtk_button_new_from_stock (GTK_STOCK_CLOSE);
  g_signal_connect (button, "clicked", gtk_main_quit, NULL);
  gtk_box_pack_start (GTK_BOX (vbox), button, TRUE, TRUE, 0);

  /*iniciando o loop main() e esperando a ocorrência de um evento*/
  gtk_widget_show_all (win);
  gtk_main ();
  return 0;
}
