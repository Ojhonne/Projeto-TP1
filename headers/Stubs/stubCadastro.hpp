/**
 * @file StubCadastro.hpp
 * @author Igor Melo
 * @brief Definição da stub de serviço de cadastro de pessoas.
 */

#ifndef STUBCADASTRO_HPP_INCLUDED
#define STUBCADASTRO_HPP_INCLUDED

#include "Interfaces/interfaces.hpp"
#include "Dominios/dominios.hpp"
#include "Entidades/pessoa.hpp"
#include <vector>

/**
 * @class StubCadastro
 * @brief Stub de serviço que simula o comportamento da camada de negócios para o cadastro de pessoas.
 * * Esta classe implementa a interface IServicoPessoa e emula uma persistência em memória
 * * utilizando um vetor estático para simular operações de banco de dados (CRUD) sem a necessidade
 * * de uma conexão ativa com o SQLite durante a fase de testes automatizados e validação da interface.
 */
class StubCadastro : public IServicoPessoa {
private:
    static std::vector<Pessoa> pessoasCadastradas; /**< vetor estático que funciona como a memória temporária para simular a tabela do banco de dados. */

public:
    /**
     * @brief Destrutor virtual padrão.
     */
    virtual ~StubCadastro() = default;

    /**
     * @brief Simula a criação e persistência de uma nova pessoa no sistema.
     * @param pessoa Referência constante para o objeto Pessoa contendo os dados validados.
     * @return Retorna true se a inclusão simulada for bem-sucedida, false caso contrário (ex: e-mail duplicado).
     */
    bool criarPessoa(const Pessoa& pessoa) override;

    /**
     * @brief Simula a leitura e busca dos dados de uma pessoa com base no e-mail fornecido.
     * @param email Chave de busca para identificar o usuário desejado.
     * @param pessoa Objeto passado por referência que receberá os dados populados caso o e-mail seja encontrado.
     * @return Retorna true se a pessoa for localizada na memória do stub, false caso contrário.
     */
    bool lerPessoa(const Email& email, Pessoa& pessoa) override;

    /**
     * @brief Simula a atualização dos dados cadastrais de uma pessoa existente.
     * @param pessoa Objeto contendo as novas informações a serem sobrescritas na memória.
     * @return Retorna true se o registro for localizado e atualizado com sucesso, false caso contrário.
     */
    bool atualizarPessoa(const Pessoa& pessoa) override;

    /**
     * @brief Simula a exclusão definitiva de uma pessoa da memória do sistema.
     * @param email Chave de identificação da conta de usuário a ser removida.
     * @return Retorna true se a exclusão simulada for concluída com sucesso, false caso contrário.
     */
    bool excluirPessoa(const Email& email) override;
};

#endif // STUBCADASTRO_HPP_INCLUDED
