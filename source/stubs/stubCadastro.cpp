#include "Stubs/stubCadastro.hpp"
#include "Dominios/dominios.hpp"
#include "Entidades/pessoa.hpp"
#include <fstream>
#include <iostream>

// inicializa o vetor estático limpo
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
                << "-------------------------------\n\n";
        arquivo.close();
    }
    return true;
}


bool StubCadastro::atualizarPessoa(const Pessoa& pessoa) {
    std::string emailBusca = pessoa.getEmail().getValor();

    // grava DIRETO no arquivo TXT sem frescura
    std::ofstream arquivo("banco_simulado.txt", std::ios::app);
    if (arquivo.is_open()) {
        arquivo << "[REGISTRO] Dados atualizados para o Email: " << emailBusca << "\n"
                << "Novo Nome:  " << pessoa.getNome().getValor() << "\n"
                << "Nova Senha: " << pessoa.getSenha().getValor() << "\n"
                << "-----------------------------------------\n\n";
        arquivo.close();
    }

    // atualiza no vetor se ele já existir lá dentro
    for (size_t i = 0; i < pessoasCadastradas.size(); i++) {
        if (pessoasCadastradas[i].getEmail().getValor() == emailBusca) {
            pessoasCadastradas[i] = pessoa;
            return true;
        }
    }

    // ae o vetor estava vazio, joga ele lá dentro e retorna true para a interface mudar de tela
    pessoasCadastradas.push_back(pessoa);
    return true;
}


bool StubCadastro::lerPessoa(const Email& email, Pessoa& pessoa) {
    std::string emailBusca = email.getValor();

    if (emailBusca == "joao@teste.com") {
        // Se o joao já foi modificado e está no vetor, puxa os dados modificados
        for (size_t i = 0; i < pessoasCadastradas.size(); i++) {
            if (pessoasCadastradas[i].getEmail().getValor() == emailBusca) {
                pessoa = pessoasCadastradas[i];
                return true;
            }
        }

        Nome n;   n.setValor("Joao");
        Senha s;  s.setValor("Abc123");
        Papel pa; pa.setValor("DESENVOLVEDOR");
        pessoa.setEmail(email);
        pessoa.setNome(n);
        pessoa.setSenha(s);
        pessoa.setPapel(pa);
        return true;
    }

    for (size_t i = 0; i < pessoasCadastradas.size(); i++) {
        if (pessoasCadastradas[i].getEmail().getValor() == emailBusca) {
            pessoa.setEmail(pessoasCadastradas[i].getEmail());
            pessoa.setNome(pessoasCadastradas[i].getNome());
            pessoa.setSenha(pessoasCadastradas[i].getSenha());
            pessoa.setPapel(pessoasCadastradas[i].getPapel());
            return true;
        }
    }
    return false;
}


bool StubCadastro::excluirPessoa(const Email& email) {
    std::string emailBusca = email.getValor();

    // Se for o e-mail forçado do teste, limpa ele do vetor (se houver) e dá verdadeiro sempre!
    if (emailBusca == "joao@teste.com") {
        for (auto it = pessoasCadastradas.begin(); it != pessoasCadastradas.end(); ++it) {
            if (it->getEmail().getValor() == emailBusca) {
                pessoasCadastradas.erase(it);
                break;
            }
        }
        std::ofstream arquivo("banco_simulado.txt", std::ios::app);
        if (arquivo.is_open()) {
            arquivo << "[REGISTRO] Conta simulada excluida: " << emailBusca << "\n";
            arquivo.close();
        }
        return true;
    }

    // varredura para outros e-mails do sistema
    for (auto it = pessoasCadastradas.begin(); it != pessoasCadastradas.end(); ++it) {
        if (it->getEmail().getValor() == emailBusca) {
            pessoasCadastradas.erase(it);

            std::ofstream arquivo("banco_simulado.txt", std::ios::app);
            if (arquivo.is_open()) {
                arquivo << "[REGISTRO] Conta excluida para o Email: " << emailBusca << "\n";
                arquivo.close();
            }
            return true;
        }
    }
    return false;
}
