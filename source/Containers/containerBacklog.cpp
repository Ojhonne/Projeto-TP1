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
    s
}

