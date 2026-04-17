#pragma once

#include <string>

class Nome {

    private:
        static const int TAM_MAXIMO= 10;
        std::string nome;

        void validar(const std::string&);
        bool ehValido(const std::string&);
        bool temEspacoValido(const std::string&);
        
    public:
        void setNome(const std::string&);
       const std::string& getNome() const noexcept;
};
inline const std::string& Nome::getNome() const noexcept{
    return nome;
}