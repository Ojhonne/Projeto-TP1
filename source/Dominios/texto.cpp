#include "Dominios/texto.hpp"

#include <cctype>
#include <string>
#include <stdexcept>

using namespace std;

bool Texto::ehValido(const string& texto){
        for(char c : texto){ //percorre o vetor de char e verifica as condições dadas
            if( !isalpha(c) && !isdigit(c) && (c != ',') && (c != '.') && !isspace(c) ) return false; //se for não alfabeto e naõ for digito e não for virgula e não for ponto e não for espaço
        }
        return true;
}

bool Texto::temFormatacaoValida(const std::string& texto ){
    for(size_t i = 0; i < texto.size() - 1; i++){
        if( (texto.at(i) == ',') && ( (texto.at(i + 1) == ',') || (texto.at(i + 1) == '.')  ) ) return false; // virgula seguida de virgula ou ponto
        if( (texto.at(i) == '.') && ( (texto.at(i + 1) == ',') || (texto.at(i + 1) == '.')  ) ) return false; // ponto seguido de virgula ou ponto
    }
    return true;
}

bool Texto::temEspacoinvalida(const std::string& texto ){
    for(size_t i = 0; i < texto.size() - 1; i++){  //percorre o vetor de char e verifica as condições dadas
        if( isspace(texto.at(i)) && !(isalpha(texto.at(i+1)) || isdigit(texto.at(i+1)))) return false;  //se for espaço e o proximo não for alfabeto ou digito
    }
    return true;
}

bool Texto::validar(const string& texto){

    if( ( texto.empty() ) || ( texto.size() > TAM_MAXIMO) ) return false; //  texto não pode ser vazio ou ter mais de 40 caracteres
    if( ( texto.front() == ',' ) || ( texto.front() == '.' ) || ( isspace(texto.front())) ) return false; //primeiro caracter não pode ser vírgula, ponto ou espaço em branco.
    if( ( texto.back() == ',' ) || ( texto.back() == '.') || ( isspace(texto.back())) ) return false; // último caracter não pode ser vírgula, ponto ou espaço em branco.
    if( !ehValido(texto) ) return false; // confere se o caracter é letra (a-z ou A-Z), dígito (0-9), vírgula, ponto ou espaço em branco;
    if( !temFormatacaoValida(texto) ) return false; // confere se vírgula não pode ser seguida por vírgula ou ponto e ponto não pode ser seguido por vírgula ou ponto; 
    if( !temEspacoinvalida(texto) ) return false; // confere se o digito é  espaço em branco o prox é seguido por letra ou dígito;

    return true;
}

void Texto::setTexto(const string& texto){
     if(!validar(texto)) throw invalid_argument("Texto invalido");
     this->texto = texto;
 }