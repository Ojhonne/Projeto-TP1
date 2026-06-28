#include "Containers/containerBacklog.hpp"
#include "Sql/sqlite3.h"
#include <stdexcept> 
#include <iostream>
#include <string>
#include "Entidades/historiaDeUsuario.hpp"

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
                            "projeto_codigo TEXT, "
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

bool ContainerBacklog::criarHistoriaUsuario(const HistoriaDeUsuario& historia){
    sqlite3* db = nullptr; 
    sqlite3_stmt* stmt = nullptr;

    conectarBanco(db); // abrindo o banco

    std::string sql = "INSERT INTO HistoriaDeUsuario (codigo, titulo, papel, acao, valor, estimativa, prioridade, estado, projeto_codigo) "
                  "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?);";

    abreQuerry(db, sql, stmt);   // Prepara a query

    std::string CodigoNovo = historia.getCodigo().getValor();
    std::string tituloNovo = historia.getTitulo().getValor(); 
    std::string papelNovo = historia.getPapel().getValor();
    std::string acaoNova = historia.getAcao().getValor();
    std::string valorNovo = historia.getValor().getValor(); 
    std::string estimativa = historia.getEstimativa().getValor();
    int estimativaNova = std::stoi(estimativa);
    std::string priodadeNovo = historia.getPrioridade().getValor();
    std::string estadoNovo = historia.getEstado().getValor();
    std::string projeto_codigo = historia.getCodigoProjeto().getValor(); 

    sqlite3_bind_text(stmt, 1, CodigoNovo.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, tituloNovo.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, papelNovo.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, acaoNova.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, valorNovo.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 6, estimativaNova);
    sqlite3_bind_text(stmt, 7, priodadeNovo.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 8, estadoNovo.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 9, projeto_codigo.c_str(), -1, SQLITE_STATIC);

    executaStep(db, stmt);   // Executa a query. 

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return true;
}
bool ContainerBacklog::lerHistoriaUsuario(const Codigo& codigo, HistoriaDeUsuario& historia){
    sqlite3* db = nullptr; 
    sqlite3_stmt* stmt = nullptr;

    conectarBanco(db); // abrindo o banco

    std::string sql = "SELECT titulo, papel, acao, valor, estimativa, prioridade, estado, projeto_codigo FROM HistoriaDeUsuario WHERE codigo = ?;";

    abreQuerry(db, sql, stmt);   // Prepara a query
    std::string CodigoBuscado = codigo.getValor();

    sqlite3_bind_text(stmt, 1, CodigoBuscado.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_ROW) {
        std::string erro = sqlite3_errmsg(db);
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return false;
    }

    // Extrai as colunas retornadas pelo SELECTel
    std::string tituloBd = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
    std::string papelBd = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
    std::string acaoBd = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
    std::string valorBd = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
    int estimativaIntBd = (sqlite3_column_int(stmt, 4));
    std::string estimativaStringBd = std::to_string(estimativaIntBd);
    std::string prioridadeBd = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
    std::string estadoBd = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));
    std::string projeto_codigoBd = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7));

    // Recria os objetos de domínio
    Texto titulo, papel, acao, valor;
    titulo.setValor(tituloBd);
    papel.setValor(papelBd);
    acao.setValor(acaoBd);
    valor.setValor(valorBd);
    Tempo estimativa;
    estimativa.setValor(estimativaStringBd);
    Prioridade prioridade;
    prioridade.setValor(prioridadeBd);
    Estado estado;
    estado.setValor(estadoBd);
    Codigo projeto_codigo;
    projeto_codigo.setValor(projeto_codigoBd);

    // Preenche a entidade Historia de usuario original recebida por ponteiro
    historia.setTitulo(titulo);
    historia.setPapel(papel);
    historia.setAcao(acao);
    historia.setValor(valor);
    historia.setEstimativa(estimativa);
    historia.setPrioridade(prioridade);
    historia.setEstado(estado);
    historia.setCodigoProjeto(projeto_codigo);

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return true;
}

