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

#include "Dominios\dominios.hpp"
#include "Interfaces\interfaces.hpp"
#include "Controladoras\CrtlApresentacaoLogin.hpp"
#include "Stubs\stubs.hpp"


using namespace std;

int main()
{
    IApresentacaoLogin *cntr;
    IServicoAutenticacao *stub;

    Email email("joaof@gmail.com");


    bool resultado;

    cntr = new CntrApresentacaoLogin();                                      // Instanciar controladora.
    stub = new StubServicoAutenticacao();                                           // Instanciar stub.

    cntr->setCtrlServicoAutenticacao(stub);                                         // Inteligar controladora e stub.

    initscr();                                                                      // Iniciar curses.

    resultado = cntr->autenticar(email);                                             // Solicitar serviço de autenticacao.

    endwin();                                                                       // Finalizar curses.

    // Apresentar resultado do processo de autenticação.

    if(resultado)
        cout << "Sucesso na autenticacao";
    else
        cout << "Falha na autenticacao";

    return 0;
}

