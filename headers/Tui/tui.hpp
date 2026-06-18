#ifndef TUI_H_INCLUDED
#define TUI_H_INCLUDED
#include <vector>
#include <string>
// Verificação multiplataforma do ncurses
#ifdef _WIN32
    #include <curses.h> 
#elif __linux__
    #include <ncurses.h>
#else
    #error "Sistema operacional nao suportado para esta biblioteca."
#endif

namespace Tui {
    /**
     * @brief Lê a entrada do usuário no ncurses com suporte a backspace e cancelamento.
     * @param win Ponteiro para a janela atual do ncurses.
     * @param buffer Array de char onde a string lida será armazenada.
     * @param tamanhoMaximo Limite de caracteres a serem lidos.
     * @param modoSenha Se true, imprime '*' ao invés dos caracteres reais.
     * @return Retorna true se a leitura foi confirmada (Enter), e false se foi cancelada (ESC).
     */
    bool lerEntradaTerminal(WINDOW* win, char* buffer, int tamanhoMaximo, bool modoSenha);

     int exibeMenu(WINDOW* win, const std::string& titulo, const std::vector<std::string>& opcoes);
}

#endif // TUI_H_INCLUDED