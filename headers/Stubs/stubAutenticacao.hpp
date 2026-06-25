/**
 * @file stubAutenticacao.hpp
 * @author João Francisco de Sousa Torres
 * @brief Definição da stub de autenticação.
 */

#ifndef STUBS_HPP_INCLUDED
#define STUBS_HPP_INCLUDED

#include <string>
#include "Dominios/dominios.hpp"
#include "Interfaces/interfaces.hpp"
#include "Entidades/historiaDeUsuario.hpp"

using namespace std;

//------------------------------------------------------------------------
// Declaração de classe stub.

class StubServicoAutenticacao: public IServicoAutenticacao {
    private:
        static const string EMAIL_VALIDO;
        static const string SENHA_VALIDA;
    public:
    /**
     * @brief Autentica uma pessoa com base no email e senha fornecidos.
     * @param Email é a chave utilizada para identificar a pessoa a ser autenticada.
     * @param Senha é utilizada para verificar se a credencial apresentada é válida.
     * @return O retorno será padrão verdadeiro ou falso, dependendo da autenticidade
     * das credenciais fornecidas.
     */
        bool autenticarPessoa(const Email&, const Senha&) override;
};

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
        bool criarHistoriaUsuario(const HistoriaDeUsuario& historia) override;
        bool lerHistoriaUsuario(const Codigo& codigo, HistoriaDeUsuario& historia) override;
        bool atualizarHistoriaUsuario(const HistoriaDeUsuario& historia) override;
        bool excluirHistoriaUsuario(const Codigo& codigo) override;
        bool associarHistoriaPessoa(const Codigo& codigo, const Email& email) override;
        bool removerAssociacaoHistoriaPessoa(const Codigo& codigo, const Email& email) override;
        bool listarHistoriasAssociadasProjeto(const Codigo& codigo, std::vector<HistoriaDeUsuario>& vetor) override;
        bool listarHistoriasAssociadasPlanoSprint(const Codigo& codigo, std::vector<HistoriaDeUsuario>& vetor) override;
        bool listarHistoriasAssociadasPessoa(const Email& email, std::vector<HistoriaDeUsuario>& vetor) override;
        bool moverHistoriaProjetoParaSprint(const Codigo& codigoHistoria, const Codigo& codigoSprint) override;
        bool alterarEstadoHistoria(const Codigo& codigo, const Estado& estado) override;
};

#endif // STUBS_HPP_INCLUDED
