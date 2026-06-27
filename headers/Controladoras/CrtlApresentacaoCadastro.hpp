#ifndef CRTLAPRESENTACOACADASTRO_H_INCLUDED
#define CRTLAPRESENTACOACADASTRO_H_INCLUDED

#include "Dominios/dominios.hpp"
#include "Interfaces/interfaces.hpp"

#ifdef _WIN32
    #include <curses.h>
#else
    #include <ncurses.h>
#endif

class CrtlApresentacaoCadastro : public IApresentacaoCadastro {
private:
    IServicoPessoa *servicoPessoa; // Ponteiro para a camada de serviço/stub [cite: 459]

    // Métodos auxiliares gráficos baseados no padrão visual do grupo
    WINDOW* criarJanelaCadastro();
    void desenharLayout(WINDOW* win, const char* titulo);
    bool capturarCampos(WINDOW* win, char* emailStr, char* senhaStr, char* nomeStr, char* papelStr);
    void exibirErro(WINDOW* win, const char* mensagem);
    void exibirSucesso(WINDOW* win, const char* mensagem);

    void cadastrarInexistente();
    void atualizarExistente(const Email& emailSessao);
    void excluirExistente(const Email& emailSessao);

public:
    virtual ~CrtlApresentacaoCadastro() = default;



    void executar(const Email&) override;

    void setCtrlServicoPessoa(IServicoPessoa*) override;
};

inline void CrtlApresentacaoCadastro::setCtrlServicoPessoa(IServicoPessoa* servicoPessoa) {
    this->servicoPessoa = servicoPessoa;
}

#endif // CRTLAPRESENTACOACADASTRO_H_INCLUDED
