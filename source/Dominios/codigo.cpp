//#include "codigo.hpp"
#include <cstring>
#include <cctype>
#include <stdexcept>
#include "Dominios/dominios.hpp"

void Codigo::validar(const std::string& s)
{
    //verifica o tamaho da string
    if(s.size() != TAMANHO)
        throw std::invalid_argument("Codigo invalido.");

    //verifica se as primeiras duas letras sao maiusculas
    if(!isupper(s[0]) || !isupper(s[1]))
        throw std::invalid_argument("Codigo invalido.");

    //verifica se os ultimos carateres sao digitos
    for(int i = 0; i < 3; i++)
    {
        if(!isdigit(s[i + 2]))
            throw std::invalid_argument("Codigo invalido.");
    }

}


