#include "Dominios/texto.hpp"

#include <cctype>
#include <string>
#include <stdexcept>

using namespace std;

bool Texto::ehValido(const string& texto){
        for(char c : texto){ //percorre o vetor de char e verifica as condições dadas
            if( !isalpha(c) && !isdigit(c) && (c != ',') && (c != '.') && !isspace(c) ) return false; //se for não alfabeto e não for digito e não for virgula e não for ponto e não for espaço
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
    if (texto.size() <= 1) { //verifica se é unico caractere
        return false; 
    }

    for(size_t i = 0; i < texto.size() - 1; i++){  //percorre o vetor de char e verifica as condições dadas
        if( isspace(texto.at(i)) && !(isalpha(texto.at(i+1)) || isdigit(texto.at(i+1)))) return false;  //se for espaço e o proximo não for alfabeto ou digito
    }
    return true;
}

void Texto::validar(const string& texto){

    if( ( texto.empty() ) || ( texto.size() > TAM_MAXIMO) ) throw length_error("Tamanho da classe texto invalido");  //  texto não pode ser vazio ou ter mais de 40 caracteres
    if( ( texto.front() == ',' ) || ( texto.front() == '.' ) || ( isspace(texto.front())) ) throw invalid_argument("Formato da classe texto invalido"); //primeiro caracter não pode ser vírgula, ponto ou espaço em branco.
    if( ( texto.back() == ',' ) || ( texto.back() == '.') || ( isspace(texto.back())) ) throw invalid_argument("Formato da classe texto invalido"); // último caracter não pode ser vírgula, ponto ou espaço em branco.
    if( !ehValido(texto) )  throw invalid_argument("Formato da classe texto invalido"); // confere se o caracter é letra (a-z ou A-Z), dígito (0-9), vírgula, ponto ou espaço em branco;
    if( !temFormatacaoValida(texto) )  throw invalid_argument("Formato da classe texto invalido"); // confere se vírgula não pode ser seguida por vírgula ou ponto e ponto não pode ser seguido por vírgula ou ponto; 
    if( !temEspacoinvalida(texto) )  throw invalid_argument("Formato da classe texto invalido");// confere se o digito é  espaço em branco o prox é seguido por letra ou dígito;

}

void Texto::setTexto(const string& texto){
     validar(texto);
     this->texto = texto;
 }