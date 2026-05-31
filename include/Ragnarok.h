#pragma once  

#include <SFML/Graphics.hpp>

#include "FlorestaGelo.h"
#include "GerenciadorGrafico.h"
#include "GerenciadorEventos.h"
#include "GerenciadorEstado.h"
#include "MainMenu.h"


class Ragnarok
{
private:
	Gerenciadores::GerenciadorGrafico* pGG;
	Gerenciadores::GerenciadorEventos* pGE;
	Gerenciadores::GerenciadorEstado* pGEst;
	Menus::MainMenu main_menu;
public:
	Ragnarok();
	~Ragnarok();

	void executar();
};