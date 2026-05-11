#include "../include/Jogador.h"

namespace Entidades
{
	namespace Personagens
	{
		Jogador::Jogador(int indice, sf::Vector2f pos, sf::Vector2f velo, sf::Vector2f tam) :
			ataque_corpo(sf::Vector2f(tam.x * 2, tam.y * 2)),
			atacando(false),
			Personagem(0, pos, velo, tam),
			venceu(false),
			id_jogador(indice),
			direita(true)
		{
			dano = DMG;
			ataque_corpo.setOrigin(ataque_corpo.getSize().x / 2, ataque_corpo.getSize().y / 2);
			ataque_corpo.setTexture(pGG->carregar_texturas("./assets/jogador1.png"));
			n_vidas = 20;
			if (id_jogador == 1)
			{
				texturas = pGG->carregar_texturas("./assets/jogador1.png");
			}
			else if (id_jogador == 2)
			{
				texturas = pGG->carregar_texturas("./assets/jogador1.png");
			}

			corpo.setTexture(texturas);
		}

		Jogador::Jogador(int indice, bool viv, int nV, sf::Vector2f pos, sf::Vector2f velo, sf::Vector2f tam) :
			ataque_corpo(corpo.getSize() * 2.f),
			atacando(false),
			Personagem(0, pos, velo, tam),
			venceu(false),
			id_jogador(indice),
			direita(true),
			ataque_direcao("Acima")
		{
			dano = DMG;
			vivo = viv;
			n_vidas = nV;

			ataque_corpo.setOrigin(ataque_corpo.getSize().x / 2, ataque_corpo.getSize().y / 2);
			if (id_jogador == 1)
			{
				pGG->carregar_texturas("./assets/jogador1-esquerda.png");
				texturas = pGG->carregar_texturas("./assets/jogador1-direita.png");
			}
			else if (id_jogador == 2)
			{
				pGG->carregar_texturas("./assets/jogador1-esquerda.png");
				texturas = pGG->carregar_texturas("./assets/jogador1-direita.png");
			}
			corpo.setTexture(texturas);

			texturas = pGG->carregar_texturas("./assets/jogador1.png");
			ataque_corpo.setTexture(texturas);
		}

		Jogador::~Jogador()
		{

		}

		void Jogador::desenhar()
		{
			if (vivo)
			{
				if (atacando)
				{
					if (ataque_direcao == "Direita")
					{
						ataque_corpo.rotate(90);
						pGG->desenhar(&ataque_corpo);
						ataque_corpo.rotate(-90);
					}
					else if (ataque_direcao == "Esquerda")
					{
						ataque_corpo.rotate(-90);
						pGG->desenhar(&ataque_corpo);
						ataque_corpo.rotate(90);
					}
					else if (ataque_direcao == "Abaixo")
					{
						ataque_corpo.rotate(180);
						pGG->desenhar(&ataque_corpo);
						ataque_corpo.rotate(180);
					}
					else
					{
						pGG->desenhar(&ataque_corpo);
					}
					atacando = false;
				}
				pGG->desenhar(&corpo);
			}
		}

		void Jogador::executar()
		{
			if (n_vidas <= 0)
				vivo = false;

			mover();

			ataque();
		}

		void Jogador::mover(char direcao)
		{
			if (id_jogador == 1)
			{
				if (!noChao)
					vel.y += GRAVIDADE;

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
					vel.x -= VELOCIDADE;
					corpo.setTexture(pGG->carregar_texturas("./assets/jogador1-esquerda.png"));
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
					vel.x += VELOCIDADE;
					corpo.setTexture(pGG->carregar_texturas("./assets/jogador1-direita.png"));
				}
				else
					vel.x *= 0.8f;

				if (vel.x > VEL_MAX)
					vel.x = VEL_MAX;
				if (vel.x < -VEL_MAX)
					vel.x = -VEL_MAX;

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && noChao)
				{
					vel.y -= 6.0;
					noChao = false;
				}
				corpo.move(vel.x, vel.y);

				noChao = false;
			}

			else if (id_jogador == 2)
			{
				if (!noChao)
					vel.y += GRAVIDADE;

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
					vel.x -= VELOCIDADE;
					corpo.setTexture(pGG->carregar_texturas("./assets/jogador1-direita.png"));
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
					vel.x += VELOCIDADE;
					corpo.setTexture(pGG->carregar_texturas("./assets/jogador1-esquerda.png"));
				}
				else
					vel.x *= 0.8f;

				if (vel.x > VEL_MAX)
					vel.x = VEL_MAX;
				if (vel.x < -VEL_MAX)
					vel.x = -VEL_MAX;

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && noChao)
				{
					vel.y -= 6.0;
					noChao = false;
				}
				corpo.move(vel.x, vel.y);

				noChao = false;
			}
		}

		void Jogador::colidir(Inimigo* pIni, std::string direcao)
		{
			receber_dano(pIni->get_dano());

			if (direcao == "Embaixo")
			{
				noChao = true;
				vel.y = 0.0f;
			}
			else if (direcao == "Cima" || direcao == "Emcima")
			{
				vel.y = 0.0f;
			}
			else if (direcao == "Esquerda" || direcao == "Direita")
			{
				vel.x = 0.0f;
			}
		}

		void Jogador::colidir(Obstaculos::Obstaculo* pObs, std::string direcao)
		{
			if (direcao == "Embaixo")
			{
				noChao = true;
				vel.y = 0.0f;
			}
			else if (direcao == "Cima" || direcao == "Emcima")
			{
				vel.y = 0.0f;
			}
			else if (direcao == "Esquerda" || direcao == "Direita")
			{
				vel.x = 0.0f;
			}
		}
			
		void Jogador::ataque()
		{
			if ((id_jogador == 1 && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) ||
				(id_jogador == 2 && !sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)))
			{
				return;
			}
			dano = DMG;
			atacando = true;

			std::string direcao = "";
			if (id_jogador == 1)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				{
					direcao = "Acima";
					ataque_direcao = "Acima";
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					direcao = "Esquerda";
					ataque_direcao = "Esquerda";
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				{
					direcao = "Direita";
					ataque_direcao = "Direita";
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{
					direcao = "Abaixo";
					ataque_direcao = "Abaixo";
				}

			}
			else if (id_jogador == 2)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					direcao = "Acima";
					ataque_direcao = "Acima";
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					direcao = "Esquerda";
					ataque_direcao = "Esquerda";
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					direcao = "Direita";
					ataque_direcao = "Direita";
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					direcao = "Abaixo";
					ataque_direcao = "Abaixo";
				}
			}
			if (direcao == "Acima")
			{
				ataque_corpo.setPosition(sf::Vector2f(corpo.getPosition().x, corpo.getPosition().y - corpo.getSize().y / 2 - ataque_corpo.getSize().y / 2));
			}
			else if (direcao == "Direita")
			{
				ataque_corpo.setPosition(sf::Vector2f(corpo.getPosition().x + corpo.getSize().x / 2 + ataque_corpo.getSize().x / 2, corpo.getPosition().y));
			}
			if (direcao == "Abaixo")
			{
				ataque_corpo.setPosition(sf::Vector2f(corpo.getPosition().x, corpo.getPosition().y + corpo.getSize().y / 2 + ataque_corpo.getSize().y / 2));
			}
			else if (direcao == "Esquerda")
			{
				ataque_corpo.setPosition(sf::Vector2f(corpo.getPosition().x - corpo.getSize().x / 2 - ataque_corpo.getSize().x / 2, corpo.getPosition().y));
			}
			pGG->desenhar(&ataque_corpo);

			dano = 0;
		}

	}//Personagens
}