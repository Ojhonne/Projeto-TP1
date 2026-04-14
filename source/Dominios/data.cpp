#include "Dominios/data.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cctype>

Data::Data(){
  this->dia = 1;
  this->mes = 01;
  this->ano = 2000;
}


bool Data::setDMA(string str){
       if(!formatoValido(str)){
         return false;
       }
       int d, m, a;
       extrair(str, d, m, a);

       if(validarData(d, m, a)){
          this->dia = d;
          this->mes = m;
          this->ano = a;
          return true;
       }
       return false;
}


bool Data::formatoValido(string str){

  int contAlgarismos = 0, contBarras = 0;

  for(int i = 0; i < str.size(); i++){
    if(isdigit(str[i])){
        contAlgarismos++;
    }
    else if(str[i] == '/'){
        contBarras++;
    }
    else{ //se for qualquer outra coisa al�m de algarismo ou /
        return false;
    }
  }

  if(str.size() == 9){ //preciso disso pois se o usuario digitar uma senha extremamente curta, as posi�oes nem sequer vao existir
       return ((contAlgarismos == 7 && contBarras == 2) && (str[1] == '/' && str[4] == '/'));
  }
  if(str.size() == 10){
       if(str[0]=='0') return false; //nao vamo aceitar input formato 01, 02, 03 pra dia
       return ((contAlgarismos == 8 && contBarras == 2) && (str[2] == '/' && str[5] == '/'));
  }

  return false;
}


void Data::extrair(string str, int&d, int&m, int&a){
    int pos1, pos2; //posicao das 2 barras

    pos1 = (str.find('/'));
    d = stoi(str.substr(0, pos1));
    pos2 = str.find('/', pos1 + 1);
    m = stoi(str.substr(pos1 + 1, pos2 - pos1 - 1));
    a = stoi(str.substr(pos2 + 1));//pq ano � 4 casas.
}


bool Data::validarData(int d, int m, int a){
    if (m < MIN_MES || m > MAX_MES || a < MIN_ANO || a > MAX_ANO) return false;
    int gDm = getDiasMes(m, a);//ainda vou calcular se eh bissexto
    if (d <= gDm && d >= MIN_DIA) return true;
    return false;
}


int Data::getDiasMes(int m, int a){
    switch(m){
        case 4:
        case 6:
        case 9:
        case 11:
            return 30; //nao usei break pois o retorno eh imediato
        case 2:
            if(ehBissexto(a)) return 29;
            else return 28;
        default:
            return 31;
    }
}


bool Data::ehBissexto(int a){
    if(a % 4 != 0 || (a % 100 == 0 && a % 400 != 0)) return false;
    return true;
}


bool Data::vemAntes(const Data &tempT) const{//primer const � pra assegurar nao mudan�a do meu objeto
    return ((this->ano * 10000 + this->mes * 100 + this->dia) < (tempT.ano * 10000 + tempT.mes * 100 + tempT.dia));
}

string Data::getData()const{
    stringstream sData; //pensei em fazer em substrings, mas tem ess fun�ao aqui que � tipo uma esteira

    sData << dia << '/';
    sData << setfill('0') << setw(2) << mes << '/'; //preenche com 0 se o mes nao vier com 2 casas
    sData << ano;

    return sData.str();
}


Intervalo::Intervalo(){
   this->dataInserida = false;
}

void Intervalo::imprimir()const{
    if(!dataInserida){
        cerr << "ERRO! Data(s) nao inserida" << endl;
    }
    else {
        cout << "Data de inicio: " << dataInicio.getData() << endl << "Data de t�rmino: " << dataTermino.getData() << endl;
    }
}


bool Intervalo::setPeriodo(string strI, string strT){

    Data tempI, tempT; //usei essas variaveis, pois no if abaixo se uma condi�ao for aceita e a outra nao, uma data vai ser setada definitivamente e nao queremos isso
    //e declarei elas aqui pois se fosse no hpp, toda vez que eu criasse um objeto Intervalo, ocupario o dobro do espa�o, esses objetos sao simplesmente pra trabalho e soh existem enquanto esse metodo rodar
     if (tempI.setDMA(strI) && tempT.setDMA(strT)){//if pra checar se as datas individuais estao blz
            if(tempI.vemAntes(tempT)){
                this->dataInicio = tempI;
                this->dataTermino = tempT;
                this->dataInserida = true;
                return true;
            }
            else{
                cerr << "Data de termino nao eh maior que data de In�cio!" << endl;
                return false;
            }
     }

     return false;
}
