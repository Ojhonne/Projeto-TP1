#include "Stubs/stubBacklog.hpp"

const string StubServicoBacklog::CODIGO_VALIDO = "AB123";

string StubServicoBacklog::save_titulo;
string StubServicoBacklog::save_papel;
string StubServicoBacklog::save_acao;
string StubServicoBacklog::save_valor;
string StubServicoBacklog::save_estimativa;
string StubServicoBacklog::save_prioridade;
string StubServicoBacklog::save_estado;

// CORRIGIDO: Nome igual ao do .hpp (criarHistoriaUsuario)
bool StubServicoBacklog::criarHistoriaUsuario(const HistoriaDeUsuario& historia){
    save_titulo      = historia.getTitulo().getValor();
    save_papel       = historia.getPapel().getValor();
    save_acao        = historia.getAcao().getValor();
    save_valor       = historia.getValor().getValor();
    save_estimativa  = historia.getEstimativa().getValor();
    save_prioridade  = historia.getPrioridade().getValor();
    save_estado      = historia.getEstado().getValor();

    return true;
}

// --- IMPLEMENTAÇÕES FALTANTES PARA A CLASSE NÃO SER ABSTRATA ---

bool StubServicoBacklog::lerHistoriaUsuario(const Codigo& codigo, HistoriaDeUsuario& historia) {
    if (codigo.getValor() != CODIGO_VALIDO)
        return false;

    historia.setCodigo(codigo);

    Texto titulo(save_titulo);
    Texto papel(save_papel);
    Texto acao(save_acao);
    Texto valor(save_valor);
    Tempo estimativa(save_estimativa);
    Prioridade prioridade;
    prioridade.setValor(save_prioridade);
    Estado estado;
    estado.setValor(save_estado);
    

    historia.setTitulo(titulo);
    historia.setPapel(papel);
    historia.setAcao(acao);
    historia.setValor(valor);
    historia.setEstimativa(estimativa);
    historia.setPrioridade(prioridade);
    historia.setEstado(estado);

    return true;
}

bool StubServicoBacklog::atualizarHistoriaUsuario(const HistoriaDeUsuario& historia) {
    return true; 
}

bool StubServicoBacklog::excluirHistoriaUsuario(const Codigo& codigo) {
    return true; 
}

bool StubServicoBacklog::associarHistoriaPessoa(const Codigo& codigo, const Email& email) {
    return true; 
}

bool StubServicoBacklog::removerAssociacaoHistoriaPessoa(const Codigo& codigo, const Email& email) {
    return true;
}

bool StubServicoBacklog::listarHistoriasAssociadasProjeto(const Codigo& codigo, std::vector<HistoriaDeUsuario>& vetor) {
    return true;
}

bool StubServicoBacklog::listarHistoriasAssociadasPlanoSprint(const Codigo& codigo, std::vector<HistoriaDeUsuario>& vetor) {
    return true;
}

bool StubServicoBacklog::listarHistoriasAssociadasPessoa(const Email& email, std::vector<HistoriaDeUsuario>& vetor) {
    return true;
}

bool StubServicoBacklog::moverHistoriaProjetoParaSprint(const Codigo& codigoHistoria, const Codigo& codigoSprint) {
    return true;
}

bool StubServicoBacklog::alterarEstadoHistoria(const Codigo& codigo, const Estado& estado) {
    return true;
}