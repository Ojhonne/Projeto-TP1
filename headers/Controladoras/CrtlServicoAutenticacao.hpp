
/**
 * @file CrtlServicoAutenticacao.hpp
 * @author João Francisco de Sousa Torres
 * @brief Definição da controladora de serviço de autenticação.
 *  @details Este serviço implementa as regras de negócio relacionadas à
 * autenticação de pessoas. A classe depende de um repositório que segue
 * a interface ContainerPessoa para acessar dados persistidos
 */
#ifndef CRTLSERVICOAUTENTICACAO_H_INCLUDED
#define CRTLSERVICOAUTENTICACAO_H_INCLUDED

#include "Interfaces/interfaces.hpp"
#include "Dominios/dominios.hpp"

/**
 * @class CrtlServicoAutenticacao
 * @brief Implementa o serviço de autenticação de pessoas.
 *
 * @details Esta classe realiza a seguinte operação:
 * - Autenticar pessoa por email e senha
 *
 * Toda interação com o armazenamento é feita por meio da interface
 * ContainerPessoa, permitindo independência entre camada de negócio
 * e persistência.
 */
class CrtlServicoAutenticacao : public IServicoAutenticacao{
    private:
        //ContainerPessoa* container;
    public:
    /**
     * @brief Autentica um Pessoa pelo par email/senha.
     *
     * @param email Objeto de domínio Email já validado.
     * @param senha Objeto de domínio Senha já validado.
     * @return true se as credenciais forem válidas, false caso contrário.
     *
     * @throws Pode capturar exceções vindas do repositório.
     */
     bool autenticarPessoa(const Email&, const Senha&) override;
};

#endif // CRTLSERVICOAUTENTICACAO_H_INCLUDED

