#include "Controladoras/CrtlApresentacaoCadastro.hpp"
#include "Tui/tui.hpp"
#include "Entidades/pessoa.hpp"
#include <stdexcept>
#include <cstring>
#include <vector>

void CrtlApresentacaoCadastro::executar(const Email& emailSessao) {

    clear();
    refresh();
    // Se o email estiver vazio, executa fluxo de cadastro (Não Logado)
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
            excluirExistente(emailSessao);
            break;
        } else {
            break;
        }
    }

    delwin(winMenu);
}

void CrtlApresentacaoCadastro::cadastrarInexistente() {
    WINDOW* win = criarJanelaCadastro();
    char emailStr[80], senhaStr[30], nomeStr[30], papelStr[30];

    while (true) {
        desenharLayout(win, " CADASTRO SISTEMA ");
        touchwin(win); // <--- Diz ao Windows: "Essa janela agora manda na tela, atualize-a!"
        wrefresh(win);

        if (!capturarCampos(win, emailStr, senhaStr, nomeStr, papelStr)) {
            break;
        }

        mvwprintw(win, 11, 2, "                                              ");
        wrefresh(win);

        try {
            // 1. Validação de Formatos via Domínios
            std::string strEmail(emailStr);
            std::string strSenha(senhaStr);
            std::string strNome(nomeStr);
            std::string strPapel(papelStr);

            // 1. Validação de Formatos via Domínios (passando as variáveis estáveis)
            Email emailLocal(strEmail);
            Senha senhaLocal(strSenha);
            Nome nomeLocal(strNome);
            Papel papelLocal(strPapel);

            // 2. Criação da Entidade Pessoa
            Pessoa pessoaNova;
            pessoaNova.setEmail(emailLocal);
            pessoaNova.setSenha(senhaLocal);
            pessoaNova.setNome(nomeLocal);
            pessoaNova.setPapel(papelLocal);

            // 3. Comunicação com a Camada de Serviço (Stub)
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
    WINDOW* win = criarJanelaCadastro();
    char emailStr[80], senhaStr[30], nomeStr[30], papelStr[30];

    while (true) {
        desenharLayout(win, " ALTERAR CADASTRO ");

        if (!capturarCampos(win, emailStr, senhaStr, nomeStr, papelStr)) {
            break;
        }

        mvwprintw(win, 11, 2, "                                              ");
        wrefresh(win);

        try {
           // 1. Criamos objetos estáveis (lvalues) na memória para cada campo
            std::string strEmail(emailStr);
            std::string strSenha(senhaStr);
            std::string strNome(nomeStr);
            std::string strPapel(papelStr);

            // 2. Passamos as strings estáveis para os construtores de Domínio
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

    delwin(win);
}

void CrtlApresentacaoCadastro::excluirExistente(const Email& emailSessao) {
    WINDOW* win = criarJanelaCadastro();
    werase(win);
    box(win, 0, 0);

    wattron(win, COLOR_PAIR(2));
    mvwprintw(win, 3, 4, "CONFIRMACAO DE EXCLUSAO");
    wattroff(win, COLOR_PAIR(2));

    mvwprintw(win, 5, 4, "Conta alvo: %s", emailSessao.getValor().c_str());
    mvwprintw(win, 8, 2, "Pressione qualquer tecla para CONFIRMAR...");
    wrefresh(win);

    wgetch(win);

    // Envia o comando de exclusão para o stub validar
    if (servicoPessoa->excluirPessoa(emailSessao)) {
        exibirSucesso(win, "Conta deletada do sistema!");
    } else {
        exibirErro(win, "Erro: Falha ao deletar conta.");
    }

    delwin(win);
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
