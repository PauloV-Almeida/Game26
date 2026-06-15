#pragma once

#include "Entidades.h"

namespace Entidades
{
    namespace Personagens
    {
        class Jogador;
    }

    class Estrutura;

    class Projetil : public Entidade
    {
    private:
        int dano;
        float velocidadeInicial;

        sf::Vector2f posicaoAlvo;
        bool lancado;

    public:
        Projetil();
        Projetil(sf::Vector2f posInicial, sf::Vector2f alvo);
        Projetil(sf::Vector2f posInicial, sf::Vector2f alvo, float velocidade, int danoBase);
        virtual ~Projetil();

        int getDano() const;
        bool foiLancado() const;
        sf::Vector2f getPosicaoAlvo() const;

        void setDano(int danoBase);
        void setVelocidadeInicial(float velocidade);

        void lancar(sf::Vector2f posInicial, sf::Vector2f alvo);

        void colidir(Personagens::Jogador* jogador);
        void colidir(Estrutura* estrutura);

        void executar();
        std::string salvar();
    };
}