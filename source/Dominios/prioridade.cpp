#include "Dominios/prioridade.hpp"

bool Prioridade::validaPrioridade(std::string prioridade) {
    if(prioridade != "BAIXA" && prioridade !=  "ALTA" && prioridade != "MEDIA") return false;
    return true;
}

bool Prioridade::setPrioridade(std::string prioridade) {
    if(!validaPrioridade(prioridade)) return false;
    this->prioridade = prioridade;
    return true;
}