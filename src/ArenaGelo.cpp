#include "../include/ArenaGelo.h"

namespace Fases
{
    ArenaGelo::ArenaGelo(
        Entidades::Personagens::Jogador* jg1,
        Entidades::Personagens::Jogador* jg2,
        bool carregaArquivo
    ) :
        Fase(jg1, jg2, carregaArquivo),
        projeteisThor()
    {
        id = 2;
        caminhoMapa = "assets/mapaArenaGelo.txt";

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
    {
        /*
            Não deletar os projéteis aqui se eles já estão na listaEntidades.
            A listaEntidades.desalocar() da Fase já cuida disso.
        */
        projeteisThor.clear();
    }

    void ArenaGelo::criarProjetil()
    {
        std::ifstream arquivo(caminhoMapa);
        std::string linha;

        if (!arquivo.is_open())
        {
            return;
        }

        int quantidadePosicoesThor = 0;

        while (std::getline(arquivo, linha))
        {
            std::istringstream entrada(linha);

            int tile;

            while (entrada >> tile)
            {
                if (tile == 8)
                {
                    quantidadePosicoesThor++;
                }
            }
        }

        arquivo.close();

        if (quantidadePosicoesThor <= 0)
        {
            return;
        }

        int quantidade = sortearQuantidade(MIN, maxThor);

        if (quantidade > quantidadePosicoesThor)
        {
            quantidade = quantidadePosicoesThor;
        }

        for (int i = 0; i < quantidade; i++)
        {
            Entidades::Projetil* projetil = new Entidades::Projetil();

            projeteisThor.push_back(projetil);

            listaEntidades.inserirNoFim(projetil);
            gC.incluirProjetil(projetil);
        }
    }

    void ArenaGelo::criarThor()
    {
        if (projeteisThor.empty())
        {
            return;
        }

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
                if (tile == 8)
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

        int criados = 0;

        while (!posicoes.empty() && criados < static_cast<int>(projeteisThor.size()))
        {
            int indice = rand() % posicoes.size();

            Entidades::Personagens::Thor* thor =
                new Entidades::Personagens::Thor(
                    posicoes[indice],
                    jogador1,
                    projeteisThor[criados]
                );

            listaEntidades.inserirNoFim(thor);
            gC.incluirInimigo(thor);

            posicoes.erase(posicoes.begin() + indice);
            criados++;
        }
    }

    void ArenaGelo::criarRuna()
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
                /*
                    Na ArenaGelo:
                    5 = Runa

                    Na FlorestaGelo:
                    5 = Espinho

                    Pode usar o mesmo número porque são mapas/fases diferentes.
                */
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

        int criadas = 0;

        while (!posicoes.empty() && criadas < quantidade)
        {
            int indice = rand() % posicoes.size();

            Entidades::Obstaculos::Runa* runa =
                new Entidades::Obstaculos::Runa(
                    posicoes[indice],
                    sf::Vector2f(TAM_TILE, TAM_TILE)
                );

            listaEntidades.inserirNoFim(runa);
            gC.incluirObstaculo(runa);

            posicoes.erase(posicoes.begin() + indice);
            criadas++;
        }
    }

    void ArenaGelo::criarInimigos()
    {
        /*
            Ordem importante:
            primeiro cria os projéteis,
            depois cria os Thor usando esses projéteis.
        */
        criarAndarilhos();
        criarProjetil();
        criarThor();
    }

    void ArenaGelo::criarObstaculo()
    {
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

        controladorEstado(id);
    }
}