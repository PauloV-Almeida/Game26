#pragma once
#include "Jogador.h"
#include <fstream>
#include "Fase.h"
#include "menuEstado.h"
class FimJogo : public menuEstado
{
private:
	Fases::Fase* pFase;
	sf::Text textoNomeJogador;
	int pontuacao;
	std::string nomeJogador;

public:
	FimJogo(Fases::Fase* fase);
	~FimJogo();
	void salvarRanking();
	void carregarBotoes();
	void executar() override;
	void lidarEvent() override;
};