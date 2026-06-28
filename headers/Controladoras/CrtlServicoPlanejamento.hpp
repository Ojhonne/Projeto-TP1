/**
 * @file CrtlServicoPlanejamento.hpp
 * @author Eduardo Sankievicz Lima
 * @brief Definição da controladora de serviço de planejamento.
 * @details Este serviço implementa as regras de negócio relacionadas ao
 * gerenciamento de projetos e planos de sprint do sistema.
 */

#ifndef CRTLSERVICOPLANEJAMENTO_HPP
#define CRTLSERVICOPLANEJAMENTO_HPP

#include "Interfaces/interfaces.hpp"
#include <vector>
#include <string>

class Projeto;
class PlanoDeSprint;
class Codigo;
class Email;

/**
 * @class CrtlServicoPlanejamento
 * @brief Implementa o serviço de gerenciamento de projetos e planos de sprint.
 *
 * @details Esta classe realiza as seguintes operações:
 * - Criar, ler, atualizar e excluir projetos;
 * - Criar, ler, atualizar e excluir planos de sprint;
 * - Listar projetos associados a uma pessoa;
 * - Listar planos de sprint associados a um projeto.
 *
 * Além disso, a classe é responsável por verificar as permissões do usuário
 * autenticado antes da execução das operações protegidas, de acordo com o
 * papel desempenhado no sistema.
 *
 * A classe herda da interface IServicoPlanejamento, garantindo que todas
 * as operações estejam de acordo com as regras de negócio definidas.
 */
class CrtlServicoPlanejamento : public IServicoPlanejamento{
private:
    const std::string DONO = "PROPRIETARIO DE PRODUTO";
    const std::string MESTRE = "MESTRE SCRUM";
    const std::string DESENVOLVEDOR = "DESENVOLVEDOR";

public:

    /**
     * @brief Cria um novo projeto no sistema.
     * @param Email é o email do usuário que está realizando a operação.
     * @param Projeto contém os dados do projeto a ser criado.
     * @return O retorno será padrão verdadeiro ou falso, dependendo do sucesso da criação.
     * @throws Pode capturar exceções vindas do repositório.
     */
    bool criarProjeto(const Email& emailSM, const Email& emailPO, const Projeto& projeto)  override;

    /**
     * @brief Lê os dados de um projeto cadastrado no sistema.
     * @param Codigo é a chave utilizada para identificar o projeto.
     * @param Projeto é o objeto que receberá os dados do projeto lido.
     * @return O retorno será padrão verdadeiro ou falso, dependendo da existência do projeto.
     * @throws Pode capturar exceções vindas do repositório.
     */
    bool lerProjeto(const Codigo&, Projeto&) override;

    /**
     * @brief Atualiza os dados de um projeto cadastrado no sistema.
     * @param Email é o email do usuário que está realizando a operação.
     * @param Projeto contém os novos dados do projeto.
     * @return O retorno será padrão verdadeiro ou falso, dependendo do sucesso da atualização.
     * @throws Pode capturar exceções vindas do repositório.
     */
    bool atualizarProjeto(const Email&, const Projeto&) override;

    /**
     * @brief Exclui um projeto cadastrado no sistema.
     * @param Email é o email do usuário que está realizando a operação.
     * @param Codigo é a chave utilizada para identificar o projeto.
     * @return O retorno será padrão verdadeiro ou falso, dependendo do sucesso da exclusão.
     * @throws Pode capturar exceções vindas do repositório.
     */
    bool excluirProjeto(const Email&, const Codigo&) override;

    /**
     * @brief Cria um novo plano de sprint associado a um projeto.
     * @param Email é o email do usuário que está realizando a operação.
     * @param Codigo identifica o projeto ao qual o plano será associado.
     * @param PlanoDeSprint contém os dados do plano de sprint.
     * @return O retorno será padrão verdadeiro ou falso, dependendo do sucesso da criação.
     * @throws Pode capturar exceções vindas do repositório.
     */
    bool criarPlanoSprint(const Email&, const Codigo&, const PlanoDeSprint&) override;

    /**
     * @brief Lê os dados de um plano de sprint cadastrado no sistema.
     * @param Codigo é a chave utilizada para identificar o plano de sprint.
     * @param PlanoDeSprint é o objeto que receberá os dados do plano lido.
     * @return O retorno será padrão verdadeiro ou falso, dependendo da existência do plano.
     * @throws Pode capturar exceções vindas do repositório.
     */
    bool lerPlanoSprint(const Codigo&, PlanoDeSprint&) override;

    /**
     * @brief Atualiza os dados de um plano de sprint cadastrado no sistema.
     * @param Email é o email do usuário que está realizando a operação.
     * @param PlanoDeSprint contém os novos dados do plano.
     * @return O retorno será padrão verdadeiro ou falso, dependendo do sucesso da atualização.
     * @throws Pode capturar exceções vindas do repositório.
     */
    bool atualizarPlanoSprint(const Email&, const PlanoDeSprint&) override;

    /**
     * @brief Exclui um plano de sprint cadastrado no sistema.
     * @param Email é o email do usuário que está realizando a operação.
     * @param Codigo é a chave utilizada para identificar o plano de sprint.
     * @return O retorno será padrão verdadeiro ou falso, dependendo do sucesso da exclusão.
     * @throws Pode capturar exceções vindas do repositório.
     */
    bool excluirPlanoSprint(const Email&, const Codigo&) override;

    /**
     * @brief Lista os projetos associados a uma pessoa.
     * @param Email é a chave utilizada para identificar a pessoa.
     * @param projetos é o vetor onde os projetos serão armazenados.
     * @return O retorno será padrão verdadeiro ou falso, dependendo do sucesso da operação.
     * @throws Pode capturar exceções vindas do repositório.
     */
    bool listarProjetos(const Email&, std::vector<Projeto>&) override;

    /**
     * @brief Lista os planos de sprint associados a um projeto.
     * @param Codigo é a chave utilizada para identificar o projeto.
     * @param planos é o vetor onde os planos de sprint serão armazenados.
     * @return O retorno será padrão verdadeiro ou falso, dependendo do sucesso da operação.
     * @throws Pode capturar exceções vindas do repositório.
     */
    bool listarPlanosSprint(const Codigo&, std::vector<PlanoDeSprint>&) override;
};

#endif // CRTLSERVICOPLANEJAMENTO_HPP