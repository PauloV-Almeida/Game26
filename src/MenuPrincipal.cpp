#include "../include/MenuPrincipal.h"

MenuPrincipal::MenuPrincipal()
	:menuEstado()
{
	carregarBotoes();
}

MenuPrincipal::~MenuPrincipal()
{}

void MenuPrincipal::carregarBotoes() {
	botaoVector.push_back(new Entidades::Button(sf::Vector2f(200.f, 425.f), "Novo Jogo ", Actions::SELECIONAR_FASE));
	botaoVector.push_back(new Entidades::Button(sf::Vector2f(200.f, 525.f), "Continuar", Actions::CARREGAR_SAVE));
	botaoVector.push_back(new Entidades::Button(sf::Vector2f(700, 425.f), "Ranking", Actions::MENU_RANKING));
	botaoVector.push_back(new Entidades::Button(sf::Vector2f(700.f, 525.f), "Sair", Actions::VOLTAR_1_MENU));
}