#include "Controladoras/CrtlServicoBacklog.hpp"
#include "Containers/containerBacklog.hpp"
#include "Entidades/HistoriaDeUsuario.hpp"
#include <stdexcept> 
#include <iostream>

bool CrtlServicoBacklog::criarHistoriaUsuario(const HistoriaDeUsuario& historia){
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

bool CrtlServicoBacklog::atualizarHistoriaUsuario(const HistoriaDeUsuario& historiaAtualizada){
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
 
bool CrtlServicoBacklog::excluirHistoriaUsuario(const Codigo& chaveID){
    try{
        // Tenta atualizar uma historia no banco de dados através do Singleton
        if(ContainerBacklog::getInstancia()->excluirHistoriaUsuario(chaveID)){
            return true;
        }
        return false; 
    } catch (const std::runtime_error& e){
        std::cerr << "[Falha no MS-BACKLOG] Erro de persistência: " << e.what() << std::endl;
        return false;
    }
 }

bool CrtlServicoBacklog::listarHistoriasAssociadasProjeto(const Codigo& chaveID, std::vector<HistoriaDeUsuario>& armazenamentoHistoria) {
    try{
        // Tenta atualizar uma historia no banco de dados através do Singleton
        if(ContainerBacklog::getInstancia()->listarHistoriasAssociadasProjeto(chaveID, armazenamentoHistoria)){
            return true;
        }
        return false; 
    } catch (const std::runtime_error& e){
        std::cerr << "[Falha no MS-BACKLOG] Erro de persistência: " << e.what() << std::endl;
        return false;
    }
 }

bool CrtlServicoBacklog::listarHistoriasAssociadasPlanoSprintconst Codigo& chaveID, std::vector<HistoriaDeUsuario>& armazenamentoHistoria)  {
    try{
        // Tenta atualizar uma historia no banco de dados através do Singleton
        if(ContainerBacklog::getInstancia()->listarHistoriasAssociadasProjeto(chaveID, armazenamentoHistoria)){
            return true;
        }
        return false; 
    } catch (const std::runtime_error& e){
        std::cerr << "[Falha no MS-BACKLOG] Erro de persistência: " << e.what() << std::endl;
        return false;
    }
 }