#pragma once

#include "Obstaculo.h"

namespace Entidades
{
    namespace Obstaculos
    {
        class Runa : public Obstaculo
        {
        private:
            float tempoTravamento;

            Personagens::Jogador* jogadorTravado;
            bool travandoJogador;
            bool jaAtivada;

            sf::Clock relogioTravamento;

        public:
            Runa();
            Runa(sf::Vector2f pos);
            Runa(sf::Vector2f pos, sf::Vector2f tamanho);
            virtual ~Runa();

            void executar() override;
            void obstaculizar(Personagens::Jogador* jogador) override;

            std::string salvar() override;
            void salvarDataBuffer();
        };
    }
}