#ifdef _WIN32
    #include <curses.h> 
#elif __linux__
    #include <ncurses.h>
#else
    #error "Sistema operacional nao suportado para esta biblioteca."
#endif

#include "Controladoras/CrtlApresentacaoBacklog.hpp"
#include "Entidades/historiaDeUsuario.hpp"
#include "Entidades/pessoa.hpp"
#include "Containers/containerPessoa.hpp"
#include "Tui/tui.hpp"
#include <stdexcept>
#include <cstring>

void CrtlApresentacaoBacklog::executar(const Email& emailLogado) {

    WINDOW* win = criarJanelaBacklog(10, 50);
    WINDOW* guardaPtr;

    bool sair = false;

    std::vector<std::string> opcoes = {
        "Criar Historia de Usuário",
        "Ler",
        "Atualizar",
        "Excluir",  
        "Voltar"
    };

    while (!sair) {
        desenharCabecalho(emailLogado);
        int opcao = Tui::exibeMenu(win, "OPCOES DE BACKLOG", opcoes);

        guardaPtr = win;

        win = criarJanelaBacklog(20, 50);

        switch (opcao) {
            case 0:
                criarBacklog(win, emailLogado);
                break;

            case 1:
                lerBacklog(win);
                break;

            case 2:
                // atualizarBacklog();
                break;

            case 3:
                // excluirBacklog();
                break;

            case 4:
                sair = true;
                wclear(win);
                win = guardaPtr;
                break;

            default:
                break;
        }
    }
    
    delwin(win);
    return ;
}

