#ifndef TEXTO_HPP
#define TEXTO_HPP

#include <string>

class Texto{

    private:
        static const int TAM_MAXIMO{40};
        std::string texto;

        void validar(const std::string& );
        bool ehValido(const std::string& );
        bool temFormatacaoValida(const std::string& );
        bool temEspacoValido(const std::string& );
        
    public:
        void setTexto(const std::string& );
        std::string getTexto() const;
};
inline  std::string Texto::getTexto() const {
    return texto;
}


#endif