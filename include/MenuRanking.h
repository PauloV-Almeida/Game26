#pragma once
#include "menuEstado.h"
#include <fstream>
class MenuRanking : public menuEstado
{
private:
	sf::Text textoRanking;
public:
	MenuRanking();
	~MenuRanking();
	void executar() override;
	void carregarBotoes();
	void carregarRanking();
};