#include "../include/Inimigo.h"

namespace Entidades
{
	namespace Personagens
	{
		Inimigo::Inimigo(int indice, sf::Vector2f pos, sf::Vector2f vel, sf::Vector2f tam) :
			Personagem(indice, pos, vel, tam)
		{
			dano = 0;
		}
		Inimigo::~Inimigo()
		{
		}
		
		void Inimigo::movimentoaleatorio()
		{
			if (!noChao)
				vel.y += GRAVIDADE;
			int r = std::rand() % 100;

			if (r < 3 && noChao)
			{
				vel.y = -8.0f;
				noChao = false;
			}

			float change = (static_cast<float>(std::rand() % 101) / 100.f) * 0.6f;
			if (r < 50)
				vel.x += change;
			else
				vel.x -= change;

			vel.x *= 0.8f;


			if (vel.x > VEL_MAX_INI) vel.x = VEL_MAX_INI;
			if (vel.x < -VEL_MAX_INI) vel.x = -VEL_MAX_INI;


			corpo.move(vel.x, vel.y);


			noChao = false;
		}

		void Inimigo::persegue(sf::Vector2f posJogador, sf::Vector2f posInimigo)
		{
			if (!noChao)
				vel.y += GRAVIDADE;

			if ((posInimigo.x - posJogador.x) > 0)
				vel.x -= vel.x;

			else if ((posInimigo.x - posJogador.x) < 0)
				vel.x += vel.x;
			else
				vel.x *= 8;

			if (vel.x > VEL_MAX_INI)
				vel.x = VEL_MAX_INI;
			if (vel.x < -VEL_MAX_INI)
				vel.x = -VEL_MAX_INI;

			if ((posInimigo.y - posJogador.y) > 0)
			{
				vel.y -= 10.0;
				noChao = false;
			}

			corpo.move(vel.x, vel.y);

			noChao = false;

		}

		void Inimigo::mover()
		{
			sf::Vector2f posInimigo = corpo.getPosition();

			if (!LJogs)
			{
				movimentoaleatorio();
				return;
			}

			bool encontrou = false;
			auto itr = LJogs->get_Primeiro();
			while (itr != NULL)
			{
				Entidades::Entidade* e = *itr;
				Entidades::Personagens::Jogador* jog = dynamic_cast<Entidades::Personagens::Jogador*>(e);
				if (jog)
				{
					sf::Vector2f posJogador = jog->get_posicao();

					if (std::fabs(posInimigo.x - posJogador.x) < RAIOX &&
						std::fabs(posInimigo.y - posJogador.y) < RAIOY)
					{
						persegue(posJogador, posInimigo);
						encontrou = true;
						break;
					}
				}
				itr++;
			}

			if (!encontrou)
				movimentoaleatorio();
		}
	}
}