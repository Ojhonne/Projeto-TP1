#include "Controladoras/CrtlServicoBacklog.hpp"
#include "Containers/containerBacklog.hpp"
#include "Entidades/HistoriaDeUsuario.hpp"
#include <stdexcept> 
#include <iostream>

bool CrtlServicoBacklog::criarHistoriaUsuario(const HistoriaDeUsuario& historia, const Email& usuarioLogado){
    try{
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
    try{
        if(lerHistoriaUsuario(codigoHistoria, armazenaHistoria)){
            armazenaHistoria.setCodigoSprint(codigoSprint);
            if(atualizarHistoriaUsuario(armazenaHistoria)){
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
    try{
        if(lerHistoriaUsuario(codigoHistoria, armazenaHistoria)){
            armazenaHistoria.setEmailPessoa(emailAlvo);
            if(atualizarHistoriaUsuario(armazenaHistoria)){
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
    try{
            if (lerHistoriaUsuario(codigoHistoria, armazenaHistoria)) {
                if (armazenaHistoria.getEmailPessoa().getValor() == emailAlvo.getValor()) { // // Só remove se o e-mail cadastrado for igual ao e-mail passado no parâmetro
                    Email emailVazio;
                    armazenaHistoria.setEmailPessoa(emailVazio);
                    return atualizarHistoriaUsuario(armazenaHistoria); 
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

    try{
        if(lerHistoriaUsuario(codigoHistoria, armazenaHistoria)){
            armazenaHistoria.setEstado(novoEstado);
            if(atualizarHistoriaUsuario(armazenaHistoria)){
                return true; 
            }
        }
        return false;
    } catch (const std::runtime_error& e){
        std::cerr << "[Falha no MS-BACKLOG] Erro de persistência: " << e.what() << std::endl;
        return false;
    }
}