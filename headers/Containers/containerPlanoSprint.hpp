/**
 * @file containerPlanoSprint.hpp
 * @author Eduardo Sankievicz Lima
 * @brief Definição do container de planos de sprint.
 * @details Este container é responsável por armazenar e gerenciar os objetos
 * da entidade PlanoDeSprint utilizando o banco de dados SQLite. Ele implementa
 * operações CRUD para planos de sprint e a listagem de planos associados a um projeto.
 */

#ifndef CONTAINERPLANOSPRINT_HPP
#define CONTAINERPLANOSPRINT_HPP

#include "Interfaces/interfaces.hpp"
#include "Sql/sqlite3.h"
#include <string>
#include <vector>

class PlanoDeSprint;
class Codigo;

/**
 * @class ContainerPlanoSprint
 * @brief Container responsável pelo acesso aos dados da entidade PlanoDeSprint.
 */
class ContainerPlanoSprint {
private:
    static ContainerPlanoSprint *instancia;
    ContainerPlanoSprint();

    const std::string nomeBanco = "scrum.db";

    void conectarBanco(sqlite3*&);
    void abreQuerry(sqlite3* db, std::string& sql, sqlite3_stmt*& stmt);
    void executaStep(sqlite3* db, sqlite3_stmt* stmt);

public:
    /**
     * @brief Implementa o padrão Singleton para garantir uma única instância do container.
     * @return Ponteiro para a instância única de ContainerPlanoSprint.
     */
    static ContainerPlanoSprint* getInstancia();

    /**
     * @brief Cria um novo plano de sprint associado a um projeto.
     * @param Codigo Código do projeto ao qual o plano de sprint será associado.
     * @param PlanoDeSprint Entidade contendo os dados do plano a ser criado.
     * @return true se a criação for bem-sucedida, false caso contrário.
     */
    bool criarPlanoSprint(const Codigo&, const PlanoDeSprint&);

    /**
     * @brief Lê os dados de um plano de sprint a partir de seu código.
     * @param Codigo Código do plano de sprint buscado.
     * @param PlanoDeSprint Entidade que será preenchida com os dados encontrados.
     * @return true se o plano for encontrado, false caso contrário.
     */
    bool lerPlanoSprint(const Codigo&, PlanoDeSprint&);

    /**
     * @brief Atualiza os dados de um plano de sprint existente.
     * @param PlanoDeSprint Entidade contendo os novos dados do plano.
     * @return true se a atualização for bem-sucedida, false caso contrário.
     */
    bool atualizarPlanoSprint(const PlanoDeSprint&);

    /**
     * @brief Exclui um plano de sprint a partir de seu código.
     * @param Codigo Código do plano de sprint a ser removido.
     * @return true se a exclusão for bem-sucedida, false caso contrário.
     */
    bool excluirPlanoSprint(const Codigo&);

    /**
     * @brief Lista os planos de sprint associados a um projeto.
     * @param Codigo Código do projeto cujos planos de sprint serão listados.
     * @param std::vector<PlanoDeSprint>& Vetor que será preenchido com os planos encontrados.
     * @return true se a listagem for executada, false caso contrário.
     */
    bool listarPlanosSprint(const Codigo&, std::vector<PlanoDeSprint>&);
};

#endif