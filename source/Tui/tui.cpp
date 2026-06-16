#include "Tui/tui.hpp"

namespace Tui {

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

} 