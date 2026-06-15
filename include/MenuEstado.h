#pragma once
#include "State.h"
#include "Botao.h"
#include <vector>
class menuEstado : public State
{
protected:
	std::vector<Entidades::Button*> botaoVector;
	sf::Sprite fundoMenu;
public:
	virtual ~menuEstado();
	menuEstado();

	virtual void carregarBotoes() = 0;
	void execBotoes();
	void mouseClick();

	virtual void lidarEvent();
	virtual void executar();

};