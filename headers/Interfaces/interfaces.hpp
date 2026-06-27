/**
 * @file interfaces.hpp
 * @author Eduardo Sankievicz Lima
 * @brief Definição das interfaces do sistema.
 */

#ifndef INTERFACES_HPP_INCLUDED
#define INTERFACES_HPP_INCLUDED

#include <vector>

// Forward declarations.
class Email;
class Senha;
class Codigo;
class Estado;
class Pessoa;
class Projeto;
class PlanoDeSprint;
class HistoriaDeUsuario;
// Interfaces da camada de apresentacao
/*
Montei as interfaces no mesmo padrão, um método construtor default para cada interface. Além disso, cada uma delas possui
um método de execução de telas, menus e leitura, as quais possuem como assinatura o endereço da conta em que os serviços serão providos
. Com exceção da interface de cadastro, a qual não prove nenhum serviço diretamente ao usuário, somente cria a conta. Os métodos sempre
irão devolver um boolean, indicando se a operação foi feita com sucesso.
*/

class IServicoAutenticacao;
class IServicoPessoa;
class IServicoPlanejamento;
class IServicoBacklog;

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
     * @brief Define a referência para o serviço de autenticação a ser utilizado pela interface de apresentação de login.
     * @param IServicoAutenticacao é a referência para o serviço de autenticação que a interface de apresentação de login utilizará para autenticar os usuários.
     * @return O método é do tipo void, portanto não retorna nenhum valor.
     *
     */
    virtual void setCtrlServicoAutenticacao(IServicoAutenticacao*) = 0;

    /**
     * @brief Autentica o usuário por meio da chave email.
     * @param Email é a chave na qual o usuário deverá apresentar, caso o email esteja
     * dentre os autenticados, o usuário poderá fazer login.
     * @return O retorno será padrão verdadeiro ou falso, dependendo da autenticidade do email.
     */

    virtual bool executar(Email&) = 0;
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
     * @brief Define a referência para o serviço de pessoa a ser utilizado pela interface de apresentação de cadastro.
     * @param IServicoPessoa é a referência para o serviço de pessoa que a interface de apresentação de cadastro utilizará para gerenciar as pessoas.
     * @return O método é do tipo void, portanto não retorna nenhum valor.
     */
    virtual void setCtrlServicoPessoa(IServicoPessoa*) = 0;

    /**
     * @brief Executa a apresentação de cadastro de modo com que o usuário possa
     * fazer o cadastro e, posteriormente, realizar o login, a fim de conseguir
     * acesso ao sistema.
     */

    virtual void executar(const Email&) = 0;
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
     * @brief Define a referência para o serviço de planejamento a ser utilizado pela interface de apresentação de planejamento.
     * @param IServicoPlanejamento é a referência para o serviço de planejamento que a interface de apresentação de planejamento utilizará para gerenciar os planos de sprint.
     * @return O método é do tipo void, portanto não retorna nenhum valor.
     */
    virtual void setCtrlServicoPlanejamento(IServicoPlanejamento*) = 0;

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
     * @brief Define a referência para o serviço de backlog a ser utilizado pela interface de apresentação de backlog.
     * @param IServicoBacklog é a referência para o serviço de backlog que a interface de apresentação de backlog utilizará para gerenciar as histórias de usuário.
     * @return O método é do tipo void, portanto não retorna nenhum valor.
     */
    virtual void setCtrlServicoBacklog(IServicoBacklog*) = 0;

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

/**
 * @interface Esta interface é responsável por fazer o link entre a interface
 * de apresentação de login e o sistema.
 */

class IServicoAutenticacao {
public:
    /**
     * @brief Destrutor virtual padrão.
     */
    virtual ~IServicoAutenticacao() = default;

    /**
     * @brief Autentica um usuário por meio do email e da senha fornecidos.
     * @param Email é a chave utilizada para identificar o usuário a ser autenticado.
     * @param Senha é utilizada para verificar se a credencial apresentada é válida.
     * @return O retorno será padrão verdadeiro ou falso, dependendo da autenticidade
     * das credenciais fornecidas.
     */

    virtual bool autenticarPessoa(const Email&, const Senha&) = 0;
};

/**
 * @interface Esta interface é responsável por tornar possível a criação, leitura, atualização
 * e exclusão de uma pessoa.
 */

class IServicoPessoa {
public:
    /**
     * @brief Destrutor virtual padrão.
     */
    virtual ~IServicoPessoa() = default;

    /**
     * @brief Cria uma nova pessoa no sistema.
     * @param Pessoa contém todos os dados necessários para o cadastro da pessoa.
     * @return O retorno será padrão verdadeiro ou falso, dependendo do sucesso da criação.
     */

    virtual bool criarPessoa(const Pessoa&) = 0;

    /**
     * @brief Lê os dados de uma pessoa cadastrada no sistema.
     * @param Email é a chave utilizada para identificar a pessoa a ser consultada.
     * @param Pessoa será preenchida com os dados da pessoa encontrada.
     * @return O retorno será padrão verdadeiro ou falso, dependendo da existência da pessoa.
     */

