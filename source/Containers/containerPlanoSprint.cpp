#include "Containers/containerPlanoSprint.hpp"
#include "Entidades/planoDeSprint.hpp"
#include "Dominios/dominios.hpp"

#include <stdexcept>
#include <iostream>

ContainerPlanoSprint* ContainerPlanoSprint::instancia = nullptr;

ContainerPlanoSprint* ContainerPlanoSprint::getInstancia() {
    if (instancia == nullptr) {
        instancia = new ContainerPlanoSprint();
    }

    return instancia;
}

ContainerPlanoSprint::ContainerPlanoSprint() {
    sqlite3* db = nullptr;
    char* mensagemErro = nullptr;

    conectarBanco(db);

    std::string sql =
        "CREATE TABLE IF NOT EXISTS PlanoDeSprint ("
        "codigo TEXT PRIMARY KEY,"
        "texto TEXT NOT NULL,"
        "tempo TEXT NOT NULL,"
        "projeto_codigo TEXT NOT NULL,"
        "FOREIGN KEY (projeto_codigo) REFERENCES Projeto(codigo)"
        ");";

    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &mensagemErro) != SQLITE_OK) {
        std::string erro = mensagemErro;
        sqlite3_free(mensagemErro);
        sqlite3_close(db);
        throw std::runtime_error("Erro ao criar tabela PlanoDeSprint: " + erro);
    }

    sqlite3_close(db);
}

bool ContainerPlanoSprint::criarPlanoSprint(const Codigo& codigoProjeto, const PlanoDeSprint& plano) {
    sqlite3* db = nullptr;
    sqlite3_stmt* stmt = nullptr;

    conectarBanco(db);

    std::string sql =
        "INSERT INTO PlanoDeSprint (codigo, texto, tempo, projeto_codigo) "
        "VALUES (?, ?, ?, ?);";

    abreQuerry(db, sql, stmt);

    std::string codigo = plano.getCodigo().getValor();
    std::string texto = plano.getTexto().getValor();
    std::string tempo = plano.getTempo().getValor();
    std::string projetoCodigo = codigoProjeto.getValor();

    sqlite3_bind_text(stmt, 1, codigo.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, texto.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, tempo.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, projetoCodigo.c_str(), -1, SQLITE_TRANSIENT);

    executaStep(db, stmt);

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return true;
}

bool ContainerPlanoSprint::lerPlanoSprint(const Codigo& codigo, PlanoDeSprint& plano) {
    sqlite3* db = nullptr;
    sqlite3_stmt* stmt = nullptr;

    conectarBanco(db);

    std::string sql =
        "SELECT codigo, texto, tempo "
        "FROM PlanoDeSprint "
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

    std::string textoBd =
        reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));

    std::string tempoBd =
        reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));

    Codigo codigoLocal(codigoBd);
    Texto textoLocal(textoBd);
    Tempo tempoLocal(tempoBd);

    plano.setCodigo(codigoLocal);
    plano.setTexto(textoLocal);
    plano.setTempo(tempoLocal);

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return true;
}

bool ContainerPlanoSprint::atualizarPlanoSprint(const PlanoDeSprint& plano) {
    sqlite3* db = nullptr;
    sqlite3_stmt* stmt = nullptr;

    conectarBanco(db);

    std::string sql =
        "UPDATE PlanoDeSprint "
        "SET texto = ?, tempo = ? "
        "WHERE codigo = ?;";

    abreQuerry(db, sql, stmt);

    std::string texto = plano.getTexto().getValor();
    std::string tempo = plano.getTempo().getValor();
    std::string codigo = plano.getCodigo().getValor();

    sqlite3_bind_text(stmt, 1, texto.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, tempo.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, codigo.c_str(), -1, SQLITE_TRANSIENT);

    executaStep(db, stmt);

    bool atualizou = sqlite3_changes(db) > 0;

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return atualizou;
}

bool ContainerPlanoSprint::excluirPlanoSprint(const Codigo& codigo) {
    sqlite3* db = nullptr;
    sqlite3_stmt* stmt = nullptr;

    conectarBanco(db);

    std::string sql =
        "DELETE FROM PlanoDeSprint "
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

bool ContainerPlanoSprint::listarPlanosSprint(
    const Codigo& codigoProjeto,
    std::vector<PlanoDeSprint>& planos
) {
    sqlite3* db = nullptr;
    sqlite3_stmt* stmt = nullptr;

    conectarBanco(db);

    std::string sql =
        "SELECT codigo, texto, tempo "
        "FROM PlanoDeSprint "
        "WHERE projeto_codigo = ?;";

    abreQuerry(db, sql, stmt);

    std::string codigoProjetoBusca = codigoProjeto.getValor();
    sqlite3_bind_text(stmt, 1, codigoProjetoBusca.c_str(), -1, SQLITE_TRANSIENT);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string codigoBd =
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));

        std::string textoBd =
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));

        std::string tempoBd =
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));

        Codigo codigoLocal(codigoBd);
        Texto textoLocal(textoBd);
        Tempo tempoLocal(tempoBd);

        PlanoDeSprint plano;
        plano.setCodigo(codigoLocal);
        plano.setTexto(textoLocal);
        plano.setTempo(tempoLocal);

        planos.push_back(plano);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return true;
}

void ContainerPlanoSprint::conectarBanco(sqlite3*& db) {
    if (sqlite3_open(nomeBanco.c_str(), &db) != SQLITE_OK) {
        throw std::runtime_error("Erro ao abrir banco de dados.");
    }

    sqlite3_exec(db, "PRAGMA foreign_keys = ON;", nullptr, nullptr, nullptr);
}

void ContainerPlanoSprint::abreQuerry(sqlite3* db, std::string& sql, sqlite3_stmt*& stmt) {
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::string erro = sqlite3_errmsg(db);
        sqlite3_close(db);
        throw std::runtime_error("Erro ao preparar query: " + erro);
    }
}

void ContainerPlanoSprint::executaStep(sqlite3* db, sqlite3_stmt* stmt) {
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::string erro = sqlite3_errmsg(db);
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        throw std::runtime_error("Erro ao executar query: " + erro);
    }
}