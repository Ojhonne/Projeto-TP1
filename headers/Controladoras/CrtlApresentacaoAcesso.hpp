/**
 * 
 * @file CrtlApresentacaoAcesso.hpp
 * @author João Francisco de Sousa Torres 
 * @brief Definição da controladora da apresentação acesso(menu principal).
 * @details Esta controladora é responsável por gerenciar a interação com o usuário no menu principal do sistema.
 * Ela implementa a interface IApresentacaoAcesso e utiliza serviços de autenticação, 
 * cadastro, planejamento e backlog para realizar operações relacionadas às entidades Pessoa, Projeto, PlanoDeSprint e HistoriaDeUsuario. A controladora captura os dados informados pelo usuário, instancia os domínios e entidades correspondentes, e encaminha as operações para a camada de serviço.
 */

#ifndef CRTLAPRESENTACAOACESSO_HPP_INCLUDED
#define CRTLAPRESENTACAOACESSO_HPP_INCLUDED

#include "Dominios/dominios.hpp"

class IApresentacaoLogin;
class IApresentacaoCadastro;
class IApresentacaoPlanejamento;
class IApresentacaoBacklog;

/**
 * @enum MenuDeslogado
 * @brief Representa as opções disponíveis no menu principal quando o usuário não está logado.
 */
enum class MenuDeslogado { Login = 0, Cadastro, Sair };
/**
 * @enum MenuLogado
 * @brief Representa as opções disponíveis no menu principal quando o usuário está logado.
 */
enum class MenuLogado { CadastroPessoas = 0, Projetos, Backlog, Logout, Sair };

/**
 * @class CrtlApresentacaoAcesso
 * @brief Funciona como uma interface principal do sistema, ou seja, as telas e menus 
com os quais o usuário interage diretamente. \n
 * Ele é responsável por exibir os 
formulários de login, os cadastros e os painéis de controle e gerenciar a navegação entre eles.
 */
class CrtlApresentacaoAcesso {
    private:
        IApresentacaoLogin* crtlLogin;
        IApresentacaoCadastro* crtlCadastro; 
        IApresentacaoPlanejamento* crtlPlanejamento;
        IApresentacaoBacklog* crtlBacklog;

        Email emailSessao; 
        bool logado{false};
        WINDOW* win;

        void inicializarInterface();
        void finalizaInterface();
        bool rotearEscolha(int escolha, bool logado);

        void criarJanelaMenu();
        
        void limparTela();
        void desenharCabecalho();
        
        bool processarMenuDeslogado(int escolha);
        bool processarMenuLogado(int escolha);
    public:
      
        /**
         * @brief Destrutor virtual .
        */
        virtual ~CrtlApresentacaoAcesso() = default;
        /**
         * @brief Executa método que exibe o menu principal do sistema. \n
         *Enquanto nenhuma pessoa estiver logado, apenas autenticação fica disponível.
         * Ao logar, todas as áreas do sistema são liberadas ao usuário.
         */
        void executar(); 
        /**
         * @brief Define qual controladora gerencia o Login.
         */
        void setCtrlLogin(IApresentacaoLogin*) ;
        /**
         * @brief Define qual controladora gerencia o Cadastro.
         */
        void setCtrlCadastro(IApresentacaoCadastro*) ;
         /**
         * @brief Define qual controladora gerencia o Planejamento do projeto.
         */
        void setCtrlPlanejamento(IApresentacaoPlanejamento*) ;
        /**
         * @brief Define qual controladora gerencia o Backlog.
         */
        void setCtrlBacklog(IApresentacaoBacklog*) ;
};
inline void CrtlApresentacaoAcesso::setCtrlLogin(IApresentacaoLogin* crtlLogin) {
    this->crtlLogin = crtlLogin;
}
inline void CrtlApresentacaoAcesso::setCtrlCadastro(IApresentacaoCadastro* crtlCadastro) {
    this->crtlCadastro = crtlCadastro;
}
inline void CrtlApresentacaoAcesso::setCtrlPlanejamento(IApresentacaoPlanejamento* crtlPlanejamento) {
    this->crtlPlanejamento = crtlPlanejamento;
}
inline void CrtlApresentacaoAcesso::setCtrlBacklog(IApresentacaoBacklog* crtlBacklog) {
    this->crtlBacklog = crtlBacklog;
}

#endif // CRTLAPRESENTACAOACESSO_HPP_INCLUDED