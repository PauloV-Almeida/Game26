#pragma once

#include "Entidades.h"

namespace Entidades
{
    namespace Personagens
    {
        class Jogador;
    }

    namespace Obstaculos
    {
        class Obstaculo : public Entidade
        {
        protected:
            bool danoso;
            bool colidivel;

            float empuxo;

        protected:
            void atualizarFisicaObstaculo();

        public:
            Obstaculo();
            Obstaculo(sf::Vector2f pos);
            virtual ~Obstaculo();

            bool ehDanoso() const;
            bool ehColidivel() const;

            void setDanoso(bool estado);
            void setColidivel(bool estado);

            virtual void executar() = 0;
            virtual void obstaculizar(Personagens::Jogador* jogador) = 0;

            virtual void salvarDataBuffer();
            virtual std::string salvar() = 0;
        };
    }
}