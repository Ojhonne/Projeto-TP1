#include "Stubs/stubs.hpp"

const string StubServicoAutenticacao::EMAIL_VALIDO = "joaof@gmail.com";
const string StubServicoAutenticacao::SENHA_VALIDA = "J1fa2b";

bool StubServicoAutenticacao::autenticarPessoa(const Email& email, const Senha& senha){
    if(email.getValor().compare(EMAIL_VALIDO) != 0)
        return false;
    if(senha.getValor().compare(SENHA_VALIDA) != 0)
        return false;
    return true;
}


