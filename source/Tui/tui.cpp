#include "Tui/tui.hpp"
#include <vector>
#include <string>

namespace Tui {

    void inicializarTerminal() {
        // configuração do terminal
        initscr(); // inicio a tela
        cbreak();
        noecho(); // nao aparece o que eu escrevo
        curs_set(0); // colocando o curso para longe
        keypad(stdscr, TRUE); // habilitando teclas especiais

        // Configuração de cores
        start_color();
        init_pair(1, COLOR_WHITE, COLOR_BLUE);  // Título
        init_pair(2, COLOR_RED, COLOR_BLACK);   // Erro
        init_pair(3, COLOR_GREEN, COLOR_BLACK); // Sucesso
        init_pair(4, COLOR_WHITE, COLOR_CYAN);  // Fundo
        init_pair(5, COLOR_BLUE, COLOR_BLACK);  // Usuário logado
        
       // bkgd(COLOR_PAIR(4)); // pinta todo terminal 
       // refresh(); // Atualiza a tela 
    }

    void finalizarTerminal() {
        endwin(); // Devolve o controle normal ao terminal do SO
    }

    bool lerEntradaTerminal(WINDOW* win, char* buffer, int tamanhoMaximo, bool modoSenha) {
        int ch;
        int i = 0;

        while (i < tamanhoMaximo) {
            ch = wgetch(win);
            
            // ESC (ASCII 27) 
            if (ch == 27) { 
                return false;
            } 
            // Enter confirma
            else if (ch == '\n' || ch == '\r') {
                break;
            } 
            // Backspace apaga
            else if (ch == KEY_BACKSPACE || ch == 127 || ch == '\b') {
                if (i > 0) {
                    i--;
                    int y, x;
                    getyx(win, y, x);           
                    mvwaddch(win, y, x - 1, ' ');
                    wmove(win, y, x - 1);         
                    wrefresh(win);
                }
            } 
            // Caracteres normais
            else {
                buffer[i++] = ch;
                if (modoSenha) {
                    waddch(win, '*');
                } else {
                    waddch(win, ch);
                }
                wrefresh(win);
            }
        }
        buffer[i] = '\0'; 
        return true;
    }
    int exibeMenu(WINDOW* win, const std::string& titulo, const std::vector<std::string>& opcoes){
        int emDestaque = 0;
        int tecla;    
        while (true) {
            werase(win);
            box(win, 0, 0);
            mvwprintw(win, 0, 2, " %s ", titulo.c_str());

            for (int i = 0; i < static_cast<int>(opcoes.size()); i++) {
                if (i == emDestaque) {
                    wattron(win, A_REVERSE);
                    mvwprintw(win, i + 2, 2, "> %s", opcoes[i].c_str());
                    wattroff(win, A_REVERSE);
                } else {
                    mvwprintw(win, i + 2, 2, "  %s", opcoes[i].c_str());
                }
            }
            wrefresh(win);

            tecla = wgetch(win);
            switch (tecla) {
                case KEY_UP: if (emDestaque > 0) emDestaque--; break;
                case KEY_DOWN: if (emDestaque < (int)opcoes.size() - 1) emDestaque++; break;
                case 10: return emDestaque; // Retorna a opção escolhida
             }
        }
    }
} 
