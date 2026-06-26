/**
 * @file CrtlApresentacaoPlanejamento.hpp
 * @author Eduardo Sankievicz Lima
 * @brief Definição da controladora da apresentação Planejamento.
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
    WINDOW *win;

    void desenharCabecalho(const Email&);

    void menuProjetos();
    void menuSprints();

    void criarProjeto();
    void lerProjeto();
    void atualizarProjeto();
    void excluirProjeto();
    void listarProjetos();

    void criarPlanoSprint();
    void lerPlanoSprint();
    void atualizarPlanoSprint();
    void excluirPlanoSprint();
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
};

inline void CrtlApresentacaoPlanejamento::setCtrlServicoPlanejamento(
    IServicoPlanejamento *servicoPlanejamento
) {
    this->servicoPlanejamento = servicoPlanejamento;
}

#endif
