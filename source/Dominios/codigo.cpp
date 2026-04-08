#include "Dominios/codigo.hpp"
#include <cstring>
#include <cctype>

bool Codigo::valida(const char s[])
{
    //verifica o tamaho da string
    if(strlen(s) != TAMANHO)
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

bool Codigo::setCodigo(const char *s)
{
   if (!valida(s))
        return false;

    //atribui o c�digo ao objeto
    strcpy(codigo,s);
    return true;
}
