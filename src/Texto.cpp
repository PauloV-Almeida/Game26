#include "../include/Texto.h"

namespace Menus
{
	Gerenciadores::GerenciadorGrafico* Texto::pGG(Gerenciadores::GerenciadorGrafico::get_instance());

	Texto::Texto(std::string n)
	{
		text.setString(n);
		text.setFont(*pGG->getFonte());
		text.setCharacterSize(30);
		text.setOrigin(15.f, 15.f);
		text.setPosition(sf::Vector2f(100.f, 25.f));
		text.setFillColor(sf::Color::White);
		text.setOutlineThickness(2.f);
		text.setOutlineColor(sf::Color::Black);
	}
	Texto::~Texto()
	{
	}

	void Texto::setPosicao(sf::Vector2f posicao)
	{
		text.setPosition(posicao);
	}

	void Texto::setTamanho(int tamanho)
	{
		text.setCharacterSize(tamanho);
	}

	void Texto::setNome(std::string n)
	{
		text.setString(n);
	}

	void Texto::desenhar()
	{
		pGG->desenhar(&text);
	}

	void Texto::setCor(int c)
	{
		if (c == 0)
			text.setFillColor(sf::Color(255, 165, 0));
	}
}