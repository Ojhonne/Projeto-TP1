#ifndef TEMPO_HPP
#define TEMPO_HPP

class Tempo{

    private:
        int tempo; 
        bool validar(const int &);

    public:
        void setTempo(const int &);
        int getTempo() const;

};
inline int Tempo::getTempo() const{
    return tempo;
}

#endif