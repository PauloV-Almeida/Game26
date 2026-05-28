#pragma once

#include "Obstaculo.h"
#include "Jogador.h"

#define DANO_ESPINHO 1
#define DURACAO_VENENO_SEGUNDOS 2.0f
#define INTERVALO_DANO_VENENO 0.5f

namespace Entidades
{
    namespace Obstaculos
    {
        class EspinhoVenenoso : public Obstaculo
        {
        private:
            float largura;

            Entidades::Personagens::Jogador* jogadorEnvenenado1;
            Entidades::Personagens::Jogador* jogadorEnvenenado2;

            sf::Clock relogioVeneno1;
            sf::Clock relogioVeneno2;

            sf::Clock relogioDano1;
            sf::Clock relogioDano2;

        private:
            void aplicarVeneno(Entidades::Personagens::Jogador* pJog);
            void atualizarVenenoJogador(
                Entidades::Personagens::Jogador*& pJog,
                sf::Clock& relogioVeneno,
                sf::Clock& relogioDano
            );

        public:
            EspinhoVenenoso(
                int indice = -1,
                sf::Vector2f pos = sf::Vector2f(500.f, 600.f),
                sf::Vector2f tam = sf::Vector2f(120.f, 25.f)
            );

            ~EspinhoVenenoso();

            void executar();
            void obstaculizar(Entidades::Entidade* outro, std::string direcao = "");

            void salvarDataBuffer();
            void salvar(std::ostream& out);
        };
    }
}