#pragma once

#include "Obstaculo.h"
#include "Personagem.h"

#define ESCORREGAMENTO_GELO 1.02f
#define VELOCIDADE_MAX_GELO 7.0f

namespace Entidades
{
    namespace Obstaculos
    {
        class Plataforma : public Obstaculo
        {
        private:
            int altura;

        public:
            Plataforma(
                int indice = -1,
                sf::Vector2f pos = sf::Vector2f(300.f, 600.f),
                sf::Vector2f tam = sf::Vector2f(200.f, 30.f)
            );

            ~Plataforma();

            void executar();
            void obstaculizar(Entidades::Entidade* outro, std::string direcao = "");

            void salvarDataBuffer();
            void salvar(std::ostream& out);
        };
    }
}