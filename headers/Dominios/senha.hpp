#ifndef SENHA_HPP
#define SENHA_HPP

#include <string>

class Senha {
    private:
        static const int TAM_MAXIMO = 6;
        std::string senha;
        bool validaSenha(std::string);
    public:
        bool setSenha(std::string);
        std::string getSenha();
};

inline std::string Senha::getSenha() {
    return senha;
}

#endif