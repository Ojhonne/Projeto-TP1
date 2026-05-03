#include "Dominios/dominios.hpp"
#include <stdexcept>

void Prioridade::validar(const std::string& prioridade) {
    if(prioridade != "BAIXA" && prioridade !=  "ALTA" && prioridade != "MEDIA") throw std::invalid_argument("Prioridade invalida.");
}
