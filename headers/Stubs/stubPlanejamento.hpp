/**
 * @file stubPlanejamento.hpp
 * @author  Eduardo Sankievicz Lima
 * @brief Definição da stub de planejamento.
 */

#ifndef STUBS_PLANEJAMENTO_HPP_INCLUDED
#define STUBS_PLANEJAMENTO_HPP_INCLUDED

#include <string>
#include "Dominios/dominios.hpp"
#include "Interfaces/interfaces.hpp"
#include "Entidades/projeto.hpp"
#include "Entidades/planoDeSprint.hpp"

using namespace std;

class StubServicoPlanejamento : public IServicoPlanejamento {
private:
    static const string CODIGO_PROJETO_VALIDO;
    static const string NOME_PROJETO_VALIDO;
    static const string DATA_INICIO_VALIDA;
    static const string DATA_FIM_VALIDA;

    static const string CODIGO_PLANO_VALIDO;
    static const string TEXTO_PLANO_VALIDO;
    static const string TEMPO_PLANO_VALIDO;

public:
    bool criarProjeto(const Projeto&) override;
    bool lerProjeto(const Codigo&, Projeto&) override;
    bool atualizarProjeto(const Projeto&) override;
    bool excluirProjeto(const Codigo&) override;

    bool criarPlanoSprint(const PlanoDeSprint&) override;
    bool lerPlanoSprint(const Codigo&, PlanoDeSprint&) override;
    bool atualizarPlanoSprint(const PlanoDeSprint&) override;
    bool excluirPlanoSprint(const Codigo&) override;
};

#endif