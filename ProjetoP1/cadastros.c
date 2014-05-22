#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "gtkLocData.h"

// VARIAVEIS GLOBAIS DO CADASTRO DE FILMES
char nome_filme_aux[200];
char genero_filme_aux[200];
char ano_filme_aux[200];
char sqlite_db [500];

// VARIAVEIS GLOBAIS DO CADASTRO DE EMPRESA

char empresa [200];
char usuario [200];
char senha [200];

void cadastro_de_filmes(GtkWidget *widget, GtkWidget *win) {

    if (nome_filme == NULL || genero_filme == NULL || ano_filme == NULL) {

        // FUNCAO DE ERRO: ALGUMA ENTRADA VAZIA
        dialog_err_entry_vazio(widget, win);

    } else {

        strcpy(nome_filme_aux, nome_filme);
        strcpy(genero_filme_aux, genero_filme);
        strcpy(ano_filme_aux, ano_filme);

        if ((strcmp(nome_filme_aux, "") == 0) || (strcmp(genero_filme_aux, "") == 0) || (strcmp(ano_filme_aux, "") == 0) ) {

            // FUNCAO DE ERRO: ALGUMA ENTRADA VAZIA
            dialog_err_entry_vazio(widget, win);

        } else {
            sqlite3 *db;
            char *zErrMsg = 0;
            int rc;
            char sql[300];
            const char* data = "Callback function called";

            rc = sqlite3_open("test.db", &db);

            if (rc) {
                fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
                exit(0);
            } else {
                fprintf(stderr, "Banco de Dados iniciado com sucesso\n");
            }

            sprintf (sql, "INSERT INTO FILMES(NOME, GENERO, ANO) VALUES('%s','%s','%s');", nome_filme_aux, genero_filme_aux, ano_filme_aux);

            rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

            if (rc != SQLITE_OK) {
                fprintf(stderr, "SQL error: %s\n", zErrMsg);
                sqlite3_free(zErrMsg);
            }  else {
                fprintf(stdout, "Dados gravados com sucesso em FILMES\n");
            }

            sprintf (sql, "SELECT * from FILMES;");

            rc = sqlite3_exec(db, sql, callback_visualizar_dados, (void*)data, &zErrMsg);

            if (rc != SQLITE_OK) {
                fprintf(stderr, "SQL error: %s\n", zErrMsg);
                sqlite3_free(zErrMsg);
            } else {
                fprintf(stdout, "Operation done successfully\n");
            }

            GtkWidget *dialog = NULL;

            dialog = gtk_message_dialog_new (GTK_WINDOW (win), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, "Seus dados foram salvos com sucesso.\n");
            gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
            gtk_dialog_run (GTK_DIALOG (dialog));
            gtk_widget_destroy (dialog);

            sqlite3_close(db);

        }
    }
}

void cadastro_de_empresas (GtkWidget *wid, GtkWidget *win) {

    if (entry_text_cadastro_empresa == NULL || entry_text_cadastro_usuario == NULL || entry_text_cadastro_senha == NULL || strcmp (entry_text_cadastro_empresa, "") == 0 || strcmp (entry_text_cadastro_usuario, "") == 0 || strcmp (entry_text_cadastro_senha, "") == 0) {
        dialog_err_entry_vazio(wid, win);
    }

    else
    {
        strcpy (empresa, entry_text_cadastro_empresa);
        strcpy (usuario, entry_text_cadastro_usuario);
        strcpy (senha, entry_text_cadastro_senha);

        sqlite3 *db;
        char *zErrMsg = 0;
        int rc;
        char *sql;
        const char* data = "Callback function called";

        rc = sqlite3_open("test.db", &db);

        if(rc) {
            fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
            exit(0);
        } else {
            fprintf(stderr, "Banco de Dados iniciado com sucesso\n");
        }

        sql = "CREATE TABLE ADMIN("  \
         "EMPRESA           TEXT    NOT NULL," \
         "ADMIN             TEXT     NOT NULL," \
         "SENHA             TEXT);";

        rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

        if(rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
        } else {
            fprintf(stdout, "Table created successfully\n");
        }

        sql = "CREATE TABLE FILMES("  \
         "NOME           TEXT     NOT NULL," \
         "GENERO         TEXT," \
         "ANO            TEXT);";

        rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

        if(rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
        } else {
            fprintf(stdout, "Table created successfully\n");
        }

        sprintf (sql, "INSERT INTO ADMIN(EMPRESA, ADMIN, SENHA) VALUES('%s','%s','%s');", empresa, usuario, senha);

        rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

        if(rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
        } else {
            fprintf(stdout, "Dados gravados com sucesso\n");
        }

        sprintf (sql, "SELECT * from ADMIN;");

        rc = sqlite3_exec(db, sql, callback_visualizar_dados, (void*)data, &zErrMsg);
        if( rc != SQLITE_OK ) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
        } else {
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



