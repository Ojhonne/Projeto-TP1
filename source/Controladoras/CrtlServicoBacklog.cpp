#include "Controladoras/CrtlServicoBacklog.hpp"
#include "Containers/containerBacklog.hpp"
#include "Containers/containerPessoa.hpp"
#include "Entidades/historiaDeUsuario.hpp"
#include "Entidades/pessoa.hpp"
#include <stdexcept> 
#include <iostream>

bool CrtlServicoBacklog::criarHistoriaUsuario(const HistoriaDeUsuario& historia, const Email& usuarioLogado){
    try{
        Pessoa pessoaVericacao;
        pessoaVericacao.setEmail(usuarioLogado);
        // Vai no banco de dados de Usuários e busca quem está logado
        if (!ContainerPessoa::getInstancia()->lerPessoa(pessoaVericacao)) {
            return false;        
        }
        if (pessoaVericacao.getPapel().getValor() != DONO) {
            return false;  
        }

        std::string codigoProjeto = historia.getCodigoProjeto().getValor();
        std::string codigoSprint = historia.getCodigoSprint().getValor();

        // Checa se os dois estão preenchidos ou se os dois estão vazios
        if ((!codigoProjeto.empty() && !codigoSprint.empty()) || (codigoProjeto.empty() && codigoSprint.empty())) {
            // Fere a restrição {OU}. Tem que ter apenas UM dos dois!
            return false; 
        }
        // Tenta criar uma historia  no banco de dados através do Singleton
        if(ContainerBacklog::getInstancia()->criarHistoriaUsuario(historia)){
            return true;
        }
        return false;
    } catch (const std::runtime_error& e){
        std::cerr << "[Falha no MS-BACKLOG] Erro de persistência: " << e.what() << std::endl;
        return false;
    }
 }

bool CrtlServicoBacklog::lerHistoriaUsuario(const Codigo& chaveID, HistoriaDeUsuario& armazenaHistoria ){
    try{
        // Tenta ler uma historia  no banco de dados através do Singleton
        if(ContainerBacklog::getInstancia()->lerHistoriaUsuario(chaveID, armazenaHistoria)){
            return true;
        }
        return false; 
    } catch (const std::runtime_error& e){
        std::cerr << "[Falha no MS-BACKLOG] Erro de persistência: " << e.what() << std::endl;
        return false;
    }
 }

bool CrtlServicoBacklog::atualizarHistoriaUsuario(const HistoriaDeUsuario& historiaAtualizada, const Email& usuarioLogado){
    try{
        Pessoa pessoaVericacao;
        pessoaVericacao.setEmail(usuarioLogado);
        // Vai no banco de dados de Usuários e busca quem está logado
        if (!ContainerPessoa::getInstancia()->lerPessoa(pessoaVericacao)) {
            return false;        
        }
        if (pessoaVericacao.getPapel().getValor() != DONO) {
            return false;  
        }
        // Tenta atualizar uma historia no banco de dados através do Singleton
        if(ContainerBacklog::getInstancia()->atualizarHistoriaUsuario(historiaAtualizada)){
            return true;
        }
        return false; 
    } catch (const std::runtime_error& e){
        std::cerr << "[Falha no MS-BACKLOG] Erro de persistência: " << e.what() << std::endl;
        return false;
    }
 }
 
bool CrtlServicoBacklog::excluirHistoriaUsuario(const Codigo& chaveID, const Email& usuarioLogado){
    try{
        // Tenta excluir uma historia no banco de dados através do Singleton
        Pessoa pessoaVericacao;
        pessoaVericacao.setEmail(usuarioLogado);
        // Vai no banco de dados de Usuários e busca quem está logado
        if (!ContainerPessoa::getInstancia()->lerPessoa(pessoaVericacao)) {
            return false;         // Se o usuário não existe no banco
        }
        if (pessoaVericacao.getPapel().getValor() != DONO) {
            return false;  // Acesso negado! 
        }
        if(ContainerBacklog::getInstancia()->excluirHistoriaUsuario(chaveID)){
            return true;
        }
        return false; 
    } catch (const std::runtime_error& e){
        std::cerr << "[Falha no MS-BACKLOG] Erro de persistência: " << e.what() << std::endl;
        return false;
    }
 }

bool CrtlServicoBacklog::listarHistoriasAssociadasProjeto(const Codigo& chaveID, std::vector<HistoriaDeUsuario>& armazenamentoHistoria){
    try{
        // Tenta listar historias no banco de dados através do Singleton
        if(ContainerBacklog::getInstancia()->listarHistoriasAssociadasProjeto(chaveID, armazenamentoHistoria)){
            return true;
        }
        return false; 
    } catch (const std::runtime_error& e){
        std::cerr << "[Falha no MS-BACKLOG] Erro de persistência: " << e.what() << std::endl;
        return false;
    }
 }

