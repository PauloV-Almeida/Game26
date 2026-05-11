#include "../include/Menu.h"

namespace Menus
{
	Menu::Menu(int n_botoes, int id, std::string t) :
		Ente(),
		Estado(id),
		MAX_BOTOES(n_botoes),
		selecionar_Indice(0),
		titulo(t)
	{
		for (int i = 0; i < MAX_BOTOES; i++)
		{
			botoes.push_back(new Botao(sf::Vector2f(LARGURA/2, (i+2)*(20 + TAM_Y))));
		}
		botoes[0]->escolherCor();

		corpo.setSize(sf::Vector2f(800.f , 600.f));
		texturas = pGG->carregar_texturas("./assets/imgMenu.png");
		corpo.setTexture(texturas);
	}
	Menu::~Menu()
	{
		for (int i = 0; i < MAX_BOTOES; i++)
		{
			delete botoes[i];
		}
	}
	void Menu::desenhar()
	{
		for(int i = 0; i < MAX_BOTOES; i++)
		{
			botoes[i]->desenhar();
		}
	}
	void Menu::moverCima()
	{
		if (selecionar_Indice > 0)
		{
			botoes[selecionar_Indice]->escolherCor();
			selecionar_Indice--;
			botoes[selecionar_Indice]->escolherCor();
		}
	}
	void Menu::moverBaixo()
	{
		if (selecionar_Indice < MAX_BOTOES - 1)
		{
			botoes[selecionar_Indice]->escolherCor();
			selecionar_Indice++;
			botoes[selecionar_Indice]->escolherCor();
		}
	}

	void Menu::executar()
	{
		desenhar();
	}
	void Menu::mudarNome(std::string nm)
	{
		titulo.setNome(nm);
	}

}