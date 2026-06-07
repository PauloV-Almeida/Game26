#pragma once
#include "menuEstado.h"


class MenuPrincipal : public menuEstado
{
private:
	sf::Color cor;
public:

	MenuPrincipal();
	~MenuPrincipal();
	void carregarBotoes();

};