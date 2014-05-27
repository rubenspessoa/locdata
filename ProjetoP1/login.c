#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "gtkLocData.h"
#include "cadastros.h"
#include "login.h"

void validacao_login (GtkWidget *wid, GtkWidget *win)
{
    if (entry_text_login_usuario == NULL || entry_text_login_senha == NULL || strcmp (entry_text_login_usuario, "\0") == 0 || strcmp (entry_text_login_senha, "\0") == 0)
    {
        dialog_err_entry_vazio(wid, win);
    }
    else
    {
        sqlite3 *db;
        int rc;
        char sql[300];
        const char* data = "Callback function called";
        char *zErrMsg = 0;

        strcpy (usuario_login, entry_text_login_usuario);
        strcpy (senha_login, entry_text_login_senha);

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

        sprintf (sql, "SELECT * from ADMIN WHERE ADMIN LIKE ('%s%') AND SENHA LIKE ('%s%');", usuario_login, senha_login);

        rc = sqlite3_exec(db, sql, callback_visualizar_dados, (void*)data, &zErrMsg);

        janela_principal (wid, win);

    }
}
