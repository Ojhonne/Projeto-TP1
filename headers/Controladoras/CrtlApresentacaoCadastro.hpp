/**
 * * @file CrtlApresentacaoCadastro.hpp
 * @author Igor Melo
 * @brief Definição da controladora da apresentação de cadastro.
 */

#ifndef CRTL_APRESENTACAO_CADASTRO_HPP
#define CRTL_APRESENTACAO_CADASTRO_HPP

#ifdef _WIN32
    #include <curses.h>
#elif __linux__
    #include <ncurses.h>
#endif

#include "Interfaces/interfaces.hpp"
#include "Dominios/dominios.hpp"

/**
 * @class CrtlApresentacaoCadastro
 * @brief Controladora da apresentação de cadastro, responsável pelo gerenciamento de contas de usuários (Pessoas).
 * * Esta classe implementa a interface IApresentacaoCadastro e gerencia o ciclo de vida das credenciais de um usuário.
 * * A classe interage com o usuário via interface de terminal (ncurses), permitindo a criação de novos cadastros, 
 * * a alteração de dados de contas existentes e a exclusão definitiva do perfil de usuário por meio da camada de serviço.
 */
class CrtlApresentacaoCadastro : public IApresentacaoCadastro {
private:
    IServicoPessoa* servicoPessoa; /**< Referência para o servidor de gerenciamento de pessoas. */
    bool contaFoiExcluida;         /**< Flag indicativa se a conta ativa da sessão foi excluída durante a execução. */

    WINDOW* criarJanelaCadastro();
    void desenharLayout(WINDOW* win, const char* titulo);
    bool capturarCampos(WINDOW* win, char* emailStr, char* senhaStr, char* nomeStr, char* papelStr);
    void exibirErro(WINDOW* win, const char* mensaje);
    void exibirSucesso(WINDOW* win, const char* mensaje);
    void desenharCabecalho(WINDOW* win, const Email& emailSessao);

    void cadastrarInexistente();
    void atualizarExistente(const Email& emailSessao);
    bool excluirExistente(const Email& emailSessao);

public:
    /**
     * @brief Construtor padrão da classe controladora de cadastro.
     * * Inicializa o ponteiro de serviço como nulo e a flag de exclusão como falsa.
     */
    CrtlApresentacaoCadastro() : servicoPessoa(nullptr), contaFoiExcluida(false) {}

    /**
     * @brief Executa o fluxo de exibição de telas e menus do módulo de cadastro.
     * * Caso o e-mail da sessão esteja vazio, aciona o fluxo para criação de uma nova conta.
     * * Se houver um usuário logado ativo, renderiza o menu de gerenciamento (alteração de dados e exclusão).
     * * @param emailSessao Objeto que contém o e-mail do usuário atualmente autenticado no sistema.
     */
    void executar(const Email& emailSessao) override;

    /**
     * @brief Recupera o estado atual do gatilho de exclusão de conta.
     * * @return Retorna true se o usuário logado solicitou e confirmou a exclusão de sua própria conta, false caso contrário.
     */
    bool getContaFoiExcluida() const { return contaFoiExcluida; }

    /**
     * @brief Define a referência para o serviço de negócios de pessoa a ser utilizado pela controladora.
     * * @param servico É a referência para o serviço de gerenciamento de pessoas que executará as operações de CRUD.
     * * @return O método é do tipo void, portanto não retorna nenhum valor.
     */
    void setCtrlServicoPessoa(IServicoPessoa* servico) override {
        this->servicoPessoa = servico;
    }
};

#endif // CRTL_APRESENTACAO_CADASTRO_HPP
