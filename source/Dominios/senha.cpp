#include <iostream>
#include "Dominios/senha.hpp"

bool Senha::validaSenha(std::string senha) {
    int tam_atual{};
    tam_atual = senha.size();
    if(tam_atual > TAM_MAXIMO || tam_atual < TAM_MAXIMO) return false;
    int k{},j{};
    int check_min{}, check_mai{}, check_dig{};
    for(int i = 0; i < tam_atual; i++) {
        if((!isdigit(senha[i])) && (!isalpha(senha[i]))) return false; // confere se tem apenas letras ou numeros
        if(isdigit(senha[k]) && isdigit(senha[k+1])) return false; // confere se tem numero seguido de numero
        if(isalpha(senha[j]) && isalpha(senha[j+1])) return false; // confere se tem letra seguida de letra
        if(islower(senha[i])) check_min++; // flag para letra minuscula
        if(isupper(senha[i])) check_mai++; // flag para letra maiuscula
        if(isdigit(senha[i])) check_dig++; // flag para digito
        if(k && j < TAM_MAXIMO) {
            k++;
            j++;
        }
    }
    if(!check_min || !check_mai || !check_dig) return false; // confirma se tem letra maiuscula, minuscula e digito
    return true;
}

bool Senha::setSenha(std::string senha) {
    if(!validaSenha(senha)) return false;
    this->senha = senha;
    return true;
}