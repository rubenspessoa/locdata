#include <gtk/gtk.h>

/* Nosso novo callback melhorado. Dados passados a essa função
* são impressos na stdout. */
static void callback( GtkWidget *widget,
                      gpointer   data )
{
    g_print ("Hello again - %s foi pressionado\n", (gchar *) data);
}

/* Outra callback */
static gboolean delete_event( GtkWidget *widget,
                              GdkEvent  *event,
                              gpointer   data )
{
    gtk_main_quit ();
    return FALSE;
}

int main( int   argc,
          char *argv[] )
{
    /* GtkWidget é o tipo de dado para widgets */
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *box1;

    /* Esta função é chamada em todas as aplicações GTK. Argumentos da linha
     * de comando são interpretados e retornados à aplicação.*/
    gtk_init (&argc, &argv);

    /* Cria uma nova janela */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    /* Esta é uma nova chamada, que apenas muda o título da nossa
     * nova janela para "Hello Buttons!"*/
    gtk_window_set_title (GTK_WINDOW (window), "Hello Buttons!");

    /* Aqui nós apenas ajustamos um tratador para delete_event que imediatamente
     * sai do GTK. */
    g_signal_connect (G_OBJECT (window), "delete_event",
                      G_CALLBACK (delete_event), NULL);

    /* Ajusta a largura da borda da janela. */
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);

    /* Nós criamos uma caixa para empacotar widgets nela. Descreveremos isso em detalhes
     * na sessão de "empacotamento". A caixa não é realmente visível, ela
     * é apenas utilizada como um instrumento para arranjar widgets. */
    box1 = gtk_hbox_new (FALSE, 0);

    /* Coloca a caixa na janela principal. */
    gtk_container_add (GTK_CONTAINER (window), box1);

    /* Cria um novo botão com o rótulo "Button 1". */
    button = gtk_button_new_with_label ("Button 1");

    /* Agora quando o botão é clicado, chamamos a função "callback"
     * com um apontador para "button 1" como argumento */
    g_signal_connect (G_OBJECT (button), "clicked",
                      G_CALLBACK (callback), (gpointer) "button 1");

    /* Ao invés de gtk_container_add nós empacotamos o botão na caixa invisível
     * que foi colocada na janela. */
    gtk_box_pack_start (GTK_BOX(box1), button, TRUE, TRUE, 0);

    /* Sempre se lembre deste passo, ele diz a GTK que nosso preparo para
     * o botão esta completo, e ele pode ser exibido. */
    gtk_widget_show (button);

    /* Execute os mesmos passos para o segundo botão */
    button = gtk_button_new_with_label ("Button 2");

    /* Chame a mesma função callback com um argumento diferente,
     * passando um apontador para o "button 2" dessa vez. */
    g_signal_connect (G_OBJECT (button), "clicked",
                      G_CALLBACK (callback), (gpointer) "button 2");

    gtk_box_pack_start(GTK_BOX (box1), button, TRUE, TRUE, 0);

    /* A ordem em que os botões são exibidos não é realmente importante, mas eu
     * recomento mostrar a janela por último, assim todos aparecem de uma vez. */
    gtk_widget_show (button);

    gtk_widget_show (box1);

    gtk_widget_show (window);

    /* Descanse em gtk_main e espere a diversão começar! */
    gtk_main ();

    return 0;
}

