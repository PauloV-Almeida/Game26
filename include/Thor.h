#pragma once

#include "Inimigo.h"
#include "Projetil.h"

namespace Entidades
{
    namespace Personagens
    {
        class Thor : public Inimigo
        {
        private:
            short int forca;

            Projetil* projetil;
            sf::Clock relogioProjetil;
            float intervaloProjetil;

        public:
            Thor(sf::Vector2f pos, Jogador* jogador, Projetil* projetil = nullptr);
            virtual ~Thor();

            void setProjetil(Projetil* pProjetil);

            void danificar(Jogador* jogador) override;
            void executar() override;

            std::string salvar() override;
            void salvarDataBuffer();
        };
    }
}