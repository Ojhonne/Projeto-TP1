#ifndef HISTORIADEUSUARIO_HPP
#define HISTORIADEUSUARIO_HPP
#include "Dominios/codigo.hpp"
#include "Dominios/texto.hpp"
#include "Dominios/tempo.hpp"
#include "Dominios/estado.hpp"
#include "Dominios/prioridade.hpp"

class HistoriaDeUsuario {
    private:
        Codigo codigo;
        Texto titulo, papel, acao, valor;
        Tempo estimativa;
        Prioridade prioridade;
        Estado estado;
    public:
        void setCodigo(const Codigo& codigo);
        const Codigo& getCodigo() const;
        void setTitulo(const Texto& titulo);  
        const Texto& getTitulo() const;
        void setPapel(const Texto& papel);
        const Texto& getPapel() const;        
        void setAcao(const Texto& acao);
        const Texto& getAcao() const;
        void setValor(const Texto& valor); 
        const Texto& getValor() const;
        void setEstimativa(const Tempo& estimativa);
        const Tempo& getEstimativa() const;
        void setPrioridade(const Prioridade& prioridade);
        const Prioridade& getPrioridade() const;
        void setEstado(const Estado& estado);
        const Estado& getEstado() const;    
};  
/*
Utilizei o como parametro dos setters o uso da referencia
dessa maneira não é criado copia alguma e é ultilizado a referencia daquele objeto
o uso const antes impede do metodo alterar o valor da referencia

Utilizei o const Tipo& nos getters pela mesma razao anterior
Retornar uma referência ao atributo original ao inves de retornar uma copia
o const impede de quem receber essa referencia, alterar o valor presente nela
isso mantem o encapsulamento.

Essa maneiras contribui com a perforamance do programa
devolver uma referência é tão rápido e leve quanto
devolver um número inteiro simples (um ponteiro)
*/

inline void HistoriaDeUsuario::setCodigo (const Codigo& codigo ){
    this->codigo = codigo;
}
inline const Codigo& HistoriaDeUsuario::getCodigo() const{
    return codigo;
}

inline void HistoriaDeUsuario::setTitulo(const Texto& titulo){
    this->titulo = titulo;
}
inline const Texto& HistoriaDeUsuario::getTitulo() const{
    return titulo;
}

inline void HistoriaDeUsuario::setPapel(const Texto& papel){
    this->papel = papel;
}
inline const Texto& HistoriaDeUsuario::getPapel() const{
    return papel;
}

inline void HistoriaDeUsuario::setAcao(const Texto& acao){
    this->acao = acao;
}
inline const Texto& HistoriaDeUsuario::getAcao() const {
        return acao;
}

inline void HistoriaDeUsuario::setValor(const Texto& valor){
    this->valor = valor;
}
inline const Texto& HistoriaDeUsuario::getValor() const{
    return valor;
}

inline void HistoriaDeUsuario::setEstimativa(const Tempo& estimativa){
    this->estimativa = estimativa;
}
inline  const Tempo& HistoriaDeUsuario::getEstimativa() const{
    return estimativa;
}

inline void HistoriaDeUsuario::setPrioridade(const Prioridade& prioridade){
    this->prioridade = prioridade;
}
inline const Prioridade& HistoriaDeUsuario::getPrioridade() const{
    return prioridade;
}

inline void HistoriaDeUsuario::setEstado(const Estado& estado){
    this->estado = estado;
}
inline const Estado& HistoriaDeUsuario::getEstado() const{
    return estado;
}



#endif