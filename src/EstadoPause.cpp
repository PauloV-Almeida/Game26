#include "../include/EstadoPause.h"
EstadoPause::EstadoPause(Fases::Fase* pfase)
	:fase(pfase)
{
	carregarBotoes();
}

EstadoPause::~EstadoPause() {

}
void EstadoPause::carregarBotoes() {
	botaoVector.push_back(new Entidades::Button(sf::Vector2f(300.f, 300.f), "Voltar ao Jogo", Actions::VOLTAR_1_MENU));
	botaoVector.push_back(new Entidades::Button(sf::Vector2f(300.f, 500.f), "Sair do jogo", Actions::VOLTAR_2_MENUS));
	botaoVector.push_back(new Entidades::Button(sf::Vector2f(300.f, 400.f), "Salvar", Actions::SALVAR));

}