#include <iostream>
#include <string>
#include <stdexcept>
#include "Dominios/tempo.hpp"
#include "Dominios/prioridade.hpp"

using namespace std;

int main() {

    int N;
    Tempo tempo;

    cin >> N;
    tempo.setTempo(N);

    cout << "deu certo!" << endl;

    tempo.getTempo();

    Prioridade p1;
    cout << "Teste de Prioridade" << endl;
    cout << "Digite a prioridade: ";
    string pr1;
    cin >> pr1;
    if(!p1.setPrioridade(pr1)) cout << "Prioridade invalida" << endl;
    else cout << "Prioridade armazenada!" << endl;

    cout << "Prioridade: ";
    cout << p1.getPrioridade() << endl;
    return 0;
}