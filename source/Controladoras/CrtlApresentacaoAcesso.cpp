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
#include "Entidades/pessoa.hpp"
#include <cstring>
#include "iostream"

#include "Containers/containerPessoa.hpp"

// Inclu�do para podermos fazer o dynamic_cast para a classe concreta de cadastro
#include "Controladoras/CrtlApresentacaoCadastro.hpp"

void CrtlApresentacaoAcesso::executar() {
    inicializarInterface();
    //declarando os topicos do menu
    const std::vector<std::string> opcoesDeslogadas = {"Realizar login", "Realizar cadastro", "Encerrar Sistema"};
    const std::vector<std::string> opcoesLogadas = {"Modulo de Cadastro (Pessoas)", "Modulo de Planejamento (Projetos e Sprints)", "Modulo de Backlog (Historias de Usuario)", "Fazer Logout", "Encerrar Sistema"};

    while (true) {
        limparTela();

        if (logado) {
            desenharCabecalho();
        }

        refresh();
        const auto& opcoes = logado ? opcoesLogadas : opcoesDeslogadas;
        const char* titulo = logado ? "MENU LOGADO" : "MENU PRINCIPAL";

        int escolha = Tui::exibeMenu(win, titulo, opcoes);// funcao que exibe os topicos
        if(!rotearEscolha(escolha, logado)) break;
    }

    finalizaInterface();
}

bool CrtlApresentacaoAcesso::rotearEscolha(int escolha, bool logado) {
    limparTela();
    if (!logado) {
        return processarMenuDeslogado(escolha);
    } else {
        return processarMenuLogado(escolha);
    }
}

bool CrtlApresentacaoAcesso::processarMenuDeslogado(int escolha) {
    switch (static_cast<MenuDeslogado>(escolha)) {
        case MenuDeslogado::Login:
            this->logado = crtlLogin->executar(emailSessao);
            // this->emailSessao.setValor("joao@teste.com"); //essa linha eu botei para logar rapidamente e testar alterar cadastro la dentro do sistema
            //this->logado = true;
            return true;
        case MenuDeslogado::Cadastro:
            crtlCadastro->executar(emailSessao);
            return true;
        case MenuDeslogado::Sair:
            return false;
        default:
            return true;
    }
}

bool CrtlApresentacaoAcesso::processarMenuLogado(int escolha) {
    switch (static_cast<MenuLogado>(escolha)) {
        case MenuLogado::CadastroPessoas: {
            this->crtlCadastro->executar(emailSessao);

            // Descobre com seguran�a se a conta foi exclu�da de fato l� dentro do m�dulo
            auto cadastroEspecifico = dynamic_cast<CrtlApresentacaoCadastro*>(this->crtlCadastro);
            if (cadastroEspecifico && cadastroEspecifico->getContaFoiExcluida()) {
                this->logado = false; // S� altera para deslogado se confirmou a exclus�o
            }
            return true;
        }
        case MenuLogado::Projetos:
            this-> crtlPlanejamento->executar(emailSessao);
            return true;
        case MenuLogado::Backlog:
            this->crtlBacklog->executar(emailSessao);
            return true;
        case MenuLogado::Logout:
            this->logado = false;
            this->emailSessao = Email();//reseta o objeto Email para o estado padr�o vazio
            return true;
        case MenuLogado::Sair:
            return false;
        default:
            return true;
    }
}

void CrtlApresentacaoAcesso::inicializarInterface() {
    Tui::inicializarTerminal(); // inicia com a janela
    criarJanelaMenu(); // cria janela
}

void CrtlApresentacaoAcesso::criarJanelaMenu() {
    int altura{10}, largura{50};
    int startY{(LINES - altura) / 2};
    int startX{(COLS - largura) / 2};

    win = newwin(altura, largura, startY, startX);
    box(win, 0, 0);
    keypad(win, TRUE);
}

void CrtlApresentacaoAcesso::limparTela() {
    wclear(win);
    wrefresh(win);
    clear();
    refresh();
}

void CrtlApresentacaoAcesso::desenharCabecalho() {
    Pessoa pessoaLogada;
    pessoaLogada.setEmail(emailSessao);
    ContainerPessoa::getInstancia()->lerPessoa(pessoaLogada);

    attron(COLOR_PAIR(5)); 
    mvprintw(0, 0, " Usuario logado: %s ", emailSessao.getValor().c_str());
    mvprintw(1, 0, " Papel Do Usuario: %s ", pessoaLogada.getPapel().getValor().c_str());
    attroff(COLOR_PAIR(5));
    refresh();
}   

void CrtlApresentacaoAcesso::finalizaInterface() {
    delwin(win);
    Tui::finalizarTerminal();
}
