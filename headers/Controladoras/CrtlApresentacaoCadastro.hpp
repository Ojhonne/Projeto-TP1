#ifndef CRTL_APRESENTACAO_CADASTRO_HPP
#define CRTL_APRESENTACAO_CADASTRO_HPP

#ifdef _WIN32
    #include <curses.h>
#elif __linux__
    #include <ncurses.h>
#endif

#include "Interfaces/interfaces.hpp"
#include "Dominios/dominios.hpp"

class CrtlApresentacaoCadastro : public IApresentacaoCadastro {
private:
    IServicoPessoa* servicoPessoa;
    bool contaFoiExcluida; 

    WINDOW* criarJanelaCadastro();
    void desenharLayout(WINDOW* win, const char* titulo);
    bool capturarCampos(WINDOW* win, char* emailStr, char* senhaStr, char* nomeStr, char* papelStr);
    void exibirErro(WINDOW* win, const char* mensaje);
    void exibirSucesso(WINDOW* win, const char* mensaje);
    void desenharCabecalho(WINDOW* win, const Email& emailSessao);

    void cadastrarInexistente();
    void atualizarExistente(const Email& emailSessao);
    bool excluirExistente(const Email& emailSessao);

public:
    CrtlApresentacaoCadastro() : servicoPessoa(nullptr), contaFoiExcluida(false) {}

    void executar(const Email& emailSessao) override;

    bool getContaFoiExcluida() const { return contaFoiExcluida; }

    void setCtrlServicoPessoa(IServicoPessoa* servico) override {
        this->servicoPessoa = servico;
    }
};

#endif
