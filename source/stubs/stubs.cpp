#include "Stubs\stubs.hpp"

const string StubServicoAutenticacao::INVALIDO = "joaof@gmail.com";
const string StubServicoAutenticacao::SENHA = "111111";

bool StubServicoAutenticacao::autenticarPessoa(const Email& email, const Senha& senha){
    if(email.getValor().compare(INVALIDO) == 0)
        return false;
    if(senha.getValor().compare(SENHA) != 0)
        return false;
    return true;
}


