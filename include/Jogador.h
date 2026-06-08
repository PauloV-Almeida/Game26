#pragma once
#include "Personagem.h"
#include "Id.h"


namespace Entidades {
	class Projetil;
	namespace Personagens {
		class Jogador : public Personagem
		{
		private:
			sf::Clock dashRelogio;
			float dashCooldown = 3;
			int pontos;
			float maxSpeed;
			sf::Vector2f center;
			bool jogadorDois;
		public:
			Jogador();
			Jogador(sf::Vector2f pos);
			~Jogador();
			sf::Vector2f getPosicao();
			//Adicionam velocidade ao vetor de velocidade do jogador
			void setPontuacao(int pontos);
			void movimentar(Directions direcao);
			void posicionarNoInicio();
			
			
			void aumentarPontos();
			void setJogadorDois(bool);
			int getPontos();
			void executar();
			std::string salvar();
			void salvarJogador();
			void resetarJogador();
		};
	}

}