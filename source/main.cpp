#include <iostream>
#include <stdexcept>
#include <string>

// Incluir cabeçalho da biblioteca PDCurses/ncurses.
#ifdef _WIN32
    #include <curses.h> 
#elif __linux__
    #include <ncurses.h>
#else
    #error "Sistema operacional nao suportado para esta biblioteca."
#endif

#include "Dominios/dominios.hpp"

// Entidades
#include "Entidades/pessoa.hpp"
#include "Interfaces/interfaces.hpp"
#include "Entidades/historiaDeUsuario.hpp"
#include "Entidades/projeto.hpp"
#include "Entidades/planoDeSprint.hpp"

// Apresentação
#include "Controladoras/CrtlApresentacaoLogin.hpp"
#include "Controladoras/CrtlApresentacaoAcesso.hpp"
#include "Controladoras/CrtlApresentacaoPlanejamento.hpp"
#include "Controladoras/CrtlApresentacaoBacklog.hpp" 

// Serviço
#include "Controladoras/CrtlServicoAutenticacao.hpp"
#include "Controladoras/CrtlServicoBacklog.hpp"
#include "Controladoras/CrtlServicoPlanejamento.hpp"

//Container
#include "Containers/containerPessoa.hpp"
#include "Containers/containerBacklog.hpp"
#include "Containers/containerPlanoSprint.hpp"
#include "Containers/containerProjeto.hpp"

// Stubs


using namespace std;

int main(void){

    // Populando o banco de dados 
    try {
        Email emailTeste;  emailTeste.setValor("joaof1@teste.com");
        Nome nomeTeste;    nomeTeste.setValor("Joao");
        Senha senhaTeste;  senhaTeste.setValor("A1b2C3"); 
        Papel papelTeste;  papelTeste.setValor("PROPRIETARIO DE PRODUTO"); 

        Pessoa novaPessoa;
        novaPessoa.setEmail(emailTeste);
        novaPessoa.setNome(nomeTeste);
        novaPessoa.setSenha(senhaTeste);
        novaPessoa.setPapel(papelTeste);

        ContainerPessoa::getInstancia()->criarPessoa(novaPessoa);

        Codigo codigo; codigo.setValor("AB123"); 
        Codigo codigoProjeto; codigoProjeto.setValor("AE333");
        
        Texto titulo; titulo.setValor("Minha Historia"); 
        Texto papel; papel.setValor("Como usuario"); 
        Texto acao; acao.setValor("Eu quero ver telas"); 
        Texto valor; valor.setValor("Para usar o sistema");
        Tempo estimativa; estimativa.setValor("7");
        Prioridade prioridade; prioridade.setValor("ALTA");
        Estado estado; estado.setValor("A FAZER");
        Email emailPessoa; emailPessoa.setValor("joao@teste.com");

        HistoriaDeUsuario historia;
        historia.setCodigo(codigo);
        historia.setCodigoProjeto(codigoProjeto);
        // historia.setCodigoSprint(codigoSprint); //  {OU} DO UML
        historia.setTitulo(titulo);
        historia.setPapel(papel);
        historia.setAcao(acao);
        historia.setValor(valor);
        historia.setEstimativa(estimativa);
        historia.setPrioridade(prioridade);
        historia.setEstado(estado);
        historia.setEmailPessoa(emailPessoa);

        ContainerBacklog::getInstancia()->criarHistoriaUsuario(historia);
        
    } catch (const invalid_argument& e) {
        cout << "[MAIN] Falha de validacao no Dominio: " << e.what() << endl;
    } catch (const exception& e) {
        cout << "[MAIN] Erro no banco ao popular dados: " << e.what() << endl;
    }

    // Instanciando controladoras da camada de apresentação
    CrtlApresentacaoAcesso *crtlApresentacaoAcesso = new CrtlApresentacaoAcesso(); 
    IApresentacaoLogin *crtlApresentacaoLogin = new CrtlApresentacaoLogin(); 
    IApresentacaoPlanejamento *crtlApresentacaoPlanejamento = new CrtlApresentacaoPlanejamento();
    IApresentacaoBacklog *crtlApresentacaoBacklog = new CrtlApresentacaoBacklog();

    // Instanciando controladoras da camada de serviço
    IServicoAutenticacao *servicoAutenticacao = new CrtlServicoAutenticacao(); 
    IServicoBacklog *servicoBacklog = new CrtlServicoBacklog();
    IServicoPlanejamento *servicoPlanejamento = new CrtlServicoPlanejamento();
    
    // Interligando controladora acesso nas outras
    crtlApresentacaoAcesso->setCtrlLogin(crtlApresentacaoLogin);
    crtlApresentacaoAcesso->setCtrlPlanejamento(crtlApresentacaoPlanejamento);
    crtlApresentacaoAcesso->setCtrlBacklog(crtlApresentacaoBacklog);
    
    // Interligando controladoras de apresentação e de servico
    crtlApresentacaoLogin->setCtrlServicoAutenticacao(servicoAutenticacao);
    crtlApresentacaoBacklog->setCtrlServicoBacklog(servicoBacklog);
    crtlApresentacaoPlanejamento->setCtrlServicoPlanejamento(servicoPlanejamento);

    // Executando o sistema
    try{
        crtlApresentacaoAcesso->executar();
    }
    catch(const runtime_error &exp){
        cout << "[MAIN] Erro no loop de apresentacao: " << exp.what() << endl;
    }
    // Limpeza de mémoria 
    delete crtlApresentacaoAcesso;
    delete crtlApresentacaoLogin;
    delete crtlApresentacaoPlanejamento; 
    delete crtlApresentacaoBacklog;
    
    delete servicoAutenticacao; 
    delete servicoBacklog;
    delete servicoPlanejamento;
    
    return 0;
}