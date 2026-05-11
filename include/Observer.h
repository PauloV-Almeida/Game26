#pragma once

#include "GerenciadorEventos.h"
#include "GerenciadorEstado.h"
#include "GerenciadorGrafico.h"

#include <SFML/Graphics.hpp>

namespace Observers
{
	class Observer
	{
	protected:
		Gerenciadores::GerenciadorEventos* pGE;
		Gerenciadores::GerenciadorEstado* pEG;
		Gerenciadores::GerenciadorGrafico* pGG;

	public:
		Observer();
		virtual ~Observer();

		virtual void executar(sf::Keyboard::Key key_code) = 0;
	};
}