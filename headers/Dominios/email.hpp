#ifndef EMAIL_HPP_INCLUDED
#define EMAIL_HPP_INCLUDED
#include <string>

class Email
{
    private:
        std::string entrada;
        static const int LIMITE_DOMINIO = 255;
        static const int LIMITE_PARTE = 64;
        void verifica(const std::string& entrada);
        void verificaSeparadores(const std::string& s);
    public:
        void set(const std::string& entrada);
        std::string get() const;

};

    inline std::string Email :: get() const
    {
        return entrada;
    }



#endif // EMAIL_HPP_INCLUDED
