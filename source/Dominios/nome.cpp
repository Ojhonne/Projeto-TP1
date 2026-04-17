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

bool Nome::temEspacoValido(const string &nome){
    for(size_t i = 0; i < nome.size() - 1; i++){
        if( (isspace(nome.at(i))) && (!isalpha(nome.at(i+1))) ) return false;//se for espaço;
    }
    return true;
}

void Nome::validar(const string& nome){

    if(nome.empty() || (nome.size() > TAM_MAXIMO) ) throw length_error("Tamanho da classe nome invalido");  //nome não pode ser vazio ou ter mais do que 10 caracteres
    if(isspace(nome.at(0)) || isspace(nome.at(nome.size() - 1))) throw invalid_argument("Formato da classe nome invalido"); // o primeiro e ultimo caracter não pode ser espaço em branco
    if(!ehValido(nome)) throw invalid_argument("Formato da classe nome invalido") ; // verifica se existe caracteres nao permitidos na string
    if(!temEspacoValido(nome)) throw invalid_argument("Formato da classe nome invalido"); //se o digito for vazio e proximo não for caracter 

}

void Nome::setNome(const string &nome){
    validar(nome);
    this->nome = nome;
}