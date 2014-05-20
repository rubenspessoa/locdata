#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

/*variáveis globais*/
const gchar *entry_text1 = NULL;
const gchar *entry_text2 = NULL;
const gchar *entry_text3 = NULL;
char empresa [100];
char usuario [100];
char senha [15];
char sqlite_db [500];

/*funçoes que "pegam" um texto digitado e imprimem no terminal*/
static void enter_callback1 (GtkWidget *widget, GtkWidget *entry1)
{

    entry_text1 = gtk_entry_get_text (GTK_ENTRY (entry1));
    printf ("Empresa: %s\n", entry_text1);

}

static void enter_callback2 (GtkWidget *widget, GtkWidget *entry2)
{

    entry_text2 = gtk_entry_get_text (GTK_ENTRY (entry2));
    printf ("Usuario: %s\n", entry_text2);

}

static void enter_callback3 (GtkWidget *widget, GtkWidget *entry3)
{

    entry_text3 = gtk_entry_get_text (GTK_ENTRY (entry3));
    printf ("Senha: %s\n", entry_text3);

}

/*função que gerencia a visualização da senha*/
static void entry_toggle_visibility (GtkWidget *checkbutton, GtkWidget *entry)
{

  gtk_entry_set_visibility (GTK_ENTRY (entry), GTK_TOGGLE_BUTTON (checkbutton)->active);

}

/*funçao de caixa de dialogo*/
void janela_descricao_login (GtkWidget *wid, GtkWidget *win)
{
    GtkWidget *dialog = NULL;

    dialog = gtk_message_dialog_new (GTK_WINDOW (win), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, "Em breve, login de administrador!\n");
    gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
    gtk_dialog_run (GTK_DIALOG (dialog));
    gtk_widget_destroy (dialog);
}

/*função de registro de dados SQLite3*/
static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    int i;

    for(i = 0; i < argc; i ++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");

    return 0;
}

