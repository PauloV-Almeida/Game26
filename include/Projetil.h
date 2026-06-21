#pragma once

#include "Entidades.h"

namespace Entidades
{
    namespace Personagens
    {
        class Jogador;
        class Thor;
    }

    class Estrutura;

    class Projetil : public Entidade
    {
    private:
        int dano;
        int veloProjetil;

        bool lancado;

        sf::Vector2f posicaoAlvo;
        Personagens::Thor* pThor;

        sf::Clock relogioLancamento;
        float tempoSemColisao;

    public:
        Projetil();
        Projetil(sf::Vector2f pos);
        virtual ~Projetil();

        int getDano() const;
        bool foiLancado() const;
        sf::Vector2f getPosicaoAlvo() const;

        bool podeColidir() const;

        void setThor(Personagens::Thor* thor);
        Personagens::Thor* getThor() const;

        void setDano(int danoBase);
        void setVelocidadeInicial(int velocidade);

        void lancar(sf::Vector2f origem, sf::Vector2f alvo, int aumentoVelo);
        void setLancado(bool estado);
        void setPosicaoAlvo(sf::Vector2f alvo);


        void colidir(Personagens::Jogador* jogador);
        void colidir(Estrutura* estrutura);

        void executar();

        void salvarDataBuffer();
        std::string salvar();
    };
}