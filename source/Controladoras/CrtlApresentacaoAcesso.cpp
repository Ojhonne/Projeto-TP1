
#ifdef _WIN32
    #include <curses.h> 
#elif __linux__
    #include <ncurses.h>
#else
    #error "Sistema operacional nao suportado para esta biblioteca."
#endif

#include "Controladoras/CrtlApresentacaoAcesso.hpp"
#include "Tui/tui.hpp"
#include <stdexcept>
#include "Interfaces/interfaces.hpp"
#include <cstring>

 void CrtlApresentacaoAcesso::inicializarInterface(){

    init_pair(1, COLOR_WHITE, COLOR_BLUE); // Título
    init_pair(2, COLOR_RED, COLOR_BLACK);  // Erro
    init_pair(3, COLOR_GREEN, COLOR_BLACK); // Sucesso

    // Dimensões da janela centralizada
    int altura{10}, largura{50};
    int startY{(LINES - altura) / 2};
    int startX{(COLS - largura) / 2};

    win = newwin(altura, largura, startY, startX); // Iniciar a janela
    box(win, 0, 0); // Desenha borda na janela
    keypad(win, TRUE); // Habilita teclas na janela

 }

void CrtlApresentacaoAcesso::rotearEscolha(int escolha){
    switch(escolha){
        case 0:
            logado = true;
        break;
        case 1:
            //
        break;
        case 2:
        return;
    }
 }
 
void CrtlApresentacaoAcesso::executar() {
    clear();     // Limpa o buffer da tela inteira
    refresh();   // Força o redesenho da stdscr
    
    const std::vector<std::string> opcoesDeslogadas = {"Realizar login", "Realizar cadastro", "Encerrar Sistema"};
    const std::vector<std::string> opcoesLogadas = {"Modulo de Cadastro (Pessoas)", "Modulo de Planejamento (Projetos e Sprints)", "Modulo de Backlog (Historias de Usuario)", "Fazer Logout", "Encerrar Sistema"};
   
    inicializarInterface();

    while (true) {
        const auto& opcoes = logado ? opcoesLogadas : opcoesDeslogadas;
        int escolha = Tui::exibeMenu(win, logado ? "MENU LOGADO" : "MENU PRINCIPAL", opcoes);
        rotearEscolha(escolha);
    }

}


void CrtlApresentacaoAcesso::finalizaInterface(){
    delwin(win); 
    endwin(); // Restaura o terminal ao estado normal
}