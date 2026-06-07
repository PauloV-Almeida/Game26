#include "../include/Personagem.h"
#include "../include/Obstaculo.h"

namespace Entidades {
	namespace Personagens {
		Personagem::Personagem()
			:Entidade()
		{
			maxVelo = 6;
			moveVelo = 3;
			pulo = 2;
			vida = 10;
			vel.x = 0;
			vel.y = 0;
		}

		Personagem::Personagem(sf::Vector2f pos)
			:Entidade(pos)
		{
			
			maxVelo = 6;
			moveVelo = 3;
			pulo = 2;
			vida = 10;
			vel.x = 0;
			vel.y = 0;
			
			setFigura(&forma);
		}

		Personagem::~Personagem()
		{
			
		}

		const bool Personagem::vivo() const
		{
			return (vida > 0);
		}
		
		void Personagem::setVida(int nvida)
		{
			vida = nvida;
		}
		void Personagem::setPulos(int pulos)
		{
			pulo = pulos;
		}
		
		const int Personagem::getVidas() const
		{
			return vida;
		}


		void Personagem::tiraVida(int dano)
		{
			vida -= dano;
		}
		void Personagem::setMoveVelocidade(float moveVel)

		{
			this->moveVelo = moveVel;
		}

		void Personagem::salvarPersonagem()
		{
			salvarEntidade();
			buffer << vida << " ";
			buffer << pulo << " ";
		}

		void Personagem::executar() {
			mover();
		}

	}
}