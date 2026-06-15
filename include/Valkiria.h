#pragma once

#include "Inimigo.h"

namespace Entidades
{
    namespace Personagens
    {
        class Valkiria : public Inimigo
        {
        private:
            float forcaEmpurraoBase;
            float forcaEmpurraoMaxima;

            float escalaX;
            float escalaY;

        private:
            void empurrarJogador(Jogador* jogador);

        public:
            Valkiria();
            Valkiria(sf::Vector2f pos);
            Valkiria(sf::Vector2f pos, Jogador* j1, Jogador* j2 = nullptr);
            ~Valkiria();

            void danificar(Jogador* jogador);

            void executar();
            std::string salvar();
        };
    }
}