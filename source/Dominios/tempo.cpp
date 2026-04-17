#include "Dominios/tempo.hpp"
#include <stdexcept>
#include <string>

using namespace std;

void Tempo::validar(const string& tempo){
    // 1. Se for vazia, volta
    if (tempo.empty()) throw std::invalid_argument("A string de tempo nao pode estar vazia."); 
    // 2.  Verifica se a string contém APENAS números de 0 a 9.
    if (tempo.find_first_not_of("0123456789") != string::npos) throw std::invalid_argument("O tempo deve conter apenas numeros.");

    try {
        int valorTempo = stoi(tempo); //converte para numero
    
        if (valorTempo < TAM_MINIMO || valorTempo > TAM_MAXIMO) { //verifica os limites
            throw std::out_of_range("Valor da classe tempo esta fora do intervalo permitido");
        }
    } catch (const out_of_range& e) {
        // Intercepta o erro caso o usuário digite uma sequência gigantesca de números
        throw std::out_of_range("O numero digitado eh muito grande");
    }
}

 void Tempo::setTempo(const string& tempo){
    validar(tempo);
    this->tempo = tempo;
 }