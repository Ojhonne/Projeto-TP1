#ifndef DOMINIOS_HPP_INCLUDED
#define DOMINIOS_HPP_INCLUDED

using namespace std;

class Codigo {

    private:
        char codigo[6];
        static const int TAMANHO = 5;
        bool valida(const char s[]);

    public:
        bool setCodigo(const char* s);
        const char* getCodigo();
};

inline const char* Codigo::getCodigo()
{
    return codigo;
}


#endif
