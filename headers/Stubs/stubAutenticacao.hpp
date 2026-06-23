/**
 * @file interfaces.hpp
 * @author João Francisco de Sousa Torres
 * @brief Definição da stub de autenticação.
 */

#ifndef STUBS_HPP_INCLUDED
#define STUBS_HPP_INCLUDED

#include <string>
#include "Dominios/dominios.hpp"
#include "Interfaces/interfaces.hpp"

using namespace std;

//------------------------------------------------------------------------
// Declaração de classe stub.

class StubServicoAutenticacao: public IServicoAutenticacao {
    private:
        static const string EMAIL_VALIDO;
        static const string SENHA_VALIDA;
    public:
    /**
     * @brief Autentica uma pessoa com base no email e senha fornecidos.
     * @param Email é a chave utilizada para identificar a pessoa a ser autenticada.
     * @param Senha é utilizada para verificar se a credencial apresentada é válida.
     * @return O retorno será padrão verdadeiro ou falso, dependendo da autenticidade
     * das credenciais fornecidas.
     */
        bool autenticarPessoa(const Email&, const Senha&) override;
};

#endif // STUBS_HPP_INCLUDED
