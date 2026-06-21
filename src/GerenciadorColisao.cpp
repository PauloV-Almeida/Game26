#include "../include/GerenciadorColisao.h"

#include <algorithm>

namespace Gerenciadores
{
    GerenciadorColisao::GerenciadorColisao() :
        inimigos(),
        obstaculos(),
        projeteis(),
        estruturas(),
        jogador1(nullptr),
        jogador2(nullptr)
    {
        for (int i = 0; i < tamVetorX; i++)
        {
            for (int j = 0; j < tamVetorY; j++)
            {
                estruturaArray[i][j] = nullptr;
            }
        }
    }

    GerenciadorColisao::~GerenciadorColisao()
    {
        jogador1 = nullptr;
        jogador2 = nullptr;

        inimigos.clear();
        obstaculos.clear();
		projeteis.clear();
        estruturas.clear();

        for (int i = 0; i < tamVetorX; i++)
        {
            for (int j = 0; j < tamVetorY; j++)
            {
                estruturaArray[i][j] = nullptr;
            }
        }
    }


    void GerenciadorColisao::executar()
    {
        colisao();
    }

    const bool GerenciadorColisao::verificarColisao(
        Entidades::Entidade* pe1,
        Entidades::Entidade* pe2
    )
    {
        if (!pe1 || !pe2)
        {
            return false;
        }

        if (!pe1->ativado() || !pe2->ativado())
        {
            return false;
        }

        return pe1->getLimites().intersects(pe2->getLimites());
    }

    void GerenciadorColisao::tratarColisoesJogsInimigos()
    {
        if (jogador1 && jogador1->ativado() && jogador1->vivo())
        {
            for (auto& inimigo : inimigos)
            {
                if (!inimigo || !inimigo->ativado() || !inimigo->vivo())
                {
                    continue;
                }

                /*
                    Ataque do jogador:
                    precisa ser testado mesmo sem o corpo encostar,
                    porque agora o ataque tem uma sprite/área na frente.
                */
                jogador1->colidir(inimigo);

                /*
                    Se o ataque matou/desativou o inimigo,
                    não precisa mais tratar colisão física.
                */
                if (!inimigo->ativado() || !inimigo->vivo())
                {
                    continue;
                }

                /*
                    Colisão física do corpo:
                    impede o jogador de atravessar o inimigo.
                */
                if (verificarColisao(jogador1, inimigo))
                {
                    empurrarPersonagem(jogador1, inimigo);

                    /*
                        Dano de contato do inimigo no jogador.
                    */
                    inimigo->danificar(jogador1);
                }
            }
        }

        if (jogador2 && jogador2->ativado() && jogador2->vivo())
        {
            for (auto& inimigo : inimigos)
            {
                if (!inimigo || !inimigo->ativado() || !inimigo->vivo())
                {
                    continue;
                }

                jogador2->colidir(inimigo);

                if (!inimigo->ativado() || !inimigo->vivo())
                {
                    continue;
                }

                if (verificarColisao(jogador2, inimigo))
                {
                    empurrarPersonagem(jogador2, inimigo);
                    inimigo->danificar(jogador2);
                }
            }
        }
    }

    void GerenciadorColisao::tratarColisoesJogsObstaculos()
    {
        if (jogador1 && jogador1->ativado())
        {
            for (auto& obstaculo : obstaculos)
            {
                if (obstaculo && verificarColisao(obstaculo, jogador1))
                {
                    if (obstaculo->ehColidivel())
                    {
                        empurrarPersonagem(jogador1, obstaculo);
                    }

                    obstaculo->obstaculizar(jogador1);
                }
            }
        }

        if (jogador2 && jogador2->ativado())
        {
            for (auto& obstaculo : obstaculos)
            {
                if (obstaculo && verificarColisao(obstaculo, jogador2))
                {
                    if (obstaculo->ehColidivel())
                    {
                        empurrarPersonagem(jogador2, obstaculo);
                    }

                    obstaculo->obstaculizar(jogador2);
                }
            }
        }
    }

    void GerenciadorColisao::tratarColisoesJogsEstruturas()
    {
        if (jogador1 && jogador1->ativado())
        {
            for (auto& estrutura : estruturas)
            {
                if (estrutura && verificarColisao(estrutura, jogador1))
                {
                    empurrarPersonagem(jogador1, estrutura);
                }
            }
        }

        if (jogador2 && jogador2->ativado())
        {
            for (auto& estrutura : estruturas)
            {
                if (estrutura && verificarColisao(estrutura, jogador2))
                {
                    empurrarPersonagem(jogador2, estrutura);
                }
            }
        }
    }

    void GerenciadorColisao::tratarColisoesObstaculosEstruturas()
    {
        for (auto& obstaculo : obstaculos)
        {
            if (obstaculo && obstaculo->ativado())
            {
                for (auto& estrutura : estruturas)
                {
                    if (estrutura && verificarColisao(obstaculo, estrutura))
                    {
                        obstaculo->setVelocidade(0, 0);
                    }
                }
            }
        }
    }

