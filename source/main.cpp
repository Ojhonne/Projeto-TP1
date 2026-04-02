#include <iostream>
#include <string>
#include <stdexcept>
#include "Dominios/tempo.hpp"

using namespace std;

int main() {

    int N;
    Tempo tempo;

    cin >> N;
    tempo.setTempo(N);

    cout << "deu certo!";

    tempo.getTempo();


    return 0;
}