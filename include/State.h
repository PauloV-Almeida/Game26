#pragma once
#include <SFML/Graphics.hpp>
#include "Ente.h"
#include "Acoes.h"
#include "Eventos.h"


class State : public Ente
{
protected:
	sf::View* view;
	mediadorEventos* mediador;
	
public:
	State();
	virtual ~State();
	virtual void lidarEvent() = 0;
	virtual void executar() = 0;

};