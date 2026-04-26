#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
#include <stdexcept>
#include "email.hpp"


using namespace std;

void Email:: verificaSeparadores(const std::string& s)
{

    size_t tam = s.size();

    for(size_t i = 0; i < tam; i++){

        if(s[i] == '-' || s[i] == '.'){

            if(i == 0 || i == tam-1){
                throw invalid_argument("Email invalido.");
            }

            if (!( (std::islower(s[i - 1]) || std::isdigit(s[i - 1])) &&
       (std::islower(s[i + 1]) || std::isdigit(s[i + 1])) )){
                throw invalid_argument("Email invalido.");
            }
        }
    }

}

void Email::verifica(const std::string& entrada)
{
    size_t pos = entrada.find('@');

    if (pos == std::string::npos)
    {
        throw invalid_argument("Email invalido."); // nao encontrou o @
    }

    if(entrada.find('@', pos + 1) != std::string::npos)
        throw invalid_argument("Email invalido.");

    std::string parte_local = entrada.substr(0, pos);
    std::string dominio = entrada.substr(pos + 1);

    size_t tam_parte = parte_local.size();
    size_t tam_dominio = dominio.size();

    if (tam_parte == 0 || tam_dominio == 0)
    {
        throw invalid_argument("Email invalido.");  // uma das partes esta vazia
    }

    if (tam_parte > LIMITE_PARTE || tam_dominio > LIMITE_DOMINIO)
    {
        throw invalid_argument("Email invalido.");  // ultrapassa o limite da especificacao
    }

    for (size_t i = 0; i < tam_parte; i++)
    {
        if (!(islower(parte_local[i]) || isdigit(parte_local[i]) ||
              parte_local[i] == '-' || parte_local[i] == '.'))
        {
            throw invalid_argument("Email invalido.");
        }
    }

    for (size_t i = 0; i < tam_dominio; i++)
    {
        if (!(islower(dominio[i]) || isdigit(dominio[i]) ||
              dominio[i] == '-' || dominio[i] == '.'))
        {
            throw invalid_argument("Email invalido.");
        }
    }

    verificaSeparadores(parte_local);
    verificaSeparadores(dominio);

}


void Email:: set(const std::string& entrada)
{
    verifica(entrada);

    this->entrada = entrada;
}