    virtual bool lerPessoa(const Email&, Pessoa&) = 0;

    /**
     * @brief Atualiza os dados de uma pessoa cadastrada no sistema com base nos novos dados
     * fornecidos pelo usuário.
     * @param Pessoa contém os novos dados da pessoa a serem persistidos.
     * @return O retorno será padrão verdadeiro ou falso, dependendo do sucesso da atualização.
     */

    virtual bool atualizarPessoa(const Pessoa&) = 0;

    /**
     * @brief Exclui uma pessoa do sistema.
     * @param Email é a chave utilizada para identificar a pessoa a ser removida.
     * @return O retorno será padrão verdadeiro ou falso, dependendo do sucesso da exclusão.
     */

    virtual bool excluirPessoa(const Email&) = 0;
};

/**
 * @interface Esta interface é responsável por fazer o link entre a interface
 * de apresentação de planejamento e o sistema.
 */

class IServicoPlanejamento {
public:
    /**
     * @brief Destrutor virtual padrão.
     */
    virtual ~IServicoPlanejamento() = default;

    /**
     * @brief Cria um novo projeto no sistema.
     * @param Projeto contém os dados do projeto a ser criado.
     * @return O retorno será padrão verdadeiro ou falso, dependendo do sucesso da criação.
     */

    virtual bool criarProjeto(const Projeto&) = 0;

    /**
     * @brief Lê os dados de um projeto cadastrado no sistema.
     * @param Codigo é a chave utilizada para identificar o projeto.
     * @param Projeto será preenchido com os dados do projeto encontrado.
     * @return O retorno será padrão verdadeiro ou falso, dependendo da existência do projeto.
     */

    virtual bool lerProjeto(const Codigo&, Projeto&) = 0;

    /**
     * @brief Atualiza os dados de um projeto cadastrado no sistema com base nos novos dados
     * fornecidos pelo usuário.
     * @param Projeto contém os novos dados do projeto a serem persistidos.
     * @return O retorno será padrão verdadeiro ou falso, dependendo do sucesso da atualização.
     */

    virtual bool atualizarProjeto(const Projeto&) = 0;

    /**
     * @brief Exclui um projeto do sistema.
     * @param Codigo é a chave utilizada para identificar o projeto a ser removido.
     * @return O retorno será padrão verdadeiro ou falso, dependendo do sucesso da exclusão.
     */

    virtual bool excluirProjeto(const Codigo&) = 0;

    /**
     * @brief Cria um novo plano de sprint no sistema.
     * @param PlanoDeSprint contém os dados do plano de sprint a ser criado.
     * @return O retorno será padrão verdadeiro ou falso, dependendo do sucesso da criação.
     */

    virtual bool criarPlanoSprint(const PlanoDeSprint&) = 0;

    /**
     * @brief Lê os dados de um plano de sprint cadastrado no sistema.
     * @param Codigo é a chave utilizada para identificar o plano de sprint.
     * @param PlanoDeSprint será preenchido com os dados do plano encontrado.
     * @return O retorno será padrão verdadeiro ou falso, dependendo da existência do plano.
     */

    virtual bool lerPlanoSprint(const Codigo&, PlanoDeSprint&) = 0;

    /**
     * @brief Atualiza os dados de um plano de sprint cadastrado no sistema com base nos novos dados
     * fornecidos pelo usuário.
     * @param PlanoDeSprint contém os novos dados do plano a serem persistidos.
     * @return O retorno será padrão verdadeiro ou falso, dependendo do sucesso da atualização.
     */

    virtual bool atualizarPlanoSprint(const PlanoDeSprint&) = 0;

    /**
     * @brief Exclui um plano de sprint do sistema.
     * @param Codigo é a chave utilizada para identificar o plano a ser removido.
     * @return O retorno será padrão verdadeiro ou falso, dependendo do sucesso da exclusão.
     */

    virtual bool excluirPlanoSprint(const Codigo&) = 0;

    /**
     * @brief Lista os projetos associados a uma pessoa.
     * @param Email é a chave utilizada para identificar a pessoa.
     * @param std::vector<Projeto>& é o vetor que será preenchido com os projetos associados à pessoa.
     * @return O retorno será padrão verdadeiro ou falso, dependendo da existência de projetos associados.
     */

    virtual bool listarProjetos(const Email&, std::vector<Projeto>&) = 0;

    /**
     * @brief Lista os planos de sprint associados a um projeto.
     * @param Codigo é a chave utilizada para identificar o projeto.
     * @param std::vector<PlanoDeSprint>& é o vetor que será preenchido com os planos de sprint associados ao projeto.
     * @return O retorno será padrão verdadeiro ou falso, dependendo da existência de planos associados.
     */


    virtual bool listarPlanosSprint(const Codigo&, std::vector<PlanoDeSprint>&) = 0;
};

