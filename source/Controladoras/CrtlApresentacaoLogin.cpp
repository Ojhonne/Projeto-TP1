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
    inicializarCores();
    WINDOW* win = criarJanelaLogin();
    
    bool autenticado{false};
    char emailStr[80], senhaStr[30]; // tamanho do buffer para capturar

    while (!autenticado) {
        desenharLayout(win);

        // Se o usuário pressionar ESC, o método retorna false e interrompe o fluxo
        if (!capturarCredenciais(win, emailStr, senhaStr)) {
            break; 
        }

        // Limpa a linha de instruções antes de processar
        mvwprintw(win, 8, 2, "                                      ");
        wrefresh(win);

        try {
            Email emailLocal(emailStr);
            Senha senhaLocal(senhaStr);

            autenticado = servicoAutenticacao->autenticarPessoa(emailLocal, senhaLocal);
            
            if (autenticado) {
                emailLogado = emailLocal;
                exibirSucesso(win);
            } else {
                exibirErro(win, "Credenciais invalidas! Tente novamente.");
            }
        } 
        catch (const std::invalid_argument& e) {
            exibirErro(win, e.what());
        }
    }
    
    delwin(win);
    return autenticado;
}

void CrtlApresentacaoLogin::inicializarCores() {
    init_pair(1, COLOR_WHITE, COLOR_BLUE);  // Título
    init_pair(2, COLOR_RED, COLOR_BLACK);   // Erro
    init_pair(3, COLOR_GREEN, COLOR_BLACK); // Sucesso
}

WINDOW* CrtlApresentacaoLogin::criarJanelaLogin() {
    int altura = 10, largura = 50;
    int startY = (LINES - altura) / 2;
    int startX = (COLS - largura) / 2;

    WINDOW* win = newwin(altura, largura, startY, startX);
    keypad(win, TRUE);
    return win;
}

void CrtlApresentacaoLogin::desenharLayout(WINDOW* win) {
    werase(win);
    box(win, 0, 0);
    
    wattron(win, COLOR_PAIR(1));
    mvwprintw(win, 0, (50 - 17) / 2, " LOGIN SISTEMA "); // 50 é a largura fixa
    wattroff(win, COLOR_PAIR(1));

    mvwprintw(win, 3, 5, "Email: ");
    mvwprintw(win, 5, 5, "Senha: ");
    mvwprintw(win, 8, 2, "(Pressione ESC para cancelar e sair)");
    wrefresh(win);
}

bool CrtlApresentacaoLogin::capturarCredenciais(WINDOW* win, char* emailStr, char* senhaStr) {
    wmove(win, 3, 13);
    wrefresh(win);
    if (!Tui::lerEntradaTerminal(win, emailStr, 79, false)) return false;

    wmove(win, 5, 13);
    wrefresh(win);
    if (!Tui::lerEntradaTerminal(win, senhaStr, 29, true)) return false;

    return true;
}

void CrtlApresentacaoLogin::exibirErro(WINDOW* win, const char* mensagem) {
    wattron(win, COLOR_PAIR(2));
    mvwprintw(win, 8, 2, "Erro: %s", mensagem);
    wattroff(win, COLOR_PAIR(2));
    wrefresh(win);
    wgetch(win); // Pausa para o usuário ler
}

void CrtlApresentacaoLogin::exibirSucesso(WINDOW* win) {
    wattron(win, COLOR_PAIR(3));
    mvwprintw(win, 8, 2, "Sucesso! Entrando no sistema...");
    wattroff(win, COLOR_PAIR(3));
    wrefresh(win);
    //wgetch(win);
    napms(1500); // Pausa automática
}