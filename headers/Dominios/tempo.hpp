#ifndef TEMPO_HPP
#define TEMPO_HPP

class Tempo{

    private:
       string tempo; 
        bool validar(const string&);
        static const int TAM_MAXIMO = 365;
        static const int TAM_MINIMO = 1;
    public:
        void setTempo(const string&);
        int getTempo() const;

};
inline int Tempo::getTempo() const{
    return tempo;
}

#endif