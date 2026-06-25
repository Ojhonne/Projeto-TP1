#include "Containers/containerPessoa.hpp"
#include "Dominios/dominios.hpp"  
#include <stdexcept> 
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

bool ContainerPessoa::lerPessoa(Email email, Pessoa* pessoa) {
    sqlite3* db; // ponteiro para o banco de dados SQLite.
    bool pessoaEncontrada{false}; // flag para indicar se a pessoa foi encontrada no banco de dados.
    
    // Abre o banco
    if (sqlite3_open(nomeBanco.c_str(), &db) == SQLITE_OK) {
        // Instrução SQL com um "bind parameter" (?) para evitar injeção de SQL
        std::string sql = "SELECT nome, senha, papel FROM Pessoa WHERE email = ?;";
        sqlite3_stmt* stmt; // É o "Statement". É um objeto do SQLite que representa a sua query já compilada e pronta para rodar.

        // Prepara a query
        if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) { // -1 avisa para o SQLite ler a string até encontrar o caractere nulo (\0) que marca o final dela.
            
            // Pega o email que foi passado na entidade 
            std::string emailBusca = pessoa->getEmail().getValor();
            
            // Vincula a string C++ no lugar da interrogação (?) na query SQL
            sqlite3_bind_text(stmt, 1, emailBusca.c_str(), -1, SQLITE_STATIC);

            // Executa a query. Se retornar SQLITE_ROW, achou uma linha no banco!
            if (sqlite3_step(stmt) == SQLITE_ROW) { // Ele manda a query para o banco de dados de fato.
                // Extrai as colunas retornadas pelo SELECT
                // Coluna 0: nome, Coluna 1: senha, Coluna 2: papel
                std::string nomeBd = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
                std::string senhaBd = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
                std::string papelBd = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));

                // Recria os objetos de domínio
                Nome nome;   
                nome.setValor(nomeBd);
                Senha senha; 
                senha.setValor(senhaBd);
                Papel papel; 
                papel.setValor(papelBd);

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

bool ContainerPessoa::criarPessoa(Pessoa pessoa) {
    sqlite3* db = nullptr; 
    sqlite3_stmt* stmt = nullptr;

    conectarBanco(db);

    std::string sql =  "INSERT INTO Pessoa (email, nome, senha, papel) Values (?, ?, ?, ?);";

    abreQuerry(db, sql, stmt);

    std::string emailNovo = pessoa.getEmail().getValor();
    std::string nomeNovo = pessoa.getNome().getValor();
    std::string senhaNova = pessoa.getSenha().getValor();
    std::string papelNovo = pessoa.getPapel().getValor();

    sqlite3_bind_text(stmt, 1, emailNovo.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, nomeNovo.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, senhaNova.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, papelNovo.c_str(), -1, SQLITE_STATIC);

    executaStep(db, stmt);

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return true;
}

bool ContainerPessoa::excluirPessoa(Email email) {
    sqlite3* db = nullptr; 
    sqlite3_stmt* stmt = nullptr;

    conectarBanco(db);

    std::string sql = "DELETE FROM Pessoa WHERE email = ?;";

    abreQuerry(db, sql, stmt);

    std::string emailDeletar = email.getValor();

    sqlite3_bind_text(stmt, 1, emailDeletar.c_str(), -1, SQLITE_STATIC);

    executaStep(db, stmt);
        
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return true;
}

bool ContainerPessoa::atualizarPessoa(Pessoa pessoa) {
    sqlite3* db = nullptr; 
    sqlite3_stmt* stmt = nullptr;

    conectarBanco(db);

    std::string sql = "UPDATE Pessoa SET nome = ?, senha = ?, papel = ? WHERE email = ?;";

    abreQuerry(db, sql, stmt);

    std::string nomeAtualizado = pessoa.getNome().getValor();
    std::string senhaAtualizada = pessoa.getSenha().getValor();
    std::string papelAtualizado = pessoa.getPapel().getValor();
    std::string emailOriginal = pessoa.getEmail().getValor();

    sqlite3_bind_text(stmt, 1, nomeAtualizado.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, senhaAtualizada.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, papelAtualizado.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, emailOriginal.c_str(), -1, SQLITE_STATIC);

    executaStep(db, stmt);

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return true;
}

// Funçoes auxiliares

void ContainerPessoa::conectarBanco(sqlite3*& db){
    if(sqlite3_open(nomeBanco.c_str(), &db) != SQLITE_OK){ // Erro ao abrir o arquivo
        std::string erro = sqlite3_errmsg(db);
        sqlite3_close(db);
        throw std::runtime_error("Erro ao abrir o banco de dados: " + erro);
    }
}

void ContainerPessoa::abreQuerry(sqlite3* db, std::string& sql, sqlite3_stmt*& stmt){
    if(sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK){  // Erro de sintaxe no SQL ou tabela não existe
        std::string erro = sqlite3_errmsg(db);
        sqlite3_close(db);
        throw std::runtime_error("Erro ao preparar a query: " + erro);
    }
}

void ContainerPessoa::executaStep(sqlite3* db, sqlite3_stmt* stmt){
    if(sqlite3_step(stmt) != SQLITE_DONE){ // Erro na execução 
        std::string erro = sqlite3_errmsg(db);
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        throw std::runtime_error("Erro ao inserir dados: " + erro);
    }
}