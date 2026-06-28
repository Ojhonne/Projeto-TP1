#include "Controladoras/CrtlServicoPessoa.hpp"
#include "Containers/containerPessoa.hpp"
#include "Entidades/pessoa.hpp"
#include <stdexcept>
#include <iostream>

bool CrtlServicoPessoa::criarPessoa(const Pessoa& pessoa) {
    try {
        return ContainerPessoa::getInstancia()->criarPessoa(pessoa);
    }
    catch (const std::runtime_error& e) {
        std::cerr << "[Falha no MS-BACKLOG] Erro de persistência: "
                  << e.what() << std::endl;
        return false;
    }
}

bool CrtlServicoPessoa::lerPessoa(const Email& chaveID, Pessoa& armazenaPessoa) {
    try {
        armazenaPessoa.setEmail(chaveID);

        return ContainerPessoa::getInstancia()->lerPessoa(armazenaPessoa);

    } catch (const std::runtime_error& e) {
        std::cerr << "[Falha no MS-BACKLOG] Erro de persistência: "
                  << e.what() << std::endl;
        return false;
    }
}

bool CrtlServicoPessoa::atualizarPessoa(const Pessoa& pessoaAtualizada) {
    try{
        return ContainerPessoa::getInstancia()->atualizarPessoa(pessoaAtualizada);
    }
    catch(const std::runtime_error& e){
        std::cerr << "[Falha no MS-BACKLOG] Erro de persistência: "
                  << e.what() << std::endl;
        return false;
    }
}

bool CrtlServicoPessoa::excluirPessoa(const Email& email) {
    try {
        return ContainerPessoa::getInstancia()->excluirPessoa(email);
    }
    catch (const std::runtime_error& e) {
        std::cerr << "[Falha no MS-BACKLOG] Erro de persistência: "
                  << e.what() << std::endl;
        return false;
    }
}