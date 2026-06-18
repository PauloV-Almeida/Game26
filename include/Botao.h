#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Entidades.h"
#include <iostream>
#include <cstdlib>
#include "Acoes.h"
#include "Eventos.h"


namespace Entidades {
	class Button : public Ente
	{
	private:

		mediadorEventos* mediador;
		sf::Text buttonText;
		Actions buttonAction;

	public:
		Button(sf::Vector2f pos, std::string txt = "", Actions action = Actions::NADA);
		~Button();
		virtual void getClicked(sf::Vector2f* mousePos);
		void executar();
	};

}