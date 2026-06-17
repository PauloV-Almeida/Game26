#include "../include/Inimigo.h"
#include "../include/Jogador.h"

#include <cmath>

int Entidades::Personagens::Inimigo::quantidadeInimigos = 0;

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
            if (!pJogador)
            {
                return false;
            }

            sf::Vector2f dist;
            dist.x = pJogador->getCentro().x - getCentro().x;
            dist.y = pJogador->getCentro().y - getCentro().y;

            float modDist = sqrt((dist.x * dist.x) + (dist.y * dist.y));

            return modDist < raioVisao;
        }

        void Inimigo::perseguirJogador()
        {
            if (!pJogador)
            {
                velo.x = 0.f;
                return;
            }

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