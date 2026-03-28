#include <iostream>
#include <string>
#include "Dominios/nome.hpp" // Ajuste este caminho se necessario

using namespace std;

// Fun��o auxiliar para n�o repetirmos c�digo no main
void testarNome(const string& valor, const string& descricaoDoTeste) {
    Nome meuNome;
    cout << "Testando: '" << valor << "' (" << descricaoDoTeste << ")" << endl;

    try {
        // Tenta atribuir o valor. Se for inv�lido, a sua classe vai lan�ar um erro!
        meuNome.setNome(valor);

        // Se chegou nesta linha, significa que o setNome n�o lan�ou exce��o.
        cout << " -> SUCESSO! Nome armazenado: " << meuNome.getNome() << "\n" << endl;

    } catch (invalid_argument &excecao) {
        // Se o setNome lan�ar o erro, o c�digo pula direto para c�.
        cout << " -> REJEITADO! Excecao capturada: " << excecao.what() << "\n" << endl;
    }
}

int main() {
    cout << "=========================================" << endl;
    cout << "   BATERIA DE TESTES - CLASSE NOME       " << endl;
    cout << "=========================================\n" << endl;
    //string nome;
    //getline(cin, nome);
    //testarNome(nome, "teste");
    
    // 1. Testando casos que DEVEM DAR CERTO (V�lidos)
    cout << "--- TESTES VALIDOS ---" << endl;
    testarNome("Ana", "Nome simples");
    testarNome("Joao Silva", "Nome com um espaco e 10 caracteres");
    testarNome("A B C D", "Caracteres isolados por espaco");

    // 2. Testando casos que DEVEM DAR ERRO (Inv�lidos)
    cout << "--- TESTES INVALIDOS ---" << endl;
    testarNome("", "String vazia");
    testarNome("NomeEnorme1", "Mais de 10 caracteres");
    testarNome(" Ana", "Comecando com espaco");
    testarNome("Ana ", "Terminando com espaco");
    testarNome("A  B", "Dois espacos seguidos");
    testarNome("Ana123", "Contem numeros");
    testarNome("Ana@Clara", "Contem caracteres especiais");

    cout << "=========================================" << endl;
    cout << "             FIM DOS TESTES              " << endl;
    cout << "=========================================" << endl;
    
    return 0;
}
