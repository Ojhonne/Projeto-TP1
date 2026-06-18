
#ifdef _WIN32
    #include <curses.h> 
#elif __linux__
    #include <ncurses.h>
#else
    #error "Sistema operacional nao suportado para esta biblioteca."
#endif

#include "Controladoras/CrtlApresentacaoLogin.hpp"
#include "Tui/tui.hpp"
#include <stdexcept>
#include <cstring>


bool CrtlApresentacaoLogin::executar(Email& emailLogado) {
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
    char emailStr[80], senhaStr[30]; // buffer para leitura de email e senha

    while (!autenticado) {
        werase(win);
        box(win, 0, 0);
        
        wattron(win, COLOR_PAIR(1));
        mvwprintw(win, 0, (largura - 17) / 2, " LOGIN SISTEMA ");
        wattroff(win, COLOR_PAIR(1));

        mvwprintw(win, 3, 5, "Email: ");
        mvwprintw(win, 5, 5, "Senha: ");
        mvwprintw(win, 8, 2, "(Pressione ESC para cancelar e sair)");
        wrefresh(win);

        //captura de email
        wmove(win, 3, 13);
        wrefresh(win);
        if (!Tui::lerEntradaTerminal(win, emailStr, 79, false)) {
            break; 
        }

        // captura de senha
        wmove(win, 5, 13);
        wrefresh(win);
        if (!Tui::lerEntradaTerminal(win, senhaStr, 29, true)) {
            break; 
        }

        mvwprintw(win, 8, 2, "                                      ");
        wrefresh(win);

        try {
            Email emailLocal(emailStr);
            Senha senhaLocal(senhaStr);

            autenticado = servicoAutenticacao->autenticarPessoa(emailLocal, senhaLocal);
            if(autenticado){
                emailLogado = emailLocal; // passar o email do usuário autenticado por referência

                wattron(win, COLOR_PAIR(3));
                mvwprintw(win, 8, 2, "Sucesso! Entrando no sistema...");
                wattroff(win, COLOR_PAIR(3));
                wrefresh(win);
                napms(1500); // tempo para o usuário ler a mensagem
            }
            if (!autenticado) {
                wattron(win, COLOR_PAIR(2));
                mvwprintw(win, 8, 2, "Credenciais invalidas! Tente novamente.");
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
    return autenticado;
}