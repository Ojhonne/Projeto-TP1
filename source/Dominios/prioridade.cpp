#include "Dominios/prioridade.hpp"

void Prioridade::validaPrioridade(std::string prioridade) {
    if(prioridade != "BAIXA" && prioridade !=  "ALTA" && prioridade != "MEDIA") throw invalid_argument("Prioridade invalida.");
}

void Prioridade::setPrioridade(std::string prioridade) {
    validaPrioridade(prioridade);
    this->prioridade = prioridade;
}