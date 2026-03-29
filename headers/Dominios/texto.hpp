#ifndef TEXTO_HPP
#define TEXTO_HPP

#include <string>

class Texto{
    private:
        static const int TAM_MAXIMO = 40;
        std::string texto;
        bool ehValido(const std::string& );
    public:
        void setTexto(const std::string& );
        const std::string getTexto();
};
inline const std::string Texto::getTexto(){
    return texto;
}


#endif