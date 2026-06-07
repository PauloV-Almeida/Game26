#include "../include/Obstaculo.h"
namespace Entidades {
	namespace Obstaculos {
		Obstaculo::Obstaculo(sf::Vector2f pos)
			:Entidade(pos)
		{
			colidivel = 1;
			danoso = 0;
		}

		Obstaculo::Obstaculo()
		{
			colidivel = 1;
			danoso = 0;
		}

		Obstaculo::~Obstaculo()
		{}

		const bool Obstaculo::ehColidivel()
		{
			return colidivel;
		}

		void Obstaculo::salvarObstaculo()
		{
			salvarEntidade();
		}

	}
}