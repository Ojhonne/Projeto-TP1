#ifndef SENHA_HPP
#define SENHA_HPP

#include <string>

using namespace std;

class Senha {
    private:
        static const int tam_maximo = 6;
        string senha;
        bool validaSenha(string);
    public:
        bool setSenha(string);
        string getSenha();
};

inline string Senha::getSenha() {
    return senha;
}

#endif