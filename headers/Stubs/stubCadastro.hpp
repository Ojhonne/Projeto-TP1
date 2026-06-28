#ifndef STUBCADASTRO_HPP_INCLUDED
#define STUBCADASTRO_HPP_INCLUDED

#include "Interfaces/interfaces.hpp"
#include "Dominios/dominios.hpp"
#include "Entidades/pessoa.hpp"
#include <vector>

class StubCadastro : public IServicoPessoa {
private:
    // Memória do Stub para guardar os objetos Pessoa completos
    static std::vector<Pessoa> pessoasCadastradas;

public:
    virtual ~StubCadastro() = default;

    bool criarPessoa(const Pessoa&) override;
    bool lerPessoa(const Email&, Pessoa&) override;
    bool atualizarPessoa(const Pessoa&) override;
    bool excluirPessoa(const Email&) override;
};

#endif
