#pragma once
#include "Entidades.h"
#include "Jogador.h"



namespace Entidades {
	namespace Obstaculos {
		class Obstaculo : public Entidade
		{
		protected:
			bool colidivel;
			bool danoso;
		public:
			Obstaculo(sf::Vector2f pos);
			Obstaculo();
			~Obstaculo();
			const bool ehColidivel();
			virtual void obstaculizar(Personagens::Jogador* pJogador) = 0;
			virtual void executar() = 0;
			virtual std::string salvar() = 0;
			void salvarObstaculo();
		};
	}
}