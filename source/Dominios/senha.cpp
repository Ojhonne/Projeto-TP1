#include <iostream>
#include <stdexcept>
//#include "Dominios/senha.hpp"
#include "Dominios/dominios.hpp"

void Senha::validar(const std::string& senha) {
    int tam_atual{};
    tam_atual = senha.size();
    if(tam_atual > TAM_MAXIMO || tam_atual < TAM_MAXIMO) throw std::invalid_argument("Senha invalida");
    int k{},j{};
    int check_min{}, check_mai{}, check_dig{};
    for(int i = 0; i < tam_atual; i++) {
        if((!isdigit(senha[i])) && (!isalpha(senha[i]))) throw std::invalid_argument("Senha invalida"); // confere se tem apenas letras ou numeros
        if(isdigit(senha[k]) && isdigit(senha[k+1])) throw std::invalid_argument("Senha invalida"); // confere se tem numero seguido de numero
        if(isalpha(senha[j]) && isalpha(senha[j+1])) throw std::invalid_argument("Senha invalida"); // confere se tem letra seguida de letra
        if(islower(senha[i])) check_min++; // flag para letra minuscula
        if(isupper(senha[i])) check_mai++; // flag para letra maiuscula
        if(isdigit(senha[i])) check_dig++; // flag para digito
        if(k && j < TAM_MAXIMO) {
            k++;
            j++;
        }
    }
    if(!check_min || !check_mai || !check_dig) throw std::invalid_argument("Senha invalida"); // confirma se tem letra maiuscula, minuscula e digito
}

