
/**
 * @file dominios.hpp
 * @brief Definição da classe base abstrata para os domínios do sistema.
 */
#ifndef DOMINIOS_HPP_INCLUDED
#define DOMINIOS_HPP_INCLUDED

#include <string>
#include <stdexcept>

/**
 * @class Dominio
 * @brief Classe base abstrata que padroniza o comportamento de classes de domínio.
 *
 * A classe Dominio gerencia o armazenamento de uma string e garante que
 * apenas valores válidos sejam atribuídos, delegando a regra de validação
 * para as classes derivadas (filhas) através de um método virtual puro.
 */

class Dominio{
    private:
        /**
        * @brief string que represanta o valor interno armazenado após validação.
         */
        std::string valor;
        /**
         * @brief Método virtual puro para validação das regras de cada Domínio.
         *
         * Este método dita o contrato de validação. Ele deve ser
         * obrigatoriamente implementado pelas classes filhas (como a classe Nome)
         * contendo as regras específicas de formatação e tamanho.
         *
         * @param valor A string que será submetida à validação.
         * @throw std::invalid_argument Se o valor não atender às regras da classe filha.
         */
        virtual void validar(const std::string&) = 0;
    public:
        /**
         * @brief Destrutor virtual.
         *
         * garante a destruição correta de objetos derivados quando deletados através
         * de um ponteiro da classe base.
         */
        virtual ~Dominio() = default;
        /**
         * @brief Define um novo valor para o domínio.
         *
         * Este método recebe uma string e aciona internamente o método validar()
         * implementado pela classe filha. O valor só será armazenado se a
         * validação for bem-sucedida.
         *
         * @param valor O novo valor a ser armazenado.
         * @throw std::invalid_argument Se a validação falhar.
         */
        virtual void setValor(const std::string&);
        /**
         * @brief Retorna o valor atualmente armazenado no domínio.
         *
         * @return std::string O valor validado.
         */
        std::string getValor() const;
         /**
         * @brief Construtor padrão.
         *
         * Cria um objeto Dominios vazio, com domínios esperando definição.
         */
        Dominio() = default;
};

inline std::string Dominio::getValor() const {
    return valor;
}

inline void Dominio::setValor(const std::string &valor){
    validar(valor);
    this->valor = valor;
}

/**
 * @class Codigo
 * @brief Representa um codigo identificador valido.
 *
 * A classe Codigo herda da classe abstrata Dominio e representa
 * um identificador de entidade no formato LLDDD, em que:
 *
 * - L representa uma letra maiuscula de A a Z.
 * - D representa um digito de 0 a 9.
 *
 * Regras de validacao:
 * - O codigo deve possuir exatamente 5 caracteres.
 * - Os dois primeiros caracteres devem ser letras maiusculas.
 * - Os tres ultimos caracteres devem ser digitos.
 */
class Codigo : public Dominio {
public:
    /**
     * @brief Constroi um objeto Codigo a partir de uma string.
     *
     * @param valor String contendo o codigo a ser validado.
     *
     * @throw std::invalid_argument Caso o valor informado nao obedeca
     * ao formato LLDDD.
     */
    Codigo(const std::string& valor);

private:
    static const int TAMANHO = 5;

    /**
     * @brief Valida o formato do codigo informado.
     *
     * @param valor String a ser validada.
     *
     * @throw std::invalid_argument Caso o valor informado seja invalido.
     */
    void validar(const std::string& valor);
};

inline Codigo::Codigo(const std::string& codigo){
    setValor(codigo);
}

/**
 * @class Email
 * @brief Representa o formato valido para um endereco de email.
 *
 * Um email eh composto por duas partes separadas pelo caractere '@'(parte-local@dominio) e
 * atua como identificador de uma entidade.
 *
 * Parte local:
 * - Pode conter letra (a-z), digito (0-9), ponto (.) ou hifen (-).
 * - Nao pode iniciar ou terminar com ponto ou hifen.
 * - Ponto ou hifen deve ser seguido por letra(s) ou digito(s).
 * - Comprimento maximo de 64 caracteres.
 *
 * Dominio:
 * - Composto por uma ou mais partes separadas por ponto (.).
 * - Cada parte pode conter letra (a-z), digito (0-9) ou hifen (-).
 * - Nao pode iniciar ou terminar com hifen.
 * - Comprimento maximo de 255 caracteres.
 *
 * Regras adicionais:
 * - Deve existir exatamente um caractere '@' separando as partes.
 * - Parte local e dominio nao podem ser vazios.
 */
