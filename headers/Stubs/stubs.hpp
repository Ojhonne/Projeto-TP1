#ifndef STUBS_HPP_INCLUDED
#define STUBS_HPP_INCLUDED

#include <string>
#include "Dominios/dominios.hpp"
#include "Interfaces/interfaces.hpp"

using namespace std;

//------------------------------------------------------------------------
// Declaração de classe stub.

class StubServicoAutenticacao: public IServicoAutenticacao {
    private:
        static const string EMAIL_VALIDO;
        static const string SENHA_VALIDA;
    public:
        bool autenticarPessoa(const Email&, const Senha&) override;
};

#endif // STUBS_HPP_INCLUDED
