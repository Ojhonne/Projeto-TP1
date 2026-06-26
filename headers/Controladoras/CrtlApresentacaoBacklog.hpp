/**
 * 
 * @file CrtlApresentacaoBacklog.hpp
 * @author Fabio Willian Alves Silva 
 * @brief Definição da controladora da apresentação de backlog.
 * @details Esta controladora é responsável por gerenciar a interação com o usuário no módulo de backlog do sistema.
 * Ela implementa a interface IApresentacaoBacklog e utiliza um serviço de backlog para realizar operações relacionadas às entidades HistoriaDeUsuario e Backlog. 
 * A controladora captura os dados informados pelo usuário, instancia os domínios e entidades correspondentes, e encaminha as operações para a camada de serviço.
 */

#ifndef CRTLAPRESENTACAOBACKLOG_H_INCLUDED
#define CRTLAPRESENTACAOBACKLOG_H_INCLUDED


#include "Dominios/dominios.hpp"
#include "Interfaces/interfaces.hpp"


/**
 * @class CrtlApresentacaoBacklog
 * @brief Controladora da apresentação de backlog, responsável por interagir com o usuário e gerenciar o backlog.
 * * Esta classe implementa a interface IApresentacaoBacklog e utiliza um serviço de backlog para verificar 
 * as informações do usuário. A classe interage com o usuário via terminal (ncurses), captura o email e a senha, 
 * e os valida através da camada de serviço.
 */

class CrtlApresentacaoBacklog : public IApresentacaoBacklog{
    private:
        IServicoBacklog *servicoBacklog;  // Referência para servidor.
        WINDOW* win;
        WINDOW* criarJanelaBacklog(int altura, int largura);
        void desenharCabecalho(const Email&);
        void desenharLayout(WINDOW* win);
        bool capturarCredenciais(WINDOW* win, char* emailStr, char* senhaStr);
        void exibirErro(WINDOW* win, const char* mensagem);
        void exibirSucesso(WINDOW* win);
        void criarBacklog(WINDOW* win, const Email& emailLogado);
        void lerBacklog(WINDOW* win);

    public:
        /**
         * @brief Destrutor virtual padrão.
         */
        virtual ~CrtlApresentacaoBacklog() = default;
        /**
         * @brief Executa a controladora da apresentação de backlog.
         * @param Email é o email do usuário logado.
         * 
         */
        void executar(const Email&) override;
        /**
         * @brief Define o serviço de backlog a ser utilizado pela controladora.
         * @param servicoBacklog é um ponteiro para o serviço de backlog.
         */
        void setCtrlServicoBacklog(IServicoBacklog*) override;
};

inline void CrtlApresentacaoBacklog::setCtrlServicoBacklog(IServicoBacklog* servicoBacklog){
    this->servicoBacklog = servicoBacklog;
}

#endif // CRTLAPRESENTACAOBACKLOG_H_INCLUDED