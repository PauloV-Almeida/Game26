#pragma once

#include "Inimigo.h"

namespace Entidades
{
    namespace Personagens
    {
        class Andarilho : public Inimigo
        {
        private:
            float raio;

        public:
            Andarilho(
                int indice = -1,
                sf::Vector2f pos = sf::Vector2f(100.f, 100.f),
                sf::Vector2f vel = sf::Vector2f(0.f, 0.f),
                sf::Vector2f tam = sf::Vector2f(50.f, 50.f),
                Jogador* pJ1 = nullptr,
                Jogador* pJ2 = nullptr
            );

            ~Andarilho();

            void executar();
            void danificar(Jogador* pJog);

            void salvarDataBuffer();
            void salvar(std::ostream& out);
        };
    }
}