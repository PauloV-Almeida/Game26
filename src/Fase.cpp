#include "../include/Fase.h"

namespace Fases
{
    Fase::Fase(
        int id,
        Entidades::Personagens::Jogador* j1,
        Entidades::Personagens::Jogador* j2,
        const std::string& mapa
    ) :
        Estados::Estado(id),
        pontucaoTotal(0),
        gColisoes(
            j1,
            j2,
            0.f,
            static_cast<float>(MAPA_COLUNAS* TAMANHO_TILE),
            static_cast<float>(MAPA_LINHAS* TAMANHO_TILE),
            0.f
        ),
        pGE(Gerenciadores::GerenciadorEventos::get_instance()),
        listaEntidades(),
        pJog1(j1),
        pJog2(j2),
        caminhoMapa(mapa),
        colisoresMapa(),
        tilesMapa(),
        portalProximaFase(),
        temPortal(false),
        faseConcluida(false)
    {
        if (pJog1)
        {
            listaEntidades.incluir(pJog1);
        }

        if (pJog2)
        {
            listaEntidades.incluir(pJog2);
        }
    }

    Fase::~Fase()
    {
        colisoresMapa.clear();
        tilesMapa.clear();

        pJog1 = nullptr;
        pJog2 = nullptr;
        pGE = nullptr;
    }

    void Fase::criarCenario()
    {
        if (caminhoMapa.empty())
        {
            std::cout << "Caminho do mapa vazio." << std::endl;
            return;
        }

        carregarMapaTXT(caminhoMapa);

        gColisoes.setColisoresMapa(colisoresMapa);
    }

    void Fase::carregarMapaTXT(const std::string& caminho)
    {
        std::ifstream arquivo(caminho);

        if (!arquivo.is_open())
        {
            std::cout << "Erro ao abrir mapa: " << caminho << std::endl;
            return;
        }

        colisoresMapa.clear();
        tilesMapa.clear();

        int valor = 0;

        for (int linha = 0; linha < MAPA_LINHAS; linha++)
        {
            for (int coluna = 0; coluna < MAPA_COLUNAS; coluna++)
            {
                if (!(arquivo >> valor))
                {
                    std::cout << "Erro: mapa terminou antes do esperado." << std::endl;
                    arquivo.close();
                    return;
                }

                sf::Vector2f pos(
                    coluna * TAMANHO_TILE + TAMANHO_TILE / 2.0f,
                    linha * TAMANHO_TILE + TAMANHO_TILE / 2.0f
                );

                tratarElementoMapa(valor, pos);
            }
        }

        arquivo.close();
    }

    void Fase::tratarElementoMapa(int valor, sf::Vector2f pos)
    {
        switch (valor)
        {
        case 0:
            break;

        case 1:
            criarBlocoSolido(pos);
            break;

        case 2:
            criarPlataforma(pos);
            break;

        case 3:
            definirSpawnJogador1(pos);
            break;

        case 4:
            definirSpawnJogador2(pos);
            break;

        case 6:
            posicoesInimigosFaceis.push_back(pos);
            break;

        case 8:
            criarPortal(pos);
            break;

        default:
            break;
        }
    }

    void Fase::criarBlocoSolido(sf::Vector2f pos)
    {
        sf::FloatRect bloco(
            pos.x - TAMANHO_TILE / 2.0f,
            pos.y - TAMANHO_TILE / 2.0f,
            static_cast<float>(TAMANHO_TILE),
            static_cast<float>(TAMANHO_TILE)
        );

        colisoresMapa.push_back(bloco);

        sf::RectangleShape tile(sf::Vector2f(TAMANHO_TILE, TAMANHO_TILE));
        tile.setOrigin(tile.getSize() / 2.0f);
        tile.setPosition(pos);

        tilesMapa.push_back(tile);
    }

    void Fase::criarPlataforma(sf::Vector2f pos)
    {
        Entidades::Obstaculos::Plataforma* plataforma =
            new Entidades::Obstaculos::Plataforma(
                2,
                pos,
                sf::Vector2f(TAMANHO_TILE, TAMANHO_TILE)
            );

        listaEntidades.incluir(plataforma);
        gColisoes.incluirObstaculo(plataforma);
    }

