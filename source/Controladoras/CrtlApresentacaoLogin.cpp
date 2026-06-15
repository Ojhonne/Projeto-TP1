#include "Controladoras/CrtlApresentacaoLogin.hpp"
#include <iostream>
#include <stdexcept>

bool CntrApresentacaoLogin::autenticar(Email& email) {
    char emailStr[80];
    char senhaStr[80];
    bool autenticado = false;

    initscr(); // Inicializa a tela
    clear();

    while (!autenticado) {
        try {
            printw("=== TELA DE LOGIN ===\n");
            
            printw("Digite seu Email: ");
            refresh(); // Atualiza a tela para exibir o texto
            getstr(emailStr); 
            
            printw("Digite sua Senha: ");
            refresh();
            getstr(senhaStr);

            // A especificação exige que os métodos set lancem exceção em caso de formato inválido
            email.setValor(emailStr); 
            Senha senha(senhaStr);

            // Se os formatos forem válidos, repassa para a camada de serviço
            autenticado = servicoAutenticacao->autenticarPessoa(email, senha);

            if (autenticado) {
                printw("\nLogin realizado com sucesso! Pressione qualquer tecla para continuar...");
                refresh();
                getch(); // Aguarda um input para não fechar a tela bruscamente
                break;
            } else {
                printw("\nCredenciais invalidas. Tente novamente.\n\n");
                refresh();
            }
        } 
        // Captura a exceção lançada pelas classes de domínio (Email ou Senha)
        catch (const std::invalid_argument& e) { 
            printw("\nErro de formato: %s\n", e.what());
            printw("Pressione qualquer tecla para tentar novamente...\n\n");
            refresh();
            getch();
            clear(); // Limpa a tela para a próxima tentativa
        }
    }

    endwin(); // Encerra o modo visual e devolve o controle ao terminal padrão
    return autenticado;
}