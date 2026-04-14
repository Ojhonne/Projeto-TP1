#include "Dominios/dominios.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <cstring>
#include <stdexcept>

using namespace std;

//Implementação do metodo set da classe Base
void Dominio::setValor(const string &valor){
    if(!validar(valor)) throw invalid_argument("Valor invalido");
    this->valor = valor;
}

bool Codigo::validar(const string &s){
    //verifica o tamaho da string
    if(s.size() != TAMANHO)
        return false;

    //verifica se as primeiras duas letras s�o mai�sculas
    if(!isupper(s[0]) || !isupper(s[1]))
        return false;

    //verifica se os �ltimos carateres s�o digitos
    for(int i = 0; i < 3; i++)
    {
        if(!isdigit(s[i + 2]))
            return false;
    }

    // se passou por todas as verifica��es, est� correto
    return true;
}


bool Nome::ehValido(const string &nome){ //função auxiliar de validar da classe nome
    for(char caracter : nome){
        if( (!isalpha(caracter)) && (!isspace(caracter)) ) return false;
    }
    return true;
}

bool Nome::temEspacoInvalido(const string &nome){ //função auxiliar de validar da classe nome
    if (nome.size() <= 1) {
        return false;
    }

    for(size_t i = 0; i < nome.size() - 1; i++){
        if( (isspace(nome.at(i))) && (!isalpha(nome.at(i+1))) ) return true;
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

bool Prioridade::validar(const std::string& prioridade) {
    if(prioridade != "BAIXA" && prioridade !=  "ALTA" && prioridade != "MEDIA") return false;
    return true;
}


bool Senha::validar(const std::string& senha) {
    int tam_atual{};
    tam_atual = senha.size();
    if(tam_atual != TAM_MAXIMO) return false;
    int k{},j{};
    int check_min{}, check_mai{}, check_dig{};
    for(int i = 0; i < tam_atual; i++) {
        if((!isdigit(senha[i])) && (!isalpha(senha[i]))) return false; // confere se tem apenas letras ou numeros
        if(isdigit(senha[k]) && isdigit(senha[k+1])) return false; // confere se tem numero seguido de numero
        if(isalpha(senha[j]) && isalpha(senha[j+1])) return false; // confere se tem letra seguida de letra
        if(islower(senha[i])) check_min++; // flag para letra minuscula
        if(isupper(senha[i])) check_mai++; // flag para letra maiuscula
        if(isdigit(senha[i])) check_dig++; // flag para digito
        if(k < TAM_MAXIMO && j < TAM_MAXIMO) {
            k++;
            j++;
        }
    }
    if(!check_min || !check_mai || !check_dig) return false; // confirma se tem letra maiuscula, minuscula e digito
    return true;
}


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
    if (texto.size() <= 1) {
        return false;
    }
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

bool Papel::validar(const string& papel) {
    if(papel != "DESENVOLVEDOR" && papel !=  "MESTRE_SCRUM" && papel != "PROPRIETARIO DE PRODUTO") return false;
    return true;
}

bool Tempo::validar(const string& tempo){
    // 1. Se for vazia, volta
    if (tempo.empty()) {
        return false;
    }

    // 2.  Verifica se a string contém APENAS números de 0 a 9. Se encontrar qualquer coisa diferente, volta.
    if (tempo.find_first_not_of("0123456789") != string::npos) {
        return false;
    }
    try {
        int valorTempo = stoi(tempo);

        // 4. Testa limites
        if (valorTempo < TAM_MINIMO || valorTempo > TAM_MAXIMO) {
            return false;
        }
        return true;

    } catch (const out_of_range& e) {
        // Intercepta o erro caso o usuário digite uma sequência grande de números
        // que estoure o limite da memória de um 'int' 
        return false;
    }
}

/*
Falta  DATA , PAPEL E EMAIL
*/
