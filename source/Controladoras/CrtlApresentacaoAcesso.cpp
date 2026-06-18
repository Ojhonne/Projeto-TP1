
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
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    start_color();
    keypad(stdscr, TRUE);

    init_pair(1, COLOR_WHITE, COLOR_BLUE); // Título
    init_pair(2, COLOR_RED, COLOR_BLACK);  // Erro
    init_pair(3, COLOR_GREEN, COLOR_BLACK); // Sucesso
    init_pair(4,COLOR_WHITE, COLOR_CYAN);

    // Dimensões da janela centralizada
    int altura{10}, largura{50};
    int startY{(LINES - altura) / 2};
    int startX{(COLS - largura) / 2};

    win = newwin(altura, largura, startY, startX); // Iniciar a janela
    box(win, 0, 0); // Desenha borda na janela
    keypad(win, TRUE); // Habilita teclas na janela

    // Para pintar a janela inteira do terminal:
    //bkgd(COLOR_PAIR(4));

    //para pintar apenas a caixinha do menu:
    //wbkgd(win, COLOR_PAIR(4));

 }

bool CrtlApresentacaoAcesso::rotearEscolha(int escolha, bool logado) {
    wclear(win); 
    wrefresh(win); 
    
    clear(); 
    refresh();

    if (!logado) {
        switch (static_cast<MenuDeslogado>(escolha)) {
            case MenuDeslogado::Login:
                this->logado = crtlLogin->executar(emailSessao);
                break;
            case MenuDeslogado::Cadastro:
               // crtlCadastro->executar();
                break;
            case MenuDeslogado::Sair:
                return false;
        }
    } else {
        switch (static_cast<MenuLogado>(escolha)) {
            case MenuLogado::CadastroPessoas:
                // ...
                break;
            case MenuLogado::Projetos:
                // ...
                break;
            case MenuLogado::Backlog:
                // ...
                break;
            case MenuLogado::Logout:
                this->logado = false;
                break;
            case MenuLogado::Sair:
                return false;
        }
    }
    return true;
}
 
void CrtlApresentacaoAcesso::executar() {
    
    const std::vector<std::string> opcoesDeslogadas = {"Realizar login", "Realizar cadastro", "Encerrar Sistema"};
    const std::vector<std::string> opcoesLogadas = {"Modulo de Cadastro (Pessoas)", "Modulo de Planejamento (Projetos e Sprints)", "Modulo de Backlog (Historias de Usuario)", "Fazer Logout", "Encerrar Sistema"};
   
    inicializarInterface();

    init_pair(1, COLOR_BLUE, COLOR_BLACK); 
    
    while (true) {
        wclear(win);

        if (logado) {
            attron(COLOR_PAIR(1)); 
            mvprintw(0, 0, " Usuario logado: %s ", emailSessao.getValor().c_str());
            attroff(COLOR_PAIR(1));
        }

        refresh(); 
        const auto& opcoes = logado ? opcoesLogadas : opcoesDeslogadas;
        int escolha = Tui::exibeMenu(win, logado ? "MENU LOGADO" : "MENU PRINCIPAL", opcoes);
        if(!rotearEscolha(escolha, logado)) break;
    }

    finalizaInterface();
}


void CrtlApresentacaoAcesso::finalizaInterface(){
    delwin(win); 
    endwin(); // Restaura o terminal ao estado normal
}