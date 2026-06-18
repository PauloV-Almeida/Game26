#include "../include/MenuRanking.h"

#include <map>
#include <vector>
#include <sstream>

MenuRanking::MenuRanking() :
    menuEstado(),
    textoRanking()
{
    carregarBotoes();

    textoRanking.setPosition(250.f, 180.f);
    textoRanking.setCharacterSize(32);
    textoRanking.setFont(*(pGG->getFont()));
    textoRanking.setFillColor(sf::Color::White);

    carregarRanking();
}

MenuRanking::~MenuRanking()
{}

void MenuRanking::carregarBotoes()
{
    botaoVector.push_back(
        new Entidades::Button(
            sf::Vector2f(50.f, 100.f),
            "Voltar",
            Actions::VOLTAR_1_MENU
        )
    );
}

void MenuRanking::executar()
{
    pGG->limpar();

    setFigura(&fundoMenu);
    desenhar();

    lidarEvent();
    execBotoes();

    setFigura(&textoRanking);
    desenhar();
}

void MenuRanking::carregarRanking()
{
    std::ifstream arquivo("salvar/ranking.txt");
    std::multimap<int, std::string> ranking;

    if (arquivo.is_open())
    {
        std::string nome;
        int pontos;

        while (arquivo >> nome >> pontos)
        {
            ranking.insert({ pontos, nome });
        }

        arquivo.close();
    }

    std::stringstream texto;

    texto << "RANKING\n\n";

    int count = 0;

    for (auto it = ranking.rbegin(); it != ranking.rend() && count < 5; ++it)
    {
        texto << count + 1 << ". "
            << it->second
            << " - "
            << it->first
            << " pontos\n";

        count++;
    }

    if (count == 0)
    {
        texto << "Nenhum ranking salvo ainda.";
    }

    textoRanking.setString(texto.str());
}