//#include "Dominios/papel.hpp"
#include "Dominios/dominios.hpp"
#include <stdexcept>

void Papel::validar(const std::string& papel) {
    if(papel != "DESENVOLVEDOR" && papel !=  "MESTRE SCRUM" && papel != "PROPRIETARIO DE PRODUTO") throw std::invalid_argument("Papel invalido");
}
