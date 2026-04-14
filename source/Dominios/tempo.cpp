#include "Dominios/tempo.hpp"
#include <stdexcept>
#include <string>

using namespace std;

bool Tempo::validar(const string& tempo){
    // 1. Se for vazia, volta
    if (tempo.empty()) {
        return false;
    }

    // 2.  Verifica se a string contém APENAS números de 0 a 9.
    // Se encontrar qualquer coisa diferente, volta.
    if (tempo.find_first_not_of("0123456789") != string::npos) {
        return false;
    }

    // 3. Como garantimos que só tem números, a conversão é segura.
    try {
        int valorTempo = stoi(tempo);
        
        // 4. Aplica a regra de negócio do domínio
        if (valorTempo < TAM_MINIMO || valorTempo > TAM_MAXIMO) {
            return false; 
        }
        return true;
        
    } catch (const out_of_range& e) {
        // Intercepta o erro caso o usuário digite uma sequência gigantesca de números
        // que estoure o limite da memória de um 'int' (ex: "999999999999999999")
        return false;
    }
}

 void Tempo::setTempo(const string& tempo){
    if(!validar(tempo)) throw invalid_argument("Definicao de tempo invalido!");
    this->tempo = tempo;
 }