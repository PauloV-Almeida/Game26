#pragma once

#include "Inimigo.h"

namespace Entidades
{
    namespace Personagens
    {
        class Andarilho : public Inimigo
        {
        private:
            float escalaX;
            float escalaY;

        public:
            Andarilho();
            Andarilho(sf::Vector2f pos);
            Andarilho(sf::Vector2f pos, Jogador* j1, Jogador* j2 = nullptr);
            ~Andarilho();

            void danificar(Jogador* jogador);

            void executar();
            std::string salvar();
        };
    }
}