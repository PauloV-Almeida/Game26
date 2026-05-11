#include "../include/MenuObserver.h"
#include "../include/MainMenu.h"

namespace Observers {
	MenuObserver::MenuObserver() : 
		Observer(),
		pMenu(nullptr)
	{
		pGE->attach(this);
	}
	MenuObserver::~MenuObserver()
	{
		pMenu = nullptr;
	}

	void MenuObserver::executar(sf::Keyboard::Key key_code)
	{
		if (!pMenu)
		{
			return;
		}
		if (pEG->get_AtualEstadoID() == 1 || pEG->get_AtualEstadoID() == 2 ||
			pEG->get_AtualEstadoID() == 5 || pEG->get_AtualEstadoID() == 6)
		{
			if (key_code == sf::Keyboard::Escape)
			{
				pEG->set_AtualEstado(0);
				return;
			}
		}
		if (pEG->get_AtualEstadoID() != 0)
		{
			return;
		}
		if (key_code == sf::Keyboard::Up) { pMenu->moverCima(); }

		if (key_code == sf::Keyboard::Down) { pMenu->moverBaixo(); }

		if (key_code == sf::Keyboard::Enter) { pMenu->selecionar(); }

		if (key_code == sf::Keyboard::Right || key_code == sf::Keyboard::Left) { pMenu->moverHorizontal(1); }

		if (key_code == sf::Keyboard::LControl || key_code == sf::Keyboard::RControl) { pMenu->moverHorizontal(2); }
	}

}