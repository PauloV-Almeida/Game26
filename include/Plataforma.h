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
            float empuxo;

        public:
            Plataforma();
            Plataforma(sf::Vector2f pos);
            Plataforma(sf::Vector2f pos, sf::Vector2f tamanho);
            ~Plataforma();

            void executar();
            void obstaculizar(Personagens::Jogador* jogador);

            std::string salvar();
        };
    }
}