static int callback_visualizar_dados(void *data, int argc, char **argv, char **azColName)
{
    int i;
    fprintf(stderr, "%s: ", (const char*)data);

    for(i = 0; i < argc; i ++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");

    return 0;
}

/*função chamada pelo botão "salvar"*/
void janela_cadastro (GtkWidget *wid, GtkWidget *win)
{

    /*caso nada tenha sido digitado em algum campo*/
    /*uma caixa de diálogo pede para que o preenchimento seja completo*/
    if (entry_text1 == NULL || entry_text2 == NULL || entry_text3 == NULL)
    {
        GtkWidget *dialog = NULL;

        dialog = gtk_message_dialog_new (GTK_WINDOW (win), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, "Por favor, preencha todos os campos.\n");
        gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
        gtk_dialog_run (GTK_DIALOG (dialog));
        gtk_widget_destroy (dialog);
    }
    /*caso todos os campos tenham sido preenchidos*/
    /*as strings lidas são salvas no DB*/
    else
    {
        strcpy (empresa, entry_text1);
        strcpy (usuario, entry_text2);
        strcpy (senha, entry_text3);

        sqlite3 *db;
        char *zErrMsg = 0;
        int rc;
        char sql[300];
        const char* data = "Callback function called";

        rc = sqlite3_open("test.db", &db);
        if(rc)
        {
            fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
            exit(0);
        }
        else
        {
            fprintf(stderr, "Banco de Dados iniciado com sucesso\n");
        }

        sprintf (sql, "INSERT INTO CADASTRO_LOCDATA_EMPRESAS ( EMPRESA,ADMIN,SENHA ) VALUES ( '%s', '%s', '%s' );", empresa, usuario, senha);

        rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

        if(rc != SQLITE_OK)
        {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
        }
        else
        {
            fprintf(stdout, "Dados gravados com sucesso\n");
        }

        sprintf (sql, "SELECT * from CADASTRO_LOCDATA_EMPRESAS;");

        rc = sqlite3_exec(db, sql, callback_visualizar_dados, (void*)data, &zErrMsg);
        if( rc != SQLITE_OK )
        {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
        }
        else
        {
            fprintf(stdout, "Operation done successfully\n");
        }

        sqlite3_close(db);

        GtkWidget *dialog = NULL;

        dialog = gtk_message_dialog_new (GTK_WINDOW (win), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, "Seus dados foram salvos com sucesso.\n");
        gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
        gtk_dialog_run (GTK_DIALOG (dialog));
        gtk_widget_destroy (dialog);
    }

}

/*função que apresenta uma janela com caixas de texto e um botão*/
void janela_cadastro_de_empresas ()
{

    GtkWidget *window;
    GtkWidget *vbox, *hbox;
    GtkWidget *entry1;
    GtkWidget *entry2;
    GtkWidget *entry3;
    GtkWidget *button;
    GtkWidget *check;
    GtkWidget *fixed;
    GtkWidget *label;
    gint tmp_pos;

    /*criando janela*/
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
    gtk_widget_set_size_request (GTK_WIDGET (window), 500, 300);
    gtk_window_set_title (GTK_WINDOW (window), "Registro de empresa LocData");
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);

    /*criando caixa vertical*/
    vbox = gtk_vbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (window), vbox);
    gtk_widget_show (vbox);

    label = gtk_label_new ("Insira abaixo o nome da sua empresa.");
    gtk_label_set_justify (GTK_LABEL (label), GTK_JUSTIFY_LEFT);
    gtk_box_pack_start (GTK_BOX (vbox), label, TRUE, TRUE, 0);

    /*criando três caixas de texto e três labels*/
    entry1 = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (entry1), 100);
    g_signal_connect (entry1, "changed", G_CALLBACK (enter_callback1), entry1);
    tmp_pos = GTK_ENTRY (entry1)->text_length;
    gtk_editable_select_region (GTK_EDITABLE (entry1), 0, GTK_ENTRY (entry1)->text_length);
    gtk_box_pack_start (GTK_BOX (vbox), entry1, TRUE, TRUE, 0);
    gtk_widget_show (entry1);

    label = gtk_label_new ("Insira abaixo o nome de usuário Admin.");
    gtk_label_set_justify (GTK_LABEL (label), GTK_JUSTIFY_LEFT);
    gtk_box_pack_start (GTK_BOX (vbox), label, TRUE, TRUE, 0);

    entry2 = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (entry2), 50);
    g_signal_connect (entry2, "changed", G_CALLBACK (enter_callback2), entry2);
    tmp_pos = GTK_ENTRY (entry2)->text_length;
    gtk_editable_select_region (GTK_EDITABLE (entry2), 0, GTK_ENTRY (entry2)->text_length);
    gtk_box_pack_start (GTK_BOX (vbox), entry2, TRUE, TRUE, 0);
    gtk_widget_show (entry2);

    label = gtk_label_new ("Insira abaixo a sua senha de usuário Admin.");
    gtk_label_set_justify (GTK_LABEL (label), GTK_JUSTIFY_LEFT);
    gtk_box_pack_start (GTK_BOX (vbox), label, TRUE, TRUE, 0);

    entry3 = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (entry3), 15);
    g_signal_connect (entry3, "changed", G_CALLBACK (enter_callback3), entry3);
    tmp_pos = GTK_ENTRY (entry3)->text_length;
    gtk_editable_select_region (GTK_EDITABLE (entry3), 0, GTK_ENTRY (entry3)->text_length);
    gtk_box_pack_start (GTK_BOX (vbox), entry3, TRUE, TRUE, 0);
    gtk_widget_show (entry3);

    /*criando um caixa vertical*/
    hbox = gtk_hbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (vbox), hbox);
    gtk_widget_show (hbox);

    /*criando um botão "toogle" de seleção*/
    check = gtk_check_button_new_with_label ("Visualizar senha");
    gtk_box_pack_start (GTK_BOX (hbox), check, TRUE, TRUE, 0);
    g_signal_connect (check, "toggled", G_CALLBACK (entry_toggle_visibility), entry3);
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (check), TRUE);
    gtk_widget_show (check);

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

int main (int argc, char *argv [])
{

    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *button2;
    GtkWidget *vbox;
    GtkWidget *image;
    GtkWidget *image2;
    GtkWidget *fixed;

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
    button2 = gtk_button_new_with_label ("Já sou registrado");
    g_signal_connect (G_OBJECT (button2), "clicked", G_CALLBACK (janela_descricao_login), (gpointer) window);
    gtk_fixed_put(GTK_FIXED (fixed), button2, 290, 100);
    gtk_widget_set_size_request (button2, 200, 35);

    /*mostrando todos os widgets dentro de janela*/
    gtk_widget_show_all(window);

    /*entrando no loop main. esperando sinais do usuário*/
    gtk_main();

    return 0;

}
