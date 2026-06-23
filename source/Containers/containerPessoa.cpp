#include "Containers/containerPessoa.hpp"
#include "Dominios/dominios.hpp"   
#include "Entidades/pessoa.hpp" 
#include "Sql/sqlite3.h"
#include <iostream>

ContainerPessoa* ContainerPessoa::instancia = nullptr; //inicializa com nullptr o ponteiro para a instância da classe ContainerPessoa (Singleton).

ContainerPessoa* ContainerPessoa::getInstancia(){
    if(instancia == nullptr){
        instancia = new ContainerPessoa();
    }
    return instancia;
}

// O construtor da classe ContainerPessoa é responsável por criar a tabela Pessoa no banco de dados SQLite caso ela não exista.
ContainerPessoa::ContainerPessoa() {
    sqlite3* db; // Ponteiro para o banco de dados SQLite.
    int resultCode = sqlite3_open(nomeBanco.c_str(), &db); // Abre o banco de dados. Se não existir, ele será criado.
    
    if (resultCode == SQLITE_OK) { 
        // Cria a tabela usando os domínios mapeados, com o EMAIL como chave primária
        std::string sql = "CREATE TABLE IF NOT EXISTS Pessoa (" // Cria a tabela Pessoa se ela não existir
                          "email TEXT PRIMARY KEY, "
                          "nome TEXT NOT NULL, "
                          "senha TEXT NOT NULL, "
                          "papel TEXT NOT NULL);";
                          
        char* mensagemErro = nullptr;
        resultCode = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &mensagemErro); // Executa o comando SQL para criar a tabela. Se houver erro, a mensagem será armazenada em mensagemErro.
        
        if (resultCode != SQLITE_OK) { 
            std::string erro = mensagemErro;
            std::cerr << "Erro ao criar tabela Pessoa: " << mensagemErro << std::endl;
            sqlite3_free(mensagemErro);
            sqlite3_close(db); // Fecha o banco de dados SQLite.

            throw std::runtime_error("Erro ao criar tabela Pessoa: " + erro);
        
        }
    }
    sqlite3_close(db); // Fecha o banco de dados SQLite.
}

bool ContainerPessoa::pesquisar(Pessoa* pessoa) {
    sqlite3* db; // ponteiro para o banco de dados SQLite.
    bool pessoaEncontrada = false; // flag para indicar se a pessoa foi encontrada no banco de dados.
    
    // Abre o banco
    if (sqlite3_open(nomeBanco.c_str(), &db) == SQLITE_OK) {
        // Instrução SQL com um "bind parameter" (?) para evitar injeção de SQL
        std::string sql = "SELECT nome, senha, papel FROM Pessoa WHERE email = ?;";
        sqlite3_stmt* stmt;

        // Prepara a query
        if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
            
            // Pega o email que foi passado na entidade (ajuste getEmail()/getValor() conforme seu código)
            std::string emailBusca = pessoa->getEmail().getValor();
            
            // Vincula a string C++ no lugar da interrogação (?) na query SQL
            sqlite3_bind_text(stmt, 1, emailBusca.c_str(), -1, SQLITE_STATIC);

            // Executa a query. Se retornar SQLITE_ROW, achou uma linha no banco!
            if (sqlite3_step(stmt) == SQLITE_ROW) {
                // Extrai as colunas retornadas pelo SELECT
                // Coluna 0: nome, Coluna 1: senha, Coluna 2: papel
                std::string nomeBd = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
                std::string senhaBd = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
                std::string papelBd = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));

                // Recria os objetos de domínio
                Nome nome;   nome.setValor(nomeBd);
                Senha senha; senha.setValor(senhaBd);
                Papel papel; papel.setValor(papelBd);

                // Preenche a entidade Pessoa original recebida por ponteiro
                pessoa->setNome(nome);
                pessoa->setSenha(senha);
                pessoa->setPapel(papel);

                pessoaEncontrada = true;
            }
        }
        // Limpa a memória da query
        sqlite3_finalize(stmt);
    }
    // Fecha o banco
    sqlite3_close(db);
    return pessoaEncontrada;
}

bool ContainerPessoa::incluir(Pessoa pessoa) {
    // 1. Abrir banco
    // 2. Preparar "INSERT INTO Pessoa (email, nome, senha, papel) VALUES (?, ?, ?, ?);"
    // 3. Fazer bind dos 4 atributos usando pessoa.getEmail().getValor(), etc.
    // 4. Executar com sqlite3_step(stmt) e retornar true se der SQLITE_DONE
    // 5. Finalizar e fechar
    return false;
}

bool ContainerPessoa::remover(Email email) {
    // 1. Abrir banco
    // 2. Preparar "DELETE FROM Pessoa WHERE email = ?;"
    // 3. Fazer bind do email
    // 4. Executar e checar sucesso
    // 5. Finalizar e fechar
    return false;
}

bool ContainerPessoa::atualizar(Pessoa pessoa) {
    // 1. Abrir banco
    // 2. Preparar "UPDATE Pessoa SET nome = ?, senha = ?, papel = ? WHERE email = ?;"
    // 3. Fazer os binds adequados
    // 4. Executar e checar sucesso
    // 5. Finalizar e fechar
    return false;
}