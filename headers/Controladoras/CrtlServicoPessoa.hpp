/**
 * @file CrtlServicoPessoa.hpp
 * @author Fábio Willian Alves Silva
 * @brief Definição da controladora de serviço de pessoa.
 * @details Este serviço implementa as regras de negócio relacionadas ao
 * gerenciamento de pessoas (usuários) cadastradas no sistema.
 */

#ifndef CRTLSERVICOPESSOA_HPP
#define CRTLSERVICOPESSOA_HPP

#include "Interfaces/interfaces.hpp"
#include <vector>
#include <string>

class Email;
class Pessoa;

/**
 * @class CrtlServicoPessoa
 * @brief Implementa o serviço de gerenciamento de pessoas no sistema.
 *
 * @details Esta classe realiza as seguintes operações:
 * - Criar, ler, atualizar e excluir pessoas cadastradas no sistema;
 *
 * Além disso, a classe é responsável por garantir que as operações
 * sobre os dados de uma pessoa sigam as regras de negócio definidas,
 * assegurando a integridade e consistência das informações armazenadas.
 *
 * A classe herda da interface IServicoPessoa, garantindo que todas
 * as operações estejam de acordo com o contrato estabelecido pela interface.
 */
class CrtlServicoPessoa : public IServicoPessoa {
    public:

        /**
         * @brief Cria uma nova pessoa no sistema.
         * @param Pessoa contém os dados da pessoa a ser criada.
         * @return O retorno será padrão verdadeiro ou falso, dependendo do sucesso da criação.
         * @throws Pode capturar exceções vindas do repositório.
         */
        bool criarPessoa(const Pessoa&) override;

        /**
         * @brief Lê os dados de uma pessoa cadastrada no sistema.
         * @param Email é a chave utilizada para identificar a pessoa.
         * @param Pessoa é o objeto que receberá os dados da pessoa lida.
         * @return O retorno será padrão verdadeiro ou falso, dependendo da existência da pessoa.
         * @throws Pode capturar exceções vindas do repositório.
         */
        bool lerPessoa(const Email&, Pessoa&) override;

        /**
         * @brief Atualiza os dados de uma pessoa cadastrada no sistema.
         * @param Pessoa contém os novos dados da pessoa a ser atualizada.
         * @return O retorno será padrão verdadeiro ou falso, dependendo do sucesso da atualização.
         * @throws Pode capturar exceções vindas do repositório.
         */
        bool atualizarPessoa(const Pessoa&) override;

        /**
         * @brief Exclui uma pessoa cadastrada no sistema.
         * @param Email é a chave utilizada para identificar a pessoa a ser excluída.
         * @return O retorno será padrão verdadeiro ou falso, dependendo do sucesso da exclusão.
         * @throws Pode capturar exceções vindas do repositório.
         */
        bool excluirPessoa(const Email&) override;

};

#endif // CRTLSERVICOPESSOA_HPP