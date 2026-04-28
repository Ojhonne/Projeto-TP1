#ifndef PLANODESPRINT
#define PLANODESPRINT
#include "Dominios/texto.hpp"
#include "Dominios/tempo.hpp"

using namespace std;

class PlanoDeSprint {
    private:
        Texto objetivo;
        Tempo capacidade;
    public:
        void setTexto(const Texto &objetivo);
        const Texto &getTexto() const;
        void setTempo(const Tempo &capacidade);
        const Tempo &getTempo() const;
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


#endif