/**
 * @file CrtlServicoBacklog.hpp
 * @author João Francisco de Sousa Torres
 * @brief Definição da controladora de serviço de backlog.
 *  @details Este serviço implementa as regras de negócio relacionadas ao gerenciamento de histórias de usuário no backlog.
 */
#ifndef CRTLSERVICOBACKLOG_HPP
#define CRTLSERVICOBACKLOG_HPP

#include "Interfaces/interfaces.hpp"
#include <vector>
#include <string>

class HistoriaDeUsuario;
class Codigo;
class Email;
class Estado;

/**
 * @class CrtlServicoBacklog
 * @brief Implementa o serviço de gerenciamento de histórias de usuário.
 * @details Esta classe realiza as seguintes operações:
 * - Criar, ler, atualizar e excluir histórias de usuário 
 * - Associar e remover histórias de usuário a pessoas
 * - Listar histórias de usuário associadas a projetos, planos de sprint e pessoas
 * - Mover histórias de usuário de projetos para planos de sprint
 * - Alterar o estado de uma história de usuário
 * ela herda da interface IServicoBacklog, garantindo que todas as operações estejam de acordo com as regras de negócio definidas.
 */
class CrtlServicoBacklog : public IServicoBacklog{
    private:
        const std::string DONO = "PROPRIETARIO DE PRODUTO";
        const std::string MESTRE = "MESTRE SCRUM";
        const std::string DESENVOLVEDOR = "DESENVOLVEDOR";

    public:
    /**
     * @brief Cria uma nova história de usuário no sistema.
     * @param HistoriaDeUsuario contém os dados da história a ser criada.
     *  @return O retorno será padrão verdadeiro ou falso, dependendo do sucesso da criação.
     *  @throws Pode capturar exceções vindas do repositório.
     */
     bool criarHistoriaUsuario(const HistoriaDeUsuario&, const Email&) override;
    /**
     * @brief Lê os dados de uma história de usuário cadastrada no sistema.
     * @param Codigo é a chave utilizada para identificar a história.
     *  @return O retorno será padrão verdadeiro ou falso, dependendo da existência da história.
     *  @throws Pode capturar exceções vindas do repositório.
     */
     bool lerHistoriaUsuario(const Codigo&, HistoriaDeUsuario&) override;
    /**
     * @brief Atualiza os dados de uma história de usuário cadastrada no sistema.
     * @param HistoriaDeUsuario contém os dados atualizados da história.
     *  @return O retorno será padrão verdadeiro ou falso, dependendo do sucesso da atualização.
     *  @throws Pode capturar exceções vindas do repositório.
     */
     bool atualizarHistoriaUsuario(const HistoriaDeUsuario&, const Email&) override;
    /**
     * @brief Exclui uma história de usuário cadastrada no sistema.
     * @param Codigo é a chave utilizada para identificar a história.
     * @return O retorno será padrão verdadeiro ou falso, dependendo do sucesso da exclusão.
     * @throws Pode capturar exceções vindas do repositório.
     */
     bool excluirHistoriaUsuario(const Codigo&, const Email&) override;
    /**
     * @brief Associa uma história de usuário a uma pessoa.
     * @param Codigo é a chave utilizada para identificar a história.
     * @param Email é a chave utilizada para identificar a pessoa.
     * @return O retorno será padrão verdadeiro ou falso, dependendo do sucesso da associação.
     * @throws Pode capturar exceções vindas do repositório.
     */
     bool associarHistoriaPessoa(const Codigo&, const Email&, const Email& usuarioLogado) override;
    /**
     * @brief Remove a associação entre uma história de usuário e uma pessoa.
     * @param Codigo é a chave utilizada para identificar a história.
     * @param Email é a chave utilizada para identificar a pessoa.
     * @return O retorno será padrão verdadeiro ou falso, dependendo do sucesso da remoção da associação.
     * @throws Pode capturar exceções vindas do repositório.
     */
     bool removerAssociacaoHistoriaPessoa(const Codigo&,  const Email& emailAlvo, const Email& usuarioLogado) override;
    /**
     * @brief Lista as histórias de usuário associadas a um projeto.
     * @param Codigo é a chave utilizada para identificar o projeto.
     * @param historias é o vetor onde as histórias serão armazenadas.
     * @return O retorno será padrão verdadeiro ou falso, dependendo do sucesso da operação.
     * @throws Pode capturar exceções vindas do repositório.
     */
     bool listarHistoriasAssociadasProjeto(const Codigo&, std::vector<HistoriaDeUsuario>&) override;
    /**
     * @brief Lista as histórias de usuário associadas a um plano de sprint.
     * @param Codigo é a chave utilizada para identificar o plano de sprint.
     * @param historias é o vetor onde as histórias serão armazenadas.
     * @return O retorno será padrão verdadeiro ou falso, dependendo do sucesso da operação.
     * @throws Pode capturar exceções vindas do repositório.
     */
     bool listarHistoriasAssociadasPlanoSprint(const Codigo&, std::vector<HistoriaDeUsuario>&) override;
    /**
     * @brief Lista as histórias de usuário associadas a uma pessoa.
     * @param Email é a chave utilizada para identificar a pessoa.
     * @param historias é o vetor onde as histórias serão armazenadas.
     * @return O retorno será padrão verdadeiro ou falso, dependendo do sucesso da operação.
     * @throws Pode capturar exceções vindas do repositório.
     */
     bool listarHistoriasAssociadasPessoa(const Email&, std::vector<HistoriaDeUsuario>&) override;
    /**
     * @brief Move uma história de usuário de um projeto para um plano de sprint.
     * @param codigoHistoria é a chave utilizada para identificar a história.
     * @param codigoSprint é a chave utilizada para identificar o plano de sprint.
     * @return O retorno será padrão verdadeiro ou falso, dependendo do sucesso da operação.
     * @throws Pode capturar exceções vindas do repositório.
     */
     bool moverHistoriaProjetoParaSprint(const Codigo& codigoHistoria, const Codigo& codigoSprint, const Email& usuarioLogado) override;
    /**
     * @brief Altera o estado de uma história de usuário.
     * @param Codigo é a chave utilizada para identificar a história.
     * @param Estado é o novo estado da história.
     * @return O retorno será padrão verdadeiro ou falso, dependendo do sucesso da operação.
     * @throws Pode capturar exceções vindas do repositório.
     */
     bool alterarEstadoHistoria(const Codigo&, const Estado&, const Email&) override;

};



#endif // CRTLSERVICOBACKLOG_HPP