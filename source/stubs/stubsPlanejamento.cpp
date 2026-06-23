#include "Stubs/stubsPlanejamento.hpp"

const string StubServicoPlanejamento::CODIGO_PROJETO_VALIDO = "AB123";
const string StubServicoPlanejamento::NOME_PROJETO_VALIDO = "Projeto01";
const string StubServicoPlanejamento::DATA_INICIO_VALIDA = "01/01/25";
const string StubServicoPlanejamento::DATA_FIM_VALIDA = "31/12/25";

const string StubServicoPlanejamento::CODIGO_PLANO_VALIDO = "CD456";
const string StubServicoPlanejamento::TEXTO_PLANO_VALIDO = "Sprint 1";
const string StubServicoPlanejamento::TEMPO_PLANO_VALIDO = "120";

bool StubServicoPlanejamento::criarProjeto(const Projeto& projeto){
    return true;
}

bool StubServicoPlanejamento::lerProjeto(const Codigo& codigo, Projeto& projeto){
    if(codigo.getValor().compare(CODIGO_PROJETO_VALIDO) != 0)
        return false;

    Data dataInicio;
    dataInicio.setValor(DATA_INICIO_VALIDA);

    Data dataFim;
    dataFim.setValor(DATA_FIM_VALIDA);

    projeto.setCodigo(Codigo(CODIGO_PROJETO_VALIDO));
    projeto.setNome(Nome(NOME_PROJETO_VALIDO));
    projeto.setInicio(dataInicio);
    projeto.setTermino(dataFim);


    return true;
}

bool StubServicoPlanejamento::atualizarProjeto(const Projeto& projeto){
    return true;
}

bool StubServicoPlanejamento::excluirProjeto(const Codigo& codigo){
    if(codigo.getValor().compare(CODIGO_PROJETO_VALIDO) != 0)
        return false;

    return true;
}

bool StubServicoPlanejamento::criarPlanoSprint(const PlanoDeSprint& plano){
    return true;
}

bool StubServicoPlanejamento::lerPlanoSprint(const Codigo& codigo, PlanoDeSprint& plano){
    if(codigo.getValor().compare(CODIGO_PLANO_VALIDO) != 0)
        return false;

    plano.setCodigo(Codigo(CODIGO_PLANO_VALIDO));
    plano.setTexto(Texto(TEXTO_PLANO_VALIDO));
    plano.setTempo(Tempo(TEMPO_PLANO_VALIDO));

    return true;
}

bool StubServicoPlanejamento::atualizarPlanoSprint(const PlanoDeSprint& plano){
    return true;
}

bool StubServicoPlanejamento::excluirPlanoSprint(const Codigo& codigo){
    if(codigo.getValor().compare(CODIGO_PLANO_VALIDO) != 0)
        return false;

    return true;
}