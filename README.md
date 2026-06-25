#  Sistema de software embasado em elementos do Framework Scrum  — Técnicas de Programação 1

### Departamento de Ciência da Computação - Universidade de Brasília  
**Técnicas de Programação 1 (TP1) - CIC0197**  

### Docente  
**Fernando Antonio de Araujo Chacon de Albuquerque**

### Discentes  
- **João Francisco de Sousa Torres**
- **Eduardo Sankievicz Lima** 
- **Fábio Willian Alves Silva**
- **Igor Melo Nascimento Silva**

---

## 📌 Sobre o Projeto
📌 Sobre o Projeto
Este projeto implementa um Sistema de Software baseado em elementos do Framework Scrum em C++, seguindo os princípios de orientação a objetos, modularização e separação em camadas definidos na disciplina.

O sistema tem o propósito de prover suporte a projetos onde os requisitos funcionais são especificados por histórias de usuário (user stories) e a gestão ocorre por um processo embasado no Scrum. O sistema permite:

- Criação e autenticação de usuários (Pessoa) assumindo os papéis de: *Proprietario de Produto*, *Mestre Scrum* ou *Desenvolvedor*.

- Gerenciamento e estruturação de Projetos.

- Criação e acompanhamento de Planos de Sprint.

- Cadastro, leitura, edição e exclusão (CRUD) de Histórias de Usuário.

- Validações completas de formato e regras de negócio através das classes de domínio.

- Interação com o usuário através de uma interface baseada em terminal (TUI).

- Todas as entidades e domínios foram implementados com validações, seguindo os requisitos especificados.

---

## 🧱 Arquitetura do Sistema

O projeto foi estruturado seguindo o modelo de arquitetura em camadas, garantindo baixo acoplamento e alta coesão:

### 1. Domínios (Unidades Básicas)
Responsáveis por encapsular e validar as regras de formatação das unidades de informação do sistema: `Codigo`, `Data`, `Email`,  `Estado`, `Nome`, `Papel`, `Prioridade`, `Senha`,  `Tempo`, `Texto`.

---

### **2. Entidades**
Representam os objetos do domínio do problema e agregam os domínios básicos: 
`HistoriaDeUsuario`, `Pessoa`, `PlanoDeSprint`, `Projeto`.

---

### **3. Interfaces**
Definem os contratos de comunicação entre as camadas  (`interfaces.hpp`), permitindo o desacoplamento entre a apresentação e os serviços de negócio.

---

### **4. Repositórios**
Implementam armazenamento em memória com `std::map`.

---

### **5. Serviços (Regras de Negócio)**
Tratam validações mais complexas relacionadas a entidades e operações do sistema.

---

### **6. Camada de Apresentação (Menus)**
Responsável por gerenciar a navegação, interagir com o usuário via terminal (tui.cpp) e validar as entradas brutas antes de repassá-las às camadas inferiores. Inclui controladoras como:

- CrtlApresentacaoAcesso

- CrtlApresentacaoLogin

- CrtlApresentacaoPlanejamento
---

## 📄 Documentação
A documentação completa da modelagem e do código foi gerada utilizando **Doxygen**.

O formato HTML da documentação está disponível no diretório:

`docs/html/index.html`

Para visualizar, basta abrir este arquivo em qualquer navegador web. O repositório também inclui os diagramas de arquitetura originais na pasta `diagrama/`.

---

## ⚙️ Configuração de Ambiente e Dependências
Este sistema foi concebido com uma arquitetura multiplataforma, garantindo a sua compilação e execução fluidas tanto em ambientes baseados em Unix (Linux e macOS) como em sistemas Windows.

Para a renderização da Interface de Utilizador em Terminal (TUI) e manipulação avançada do ecrã, o projeto recorre às seguintes bibliotecas:

+ **ncurses**: Utilizada nativamente nos sistemas Linux e macOS.
+ **pdcurses**: Uma implementação compatível com a API do ncurses, destinada à compilação e funcionamento nativo em ambientes Windows.

### 🛠️ Processo de Instalação
Antes de compilar o projeto, certifique-se de que possui um compilador C++ (como o GCC/G++) e a ferramenta make instalados no seu sistema, juntamente com a biblioteca correspondente ao seu ambiente.

#### 🐧 Linux
A biblioteca ncurses encontra-se disponível nos repositórios oficiais da grande maioria das distribuições.

+ **Ubuntu / Debian / Pop!_OS**:

```Bash
sudo apt update
sudo apt install libncurses5-dev libncursesw5-dev
```

+ **Arch Linux**:

```Bash
sudo pacman -S ncurses
```

#### **🍏 macOS:**
Para utilizadores de macOS, o método mais simples é a instalação através do gestor de pacotes Homebrew:
```Bash
brew install ncurses
```

####  🪟 Windows (MinGW / MSYS2)
## ▶️ Como Executar
### Pelo Code Blocks:
1. Clone o repositório
2. Abra o projeto no **CodeBlocks**  
3. Certifique-se de que todos os arquivos `.h` e `.cpp` estão incluídos no projeto  
4. Compile usando *Build & Run*  
5. Navegue pelos menus do sistema via terminal

### Via Make File:
Com um Makefile próprio, a compilação é automatizada.
1. Clone o repositório e acesse a raiz do projeto no seu terminal.
2. Compile o código-fonte executando o comando:

```Bash
make 
```

Após a compilação bem-sucedida, execute o binário gerado:
```Bash
./scrum
```
ou para compilar e executar:

```Bash
make run
```

---

## 🏁 Status do Projeto
- ✔️ Classes de Domínio implementadas e validadas
- ✔️ Entidades estruturadas
- ✔️ Interfaces e contratos definidos
- ✔️ Controladoras de Apresentação em funcionamento
- ✔️ Interface de Terminal (TUI) integrada
- ✔️ Documentação Doxygen gerada (Doxyfile configurado)
-  Integração completa das camadas finalizada

---

## 📚 Observações Finais
Este trabalho foi desenvolvido com foco estrito na aplicação prática dos conceitos de Engenharia de Software e Programação Orientada a Objetos, incluindo:

* Encapsulamento e ocultação de informação.
* Validação rigorosa e tratamento de exceções (argumentos inválidos).
* Modularização e dependência por interfaces (Classes Abstratas).
* Documentação padronizada no código.





