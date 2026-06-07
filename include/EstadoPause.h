#pragma once
#include "menuEstado.h"
#include "Fase.h"


class EstadoPause : public menuEstado
{
private:
	Fases::Fase* fase;
public:
	EstadoPause(Fases::Fase* pFase);
	~EstadoPause();
	void carregarBotoes();
};