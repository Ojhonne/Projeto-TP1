#include "Dominios/dominios.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <stdexcept>

using namespace std;

void Data::setValor(const string& str){
    setDMA(str);//o setDMA ja valida e lança exceçao
}

Data::Data(){
  this->dia = 1;
  this->mes = 01;
  this->ano = 2000;
}

void Data::setDMA(string str){
       validar(str);

       int d, m, a;
       extrair(str, d, m, a);

       //se validarData encontrar erro, o setDMA para e o programa busca o catch
       validarData(d, m, a);

       this->dia = d;
       this->mes = m;
       this->ano = a;

       Dominio::setValor(getData());//vamos passar a data individual ja validada pra atribuir a "valor"

}

void Data::validar(const string& str){

  int contAlgarismos = 0, contBarras = 0;

  for(int i = 0; i < str.size(); i++){
    if(isdigit(str[i])){
        contAlgarismos++;
    }
    else if(str[i] == '/'){
        contBarras++;
    }
    else{ //se for qualquer outra coisa além de algarismo ou /
        throw invalid_argument("Formato Invalido: inserçao de caracter nao valido!"); //return false;
    }
  }

  if(str.size() == 9){ //preciso disso pois se o usuario digitar uma senha extremamente curta, as posiçoes nem sequer vao existir
       if (!((contAlgarismos == 7 && contBarras == 2) && (str[1] == '/' && str[4] == '/'))) throw invalid_argument("Formato Invalido (D/MM/AAAA)");
  }
  else if(str.size() == 10){
       if(str[0]=='0') throw invalid_argument("Formato Invalido. Dia nao pode comçar com zero!"); //nao vamo aceitar input formato 01, 02, 03 pra dia
       if(!((contAlgarismos == 8 && contBarras == 2) && (str[2] == '/' && str[5] == '/'))) throw invalid_argument("Formato Invalido (D/MM/AAAA)");
  }

  else{
      throw invalid_argument("Formato Invalido: Tamanho incorreto.");
  }

}


void Data::extrair(string str, int&d, int&m, int&a){
    int pos1, pos2; //posicao das 2 barras

    pos1 = (str.find('/'));
    d = stoi(str.substr(0, pos1));
    pos2 = str.find('/', pos1 + 1);
    m = stoi(str.substr(pos1 + 1, pos2 - pos1 - 1));
    a = stoi(str.substr(pos2 + 1));//pq ano é 4 casas.
}


void Data::validarData(int d, int m, int a){ 
    if(m < MIN_MES){
        throw out_of_range("O mes esta ABAIXO do minimo estableecido!");
    }
    if(m > MAX_MES){
        throw out_of_range("O mes esta ACIMA do maximo estabelecido!");
    }
    if(a < MIN_ANO){
        throw out_of_range("O ano esta ABAIXO do minimo estabelecido!");
    }
    if(a > MAX_ANO){
        throw out_of_range("O ano esta ACIMA do maximo estabelecido!");
    }

    int gDm = getDiasMes(m, a);//ainda vou calcular se eh bissexto

    if (d > gDm || d < MIN_DIA){
        throw out_of_range("Dia incorreto para o mes e ano fornecidos");
    }
    //se chegou ao fim sem lançar nada, a data é valida por definiçao
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


bool Data::vemAntes(const Data &tempT) const{//primer const é pra assegurar nao mudança do meu objeto
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


void Intervalo::setPeriodo(string strI, string strT){
    Data tempI, tempT;

    tempI.setDMA(strI);
    tempT.setDMA(strT);


    if(tempI.vemAntes(tempT)){

        this->dataInicio = tempI;
        this->dataTermino = tempT;
        this->dataInserida = true;
    }

    else{
        throw invalid_argument("Data de inicio deve ser menor que data de termino!");
    }

}
