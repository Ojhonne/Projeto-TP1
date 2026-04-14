#ifndef PAPEL_HPP
#define PAPEL_HPP

#include <string>

class Papel {
    private:
       std::string papel;
       bool validaPapel(std::string);
    public:
        bool setPapel(std::string);
        std::string getPapel() const;
};

inline std::string Papel::getPapel() const{
    return papel;
}

#endif