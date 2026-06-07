#include "../include/MenuSelecionar.h"

MenuSelecionar::MenuSelecionar()
	:menuEstado()
{
	carregarBotoes();
}

MenuSelecionar::~MenuSelecionar()
{

}

void MenuSelecionar::carregarBotoes() {
	botaoVector.push_back(new Entidades::Button(sf::Vector2f(50.f, 100.f), "Voltar", Actions::VOLTAR_1_MENU));
	botaoVector.push_back(new Entidades::Button(sf::Vector2f(200.f, 300.f), "Fase 1", Actions::FASE_1));
	botaoVector.push_back(new Entidades::Button(sf::Vector2f(200.f, 400.f), "Fase 2", Actions::FASE_2));
}