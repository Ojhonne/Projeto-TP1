#include "Controladoras/CrtlServicoPlanejamento.hpp"

#include "Containers/containerPessoa.hpp"
#include "Containers/containerProjeto.hpp"
#include "Containers/containerPlanoSprint.hpp"

#include "Entidades/pessoa.hpp"
#include "Entidades/projeto.hpp"
#include "Entidades/planoDeSprint.hpp"

#include "Dominios/dominios.hpp"

#include <stdexcept>
#include <iostream>

bool CrtlServicoPlanejamento::criarProjeto(const Email& email, const Projeto& projeto) {
    try {
        Pessoa pessoaVerificacao;
        pessoaVerificacao.setEmail(email);

        if (!ContainerPessoa::getInstancia()->lerPessoa(pessoaVerificacao))
            return false;

        if (pessoaVerificacao.getPapel().getValor() != DONO)
            return false;

        return ContainerProjeto::getInstancia()->criarProjeto(email, projeto);
    }
    catch (const std::runtime_error& e) {
        std::cerr << "[Falha no MS-PLANEJAMENTO] Erro de persistência: " << e.what() << std::endl;
        return false;
    }
}

bool CrtlServicoPlanejamento::lerProjeto(const Codigo& codigo, Projeto& projeto) {
    try {
        return ContainerProjeto::getInstancia()->lerProjeto(codigo, projeto);
    }
    catch (const std::runtime_error& e) {
        std::cerr << "[Falha no MS-PLANEJAMENTO] Erro de persistência: " << e.what() << std::endl;
        return false;
    }
}

bool CrtlServicoPlanejamento::atualizarProjeto(const Email& email, const Projeto& projeto) {
    try {
        Pessoa pessoaVerificacao;
        pessoaVerificacao.setEmail(email);

        if (!ContainerPessoa::getInstancia()->lerPessoa(pessoaVerificacao))
            return false;

        if (pessoaVerificacao.getPapel().getValor() != DONO)
            return false;

        return ContainerProjeto::getInstancia()->atualizarProjeto(projeto);
    }
    catch (const std::runtime_error& e) {
        std::cerr << "[Falha no MS-PLANEJAMENTO] Erro de persistência: " << e.what() << std::endl;
        return false;
    }
}

bool CrtlServicoPlanejamento::excluirProjeto(const Email& email, const Codigo& codigo) {
    try {
        Pessoa pessoaVerificacao;
        pessoaVerificacao.setEmail(email);

        if (!ContainerPessoa::getInstancia()->lerPessoa(pessoaVerificacao))
            return false;

        if (pessoaVerificacao.getPapel().getValor() != DONO)
            return false;

        return ContainerProjeto::getInstancia()->excluirProjeto(codigo);
    }
    catch (const std::runtime_error& e) {
        std::cerr << "[Falha no MS-PLANEJAMENTO] Erro de persistência: " << e.what() << std::endl;
        return false;
    }
}

bool CrtlServicoPlanejamento::criarPlanoSprint(
    const Email& email,
    const Codigo& codigoProjeto,
    const PlanoDeSprint& plano
) {
    try {
        Pessoa pessoaVerificacao;
        pessoaVerificacao.setEmail(email);

        if (!ContainerPessoa::getInstancia()->lerPessoa(pessoaVerificacao))
            return false;

        if (pessoaVerificacao.getPapel().getValor() != MESTRE)
            return false;

        return ContainerPlanoSprint::getInstancia()->criarPlanoSprint(codigoProjeto, plano);
    }
    catch (const std::runtime_error& e) {
        std::cerr << "[Falha no MS-PLANEJAMENTO] Erro de persistência: " << e.what() << std::endl;
        return false;
    }
}

bool CrtlServicoPlanejamento::lerPlanoSprint(const Codigo& codigo, PlanoDeSprint& plano) {
    try {
        return ContainerPlanoSprint::getInstancia()->lerPlanoSprint(codigo, plano);
    }
    catch (const std::runtime_error& e) {
        std::cerr << "[Falha no MS-PLANEJAMENTO] Erro de persistência: " << e.what() << std::endl;
        return false;
    }
}

bool CrtlServicoPlanejamento::atualizarPlanoSprint(const Email& email, const PlanoDeSprint& plano) {
    try {
        Pessoa pessoaVerificacao;
        pessoaVerificacao.setEmail(email);

        if (!ContainerPessoa::getInstancia()->lerPessoa(pessoaVerificacao))
            return false;

        if (pessoaVerificacao.getPapel().getValor() != MESTRE)
            return false;

        return ContainerPlanoSprint::getInstancia()->atualizarPlanoSprint(plano);
    }
    catch (const std::runtime_error& e) {
        std::cerr << "[Falha no MS-PLANEJAMENTO] Erro de persistência: " << e.what() << std::endl;
        return false;
    }
}

bool CrtlServicoPlanejamento::excluirPlanoSprint(const Email& email, const Codigo& codigo) {
    try {
        Pessoa pessoaVerificacao;
        pessoaVerificacao.setEmail(email);

        if (!ContainerPessoa::getInstancia()->lerPessoa(pessoaVerificacao))
            return false;

        if (pessoaVerificacao.getPapel().getValor() != MESTRE)
            return false;

        return ContainerPlanoSprint::getInstancia()->excluirPlanoSprint(codigo);
    }
    catch (const std::runtime_error& e) {
        std::cerr << "[Falha no MS-PLANEJAMENTO] Erro de persistência: " << e.what() << std::endl;
        return false;
    }
}

bool CrtlServicoPlanejamento::listarProjetos(const Email& email, std::vector<Projeto>& projetos) {
    try {
        return ContainerProjeto::getInstancia()->listarProjetos(email, projetos);
    }
    catch (const std::runtime_error& e) {
        std::cerr << "[Falha no MS-PLANEJAMENTO] Erro de persistência: " << e.what() << std::endl;
        return false;
    }
}

bool CrtlServicoPlanejamento::listarPlanosSprint(
    const Codigo& codigoProjeto,
    std::vector<PlanoDeSprint>& planos
) {
    try {
        return ContainerPlanoSprint::getInstancia()->listarPlanosSprint(codigoProjeto, planos);
    }
    catch (const std::runtime_error& e) {
        std::cerr << "[Falha no MS-PLANEJAMENTO] Erro de persistência: " << e.what() << std::endl;
        return false;
    }
}