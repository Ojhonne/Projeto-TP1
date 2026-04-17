#ifndef TEMPO_HPP
#define TEMPO_HPP
#include <string>
class Tempo{

    private:
        std::string tempo; 
        void validar(const std::string&);
        static const int TAM_MAXIMO = 365;
        static const int TAM_MINIMO = 1;
    public:
        void setTempo(const std::string&);
        const std::string& getTempo() const noexcept;

};
inline const std::string& Tempo::getTempo() const noexcept{
    return tempo;
}
/*
Uma função inline será inserida no codigo ao ser chamada
const pois retorna um endereço de uma variavel e o seu valor não pode mudar
std::string& pois ela retorna um endereço de string
Tempo::getTempo() nome do método da classe Tempo
const pois esse método não pode alterar os valores dos atributos dessa classe
noexcept é um trato com o compilador que nesse metodo não terá tratamento de exceções e caso de um erro, pode interromper o programa

utilizar o retorno por referencia é uma forma de deixar o código mais rapído e com menor uso de memoria
pois não precisará fazer uma copia do dado e vai usar ele mesmo, o custo é quase zero
é bom utilizar em objetos grandes como std::string pois evita alocações desnecessárias e ganha perfomance 

o noexcept é uma forma de deixar o programa mais rapído pois o compilador não precisa criar estrturas para caso o erro acontecer.
*/

#endif