#include "../include/FlorestaGelo.h"

namespace Fases
{
    FlorestaGelo::FlorestaGelo(int idEstado,
        Entidades::Personagens::Jogador* j1,
        Entidades::Personagens::Jogador* j2
    ) :
        Fase(
            1,
            j1,
            j2,
            "./assets/mapas/mapaFloGelo.txt"
        ),
        minInimigos(3),
        maxInimigos(6),
        minEspinhos(3),
        maxEspinhos(5),
        posicoesValkirias(),
        posicoesEspinhos()
    {
        criarCenario();

        criarInimigos();
        criarObstaculos();
    }

    FlorestaGelo::~FlorestaGelo()
    {}

    void FlorestaGelo::tratarElementoMapa(int valor, sf::Vector2f pos)
    {
        Fase::tratarElementoMapa(valor, pos);

        switch (valor)
        {
        case 5:
            posicoesEspinhos.push_back(pos);
            break;

        case 7:
            posicoesValkirias.push_back(pos);
            break;

        default:
            break;
        }
    }

    void FlorestaGelo::criarEspinhoVenenoso(sf::Vector2f pos)
    {
        Entidades::Obstaculos::EspinhoVenenoso* espinho =
            new Entidades::Obstaculos::EspinhoVenenoso(
                5,
                pos,
                sf::Vector2f(TAMANHO_TILE, TAMANHO_TILE)
            );

        listaEntidades.incluir(espinho);
        gColisoes.incluirObstaculo(espinho);
    }

    void FlorestaGelo::criarValkiria(sf::Vector2f pos)
    {
        Entidades::Personagens::Valkiria* valkiria =
            new Entidades::Personagens::Valkiria(
                7,
                pos,
                sf::Vector2f(0.f, 0.f),
                sf::Vector2f(TAMANHO_TILE, TAMANHO_TILE),
                pJog1,
                pJog2
            );

        listaEntidades.incluir(valkiria);
        gColisoes.incluirInimigo(valkiria);
    }

    void FlorestaGelo::criarInimigos()
    {
        struct SpawnInimigo
        {
            int tipo;
            sf::Vector2f pos;
        };

        std::vector<SpawnInimigo> spawnsPossiveis;

        for (unsigned int i = 0; i < posicoesInimigosFaceis.size(); i++)
        {
            SpawnInimigo spawn;
            spawn.tipo = 6;
            spawn.pos = posicoesInimigosFaceis[i];

            spawnsPossiveis.push_back(spawn);
        }

        for (unsigned int i = 0; i < posicoesValkirias.size(); i++)
        {
            SpawnInimigo spawn;
            spawn.tipo = 7;
            spawn.pos = posicoesValkirias[i];

            spawnsPossiveis.push_back(spawn);
        }

        if (spawnsPossiveis.empty())
        {
            std::cout << "Nenhuma posicao de inimigo encontrada no mapa." << std::endl;
            return;
        }

        std::random_device rd;
        std::mt19937 gerador(rd());

        std::shuffle(spawnsPossiveis.begin(), spawnsPossiveis.end(), gerador);

        int qtdMaximaPossivel = static_cast<int>(spawnsPossiveis.size());

        int minimo = minInimigos;
        int maximo = maxInimigos;

        if (qtdMaximaPossivel < minimo)
        {
            minimo = qtdMaximaPossivel;
        }

        if (qtdMaximaPossivel < maximo)
        {
            maximo = qtdMaximaPossivel;
        }

        std::uniform_int_distribution<int> sorteioQuantidade(minimo, maximo);

        int quantidadeCriar = sorteioQuantidade(gerador);

        for (int i = 0; i < quantidadeCriar; i++)
        {
            if (spawnsPossiveis[i].tipo == 6)
            {
                criarAndarilho(spawnsPossiveis[i].pos);
            }
            else if (spawnsPossiveis[i].tipo == 7)
            {
                criarValkiria(spawnsPossiveis[i].pos);
            }
        }
    }

    void FlorestaGelo::criarObstaculos()
    {
        if (posicoesEspinhos.empty())
        {
            std::cout << "Nenhuma posicao de espinho encontrada no mapa." << std::endl;
            return;
        }

        std::random_device rd;
        std::mt19937 gerador(rd());

        std::shuffle(posicoesEspinhos.begin(), posicoesEspinhos.end(), gerador);

        int qtdMaximaPossivel = static_cast<int>(posicoesEspinhos.size());

        int minimo = minEspinhos;
        int maximo = maxEspinhos;

        if (qtdMaximaPossivel < minimo)
        {
            minimo = qtdMaximaPossivel;
        }

        if (qtdMaximaPossivel < maximo)
        {
            maximo = qtdMaximaPossivel;
        }

        std::uniform_int_distribution<int> sorteioQuantidade(minimo, maximo);

        int quantidadeCriar = sorteioQuantidade(gerador);

        for (int i = 0; i < quantidadeCriar; i++)
        {
            criarEspinhoVenenoso(posicoesEspinhos[i]);
        }
    }

    void FlorestaGelo::executar()
    {

        listaEntidades.executar();

        gColisoes.executar();

        verificarPortal();

        desenhar();
    }
}