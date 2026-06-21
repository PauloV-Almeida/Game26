#pragma once

#include "Personagem.h"
#include "Texturas.h"
#include "Id.h"

namespace Entidades
{
    namespace Personagens
    {
        class Inimigo;

        class Jogador : public Personagem
        {
        private:
            int pontos;
            float velMax;

            bool atacando;
            bool danoAplicadoAtaque;
            bool jogadorDois;

            sf::Clock relogioAtaque;
            float tempoAtaque;
            float intervaloAtaque;

            sf::Sprite spriteAtaque;

            float empurraoAtaque;
            float larguraAtaque;
            float alturaAtaque;

        private:
            sf::FloatRect getAreaAtaque() const;
            void atualizarAtaque();
            void posicionarSpriteAtaque();

        public:
            Jogador();
            Jogador(sf::Vector2f pos);
            ~Jogador();

            void setPontuacao(int pontos);
            void aumentarPontos();

            void movimentar(Direcao direcao);
            void posicaoInicial();
            sf::Vector2f getPosicao();
            void pararEixoX();

            void setJogadorDois(bool jg2);
            int getPontos();

            void atacar();
            void desenhar();
            void colidir(Inimigo* pInimigo);

            void executar() override;
            std::string salvar() override;
            void salvarDataBuffer();

            void resetarJogador();
        };
    }
}