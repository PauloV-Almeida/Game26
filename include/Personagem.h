#pragma once
#include "Entidades.h"
#include "ListaEntidades.h"


namespace Gerenciadores {
	class GerenciadorColisao;
}

namespace Entidades {

	namespace Obstaculos {
		class Obstaculo;
	}

	namespace Personagens {
		class Personagem : public Entidade
		{
		protected:
			
			
			float maxVelo;
			float moveVelo;
			sf::Clock RelogioPuloCooldown;
			float puloCooldown = 0.2;
			int vida;
			int pulo = 2;
			
		public:
			
			Personagem();
			Personagem(sf::Vector2f pos);
			~Personagem();
			void colidiu(Entidade* entidade);
			
			const int getVidas() const;
			const bool vivo() const;

			void setVida(int vida);
			void setPulos(int pulos);

			virtual void aumentarPontos() = 0;
			void tiraVida(int dano);
			void setMoveVelocidade(float moveVelo);


			void salvarPersonagem();
			virtual std::string salvar() = 0;
			virtual void executar() = 0;

		};
	}
}