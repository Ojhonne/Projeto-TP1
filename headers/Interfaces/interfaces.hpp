/**
 * @file interfaces.hpp
 * @brief Definição das interfaces do sistema.
 */

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

/**
 * @interface Esta interface é responsável por permitir que o usuario faça login usando
 *  o email como forma de autenticação.
 */

class IApresentacaoLogin {
public:
    /**
     * @brief Destrutor virtual padrão.
     */

    virtual ~IApresentacaoLogin() = default;

    /**
     * @brief Autentica o usuário por meio da chave email.
     * @param Email é a chave na qual o usuário deverá apresentar, caso o email esteja
     * dentre os autenticados, o usuário poderá fazer login.
     * @return O retorno será padrão verdadeiro ou falso, dependendo da autenticidade do email.
     */

    virtual bool autenticar(Email&) = 0;
};

/**
 * @interface Esta interface é responsável por iniciar a apresentação de cadastro
 * caso o usuário não ainda não tenha.
 */

class IApresentacaoCadastro {
public:
    /**
     * @brief Destrutor virtual padrão.
     */
    virtual ~IApresentacaoCadastro() = default;

    /**
     * @brief Executa a apresentação de cadastro de modo com que o usuário possa
     * fazer o cadastro e, posteriormente, realizar o login, a fim de conseguir
     * acesso ao sistema.
     */

    virtual void executar() = 0;
};

    /**
     * @interface Esta interface é responsável por permitir com que o usuário
     * possa ter acesso ao planejamento de planos de sprint.
     */

class IApresentacaoPlanejamento {
public:

    /**
     * @brief Desstrutor virtual padrão.
     */

    virtual ~IApresentacaoPlanejamento() = default;

    /**
     * @brief Executa a interface de apresentação de planejamento, permitindo com que 
     * o usuario possa usá-la.
     * @param Email é utilizado com o intuito de identificar o usuário que está usando
     * a interface e realizando o planejamento.
     */

    virtual void executar(const Email&) = 0;
};

/**
 * @interface Esta interface é a responsável por tornar possível a interação 
 * do usuário com as histórias de usuário.
 */

class IApresentacaoBacklog {
public:
    /**
     * @brief Destrutor padrão virtual.
     */
    virtual ~IApresentacaoBacklog() = default;

    /**
     * @brief Executa a interface de backlog, permitindo com que o usuário possa
     * ter acesso a tela de backlog e criar uma história de usuário.
     * @param Email é utilizado com o intuito de identificar o usuário que está usando
     * a interface e realizando a história.
     */

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