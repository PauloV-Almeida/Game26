#pragma once

#include "FlorestaGelo.h"
#include "GerenciadorGrafico.h"
#include "GerenciadorEventos.h"
#include "GerenciadorEstado.h"
#include "MainMenu.h"
#include "Jogador.h"

class Ragnarok
{
private:
    Gerenciadores::GerenciadorGrafico* pGG;
    Gerenciadores::GerenciadorEventos* pGE;
    Gerenciadores::GerenciadorEstado* pGEst;

public:
    Ragnarok();
    ~Ragnarok();

    void executar();
};