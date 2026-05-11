#include "../include/Esqueleto.h"

namespace Entidades
{
	namespace Personagens
	{
		
		Esqueleto::Esqueleto(bool viv, int nV, sf::Vector2f pos, sf::Vector2f velo, float dmg, sf::Vector2f tam, float emp) :
			Inimigo(1, pos, velo, tam),
			empurrar(emp)
		{
			dano = dmg;
			n_vidas = nV;
			texturas = pGG->carregar_texturas("./assets/Esqueleto.png");
			corpo.setTexture(texturas);
			vivo = viv;
			
		}
		Esqueleto::~Esqueleto()
		{
		}
		void Esqueleto::executar()
		{
			mover();
			desenhar();
		}
		void Esqueleto::danificar()
		{
			if (velocidade > 0)
			{
				vel.y -= 5.f;
				corpo.setPosition(corpo.getPosition() + sf::Vector2f(velocidade * vel.x / 10, velocidade * vel.y / 10));
			}
			

		}
		void Esqueleto::colidir(Jogador* pJog, std::string direcao)
		{
			pJog->receber_dano(dano);
			if (direcao == "Embaixo")
			{
				noChao = true;
				vel.y = 0.0f;
			}
			else if (direcao == "Cima")
			{
				vel.y = 0.0f;
			}
			else if (direcao == "Esquerda")
			{
				vel.x = 0.0f;
				pJog->set_vel(pJog->get_vel() + sf::Vector2f(-empurrar, 0.f));
			}
			else if (direcao == "Direita")
			{
				vel.x = 0.0f;
				pJog->set_vel(pJog->get_vel() + sf::Vector2f(empurrar, 0.f));
			}
		}
		void Esqueleto::colidir(Obstaculos::Obstaculo* pObs, std::string direcao)
		{
			if (direcao == "Embaixo")
			{
				noChao = true;
				vel.y = 0.0f;
			}
			else if (direcao == "Cima")
			{
				vel.y = 0.0f;
			}
			else if (direcao == "Esquerda" || direcao == "Direita")
			{
				vel.x = 0.0f;
			}
		}

		void Esqueleto::desenhar()
		{
			pGG->desenhar(&corpo);
		}
	}
}