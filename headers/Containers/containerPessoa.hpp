/**
 * @file containerPessoa.hpp
 * @author João Francisco de Sousa Torres
 * @brief Definição do container de pessoas.
* @details Este container é responsável por armazenar e gerenciar os objetos de domínio
 * relacionados às pessoas do sistema utilizando o banco de dados SQLite. Ele implementa operações 
 * de inclusão, remoção, pesquisa e atualização de pessoas, garantindo a integridade dos dados e a 
 * consistência das informações armazenadas.
 */

#ifndef CONTAINERPESSOA_H_INCLUDED
#define CONTAINERPESSOA_H_INCLUDED

// Forward declarations.
class Email;
class Pessoa;

#include <string>    
#include "Sql/sqlite3.h"

/**
 * @class ContainerPessoa
 * @brief Implementa um container para armazenar e gerenciar objetos de domínio relacionados às pessoas
 * 
 */

// Declaração adota padrão de projeto Singleton.


class ContainerPessoa{
    private:
        static ContainerPessoa *instancia;             // Ponteiro para instância da classe.

        void conectarBanco(sqlite3*&);
        void abreQuerry(sqlite3* db, std::string& sql, sqlite3_stmt*& stmt);
        void executaStep(sqlite3* db, sqlite3_stmt* stmt);
        
        const std::string nomeBanco = "scrum.db"; // nome do arquivo do banco de dados SQLite.
        // Construtor privado (Singleton). 
        // Ele será responsável por criar a tabela Pessoa no SQLite caso ela não exista.
        ContainerPessoa(){};                           // Construtor.

    public:
       // Método para instanciar classe.
        /**
         * @brief implementa o padrão Singleton para garantir que apenas uma instância do container seja criada.
         * @return Retorna um ponteiro para a instância única do container.
         */
        static ContainerPessoa* getInstancia();       
       
       // Métodos responsáveis por prestar serviços.
        /**
         * @brief Inclui uma nova pessoa no container.
         * @param Pessoa é o objeto de domínio que representa a pessoa a ser incluída.
         * @return Retorna verdadeiro se a inclusão for bem-sucedida, falso caso contrário
         */
        bool incluir(Pessoa);                          
        /**
         * @brief Remove uma pessoa do container com base no email fornecido.
         * @param Email é a chave utilizada para identificar a pessoa a ser removida.
         * @return Retorna verdadeiro se a remoção for bem-sucedida, falso caso contrário.
         */
        bool remover(Email);
        /**
         * @brief Pesquisa uma pessoa no container com base no email fornecido.
         * @param Pessoa é um ponteiro para o objeto de domínio que será preenchido com os dados da pessoa encontrada.
         * @return Retorna verdadeiro se a pesquisa for bem-sucedida e a pessoa for encontrada, falso caso contrário.
         */
        bool pesquisar(Pessoa*);
        /**
         * @brief Atualiza os dados de uma pessoa no container com base no objeto de domínio fornecido.
         * @param Pessoa é o objeto de domínio que contém os novos dados da pessoa a serem atualizados.
         * @return Retorna verdadeiro se a atualização for bem-sucedida, falso
         */
        bool atualizar(Pessoa);
};

#endif // CONTAINERPESSOA_H_INCLUDED