#include "Dominios/nome.hpp"
#include <cctype>
#include <string>
#include <stdexcept>
using namespace std;

bool Nome::ehValido(const string &nome){
    for(char caracter : nome){ 
        if( (!isalpha(caracter)) && (!isspace(caracter)) ) return false;
    }
    return true;
}

bool Nome::temEspacoInvalido(const string &nome){
    if (nome.size() <= 1) { //verifica se é unico caractere
        return false; 
    }

    for(size_t i = 0; i < nome.size() - 1; i++){
        if( (isspace(nome.at(i))) && (!isalpha(nome.at(i+1))) ) return true; //se for espaço;
    }
    return false;
}

bool Nome::validar(const string& nome){

    if(nome.empty() || (nome.size() > TAM_MAXIMO) ) return false; //nome não pode ser vazio ou ter mais do que 10 caracteres
    if(isspace(nome.at(0)) || isspace(nome.at(nome.size() - 1))) return false; // o primeiro e ultimo caracter não pode ser espaço em branco
    if(!ehValido(nome)) return false; // verifica se existe caracteres nao permitidos na string
    if(temEspacoInvalido(nome)) return false; //se o digito for vazio e proximo não for caracter 

   return true;
}

void Nome::setNome(const string &nome){
    if(!validar(nome)) throw invalid_argument("Nome invalido");
    this->nome = nome;
}