bool CrtlServicoBacklog::listarHistoriasAssociadasPlanoSprint(const Codigo& chaveID, std::vector<HistoriaDeUsuario>& armazenamentoHistoria) {
    try{
        // Tenta listar historias do banco de dados através do Singleton
        if(ContainerBacklog::getInstancia()->listarHistoriasAssociadasPlanoSprint(chaveID, armazenamentoHistoria)){
            return true;
        }
        return false; 
    } catch (const std::runtime_error& e){
        std::cerr << "[Falha no MS-BACKLOG] Erro de persistência: " << e.what() << std::endl;
        return false;
    }
 }

 bool CrtlServicoBacklog::listarHistoriasAssociadasPessoa(const Email& emailID, std::vector<HistoriaDeUsuario>& armazenamentoHistoria){
    try{
        // Tenta listar historias do banco de dados através do Singleton
        if(ContainerBacklog::getInstancia()->listarHistoriasAssociadasPessoa(emailID, armazenamentoHistoria)){
            return true;
        }
        return false; 
    } catch (const std::runtime_error& e){
        std::cerr << "[Falha no MS-BACKLOG] Erro de persistência: " << e.what() << std::endl;
        return false;
    }
 }

bool CrtlServicoBacklog::moverHistoriaProjetoParaSprint(const Codigo& codigoHistoria, const Codigo& codigoSprint, const Email& usuarioLogado){
    HistoriaDeUsuario armazenaHistoria;
    Pessoa pessoaVericacao;
    pessoaVericacao.setEmail(usuarioLogado);
    try{
        // Vai no banco de dados de Usuários e busca quem está logado
        if (!ContainerPessoa::getInstancia()->lerPessoa(pessoaVericacao)) {
            return false;        
        }
        if (pessoaVericacao.getPapel().getValor() != MESTRE) {
            return false;  
        }
        if(lerHistoriaUsuario(codigoHistoria, armazenaHistoria)){
            armazenaHistoria.setCodigoSprint(codigoSprint);

            // apagando o código do Projeto para manter a regra {OU} do UML
            Codigo codigoVazio; // Código limpo
            armazenaHistoria.setCodigoProjeto(codigoVazio);

            if(atualizarHistoriaUsuario(armazenaHistoria, usuarioLogado)){
                return true; 
            }
        }
        return false;
    } catch (const std::runtime_error& e){
        std::cerr << "[Falha no MS-BACKLOG] Erro de persistência: " << e.what() << std::endl;
        return false;
    }
}

bool CrtlServicoBacklog::associarHistoriaPessoa(const Codigo& codigoHistoria, const Email& emailAlvo, const Email& usuarioLogado){
    HistoriaDeUsuario armazenaHistoria;
    Pessoa pessoaVericacao;
    pessoaVericacao.setEmail(usuarioLogado);
    try{
        if (!ContainerPessoa::getInstancia()->lerPessoa(pessoaVericacao)) {
            return false;        
        }
        if (pessoaVericacao.getPapel().getValor() != MESTRE) {
            return false;  
        }
        if(lerHistoriaUsuario(codigoHistoria, armazenaHistoria)){
            armazenaHistoria.setEmailPessoa(emailAlvo);
            if(atualizarHistoriaUsuario(armazenaHistoria, usuarioLogado)){
                return true; 
            }
        }
        return false;
    } catch (const std::runtime_error& e){
        std::cerr << "[Falha no MS-BACKLOG] Erro de persistência: " << e.what() << std::endl;
        return false;
    }

}

bool CrtlServicoBacklog::removerAssociacaoHistoriaPessoa(const Codigo& codigoHistoria, const Email& emailAlvo, const Email& usuarioLogado){
    HistoriaDeUsuario armazenaHistoria;
    Pessoa pessoaVericacao;
    pessoaVericacao.setEmail(usuarioLogado);
    try{
        if (!ContainerPessoa::getInstancia()->lerPessoa(pessoaVericacao)) {
            return false;        
        }
        if (pessoaVericacao.getPapel().getValor() != MESTRE) {
            return false;  
        }
        if (lerHistoriaUsuario(codigoHistoria, armazenaHistoria)) {
            if (armazenaHistoria.getEmailPessoa().getValor() == emailAlvo.getValor()) { // // Só remove se o e-mail cadastrado for igual ao e-mail passado no parâmetro
                    Email emailVazio;
                    armazenaHistoria.setEmailPessoa(emailVazio);
                    return atualizarHistoriaUsuario(armazenaHistoria, usuarioLogado); 
            }
        }
            return false;
        } catch (const std::runtime_error& e){
        std::cerr << "[Falha no MS-BACKLOG] Erro de persistência: " << e.what() << std::endl;
        return false;
    }
}

bool CrtlServicoBacklog::alterarEstadoHistoria(const Codigo& codigoHistoria, const Estado& novoEstado, const Email& usuarioLogado){
    HistoriaDeUsuario armazenaHistoria;
    Pessoa pessoaVericacao;
    pessoaVericacao.setEmail(usuarioLogado);
    try{
        if (!ContainerPessoa::getInstancia()->lerPessoa(pessoaVericacao)) {
            return false;        
        }
        if (pessoaVericacao.getPapel().getValor() != MESTRE && pessoaVericacao.getPapel().getValor() != DONO) {
            return false;  
        }
        if(lerHistoriaUsuario(codigoHistoria, armazenaHistoria)){
            armazenaHistoria.setEstado(novoEstado);
            if(atualizarHistoriaUsuario(armazenaHistoria, usuarioLogado)){
                return true; 
            }
        }
        return false;
    } catch (const std::runtime_error& e){
        std::cerr << "[Falha no MS-BACKLOG] Erro de persistência: " << e.what() << std::endl;
        return false;
    }
}