void CrtlApresentacaoBacklog::criarBacklog(WINDOW* win, const Email& emailLogado) {
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
        mvwprintw(win, 12, 5, "Estimativa: ");
        mvwprintw(win, 13, 5, "Prioridade: ");
        mvwprintw(win, 14, 5, "Estado: ");
        mvwprintw(win, 18, 2, "Pressione ESC para cancelar e sair");

        wrefresh(win);

        //inicializa as variáveis que serão capturadas do usuário
        char strCodigo[10];
        char strTitulo[15];
        char strPapel[15];
        char strAcao[15];
        char strValor[101];
        char strEstimativa[15];
        char strPrioridade[11];
        char strEstado[21];

       // Captura os dados necessários para instanciar os domínios
        // e montar a entidade Projeto.
        wmove(win, 2, 14);
        if (!Tui::lerEntradaTerminal(win, strCodigo, 9, false)) {
            return;
        }

        wmove(win, 3, 14);
        if (!Tui::lerEntradaTerminal(win, strTitulo, 14, false)) {
            return;
        }

        wmove(win, 4, 12);
        if (!Tui::lerEntradaTerminal(win, strPapel, 14, false)) {
            return;
        }

        wmove(win, 5, 10);
        if (!Tui::lerEntradaTerminal(win, strAcao, 14, false)) {
            return;
        }

        wmove(win, 6, 12);
        if (!Tui::lerEntradaTerminal(win, strValor, 100, false)) {
            return;
        }

        wmove(win, 12, 20);
        if (!Tui::lerEntradaTerminal(win, strEstimativa, 14, false)) {
            return;
        }
        wmove(win, 13, 20);
        if (!Tui::lerEntradaTerminal(win, strPrioridade, 10, false)) {
            return;
        }

        wmove(win, 14, 14);
        if (!Tui::lerEntradaTerminal(win, strEstado, 20, false)) {
            return;
        }


        // Tenta construir os domínios e a entidade Projeto.
        // Caso alguma validação dos domínios falhe,
        // a exceção é capturada e a operação é repetida.
        try {
            Codigo codigoLocal(strCodigo);
            Texto tituloLocal(strTitulo);
            Texto papelLocal(strPapel);
            Texto acaoLocal(strAcao);
            Texto valorLocal(strValor);
            Tempo estimativaLocal(strEstimativa);

            Prioridade prioridadeLocal;
            prioridadeLocal.setValor(strPrioridade);

            Estado estadoLocal;
            estadoLocal.setValor(strEstado);

            Email enviar;
            enviar.setValor("joao@teste.com"); // simulando um teste

            HistoriaDeUsuario historiaLocal;

            historiaLocal.setCodigo(codigoLocal);
            historiaLocal.setTitulo(tituloLocal);
            historiaLocal.setPapel(papelLocal);
            historiaLocal.setAcao(acaoLocal);
            historiaLocal.setValor(valorLocal);
            historiaLocal.setEstimativa(estimativaLocal);
            historiaLocal.setPrioridade(prioridadeLocal);
            historiaLocal.setEstado(estadoLocal);
            historiaLocal.setCodigoProjeto(codigoLocal); // trocar por um input devido
            //historiaLocal.setEmailPessoa(enviar);

            valido = servicoBacklog->criarHistoriaUsuario(historiaLocal, emailLogado);

            if (valido) {
                wattron(win, COLOR_PAIR(3));
                mvwprintw(win, 8, 2, "Historia criada com sucesso!");
                wattroff(win, COLOR_PAIR(3));
                wrefresh(win);
                wgetch(win);
                return;
            }

            wattron(win, COLOR_PAIR(2));
            mvwprintw(win, 8, 2, "Erro: historia nao foi criada.");
            wattroff(win, COLOR_PAIR(2));
            wrefresh(win);
            wgetch(win);
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

void CrtlApresentacaoBacklog::lerBacklog(WINDOW* win) {
    while (true) {
        werase(win);
        box(win, 0, 0);

        wattron(win, COLOR_PAIR(1));
        mvwprintw(win, 0, 17, " LER HISTORIA ");
        wattroff(win, COLOR_PAIR(1));

        mvwprintw(win, 2, 5, "Codigo:");
        mvwprintw(win, 18, 2, "Pressione ESC para cancelar e sair");

        wrefresh(win);

        char strCodigo[6];

        wmove(win, 2, 14);

        if (!Tui::lerEntradaTerminal(win, strCodigo, 5, false)) {
            return;
        }

        try {
            Codigo codigoLocal(strCodigo);

            HistoriaDeUsuario historiaLocal;

            bool encontrado =
                servicoBacklog->lerHistoriaUsuario(
                    codigoLocal,
                    historiaLocal
                );

            werase(win);
            box(win, 0, 0);

            wattron(win, COLOR_PAIR(1));
            mvwprintw(win, 0, 14, " DADOS DA HISTORIA ");
            wattroff(win, COLOR_PAIR(1));

            if (encontrado) {

                mvwprintw(win, 2, 5,
                    "Codigo: %s",
                    historiaLocal.getCodigo().getValor().c_str());

                mvwprintw(win, 3, 5,
                    "Titulo: %s",
                    historiaLocal.getTitulo().getValor().c_str());

                mvwprintw(win, 4, 5,
                    "Papel: %s",
                    historiaLocal.getPapel().getValor().c_str());

                mvwprintw(win, 5, 5,
                    "Acao: %s",
                    historiaLocal.getAcao().getValor().c_str());

                mvwprintw(win, 6, 5,
                    "Valor: %s",
                    historiaLocal.getValor().getValor().c_str());

                mvwprintw(win, 7, 5,
                    "Estimativa: %s",
                    historiaLocal.getEstimativa().getValor().c_str());

                mvwprintw(win, 8, 5,
                    "Prioridade: %s",
                    historiaLocal.getPrioridade().getValor().c_str());

                mvwprintw(win, 9, 5,
                    "Estado: %s",
                    historiaLocal.getEstado().getValor().c_str());

                wattron(win, COLOR_PAIR(3));
                mvwprintw(win, 16, 2,
                    "Pressione qualquer tecla para voltar.");
                wattroff(win, COLOR_PAIR(3));

                wrefresh(win);
                wgetch(win);

                return;
            }

            wattron(win, COLOR_PAIR(2));
            mvwprintw(win, 16, 2,
                "Historia nao encontrada. Pressione qualquer tecla.");
            wattroff(win, COLOR_PAIR(2));

            wrefresh(win);
            wgetch(win);
        }
        catch (const std::invalid_argument& e) {
            wattron(win, COLOR_PAIR(2));
            mvwprintw(win, 16, 2,
                "Erro: %s",
                e.what());
            wattroff(win, COLOR_PAIR(2));

            wrefresh(win);
            wgetch(win);
        }
    }
}


WINDOW* CrtlApresentacaoBacklog::criarJanelaBacklog(int altura, int largura) {
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

void CrtlApresentacaoBacklog::desenharCabecalho(const Email& emailLogado) {
    //Variaveis para o cabeçalho
    Pessoa pessoaLogada;
    pessoaLogada.setEmail(emailLogado);
    ContainerPessoa::getInstancia()->lerPessoa(pessoaLogada); // tenta se comunicar com banco

    attron(COLOR_PAIR(5)); 
    mvprintw(0, 0, " Usuario logado: %s ", emailLogado.getValor().c_str());
    mvprintw(1, 0, " Papel Do Usuario: %s ", pessoaLogada.getPapel().getValor().c_str());
    attroff(COLOR_PAIR(5));
    refresh();
}   