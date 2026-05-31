#include "../include/Ragnarok.h"

Ragnarok::Ragnarok() :
    pGG(Gerenciadores::GerenciadorGrafico::get_instance()),
    pGE(Gerenciadores::GerenciadorEventos::get_instance()),
    pGEst(Gerenciadores::GerenciadorEstado::get_instance())
{
    using namespace Entidades::Personagens;

    pGEst->add_estado(new Menus::MainMenu());

    pGEst->add_estado(
        new Fases::FlorestaGelo(
            1,
            new Jogador(
                1,
                sf::Vector2f(100.f, 100.f),
                sf::Vector2f(0.f, 0.f),
                sf::Vector2f(32.f, 32.f)
            )
        )
    );

    pGEst->add_estado(
        new Fases::FlorestaGelo(
            6,
            new Jogador(
                1,
                sf::Vector2f(100.f, 100.f),
                sf::Vector2f(0.f, 0.f),
                sf::Vector2f(32.f, 32.f)
            ),
            new Jogador(
                2,
                sf::Vector2f(140.f, 100.f),
                sf::Vector2f(0.f, 0.f),
                sf::Vector2f(32.f, 32.f)
            )
        )
    );

    executar();
}

Ragnarok::~Ragnarok()
{}

void Ragnarok::executar()
{
    while (pGG->abreJanela())
    {
        pGG->limpar();

        pGE->executar();

        pGEst->executar();

        pGG->mostrar();
    }
}