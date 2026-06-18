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
        std::ifstream arquivo(caminhoMapa);
        std::string linha;

        if (!arquivo.is_open())
        {
            return;
        }

        std::vector<sf::Vector2f> posicoes;

        int y = 0;

        while (std::getline(arquivo, linha))
        {
            std::istringstream entrada(linha);

            int tile;
            int x = 0;

            while (entrada >> tile)
            {
                if (tile == 7)
                {
                    posicoes.push_back(
                        sf::Vector2f(TAM_TILE * x, TAM_TILE * y)
                    );
                }

                x++;
            }

            y++;
        }

        arquivo.close();

        if (posicoes.empty())
        {
            return;
        }

        int quantidade = sortearQuantidade(MIN, maxValkiria);

        int criadas = 0;

        while (!posicoes.empty() && criadas < quantidade)
        {
            int indice = rand() % posicoes.size();

            Entidades::Personagens::Valkiria* valkiria =
                new Entidades::Personagens::Valkiria(
                    posicoes[indice],
                    jogador1
                );

            listaEntidades.inserirNoFim(valkiria);
            gC.incluirInimigo(valkiria);

            posicoes.erase(posicoes.begin() + indice);
            criadas++;
        }
    }

    void FlorestaGelo::criarEspinhoVenenoso()
    {
        std::ifstream arquivo(caminhoMapa);
        std::string linha;

        if (!arquivo.is_open())
        {
            return;
        }

        std::vector<sf::Vector2f> posicoes;

        int y = 0;

        while (std::getline(arquivo, linha))
        {
            std::istringstream entrada(linha);

            int tile;
            int x = 0;

            while (entrada >> tile)
            {
                if (tile == 5)
                {
                    posicoes.push_back(
                        sf::Vector2f(TAM_TILE * x, TAM_TILE * y)
                    );
                }

                x++;
            }

            y++;
        }

        arquivo.close();

        if (posicoes.empty())
        {
            return;
        }

        int quantidade = sortearQuantidade(MIN, MAX);

        int criados = 0;

        while (!posicoes.empty() && criados < quantidade)
        {
            int indice = rand() % posicoes.size();

            Entidades::Obstaculos::EspinhoVenenoso* espinho =
                new Entidades::Obstaculos::EspinhoVenenoso(
                    posicoes[indice],
                    sf::Vector2f(TAM_TILE, TAM_TILE)
                );

            listaEntidades.inserirNoFim(espinho);
            gC.incluirObstaculo(espinho);

            posicoes.erase(posicoes.begin() + indice);
            criados++;
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