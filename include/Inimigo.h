#pragma once

#include "Personagem.h"
#include "Jogador.h"
#include "../stdafx/stdafx.h"

#define VEL_MAX_INI 3.0f

#define RAIO_PERSEGUIR_X 220.0f
#define RAIO_PERSEGUIR_Y 100.0f

#define RAIO_ATAQUE_X 45.0f
#define RAIO_ATAQUE_Y 45.0f

#define NIVEL_MALDADE_MAX 5

namespace Entidades
{
    namespace Personagens
    {
        class Jogador;

        class Inimigo : public Personagem
        {
        protected:
            int nivel_maldade;
            int dano_base;

            Jogador* pJog1;
            Jogador* pJog2;

            int direcaoAleatoria;
            int tempoTrocaDirecao;

        protected:
            Jogador* escolherAlvo();

            bool jogadorNoRaioPerseguicao(Jogador* pJog);
            bool jogadorNoRaioAtaque(Jogador* pJog);

            void aplicarGravidade();
            void limitarVelocidade();

            void andarAleatorio();
            void perseguir(Jogador* pJog);

            void aumentarMaldade();
            int calcularDanoAtual() const;

        public:
            Inimigo(
                int indice = -1,
                sf::Vector2f pos = sf::Vector2f(10.f, 0.f),
                sf::Vector2f vel = sf::Vector2f(0.f, 0.f),
                sf::Vector2f tam = sf::Vector2f(50.f, 50.f),
                Jogador* pJ1 = nullptr,
                Jogador* pJ2 = nullptr
            );

            virtual ~Inimigo();

            virtual void executar() = 0;
            virtual void danificar(Jogador* pJog) = 0;

            virtual void mover();

            int get_nivel_maldade() const { return nivel_maldade; }
            void set_nivel_maldade(int n) { nivel_maldade = n; }

            virtual void salvarDataBuffer();
            virtual void salvar(std::ostream& out) = 0;
        };
    }
}