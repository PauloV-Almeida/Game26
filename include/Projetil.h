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
        int veloProjetil;

        bool lancado;

        sf::Vector2f posicaoAlvo;

    public:
        Projetil();
        Projetil(sf::Vector2f pos);
        virtual ~Projetil();

        int getDano() const;
        bool foiLancado() const;
        sf::Vector2f getPosicaoAlvo() const;

        void setDano(int danoBase);
        void setVelocidadeInicial(int velocidade);

        void lancar(sf::Vector2f origem, sf::Vector2f alvo, int aumentoVelo);

        void colidir(Personagens::Jogador* jogador);
        void colidir(Estrutura* estrutura);

        void executar() override;

        void salvarDataBuffer();
        std::string salvar() override;
    };
}