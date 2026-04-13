#ifndef DOMINIOS_HPP_INCLUDED
#define DOMINIOS_HPP_INCLUDED

#include <string>

class Dominio{
    private:
        std::string valor;
        virtual bool validar(const std::string&) = 0;
    public:
        void setValor(const std::string&);
        std::string getValor() const;
};

inline std::string Dominio::getValor() const {
    return valor;
}

class Codigo : public Dominio {
    private:
        static const int TAMANHO = 5;
        bool validar(const std::string&);
};

class Estado : public Dominio{
   private:
        static const std::string estado1;
        static const std::string estado2;
        static const std::string estado3;
        bool validar(const std::string&);
   public:
       Estado();
};

inline const std::string Estado::estado1 = "A FAZER";
inline const std::string Estado::estado2 = "FAZENDO";
inline const std::string Estado::estado3 = "FEITO";

inline Estado::Estado(){
     // this->valor= "A FAZER";
}

inline bool Estado::validar(const std::string& strEstado){

      if(strEstado == estado1 || strEstado == estado2 || strEstado == estado3){
            return true;
      }
      else return false;
}

class Nome : public Dominio{
    private:
        static const int TAM_MAXIMO= 10;
        bool validar(const std::string&);
        bool ehValido(const std::string&);
        bool temEspacoInvalido(const std::string&);

};

class Prioridade : public Dominio {
    private:
       bool validar(const std::string&);
};

class Senha : public Dominio {
    private:
        static const int TAM_MAXIMO = 6;
        bool validar(const std::string&);
};

class Texto : public Dominio{
    private:
        static const int TAM_MAXIMO = 40;
        bool validar(const std::string& );
        bool ehValido(const std::string& );
        bool temFormatacaoValida(const std::string& );
        bool temEspacoinvalida(const std::string& );
};

class Tempo : public Dominio{
    private:
        static const int TAM_MAXIMO = 365;
        static const int TAM_MINIMO = 1;
        bool validar(const std::string&);
};
/*
Falta DATA,  PAPEL e EMAIL
*/

#endif
