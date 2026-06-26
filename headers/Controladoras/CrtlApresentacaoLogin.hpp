/**
 * 
 * @file CrtlApresentacaoLogin.hpp
 * @author João Francisco de Sousa Torres
 * @brief Definição da controladora da apresentação de login.
 */

#ifndef CRTLAPRESENTACAOLOGIN_H_INCLUDED
#define CRTLAPRESENTACAOLOGIN_H_INCLUDED


#include "Dominios/dominios.hpp"
#include "Interfaces/interfaces.hpp"


/**
 * @class CrtlApresentacaoLogin
 * @brief Controladora da apresentação de login, responsável por interagir com o usuário e autenticá-lo.
 * * Esta classe implementa a interface IApresentacaoLogin e utiliza um serviço de autenticação para verificar 
 * as credenciais do usuário. A classe interage com o usuário via terminal (ncurses), captura o email e a senha, 
 * e os valida através da camada de serviço.
 */

class CrtlApresentacaoLogin : public IApresentacaoLogin{
    private:
        IServicoAutenticacao *servicoAutenticacao;  // Referência para servidor.
        
        WINDOW* criarJanelaLogin();
        void desenharLayout(WINDOW* win);
        bool capturarCredenciais(WINDOW* win, char* emailStr, char* senhaStr);
        void exibirErro(WINDOW* win, const char* mensagem);
        void exibirSucesso(WINDOW* win);

    public:
        /**
         * @brief Destrutor virtual padrão.
         */
        virtual ~CrtlApresentacaoLogin() = default;
        /**
         * @brief Define o metodo para autenticar o usuário.
         * * Solicita o email e a senha via interface de terminal. Se as credenciais forem válidas,
         * o objeto passado por referência será populado.
         * * @param email Objeto que receberá o email validado do usuário autenticado.
         * @return Retorna true se a autenticação for bem-sucedida, false caso contrário.
         */
        bool executar(Email&) override;

        /**
         * @brief Define a referência para o serviço de autenticação a ser utilizado pela controladora de apresentação de login.
         * @param IServicoAutenticacao é a referência para o serviço de autenticação que a controladora de apresentação de login utilizará para autenticar os usuários.
         * @return O método é do tipo void, portanto não retorna nenhum valor.
         */
        void setCtrlServicoAutenticacao(IServicoAutenticacao*) override;
};

inline void CrtlApresentacaoLogin::setCtrlServicoAutenticacao(IServicoAutenticacao* servicoAutenticacao){
    this->servicoAutenticacao = servicoAutenticacao;
}

#endif // CRTLAPRESENTACAOLOGIN_H_INCLUDED