//#include "codigo.hpp"
#include <cstring>
#include <cctype>
#include <stdexcept>

void Codigo::validar(const& char s[])
{
    //verifica o tamaho da string
    if(strlen(s) != TAMANHO)
        throw invalid_argument("Codigo invalido.");

    //verifica se as primeiras duas letras sao maiusculas
    if(!isupper(s[0]) || !isupper(s[1]))
        throw invalid_argument("Codigo invalido.");

    //verifica se os ultimos carateres sao digitos
    for(int i = 0; i < 3; i++)
    {
        if(!isdigit(s[i + 2]))
            throw invalid_argument("Codigo invalido.");
    }

}

void Codigo::setCodigo(const char *s)
{
    valida(s);

    //atribui o codigo ao objeto
    strcpy(codigo,s);
}
