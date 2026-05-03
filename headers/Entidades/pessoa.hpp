#ifndef PESSOA_HPP
#define PESSOA_HPP

#include "Dominios/dominios.hpp"


class Pessoa{
    private:
        Email email;
        Nome nome;
        Senha senha;
        Papel papel;
    public:
        const Email& getEmail()const;
        void setEmail(const Email&);
        const Nome& getNome()const;
        void setNome(const Nome&);
        const Senha& getSenha()const;
        void setSenha(const Senha&);
        const Papel& getPapel()const;
        void setPapel(const Papel&);
};

inline const Email& Pessoa::getEmail() const{
    return email;
}

inline void Pessoa::setEmail(const Email& email){
    this->email = email;
}

inline const Senha& Pessoa::getSenha() const{
    return senha;
}

inline void Pessoa::setSenha(const Senha& senha)
{
    this->senha = senha;
}

inline const Nome& Pessoa::getNome() const{
    return nome;
}

inline void Pessoa::setNome(const Nome& nome){
    this->nome = nome;
}

inline const Papel& Pessoa::getPapel()const{
    return papel;
}

inline void Pessoa:: setPapel(const Papel& papel)
{
    this->papel = papel;
}

#endif