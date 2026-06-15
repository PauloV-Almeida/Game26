#pragma once

#include "menuEstado.h"
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

class MenuRanking : public menuEstado
{
private:
    sf::Text textoRanking;

public:
    MenuRanking();
    ~MenuRanking();

    void executar() override;
    void carregarBotoes();
    void carregarRanking();
};