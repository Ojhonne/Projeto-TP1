#ifndef ESTADO_H_INCLUDED
#define ESTADO_H_INCLUDED

#include <string>

using namespace std;

class Estado{
   private:
       string estado;
       static const string estado1;
       static const string estado2;
       static const string estado3;
        bool validarEstado(string)const;
   public:
       Estado();
       bool setEstado(string);
       string getEstado()const;
};

inline const string Estado::estado1 = "A FAZER";
inline const string Estado::estado2 = "FAZENDO";
inline const string Estado::estado3 = "FEITO";


inline Estado::Estado(){
       this->estado= "A FAZER";
}

inline bool Estado::validarEstado(string strEstado)const{

      if(strEstado == estado1 || strEstado == estado2 || strEstado == estado3){
            return true;
      }
      else return false;
}

inline bool Estado::setEstado(string strEstado){
      if(validarEstado(strEstado)){
           this->estado = strEstado;
           return true;
      }

      return false;
}

inline string Estado::getEstado()const{
     return estado;
}



#endif // ESTADO_H_INCLUDED
