#pragma once
#include "Obstaculo.h"

namespace Entidades {
	namespace Obstaculos {
		class EspinhoVenenoso : public Obstaculo
		{
		private:
			sf::Clock danoRelogio;
			float danoCooldown;
			float altura;
		public:
			EspinhoVenenoso(sf::Vector2f pos, float altura = 1);
			EspinhoVenenoso();
			~EspinhoVenenoso();
			void setAltura(float alt);
			const float getDanoCooldown() const;
			const float getDanoRelogio() const;
			void obstacular(Personagens::Jogador* pJogador);
			void executar();
			std::string salvar();
			void salvarEspinho();
		};

	}
}