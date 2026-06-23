/**
 * @file interfaces.hpp
 * @author João Francisco de Sousa Torres
 * @brief Definição do namespace Tui para auxiliar no desenvolvimento gráfico.
 */


#ifndef TUI_H_INCLUDED
#define TUI_H_INCLUDED
#include <vector>
#include <string>

#ifdef _WIN32
    #include <curses.h> 
#elif __linux__
    #include <ncurses.h>
#else
    #error "Sistema operacional nao suportado para esta biblioteca."
#endif

namespace Tui {
    /** @brief Inicializa o terminal para uso com ncurses. \n
     * Configura o terminal para capturar entradas do usuário, desabilita a exibição de caracteres digitados,
     * e habilita o uso de cores e teclas especiais. \n
     */
    void inicializarTerminal();
    /** @brief Finaliza o uso do ncurses e restaura o estado original do terminal. 
    */
    void finalizarTerminal();
    
    /**
     * @brief Lê a entrada do usuário no ncurses com suporte a backspace e cancelamento.
     * @param win Ponteiro para a janela atual do ncurses.
     * @param buffer Array de char onde a string lida será armazenada.
     * @param tamanhoMaximo Limite de caracteres a serem lidos.
     * @param modoSenha Se true, imprime '*' ao invés dos caracteres reais.
     * @return Retorna true se a leitura foi confirmada (Enter), e false se foi cancelada (ESC).
     */
    bool lerEntradaTerminal(WINDOW* win, char* buffer, int tamanhoMaximo, bool modoSenha);

    /**
     * @brief Exibe um menu de opções no terminal usando ncurses.
     * @param win Ponteiro para a janela atual do ncurses.
     * @param titulo Título do menu a ser exibido.    
     * @param opcoes Vetor de strings representando as opções do menu.
     * @return Retorna o índice da opção selecionada pelo usuário.
     */
     int exibeMenu(WINDOW* win, const std::string& titulo, const std::vector<std::string>& opcoes);
}

#endif // TUI_H_INCLUDED