/**
 * 
 * @file CrtlApresentacaoLogin.hpp
 * @brief Definição da controladora da apresentação de login.
 */

#ifndef CRTLAPRESENTACAOBACKLOG_H_INCLUDED
#define CRTLAPRESENTACAOBACKLOG_H_INCLUDED


#include "Dominios/dominios.hpp"
#include "Interfaces/interfaces.hpp"


/**
 * @class CtrlApresentacaoLogin
 * @brief Controladora da apresentação de login, responsável por interagir com o usuário e autenticá-lo.
 * * Esta classe implementa a interface IApresentacaoLogin e utiliza um serviço de autenticação para verificar 
 * as credenciais do usuário. A classe interage com o usuário via terminal (ncurses), captura o email e a senha, 
 * e os valida através da camada de serviço.
 */

class CrtlApresentacaoBacklog : public IApresentacaoBacklog{
    private:
        IServicoBacklog *servicoBacklog;  // Referência para servidor.
        WINDOW* win;
        WINDOW* criarJanelaBacklog();
        void desenharLayout(WINDOW* win);
        bool capturarCredenciais(WINDOW* win, char* emailStr, char* senhaStr);
        void exibirErro(WINDOW* win, const char* mensagem);
        void exibirSucesso(WINDOW* win);
        void criarBacklog(WINDOW* win);

    public:
        /**
         * @brief Destrutor virtual padrão.
         */
        virtual ~CrtlApresentacaoBacklog() = default;
        /**
         * @brief Define o metodo para autenticar o usuário.
         * * Solicita o email e a senha via interface de terminal. Se as credenciais forem válidas,
         * o objeto passado por referência será populado.
         * * @param email Objeto que receberá o email validado do usuário autenticado.
         * @return Retorna true se a autenticação for bem-sucedida, false caso contrário.
         */
        void executar(const Email&) override;

        /**
         * @brief Define a referência para o serviço de autenticação a ser utilizado pela controladora de apresentação de login.
         * @param IServicoAutenticacao é a referência para o serviço de autenticação que a controladora de apresentação de login utilizará para autenticar os usuários.
         * @return O método é do tipo void, portanto não retorna nenhum valor.
         */
        void setCtrlServicoBacklog(IServicoBacklog*) override;
};

inline void CrtlApresentacaoBacklog::setCtrlServicoBacklog(IServicoBacklog* servicoBacklog){
    this->servicoBacklog = servicoBacklog;
}

#endif // CRTLAPRESENTACAOLOGIN_H_INCLUDED