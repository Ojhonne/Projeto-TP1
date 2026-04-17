#include "Dominios/papel.hpp"

bool Papel::validaPapel(std::string papel) {
    if(papel != "DESENVOLVEDOR" && papel !=  "MESTRE SCRUM" && papel != "PROPRIETARIO DE PRODUTO") return false;
    return true;
}

bool Papel::setPapel(std::string papel) {
    if(!validaPapel(papel)) return false;
    this->papel = papel;
    return true;
}