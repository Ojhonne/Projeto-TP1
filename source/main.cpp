#include <iostream>
#include <string>
#include <stdexcept>
#include "Dominios/texto.hpp" // Ajuste o caminho conforme a estrutura do seu projeto

using namespace std;

// Função auxiliar para evitar repetição de código no main
void testarCenario(const string& descricao, const string& valor, bool deveSerValido) {
    Texto t;
    try {
        t.setTexto(valor);
        
        // Se chegou aqui, não lançou exceção
        if (deveSerValido) {
            cout << "[SUCESSO] " << descricao << " - Valor aceito: '" << valor << "'\n";
        } else {
            cout << "[FALHA] " << descricao << " - Valor aceito indevidamente: '" << valor << "'\n";
        }
    } catch (invalid_argument& e) {
        // Se chegou aqui, a exceção foi lançada pelo seu setTexto
        if (!deveSerValido) {
            cout << "[SUCESSO] " << descricao << " - Bloqueado corretamente: '" << valor << "'\n";
        } else {
            cout << "[FALHA] " << descricao << " - Excecao lancada indevidamente: '" << valor << "'\n";
        }
    }
}

int main() {
    cout << "--- INICIANDO BATERIA DE TESTES DA CLASSE TEXTO ---\n\n";

    // 1. Testando o "Caminho Feliz" (Casos que DEVEM ser válidos)
    cout << ">> TESTANDO CASOS VALIDOS:\n";
    testarCenario("Texto simples e valido", "Ola Mundo 123", true);
    testarCenario("Texto com pontuacao correta", "UnB, departamento de CS. Top", true);
    testarCenario("Texto com exatos 40 chars", "1234567890123456789012345678901234567890", true);

    cout << "\n>> TESTANDO CASOS INVALIDOS (Regras de Negocio):\n";
    
    // 2. Testando Restrições de Tamanho
    testarCenario("Texto vazio", "", false);
    testarCenario("Maior que 40 caracteres", "Este texto e muito grande e com certeza tem mais de quarenta caracteres", false);
    
    // 3. Testando Caracteres Inválidos
    testarCenario("Presenca de caractere especial (@)", "Email falso@teste", false);
    testarCenario("Presenca de hifen (-)", "Texto-com-hifen", false);

    // 4. Testando Bordas (Primeiro e Último caractere)
    testarCenario("Comeca com espaco", " Espaco no inicio", false);
    testarCenario("Comeca com virgula", ",Comeca com virgula", false);
    testarCenario("Termina com ponto", "Termina com ponto.", false);

    // 5. Testando Regras de Formatação (Pontuação e Espaços)
    testarCenario("Virgula seguida de virgula", "Erro,, duplo", false);
    testarCenario("Ponto seguido de virgula", "Erro., misto", false);
    testarCenario("Ponto seguido de ponto", "Erro.. duplo", false);
    testarCenario("Espaco seguido de espaco", "Dois  espacos", false); // O 1º espaço será seguido por outro espaço (inválido)
    testarCenario("Espaco seguido de virgula", "Espaco , e virgula", false); // O espaço é seguido por vírgula (inválido)

    cout << "\n--- TESTES FINALIZADOS ---\n";
    return 0;
}