#ifndef PRIORIDADE_HPP
#define PRIORIDADE_HPP

#include <string>

class Prioridade {
    private:
       std::string prioridade;
       bool validaPrioridade(std::string);
    public:
        bool setPrioridade(std::string);
        std::string getPrioridade() const;
};

inline std::string Prioridade::getPrioridade() const{
    return prioridade;
}

#endif