/**
 * @file CrtlApresentacaoPlanejamento.hpp
 * @author Eduardo Sankievicz Lima
 * @brief Definição da controladora da apresentação Planejamento.
 * @details Esta controladora é responsável por gerenciar a interação com o usuário no módulo de planejamento do sistema.
 * Ela implementa a interface IApresentacaoPlanejamento e utiliza um serviço de planejamento para realizar operações relacionadas às entidades Projeto e PlanoDeSprint. A controladora captura os dados informados pelo usuário, instancia os domínios e entidades correspondentes, e encaminha as operações para a camada de serviço.
 */

#ifndef CRTLAPRESENTACAOPLANEJAMENTO_H_INCLUDED 
#define CRTLAPRESENTACAOPLANEJAMENTO_H_INCLUDED

#ifdef _WIN32
    #include <curses.h> 
#elif __linux__
    #include <ncurses.h>
#else
    #error "Sistema operacional nao suportado para esta biblioteca."
#endif

#include <vector>
#include "Dominios/dominios.hpp"
#include "Interfaces/interfaces.hpp"
#include "Entidades/projeto.hpp"
#include "Entidades/planoDeSprint.hpp"

/**
 * @class CrtlApresentacaoPlanejamento
 * @brief Controladora de apresentação responsável pelo módulo de planejamento.
 *
 * Esta classe implementa a interface IApresentacaoPlanejamento e gerencia
 * as telas e menus relacionados às entidades Projeto e PlanoDeSprint.
 *
 * A controladora é responsável por capturar os dados informados pelo usuário,
 * instanciar os domínios e entidades correspondentes e encaminhar as operações
 * para a camada de serviço por meio da interface IServicoPlanejamento.
 */
class CrtlApresentacaoPlanejamento : public IApresentacaoPlanejamento {
private:
    IServicoPlanejamento *servicoPlanejamento;
    IServicoPessoa* servicoPessoa;
    WINDOW *win;

    void desenharCabecalho(const Email&);

    void menuProjetos(const Email&);
    void menuSprints(const Email&);

    void criarProjeto(const Email&);
    void lerProjeto();
    void atualizarProjeto(const Email&);
    void excluirProjeto(const Email&);
    void listarProjetos();

    void criarPlanoSprint(const Email&);
    void lerPlanoSprint();
    void atualizarPlanoSprint(const Email&);
    void excluirPlanoSprint(const Email&);
    void listarPlanosSprint();

public:
    /**
     * @brief Destrutor virtual padrão.
     */
    virtual ~CrtlApresentacaoPlanejamento() = default;

    /**
     * @brief Executa o módulo de apresentação de planejamento.
     *
     * Exibe o menu principal do módulo de planejamento e permite que o usuário
     * acesse as operações relacionadas a projetos e planos de sprint.
     *
     * @param email Email do usuário autenticado na sessão atual.
     */
    void executar(const Email& email) override;

    /**
     * @brief Define o serviço de planejamento associado à controladora.
     *
     * Armazena o ponteiro para a interface de serviço responsável por executar
     * as operações de negócio relacionadas a Projeto e PlanoDeSprint.
     *
     * @param servicoPlanejamento Ponteiro para objeto que implementa
     * IServicoPlanejamento.
     */
    void setCtrlServicoPlanejamento(IServicoPlanejamento *servicoPlanejamento) override;
        /**
     * @brief Define qual serviço gerencia as operações relacionadas à entidade Pessoa.
     */
    void setServicoPessoa(IServicoPessoa* servico);
};

inline void CrtlApresentacaoPlanejamento::setCtrlServicoPlanejamento(
    IServicoPlanejamento *servicoPlanejamento
) {
    this->servicoPlanejamento = servicoPlanejamento;
}
inline void CrtlApresentacaoPlanejamento::setServicoPessoa(IServicoPessoa* servico){
    this->servicoPessoa = servico;
}

#endif