class Email : public Dominio {
public:
    /**
     * @brief Constroi um objeto Email a partir de uma string.
     *
     * @param valor String contendo o email a ser validado.
     *
     * @throw std::invalid_argument Caso o email nao obedeça
     * as regras de formato especificadas.
     */
    Email(const std::string&);

private:
    static const int LIMITE_DOMINIO = 255;
    static const int LIMITE_PARTE = 64;

    /**
     * @brief Valida o formato geral do email.
     *
     * @throw std::invalid_argument em caso de formato invalido.
     */
    void validar(const std::string&);

    /**
     * @brief Verifica o uso correto de separadores ('@', '.', '-').
     *
     * @throw std::invalid_argument se os separadores estiverem em posicoes invalidas.
     */
    void verificaSeparadores(const std::string&);
};

inline Email::Email(const std::string& email){
    setValor(email);
}

/**
 * @class Estado
 * @brief Representa um estado válido de andamento de tarefa.
 *
 * A classe Estado herda as operações públicas da classe abstrata Dominio.
 * A classe Estado é responsável por garantir que o usuário defina um estado válido, que por sua vez, são eles: "A FAZER", "FAZENDO", "FEITO".
 *
 * OBSERVAÇÃO: O estado deve ser EXATAMENTE igual a uma das 3 alternativas, sem letras minúsculas!
 */
class Estado : public Dominio{
   private:
        static const std::string estado1;
        static const std::string estado2;
        static const std::string estado3;
        void validar(const std::string&);
   public:
        /**
         * @brief Construtor padrão.
         *
         * Inicializa o estado com estado1, que por sua vez é a string "A FAZER". \n
         * O valor só será validado quando setValor() for chamado.
         */
       Estado();
};

inline const std::string Estado::estado1 = "A FAZER";
inline const std::string Estado::estado2 = "FAZENDO";
inline const std::string Estado::estado3 = "FEITO";

inline Estado::Estado(){
     setValor(estado1);
}

inline void Estado::validar(const std::string& strEstado){
      if(strEstado != estado1 && strEstado != estado2 && strEstado != estado3){
            throw std::invalid_argument("Estado inserido nao eh valido");
      }
}


/**
 * @class Nome
 * @brief Representa o formato válido para armazenar um Nome.
 *
 * A classe domínio Nome herda as operações públicas da classe abstrata Dominio. \n
 * A classe Nome representa palavras que distinguem e identificam uma coisa própria com regras formais
 * de espaçamento e caracteres permitidos.
 *
 * Regras:
 *  - Tamanho de até 10 caracteres.
 *  - Não pode ser vazio.
 *  - Não pode começar ou terminar com espaço.
 *  - Espaço em branco é deve ser seguido por letra.
 *  - Cada termo deve iniciar com letra maiúscula ou minúscula.
 *  - Apenas letras e espaços são permitidos.
 */

class Nome : public Dominio{
    private:
        static const int TAM_MAXIMO{10};
        /**
         * @brief Valida o nome segundo as regras do domínio.
         *
         * @param valor Nome em formato string.
         * @throw std::invalid_argument ou std::Length_error Caso alguma regra seja violada.
         */
        void validar(const std::string&);
        /**
         * @brief Método auxiliar para verificar se a string é alfanumérica.
         * @param str A string a ser verificada.
         * @return true se todos os caracteres forem alfanuméricos, false caso contrário.
         */
        bool ehValido(const std::string&);
         /**
         * @brief Método auxiliar para validar as regras de espaçamento do nome.
         * @param str A string a ser verificada.
         * @return true se todos os caracteres estiverem no formato valído, false caso contrário.
         */
        bool temEspacoValido(const std::string&);
    public:
        /**
         * @brief Construtor padrão.
         *
         * Inicializa o nome com string "Sem nome". \n
         * O valor só será validado quando setValor() for chamado.
         */
        Nome();
};
inline Nome::Nome(){
    setValor("Sem nome");
}

/**
 * @class Papel
 * @brief Representa o formato válido para armazenar um papel do usuário.
 *
 * A classe domínio Papel herda as operações públicas da classe abstrata Dominio. \n
 * A classe Papel é responsavel por garantir que cada usuário possa receber um papel
 * que representará seu nível de acesso ao programa
 */

