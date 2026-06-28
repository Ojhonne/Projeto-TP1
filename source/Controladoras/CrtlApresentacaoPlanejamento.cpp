#ifdef _WIN32
    #include <curses.h> 
#elif __linux__
    #include <ncurses.h>
#else
    #error "Sistema operacional nao suportado para esta biblioteca."
#endif

#include "Controladoras/CrtlApresentacaoPlanejamento.hpp"
#include "Entidades/pessoa.hpp"
#include "Tui/tui.hpp"
#include <stdexcept>
#include <cstring>


// Menu principal do módulo de planejamento.
// Responsável apenas por navegar entre os submenus
// de Projetos e Planos de Sprint.
void CrtlApresentacaoPlanejamento::executar(const Email& emailLogado) {
    // Configura as cores utilizadas pelo módulo.
    // Pair 1: títulos.
    // Pair 2: mensagens de erro.
    // Pair 3: mensagens de sucesso.
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    init_pair(6, COLOR_BLUE, COLOR_BLACK);

    int altura = 10;
    int largura = 50;
    int startY = (LINES - altura) / 2;
    int startX = (COLS - largura) / 2;

    win = newwin(altura, largura, startY, startX);

    // Caso a criação da janela falhe, o módulo é encerrado
    // para evitar acessos a um ponteiro inválido.
    if (win == nullptr) {
        return;
    }

    box(win, 0, 0);
    keypad(win, TRUE);

    bool sair = false;

    std::vector<std::string> opcoes = {
        "Projetos",
        "Planos de Sprint",
        "Voltar"
    };

    //enquanto o usuário não escolher sair o programa continuará mostrando as opçoes(menu projeto ou menu sprint)
    while (!sair) {
        desenharCabecalho(emailLogado);
        //captura a opção desejada pelo usuário
        int opcao = Tui::exibeMenu(win, "PLANEJAMENTO", opcoes);
        switch (opcao) {
            case 0:
                menuProjetos(emailLogado);
                break;

            case 1:
                menuSprints(emailLogado);
                break;

            case 2:
                sair = true;
                break;

            default:
                break;
        }
    }

    //faz a deleção da janela da forma correta
    delwin(win);
    win = nullptr;
}

void CrtlApresentacaoPlanejamento::menuProjetos(const Email& emailLogado) {
    bool sair = false;

    std::vector<std::string> opcoes = {
        "Criar Projeto",
        "Ler Projeto",
        "Atualizar Projeto",
        "Excluir Projeto",
        "Listar projetos associados à pessoa",
        "Voltar"
    };

    //exibe as possíveis ações a serem feitas com os projetos até que o usuário escolha sair.
    while (!sair) {
        //captura a opção desejada pelo usuário
        int opcao = Tui::exibeMenu(win, "PROJETOS", opcoes);

        switch (opcao) {
            case 0:
                criarProjeto(emailLogado);
                break;

            case 1:
                lerProjeto();
                break;

            case 2:
                atualizarProjeto(emailLogado);
                break;

            case 3:
                excluirProjeto(emailLogado);
                break;

            case 4:
                listarProjetos();
                break;

            case 5:
                sair = true;
                break;

            default:
                break;
        }
    }
}


void CrtlApresentacaoPlanejamento::menuSprints(const Email& emailLogado) {
    bool sair = false;

    std::vector<std::string> opcoes = {
        "Criar Plano de Sprint",
        "Ler Plano de Sprint",
        "Atualizar Plano de Sprint",
        "Excluir Plano de Sprint",
        "Listar Planos de Sprint Associados à Projeto",
        "Voltar"
    };
    //exibe as possíveis ações a serem feitas com os planos de sprint até que o usuário escolha sair.
    while (!sair) {
        //captura a opção desejada pelo usuário.
        int opcao = Tui::exibeMenu(win, "PLANOS DE SPRINT", opcoes);

        switch (opcao) {
            case 0:
                criarPlanoSprint(emailLogado);
                break;

            case 1:
                lerPlanoSprint();
                break;

            case 2:
                atualizarPlanoSprint(emailLogado);
                break;

            case 3:
                excluirPlanoSprint(emailLogado);
                break;

            case 4:
                listarPlanosSprint();
                break;

            case 5:
                sair = true;
                break;

            default:
                break;
        }
    }
}

