#include "dominios.hpp"
#include <cstring>
#include <cctype>

bool Codigo::valida(const char s[])
{
    //verifica o tamaho da string
    if(strlen(s) != TAMANHO)
        return false;

    //verifica se as primeiras duas letras são maiúsculas
    if(!isupper(s[0]) || !isupper(s[1]))
        return false;

    //verifica se os últimos carateres são digitos
    for(int i = 0; i < 3; i++)
    {
        if(!isdigit(s[i + 2]))
            return false;
    }

    // se passou por todas as verificações, está correto
    return true;
}

bool Codigo::setCodigo(const char *s)
{
   if (!valida(s))
    return false;

    //atribui o código ao objeto
    strcpy(codigo,s);
    return true;
}
