/**
 * @file pessoa.hpp
 * @author Eduardo Sankievicz Lima
 * @brief Definição da classe entidade Pessoa.
 */

#ifndef PESSOA_HPP
#define PESSOA_HPP

#include "Dominios/dominios.hpp"


/**
 * @class Pessoa
 * @brief Entidade que representa um usuario do sistema.
 *
 * @details A entidade Pessoa agrupa as informacoes basicas de um usuario,
 * sendo composta por objetos de dominio responsaveis por validar seus
 * respectivos formatos e regras.
 *
 * Os dominios utilizados sao:
 *  - Email (identificador unico da pessoa)
 *  - Nome
 *  - Senha
 *  - Papel (define o perfil ou permissao do usuario no sistema)
 *
 * Cada atributo encapsula sua propria validacao, garantindo que a entidade
 * Pessoa sempre esteja em um estado consistente.
 *
 * @note **Decisao de Arquitetura e Performance:** Todos os metodos de acesso
 * (getters) e modificadores (setters) utilizam passagem e retorno por
 * referencia constante (`const Tipo&`). Isso evita copias desnecessarias
 * dos objetos de dominio e melhora a performance, alem de manter o
 * encapsulamento da entidade.
 */
class Pessoa {
private:
    Email email;
    Nome nome;
    Senha senha;
    Papel papel;

public:

    /**
     * @brief Atribui um novo email a pessoa.
     * @param email Referencia constante para o objeto de dominio Email.
     */
    void setEmail(const Email& email);

    /**
     * @brief Recupera o email da pessoa.
     * @return const Email& Referencia constante para o email armazenado.
     */
    const Email& getEmail() const;

    /**
     * @brief Atribui um novo nome a pessoa.
     * @param nome Referencia constante para o objeto de dominio Nome.
     */
    void setNome(const Nome& nome);

    /**
     * @brief Recupera o nome da pessoa.
     * @return const Nome& Referencia constante para o nome armazenado.
     */
    const Nome& getNome() const;

    /**
     * @brief Atribui uma nova senha a pessoa.
     * @param senha Referencia constante para o objeto de dominio Senha.
     */
    void setSenha(const Senha& senha);

    /**
     * @brief Recupera a senha da pessoa.
     * @return const Senha& Referencia constante para a senha armazenada.
     */
    const Senha& getSenha() const;

    /**
     * @brief Define o papel da pessoa no sistema.
     * @param papel Referencia constante para o objeto de dominio Papel.
     */
    void setPapel(const Papel& papel);

    /**
     * @brief Recupera o papel da pessoa.
     * @return const Papel& Referencia constante para o papel armazenado.
     */
    const Papel& getPapel() const;
};

#endif