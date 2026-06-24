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
        return false; // Não foi possivel criar a historia
    } catch (const std::runtime_error& e){
        std::cerr << "[Falha no MS-BACKLOG] Erro de persistência: " << e.what() << std::endl;
        return false;
    }
 }