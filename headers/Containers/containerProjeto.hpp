/**
 * @file containerProjeto.hpp
 * @author Eduardo Sankievicz Lima
 * @brief Definição do container de projetos.
 * @details Este container é responsável por armazenar e gerenciar os objetos
 * da entidade Projeto utilizando o banco de dados SQLite. Ele implementa
 * operações CRUD para projetos e a listagem de projetos associados a uma pessoa.
 */

#ifndef CONTAINERPROJETO_HPP
#define CONTAINERPROJETO_HPP

#include "Interfaces/interfaces.hpp"
#include "Sql/sqlite3.h"
#include <string>
#include <vector>

class Projeto;
class Codigo;
class Email;

/**
 * @class ContainerProjeto
 * @brief Container responsável pelo acesso aos dados da entidade Projeto.
 */
class ContainerProjeto {
private:
    static ContainerProjeto *instancia;
    ContainerProjeto();

    const std::string nomeBanco = "scrum.db";

    void conectarBanco(sqlite3*&);
    void abreQuerry(sqlite3* db, std::string& sql, sqlite3_stmt*& stmt);
    void executaStep(sqlite3* db, sqlite3_stmt* stmt);

public:
    /**
     * @brief Implementa o padrão Singleton para garantir uma única instância do container.
     * @return Ponteiro para a instância única de ContainerProjeto.
     */
    static ContainerProjeto* getInstancia();

    /**
     * @brief Cria um novo projeto no banco de dados associado a uma pessoa.
     * @param Email Email da pessoa à qual o projeto será associado.
     * @param Projeto Entidade contendo os dados do projeto a ser criado.
     * @return true se a criação for bem-sucedida, false caso contrário.
     */
    bool criarProjeto(const Email&, const Projeto&);

    /**
     * @brief Lê os dados de um projeto a partir de seu código.
     * @param Codigo Código do projeto buscado.
     * @param Projeto Entidade que será preenchida com os dados encontrados.
     * @return true se o projeto for encontrado, false caso contrário.
     */
    bool lerProjeto(const Codigo&, Projeto&);

    /**
     * @brief Atualiza os dados de um projeto existente.
     * @param Projeto Entidade contendo os novos dados do projeto.
     * @return true se a atualização for bem-sucedida, false caso contrário.
     */
    bool atualizarProjeto(const Projeto&);

    /**
     * @brief Exclui um projeto a partir de seu código.
     * @param Codigo Código do projeto a ser removido.
     * @return true se a exclusão for bem-sucedida, false caso contrário.
     */
    bool excluirProjeto(const Codigo&);

    /**
     * @brief Lista os projetos associados a uma pessoa.
     * @param Email Email da pessoa cujos projetos serão listados.
     * @param std::vector<Projeto>& Vetor que será preenchido com os projetos encontrados.
     * @return true se a listagem for executada, false caso contrário.
     */
    bool listarProjetos(const Email&, std::vector<Projeto>&);
};

#endif