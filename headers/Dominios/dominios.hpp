#ifndef DOMINIOS_HPP_INCLUDED
#define DOMINIOS_HPP_INCLUDED

#include <string>

class Dominio{ //classe base Abstrata
    private:
        std::string valor;
        virtual void validar(const std::string&) = 0; // metodo que as classes filhas devem implementar
    public:
        virtual void setValor(const std::string&);
        std::string getValor() const;
};

inline std::string Dominio::getValor() const { //implementação do metodo get
    return valor;
}


class Codigo : public Dominio { // classe codigo
    private:
        static const int TAMANHO = 5;
        void validar(const std::string&);
};

class Email : public Dominio{
    private:
        static const int LIMITE_DOMINIO = 255;
        static const int LIMITE_PARTE = 64;
        void validar(const std::string& );
        void verificaSeparadores(const std::string& );
};

class Estado : public Dominio{
   private:
        static const std::string estado1;
        static const std::string estado2;
        static const std::string estado3;
        void validar(const std::string&);
   public:
       Estado();
        void setValor(const std::string&) override;
};

inline const std::string Estado::estado1 = "A FAZER";
inline const std::string Estado::estado2 = "FAZENDO";
inline const std::string Estado::estado3 = "FEITO";

inline Estado::Estado(){
     setValor(estado1);
}

inline void Estado::validar(const std::string& strEstado){
      if(strEstado != estado1 && strEstado != estado2 && strEstado != estado3){
            throw invalid_argument("Estado inserido nao eh valido");
      }
}

class Nome : public Dominio{
    private:
        static const int TAM_MAXIMO{10};
        void validar(const std::string&);
        bool ehValido(const std::string&);
        bool temEspacoValido(const std::string&);
};

class Papel : public Dominio {
    private:
        void validar(const std::string&);
};

class Prioridade : public Dominio {
    private:
       void validar(const std::string&);
};

class Senha : public Dominio {
    private:
        static const int TAM_MAXIMO = 6;
        void validar(const std::string&);
};

class Tempo : public Dominio{
    private:
        static const int TAM_MAXIMO{365};
        static const int TAM_MINIMO{1};
        void validar(const std::string&);
};
class Texto : public Dominio{

    private:
        static const int TAM_MAXIMO{40};
        void validar(const std::string& );

        bool ehValido(const std::string& );
        bool temFormatacaoValida(const std::string& );
        bool temEspacoValido(const std::string& );

};


/*
Falta DATA
*/

#endif