#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Menu.h"

namespace Menus
{
	class MainMenu : public Menu
	{
	private:
		Observers::MenuObserver* pMenuObserver;
		int AtualFase;
		int AtualJogador;
		Texto Fase1;
		Texto Fase2;
		Texto Jogador1;
		Texto Jogador2;
	public:
		MainMenu();
		~MainMenu();
		void selecionar();
		void moverHorizontal(int i);
		void desenhar();
	};
}
