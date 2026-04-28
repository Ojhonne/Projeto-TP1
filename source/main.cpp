#include "Dominios/dominios.hpp" // Certifique-se de que este header declara todas as classes e constantes (TAMANHO, TAM_MAXIMO, etc.)
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

// Função template (genérica) para rodar os testes de qualquer domínio
template <typename ClasseDominio>
void rodarTestes(const string& nomeDominio, const vector<string>& valoresValidos, const vector<string>& valoresInvalidos) {
    cout << "=== Testando " << nomeDominio << " ===" << endl;
    ClasseDominio dominio;

    // Testando valores que DEVEM passar
    for (const string& valor : valoresValidos) {
        try {
            // Assume que todas as classes herdam de 'Dominio' e usam 'setValor'
            dominio.setValor(valor);
            cout << "[SUCESSO] Valor valido aceito: '" << valor << "'" << endl;
        } catch (const exception& e) {
            cout << "[FALHA] Valor valido rejeitado incorretamente: '" << valor << "' - Erro: " << e.what() << endl;
        }
    }

    // Testando valores que DEVEM falhar
    for (const string& valor : valoresInvalidos) {
        try {
            dominio.setValor(valor);
            cout << "[FALHA] Valor invalido aceito incorretamente: '" << valor << "'" << endl;
        } catch (const exception& e) {
            cout << "[SUCESSO] Valor invalido rejeitado corretamente: '" << valor << "'" << endl;
        }
    }
    cout << endl;
}

int main() {
    cout << "Iniciando bateria de testes dos Dominios...\n\n";

    // 1. Testes para Codigo (Ex: Assume TAMANHO = 5)
    rodarTestes<Codigo>("Codigo",
        {"AB123", "XY987"}, // Válidos: 2 letras maiúsculas + 3 dígitos
        {"aB123", "AB12", "ABC12", "123AB"} // Inválidos
    );

    // 2. Testes para Nome (Ex: Assume TAM_MAXIMO = 10)
    rodarTestes<Nome>("Nome",
        {"Joao", "Ana Silva"}, // Válidos
        {"", " Joao", "Joao ", "Joao  Silva", "Joao123", "NomeMuitoGrande"} // Inválidos
    );

    // 3. Testes para Prioridade
    rodarTestes<Prioridade>("Prioridade",
        {"ALTA", "MEDIA", "BAIXA"}, // Válidos
        {"alta", "Alta", "URGENTE", ""} // Inválidos
    );

    // 4. Testes para Senha (Ex: Assume TAM_MAXIMO = 6)
    // ATENÇÃO: Verifique o aviso abaixo sobre um bug na sua classe Senha
    rodarTestes<Senha>("Senha",
        {"A1b2C3", "x9Y8z7"}, // Válidos: Letras e números intercalados, contém maiúscula e minúscula
        {"123456", "abcdef", "A1B2C3", "a1b2c3", "A112C3"} // Inválidos
    );

    // 5. Testes para Texto (Ex: Assume TAM_MAXIMO = 40)
    rodarTestes<Texto>("Texto",
        {"Oi, tudo bem.", "Um texto simples", "Texto com numero 1"}, // Válidos
        {" Texto", "Texto ", ",Texto", "Texto..", "Texto,, ", ""} // Inválidos
    );

    // 6. Testes para Tempo (Ex: Assume TAM_MINIMO = 1, TAM_MAXIMO = 365)
    rodarTestes<Tempo>("Tempo",
        {"1", "15", "365"}, // Válidos
        {"0", "366", "15abc", "-5", " ", ""} // Inválidos
    );
    //7.teste
    rodarTestes<Papel>("Papel",
        {"DESENVOLVEDOR", "MESTRE SCRUM", "PROPRIETARIO DE PRODUTO"}, // Válidos
        {"0", "366", "15abc", "-5", " ", ""} // Inválidos
    );
    cout << "Bateria de testes finalizada." << endl;
    return 0;
}
