#ifndef SENHA_HPP
#define SENHA_HPP

#include <string>
#include <stdexcept>

class Senha {
    private:
        static const int TAM_MAXIMO = 6;
        std::string senha;
        void validaSenha(std::string);
    public:
        void setSenha(std::string);
        std::string getSenha();
};

inline std::string Senha::getSenha() {
    return senha;
}

#endif