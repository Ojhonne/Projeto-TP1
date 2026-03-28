#include <iostream>
#include "senha.hpp"

bool Senha::validaSenha(string senha) {
    int tam_atual{};
    tam_atual = senha.size();
    if(tam_atual > tam_maximo || tam_atual < tam_maximo) return false;
    int k{},j{};
    int check_min{}, check_mai{}, check_dig{};
    for(int i = 0; i < tam_atual; i++) {
        if((!isdigit(senha[i])) && (!isalpha(senha[i]))) return false;
        if(isdigit(senha[k]) && isdigit(senha[k+1])) return false;
        if(isalpha(senha[j]) && isalpha(senha[j+1])) return false;
        if(islower(senha[i])) check_min++;
        if(isupper(senha[i])) check_mai++;
        if(isdigit(senha[i])) check_dig++;
        if(k && j < 6) {
            k++;
            j++;
        }
    }
    if(!check_min || !check_mai || !check_dig) return false;
    return true;
}

bool Senha::setSenha(string senha) {
    if(!validaSenha(senha)) return false;
    this->senha = senha;
    return true;
}