#include "Controladoras/CrtlServicoAutenticacao.hpp"

/*
CrtlServicoAutenticacao::CrtlServicoAutenticacao(ContainerPessoa* container) {
    this->container = container;
}
*/

bool CrtlServicoAutenticacao::autenticarPessoa(const Email& email, const Senha& senha) {
    //pega os objetos de domínio Email e Senha e convertendo para string para poder fazer a autenticação
    std::string emailStr = email.getValor();
    std::string senhaStr = senha.getValor();

    return container->verificarCredenciais(emailStr, senhaStr);

    // Implementação da lógica de autenticação
    // Aqui você pode adicionar a lógica para verificar as credenciais
    // usando o repositório ContainerPessoa.
    // Por exemplo:
    // return container->verificarCredenciais(email, senha);
    
    // Para fins de exemplo, vamos retornar true.
    return true;
}