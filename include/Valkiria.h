#pragma once

#include "Inimigo.h"

#define EMPURRAO_BASE 2.0f
#define EMPURRAO_MAX 6.0f

namespace Entidades
{
    namespace Personagens
    {
        class Valkiria : public Inimigo
        {
        private:
            int tamanho;

        public:
            Valkiria(
                int indice = -1,
                sf::Vector2f pos = sf::Vector2f(100.f, 100.f),
                sf::Vector2f vel = sf::Vector2f(0.f, 0.f),
                sf::Vector2f tam = sf::Vector2f(60.f, 60.f),
                Jogador* pJ1 = nullptr,
                Jogador* pJ2 = nullptr
            );

            ~Valkiria();

            void executar();
            void danificar(Jogador* pJog);

            void salvarDataBuffer();
            void salvar(std::ostream& out);
        };
    }
}