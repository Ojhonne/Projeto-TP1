#ifndef INTERFACES_HPP_INCLUDED
#define INTERFACES_HPP_INCLUDED

#include "Dominios/dominios.hpp"
#include "Entidades/historiaDeUsuario.hpp"
#include "Entidades/pessoa.hpp"
#include "Entidades/planoDeSprint.hpp"
#include "Entidades/projeto.hpp"

// Interfaces da camada de apresentacao
/*
Montei as interfaces no mesmo padrão, um método construtor default para cada interface. Além disso, cada uma delas possui
um método de execução de telas, menus e leitura, as quais possuem como assinatura o endereço da conta em que os serviços serão providos
. Com exceção da interface de cadastro, a qual não prove nenhum serviço diretamente ao usuário, somente cria a conta. Os métodos sempre
irão devolver um boolean, indicando se a operação foi feita com sucesso.
*/

class IApresentacaoLogin {
public:
    virtual ~IApresentacaoLogin() = default;

    virtual bool autenticar(Email&) = 0;
};

class IApresentacaoCadastro {
public:
    virtual ~IApresentacaoCadastro() = default;

    virtual void executar() = 0;
};

class IApresentacaoPlanejamento {
public:
    virtual ~IApresentacaoPlanejamento() = default;

    virtual void executar(const Email&) = 0;
};

class IApresentacaoBacklog {
public:
    virtual ~IApresentacaoBacklog() = default;

    virtual void executar(const Email&) = 0;
};

// Interfaces da camada de servico
/*
Para as interfaces de serviço eu também criei um cosntrutor default, os métodos de cada interface são as CRUD'S citadas nas 
especificações do trabalho. Todos os parâmetros foram passados como referência e constantes, com excessão das entidades nos métodos de leitura, 
já que esses sim serão parâmetros modificados. Uma observação importante, os domínios passados como parâmetros são todos PK's, 
os quais serão utilizados para referênciar a entidade que o método se aplicará.
*/

class IServicoAutenticacao {
public:
    virtual ~IServicoAutenticacao() = default;

    virtual bool autenticarPessoa(const Email&, const Senha&) = 0;
};

class IServicoPessoa {
public:
    virtual ~IServicoPessoa() = default;

    virtual bool criarPessoa(const Pessoa&) = 0;
    virtual bool lerPessoa(const Email&, Pessoa&) = 0;
    virtual bool atualizarPessoa(const Pessoa&) = 0;
    virtual bool excluirPessoa(const Email&) = 0;
};

class IServicoPlanejamento {
public:
    virtual ~IServicoPlanejamento() = default;

    virtual bool criarProjeto(const Projeto&) = 0;
    virtual bool lerProjeto(const Codigo&, Projeto&) = 0;
    virtual bool atualizarProjeto(const Projeto&) = 0;
    virtual bool excluirProjeto(const Codigo&) = 0;

    virtual bool criarPlanoSprint(const PlanoDeSprint&) = 0;
    virtual bool lerPlanoSprint(const Codigo&, PlanoDeSprint&) = 0;
    virtual bool atualizarPlanoSprint(const PlanoDeSprint&) = 0;
    virtual bool excluirPlanoSprint(const Codigo&) = 0;

    virtual bool listarProjetosAssociadosPessoa(const Email&) = 0;
    virtual bool listarPlanosSprintAssociadosProjeto(const Codigo&) = 0;
};

class IServicoBacklog {
public:
    virtual ~IServicoBacklog() = default;

    virtual bool criarHistoriaUsuario(const HistoriaDeUsuario&) = 0;
    virtual bool lerHistoriaUsuario(const Codigo&, HistoriaDeUsuario&) = 0;
    virtual bool atualizarHistoriaUsuario(const HistoriaDeUsuario&) = 0;
    virtual bool excluirHistoriaUsuario(const Codigo&) = 0;

    virtual bool associarHistoriaPessoa(const Codigo&, const Email&) = 0;
    virtual bool removerAssociacaoHistoriaPessoa(const Codigo&, const Email&) = 0;

    virtual bool listarHistoriasAssociadasProjeto(const Codigo&) = 0;
    virtual bool listarHistoriasAssociadasPlanoSprint(const Codigo&) = 0;
    virtual bool listarHistoriasAssociadasPessoa(const Email&) = 0;

    virtual bool moverHistoriaProjetoParaSprint(const Codigo&, const Codigo&) = 0;
    virtual bool alterarEstadoHistoria(const Codigo&, const Estado&) = 0;
};

#endif