#ifndef TEMPO_HPP
#define TEMPO_HPP
#include <string>
class Tempo{

    private:
        std::string tempo; 
        bool validar(const std::string&);
        static const int TAM_MAXIMO = 365;
        static const int TAM_MINIMO = 1;
    public:
        void setTempo(const std::string&);
        std::string getTempo() const;

};
inline std::string Tempo::getTempo() const{
    return tempo;
}

#endif