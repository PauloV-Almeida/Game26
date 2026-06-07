#include "../include/Hub.h"


Hub::Hub()
{
	
	jogador = nullptr;
	jogador2 = nullptr;
	hub.setFont(*(pGG->getFont()));

	hub.setCharacterSize(30);
	setFigura(&hub);
}

Hub::~Hub()
{}

void Hub::setPlayer2(Entidades::Personagens::Jogador* jogador)
{
	jogador2 = jogador;
}

void Hub::setPlayer(Entidades::Personagens::Jogador* jogador)
{
	
	this->jogador = jogador;
}

void Hub::draw()
{
	
	pGG->setView(sf::View(pGG->getPadraoView()));

	desenhar();
}

void Hub::executar()
{
	std::stringstream ss;

	if (jogador2) {
		ss << "Jogador 1:" << "\nVida:" << jogador->getVidas() << "\nJogador 2:" << "\n Vida:" << jogador2->getVidas() << "\nPontos :" << jogador->getPontos() + jogador2->getPontos();
	}
	else {
		ss << "\nVida:" << jogador->getVidas() << "\nPontos :" << jogador->getPontos();
	}
	hub.setString(ss.str());

}