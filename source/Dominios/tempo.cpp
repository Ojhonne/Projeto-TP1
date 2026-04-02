#include "Dominios/tempo.hpp"
#include <stdexcept>

using namespace std;

bool Tempo::validar(const int& tempo){
    if(tempo <= 0  || tempo > 365) return false; 
    return true;
}

 void Tempo::setTempo(const int& tempo){
    if(!validar(tempo)) throw invalid_argument("Definicao de tempo invalido!");
    this->tempo = tempo;
 }