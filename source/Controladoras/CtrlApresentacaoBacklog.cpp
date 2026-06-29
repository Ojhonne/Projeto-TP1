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
        "Listar",  
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
                atualizarBacklog(win, emailLogado);
                break;

            case 3:
                excluirBacklog(win, emailLogado);
                break;

            case 4:
                menuListar(win, emailLogado);
                break;
            
            case 5:
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
        mvwprintw(win, 8, 5, "Valor: ");
        mvwprintw(win, 12, 5, "Estimativa: ");
        mvwprintw(win, 13, 5, "Prioridade: ");
        mvwprintw(win, 14, 5, "Codigo do Projeto: ");
        mvwprintw(win, 16, 2, "Pressione ESC para cancelar e sair");

        wrefresh(win);

        //inicializa as variáveis que serão capturadas do usuário
        char strCodigo[10];
        char strCodigoProjeto[10];
        char strTitulo[15];
        char strPapel[15];
        char strAcao[30];
        char strValor[101];
        char strEstimativa[15];
        char strPrioridade[11];

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
        if (!Tui::lerEntradaTerminal(win, strAcao, 29, false)) {
            return;
        }

        wmove(win, 8, 12);
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
        wmove(win, 14, 25);
        if (!Tui::lerEntradaTerminal(win, strCodigoProjeto, 9, false)) {
            return;
        }

        Estado estadoInicial;
        estadoInicial.setValor("A FAZER"); // formato exigido para o estado inicial de uma história de usuário


        // Tenta construir os domínios e a entidade Projeto.
        // Caso alguma validação dos domínios falhe,
        // a exceção é capturada e a operação é repetida.
        try {
            Codigo codigoLocal(strCodigo);
            Codigo codigoProjeto(strCodigoProjeto);
            Texto tituloLocal(strTitulo);
            Texto papelLocal(strPapel);
            Texto acaoLocal(strAcao);
            Texto valorLocal(strValor);
            Tempo estimativaLocal(strEstimativa);

            Prioridade prioridadeLocal;
            prioridadeLocal.setValor(strPrioridade);


            HistoriaDeUsuario historiaLocal;

            historiaLocal.setCodigo(codigoLocal);
            historiaLocal.setTitulo(tituloLocal);
            historiaLocal.setPapel(papelLocal);
            historiaLocal.setAcao(acaoLocal);
            historiaLocal.setValor(valorLocal);
            historiaLocal.setEstimativa(estimativaLocal);
            historiaLocal.setPrioridade(prioridadeLocal);
            historiaLocal.setEstado(estadoInicial);
            historiaLocal.setCodigoProjeto(codigoProjeto); // trocar por um input devido

            valido = servicoBacklog->criarHistoriaUsuario(historiaLocal, emailLogado);

            if (valido) {
                wattron(win, COLOR_PAIR(3));
                mvwprintw(win, 15, 2, "Historia criada com sucesso!");
                wattroff(win, COLOR_PAIR(3));
                wrefresh(win);
                wgetch(win);
                return;
            }

            wattron(win, COLOR_PAIR(2));
            mvwprintw(win, 15, 2, "Erro: historia nao foi criada.");
            wattroff(win, COLOR_PAIR(2));
            wrefresh(win);
            wgetch(win);
        }
        catch (const std::invalid_argument& e) {
            wattron(win, COLOR_PAIR(2));
            mvwprintw(win, 15, 2, "Erro: %s", e.what());
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

        char strCodigo[8];

        wmove(win, 2, 14);

        if (!Tui::lerEntradaTerminal(win, strCodigo, 7, false)) {
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

                mvwprintw(win, 3, 5,
                    "Titulo: %s",
                    historiaLocal.getTitulo().getValor().c_str());

                mvwprintw(win, 4, 5,
                    "Papel: %s",
                    historiaLocal.getPapel().getValor().c_str());

                mvwprintw(win, 5, 5,
                    "Acao: %s",
                    historiaLocal.getAcao().getValor().c_str());

                mvwprintw(win, 8, 5,
                    "Valor: %s",
                    historiaLocal.getValor().getValor().c_str());

                mvwprintw(win, 12, 5,
                    "Estimativa: %s",
                    historiaLocal.getEstimativa().getValor().c_str());

                mvwprintw(win, 13, 5,
                    "Prioridade: %s",
                    historiaLocal.getPrioridade().getValor().c_str());

                mvwprintw(win, 14, 5,
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

void CrtlApresentacaoBacklog::atualizarBacklog(WINDOW* win, const Email& emailLogado) {
    bool valido = false;

    while (!valido) {
        werase(win);
        box(win, 0, 0);

        wattron(win, COLOR_PAIR(1));
        mvwprintw(win, 0, 15, " ATUALIZAR HISTORIA DE USUARIO ");
        wattroff(win, COLOR_PAIR(1));

        mvwprintw(win, 2, 5, "Codigo: ");
        mvwprintw(win, 3, 5, "Novo Titulo: ");
        mvwprintw(win, 4, 5, "Novo Papel: ");
        mvwprintw(win, 5, 5, "Nova Acao: ");
        mvwprintw(win, 6, 5, "Novo Valor: ");
        mvwprintw(win, 12, 5, "Nova Estimativa: ");
        mvwprintw(win, 13, 5, "Nova Prioridade: ");
        mvwprintw(win, 14, 5, "Novo Estado: ");
        mvwprintw(win, 14, 5, "Novo Codigo do Projeto: ");
        mvwprintw(win, 18, 2, "Pressione ESC para cancelar e sair");

        wrefresh(win);

        char strCodigo[10];
        char strCodigoProjeto[10];
        char strTitulo[15];
        char strPapel[15];
        char strAcao[15];
        char strValor[101];
        char strEstimativa[15];
        char strPrioridade[11];
        char strEstado[21];

       wmove(win, 2, 14);
        if (!Tui::lerEntradaTerminal(win, strCodigo, 9, false)) {
            return;
        }

        wmove(win, 3, 18);
        if (!Tui::lerEntradaTerminal(win, strTitulo, 14, false)) {
            return;
        }

        wmove(win, 4, 18);
        if (!Tui::lerEntradaTerminal(win, strPapel, 14, false)) {
            return;
        }

        wmove(win, 5, 16);
        if (!Tui::lerEntradaTerminal(win, strAcao, 14, false)) {
            return;
        }

        wmove(win, 6, 17);
        if (!Tui::lerEntradaTerminal(win, strValor, 100, false)) {
            return;
        }

        wmove(win, 12, 22);
        if (!Tui::lerEntradaTerminal(win, strEstimativa, 14, false)) {
            return;
        }
        wmove(win, 13, 22);
        if (!Tui::lerEntradaTerminal(win, strPrioridade, 10, false)) {
            return;
        }

        wmove(win, 14, 18);
        if (!Tui::lerEntradaTerminal(win, strEstado, 20, false)) {
            return;
        }
        wmove(win, 14, 32);
        if (!Tui::lerEntradaTerminal(win, strCodigoProjeto, 9, false)) {
            return;
        }


        try {
            Codigo codigoLocal(strCodigo);
            Codigo codigoProjeto(strCodigoProjeto);
            Texto tituloLocal(strTitulo);
            Texto papelLocal(strPapel);
            Texto acaoLocal(strAcao);
            Texto valorLocal(strValor);
            Tempo estimativaLocal(strEstimativa);

            Prioridade prioridadeLocal;
            prioridadeLocal.setValor(strPrioridade);

            Estado estadoLocal;
            estadoLocal.setValor(strEstado);

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

            valido = servicoBacklog->atualizarHistoriaUsuario(historiaLocal, emailLogado);

            if (valido) {
                wattron(win, COLOR_PAIR(3));
                mvwprintw(win, 14, 2, "Historia atualizada com sucesso!");
                wattroff(win, COLOR_PAIR(3));
                wrefresh(win);
                wgetch(win);
            } else {
                wattron(win, COLOR_PAIR(2));
                mvwprintw(win, 14, 2, "Erro: Historia nao foi atualizada.");
                wattroff(win, COLOR_PAIR(2));
                wrefresh(win);
                wgetch(win);
            }
        }
        catch (const std::invalid_argument& e) {
            wattron(win, COLOR_PAIR(2));
            mvwprintw(win, 14, 2, "Erro: %s", e.what());
            wattroff(win, COLOR_PAIR(2));
            wrefresh(win);
            wgetch(win);
        }
    }
}

void CrtlApresentacaoBacklog::menuListar(WINDOW* win, const Email& emailLogado) {
    bool sair = false;

    std::vector<std::string> opcoes = {
        "Associadas a Projeto",
        "Associadas a Plano Sprint",
        "Associadas a Pessoa",
        "Associar Pessoa",       // case 5
        "Remover Associacao",    // case 6
        "Mover para Sprint",     // case 7
        "Alterar Estado",        // case 8
        "Voltar"                 // case 9 (era 5)
    };

    //exibe as possíveis ações a serem feitas com os projetos até que o usuário escolha sair.
    while (!sair) {
        //captura a opção desejada pelo usuário
        int opcao = Tui::exibeMenu(win, "LISTAR HISTORIAS", opcoes);

        switch (opcao) {
            case 0:
                listarAssociadasProjeto(win);
                break;

            case 1:
                listarAssociadasPlanoSprint(win);
                break;

            case 2:
                listarAssociadasPessoa(win);
                break;
            case 3: associarHistoriaPessoa(win, emailLogado);           break;
            case 4: removerAssociacaoHistoriaPessoa(win, emailLogado);  break;
            case 5: moverHistoriaProjetoParaSprint(win, emailLogado);   break;
            case 6: alterarEstadoHistoria(win, emailLogado);            break;
            case 7: sair = true;      break;

            default:
                break;
        }
    }
}

void CrtlApresentacaoBacklog::listarAssociadasPessoa(WINDOW* win) {
    bool sair = false;

    while (!sair) {
        werase(win);
        box(win, 0, 0);

        wattron(win, COLOR_PAIR(1));
        mvwprintw(win, 0, 10, " LISTAR HISTORIA POR PESSOA ");
        wattroff(win, COLOR_PAIR(1));

        mvwprintw(win, 2, 5, "Email: ");
        mvwprintw(win, 8, 2, "Pressione ESC para cancelar e sair");

        wrefresh(win);

        char strEmail[330];

        wmove(win, 2, 12);
        if (!Tui::lerEntradaTerminal(win, strEmail, 329, false)) {
            return;
        }

        try {
            Email emailLocal(strEmail);
            std::vector<HistoriaDeUsuario> historiaDeUsuario;

            bool encontrado = servicoBacklog->listarHistoriasAssociadasPessoa(emailLocal, historiaDeUsuario);

            werase(win);
            box(win, 0, 0);

            wattron(win, COLOR_PAIR(1));
            mvwprintw(win, 0, 10, " HISTORIAS ASSOCIADAS ");
            wattroff(win, COLOR_PAIR(1));

            if (encontrado && !historiaDeUsuario.empty()) {
                mvwprintw(win, 2, 5, "Email: %s", emailLocal.getValor().c_str());
                mvwprintw(win, 4, 5, "Codigos das historias:");

                int linha = 5;

                for (size_t i = 0; i < historiaDeUsuario.size(); i++) {
                    mvwprintw(
                        win,
                        linha,
                        7,
                        "%zu - %s",
                        i + 1,
                        historiaDeUsuario[i].getCodigo().getValor().c_str()
                    );

                    linha++;
                    //chegou no limite, cria uma nova janela
                    if (linha >= 8) {
                        mvwprintw(win, 8, 2, "Pressione tecla para continuar...");
                        wrefresh(win);
                        wgetch(win);

                        werase(win);
                        box(win, 0, 0);

                        wattron(win, COLOR_PAIR(1));
                        mvwprintw(win, 0, 10, " HISTORIAS ASSOCIADAS ");
                        wattroff(win, COLOR_PAIR(1));

                        linha = 2;
                    }
                }

                wattron(win, COLOR_PAIR(3));
                mvwprintw(win, 8, 2, "Pressione qualquer tecla para voltar.");
                wattroff(win, COLOR_PAIR(3));

                wrefresh(win);
                wgetch(win);

                sair = true;
            }
            else {
                wattron(win, COLOR_PAIR(2));
                mvwprintw(win, 8, 2, "Nenhuma historia encontrada. Pressione tecla.");
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

void CrtlApresentacaoBacklog::listarAssociadasPlanoSprint(WINDOW* win) {
    bool sair = false;

    while (!sair) {
        werase(win);
        box(win, 0, 0);

        wattron(win, COLOR_PAIR(1));
        mvwprintw(win, 0, 10, " LISTAR HISTORIAS POR PLANO DE SPRINT ");
        wattroff(win, COLOR_PAIR(1));

        mvwprintw(win, 2, 5, "Codigo: ");
        mvwprintw(win, 8, 2, "Pressione ESC para cancelar e sair");

        wrefresh(win);

        char strCodigo[330];

        wmove(win, 2, 12);
        if (!Tui::lerEntradaTerminal(win, strCodigo, 329, false)) {
            return;
        }

        try {
            Codigo codigoLocal(strCodigo);
            std::vector<HistoriaDeUsuario> historiaDeUsuario;

            bool encontrado = servicoBacklog->listarHistoriasAssociadasPlanoSprint(codigoLocal, historiaDeUsuario);

            werase(win);
            box(win, 0, 0);

            wattron(win, COLOR_PAIR(1));
            mvwprintw(win, 0, 10, " HISTORIAS ASSOCIADAS ");
            wattroff(win, COLOR_PAIR(1));

            if (encontrado && !historiaDeUsuario.empty()) {
                mvwprintw(win, 2, 5, "Codigo: %s", codigoLocal.getValor().c_str());
                mvwprintw(win, 4, 5, "Codigos das historias");

                int linha = 5;

                for (size_t i = 0; i < historiaDeUsuario.size(); i++) {
                    mvwprintw(
                        win,
                        linha,
                        7,
                        "%zu - %s",
                        i + 1,
                        historiaDeUsuario[i].getCodigo().getValor().c_str()
                    );

                    linha++;
                    //chegou no limite, cria uma nova janela
                    if (linha >= 8) {
                        mvwprintw(win, 8, 2, "Pressione tecla para continuar...");
                        wrefresh(win);
                        wgetch(win);

                        werase(win);
                        box(win, 0, 0);

                        wattron(win, COLOR_PAIR(1));
                        mvwprintw(win, 0, 10, " HISTORIAS ASSOCIADAS ");
                        wattroff(win, COLOR_PAIR(1));

                        linha = 2;
                    }
                }

                wattron(win, COLOR_PAIR(3));
                mvwprintw(win, 8, 2, "Pressione qualquer tecla para voltar.");
                wattroff(win, COLOR_PAIR(3));

                wrefresh(win);
                wgetch(win);

                sair = true;
            }
            else {
                wattron(win, COLOR_PAIR(2));
                mvwprintw(win, 8, 2, "Nenhuma historia encontrada. Pressione tecla.");
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

void CrtlApresentacaoBacklog::listarAssociadasProjeto(WINDOW* win) {
    bool sair = false;

    while (!sair) {
        werase(win);
        box(win, 0, 0);

        wattron(win, COLOR_PAIR(1));
        mvwprintw(win, 0, 10, " LISTAR HISTORIAS POR PROJETO ");
        wattroff(win, COLOR_PAIR(1));

        mvwprintw(win, 2, 5, "Codigo: ");
        mvwprintw(win, 8, 2, "Pressione ESC para cancelar e sair");

        wrefresh(win);

        char strCodigo[330];

        wmove(win, 2, 12);
        if (!Tui::lerEntradaTerminal(win, strCodigo, 329, false)) {
            return;
        }

        try {
            Codigo codigoLocal(strCodigo);
            std::vector<HistoriaDeUsuario> historiaDeUsuario;

            bool encontrado = servicoBacklog->listarHistoriasAssociadasProjeto(codigoLocal, historiaDeUsuario);
            
            werase(win);
            box(win, 0, 0);

            wattron(win, COLOR_PAIR(1));
            mvwprintw(win, 0, 10, " HISTORIAS ASSOCIADAS ");
            wattroff(win, COLOR_PAIR(1));

            if (encontrado && !historiaDeUsuario.empty()) {
                mvwprintw(win, 2, 5, "Codigo: %s", codigoLocal.getValor().c_str());
                mvwprintw(win, 4, 5, "Codigos das historias:");

                int linha = 5;

                for (size_t i = 0; i < historiaDeUsuario.size(); i++) {
                    mvwprintw(
                        win,
                        linha,
                        7,
                        "%zu - %s",
                        i + 1,
                        historiaDeUsuario[i].getCodigo().getValor().c_str()
                    );

                    linha++;
                    //chegou no limite, cria uma nova janela
                    if (linha >= 8) {
                        mvwprintw(win, 8, 2, "Pressione tecla para continuar...");
                        wrefresh(win);
                        wgetch(win);

                        werase(win);
                        box(win, 0, 0);

                        wattron(win, COLOR_PAIR(1));
                        mvwprintw(win, 0, 10, " HISTORIAS ASSOCIADAS ");
                        wattroff(win, COLOR_PAIR(1));

                        linha = 2;
                    }
                }

                wattron(win, COLOR_PAIR(3));
                mvwprintw(win, 8, 2, "Pressione qualquer tecla para voltar.");
                wattroff(win, COLOR_PAIR(3));

                wrefresh(win);
                wgetch(win);

                sair = true;
            }
            else {
                wattron(win, COLOR_PAIR(2));
                mvwprintw(win, 11, 2, "Nenhuma historia encontrada. Pressione tecla.");
                wattroff(win, COLOR_PAIR(2));

                wrefresh(win);
                wgetch(win);
            }
        }
        catch (const std::invalid_argument& e) {
            wattron(win, COLOR_PAIR(2));
            mvwprintw(win, 11, 2, "Erro: %s", e.what());
            wattroff(win, COLOR_PAIR(2));

            wrefresh(win);
            wgetch(win);
        }
    }
}

void CrtlApresentacaoBacklog::excluirBacklog(WINDOW* win, const Email& emailLogado) {
    bool concluido = false;

    while (!concluido) {
        werase(win);
        box(win, 0, 0);

        wattron(win, COLOR_PAIR(1));
        mvwprintw(win, 0, 16, " EXCLUIR HISTORIA ");
        wattroff(win, COLOR_PAIR(1));

        mvwprintw(win, 2, 5, "Codigo: ");
        mvwprintw(win, 18, 2, "Pressione ESC para cancelar e sair");

        wrefresh(win);

        char strCodigo[16];

        wmove(win, 2, 14);

        if (!Tui::lerEntradaTerminal(win, strCodigo, 15, false)) {
            return;
        }

        try {
            Codigo codigoLocal(strCodigo);

            bool sucesso = servicoBacklog->excluirHistoriaUsuario(codigoLocal, emailLogado);

            if (sucesso) {
                wattron(win, COLOR_PAIR(3));
                mvwprintw(win, 12, 2,
                    "Historia excluida com sucesso!");
                wattroff(win, COLOR_PAIR(3));

                concluido = true;
            }
            else {
                wattron(win, COLOR_PAIR(2));
                mvwprintw(win, 12, 2,
                    "Historia nao encontrada.");
                wattroff(win, COLOR_PAIR(2));
            }

            wrefresh(win);
            wgetch(win);
        }
        catch (const std::invalid_argument& e) {
            wattron(win, COLOR_PAIR(2));
            mvwprintw(win, 12, 2, "Erro: %s", e.what());
            wattroff(win, COLOR_PAIR(2));

            wrefresh(win);
            wgetch(win);
        }
    }
}

void CrtlApresentacaoBacklog::associarHistoriaPessoa(WINDOW* win, const Email& emailLogado) {
    bool sair = false;

    while (!sair) {
        werase(win);
        box(win, 0, 0);

        wattron(win, COLOR_PAIR(1));
        mvwprintw(win, 0, 10, " ASSOCIAR HISTORIA A PESSOA ");
        wattroff(win, COLOR_PAIR(1));

        mvwprintw(win, 2, 5, "Codigo da Historia: ");
        mvwprintw(win, 4, 5, "Email da Pessoa:    ");
        mvwprintw(win, 18, 2, "Pressione ESC para cancelar e sair");

        wrefresh(win);

        char strCodigo[10];
        char strEmail[330];

        wmove(win, 2, 25);
        if (!Tui::lerEntradaTerminal(win, strCodigo, 9, false)) return;

        wmove(win, 4, 25);
        if (!Tui::lerEntradaTerminal(win, strEmail, 329, false)) return;

        try {
            Codigo codigoLocal(strCodigo);
            Email emailAlvo(strEmail);

            bool sucesso = servicoBacklog->associarHistoriaPessoa(codigoLocal, emailAlvo, emailLogado);

            if (sucesso) {
                wattron(win, COLOR_PAIR(3));
                mvwprintw(win, 8, 2, "Associacao realizada com sucesso!");
                wattroff(win, COLOR_PAIR(3));
                sair = true;
            } else {
                wattron(win, COLOR_PAIR(2));
                mvwprintw(win, 8, 2, "Erro: nao foi possivel associar. Verifique permissoes.");
                wattroff(win, COLOR_PAIR(2));
            }

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

void CrtlApresentacaoBacklog::removerAssociacaoHistoriaPessoa(WINDOW* win, const Email& emailLogado) {
    bool sair = false;

    while (!sair) {
        werase(win);
        box(win, 0, 0);

        wattron(win, COLOR_PAIR(1));
        mvwprintw(win, 0, 10, " REMOVER ASSOCIACAO HISTORIA/PESSOA ");
        wattroff(win, COLOR_PAIR(1));

        mvwprintw(win, 2, 5, "Codigo da Historia: ");
        mvwprintw(win, 4, 5, "Email da Pessoa:    ");
        mvwprintw(win, 18, 2, "Pressione ESC para cancelar e sair");

        wrefresh(win);

        char strCodigo[10];
        char strEmail[330];

        wmove(win, 2, 25);
        if (!Tui::lerEntradaTerminal(win, strCodigo, 9, false)) return;

        wmove(win, 4, 25);
        if (!Tui::lerEntradaTerminal(win, strEmail, 329, false)) return;

        try {
            Codigo codigoLocal(strCodigo);
            Email emailAlvo(strEmail);

            bool sucesso = servicoBacklog->removerAssociacaoHistoriaPessoa(codigoLocal, emailAlvo, emailLogado);

            if (sucesso) {
                wattron(win, COLOR_PAIR(3));
                mvwprintw(win, 8, 2, "Associacao removida com sucesso!");
                wattroff(win, COLOR_PAIR(3));
                sair = true;
            } else {
                wattron(win, COLOR_PAIR(2));
                mvwprintw(win, 8, 2, "Erro: nao foi possivel remover. Verifique permissoes.");
                wattroff(win, COLOR_PAIR(2));
            }

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

void CrtlApresentacaoBacklog::moverHistoriaProjetoParaSprint(WINDOW* win, const Email& emailLogado) {
    bool sair = false;

    while (!sair) {
        werase(win);
        box(win, 0, 0);

        wattron(win, COLOR_PAIR(1));
        mvwprintw(win, 0, 10, " MOVER HISTORIA PARA SPRINT ");
        wattroff(win, COLOR_PAIR(1));

        mvwprintw(win, 2, 5, "Codigo da Historia: ");
        mvwprintw(win, 4, 5, "Codigo do Sprint:   ");
        mvwprintw(win, 18, 2, "Pressione ESC para cancelar e sair");

        wrefresh(win);

        char strCodigoHistoria[10];
        char strCodigoSprint[10];

        wmove(win, 2, 25);
        if (!Tui::lerEntradaTerminal(win, strCodigoHistoria, 9, false)) return;

        wmove(win, 4, 25);
        if (!Tui::lerEntradaTerminal(win, strCodigoSprint, 9, false)) return;

        try {
            Codigo codigoHistoria(strCodigoHistoria);
            Codigo codigoSprint(strCodigoSprint);

            bool sucesso = servicoBacklog->moverHistoriaProjetoParaSprint(codigoHistoria, codigoSprint, emailLogado);

            if (sucesso) {
                wattron(win, COLOR_PAIR(3));
                mvwprintw(win, 8, 2, "Historia movida para o Sprint com sucesso!");
                wattroff(win, COLOR_PAIR(3));
                sair = true;
            } else {
                wattron(win, COLOR_PAIR(2));
                mvwprintw(win, 8, 2, "Erro: nao foi possivel mover. Verifique permissoes.");
                wattroff(win, COLOR_PAIR(2));
            }

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

void CrtlApresentacaoBacklog::alterarEstadoHistoria(WINDOW* win, const Email& emailLogado) {
    bool sair = false;

    while (!sair) {
        werase(win);
        box(win, 0, 0);

        wattron(win, COLOR_PAIR(1));
        mvwprintw(win, 0, 10, " ALTERAR ESTADO DA HISTORIA ");
        wattroff(win, COLOR_PAIR(1));

        mvwprintw(win, 2, 5, "Codigo da Historia: ");
        mvwprintw(win, 4, 5, "Novo Estado:        ");
        mvwprintw(win, 6, 5, "(A FAZER / FAZENDO / FEITO)");
        mvwprintw(win, 18, 2, "Pressione ESC para cancelar e sair");

        wrefresh(win);

        char strCodigo[10];
        char strEstado[21];

        wmove(win, 2, 25);
        if (!Tui::lerEntradaTerminal(win, strCodigo, 9, false)) return;

        wmove(win, 4, 25);
        if (!Tui::lerEntradaTerminal(win, strEstado, 20, false)) return;

        try {
            Codigo codigoLocal(strCodigo);
            Estado estadoLocal;
            estadoLocal.setValor(strEstado);

            bool sucesso = servicoBacklog->alterarEstadoHistoria(codigoLocal, estadoLocal, emailLogado);

            if (sucesso) {
                wattron(win, COLOR_PAIR(3));
                mvwprintw(win, 8, 2, "Estado alterado com sucesso!");
                wattroff(win, COLOR_PAIR(3));
                sair = true;
            } else {
                wattron(win, COLOR_PAIR(2));
                mvwprintw(win, 8, 2, "Erro: nao foi possivel alterar. Verifique permissoes.");
                wattroff(win, COLOR_PAIR(2));
            }

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
    if (this->servicoPessoa != nullptr) {
        this->servicoPessoa->lerPessoa(emailLogado, pessoaLogada); 
    }

    attron(COLOR_PAIR(6)); 
    mvprintw(0, 0, " Usuario logado: %s ", emailLogado.getValor().c_str());
    mvprintw(1, 0, " Papel Do Usuario: %s ", pessoaLogada.getPapel().getValor().c_str());
    attroff(COLOR_PAIR(6));
    refresh();
}   