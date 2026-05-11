#pragma once

#include "../stdafx/stdafx.h"
#include "GerenciadorGrafico.h"

#define GRAVIDADE 0.3
#define VELOCIDADE 0.1
#define VEL_MAX 5.0

class Ente
{
protected:

    const int id;
    static Gerenciadores::GerenciadorGrafico* pGG;
    sf::Texture* texturas;
public:
    Ente();
    virtual ~Ente();

    virtual void desenhar() = 0;

    virtual void executar() = 0;
};