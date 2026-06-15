#include "../include/Ragnarok.h"

Ragnarok::Ragnarok() :
    pGG(Gerenciadores::GerenciadorGrafico::get_instance()),
    pGEst(nullptr),
    jogador1(nullptr),
    jogador2(nullptr)
{
    jogador1 = new Entidades::Personagens::Jogador(
        1,
        sf::Vector2f(100.f, 100.f)
    );

    jogador2 = new Entidades::Personagens::Jogador(
        2,
        sf::Vector2f(140.f, 100.f)
    );

    pGEst = new Gerenciadores::GerenciadorEstado(jogador1, jogador2);
}

Ragnarok::~Ragnarok()
{
    if (pGEst)
    {
        delete pGEst;
        pGEst = nullptr;
    }

    /*
        Os jogadores entram na ListaEntidades da fase.
        Então cuidado para não deletar duas vezes.
        Se a ListaEntidades desalocar os jogadores, não delete aqui.
    */
    jogador1 = nullptr;
    jogador2 = nullptr;
}

void Ragnarok::executar()
{
    while (pGG->estaAberto())
    {
        pGG->limpar();

        pGEst->executar();

        pGG->mostrar();
    }
}