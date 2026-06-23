#ifdef _WIN32
    #include <curses.h> 
#elif __linux__
    #include <ncurses.h>
#else
    #error "Sistema operacional nao suportado para esta biblioteca."
#endif

#include "Controladoras/CrtlApresentacaoBacklog.hpp"
#include "Tui/tui.hpp"
#include <stdexcept>
#include <cstring>

void CrtlApresentacaoBacklog::executar(const Email& emailLogado) {

    WINDOW* win = criarJanelaBacklog();

    while (true) {
        
        desenharLayout(win);
        
    }
    
    delwin(win);
    return ;
}


WINDOW* CrtlApresentacaoBacklog::criarJanelaBacklog() {
    int altura = 10, largura = 50;
    int startY = (LINES - altura) / 2;
    int startX = (COLS - largura) / 2;

    WINDOW* win = newwin(altura, largura, startY, startX);
    keypad(win, TRUE);

    //wbkgd(win, COLOR_PAIR(4)); desenha dentro da caxinha
    return win;
}

void CrtlApresentacaoBacklog::desenharLayout(WINDOW* win) {
    werase(win);
    box(win, 0, 0);
    
    wattron(win, COLOR_PAIR(1));
    mvwprintw(win, 0, (50 - 17) / 2, " ACOES DE BACKLOG "); // 50 é a largura fixa
    wattroff(win, COLOR_PAIR(1));

    mvwprintw(win, 3, 5, "Email: ");
    mvwprintw(win, 5, 5, "Senha: ");
    mvwprintw(win, 8, 2, "(Pressione ESC para cancelar e sair)");
    wrefresh(win);
}

bool CrtlApresentacaoBacklog::capturarCredenciais(WINDOW* win, char* emailStr, char* senhaStr) {
    wmove(win, 3, 13);
    wrefresh(win);
    if (!Tui::lerEntradaTerminal(win, emailStr, 79, false)) return false;

    wmove(win, 5, 13); // move o campo para digitar
    wrefresh(win); // atualiza
    if (!Tui::lerEntradaTerminal(win, senhaStr, 29, true)) return false;

    return true;
}

void CrtlApresentacaoBacklog::exibirErro(WINDOW* win, const char* mensagem) {
    wattron(win, COLOR_PAIR(2));
    mvwprintw(win, 8, 2, "Erro: %s", mensagem);
    wattroff(win, COLOR_PAIR(2));
    wrefresh(win);
    wgetch(win); // Pausa para o usuário ler
}

void CrtlApresentacaoBacklog::exibirSucesso(WINDOW* win) {
    wattron(win, COLOR_PAIR(3));
    mvwprintw(win, 8, 2, "Sucesso! Entrando no sistema...");
    wattroff(win, COLOR_PAIR(3));
    wrefresh(win);
    //wgetch(win);
    napms(1500); // Pausa automática
}