    void Fase::criarAndarilho(sf::Vector2f pos)
    {
        Entidades::Personagens::Andarilho* andarilho =
            new Entidades::Personagens::Andarilho(
                6,
                pos,
                sf::Vector2f(0.f, 0.f),
                sf::Vector2f(TAMANHO_TILE, TAMANHO_TILE),
                pJog1,
                pJog2
            );

        listaEntidades.incluir(andarilho);
        gColisoes.incluirInimigo(andarilho);
    }

    void Fase::criarPortal(sf::Vector2f pos)
    {
        sf::FloatRect novoPortal(
            pos.x - TAMANHO_TILE / 2.0f,
            pos.y - TAMANHO_TILE / 2.0f,
            static_cast<float>(TAMANHO_TILE),
            static_cast<float>(TAMANHO_TILE)
        );

        if (!temPortal)
        {
            portalProximaFase = novoPortal;
            temPortal = true;
        }
        else
        {
            float left = std::min(portalProximaFase.left, novoPortal.left);
            float top = std::min(portalProximaFase.top, novoPortal.top);

            float right = std::max(
                portalProximaFase.left + portalProximaFase.width,
                novoPortal.left + novoPortal.width
            );

            float bottom = std::max(
                portalProximaFase.top + portalProximaFase.height,
                novoPortal.top + novoPortal.height
            );

            portalProximaFase = sf::FloatRect(left, top, right - left, bottom - top);
        }

        sf::RectangleShape tile(sf::Vector2f(TAMANHO_TILE, TAMANHO_TILE));
        tile.setOrigin(tile.getSize() / 2.0f);
        tile.setPosition(pos);

        tilesMapa.push_back(tile);
    }

    void Fase::definirSpawnJogador1(sf::Vector2f pos)
    {
        if (pJog1)
        {
            pJog1->set_posicao(pos);
        }
    }

    void Fase::definirSpawnJogador2(sf::Vector2f pos)
    {
        if (pJog2)
        {
            pJog2->set_posicao(pos);
        }
    }

    void Fase::verificarPortal()
    {
        if (!temPortal)
        {
            return;
        }

        if (pJog1 && pJog1->get_vivo())
        {
            sf::Vector2f pos = pJog1->get_posicao();
            sf::Vector2f tam = pJog1->get_tamanho();

            sf::FloatRect corpoJog(
                pos.x - tam.x / 2.0f,
                pos.y - tam.y / 2.0f,
                tam.x,
                tam.y
            );

            if (corpoJog.intersects(portalProximaFase))
            {
                pJog1->set_venceu(true);
                faseConcluida = true;
            }
        }

        if (pJog2 && pJog2->get_vivo())
        {
            sf::Vector2f pos = pJog2->get_posicao();
            sf::Vector2f tam = pJog2->get_tamanho();

            sf::FloatRect corpoJog(
                pos.x - tam.x / 2.0f,
                pos.y - tam.y / 2.0f,
                tam.x,
                tam.y
            );

            if (corpoJog.intersects(portalProximaFase))
            {
                pJog2->set_venceu(true);
                faseConcluida = true;
            }
        }
    }

    void Fase::desenharMapa()
    {
        for (unsigned int i = 0; i < tilesMapa.size(); i++)
        {
            pGG->desenhar(&tilesMapa[i]);
        }
    }

    void Fase::desenhar()
    {
        desenharMapa();
        listaEntidades.desenhar();
    }

    void Fase::salvar()
    {
        std::ofstream arquivo("./salvar/fase1/fase.txt");

        if (!arquivo.is_open())
        {
            std::cout << "Erro ao salvar fase." << std::endl;
            return;
        }

        for (int i = 0; i < listaEntidades.getTamanho(); i++)
        {
            Entidades::Entidade* ent = listaEntidades[i];

            if (ent)
            {
                ent->salvar(arquivo);
            }
        }

        arquivo.close();
    }

    void Fase::carregarSalvamente()
    {
        std::cout << "carregarSalvamente ainda nao implementado." << std::endl;
    }

    void Fase::reiniciar()
    {
        faseConcluida = false;
    }
}