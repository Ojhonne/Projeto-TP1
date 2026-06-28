#include "Stubs/stubCadastro.hpp"
#include "Dominios/dominios.hpp"
#include "Entidades/pessoa.hpp"
#include <fstream>
#include <iostream>

// Inicializa o vetor estático limpo
std::vector<Pessoa> StubCadastro::pessoasCadastradas = {};


bool StubCadastro::criarPessoa(const Pessoa& pessoa) {
    std::string emailNovo = pessoa.getEmail().getValor();

    for (size_t i = 0; i < pessoasCadastradas.size(); i++) {
        if (pessoasCadastradas[i].getEmail().getValor() == emailNovo) {
            return false;
        }
    }

    pessoasCadastradas.push_back(pessoa);


    std::ofstream arquivo("banco_simulado.txt", std::ios::app);
    if (arquivo.is_open()) {
        arquivo << "--- NOVO CADASTRO VALIDADO ---\n"
                << "Email: " << emailNovo << "\n"
                << "Nome:  " << pessoa.getNome().getValor() << "\n"
                << "Papel: " << pessoa.getPapel().getValor() << "\n" // <-- LINHA ADICIONADA
                << "-------------------------------\n\n";
        arquivo.close();
    }
    return true;
}


bool StubCadastro::atualizarPessoa(const Pessoa& pessoa) {
    std::string emailBusca = pessoa.getEmail().getValor();

    // grava o registro de Log no arquivo físico TXT
    std::ofstream arquivo("banco_simulado.txt", std::ios::app);
    if (arquivo.is_open()) {
        arquivo << "[REGISTRO] Dados atualizados para o Email: " << emailBusca << "\n"
                << "Novo Nome:  " << pessoa.getNome().getValor() << "\n"
                << "Nova Senha: " << pessoa.getSenha().getValor() << "\n"
                << "-----------------------------------------\n\n";
        arquivo.close();
    }

    // atualiza os dados no vetor em memória RAM
    for (size_t i = 0; i < pessoasCadastradas.size(); i++) {
        if (pessoasCadastradas[i].getEmail().getValor() == emailBusca) {
            pessoasCadastradas[i] = pessoa;
            return true;
        }
    }

    // se o vetor estava vazio (teste do joao), insere ele para as próximas consultas
    pessoasCadastradas.push_back(pessoa);
    return true;
}


bool StubCadastro::lerPessoa(const Email& email, Pessoa& pessoa) {
    std::string emailBusca = email.getValor();

    for (size_t i = 0; i < pessoasCadastradas.size(); i++) {
        if (pessoasCadastradas[i].getEmail().getValor() == emailBusca) {
            pessoa = pessoasCadastradas[i];
            return true;
        }
    }

    if (emailBusca == "joao@teste.com") {
        Nome n;   n.setValor("Joao");
        Senha s;  s.setValor("Abc123");
        Papel pa; pa.setValor("DESENVOLVEDOR");
        pessoa.setEmail(email);
        pessoa.setNome(n);
        pessoa.setSenha(s);
        pessoa.setPapel(pa);
        return true;
    }
    return false;
}


bool StubCadastro::excluirPessoa(const Email& email) {
    std::string emailBusca = email.getValor();

    std::ofstream arquivo("banco_simulado.txt", std::ios::app);
    if (arquivo.is_open()) {
        arquivo << "[REGISTRO] Conta excluida para o Email: " << emailBusca << "\n";
        arquivo.close();
    }

    for (auto it = pessoasCadastradas.begin(); it != pessoasCadastradas.end(); ++it) {
        if (it->getEmail().getValor() == emailBusca) {
            pessoasCadastradas.erase(it);
            return true;
        }
    }
    return true; // Retorna true para o login fictício funcionar mesmo com o vetor vazio
}
