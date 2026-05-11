#include "../include/GerenciadorEventos.h"
#include "../include/Observer.h"

namespace Gerenciadores {
	GerenciadorEventos* GerenciadorEventos::instance = nullptr;

	GerenciadorEventos* GerenciadorEventos::get_instance() {
		if (instance == nullptr) {
			instance = new GerenciadorEventos();
		}
		return instance;
	}

	GerenciadorEventos::GerenciadorEventos() : Subject()
	{
		pGG = GerenciadorGrafico::get_instance();
	}

	GerenciadorEventos::~GerenciadorEventos() {

	}

	void GerenciadorEventos::executar()
	{
		sf::Event event;

		while (pGG->get_janela()->pollEvent(event)) {
			if (event.type == sf::Event::KeyPressed)
			{
				notify((event.key.code));
			}
			else if (event.type == sf::Event::Closed)
			{
				pGG->fechaJanela();
			}

		}
	}

}