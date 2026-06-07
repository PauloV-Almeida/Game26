#pragma once
#include "Ente.h"
#include "sstream"
#include "Jogador.h"
class Hub : public Ente
{
private:
	Entidades::Personagens::Jogador* jogador2;
	Entidades::Personagens::Jogador* jogador;
	sf::Text hub;
public:
	Hub();
	~Hub();
	void setPlayer2(Entidades::Personagens::Jogador* jogador);
	void setPlayer(Entidades::Personagens::Jogador* jogador);
	void draw();
	void executar();


};