/**
 * @interface Esta interface é responsável por fazer o link entre a interface
 * de apresentação de backlog e o sistema.
 */

class IServicoBacklog {
public:
    /**
     * @brief Destrutor virtual padrão.
     */
    virtual ~IServicoBacklog() = default;

    /**
     * @brief Cria uma nova história de usuário no sistema.
     * @param HistoriaDeUsuario contém os dados da história a ser criada.
     * @return O retorno será padrão verdadeiro ou falso, dependendo do sucesso da criação.
     */

    virtual bool criarHistoriaUsuario(const HistoriaDeUsuario&) = 0;

    /**
     * @brief Lê os dados de uma história de usuário cadastrada no sistema.
     * @param Codigo é a chave utilizada para identificar a história.
     * @param HistoriaDeUsuario será preenchida com os dados da história encontrada.
     * @return O retorno será padrão verdadeiro ou falso, dependendo da existência da história.
     */

    virtual bool lerHistoriaUsuario(const Codigo&, HistoriaDeUsuario&) = 0;

    /**
     * @brief Atualiza os dados de uma história de usuário cadastrada no sistema com base nos novos dados
     * fornecidos pelo usuário.
     * @param HistoriaDeUsuario contém os novos dados da história a serem persistidos.
     * @return O retorno será padrão verdadeiro ou falso, dependendo do sucesso da atualização.
     */

    virtual bool atualizarHistoriaUsuario(const HistoriaDeUsuario&) = 0;

    /**
     * @brief Exclui uma história de usuário do sistema.
     * @param Codigo é a chave utilizada para identificar a história a ser removida.
     * @return O retorno será padrão verdadeiro ou falso, dependendo do sucesso da exclusão.
     */

    virtual bool excluirHistoriaUsuario(const Codigo&) = 0;

    /**
     * @brief Associa uma história de usuário a uma pessoa.
     * @param Codigo é a chave utilizada para identificar a história.
     * @param Email é a chave utilizada para identificar a pessoa.
     * @return O retorno será padrão verdadeiro ou falso, dependendo do sucesso da associação.
     */

    virtual bool associarHistoriaPessoa(const Codigo&, const Email&) = 0;

    /**
     * @brief Remove a associação entre uma história de usuário e uma pessoa.
     * @param Codigo é a chave utilizada para identificar a história.
     * @param Email é a chave utilizada para identificar a pessoa.
     * @return O retorno será padrão verdadeiro ou falso, dependendo do sucesso da remoção.
     */

    virtual bool removerAssociacaoHistoriaPessoa(const Codigo&, const Email&) = 0;

    /**
     * @brief Lista as histórias de usuário associadas a um projeto.
     * @param Codigo é a chave utilizada para identificar o projeto.
     * @param std::vector<HistoriaDeUsuario>& é o vetor que será preenchido com as histórias associadas ao projeto.
     * @return O retorno será padrão verdadeiro ou falso, dependendo da existência de histórias associadas.
     */

    virtual bool listarHistoriasAssociadasProjeto(const Codigo&, std::vector<HistoriaDeUsuario>&) = 0;

    /**
     * @brief Lista as histórias de usuário associadas a um plano de sprint.
     * @param Codigo é a chave utilizada para identificar o plano de sprint.
     * @param std::vector<HistoriaDeUsuario>& é o vetor que será preenchido com as histórias associadas ao plano de sprint.
     * @return O retorno será padrão verdadeiro ou falso, dependendo da existência de histórias associadas.
     */

    virtual bool listarHistoriasAssociadasPlanoSprint(const Codigo&, std::vector<HistoriaDeUsuario>&) = 0;

    /**
     * @brief Lista as histórias de usuário associadas a uma pessoa.
     * @param Email é a chave utilizada para identificar a pessoa.
     * @param std::vector<HistoriaDeUsuario>& é o vetor que será preenchido com as histórias associadas à pessoa.
     * @return O retorno será padrão verdadeiro ou falso, dependendo da existência de histórias associadas.
     */

    virtual bool listarHistoriasAssociadasPessoa(const Email&, std::vector<HistoriaDeUsuario>&) = 0;

    /**
     * @brief Move uma história de usuário de um projeto para um plano de sprint.
     * @param Codigo é a chave utilizada para identificar a história.
     * @param Codigo é a chave utilizada para identificar o plano de sprint de destino.
     * @return O retorno será padrão verdadeiro ou falso, dependendo do sucesso da operação.
     */

    virtual bool moverHistoriaProjetoParaSprint(const Codigo& codigoHistoria, const Codigo& codigoSprint) = 0;

    /**
     * @brief Altera o estado de uma história de usuário.
     * @param Codigo é a chave utilizada para identificar a história.
     * @param Estado representa o novo estado da história.
     * @return O retorno será padrão verdadeiro ou falso, dependendo do sucesso da alteração.
     */

    virtual bool alterarEstadoHistoria(const Codigo&, const Estado&) = 0;
};

#endif
