/**
 * @file planoDeSprint.hpp
 * @author Fábio Willian Alves Silva
 * @brief Definição da classe entidade HistoriaDeUsuario.
 */


#ifndef PLANODESPRINT
#define PLANODESPRINT
#include "Dominios/dominios.hpp"


using namespace std;

/**
 * @class PlanoDeSprint
 * @brief Entidade que representa planos de sprint no sistema.
 *
 * @details A entidade planoDeSprint representa uma classe capaz de agrupar 
 * informações sobre pĺanos de sprints elaborados pelo usuario a fim 
 * de facilitar a organização de projetos.
 * A classe é composta por objetos de domínio, e estes são os responsáveis 
 * por garantir que todas as regras básicas de contrução de um plano
 * de sprint, são eles:
 * 
 *  - Codigo
 *  - Texto
 *  - Tempo
 * 
 * * @note **Decisão de Arquitetura e Performance:** Todos os métodos de acesso (getters) 
 * e modificadores (setters) desta classe utilizam passagem e retorno por referência 
 * constante (`const Tipo&`). Isso garante alta performance ao evitar chamadas 
 * aos construtores de cópia dos domínios, além de preservar rigorosamente o 
 * encapsulamento da entidade.
 */

class PlanoDeSprint {
    private:
        Codigo codigo;
        Texto objetivo;
        Tempo capacidade;
    public:
        /**
         * @brief Atribui um novo objetivo ao Plano de Sprint.
         * @param objetivo Referência constante para o objeto de domínio Texto.
         */
        void setTexto(const Texto &objetivo);
         /**
         * @brief Recupera o objetivo do Plano de Sprint.
         * @return const Codigo& Referência constante para o objetivo armazenado.
         */
        const Texto &getTexto() const;
        /**
         * @brief Atribui uma nova capacidade ao Plano de Sprint.
         * @param capacidade Referência constante para o objeto de domínio Tempo.
         */
        void setTempo(const Tempo &capacidade);
         /**
         * @brief Recupera a capacidade do Plano de Sprint.
         * @return const Codigo& Referência constante para a capacidade armazenado.
         */
        const Tempo &getTempo() const;
        /**
         * @brief Atribui um novo código ao Plano de Sprint.
         * @param codigo Referência constante para o objeto de domínio Codigo.
         */
        void setCodigo(const Codigo& codigo);
         /**
         * @brief Recupera o código atual do Plano de Sprint.
         * @return const Codigo& Referência constante para o código armazenado.
         */  
        const Codigo& getCodigo() const;
};

inline void PlanoDeSprint::setTexto(const Texto &objetivo) {
    this->objetivo = objetivo;
}

inline const Texto& PlanoDeSprint::getTexto() const {
    return objetivo;
}

inline void PlanoDeSprint::setTempo(const Tempo &capacidade) {
    this->capacidade = capacidade;
}

inline const Tempo& PlanoDeSprint::getTempo() const {
    return capacidade;
}

inline void PlanoDeSprint::setCodigo(const Codigo& codigo) {
    this->codigo = codigo;
}


#endif