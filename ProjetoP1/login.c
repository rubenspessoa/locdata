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
        janela_principal(wid, win);
    }
}
