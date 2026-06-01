

#ifndef PROJETO_H_INCLUDED
#define PROJETO_H_INCLUDED
#include "Dominios/dominios.hpp"

/**
 * @class Projeto
 * @brief Classe que representa a entidade Projeto no sistema.
 *
 * @details A classe Projeto agrega os domínios de Código, Nome e as Datas de início e término,
 * centralizando as informações estruturais de um projeto da aplicação.
 *
 *
 *  Os dominios utilizados sao:
 *  - Codigo
 *  - Nome
 *  - Data (inicio e termino)
 *
 *
 * Cada atributo encapsula sua propria validacao, garantindo que a entidade
 * Projeto sempre esteja em um estado consistente.
 *
 * @note **Decisao de Arquitetura e Performance:** Todos os metodos de acesso
 * (getters) e modificadores (setters) utilizam passagem e retorno por
 * referencia constante (`const Tipo&`). Isso evita copias desnecessarias
 * dos objetos de dominio e melhora a performance, alem de manter o
 * encapsulamento da entidade.
 */

class Projeto{
   private:
       Codigo codigo;
       Nome nome;
       Data inicio;
       Data termino;
   public:
       /**
         * @brief Construtor padrão.
         *
         * Cria um objeto Projeto com seus atributos de domínio inicializados por seus respectivos construtores.
         */
       Projeto() = default;

        /**
         * @brief Define um objeto codigo para o projeto.
         * @param codigo Referencia constante para objeto de dominio Codigo.
        */
       void setCodigo(const Codigo& codigo);

       /**
        * @brief Recupera o objeto codigo do projeto.
        * @return const Codigo& Referencia constante para o objeto (codigo) armazenado do domínio Codigo.
       */
       const Codigo& getCodigo() const;

       /**
        * @brief Define um objeto nome ao projeto.
        * @param nome Referencia constante para o objeto de dominio Nome.
       */
       void setNome (const Nome& nome);

        /**
        * @brief Recupera o objeto nome do projeto.
        * @return const Nome& Referencia constante para o objeto (nome) armazenado do domínio Nome.
        */
       const Nome& getNome() const;

        /**
         * @brief Define um objeto de data de inicio para o projeto.
         * @param inicio Referencia constante para objeto de dominio Data.
        */
       void setInicio(const Data& inicio);

        /**
        * @brief Recupera o objeto que indica inicio do projeto.
        * @return const Data& Referencia constante para o objeto (inicio) armazenado do domínio Data.
       */
       const Data& getInicio()const;

        /**
         * @brief Define um objeto de data de termino para o projeto.
         * @param termino Referencia constante para objeto de dominio Data.
        */
       void setTermino(const Data& termino);

        /**
        * @brief Recupera o objeto que indica termino do projeto.
        * @return const Data& Referencia constante para o objeto (termino) armazenado do domínio Data.
       */
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
