#include "Containers/containerProjeto.hpp"
#include "Entidades/projeto.hpp"
#include "Dominios/dominios.hpp"

#include <stdexcept>
#include <iostream>

ContainerProjeto* ContainerProjeto::instancia = nullptr;

ContainerProjeto* ContainerProjeto::getInstancia() {
    if (instancia == nullptr) {
        instancia = new ContainerProjeto();
    }

    return instancia;
}

ContainerProjeto::ContainerProjeto() {
    sqlite3* db = nullptr;
    char* mensagemErro = nullptr;

    conectarBanco(db);

    std::string sql =
        "CREATE TABLE IF NOT EXISTS Projeto ("
        "codigo TEXT PRIMARY KEY,"
        "nome TEXT NOT NULL,"
        "inicio TEXT NOT NULL,"
        "termino TEXT NOT NULL,"
        "pessoa_email TEXT NOT NULL,"
        "FOREIGN KEY (pessoa_email) REFERENCES Pessoa(email)"
        ");";

    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &mensagemErro) != SQLITE_OK) {
        std::string erro = mensagemErro;
        sqlite3_free(mensagemErro);
        sqlite3_close(db);
        throw std::runtime_error("Erro ao criar tabela Projeto: " + erro);
    }

    sqlite3_close(db);
}

bool ContainerProjeto::criarProjeto(const Email& email, const Projeto& projeto) {
    sqlite3* db = nullptr;
    sqlite3_stmt* stmt = nullptr;

    conectarBanco(db);

    std::string sql =
        "INSERT INTO Projeto (codigo, nome, inicio, termino, pessoa_email) "
        "VALUES (?, ?, ?, ?, ?);";

    abreQuerry(db, sql, stmt);

    std::string codigo = projeto.getCodigo().getValor();
    std::string nome = projeto.getNome().getValor();
    std::string inicio = projeto.getInicio().getData();
    std::string termino = projeto.getTermino().getData();
    std::string pessoaEmail = email.getValor();

    sqlite3_bind_text(stmt, 1, codigo.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, nome.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, inicio.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, termino.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, pessoaEmail.c_str(), -1, SQLITE_TRANSIENT);

    executaStep(db, stmt);

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return true;
}

bool ContainerProjeto::lerProjeto(const Codigo& codigo, Projeto& projeto) {
    sqlite3* db = nullptr;
    sqlite3_stmt* stmt = nullptr;

    conectarBanco(db);

    std::string sql =
        "SELECT codigo, nome, inicio, termino "
        "FROM Projeto "
        "WHERE codigo = ?;";

    abreQuerry(db, sql, stmt);

    std::string codigoBusca = codigo.getValor();
    sqlite3_bind_text(stmt, 1, codigoBusca.c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) != SQLITE_ROW) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return false;
    }

    std::string codigoBd =
        reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));

    std::string nomeBd =
        reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));

    std::string inicioBd =
        reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));

    std::string terminoBd =
        reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));

    Codigo codigoLocal(codigoBd);
    Nome nomeLocal(nomeBd);

    Data inicioLocal;
    inicioLocal.setValor(inicioBd);

    Data terminoLocal;
    terminoLocal.setValor(terminoBd);

    projeto.setCodigo(codigoLocal);
    projeto.setNome(nomeLocal);
    projeto.setInicio(inicioLocal);
    projeto.setTermino(terminoLocal);

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return true;
}

bool ContainerProjeto::atualizarProjeto(const Projeto& projeto) {
    sqlite3* db = nullptr;
    sqlite3_stmt* stmt = nullptr;

    conectarBanco(db);

    std::string sql =
        "UPDATE Projeto "
        "SET nome = ?, inicio = ?, termino = ? "
        "WHERE codigo = ?;";

    abreQuerry(db, sql, stmt);

    std::string nome = projeto.getNome().getValor();
    std::string inicio = projeto.getInicio().getData();
    std::string termino = projeto.getTermino().getData();
    std::string codigo = projeto.getCodigo().getValor();

    sqlite3_bind_text(stmt, 1, nome.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, inicio.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, termino.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, codigo.c_str(), -1, SQLITE_TRANSIENT);

    executaStep(db, stmt);

    bool atualizou = sqlite3_changes(db) > 0;

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return atualizou;
}

bool ContainerProjeto::excluirProjeto(const Codigo& codigo) {
    sqlite3* db = nullptr;
    sqlite3_stmt* stmt = nullptr;

    conectarBanco(db);

    std::string sql =
        "DELETE FROM Projeto "
        "WHERE codigo = ?;";

    abreQuerry(db, sql, stmt);

    std::string codigoBusca = codigo.getValor();
    sqlite3_bind_text(stmt, 1, codigoBusca.c_str(), -1, SQLITE_TRANSIENT);

    executaStep(db, stmt);

    bool excluiu = sqlite3_changes(db) > 0;

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return excluiu;
}

bool ContainerProjeto::listarProjetos(const Email& email, std::vector<Projeto>& projetos) {
    sqlite3* db = nullptr;
    sqlite3_stmt* stmt = nullptr;

    conectarBanco(db);

    std::string sql =
        "SELECT codigo, nome, inicio, termino "
        "FROM Projeto "
        "WHERE pessoa_email = ?;";

    abreQuerry(db, sql, stmt);

    std::string emailBusca = email.getValor();
    sqlite3_bind_text(stmt, 1, emailBusca.c_str(), -1, SQLITE_TRANSIENT);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string codigoBd =
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));

        std::string nomeBd =
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));

        std::string inicioBd =
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));

        std::string terminoBd =
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));

        Codigo codigoLocal(codigoBd);
        Nome nomeLocal(nomeBd);

        Data inicioLocal;
        inicioLocal.setValor(inicioBd);

        Data terminoLocal;
        terminoLocal.setValor(terminoBd);

        Projeto projeto;
        projeto.setCodigo(codigoLocal);
        projeto.setNome(nomeLocal);
        projeto.setInicio(inicioLocal);
        projeto.setTermino(terminoLocal);

        projetos.push_back(projeto);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return true;
}

void ContainerProjeto::conectarBanco(sqlite3*& db) {
    if (sqlite3_open(nomeBanco.c_str(), &db) != SQLITE_OK) {
        throw std::runtime_error("Erro ao abrir banco de dados.");
    }

    sqlite3_exec(db, "PRAGMA foreign_keys = ON;", nullptr, nullptr, nullptr);
}

void ContainerProjeto::abreQuerry(sqlite3* db, std::string& sql, sqlite3_stmt*& stmt) {
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::string erro = sqlite3_errmsg(db);
        sqlite3_close(db);
        throw std::runtime_error("Erro ao preparar query: " + erro);
    }
}

void ContainerProjeto::executaStep(sqlite3* db, sqlite3_stmt* stmt) {
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::string erro = sqlite3_errmsg(db);
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        throw std::runtime_error("Erro ao executar query: " + erro);
    }
}