class Papel : public Dominio {
    private:
        /**
         * @brief Valida a string de acordo com as demandas da aplicação
         * A string passada deve ser um dos papéis existentes:
         *  - DESENVOLVEDOR;
         *  - MESTRE SCRUM;
         *  - PROPRIETARIO DE PRODUTO;
         *
         * @param papel É a string que será verificada
         *
         */
        void validar(const std::string&);
    public:
        /**
         * @brief Construtor padrão.
         *
         * Ao ser instaciada, um parametro deve ser passado para garantir a integridade do programa e evitar incompatibilidade de papel.
         *
         */
        Papel(std::string& valor);
};

inline Papel::Papel(std::string& valor) {
    setValor(valor);
}

/**
 * @class Prioridade
 * @brief Representa o formato válido para armazenar uma prioridade do usuário.
 *
 * A classe domínio Prioridade herda as operações públicas da classe abstrata Dominio. \n
 * A classe Prioridade e responsável por garantir que cada usuário receba uma prioridade ao acessar
 * o programa.
 */

class Prioridade : public Dominio {
    private:
         /**
         * @brief Valida a string de acordo com as demandas da aplicação
         * A string passada deve ser um dos papéis existentes:
         *  - ALTA;
         *  - MEDIA;
         *  - BAIXA;
         *
         * @param prioridade É a string que será verificada.
         *
         */
       void validar(const std::string&);
    public:
        /**
         * @brief Construtor padrão.
         *
         * Inicializa o nome com string "BAIXA".
         * Com o valor baixo, a segurança da aplicação é mantida e seu valor será mudado assim
         * que um usuario com maior prioridade acesse o programa.
         */
        Prioridade();
};

inline Prioridade::Prioridade() {
    setValor("BAIXA");
}

/**
 * @class Senha
 * @brief Representa o formato válido para armazenar uma senha.
 *
 * A senha deve ter exatamente 6 caracteres, eles podem ser:
 *  - Letras de A - Z podendo ser maiúsculas ou minúsculas;
 *  - Digitos de 0 - 9;
 *
 * Para uma senha ser considerada válida ele deve seguir as seguintes obrigatoriedades:
 *  - Letra não pode ser seguida por letra;
 *  - Dígito não pode ser seguido por dígito;
 *  - Existe pelo menos uma letra minúscula (a-z);
 *  - Uma letra maiúscula (A-Z);
 *  - Um dígito (0-9);
 *
 */

class Senha : public Dominio {
    private:
        static const int TAM_MAXIMO = 6;
        /**
         * @brief Valida ou não a senha de acordo com as obrigatoriedades.
         *
         * @param senha Senha em formato string.
         * @throw std::invalid_argument Caso alguma regra seja violada.
         */
        void validar(const std::string&);
    public:
    /**
         * @brief Construtor padrão.
         *
         * Ao ser instaciada, um parametro deve ser passado para garantir a integridade do programa e evitar incompatibilidade de senha.
         */
        Senha(std::string& valor);
};

inline Senha::Senha(std::string& valor) {
    setValor(valor);
}

/**
 * @class Tempo
 * @brief Representa o formato válido para armazenar um Tempo.
 *
 * A classe domínio Tempo herda as operações públicas da classe abstrata Dominio. \n
 * A classe Tempo representa um valor numérico que determina a duração dos eventos com regras formais de limties e caracteres permitidos.
 *
 * Regras:
 *  - O tamanho minimo é 1.
 *  - O tamanho maximo é 365.
 *  - Apenas números são permitidos.
 */

class Tempo : public Dominio{
    private:
        static const int TAM_MAXIMO{365};
        static const int TAM_MINIMO{1};
        void validar(const std::string&);
    public:
        Tempo();
};
inline Tempo::Tempo(){
    setValor("1");
}

/**
 * @class Texto
 * @brief Representa o formato válido para armazenar um Texto.
 *
 * A classe domínio Texto herda as operações públicas da classe abstrata Dominio. \n
 * A classe Texto representa palavras que formam uma maneira de transmitir uma mensagem com regras formais
 * de espaçamento e caracteres permitidos.
 *
 * Regras:
 *  - Tamanho de até 40 caracteres.
 *  - Não pode começar ou terminar com espaço em branco, virgula ou ponto.
 *  - Espaço em branco é deve ser seguido por letra ou digito.
 *  - Ponto não pode ser seguido por virgula ou ponto.
 *  - Virgula não pode ser seguido por virgula ou ponto.
 *  - Apenas letras, espaços, digitos, ponto e virgula são permitidos.
 */

class Texto : public Dominio{

    private:
        static const int TAM_MAXIMO{40};
        void validar(const std::string& );

