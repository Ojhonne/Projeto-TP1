#ifndef CRTLAPRESENTACAOLOGIN_H_INCLUDED
#define CRTLAPRESENTACAOLOGIN_H_INCLUDED

#ifdef _WIN32
    #include <curses.h> 
#elif __linux__
    #include <ncurses.h>
#else
    #error "Sistema operacional nao suportado para esta biblioteca."
#endif

#include <string.h>
#include "Dominios/dominios.hpp"
#include "Interfaces/interfaces.hpp"


//------------------------------------------------------------------------
// Declaração de controladora e implementação de método.

class CntrApresentacaoLogin : public IApresentacaoLogin{
    private:
        IServicoAutenticacao *servicoAutenticacao;  // Referência para servidor.

    public:
        bool autenticar(const Email&);
        void setCtrlServicoAutenticacao(IServicoAutenticacao*);
};

inline void CntrApresentacaoLogin::setCtrlServicoAutenticacao(IServicoAutenticacao* servicoAutenticacao){
    this->servicoAutenticacao = servicoAutenticacao;
}

#endif // CRTLAPRESENTACAOLOGIN_H_INCLUDED