#pragma once

#include "Personagem.h"

namespace Entidades
{
    namespace Personagens
    {
        class Jogador;

        class Inimigo : public Personagem
        {
        protected:
            sf::Clock danoContatoRelogio;
            float danotempoContato;

            static int quantidadeInimigos;

            int nivel_maldade;
            Jogador* pJogador;
            float raioVisao;

        public:
            Inimigo(sf::Vector2f pos, Jogador* jogador);
            virtual ~Inimigo();

            Jogador* getPlayer() const;
            static int getQuantidadeInimigos();

            void setNivelMaldade(int maldade);
            static void zerarInimigos();
            void diminuirInimigos();

            virtual void setAtivo(bool at);
            virtual void perseguirJogador();
            virtual bool jogadorNoAlcance();

            void salvarDataBuffer();

            virtual void executar() = 0;
            virtual void danificar(Jogador* jogador) = 0;
            virtual std::string salvar() = 0;
        };
    }
}