#include "Dominios/papel.hpp"

void Papel::validaPapel(std::string papel) {
    if(papel != "DESENVOLVEDOR" && papel !=  "MESTRE SCRUM" && papel != "PROPRIETARIO DE PRODUTO") throw invalid_argument("Papel invalido");
}

void Papel::setPapel(std::string papel) {
    validaPapel(papel)
    this->papel = papel;
}