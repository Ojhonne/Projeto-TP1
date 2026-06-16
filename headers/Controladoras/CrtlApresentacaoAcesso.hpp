#ifndef CRTLAPRESENTACAOACESSO_HPP_INCLUDED
#define CRTLAPRESENTACAOACESSO_HPP_INCLUDED

class IApresentacaoLogin;
class IApresentacaoCadastro;
class IApresentacaoPlanejamento;
class IApresentacaoBacklog;

class CrtlApresentacaoAcesso {
    private:
        IApresentacaoLogin* crtlApresentacaoLogin;
        IApresentacaoCadastro* crtlApresentacaoCadastro; 
        IApresentacaoPlanejamento* crtlApresentacaoPlanejamento;
        IApresentacaoBacklog* crtlApresentacaoBacklog;

    public:
        /**
         * @brief Destrutor virtual padrão.
        */
        virtual ~CrtlApresentacaoAcesso() = default;
        /**
         * @brief 
         */
        void executar(); 
};

#endif // CRTLAPRESENTACAOACESSO_HPP_INCLUDED