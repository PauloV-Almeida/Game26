#pragma once

#include "GerenciadorGrafico.h"
#include "GerenciadorEstado.h"
#include "Jogador.h"

class Ragnarok
{
private:
    Gerenciadores::GerenciadorGrafico* pGG;
    Gerenciadores::GerenciadorEstado* pGEst;

    Entidades::Personagens::Jogador* jogador1;
    Entidades::Personagens::Jogador* jogador2;

public:
    Ragnarok();
    ~Ragnarok();

    void executar();
};