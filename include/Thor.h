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
            Projetil* projetilAtual;

            float raioDisparo;
            float intervaloDisparo;
            float velocidadeProjetil;

            int danoProjetil;

            sf::Clock relogioDisparo;

            float escalaX;
            float escalaY;

        private:
            bool podeDisparar();
            void dispararProjetil(Jogador* jogador);

        public:
            Thor();
            Thor(sf::Vector2f pos);
            Thor(sf::Vector2f pos, Jogador* j1, Jogador* j2 = nullptr);
            ~Thor();

            Projetil* getProjetilAtual() const;

            void setProjetilAtual(Projetil* projetil);
            void setVelocidadeProjetil(float velocidade);
            void setDanoProjetil(int dano);

            void danificar(Jogador* jogador);

            void executar();
            std::string salvar();
        };
    }
}