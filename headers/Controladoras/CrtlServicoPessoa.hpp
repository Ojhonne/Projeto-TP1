#ifndef CRTLSERVICOPESSOA_HPP
#define CRTLSERVICOPESSOA_HPP

#include "Interfaces/interfaces.hpp"
#include <vector>
#include <string>

class Email;
class Pessoa;

class CrtlServicoPessoa : public IServicoPessoa {
    public:

        bool criarPessoa(const Pessoa&) override;
        bool lerPessoa(const Email&, Pessoa&) override;
        bool atualizarPessoa(const Pessoa&) override;
        bool excluirPessoa(const Email&) override;

};

#endif