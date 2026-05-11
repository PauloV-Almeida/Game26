#pragma once

#include <SFML/Graphics.hpp>

#include "GerenciadorGrafico.h"

#define TAM_X 600.f
#define TAM_Y 80.f

namespace Menus {
	class Botao
	{
	private:
		sf::RectangleShape corpo;
		sf::Text text;
		static Gerenciadores::GerenciadorGrafico* pGG;
	public:
		Botao(sf::Vector2f posicao = sf::Vector2f(0.f, 0.f));
		~Botao();
		void desenhar();
		void escolherCor();
		void setNome(std::string nome);
		void setPosicao(sf::Vector2f posicao);
	};


}