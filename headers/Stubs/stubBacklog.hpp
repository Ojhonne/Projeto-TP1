/*#ifndef STUBBACKLOG_HPP_INCLUDED
#define STUBBACKLOG_HPP_INCLUDED

#include <string>
#include "Dominios/dominios.hpp"
#include "Interfaces/interfaces.hpp"
#include "Entidades/historiaDeUsuario.hpp"

using namespace std;

//------------------------------------------------------------------------
// Declaração de classe stub.

class StubServicoBacklog: public IServicoBacklog {
    private:
        static const string CODIGO_VALIDO;

        static string save_titulo;
        static string save_papel;
        static string save_acao;
        static string save_valor;
        static string save_estimativa;
        static string save_prioridade;
        static string save_estado;
    public:
        bool criarHistoriaUsuario(const HistoriaDeUsuario& historia, const Email&) override;
        bool lerHistoriaUsuario(const Codigo& codigo, HistoriaDeUsuario& historia) override;
        bool atualizarHistoriaUsuario(const HistoriaDeUsuario& historia, const Email&) override;
        bool excluirHistoriaUsuario(const Codigo& codigo, const Email&) override;
        bool associarHistoriaPessoa(const Codigo& codigo, const Embool criarHisail& email) override;
        bool removerAssociacaoHistoriaPessoa(const Codigo& codigo, const Email& email, const Email&) override;
        bool listarHistoriasAssociadasProjeto(const Codigo& codigo, std::vector<HistoriaDeUsuario>& vetor) override;
        bool listarHistoriasAssociadasPlanoSprint(const Codigo& codigo, std::vector<HistoriaDeUsuario>& vetor) override;
        bool listarHistoriasAssociadasPessoa(const Email& email, std::vector<HistoriaDeUsuario>& vetor) override;
        bool moverHistoriaProjetoParaSprint(const Codigo& codigoHistoria, const Codigo& codigoSprin, const Email&) override;
        bool alterarEstadoHistoria(const Codigo& codigo, const Estado& estado, const Email&) override;
}

#endif // STUBS_HPP_INCLUDED
*/