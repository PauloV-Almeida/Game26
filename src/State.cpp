#include "../include/State.h"
State::State()
	:Ente()
{

	mediador = mediadorEventos::getMediadorEventos();
	view = new sf::View(sf::FloatRect(0, 0, 1280, 720));
	pGG->setView(*view);
}

State::~State() {
	delete view;
}