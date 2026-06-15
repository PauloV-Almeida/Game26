#include "../include/ArenaGelo.h"

namespace Fases
{
    ArenaGelo::ArenaGelo(
        Entidades::Personagens::Jogador* jg1,
        Entidades::Personagens::Jogador* jg2,
        bool carregaArquivo
    ) :
        Fase(jg1, jg2, carregaArquivo)
    {
        id = 2;
        caminhoMapa = "../assents/mapaArenaGelo.txt";

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

    ArenaGelo::~ArenaGelo()
    {}

    void ArenaGelo::criarThor()
    {
        int quantidade = sortearQuantidade(MIN, maxThor);

        for (int i = 0; i < quantidade; i++)
        {
            Entidades::Projetil* projetil = new Entidades::Projetil();

            Entidades::Personagens::Thor* thor =
                new Entidades::Personagens::Thor(
                    sf::Vector2f(900.f + i * 420.f, 250.f),
                    jogador1,
                    jogador2Ativo ? jogador2 : nullptr
                );

            thor->setProjetilAtual(projetil);

            listaEntidades.inserirNoFim(thor);
            listaEntidades.inserirNoFim(projetil);

            gC.incluirInimigo(thor);
            gC.incluirProjetil(projetil);
        }
    }

    void ArenaGelo::criarRuna()
    {
        int quantidade = sortearQuantidade(MIN, MAX);

        for (int i = 0; i < quantidade; i++)
        {
            Entidades::Obstaculos::Runa* runa =
                new Entidades::Obstaculos::Runa(
                    sf::Vector2f(700.f + i * 300.f, 580.f),
                    sf::Vector2f(TAM_TILE, TAM_TILE)
                );

            listaEntidades.inserirNoFim(runa);
            gC.incluirObstaculo(runa);
        }
    }

    void ArenaGelo::criarProjetil()
    {
        /*
            Como cada Thor precisa de um projétil próprio,
            o projétil está sendo criado dentro de criarThor().

            Esse método pode ser apagado depois do .h e do .cpp,
            se você não for usá-lo separadamente.
        */
    }

    void ArenaGelo::criarInimigos()
    {
        /*
            Andarilho vem da Fase base.
            Thor/Boss é específico da ArenaGelo.
        */
        criarAndarilhos();
        criarThor();
    }

    void ArenaGelo::criarObstaculo()
    {
        /*
            Plataforma vem da Fase base.
            Runa é específica da ArenaGelo.
        */
        criarPlataformas();
        criarRuna();
    }

    void ArenaGelo::executar()
    {
        lidarEvent();

        listaEntidades.executar();
        gC.executar();

        executarJanela();

        listaEntidades.desenhar();

        hub.executar();
        hub.draw();

        controladorEstado(2);
    }
}