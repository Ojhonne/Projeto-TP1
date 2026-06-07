#include "Dominios/dominios.hpp" // Certifique-se de que o caminho está correto
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

// Função que roda os testes recebendo a referência da classe base polimórfica 'Dominio'
void rodarTestes(Dominio& dominio, const string& nomeDominio, const vector<string>& valoresValidos, const vector<string>& valoresInvalidos) {
    cout << "=== Testando " << nomeDominio << " ===" << endl;

    // Testando valores que DEVEM passar
    for (const string& valor : valoresValidos) {
        try {
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
    cout << "Iniciando bateria de testes dos Dominios baseada no arquivo .hpp...\n\n";

    // 1. Código (LLDDD)
    try {
        Codigo codigo("AA123"); // Instancia com um valor inicial válido
        rodarTestes(codigo, "Codigo",
            {"AB123", "ZZ999", "AA000"}, 
            {"aB123", "AB12", "ABC12", "123AB", "AB1234", "A1234"}
        );
    } catch (const exception& e) {
        cout << "Erro crítico ao inicializar Codigo: " << e.what() << endl;
    }

    // 2. Data (D/MM/AAAA ou DD/MM/AAAA - conforme hpp/imagem)
    try {
        Data data; // Possui construtor padrão (1/01/2000)
        rodarTestes(data, "Data",
            {"1/01/2000", "29/02/2024", "31/12/2099", "28/02/2023"}, // 2024 é bissexto
            {"01/01/2000", "29/02/2023", "32/01/2020", "15/13/2020", "10/10/1999", "1/1/2020", "10-10-2020", "31/04/2024"}
        );
    } catch (const exception& e) {
        cout << "Erro crítico ao inicializar Data: " << e.what() << endl;
    }

    // 3. Email
    try {
        Email email("teste@dominio.com");
        rodarTestes(email, "Email",
            {"parte.local@dominio.com", "a1-b2.c3@gmail.com", "u@d.org"},
            {".abc@dom.com", "abc.@dom.com", "-abc@dom.com", "abc-@dom.com", "ab..c@dom.com", "abc.-d@dom.com", "abc@dom-.com", "abc@-dom.com", "abc@dom..com", "abc@dominio", "abc", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa@dom.com"}
        );
    } catch (const exception& e) {
        cout << "Erro crítico ao inicializar Email: " << e.what() << endl;
    }

    // 4. Estado (A FAZER, FAZENDO, FEITO)
    try {
        Estado estado; // Possui construtor padrão
        rodarTestes(estado, "Estado",
            {"A FAZER", "FAZENDO", "FEITO"},
            {"a fazer", "Fazendo", "FEITO ", " A FAZER", "CANCELADO", ""}
        );
    } catch (const exception& e) {
        cout << "Erro crítico ao inicializar Estado: " << e.what() << endl;
    }

    // 5. Nome (Até 10 caracteres, sem espaços extremistas ou seguidos)
    try {
        Nome nome("Ana");
        rodarTestes(nome, "Nome",
            {"Joao", "Ana Silva", "A B C D E"},
            {"", " Joao", "Joao ", "Ana  Silva", "Joao123", "NomeGrandao"}
        );
    } catch (const exception& e) {
        cout << "Erro crítico ao inicializar Nome: " << e.what() << endl;
    }

    // 6. Papel (Contorna a referência modificável string& do seu construtor)
    try {
        string dummyPapel = "DESENVOLVEDOR";
        Papel papel(dummyPapel); 
        rodarTestes(papel, "Papel",
            {"DESENVOLVEDOR", "MESTRE SCRUM", "PROPRIETARIO DE PRODUTO"},
            {"desenvolvedor", "MESTRE  SCRUM", "SCRUM MASTER", "GERENTE", ""}
        );
    } catch (const exception& e) {
        cout << "Erro crítico ao inicializar Papel: " << e.what() << endl;
    }

    // 7. Prioridade (ALTA, MEDIA, BAIXA)
    try {
        Prioridade prioridade; // Possui construtor padrão
        rodarTestes(prioridade, "Prioridade",
            {"ALTA", "MEDIA", "BAIXA"},
            {"alta", "MÉDIA", "BAIXA ", "URGENTE", ""}
        );
    } catch (const exception& e) {
        cout << "Erro crítico ao inicializar Prioridade: " << e.what() << endl;
    }

    // 8. Senha (6 caracteres intercalados L-D-L-D. Contorna a referência string&)
    try {
        string dummySenha = "a1B2c3";
        Senha senha(dummySenha);
        rodarTestes(senha, "Senha",
            {"a1B2c3", "1A2b3C", "X9y8Z7"},
            {"123456", "abcdef", "A1B2C3", "a1b2c3", "aB1234", "a1B2c34", "a1B2c"}
        );
    } catch (const exception& e) {
        cout << "Erro crítico ao inicializar Senha: " << e.what() << endl;
    }

    // 9. Tempo (1 a 365)
    try {
        Tempo tempo("1");
        rodarTestes(tempo, "Tempo",
            {"1", "15", "365", "100"},
            {"0", "366", "-1", "abc", " 10", ""}
        );
    } catch (const exception& e) {
        cout << "Erro crítico ao inicializar Tempo: " << e.what() << endl;
    }

    // 10. Texto (Até 400 chars na imagem / alterado para refletir limites e pontuação)
    try {
        Texto texto("Texto valido");
        rodarTestes(texto, "Texto",
            {"Oi, tudo bem", "Um texto simples", "Texto com numero 1", "A, b. C"}, // Válidos (terminam em letra/dígito)
            {" Texto", "Texto ", ",Texto", "Texto.", "Texto..", "Texto,,", "Oi,  tudo", "Texto muito grande que ultrapassa o limite de quarenta caracteres."} // Inválidos (iniciam/terminam com pontuação/espaço ou duplicados)
        );
    } catch (const exception& e) {
        cout << "Erro crítico ao inicializar Texto: " << e.what() << endl;
    }

    cout << "Bateria de testes finalizada." << endl;
    return 0;
}