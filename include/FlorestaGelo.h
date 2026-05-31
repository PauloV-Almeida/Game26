#pragma once

#include "Fase.h"

#include "EspinhoVenenoso.h"
#include "Valkiria.h"

#include <vector>
#include <algorithm>
#include <random>
#include <iostream>

namespace Fases
{
    class FlorestaGelo : public Fase
    {
    private:
        const int minInimigos;
        const int maxInimigos;

        const int minEspinhos;
        const int maxEspinhos;

        std::vector<sf::Vector2f> posicoesValkirias;
        std::vector<sf::Vector2f> posicoesEspinhos;

    private:
        void criarEspinhoVenenoso(sf::Vector2f pos);
        void criarValkiria(sf::Vector2f pos);

    protected:
        void criarInimigos();
        void criarObstaculos();

        void tratarElementoMapa(int valor, sf::Vector2f pos);

    public:
        FlorestaGelo(
            Entidades::Personagens::Jogador* j1,
            Entidades::Personagens::Jogador* j2 = nullptr
        );

        ~FlorestaGelo();

        void executar();
    };
}