#pragma once

#include "Jogador.h"
#include "Fase.h"
#include "menuEstado.h"

#include <fstream>
#include <sstream>
#include <string>

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