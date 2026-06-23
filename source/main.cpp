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
#include "Interfaces/interfaces.hpp"
#include "Controladoras/CrtlApresentacaoLogin.hpp"
#include "Controladoras/CrtlApresentacaoAcesso.hpp"
#include "Stubs/stubAutenticacao.hpp"
#include "Controladoras/CrtlApresentacaoPlanejamento.hpp"
#include "Stubs/stubPlanejamento.hpp"


using namespace std;

int main(void){

    // Instanciar controladoras da camada de apresentação.
    CrtlApresentacaoAcesso *crtlApresentacaoAcesso; // menu principal
    IApresentacaoLogin *crtlApresentacaoLogin; //istanciar usando a interface
    IApresentacaoPlanejamento *crtlApresentacaoPlanejamento; 

    crtlApresentacaoAcesso = new CrtlApresentacaoAcesso(); // criando o objeto dinamicamente
    crtlApresentacaoLogin = new CrtlApresentacaoLogin(); // criando o objeto e associando a controladora
    crtlApresentacaoPlanejamento = new CrtlApresentacaoPlanejamento();

    // Instanciar stubs de serviço.
    IServicoAutenticacao *stubServicoAutenticacao; // ponteiro para o stub
    stubServicoAutenticacao = new StubServicoAutenticacao(); // criando o objeto dinamicamente
    IServicoPlanejamento *stubServicoPlanejamento;
    stubServicoPlanejamento = new StubServicoPlanejamento();

    // Interligar controladoras e stubs.
    crtlApresentacaoAcesso->setCtrlLogin(crtlApresentacaoLogin); //

    crtlApresentacaoLogin->setCtrlServicoAutenticacao(stubServicoAutenticacao);

    crtlApresentacaoPlanejamento->setCtrlServicoPlanejamento(stubServicoPlanejamento);

    try{
        crtlApresentacaoAcesso->executar();
    }
    catch(const runtime_error &exp){
        cout << "Erro de sistema." << endl;
    }


    delete crtlApresentacaoAcesso;
    delete crtlApresentacaoLogin;
    delete crtlApresentacaoPlanejamento;
    return 0;
}

