#include "../include/EspinhoVenenoso.h"

namespace Entidades {
	namespace Obstaculos {
		EspinhoVenenoso::EspinhoVenenoso(sf::Vector2f pos, float altura)
			:Obstaculo(pos) {
			id = Id::Espinho;
			this->altura = altura;
			danoso = 1;
			danoRelogio.restart();
			danoCooldown = 0.5;
			colidivel = 0;
			forma.setTexture(*pGG->getTextura(Texturas::espinho));
			forma.setTextureRect(sf::IntRect(127, 46, 100, 80));
			forma.setScale(1, 1 * altura);
		}
		EspinhoVenenoso::EspinhoVenenoso()
			:Obstaculo()
		{
			altura = 1;
			danoso = 1;
			danoCooldown = 0.5;
			colidivel = 0;
		}
		EspinhoVenenoso::~EspinhoVenenoso()
		{}

		void EspinhoVenenoso::setAltura(float alt)
		{
			altura = alt;
			forma.setScale(1, 1 * altura);
		}

		const float EspinhoVenenoso::getDanoCooldown() const
		{
			return danoCooldown;
		}
		const float EspinhoVenenoso::getDanoRelogio() const {
			return danoRelogio.getElapsedTime().asSeconds();
		}

		void EspinhoVenenoso::executar() {
			mover();
		}

		std::string EspinhoVenenoso::salvar()
		{
			salvarEspinho();
			return buffer.str();
		}
		void EspinhoVenenoso::salvarEspinho()
		{
			salvarObstaculo();
			buffer << altura;
		}

		void EspinhoVenenoso::obstacular(Personagens::Jogador* pJogador) {

			if (pJogador->getTipo() == TipoPersonagem::PLAYER) {
				if (getDanoRelogio() > getDanoCooldown()) {
					danoRelogio.restart();
					pJogador->tiraVida(1);
				}
			}
		}
	}
}