    void GerenciadorColisao::tratarColisaoProjeteis()
    {
        for (auto& projetil : projeteis)
        {
            if (!projetil || !projetil->ativado())
            {
                continue;
            }

            if (!projetil->podeColidir())
            {
                continue;
            }

            if (jogador1 && jogador1->ativado())
            {
                if (verificarColisao(projetil, jogador1))
                {
                    projetil->colidir(jogador1);
                    continue;
                }
            }

            if (jogador2 && jogador2->ativado())
            {
                if (verificarColisao(projetil, jogador2))
                {
                    projetil->colidir(jogador2);
                    continue;
                }
            }

            for (auto& estrutura : estruturas)
            {
                if (estrutura && verificarColisao(projetil, estrutura))
                {
                    projetil->colidir(estrutura);
                    break;
                }
            }
        }
    }

    void GerenciadorColisao::tratarColisaoInimigos()
    {
        for (auto& inimigo : inimigos)
        {
            if (inimigo && inimigo->ativado())
            {
                for (auto& obstaculo : obstaculos)
                {
                    if (obstaculo && verificarColisao(obstaculo, inimigo))
                    {
                        if (obstaculo->ehColidivel())
                        {
                            empurrarPersonagem(inimigo, obstaculo);
                        }
                    }
                }

                for (auto& estrutura : estruturas)
                {
                    if (estrutura && verificarColisao(estrutura, inimigo))
                    {
                        empurrarPersonagem(inimigo, estrutura);
                    }
                }
            }
        }
    }

    void GerenciadorColisao::incluirInimigo(
        Entidades::Personagens::Inimigo* inimigo
    )
    {
        if (inimigo)
        {
            inimigos.emplace_back(inimigo);
        }
    }

    void GerenciadorColisao::incluirObstaculo(
        Entidades::Obstaculos::Obstaculo* obstaculo
    )
    {
        if (obstaculo)
        {
            obstaculos.emplace_back(obstaculo);
        }
    }

    
    void GerenciadorColisao::incluirProjetil(
        Entidades::Projetil* projetil
    )
    {
        if (projetil)
        {
            projeteis.insert(projetil);
        }
    }
    

    void GerenciadorColisao::incluirEstrutura(
        Entidades::Estrutura* estrutura
    )
    {
        if (!estrutura)
        {
            return;
        }

        estruturas.emplace_back(estrutura);

        int x = static_cast<int>(estrutura->getPosicao().x / 100);
        int y = static_cast<int>(estrutura->getPosicao().y / 100);

        if (x >= 0 && x < tamVetorX && y >= 0 && y < tamVetorY)
        {
            estruturaArray[x][y] = estrutura;
        }
    }

    void GerenciadorColisao::incluirJogador1(
        Entidades::Personagens::Jogador* jogador
    )
    {
        jogador1 = jogador;
    }

    void GerenciadorColisao::incluirJogador2(
        Entidades::Personagens::Jogador* jogador
    )
    {
        jogador2 = jogador;
    }

    void GerenciadorColisao::empurrarPersonagem(
        Entidades::Personagens::Personagem* personagem,
        Entidades::Entidade* entidade
    )
    {
        if (!personagem || !entidade)
        {
            return;
        }

        sf::FloatRect characterBounds = personagem->getLimites();
        sf::FloatRect entBounds = entidade->getLimites();

        float charCenterX = characterBounds.left + characterBounds.width / 2.f;
        float charCenterY = characterBounds.top + characterBounds.height / 2.f;

        float entCenterX = entBounds.left + entBounds.width / 2.f;
        float entCenterY = entBounds.top + entBounds.height / 2.f;

        float overlapX =
            std::min(
                characterBounds.left + characterBounds.width,
                entBounds.left + entBounds.width
            )
            -
            std::max(
                characterBounds.left,
                entBounds.left
            );

        float overlapY =
            std::min(
                characterBounds.top + characterBounds.height,
                entBounds.top + entBounds.height
            )
            -
            std::max(
                characterBounds.top,
                entBounds.top
            );

        if (overlapX < overlapY)
        {
            if (charCenterX < entCenterX)
            {
                personagem->colidiu(entidade, Direcao::RIGHT);
            }
            else
            {
                personagem->colidiu(entidade, Direcao::LEFT);
            }
        }
        else
        {
            if (charCenterY < entCenterY)
            {
                personagem->colidiu(entidade, Direcao::DOWN);
            }
            else
            {
                personagem->colidiu(entidade, Direcao::UP);
            }
        }
    }

    int GerenciadorColisao::getQuantidadeInimigosAtivos() const
    {
        int quantidade = 0;

        for (auto inimigo : inimigos)
        {
            if (inimigo && inimigo->ativado() && inimigo->vivo())
            {
                quantidade++;
            }
        }

        return quantidade;
    }

    void GerenciadorColisao::colisao()
    {
        

        tratarColisoesJogsEstruturas();
        tratarColisoesJogsObstaculos();
        tratarColisoesJogsInimigos();
        tratarColisaoProjeteis();
        tratarColisaoInimigos();
        tratarColisoesObstaculosEstruturas();
    }
}