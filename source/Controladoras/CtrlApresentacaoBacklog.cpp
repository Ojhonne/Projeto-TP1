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

    bool sair = false;

    std::vector<std::string> opcoes = {
        "Criar Historia de Usuário",
        "Ler",
        "Atualizar",
        "Excluir",
        "Voltar"
    };

    while (!sair) {

        int opcao = Tui::exibeMenu(win, "OPCOES DE BACKLOG", opcoes);

        switch (opcao) {
            case 0:
                criarBacklog(win);
                break;

            case 1:
               // lerBacklog();
                break;

            case 2:
                // atualizarBacklog();
                break;

            case 3:
                // excluirBacklog();
                break;

            case 4:
                sair = true;
                break;

            default:
                break;
        }
    }
    
    delwin(win);
    return ;
}

void CrtlApresentacaoBacklog::criarBacklog(WINDOW* win) {
   bool valido = false;

    while (!valido) {
        werase(win);
        box(win, 0, 0);

        wattron(win, COLOR_PAIR(1));
        mvwprintw(win, 0, 17, " CRIAR HISTORIA DE USUARIO ");
        wattroff(win, COLOR_PAIR(1));

        mvwprintw(win, 2, 5, "Codigo: ");
        mvwprintw(win, 3, 5, "Titulo: ");
        mvwprintw(win, 4, 5, "Papel: ");
        mvwprintw(win, 5, 5, "Acao: ");
        mvwprintw(win, 6, 5, "Valor: ");
        mvwprintw(win, 7, 5, "Estimativa: ");
        mvwprintw(win, 8, 5, "Prioridade: ");
        mvwprintw(win, 9, 5, "Estado: ");
        mvwprintw(win, 12, 2, "Pressione ESC para cancelar e sair");

        wrefresh(win);

        //inicializa as variáveis que serão capturadas do usuário
        char strCodigo[6];
        char strTitulo[11];
        char strPapel[11];
        char strAcao[11];
        char strValor[101];
        char strEstimativa[11];
        char strPrioridade[11];
        char strEstado[11];

       // Captura os dados necessários para instanciar os domínios
        // e montar a entidade Projeto.
        wmove(win, 2, 14);
        if (!Tui::lerEntradaTerminal(win, strCodigo, 5, false)) {
            return;
        }

        wmove(win, 3, 14);
        if (!Tui::lerEntradaTerminal(win, strTitulo, 10, false)) {
            return;
        }

        wmove(win, 4, 18);
        if (!Tui::lerEntradaTerminal(win, strPapel, 10, false)) {
            return;
        }

        wmove(win, 5, 15);
        if (!Tui::lerEntradaTerminal(win, strAcao, 10, false)) {
            return;
        }

        wmove(win, 5, 15);
        if (!Tui::lerEntradaTerminal(win, strValor, 100, false)) {
            return;
        }

        wmove(win, 5, 15);
        if (!Tui::lerEntradaTerminal(win, strEstimativa, 10, false)) {
            return;
        }

        wmove(win, 5, 15);
        if (!Tui::lerEntradaTerminal(win, strPrioridade, 10, false)) {
            return;
        }

        wmove(win, 5, 15);
        if (!Tui::lerEntradaTerminal(win, strEstado, 10, false)) {
            return;
        }


        // Tenta construir os domínios e a entidade Projeto.
        // Caso alguma validação dos domínios falhe,
        // a exceção é capturada e a operação é repetida.
        try {
            Codigo codigoLocal(strCodigo);
            Texto tituloLocal(strTitulo);
            Texto acaoLocal(strAcao);
            Texto valorLocal(strValor);
            Tempo estimativaLocal(strEstimativa);
            Prioridade PrioridadeLocal(strPrioridade);
            Estado estadoLocal(strEstado);

            /*Projeto projetoLocal;
            projetoLocal.setCodigo(codigoLocal);
            projetoLocal.setNome(nomeLocal);
            projetoLocal.setInicio(dataInicioLocal);
            projetoLocal.setTermino(dataFimLocal);*/

            //valido = servicoPlanejamento->criarProjeto(projetoLocal);

            if (valido) {
                wattron(win, COLOR_PAIR(3));
                mvwprintw(win, 8, 2, "Projeto criado com sucesso!");
                wattroff(win, COLOR_PAIR(3));
                wrefresh(win);
                wgetch(win);
            } else {
                wattron(win, COLOR_PAIR(2));
                mvwprintw(win, 8, 2, "Erro: projeto nao foi criado.");
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
}


WINDOW* CrtlApresentacaoBacklog::criarJanelaBacklog() {
    int altura = 14, largura = 50;
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