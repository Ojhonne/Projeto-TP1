#include "Controladoras/CrtlApresentacaoCadastro.hpp"
#include "Tui/tui.hpp"
#include "Entidades/pessoa.hpp"
#include <stdexcept>
#include <cstring>
#include <vector>

void CrtlApresentacaoCadastro::executar(const Email& emailSessao) {
    this->contaFoiExcluida = false; // Reseta a flag ao entrar no m�dulo
    clear();
    refresh();

    // Se o email estiver vazio, executa fluxo de cadastro (N�o Logado)
    if (emailSessao.getValor().empty()) {
        cadastrarInexistente();
        return;
    }

    // Se o email estiver preenchido, executa fluxo de gerenciamento (Logado)
    WINDOW* winMenu = criarJanelaCadastro();
    std::vector<std::string> opcoes = {
        "Atualizar dados (Mudar cadastro)",
        "Excluir minha conta",
        "Voltar ao menu anterior"
    };

    while (true) {
        int escolha = Tui::exibeMenu(winMenu, "GERENCIAR CONTA", opcoes);
        if (escolha == 0) {
            atualizarExistente(emailSessao);
        } else if (escolha == 1) {
            // Se o usu�rio confirmou a exclus�o l� dentro:
            if (excluirExistente(emailSessao)) {
                this->contaFoiExcluida = true; // Ativa o gatilho para a classe de Acesso
                break; // Sai do menu de gerenciamento e encerra o m�todo
            }
            // Se retornou false (cancelou), o 'break' n�o roda e o loop continua na tela "GERENCIAR CONTA"
        } else {
            break;
        }
    }

    delwin(winMenu);
}

void CrtlApresentacaoCadastro::cadastrarInexistente() {
    WINDOW* win = criarJanelaCadastro();
    char emailStr[80], senhaStr[30], nomeStr[25], papelStr[30];
    while (true) {
        desenharLayout(win, " CADASTRO SISTEMA ");
        touchwin(win);
        wrefresh(win);

        if (!capturarCampos(win, emailStr, senhaStr, nomeStr, papelStr)) {
            break;
        }

        mvwprintw(win, 11, 2, "                                              ");
        wrefresh(win);

        try {
            std::string strEmail(emailStr);
            std::string strSenha(senhaStr);
            std::string strNome(nomeStr);
            std::string strPapel(papelStr);

            Email emailLocal(strEmail);
            Senha senhaLocal(strSenha);
            Nome nomeLocal(strNome);
            Papel papelLocal(strPapel);

            Pessoa pessoaNova;
            pessoaNova.setEmail(emailLocal);
            pessoaNova.setSenha(senhaLocal);
            pessoaNova.setNome(nomeLocal);
            pessoaNova.setPapel(papelLocal);

            if (servicoPessoa->criarPessoa(pessoaNova)) {
                exibirSucesso(win, "Sucesso! Cadastro efetuado.");
                break;
            } else {
                exibirErro(win, "Erro de Negocio: Email ja existe.");
            }
        }
        catch (const std::exception& e) {
            exibirErro(win, e.what());
        }
    }

    delwin(win);
}

void CrtlApresentacaoCadastro::atualizarExistente(const Email& emailSessao) {
    WINDOW* winCabecalho = newwin(10,55, 5, 22);
    box(winCabecalho, 0, 0);
    WINDOW* win = criarJanelaCadastro();
    char emailStr[85], senhaStr[30], nomeStr[20], papelStr[20];
    while (true) {
        desenharCabecalho(winCabecalho, emailSessao);
        desenharLayout(win, " ALTERAR CADASTRO ");
        if (!capturarCampos(win, emailStr, senhaStr, nomeStr, papelStr)) {
            break;
        }

        mvwprintw(win, 11, 2, "                                              ");
        wrefresh(win);

        try {
            std::string strEmail(emailStr);
            std::string strSenha(senhaStr);
            std::string strNome(nomeStr);
            std::string strPapel(papelStr);

            Email emailLocal(strEmail);
            Senha senhaLocal(strSenha);
            Nome nomeLocal(strNome);
            Papel papelLocal(strPapel);

            Pessoa pessoaAtualizada;
            pessoaAtualizada.setEmail(emailLocal);
            pessoaAtualizada.setSenha(senhaLocal);
            pessoaAtualizada.setNome(nomeLocal);
            pessoaAtualizada.setPapel(papelLocal);

            if (servicoPessoa->atualizarPessoa(pessoaAtualizada)) {
                exibirSucesso(win, "Sucesso! Cadastro atualizado.");
                break;
            } else {
                exibirErro(win, "Erro ao atualizar dados no Servico.");
            }
        }
        catch (const std::exception& e) {
            exibirErro(win, e.what());
        }
    }
    delwin(winCabecalho);
    delwin(win);
}

