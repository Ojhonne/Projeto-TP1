#include "Dominios/texto.hpp"
#include <cctype>
#include <string>
#include <stdexcept>

using namespace std;

bool Texto::validar(const std::string& texto){


}


void Texto::setTexto(const std::string& texto){
     if(!validar(texto)) throw invalid_argument("Texto invalido");
     this->texto = texto;
 }