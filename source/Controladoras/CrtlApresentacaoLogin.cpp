#include "Controladoras/CrtlApresentacaoLogin.hpp"
#include <iostream>
#include <stdexcept>
#include <cstring>

bool CntrApresentacaoLogin::autenticar(const Email&) {
    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    // Definição das cores
    init_pair(1, COLOR_WHITE, COLOR_BLUE); // Título
    init_pair(2, COLOR_RED, COLOR_BLACK);  // Erro
    init_pair(3, COLOR_GREEN, COLOR_BLACK); // Sucesso

    // Dimensões da janela centralizada
    int altura = 10, largura = 50;
    int startY = (LINES - altura) / 2;
    int startX = (COLS - largura) / 2;

    WINDOW *win = newwin(altura, largura, startY, startX);
    box(win, 0, 0); // Desenha borda na janela
    keypad(win, TRUE);

    bool autenticado{false};
    char emailStr[80], senhaStr[30];

    while (!autenticado) {
        werase(win);
        box(win, 0, 0);
        
        wattron(win, COLOR_PAIR(1));
        mvwprintw(win, 0, (largura - 17) / 2, " LOGIN SISTEMA ");
        wattroff(win, COLOR_PAIR(1));

        mvwprintw(win, 3, 5, "Email: ");
        mvwprintw(win, 5, 5, "Senha: ");
        wrefresh(win);

        // Captura o email
        echo(); // habilita o echo para o email
        mvwgetnstr(win, 3, 13, emailStr, 79);
        noecho(); //desliga o echo para a senha

        // Captura a senha (mascarada)
        mvwgetnstr(win, 5, 13, senhaStr, 29);

        try {
            Email emailLocal(emailStr);
            Senha senhaLocal(senhaStr);

            autenticado = servicoAutenticacao->autenticarPessoa(emailLocal, senhaLocal);
            if(autenticado){
                wattron(win, COLOR_PAIR(3));
                mvwprintw(win, 8, 2, "Sucesso! Entrando no sistema...");
                wattroff(win, COLOR_PAIR(3));
                wrefresh(win);
                napms(1500); // tempo  para o usuário ler a mensagem
            }
            if (!autenticado) {
                wattron(win, COLOR_PAIR(2));
                mvwprintw(win, 8, 2, "Credenciais invalidas!");
                wattroff(win, COLOR_PAIR(2));
                wrefresh(win);
                wgetch(win);
            }
        } 
        catch (const std::invalid_argument& e) {
            wattron(win, COLOR_PAIR(2));
            mvwprintw(win, 8, 2, "Erro: %s", e.what());
            wattroff(win, COLOR_PAIR(2));
            wrefresh(win);
            wgetch(win);
        }
    }

    delwin(win);
    endwin();
    return autenticado;
}