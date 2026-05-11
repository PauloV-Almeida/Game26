#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "Ente.h"
#include "GerenciadorEventos.h"
#include "MenuObserver.h"
#include "Botao.h"
#include "Texto.h"
#include "Estado.h"

namespace Menus
{
	class Menu : public Ente, public Estados::Estado
	{
	protected:
		const int MAX_BOTOES;
		std::vector<Botao*> botoes;
		int selecionar_Indice;
		sf::RectangleShape corpo;
		Texto titulo;
	public:
		Menu(int n_botoes = 0, int id = -1, std::string t = "0");
		~Menu();
		virtual void desenhar();
		void moverCima();
		void moverBaixo();
		virtual void selecionar() = 0;
		void executar();
		void mudarNome(std::string nm);
	};
}