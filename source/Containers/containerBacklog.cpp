#include "Containers/containerBacklog.hpp"
#include "Sql/sqlite3.h"
#include <stdexcept> 
#include <iostream>

ContainerBacklog* ContainerBacklog::instancia = nullptr; //inicializa com nullptr o ponteiro para a instância da classe ContainerPessoa (Singleton).

ContainerBacklog* ContainerBacklog::getInstancia(){
    if(instancia == nullptr){
        instancia = new ContainerBacklog();
    } 
    return instancia;
}

ContainerBacklog::ContainerBacklog(){
    sqlite3* db; 
    int resultCode = sqlite3_open(nomeBanco.c_str(), &db); 

    if (resultCode == SQLITE_OK) { 
        std::string sql = "CREATE TABLE IF NOT EXISTS HistoriaDeUsuario (" 
                            "codigo TEXT PRIMARY KEY, "
                            "titulo TEXT NOT NULL, "
                            "papel TEXT NOT NULL, "
                            "acao TEXT NOT NULL, "
                            "valor TEXT NOT NULL, "
                            "estimativa INTEGER NOT NULL, "
                            "prioridade TEXT NOT NULL, "
                            "estado TEXT NOT NULL, "
                            "projeto_codigo TEXT NOT NULL, "
                            "sprint_codigo  TEXT, "
                            "pessoa_email  TEXT, "
                            "FOREIGN KEY(projeto_codigo) REFERENCES Projeto(codigo), "
                            "FOREIGN KEY(sprint_codigo) REFERENCES PlanoDeSprint(codigo), "
                            "FOREIGN KEY(pessoa_email) REFERENCES Pessoa(email));";
                          
        char* mensagemErro = nullptr;
        resultCode = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &mensagemErro); 
        
        if (resultCode != SQLITE_OK) { 
            std::string erro = mensagemErro;
            std::cerr << "Erro ao criar tabela HistoriaDeUsuario: " << mensagemErro << std::endl;
            sqlite3_free(mensagemErro);
            sqlite3_close(db); 

            throw std::runtime_error("Erro ao criar tabela HistoriaDeUsuario: " + erro);
        
        }
    }
    sqlite3_close(db); // Fecha o banco de dados SQLite.
    
}






// Funçoes auxiliares

void ContainerBacklog::conectarBanco(sqlite3*& db){
    if(sqlite3_open(nomeBanco.c_str(), &db) != SQLITE_OK){ // Erro ao abrir o arquivo
        std::string erro = sqlite3_errmsg(db);
        sqlite3_close(db);
        throw std::runtime_error("Erro ao abrir o banco de dados: " + erro);
    }
}

void ContainerBacklog::abreQuerry(sqlite3* db, std::string& sql, sqlite3_stmt*& stmt){
    if(sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK){  // Erro de sintaxe no SQL ou tabela não existe
        std::string erro = sqlite3_errmsg(db);
        sqlite3_close(db);
        throw std::runtime_error("Erro ao preparar a query: " + erro);
    }
}

void ContainerBacklog::executaStep(sqlite3* db, sqlite3_stmt* stmt){
    if(sqlite3_step(stmt) != SQLITE_DONE){ // Erro na execução 
        std::string erro = sqlite3_errmsg(db);
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        throw std::runtime_error("Erro ao inserir dados: " + erro);
    }
}