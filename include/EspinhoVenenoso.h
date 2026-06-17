#pragma once

#include "Obstaculo.h"

namespace Entidades
{
    namespace Obstaculos
    {
        class EspinhoVenenoso : public Obstaculo
        {
        private:
            int dano;
            float intervaloDano;
            sf::Clock relogioDano;

        public:
            EspinhoVenenoso();
            EspinhoVenenoso(sf::Vector2f pos);
            EspinhoVenenoso(sf::Vector2f pos, sf::Vector2f tamanho);
            virtual ~EspinhoVenenoso();

            void executar() override;
            void obstaculizar(Personagens::Jogador* jogador) override;

            std::string salvar() override;
            void salvarDataBuffer();
        };
    }
}