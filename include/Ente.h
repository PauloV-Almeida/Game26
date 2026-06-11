#pragma once

#include "../stdafx/stdafx.h"
#include "GerenciadorGrafico.h"
#include "Id.h"

#define GRAVIDADE 9.8f

class Ente
{
protected:
    sf::Clock clock;
    Id id;
    static Gerenciadores::GerenciadorGrafico* pGG;
    sf::Drawable* figura;
public:
    Ente();
    virtual ~Ente();
    virtual void executar() = 0;
    virtual void desenhar();

	Id getId();
	sf::Drawable* getFigura();

	void setFigura(sf::Drawable* figura);
};