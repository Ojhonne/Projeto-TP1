#ifndef DATA_HPP_INCLUDED
#define DATA_HPP_INCLUDED

#include <string>

using namespace std;

class Data{
   private:
       int dia, mes, ano;
       static const int MIN_DIA = 1;
       static const int MAX_MES = 12;
       static const int  MIN_MES = 1;
       static const int MAX_ANO = 2099;
       static const int MIN_ANO = 2000;
       bool formatoValido(string str);
       void extrair(string str, int&, int&, int&);
       bool validarData(int, int, int);
       int getDiasMes(int, int);
       bool ehBissexto(int);//os metodos acima sao parametrizados pois nao sao valores que estoa associados a atributos da classe

   public:
       bool setDMA(string str);
       int getDia() const;
       int getMes() const;
       int getAno() const;
       string getData() const;
       bool vemAntes(const Data&) const;
       Data();
};

class Intervalo{
    private:
        Data dataInicio;
        Data dataTermino;
        bool dataInserida;

    public:
        bool setPeriodo(string strI, string strT);
        void imprimir()const;
        Intervalo();

};

inline int Data::getDia()const{
        return dia;
}
inline int Data::getMes()const{
        return mes;
}
inline int Data::getAno()const{
        return ano;
}

#endif // DATA_HPP_INCLUDED

