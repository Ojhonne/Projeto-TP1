/**
 * @file containerBacklog.hpp
 * @author João Francisco de Sousa Torres
 * @brief Definição do container de backlog. 
 * @details Este container é responsável por armazenar e gerenciar os objetos de domínio
 * relacionados às histórias de usuário do sistema utilizando o banco de dados SQLite. Ele implementa operações CRUD (Create, Read, Update, Delete) 
 * para as histórias de usuário, bem como operações de associação entre histórias e pessoas, garantindo a integridade dos dados e a consistência das informações armazenadas.
 * 
 */

#ifndef CONTAINERBACKLOG_HPP
#define CONTAINERBACKLOG_HPP

#include "Interfaces/interfaces.hpp"
#include "Sql/sqlite3.h"
#include <string>
#include <vector>

/**
 * @class HistoriaDeUsuario
 */
class HistoriaDeUsuario;
/*
 *@class Codigo
 */
class Codigo;
/**
 * @class Estado
 */
class Estado;
/**
 * @class Email
 */
class Email;


/**
 * @class ContainerBacklog
 * @brief Implementa um container para armazenar e gerenciar objetos de domínio relacionados às histórias de usuário.
 * 
 */
class ContainerBacklog{
    private:
        static ContainerBacklog *instancia;
        ContainerBacklog();

        void conectarBanco(sqlite3*&);
        void abreQuerry(sqlite3* db, std::string& sql, sqlite3_stmt*& stmt);
        void executaStep(sqlite3* db, sqlite3_stmt* stmt);
         std::string lerStringSegura(sqlite3_stmt* stmt, int coluna);
        const std::string nomeBanco = "scrum.db"; 

        bool listarHistoriasAssociadas(const std::string& sql, const std::string& parametro, std::vector<HistoriaDeUsuario>& historias);

    public:
        /**
         * @brief Implementa o padrão Singleton para garantir que apenas uma instância do container seja criada.
         * @return Retorna um ponteiro para a instância única do container.
         */
        static ContainerBacklog* getInstancia();
        /**
         * @brief Cria uma nova história de usuário no container.
         * @param HistoriaDeUsuario é o objeto de domínio que representa a história de usuário a ser criada.
         * @return Retorna verdadeiro se a criação for bem-sucedida, falso caso contrário.
         */
        bool criarHistoriaUsuario(const HistoriaDeUsuario&);

        /**
         * @brief Lê os dados de uma história de usuário no container.
         * @param Codigo é o código único da história de usuário a ser lida.
         * @param HistoriaDeUsuario é um ponteiro para o objeto de domínio que será preenchido com os dados da história de usuário encontrada.
         * @return Retorna verdadeiro se a leitura for bem-sucedida e a história de usuário for encontrada, falso caso contrário.
         */
        bool lerHistoriaUsuario(const Codigo&, HistoriaDeUsuario&);
        /**
         * @brief Atualiza os dados de uma história de usuário no container.
         * @param HistoriaDeUsuario é o objeto de domínio que contém os novos dados da história de usuário a serem atualizados.
         * @return Retorna verdadeiro se a atualização for bem-sucedida, falso caso contrário.
         */
        bool atualizarHistoriaUsuario(const HistoriaDeUsuario&);
        /**
         * @brief Exclui uma história de usuário do container.
         * @param Codigo é o código único da história de usuário a ser excluída.
         * @return Retorna verdadeiro se a exclusão for bem-sucedida, falso caso contrário.
         */
        bool excluirHistoriaUsuario(const Codigo&);
        /**
         * @brief Lista as histórias de usuário associadas a um projeto.
         * @param Codigo é o código único do projeto cujas histórias de usuário serão listadas.
         * @param std::vector<HistoriaDeUsuario>& é o vetor que será preenchido com as histórias de usuário associadas ao projeto.
         * @return Retorna verdadeiro se a listagem for bem-sucedida, falso caso contrário.
         */
        bool listarHistoriasAssociadasProjeto(const Codigo&, std::vector<HistoriaDeUsuario>&);
        /**
         * @brief Lista as histórias de usuário associadas a um plano de sprint.
         * @param Codigo é o código único do plano de sprint cujas histórias de usuário serão listadas.
         * @param std::vector<HistoriaDeUsuario>& é o vetor que será preenchido com as histórias de usuário associadas ao plano de sprint.
         * @return Retorna verdadeiro se a listagem for bem-sucedida, falso caso contrário.
         */
        bool listarHistoriasAssociadasPlanoSprint(const Codigo&, std::vector<HistoriaDeUsuario>&);
        /**
         * @brief Lista as histórias de usuário associadas a uma pessoa.
         * @param Email é o endereço de e-mail da pessoa cujas histórias de usuário serão listadas.
         * @param std::vector<HistoriaDeUsuario>& é o vetor que será preenchido com as histórias de usuário associadas à pessoa.
         * @return Retorna verdadeiro se a listagem for bem-sucedida, falso caso contrário.
         */
        bool listarHistoriasAssociadasPessoa(const Email&, std::vector<HistoriaDeUsuario>&);

};

#endif //CONTAINERBACKLOG_HPP