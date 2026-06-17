#pragma once

#include "Inimigo.h"

namespace Entidades
{
    namespace Personagens
    {
        class Andarilho : public Inimigo
        {
        private:
            int forca;

        public:
            Andarilho(sf::Vector2f pos, Jogador* jogador);
            virtual ~Andarilho();

            void danificar(Jogador* jogador) override;

            void executar() override;
            std::string salvar() override;
            void salvarDataBuffer();
        };
    }
}