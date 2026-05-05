#ifndef PROJETO_H_INCLUDED
#define PROJETO_H_INCLUDED
#include "Dominios/dominios.hpp"



class Projeto{
   private:
       Codigo codigo;
       Nome nome;
       Data inicio;
       Data termino;
   public:
       Projeto() = default;
       void setCodigo(const Codigo& codigo);
       const Codigo& getCodigo() const;
       void setNome (const Nome& nome);
       const Nome& getNome() const;
       void setInicio(const Data& inicio);
       const Data& getInicio()const;
       void setTermino(const Data& termino);
       const Data& getTermino()const;
};


inline void Projeto::setCodigo(const Codigo& codigo){
   this->codigo = codigo;
}

inline const Codigo& Projeto::getCodigo() const{
   return codigo;
}

inline void Projeto::setNome(const Nome& nome){
   this->nome = nome;
}

inline const Nome& Projeto::getNome()const{
   return nome;
}

inline void Projeto::setInicio(const Data& inicio){
   this->inicio = inicio;
}

inline const Data& Projeto::getInicio()const{
   return inicio;
}

inline void Projeto::setTermino(const Data& termino){
   this->termino = termino;
}

inline const Data& Projeto::getTermino()const{
   return termino;
}


#endif // PROJETO_H_INCLUDED
