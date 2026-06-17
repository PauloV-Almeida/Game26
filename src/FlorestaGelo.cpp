#include "../include/FlorestaGelo.h"

namespace Fases
{
    FlorestaGelo::FlorestaGelo(
        Entidades::Personagens::Jogador* jg1,
        Entidades::Personagens::Jogador* jg2,
        bool carregaArquivo
    ) :
        Fase(jg1, jg2, carregaArquivo)
    {
        id = 1;
        caminhoMapa = "assets/mapaFloGelo.txt";

        if (carregaArquivo)
        {
            carregarSalvamento();
        }
        else
        {
            criarCenario();
            carregamentoPadrao();
        }
    }

    FlorestaGelo::~FlorestaGelo()
    {}

    void FlorestaGelo::criarValkiria()
    {
        int quantidade = sortearQuantidade(MIN, maxValkiria);

        for (int i = 0; i < quantidade; i++)
        {
            Entidades::Personagens::Valkiria* valkiria =
                new Entidades::Personagens::Valkiria(
                    sf::Vector2f(900.f + i * 320.f, 300.f),
                    jogador1,
                    jogador2Ativo ? jogador2 : nullptr
                );

            listaEntidades.inserirNoFim(valkiria);
            gC.incluirInimigo(valkiria);
        }
    }

    void FlorestaGelo::criarEspinhoVenenoso()
    {
        int quantidade = sortearQuantidade(MIN, MAX);

        for (int i = 0; i < quantidade; i++)
        {
            Entidades::Obstaculos::EspinhoVenenoso* espinho =
                new Entidades::Obstaculos::EspinhoVenenoso(
                    sf::Vector2f(800.f + i * 256.f, 650.f),
                    sf::Vector2f(TAM_TILE, TAM_TILE)
                );

            listaEntidades.inserirNoFim(espinho);
            gC.incluirObstaculo(espinho);
        }
    }

    void FlorestaGelo::criarInimigos()
    {
        /*
            Andarilho vem da Fase base.
            Valkiria é específica da FlorestaGelo.
        */
        criarAndarilhos();
        criarValkiria();
    }

    void FlorestaGelo::criarObstaculo()
    {
        /*
            Plataforma vem da Fase base.
            EspinhoVenenoso é específico da FlorestaGelo.
        */
        criarPlataformas();
        criarEspinhoVenenoso();
    }

    void FlorestaGelo::executar()
    {
        lidarEvent();

        listaEntidades.executar();
        gC.executar();

        executarJanela();

        listaEntidades.desenhar();

        hub.executar();
        hub.draw();

        controladorEstado(id);
    }
}