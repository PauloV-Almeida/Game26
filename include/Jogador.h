#pragma once

#include <SFML/Graphics.hpp>
#include <math.h>
#include <string>

#include "Personagem.h"
#include "Obstaculo.h"
#include "Inimigo.h"

#define DMG 3

namespace Entidades
{
	namespace Personagens
	{
		class Inimigo;
		class Jogador : public Personagem
		{
		protected:
			sf::RectangleShape ataque_corpo;
			bool atacando;
			int id_jogador;
			bool venceu;
			bool direita;
			std::string ataque_direcao;
		public:
			Jogador(int indice = 1, sf::Vector2f pos = sf::Vector2f(10.f, 0.f), sf::Vector2f vel = sf::Vector2f(0.f, 0.f), sf::Vector2f tam = sf::Vector2f(5.f, 5.f));
			Jogador(int indice, bool viv, int nV, sf::Vector2f pos, sf::Vector2f velo, sf::Vector2f tam);
			~Jogador();

			void executar();
			void mover(char direcao = '0');
			void colidir(Inimigo* pIni, std::string direcao = "");
			void colidir(Obstaculos::Obstaculo* pObs, std::string direcao = "");
			void ataque();
			void set_venceu(bool v) { venceu = v; };
			bool get_venceu() { return venceu; };

			sf::Vector2f get_ataque_posicao() { return ataque_corpo.getPosition(); }
			sf::Vector2f get_ataque_tamanho() { return ataque_corpo.getSize(); }

			void desenhar();
			
		};
	}
}