#pragma once
#include "menuEstado.h"

class MenuSelecionar: public menuEstado
{
private:
	sf::Color cor;
public:

	MenuSelecionar();
	~MenuSelecionar();
	void carregarBotoes();
};