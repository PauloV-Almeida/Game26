#pragma once

#include "Obstaculo.h"

namespace Entidades
{
    namespace Obstaculos
    {
        class Runa : public Obstaculo
        {
        private:
            float tempoTravamento;

            Personagens::Jogador* jogadorTravado;
            bool travandoJogador;

            sf::Clock relogioTravamento;

        public:
            Runa();
            Runa(sf::Vector2f pos);
            Runa(sf::Vector2f pos, sf::Vector2f tamanho);
            ~Runa();

            void executar();
            void obstaculizar(Personagens::Jogador* jogador);

            std::string salvar();
        };
    }
}