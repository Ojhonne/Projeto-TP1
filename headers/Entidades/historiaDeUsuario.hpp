/**
 * @file historiaDeUsuario.hpp
 * @author João Francisco
 * @brief Definição da classe entidade HistoriaDeUsuario.
 */

#ifndef HISTORIADEUSUARIO_HPP
#define HISTORIADEUSUARIO_HPP
#include "Dominios/dominios.hpp"

/**
 * @class HistoriaDeUsuario
 * @brief Entidade que representa uma História de Usuário no sistema.
 *
 * @details Uma História de Usuário agrupa as informações de um requisito ágil, 
 * compondo-se de múltiplos objetos de domínio:  (Código, Título, Papel, Ação, 
 * Valor, Estimativa, Prioridade e Estado). \n
 * Cada atributo é reponsável por validar seu formato e regra. \n
 * Os dominios utilizados são:
 *  - Codigo
 *  - Texto
 *  - Tempo
 *  - Prioridade
 *  - Estado
 * * @note **Decisão de Arquitetura e Performance:** Todos os métodos de acesso (getters) 
 * e modificadores (setters) desta classe utilizam passagem e retorno por referência 
 * constante (`const Tipo&`). Isso garante alta performance ao evitar chamadas 
 * aos construtores de cópia dos domínios, além de preservar rigorosamente o 
 * encapsulamento da entidade.
 */
class HistoriaDeUsuario {
    private:
        Codigo codigo;
        Texto titulo, papel, acao, valor;
        Tempo estimativa;
        Prioridade prioridade;
        Estado estado;
    public:
        /**
         * @brief Atribui um novo código à história de usuário.
         * @param codigo Referência constante para o objeto de domínio Codigo.
         */
        void setCodigo(const Codigo& codigo);
         /**
         * @brief Recupera o código atual da história de usuário.
         * @return const Codigo& Referência constante para o código armazenado.
         */  
        const Codigo& getCodigo() const;
        /**
         * @brief Atribui um novo título.
         * @param titulo Referência constante para o objeto de domínio Texto.
         */
        void setTitulo(const Texto& titulo);  
        /**
         * @brief Recupera o título atual.
         * @return const Texto& Referência constante para o título armazenado.
         */
        const Texto& getTitulo() const;
        /**
         * @brief Define o papel de quem solicitou a história (ex: "como um DESENVOLVEDOR.").
         * @param papel Referência constante para o objeto de domínio Texto.
         */
        void setPapel(const Texto& papel);
        /**
         * @brief Recupera o papel definido.
         * @return const Texto& Referência constante para o papel armazenado.
         */
        const Texto& getPapel() const;        
        /**
         * @brief Define a ação desejada na história (ex: "...eu quero deletar usuários...").
         * @param acao Referência constante para o objeto de domínio Texto.
         */
        void setAcao(const Texto& acao);
        /**
         * @brief Recupera a ação desejada.
         * @return const Texto& Referência constante para a ação armazenada.
         */
        const Texto& getAcao() const;
        /**
         * @brief Define o valor ou benefício da história (ex: "...para manter o sistema seguro.").
         * @param valor Referência constante para o objeto de domínio Texto.
         */
        void setValor(const Texto& valor); 
        /**
         * @brief Recupera o valor ou benefício definido.
         * @return const Texto& Referência constante para o valor armazenado.
         */
        const Texto& getValor() const;
        /**
         * @brief Define a estimativa de tempo/esforço da história.
         * @param estimativa Referência constante para o objeto de domínio Tempo.
         */
        void setEstimativa(const Tempo& estimativa);
        /**
         * @brief Recupera a estimativa atual.
         * @return const Tempo& Referência constante para a estimativa armazenada.
         */
        const Tempo& getEstimativa() const;
        /**
         * @brief Define a prioridade de execução.
         * @param prioridade Referência constante para o objeto de domínio Prioridade.
         */
        void setPrioridade(const Prioridade& prioridade);
        /**
         * @brief Recupera a prioridade atual.
         * @return const Prioridade& Referência constante para a prioridade armazenada.
         */
        const Prioridade& getPrioridade() const;
        /**
         * @brief Define o estado atual da história (ex: A FAZER, FAZENDO, FEITO).
         * @param estado Referência constante para o objeto de domínio Estado.
         */
        void setEstado(const Estado& estado);
        /**
         * @brief Recupera o estado atual.
         * @return const Estado& Referência constante para o estado armazenado.
         */
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