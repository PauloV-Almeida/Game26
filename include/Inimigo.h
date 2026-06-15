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
            int nivel_maldade;

            int danoBase;
            int danoMaximo;

            float raioVisao;
            float raioAtaque;

            Jogador* jogador1;
            Jogador* jogador2;
            Jogador* alvoAtual;

            sf::Clock relogioAtaque;
            sf::Clock relogioMovimentoAleatorio;

            float intervaloAtaque;
            float tempoTrocaDirecao;

            int direcaoAleatoria;

        protected:
            float calcularDistancia(Jogador* jogador) const;

            Jogador* escolherAlvo();

            bool jogadorNoRaioVisao(Jogador* jogador) const;
            bool jogadorNoRaioAtaque(Jogador* jogador) const;

            void perseguir(Jogador* jogador);
            void andarAleatorio();

            int calcularDanoAtual() const;
            void aumentarMaldade();

            bool podeAtacar();

            void salvarInimigo();

        public:
            Inimigo();
            Inimigo(sf::Vector2f pos);
            Inimigo(sf::Vector2f pos, Jogador* j1, Jogador* j2 = nullptr);

            virtual ~Inimigo();

            int getNivelMaldade() const;
            int getDanoBase() const;
            int getDanoMaximo() const;

            float getRaioVisao() const;
            float getRaioAtaque() const;

            Jogador* getAlvoAtual() const;

            void setJogadores(Jogador* j1, Jogador* j2 = nullptr);

            void setNivelMaldade(int nivel);
            void setDanoBase(int dano);
            void setDanoMaximo(int dano);
            void setRaioVisao(float raio);
            void setRaioAtaque(float raio);

            virtual void executar();

            virtual void danificar(Jogador* jogador) = 0;
            virtual std::string salvar() = 0;
        };
    }
}