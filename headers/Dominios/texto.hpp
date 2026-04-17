#ifndef TEXTO_HPP
#define TEXTO_HPP

#include <string>

class Texto{

    private:
        static const int TAM_MAXIMO = 40;
        std::string texto;

        void validar(const std::string& );
        bool ehValido(const std::string& );
        bool temFormatacaoValida(const std::string& );
        bool temEspacoinvalida(const std::string& );
        
    public:
        void setTexto(const std::string& );
        const std::string& getTexto() const noexcept;
};
inline const std::string& Texto::getTexto() const noexcept {
    return texto;
}


#endif