// Fluxo:
// 1. Captura os dados informados pelo usuário.
// 2. Instancia os domínios e a entidade Projeto.
// 3. Solicita a criação do projeto à camada de serviço.
// 4. Exibe mensagem de sucesso ou erro.
void CrtlApresentacaoPlanejamento::criarProjeto(const Email& emailLogado) {
    bool valido = false;

    while (!valido) {
        //monta a nova janela para a captura de dados para realizar a ação de criar um projeto.
        werase(win);
        box(win, 0, 0);

        wattron(win, COLOR_PAIR(1));
        mvwprintw(win, 0, 17, " CRIAR PROJETO ");
        wattroff(win, COLOR_PAIR(1));

        mvwprintw(win, 2, 5, "Codigo: ");
        mvwprintw(win, 3, 5, "Nome: ");
        mvwprintw(win, 4, 5, "Data inicio: ");
        mvwprintw(win, 5, 5, "Data fim: ");
        mvwprintw(win, 8, 2, "Pressione ESC para cancelar e sair");

        wrefresh(win);

        //inicializa as variáveis queserão capturadas do usuário
        char strCodigo[16];
        char strNome[21];
        char strDataInicio[21];
        char strDataFim[21];

       // Captura os dados necessários para instanciar os domínios
        // e montar a entidade Projeto.
        wmove(win, 2, 14);
        if (!Tui::lerEntradaTerminal(win, strCodigo, 15, false)) {
            return;
        }

        wmove(win, 3, 14);
        if (!Tui::lerEntradaTerminal(win, strNome, 20, false)) {
            return;
        }

        wmove(win, 4, 18);
        if (!Tui::lerEntradaTerminal(win, strDataInicio, 20, false)) {
            return;
        }

        wmove(win, 5, 15);
        if (!Tui::lerEntradaTerminal(win, strDataFim, 20, false)) {
            return;
        }

        // Tenta construir os domínios e a entidade Projeto.
        // Caso alguma validação dos domínios falhe,
        // a exceção é capturada e a operação é repetida.
        try {
            Codigo codigoLocal(strCodigo);
            Nome nomeLocal(strNome);

            Data dataInicioLocal;
            dataInicioLocal.setValor(strDataInicio);

            Data dataFimLocal;
            dataFimLocal.setValor(strDataFim);

            Projeto projetoLocal;
            projetoLocal.setCodigo(codigoLocal);
            projetoLocal.setNome(nomeLocal);
            projetoLocal.setInicio(dataInicioLocal);
            projetoLocal.setTermino(dataFimLocal);

            valido = servicoPlanejamento->criarProjeto(emailLogado, emailLogado, projetoLocal);

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


// Fluxo:
// 1. Solicita o código do projeto.
// 2. Encaminha a busca para a camada de serviço.
// 3. Caso encontrado, exibe os dados do projeto.
// 4. Caso contrário, informa que o projeto não existe.
void CrtlApresentacaoPlanejamento::lerProjeto() {
    bool sair = false;

    while (!sair) {
        werase(win);
        box(win, 0, 0);

        wattron(win, COLOR_PAIR(1));
        mvwprintw(win, 0, 17, " LER PROJETO ");
        wattroff(win, COLOR_PAIR(1));

        mvwprintw(win, 2, 5, "Codigo: ");
        mvwprintw(win, 8, 2, "Pressione ESC para cancelar e sair");

        wrefresh(win);

        char strCodigo[16];

        wmove(win, 2, 14);
        if (!Tui::lerEntradaTerminal(win, strCodigo, 15, false)) {
            return;
        }

        try {
            Codigo codigoLocal(strCodigo);

            Projeto projetoLocal;

            bool encontrado = servicoPlanejamento->lerProjeto(codigoLocal, projetoLocal);

            werase(win);
            box(win, 0, 0);

            wattron(win, COLOR_PAIR(1));
            mvwprintw(win, 0, 17, " DADOS DO PROJETO ");
            wattroff(win, COLOR_PAIR(1));

            if (encontrado) {
                mvwprintw(win, 2, 5, "Codigo: %s", projetoLocal.getCodigo().getValor().c_str());
                mvwprintw(win, 3, 5, "Nome: %s", projetoLocal.getNome().getValor().c_str());
                mvwprintw(win, 4, 5, "Data inicio: %s", projetoLocal.getInicio().getValor().c_str());
                mvwprintw(win, 5, 5, "Data fim: %s", projetoLocal.getTermino().getValor().c_str());

                wattron(win, COLOR_PAIR(3));
                mvwprintw(win, 8, 2, "Pressione qualquer tecla para voltar.");
                wattroff(win, COLOR_PAIR(3));
                wrefresh(win);
                wgetch(win);

                sair = true;
            } else {
                wattron(win, COLOR_PAIR(2));
                mvwprintw(win, 8, 2, "Projeto nao encontrado. Pressione tecla.");
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

// Fluxo:
// 1. Obtém o código do projeto a ser atualizado.
// 2. Captura os novos dados.
// 3. Monta uma entidade Projeto contendo os valores atualizados.
// 4. Solicita a atualização à camada de serviço.
void CrtlApresentacaoPlanejamento::atualizarProjeto(const Email& emailLogado) {
    bool valido = false;

    while (!valido) {
        werase(win);
        box(win, 0, 0);

        wattron(win, COLOR_PAIR(1));
        mvwprintw(win, 0, 15, " ATUALIZAR PROJETO ");
        wattroff(win, COLOR_PAIR(1));

        mvwprintw(win, 2, 5, "Codigo: ");
        mvwprintw(win, 3, 5, "Novo nome: ");
        mvwprintw(win, 4, 5, "Nova data inicio: ");
        mvwprintw(win, 5, 5, "Nova data fim: ");
        mvwprintw(win, 8, 2, "Pressione ESC para cancelar e sair");

        wrefresh(win);

        char strCodigo[16];
        char strNome[21];
        char strDataInicio[21];
        char strDataFim[21];

        wmove(win, 2, 14);
        if (!Tui::lerEntradaTerminal(win, strCodigo, 15, false)) {
            return;
        }

        wmove(win, 3, 16);
        if (!Tui::lerEntradaTerminal(win, strNome, 20, false)) {
            return;
        }

        wmove(win, 4, 23);
        if (!Tui::lerEntradaTerminal(win, strDataInicio, 20, false)) {
            return;
        }

        wmove(win, 5, 20);
        if (!Tui::lerEntradaTerminal(win, strDataFim, 20, false)) {
            return;
        }

        try {
            Codigo codigoLocal(strCodigo);
            Nome nomeLocal(strNome);

            Data dataInicioLocal;
            dataInicioLocal.setValor(strDataInicio);

            Data dataFimLocal;
            dataFimLocal.setValor(strDataFim);

            Projeto projetoLocal;
            projetoLocal.setCodigo(codigoLocal);
            projetoLocal.setNome(nomeLocal);
            projetoLocal.setInicio(dataInicioLocal);
            projetoLocal.setTermino(dataFimLocal);

            valido = servicoPlanejamento->atualizarProjeto(emailLogado, projetoLocal);

            if (valido) {
                wattron(win, COLOR_PAIR(3));
                mvwprintw(win, 8, 2, "Projeto atualizado com sucesso!");
                wattroff(win, COLOR_PAIR(3));
                wrefresh(win);
                wgetch(win);
            } else {
                wattron(win, COLOR_PAIR(2));
                mvwprintw(win, 8, 2, "Erro: projeto nao foi atualizado.");
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

// Fluxo:
// 1. Obtém o código do projeto.
// 2. Solicita a exclusão à camada de serviço.
// 3. Informa ao usuário o resultado da operação.
void CrtlApresentacaoPlanejamento::excluirProjeto(const Email& emailLogado) {
    bool concluido = false;

    while (!concluido) {
        werase(win);
        box(win, 0, 0);

        wattron(win, COLOR_PAIR(1));
        mvwprintw(win, 0, 16, " EXCLUIR PROJETO ");
        wattroff(win, COLOR_PAIR(1));

        mvwprintw(win, 2, 5, "Codigo: ");
        mvwprintw(win, 8, 2, "Pressione ESC para cancelar e sair");

        wrefresh(win);

        char strCodigo[16];

        wmove(win, 2, 14);

        if (!Tui::lerEntradaTerminal(win, strCodigo, 15, false)) {
            return;
        }

        try {
            Codigo codigoLocal(strCodigo);

            bool sucesso =
                servicoPlanejamento->excluirProjeto(emailLogado, codigoLocal);

            if (sucesso) {
                wattron(win, COLOR_PAIR(3));
                mvwprintw(win, 8, 2,
                    "Projeto excluido com sucesso!");
                wattroff(win, COLOR_PAIR(3));

                concluido = true;
            }
            else {
                wattron(win, COLOR_PAIR(2));
                mvwprintw(win, 8, 2,
                    "Projeto nao encontrado.");
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

void CrtlApresentacaoPlanejamento::listarProjetos() {
    bool sair = false;

    while (!sair) {
        werase(win);
        box(win, 0, 0);

        wattron(win, COLOR_PAIR(1));
        mvwprintw(win, 0, 10, " LISTAR PROJETOS POR PESSOA ");
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
            std::vector<Projeto> projetos;

            bool encontrado = servicoPlanejamento->
                listarProjetos(emailLocal, projetos);

            werase(win);
            box(win, 0, 0);

            wattron(win, COLOR_PAIR(1));
            mvwprintw(win, 0, 10, " PROJETOS ASSOCIADOS ");
            wattroff(win, COLOR_PAIR(1));

            if (encontrado && !projetos.empty()) {
                mvwprintw(win, 2, 5, "Email: %s", emailLocal.getValor().c_str());
                mvwprintw(win, 4, 5, "Codigos dos projetos:");

                int linha = 5;

                for (size_t i = 0; i < projetos.size(); i++) {
                    mvwprintw(
                        win,
                        linha,
                        7,
                        "%zu - %s",
                        i + 1,
                        projetos[i].getCodigo().getValor().c_str()
                    );

                    linha++;
                    //chegou no limite, cria uma nova janela
                    if ((linha >= 8 && i + 1 < projetos.size())) {
                        mvwprintw(win, 8, 2, "Pressione tecla para continuar...");
                        wrefresh(win);
                        wgetch(win);

                        werase(win);
                        box(win, 0, 0);

                        wattron(win, COLOR_PAIR(1));
                        mvwprintw(win, 0, 10, " PROJETOS ASSOCIADOS ");
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
                mvwprintw(win, 8, 2, "Nenhum projeto encontrado. Pressione tecla.");
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


// Fluxo:
// 1. Captura os dados informados pelo usuário.
// 2. Instancia os domínios e a entidade PlanoDeSprint.
// 3. Solicita a criação do plano de sprint à camada de serviço.
// 4. Exibe mensagem de sucesso ou erro.
void CrtlApresentacaoPlanejamento::criarPlanoSprint(const Email& emailLogado) {
    bool valido = false;

    while (!valido) {

        werase(win);
        box(win, 0, 0);

        wattron(win, COLOR_PAIR(1));
        mvwprintw(win, 0, 14, " CRIAR PLANO DE SPRINT ");
        wattroff(win, COLOR_PAIR(1));

        mvwprintw(win, 2, 5, "Codigo plano: ");
        mvwprintw(win, 3, 5, "Codigo projeto: ");
        mvwprintw(win, 4, 5, "Objetivo: ");
        mvwprintw(win, 5, 5, "Tempo: ");

        mvwprintw(win, 8, 2, "Pressione ESC para cancelar e sair");

        wrefresh(win);

        char strCodigoPlano[16];
        char strCodigoProjeto[16];
        char strTexto[51];
        char strTempo[14];

        wmove(win, 2, 19);
        if (!Tui::lerEntradaTerminal(win, strCodigoPlano, 15, false)) {
            return;
        }

        wmove(win, 3, 21);
        if (!Tui::lerEntradaTerminal(win, strCodigoProjeto, 15, false)) {
            return;
        }

        wmove(win, 4, 15);
        if (!Tui::lerEntradaTerminal(win, strTexto, 50, false)) {
            return;
        }

        wmove(win, 5, 12);
        if (!Tui::lerEntradaTerminal(win, strTempo, 13, false)) {
            return;
        }

        try {
            Codigo codigoPlanoLocal(strCodigoPlano);
            Codigo codigoProjetoLocal(strCodigoProjeto);
            Texto textoLocal(strTexto);
            Tempo tempoLocal(strTempo);

            PlanoDeSprint planoLocal;

            planoLocal.setCodigo(codigoPlanoLocal);
            planoLocal.setTexto(textoLocal);
            planoLocal.setTempo(tempoLocal);

            valido = servicoPlanejamento->criarPlanoSprint(
                emailLogado,
                codigoProjetoLocal,
                planoLocal
            );

            if (valido) {
                wattron(win, COLOR_PAIR(3));
                mvwprintw(win, 8, 2, "Plano criado com sucesso!");
                wattroff(win, COLOR_PAIR(3));
            }
            else {
                wattron(win, COLOR_PAIR(2));
                mvwprintw(win, 8, 2, "Falha ao criar plano.");
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

// Fluxo:
// 1. Solicita o código do plano de sprint.
// 2. Encaminha a busca para a camada de serviço.
// 3. Caso encontrado, exibe os dados do plano de sprint.
// 4. Caso contrário, informa que o plano não existe.
void CrtlApresentacaoPlanejamento::lerPlanoSprint() {
    bool sair = false;

    while (!sair) {
        werase(win);
        box(win, 0, 0);

        wattron(win, COLOR_PAIR(1));
        mvwprintw(win, 0, 14, " LER PLANO DE SPRINT ");
        wattroff(win, COLOR_PAIR(1));

        mvwprintw(win, 2, 5, "Codigo: ");
        mvwprintw(win, 8, 2, "Pressione ESC para cancelar e sair");

        wrefresh(win);

        char strCodigo[16];

        wmove(win, 2, 14);
        if (!Tui::lerEntradaTerminal(win, strCodigo, 15, false)) {
            return;
        }

        try {
            Codigo codigoLocal(strCodigo);

            PlanoDeSprint planoLocal;

            bool encontrado =
                servicoPlanejamento->lerPlanoSprint(codigoLocal, planoLocal);

            werase(win);
            box(win, 0, 0);

            wattron(win, COLOR_PAIR(1));
            mvwprintw(win, 0, 12, " DADOS DO PLANO DE SPRINT ");
            wattroff(win, COLOR_PAIR(1));

            if (encontrado) {
                mvwprintw(win, 2, 5, "Codigo: %s",
                    planoLocal.getCodigo().getValor().c_str());

                mvwprintw(win, 3, 5, "Objetivo: %s",
                    planoLocal.getTexto().getValor().c_str());

                mvwprintw(win, 4, 5, "Tempo: %s",
                    planoLocal.getTempo().getValor().c_str());

                wattron(win, COLOR_PAIR(3));
                mvwprintw(win, 8, 2, "Pressione qualquer tecla para voltar.");
                wattroff(win, COLOR_PAIR(3));

                wrefresh(win);
                wgetch(win);

                sair = true;
            }
            else {
                wattron(win, COLOR_PAIR(2));
                mvwprintw(win, 8, 2, "Plano nao encontrado. Pressione tecla.");
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


// Fluxo:
// 1. Obtém o código do plano de sprint a ser atualizado.
// 2. Captura os novos dados do plano.
// 3. Monta uma entidade PlanoDeSprint contendo os valores atualizados.
// 4. Solicita a atualização à camada de serviço.
// 5. Exibe mensagem de sucesso ou erro.
void CrtlApresentacaoPlanejamento::atualizarPlanoSprint(const Email& emailLogado) {
    bool valido = false;

    while (!valido) {
        werase(win);
        box(win, 0, 0);

        wattron(win, COLOR_PAIR(1));
        mvwprintw(win, 0, 11, " ATUALIZAR PLANO DE SPRINT ");
        wattroff(win, COLOR_PAIR(1));

        mvwprintw(win, 2, 5, "Codigo: ");
        mvwprintw(win, 3, 5, "Novo objetivo: ");
        mvwprintw(win, 4, 5, "Novo tempo: ");
        mvwprintw(win, 8, 2, "Pressione ESC para cancelar e sair");

        wrefresh(win);

        char strCodigo[16];
        char strTexto[51];
        char strTempo[14];

        wmove(win, 2, 14);
        if (!Tui::lerEntradaTerminal(win, strCodigo, 15, false)) {
            return;
        }

        wmove(win, 3, 20);
        if (!Tui::lerEntradaTerminal(win, strTexto, 50, false)) {
            return;
        }

        wmove(win, 4, 17);
        if (!Tui::lerEntradaTerminal(win, strTempo, 13, false)) {
            return;
        }

        try {
            Codigo codigoLocal(strCodigo);
            Texto textoLocal(strTexto);
            Tempo tempoLocal(strTempo);

            PlanoDeSprint planoLocal;
            planoLocal.setCodigo(codigoLocal);
            planoLocal.setTexto(textoLocal);
            planoLocal.setTempo(tempoLocal);

            valido = servicoPlanejamento->atualizarPlanoSprint(emailLogado, planoLocal);

            if (valido) {
                wattron(win, COLOR_PAIR(3));
                mvwprintw(win, 8, 2, "Plano atualizado com sucesso!");
                wattroff(win, COLOR_PAIR(3));
            } else {
                wattron(win, COLOR_PAIR(2));
                mvwprintw(win, 8, 2, "Erro: plano nao foi atualizado.");
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

// Fluxo:
// 1. Obtém o código do plano de sprint.
// 2. Solicita a exclusão à camada de serviço.
// 3. Informa ao usuário o resultado da operação.
void CrtlApresentacaoPlanejamento::excluirPlanoSprint(const Email& emailLogado) {
    bool concluido = false;

    while (!concluido) {
        werase(win);
        box(win, 0, 0);

        wattron(win, COLOR_PAIR(1));
        mvwprintw(win, 0, 13, " EXCLUIR PLANO DE SPRINT ");
        wattroff(win, COLOR_PAIR(1));

        mvwprintw(win, 2, 5, "Codigo: ");
        mvwprintw(win, 8, 2, "Pressione ESC para cancelar e sair");

        wrefresh(win);

        char strCodigo[16];

        wmove(win, 2, 14);

        if (!Tui::lerEntradaTerminal(win, strCodigo, 15, false)) {
            return;
        }

        try {
            Codigo codigoLocal(strCodigo);

            bool sucesso =
                servicoPlanejamento->excluirPlanoSprint(emailLogado, codigoLocal);

            if (sucesso) {
                wattron(win, COLOR_PAIR(3));
                mvwprintw(win, 8, 2,
                    "Plano excluido com sucesso!");
                wattroff(win, COLOR_PAIR(3));

                concluido = true;
            }
            else {
                wattron(win, COLOR_PAIR(2));
                mvwprintw(win, 8, 2,
                    "Plano nao encontrado.");
                wattroff(win, COLOR_PAIR(2));
            }

            wrefresh(win);
            wgetch(win);
        }
        catch (const std::invalid_argument& e) {
            wattron(win, COLOR_PAIR(2));
            mvwprintw(win, 8, 2,
                "Erro: %s", e.what());
            wattroff(win, COLOR_PAIR(2));

            wrefresh(win);
            wgetch(win);
        }
    }
}

void CrtlApresentacaoPlanejamento::listarPlanosSprint() {
    bool sair = false;

    while (!sair) {
        werase(win);
        box(win, 0, 0);

        wattron(win, COLOR_PAIR(1));
        mvwprintw(win, 0, 7, " LISTAR PLANOS POR PROJETO ");
        wattroff(win, COLOR_PAIR(1));

        mvwprintw(win, 2, 5, "Codigo do projeto: ");
        mvwprintw(win, 8, 2, "Pressione ESC para cancelar e sair");

        wrefresh(win);

        char strCodigo[16];

        wmove(win, 2, 24);
        if (!Tui::lerEntradaTerminal(win, strCodigo, 15, false)) {
            return;
        }

        try {
            Codigo codigoProjeto(strCodigo);
            std::vector<PlanoDeSprint> planos;

            bool encontrado = servicoPlanejamento->
                listarPlanosSprint(codigoProjeto, planos);

            werase(win);
            box(win, 0, 0);

            wattron(win, COLOR_PAIR(1));
            mvwprintw(win, 0, 7, " PLANOS DE SPRINT ASSOCIADOS ");
            wattroff(win, COLOR_PAIR(1));

            if (encontrado && !planos.empty()) {
                mvwprintw(win, 2, 5, "Projeto: %s",
                    codigoProjeto.getValor().c_str());

                mvwprintw(win, 4, 5, "Codigos dos planos:");

                int linha = 5;
                const int linhaLimite = 8;

                for (size_t i = 0; i < planos.size(); i++) {
                    mvwprintw(
                        win,
                        linha,
                        7,
                        "%zu - %s",
                        i + 1,
                        planos[i].getCodigo().getValor().c_str()
                    );

                    linha++;

                    if (linha >= linhaLimite && i + 1 < planos.size()) {
                        mvwprintw(win, 8, 2, "Pressione tecla para continuar...");
                        wrefresh(win);
                        wgetch(win);

                        werase(win);
                        box(win, 0, 0);

                        wattron(win, COLOR_PAIR(1));
                        mvwprintw(win, 0, 7, " PLANOS DE SPRINT ASSOCIADOS ");
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
                mvwprintw(win, 8, 2, "Nenhum plano encontrado. Pressione tecla.");
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

void CrtlApresentacaoPlanejamento::desenharCabecalho(const Email& emailLogado) {
    //Variaveis para o cabeçalho
    Pessoa pessoaLogada;
    pessoaLogada.setEmail(emailLogado);
    if (this->servicoPessoa != nullptr) {
        this->servicoPessoa->lerPessoa(emailLogado, pessoaLogada); 
    }
    attron(COLOR_PAIR(5)); 
    mvprintw(0, 0, " Usuario logado: %s ", emailLogado.getValor().c_str());
    mvprintw(1, 0, " Papel Do Usuario: %s ", pessoaLogada.getPapel().getValor().c_str());
    attroff(COLOR_PAIR(5));
    refresh();
}   