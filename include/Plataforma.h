#pragma once

#include "Obstaculo.h"

namespace Entidades
{
    namespace Obstaculos
    {
        class Plataforma : public Obstaculo
        {
        private:
            float aceleracaoGelo;
            float velocidadeMaximaGelo;
            

        public:
            Plataforma();
            Plataforma(sf::Vector2f pos);
            Plataforma(sf::Vector2f pos, sf::Vector2f tamanho);
            virtual ~Plataforma();

            void executar() override;
            void obstaculizar(Personagens::Jogador* jogador) override;

            std::string salvar() override;
            void salvarDataBuffer();
        };
    }
}