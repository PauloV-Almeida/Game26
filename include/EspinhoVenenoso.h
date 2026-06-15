#pragma once

#include "Obstaculo.h"

namespace Entidades
{
    namespace Obstaculos
    {
        class EspinhoVenenoso : public Obstaculo
        {
        private:
            int danoContato;
            int danoVeneno;

            float tempoVeneno;
            bool venenoAtivo;

            sf::Clock relogioVeneno;
            sf::Clock relogioDanoContato;

            float intervaloDanoContato;

        public:
            EspinhoVenenoso();
            EspinhoVenenoso(sf::Vector2f pos);
            EspinhoVenenoso(sf::Vector2f pos, sf::Vector2f tamanho);
            ~EspinhoVenenoso();

            void executar();
            void obstaculizar(Personagens::Jogador* jogador);

            std::string salvar();
        };
    }
}