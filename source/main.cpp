// Exemplo de controladora de interação com PDCurses.

#include <string.h>
#include <stdexcept>
#include <iostream>

// Incluir cabeçalho da biblioteca PDCurses.
#ifdef _WIN32
    #include <curses.h> 
#elif __linux__
    #include <ncurses.h>
#else
    #error "Sistema operacional nao suportado para esta biblioteca."
#endif

#include "Dominios/dominios.hpp"
#include "Entidades/pessoa.hpp"
#include "Interfaces/interfaces.hpp"

// Apresentação
#include "Controladoras/CrtlApresentacaoLogin.hpp"
#include "Controladoras/CrtlApresentacaoAcesso.hpp"
#include "Controladoras/CrtlApresentacaoPlanejamento.hpp"

//serviço
#include "Controladoras/CrtlServicoAutenticacao.hpp"
#include "Containers/containerPessoa.hpp"

//stubs
#include "Stubs/stubPlanejamento.hpp"

using namespace std;

int main(void){

    // Populando o banco de dados para o login
    try {
        Email emailTeste;  emailTeste.setValor("joao@teste.com");
        Nome nomeTeste;    nomeTeste.setValor("Joao");
        Senha senhaTeste;  senhaTeste.setValor("A1b2C3"); 
        Papel papelTeste;  papelTeste.setValor("DESENVOLVEDOR");

        Pessoa novaPessoa;
        novaPessoa.setEmail(emailTeste);
        novaPessoa.setNome(nomeTeste);
        novaPessoa.setSenha(senhaTeste);
        novaPessoa.setPapel(papelTeste);

        ContainerPessoa::getInstancia()->incluir(novaPessoa);
    } catch (...) {
        // Ignora erros de inserção
    }

    // intanciando controladoras da camada de apresentação
    CrtlApresentacaoAcesso *crtlApresentacaoAcesso; // menu principal
    IApresentacaoLogin *crtlApresentacaoLogin;  // tela login
    IApresentacaoPlanejamento *crtlApresentacaoPlanejamento;

    crtlApresentacaoAcesso = new CrtlApresentacaoAcesso(); 
    crtlApresentacaoLogin = new CrtlApresentacaoLogin(); 
    crtlApresentacaoPlanejamento = new CrtlApresentacaoPlanejamento;

    // Instanciando controladoras da camada de serviço
    IServicoAutenticacao *servicoAutenticacao; // ponteiro para o serviço real
    servicoAutenticacao = new CrtlServicoAutenticacao(); // controladora para sql
    
    // instanciando os stubs
    IServicoPlanejamento *stubServicoPlanejamento;
    stubServicoPlanejamento = new StubServicoPlanejamento();

    
    // interligando controladoras e servico.
    crtlApresentacaoAcesso->setCtrlLogin(crtlApresentacaoLogin); 
    crtlApresentacaoAcesso->setCtrlPlanejamento(crtlApresentacaoPlanejamento);
    
    crtlApresentacaoLogin->setCtrlServicoAutenticacao(servicoAutenticacao);

    crtlApresentacaoPlanejamento->setCtrlServicoPlanejamento(stubServicoPlanejamento);

    // Executar o sistema
    try{
        crtlApresentacaoAcesso->executar();
    }
    catch(const runtime_error &exp){
        cout << "Erro de sistema." << endl;
    }

    // Limpeza de mémoria
    delete crtlApresentacaoAcesso;
    delete crtlApresentacaoLogin;
    delete servicoAutenticacao; // Limpa o serviço real criado
    // delete crtlApresentacaoPlanejamento; 
    return 0;
}