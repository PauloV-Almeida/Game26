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
            int idJogador;
            int pontos;

            int danoAtaque;
            int maxPulos;
            int pulosRestantes;

            bool atacando;
            bool olhandoDireita;
            bool venceu;

            sf::RectangleShape areaAtaque;
            sf::Clock relogioAtaque;
            float tempoAtaque;

        private:
            void tratarEntrada();
            void moverEsquerda();
            void moverDireita();
            void pular();
            void atacar();

            void atualizarTextura();
            void atualizarAreaAtaque();

        public:
            Jogador();
            Jogador(int idJogador, sf::Vector2f pos);
            ~Jogador();

            int getIdJogador() const;
            int getDanoAtaque() const;
            int getPontos() const;
            void setPontos(int pontos);
            void adicionarPontos(int pontos);
            bool estaAtacando() const;
            bool getVenceu() const;

            void setVenceu(bool venceu);
            void setDanoAtaque(int dano);

            void colidir(Inimigo* inimigo);

            void executar();
            void desenhar();
            std::string salvar();
        };
    }
}