bool ContainerBacklog::atualizarHistoriaUsuario(const HistoriaDeUsuario& historia){
    sqlite3* db = nullptr; 
    sqlite3_stmt* stmt = nullptr;

    conectarBanco(db); // abrindo o banco

    std::string sql = "UPDATE HistoriaDeUsuario SET titulo = ?, papel = ?, acao = ?, valor = ?, estimativa = ?, prioridade  = ?, estado= ?, projeto_codigo= ?, sprint_codigo = ?, pessoa_email = ? WHERE codigo = ?;";

    abreQuerry(db, sql, stmt);   // Prepara a query

    std::string tituloAtualizado = historia.getTitulo().getValor(); 
    std::string papelAtualizado = historia.getPapel().getValor();
    std::string acaoAtualizada = historia.getAcao().getValor();
    std::string valorAtualizado = historia.getValor().getValor(); 
    std::string estimativa = historia.getEstimativa().getValor();
    int estimativaAtualizada = std::stoi(estimativa);
    std::string priodadeAtualizado = historia.getPrioridade().getValor();
    std::string estadoAtualizado = historia.getEstado().getValor();
    std::string projeto_codigo = historia.getCodigoProjeto().getValor();
    std::string sprint_codigo = historia.getCodigoSprint().getValor();  
    std::string pessoa_email = historia.getEmailPessoa().getValor();  
    std::string codigo = historia.getCodigo().getValor(); 

    sqlite3_bind_text(stmt, 1, tituloAtualizado.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, papelAtualizado.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, acaoAtualizada.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, valorAtualizado.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 5, estimativaAtualizada);
    sqlite3_bind_text(stmt, 6, priodadeAtualizado.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 7, estadoAtualizado.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 8, projeto_codigo.c_str(), -1, SQLITE_STATIC);
    if (sprint_codigo.empty()) {
    sqlite3_bind_null(stmt, 9);
    } else {
        sqlite3_bind_text(stmt, 9, sprint_codigo.c_str(), -1, SQLITE_STATIC);
    }
    if (pessoa_email.empty()) {
    sqlite3_bind_null(stmt, 10);
    } else {
        sqlite3_bind_text(stmt, 10, pessoa_email.c_str(), -1, SQLITE_STATIC);
    }
    sqlite3_bind_text(stmt, 11, codigo.c_str(), -1, SQLITE_STATIC);

    executaStep(db, stmt);   // Executa a query. 

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return true;
}

bool ContainerBacklog:: excluirHistoriaUsuario(const Codigo& codigo) {
    sqlite3* db = nullptr; 
    sqlite3_stmt* stmt = nullptr;

    conectarBanco(db);

    std::string sql = "DELETE FROM HistoriaDeUsuario WHERE codigo = ?;";

    abreQuerry(db, sql, stmt);

    std::string codigoRemover = codigo.getValor();

    sqlite3_bind_text(stmt, 1, codigoRemover.c_str(), -1, SQLITE_STATIC);

    executaStep(db, stmt);
        
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return true;
}


bool ContainerBacklog::listarHistoriasAssociadas(const std::string& sql, const std::string& parametro, std::vector<HistoriaDeUsuario>& historias){
    sqlite3* db = nullptr; 
    sqlite3_stmt* stmt = nullptr;

    conectarBanco(db); // abrindo o banco
    std::string meuSql = sql;
    abreQuerry(db, meuSql, stmt);   // Prepara a query

    sqlite3_bind_text(stmt, 1, parametro.c_str(), -1, SQLITE_STATIC);

    while( (sqlite3_step(stmt) == SQLITE_ROW)){
        std::string codigoBd = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        std::string tituloBd = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        std::string papelBd = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        std::string acaoBd = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        std::string valorBd = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        int estimativaIntBd = (sqlite3_column_int(stmt, 5));
        std::string estimativaStringBd = std::to_string(estimativaIntBd);
        std::string prioridadeBd = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));
        std::string estadoBd = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7));
        std::string projeto_codigoBd = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8));

        // Recria os objetos de domínio
        Texto titulo, papel, acao, valor;
        titulo.setValor(tituloBd);
        papel.setValor(papelBd);
        acao.setValor(acaoBd);
        valor.setValor(valorBd);
        Tempo estimativa;
        estimativa.setValor(estimativaStringBd);
        Prioridade prioridade;
        prioridade.setValor(prioridadeBd);
        Estado estado;
        estado.setValor(estadoBd);
        Codigo projeto_codigo, codigoOriginal;
        projeto_codigo.setValor(projeto_codigoBd);
        codigoOriginal.setValor(codigoBd);

        HistoriaDeUsuario historia;
        historia.setTitulo(titulo);
        historia.setPapel(papel);
        historia.setAcao(acao);
        historia.setValor(valor);
        historia.setEstimativa(estimativa);
        historia.setPrioridade(prioridade);
        historia.setEstado(estado);
        historia.setCodigoProjeto(projeto_codigo);
        historia.setCodigo(codigoOriginal);

        historias.push_back(historia);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return true;
}

bool ContainerBacklog::listarHistoriasAssociadasProjeto(const Codigo& codigo, std::vector<HistoriaDeUsuario>& historias){
    std::string sql = "SELECT codigo, titulo, papel, acao, valor, estimativa, prioridade, estado, projeto_codigo FROM HistoriaDeUsuario WHERE projeto_codigo = ?;";
    return listarHistoriasAssociadas(sql, codigo.getValor(), historias);
}

bool ContainerBacklog::listarHistoriasAssociadasPlanoSprint(const Codigo& codigo, std::vector<HistoriaDeUsuario>& historias){
    std::string sql = "SELECT codigo, titulo, papel, acao, valor, estimativa, prioridade, estado, projeto_codigo FROM HistoriaDeUsuario WHERE sprint_codigo = ?;";
    return listarHistoriasAssociadas(sql, codigo.getValor(), historias);
}

bool ContainerBacklog::listarHistoriasAssociadasPessoa(const Email& email, std::vector<HistoriaDeUsuario>& historias){
    std::string sql = "SELECT codigo, titulo, papel, acao, valor, estimativa, prioridade, estado, projeto_codigo FROM HistoriaDeUsuario WHERE pessoa_email = ?;";
    return listarHistoriasAssociadas(sql, email.getValor(), historias);
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