        bool ehValido(const std::string& );
        bool temFormatacaoValida(const std::string& );
        bool temEspacoValido(const std::string& );
    public:
            /**
         * @brief Construtor padrão.
         *
         * Inicializa o nome com string "Sem Texto". \n
         * O valor só será validado quando setValor() for chamado.
         */
        Texto();
};
inline Texto::Texto(){
    setValor("Sem Texto");
}



/**
 * @class Data
 * @brief Representa uma data válida no formato D/MM/AAAA ou DD/MM/AAAA.
 *
 * @details A classe Data herda as operações da classe abstrata Dominio e gerencia
 * valores cronológicos compreendidos entre os anos de 2000 e 2099.
 * Ela encapsula regras de validação para dias, meses, anos (incluindo anos bissextos)
 * e impede formatos inconsistentes (como dias iniciados em zero '01/' e meses que nao estao no formato 'MM').
 */
class Data : public Dominio{
   private:
       int dia, mes, ano;
       static const int MIN_DIA = 1;
       static const int MAX_MES = 12;
       static const int  MIN_MES = 1;
       static const int MAX_ANO = 2099;
       static const int MIN_ANO = 2000;
       void validar(const std::string& str);
       void extrair(std::string str, int&, int&, int&);
       void validarData(int, int, int);
       int getDiasMes(int, int);
       bool ehBissexto(int);//os metodos acima sao parametrizados pois nao sao valores que estoa associados a atributos da classe

   public:

       /**
        * @brief Sobrescreve o método base para definir e validar a data a partir de uma string.
        * @param str String contendo a data a ser validada e armazenada.
        * @throw std::invalid_argument Se o formato ou a consistência da data forem inválidos.
        */
       void setValor(const std::string& str) override;//pq senao ia setar sem atualizar os inteiros componentes de data caso eu chamasse esse metodo antes de toda a etapa de validaçao

       /**
        * @brief Define individualmente os componentes inteiros de dia, mês e ano após validação.
        * @param str String contendo a data completa no formato string.
        * @throw std::invalid_argument ou std::out_of_range se a validação falhar.
        */
       void setDMA(std::string str);

       /** @brief Recupera o dia armazenado na data.
        * @return int O valor numérico do dia.
        */
       int getDia() const;

       /**
        * @brief Recupera o mês armazenado na data.
        * @return int O valor numérico do mês.
        */
       int getMes() const;

       /**
        * @brief Recupera o ano armazenado na data.
        * @return int O valor numérico do ano.
        */
       int getAno() const;

       /**
        * @brief Formata e retorna a data em formato textual padronizado.
        * @return std::string A data formatada como string (ex: "5/04/2026").
        */
       std::string getData() const;

       /**
        * @brief Verifica se a instância de termino tempT do domínio Data ocorre cronologicamente antes da data de inicio (tempI).
        * @param tempT Referência constante para o objeto temporario tempT do domínio Data e que será comparado com a data de inicio (tempI).
        * @return true se tempI for menor/anterior à tempT, false caso contrário.
        */
       bool vemAntes(const Data&) const;

       /**
        * @brief Construtor padrão.
        * * Inicializa a data de forma consistente com o valor padrão: 1/01/2000.
        */
       Data();
};

inline int Data::getDia()const{
        return dia;
}
inline int Data::getMes()const{
        return mes;
}
inline int Data::getAno()const{
        return ano;
}


/**
 * @class Intervalo
 * @brief Gerencia um período de tempo composto por uma data de início e uma de término.
 *
 * @details Esta classe é responsável por garantir a consistência cronológica de um intervalo,
 * impedindo que a data de início seja posterior à data de término.
 */
class Intervalo{
    private:
        Data dataInicio;
        Data dataTermino;
        bool dataInserida;

    public:

        /**
         * @brief Define e valida o período cronológico do intervalo, buscando primeiramente validar uma instancia de Data de inicio e termino individualmente.
         * @param strI String representando a data de início.
         * @param strT String representando a data de término.
         * @throw std::invalid_argument Se a data de início não for cronologicamente menor que a de término.
         */
        void setPeriodo(std::string strI, std::string strT);

        /**
         * @brief Imprime o intervalo na tela de forma amigável.
         * * Se o período não tiver sido configurado com sucesso previamente, emite um aviso de erro via cerr.
         */
        void imprimir()const;

        /**
         * @brief Construtor padrão.
         * * Inicializa o intervalo marcando o estado interno de inserção de dados como falso.
        */
        Intervalo();

};

#endif
