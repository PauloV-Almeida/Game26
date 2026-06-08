#include "../include/Jogador.h"

namespace Entidades {
	namespace Personagens {
		Jogador::Jogador()
			:Personagem()
		{
			ativo = 1;
			pulo = 2;
			jogadorDois = 0;
			pontos = 0;
			posicao = sf::Vector2f(300.f, 0.f);
			forma.setPosition(posicao);
			maxSpeed = 6;
			forma.setTexture(*pGG->getTextura(Texturas::jogador));
		}

		Jogador::Jogador(sf::Vector2f pos)
			:Personagem(pos)
		{
			jogadorDois = 0;
			id = Id::Jogador;
			pontos = 0;
			maxSpeed = 6;
			vida = 55;
			pulo = 2;
			forma.setTexture(*pGG->getTextura(Texturas::jogador));
			forma.setTextureRect(sf::IntRect(0, 0, 16, 16));
			forma.setScale(5, 5);
			setFigura(&forma);

		}

		Jogador::~Jogador()
		{

		}

		sf::Vector2f Jogador::getPosicao()
		{
			return forma.getPosition();
		}

		void Jogador::setPontuacao(int pontuacao)
		{
			pontos = pontuacao;
		}

		void Jogador::movimentar(Directions direcao)
		{
			switch (direcao) {
			case Directions::UP: {
				if (pulo && (RelogioPuloCooldown.getElapsedTime().asSeconds() >= puloCooldown)) {
					RelogioPuloCooldown.restart();
					vel.y = -8;
					pulo--;
				}
				break;
			}
			case Directions::DOWN: {
				direction = Directions::DOWN;
				vel.y += 0.3;
				break;
			}
			case Directions::LEFT: {
				direction = Directions::LEFT;
				if (vel.x >= -maxSpeed) {
					vel.x -= 0.4;
				}
				break;
			}
			case Directions::RIGHT: {
				direction = Directions::RIGHT;
				if (vel.x <= maxSpeed) {
					vel.x += 0.4;
				}
				break;
			}
			default:
			{
				break;
			}

			}
		}

		void Jogador::posicionarNoInicio()
		{
			forma.setPosition(100, 100);
		}

		

		void Jogador::aumentarPontos()
		{
			pontos++;
		}

		void Jogador::setJogadorDois(bool jg2)
		{
			jogadorDois = jg2;
		}

		int Jogador::getPontos()
		{
			return pontos;
		}

		void Jogador::executar()
		{
			//move o player a atualiza a posição da camera
			if (direction == Directions::LEFT) {
				forma.setTexture(*pGG->getTextura(Texturas::jogadorEsq));

			}
			else {
				forma.setTexture(*pGG->getTextura(Texturas::jogador));
			}
			mover();
		}

		std::string Jogador::salvar()
		{
			salvarJogador();
			return buffer.str();
		}
		void Jogador::salvarJogador()
		{
			salvarPersonagem();
			buffer << pontos << " " << jogadorDois;
		}

		void Jogador::resetarJogador()
		{
			setAtivo(1);
			setVelocidade(0, 0);
			setVida(55);
			setPosicao(100, 100);
			setPontuacao(0);
			setPulos(2);
		}



	}
}