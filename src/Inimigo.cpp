#include "../include/Inimigo.h"
#include "../include/Jogador.h"

#include <cmath>

int Entidades::Personagens::Inimigo::quantidadeInimigos = 0;
Entidades::Personagens::Jogador* Entidades::Personagens::Inimigo::jogador2Global = nullptr;

namespace Entidades
{
    namespace Personagens
    {
        Inimigo::Inimigo(sf::Vector2f pos, Jogador* jogador) :
            Personagem(pos),
            danoContatoRelogio(),
            danotempoContato(1.f),
            nivel_maldade(2),
            pJogador(jogador),
            raioVisao(250.f)
        {
            setNivelMaldade(1 + (rand() % 10));
            quantidadeInimigos++;
        }

        Inimigo::~Inimigo()
        {}

        Jogador* Inimigo::getPlayer() const
        {
            return pJogador;
        }

        int Inimigo::getQuantidadeInimigos()
        {
            return quantidadeInimigos;
        }

		void Inimigo::setNivelMaldade(int maldade)
		{
			nivel_maldade = maldade;
		}

        int Inimigo::getNivelMaldade()
        {
            return nivel_maldade;
        }

        void Inimigo::zerarInimigos()
        {
            quantidadeInimigos = 0;
        }

        void Inimigo::setJogador2Global(Jogador* jogador2)
        {
            jogador2Global = jogador2;
        }

        bool Inimigo::jogadorValido(Jogador* jogador) const
        {
            return jogador && jogador->ativado() && jogador->vivo();
        }

        float Inimigo::calcularDistancia(Jogador* jogador) 
        {
            if (!jogador)
            {
                return 999999.f;
            }

            sf::Vector2f dist;
            dist.x = jogador->getCentro().x - getCentro().x;
            dist.y = jogador->getCentro().y - getCentro().y;

            return sqrt((dist.x * dist.x) + (dist.y * dist.y));
        }

        Jogador* Inimigo::escolherMelhorAlvo()
        {
            Jogador* melhorAlvo = nullptr;
            float menorDistancia = raioVisao;

            if (jogadorValido(pJogador))
            {
                float distancia1 = calcularDistancia(pJogador);

                if (distancia1 <= menorDistancia)
                {
                    menorDistancia = distancia1;
                    melhorAlvo = pJogador;
                }
            }

            if (jogadorValido(jogador2Global))
            {
                float distancia2 = calcularDistancia(jogador2Global);

                if (distancia2 <= menorDistancia)
                {
                    menorDistancia = distancia2;
                    melhorAlvo = jogador2Global;
                }
            }

            return melhorAlvo;
        }

        void Inimigo::diminuirInimigos()
        {
            if (quantidadeInimigos > 0)
            {
                quantidadeInimigos--;
            }
        }

        void Inimigo::setAtivo(bool at)
        {
            if (ativo && !at)
            {
                diminuirInimigos();
            }

            ativo = at;
        }

        bool Inimigo::jogadorNoAlcance()
        {
            Jogador* alvo = escolherMelhorAlvo();

            if (!alvo)
            {
                return false;
            }

            pJogador = alvo;
            return true;
        }

        void Inimigo::perseguirJogador()
        {
            Jogador* alvo = escolherMelhorAlvo();

            if (!alvo)
            {
                velo.x = 0.f;
                return;
            }

            pJogador = alvo;

            if (getPosicao().x < pJogador->getPosicao().x)
            {
                velo.x = velMovimento;
                direcao = Direcao::RIGHT;
            }
            else
            {
                velo.x = -velMovimento;
                direcao = Direcao::LEFT;
            }
        }

        void Inimigo::salvarDataBuffer()
        {
            Personagem::salvarDataBuffer();
            buffer << nivel_maldade << " ";
        }
    }
}