bool CrtlApresentacaoCadastro::excluirExistente(const Email& emailSessao) {
    WINDOW* win = criarJanelaCadastro();
    werase(win);
    box(win, 0, 0);

    wattron(win, COLOR_PAIR(2));
    mvwprintw(win, 3, 4, "CONFIRMACAO DE EXCLUSAO");
    wattroff(win, COLOR_PAIR(2));

    mvwprintw(win, 5, 4, "Conta alvo: %s", emailSessao.getValor().c_str());
    mvwprintw(win, 7, 4, "Deseja realmente excluir a conta?");
    mvwprintw(win, 9, 4, "[S] - Confirmar Exclusao");
    mvwprintw(win, 10, 4, "[Qualquer outra tecla] - Cancelar e Voltar");
    wrefresh(win);

    int ch = wgetch(win);

    if (ch == 'S' || ch == 's') {
        if (servicoPessoa->excluirPessoa(emailSessao)) {
            exibirSucesso(win, "Conta deletada do sistema!");
            delwin(win);
            return true; // Confirmou e deletou com sucesso
        } else {
            exibirErro(win, "Erro: Falha ao deletar conta.");
            delwin(win);
            return false;
        }
    } else {
        wattron(win, COLOR_PAIR(1));
        mvwprintw(win, 11, 2, "Exclusao cancelada pelo usuario.");
        wattroff(win, COLOR_PAIR(1));
        wrefresh(win);
        napms(1200);

        delwin(win);
        return false; // Cancelou a opera��o, retorna falso para manter o menu
    }
}

WINDOW* CrtlApresentacaoCadastro::criarJanelaCadastro() {
    int altura = 13, largura = 50;
    int startY = (LINES - altura) / 2;
    int startX = (COLS - largura) / 2;
    WINDOW* win = newwin(altura, largura, startY, startX);
    keypad(win, TRUE);
    return win;
}

void CrtlApresentacaoCadastro::desenharLayout(WINDOW* win, const char* titulo) {
    werase(win);
    box(win, 0, 0);
    wattron(win, COLOR_PAIR(1));
    mvwprintw(win, 0, (50 - std::strlen(titulo)) / 2, "%s", titulo);
    wattroff(win, COLOR_PAIR(1));
    mvwprintw(win, 2, 5, "Email: ");
    mvwprintw(win, 4, 5, "Senha: ");
    mvwprintw(win, 6, 5, "Nome: ");
    mvwprintw(win, 8, 5, "Papel: ");
    mvwprintw(win, 11, 2, "(Pressione ESC para cancelar)");
    wrefresh(win);
}

bool CrtlApresentacaoCadastro::capturarCampos(WINDOW* win, char* emailStr, char* senhaStr, char* nomeStr, char* papelStr) {
    wmove(win, 2, 13); wrefresh(win);
    if (!Tui::lerEntradaTerminal(win, emailStr, 79, false)) return false;
    wmove(win, 4, 13); wrefresh(win);
    if (!Tui::lerEntradaTerminal(win, senhaStr, 29, true)) return false;
    wmove(win, 6, 13); wrefresh(win);
    if (!Tui::lerEntradaTerminal(win, nomeStr, 29, false)) return false;
    wmove(win, 8, 13); wrefresh(win);
    if (!Tui::lerEntradaTerminal(win, papelStr, 29, false)) return false;
    return true;
}

void CrtlApresentacaoCadastro::exibirErro(WINDOW* win, const char* mensaje) {
    wattron(win, COLOR_PAIR(2));
    mvwprintw(win, 11, 2, "Erro: %s", mensaje);
    wattroff(win, COLOR_PAIR(2));
    wrefresh(win);
    wgetch(win);
}

void CrtlApresentacaoCadastro::exibirSucesso(WINDOW* win, const char* mensaje) {
    wattron(win, COLOR_PAIR(3));
    mvwprintw(win, 11, 2, "%s", mensaje);
    wattroff(win, COLOR_PAIR(3));
    wrefresh(win);
    napms(1500);
}
void CrtlApresentacaoCadastro::desenharCabecalho(WINDOW* win, const Email& emailSessao) {
    Pessoa pessoaLogada;
    pessoaLogada.setEmail(emailSessao);
    if (this->servicoPessoa != nullptr) {
        this->servicoPessoa->lerPessoa(emailSessao, pessoaLogada); 
    }
    wattron(win, COLOR_PAIR(6)); 
    mvwprintw(win, 1, 2, " Usuario logado: %s ", emailSessao.getValor().c_str());
    mvwprintw(win, 2, 2, " Papel Do Usuario: %s ", pessoaLogada.getPapel().getValor().c_str());
    wattroff(win, COLOR_PAIR(6));
    wrefresh(win);
}   
