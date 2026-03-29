#pragma once

#include <string>

class Nome {
    private:
        static const int TAM_MAXIMO= 10;
        std::string nome;
        bool validar(const std::string&);
        bool eValido(const std::string& );
        bool temEspacoInvalido(const std::string&);
    public:
        void setNome(const std::string&);
        std::string getNome() const;
};
inline std::string Nome::getNome() const {
    return nome;
}