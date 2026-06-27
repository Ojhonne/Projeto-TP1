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
#include "Controladoras/CrtlApresentacaoCadastro.hpp"

//serviço
#include "Controladoras/CrtlServicoAutenticacao.hpp"
#include "Containers/containerPessoa.hpp"

//stubs
#include "Stubs/stubPlanejamento.hpp"
#include "Stubs/stubCadastro.hpp"

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

    // Instanciando controladoras da camada de apresentação
    CrtlApresentacaoAcesso *crtlApresentacaoAcesso = new CrtlApresentacaoAcesso(); // menu principal
    IApresentacaoLogin *crtlApresentacaoLogin = new CrtlApresentacaoLogin();     // tela login
    IApresentacaoPlanejamento *crtlApresentacaoPlanejamento = new CrtlApresentacaoPlanejamento();
    IApresentacaoCadastro *crtlApresentacaoCadastro = new CrtlApresentacaoCadastro();

    // Instanciando controladoras da camada de serviço
    IServicoAutenticacao *servicoAutenticacao = new CrtlServicoAutenticacao();

    // Instanciando os STUBS com seus respectivos nomes reais (CORRIGIDO)
    IServicoPlanejamento *stubServicoPlanejamento = new StubServicoPlanejamento(); // Usando a classe existente!
    IServicoPessoa *stubCadastro = new StubCadastro();                             // Usando a classe existente!

    // Interligando apresentações e seus respectivos serviços/stubs
    crtlApresentacaoLogin->setCtrlServicoAutenticacao(servicoAutenticacao);
    crtlApresentacaoPlanejamento->setCtrlServicoPlanejamento(stubServicoPlanejamento);
    crtlApresentacaoCadastro->setCtrlServicoPessoa(stubCadastro);

    // Interligando os sub-módulos de apresentação ao Menu Principal (CORRIGIDO)
    crtlApresentacaoAcesso->setCtrlLogin(crtlApresentacaoLogin);
    crtlApresentacaoAcesso->setCtrlCadastro(crtlApresentacaoCadastro);
    crtlApresentacaoAcesso->setCtrlPlanejamento(crtlApresentacaoPlanejamento);

    // Executar o sistema
    try{
        crtlApresentacaoAcesso->executar();
    }
    catch(const runtime_error &exp){
        endwin(); // Garante o fechamento do ncurses antes de mostrar o erro no terminal comum
        cout << "Erro de sistema: " << exp.what() << endl;
    }

    // Limpeza de mémoria (CORRIGIDO: Descomentados e adicionados os stubs alocados)
    delete crtlApresentacaoAcesso;
    delete crtlApresentacaoLogin;
    delete crtlApresentacaoPlanejamento;
    delete crtlApresentacaoCadastro;

    delete servicoAutenticacao;
    delete stubServicoPlanejamento;
    delete stubCadastro;

    return 0;
}
