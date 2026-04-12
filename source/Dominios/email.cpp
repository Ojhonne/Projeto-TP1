#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
#include "email.hpp"


using namespace std;

bool Email:: verificaSeparadores(const std::string& s)
{

    size_t tam = s.size();

    for(size_t i = 0; i < tam; i++){

        if(s[i] == '-' || s[i] == '.'){

            if(i == 0 || i == tam-1){
                return false;
            }

            if (!( (std::islower(s[i - 1]) || std::isdigit(s[i - 1])) &&
       (std::islower(s[i + 1]) || std::isdigit(s[i + 1])) )){
                return false;
            }
        }
    }

    return true;
}

bool Email::verifica(const std::string& entrada)
{
    size_t pos = entrada.find('@');

    if (pos == std::string::npos)
    {
        return false; // nao encontrou o @
    }

    if(entrada.find('@', pos + 1) != std::string::npos)
        return false;

    std::string parte_local = entrada.substr(0, pos);
    std::string dominio = entrada.substr(pos + 1);

    size_t tam_parte = parte_local.size();
    size_t tam_dominio = dominio.size();

    if (tam_parte == 0 || tam_dominio == 0)
    {
        return false; // uma das partes está vazia
    }

    if (tam_parte > LIMITE_PARTE || tam_dominio > LIMITE_DOMINIO)
    {
        return false; // ultrapassa o limite da especificacao
    }

    for (size_t i = 0; i < tam_parte; i++)
    {
        if (!(islower(parte_local[i]) || isdigit(parte_local[i]) ||
              parte_local[i] == '-' || parte_local[i] == '.'))
        {
            return false;
        }
    }

    for (size_t i = 0; i < tam_dominio; i++)
    {
        if (!(islower(dominio[i]) || isdigit(dominio[i]) ||
              dominio[i] == '-' || dominio[i] == '.'))
        {
            return false;
        }
    }

    if(!verificaSeparadores(parte_local) || !verificaSeparadores(dominio)){
        return false;
    }

    return true;
}


bool Email:: set(const std::string& entrada)
{
    if(!verifica(entrada))
        return false;

    this->entrada = entrada;
    return true;
}
