#pragma once

#include "Obstaculo.h"

namespace Entidades
{
    namespace Obstaculos
    {
        class Plataforma : public Obstaculo
        {
        private:
            bool pVerifica;
        public:
            Plataforma(sf::Vector2f pos = sf::Vector2f(0.f, 0.f), bool veri = false);
            ~Plataforma();
            void obstaculizar(Entidade* outro, std::string  direcao = "");
            void executar();
            void mover();
        };
    }
}