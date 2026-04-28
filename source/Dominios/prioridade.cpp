//#include "Dominios/prioridade.hpp"
#include "Dominios/dominios.hpp"

void Prioridade::validar(const std::string& prioridade) {
    if(prioridade != "BAIXA" && prioridade !=  "ALTA" && prioridade != "MEDIA") throw std::invalid_argument("Prioridade invalida.");
}
