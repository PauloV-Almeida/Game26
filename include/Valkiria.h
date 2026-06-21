#pragma once

#include "Inimigo.h"

namespace Entidades
{
    namespace Personagens
    {
        class Valkiria : public Inimigo
        {
        private:
            float empurrar;
            bool empurraoForte;
            float multiplicadorEmpurraoForte;
        public:
            Valkiria(sf::Vector2f pos, Jogador* jogador);
            virtual ~Valkiria();

            void danificar(Jogador* jogador) override;

            void executar() override;
            std::string salvar() override;
            void salvarDataBuffer();
        };
    }
}