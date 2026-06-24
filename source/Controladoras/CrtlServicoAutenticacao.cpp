#include "Controladoras/CrtlServicoAutenticacao.hpp"
#include "Containers/containerPessoa.hpp"
#include "Entidades/pessoa.hpp"
#include <stdexcept> 
#include <iostream>

bool CrtlServicoAutenticacao::autenticarPessoa(const Email& email, const Senha& senha) {
    Pessoa pessoa;
    pessoa.setEmail(email); // chave primaria

    try{
        // Tenta pesquisar a pessoa no banco de dados através do Singleton
        bool pessoaExiste = ContainerPessoa::getInstancia()->pesquisar(&pessoa);

        if(pessoaExiste) {
            std::string senhaDigitada = senha.getValor(); // senha que o usuario digitou

            std::string senhaDoBanco = pessoa.getSenha().getValor(); // senha puxada do banco

            if(senhaDigitada == senhaDoBanco){
                return true;
            }
        }
        return false; // a pessoa nao existe ou a senha está incorreta
    } catch (const std::runtime_error& e){
        std::cerr << "[Falha no MS-AUTENTICAÇÃO] Erro de persistência: " << e.what() << std::endl;
        return false;
    }
    return true;
}