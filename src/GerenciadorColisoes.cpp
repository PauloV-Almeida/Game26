#include "../include/GerenciadorColisoes.h"

namespace Gerenciadores
{
    GerenciadorColisoes::GerenciadorColisoes(
        Entidades::Personagens::Jogador* pJ1,
        Entidades::Personagens::Jogador* pJ2,
        float limEsq,
        float limDir,
        float limInf,
        float limSup
    ) :
        LIs(),
        LOs(),
        //LPs(),
        colisoresMapa(),
        pJog1(pJ1),
        pJog2(pJ2),
        limiteEsquerdo(limEsq),
        limiteDireito(limDir),
        limiteSuperior(limSup),
        limiteInferior(limInf)
    {}

    GerenciadorColisoes::~GerenciadorColisoes()
    {
        LIs.clear();
        LOs.clear();
        //LPs.clear();
        colisoresMapa.clear();

        pJog1 = nullptr;
        pJog2 = nullptr;
    }

    void GerenciadorColisoes::incluirInimigo(Entidades::Personagens::Inimigo* pIni)
    {
        if (pIni)
        {
            LIs.push_back(pIni);
        }
    }

    void GerenciadorColisoes::incluirObstaculo(Entidades::Obstaculos::Obstaculo* pObs)
    {
        if (pObs)
        {
            LOs.push_back(pObs);
        }
    }

    /*void GerenciadorColisoes::incluirProjetil(Entidades::Projetil* pProj)
    {
        if (pProj)
        {
            LPs.insert(pProj);
        }
    }*/

    void GerenciadorColisoes::setColisoresMapa(const std::vector<sf::FloatRect>& colisores)
    {
        colisoresMapa = colisores;
    }

    bool GerenciadorColisoes::verificarColisao(
        Entidades::Entidade* pe1,
        Entidades::Entidade* pe2,
        std::string* direcao1,
        std::string* direcao2
    )
    {
        if (!pe1 || !pe2 || !direcao1 || !direcao2)
        {
            return false;
        }

        sf::Vector2f pos1 = pe1->get_posicao();
        sf::Vector2f pos2 = pe2->get_posicao();

        sf::Vector2f tam1 = pe1->get_tamanho();
        sf::Vector2f tam2 = pe2->get_tamanho();

        sf::Vector2f distancia = pos1 - pos2;

        float intersecaoX = std::fabs(distancia.x) - ((tam1.x + tam2.x) / 2.0f);
        float intersecaoY = std::fabs(distancia.y) - ((tam1.y + tam2.y) / 2.0f);

        if (intersecaoX < 0.0f && intersecaoY < 0.0f)
        {
            if (intersecaoX > intersecaoY)
            {
                if (distancia.x > 0.0f)
                {
                    pe1->set_posicao(
                        sf::Vector2f(
                            pos2.x + ((tam1.x + tam2.x) / 2.0f),
                            pos1.y
                        )
                    );

                    *direcao1 = "Esquerda";
                    *direcao2 = "Direita";
                }
                else
                {
                    pe1->set_posicao(
                        sf::Vector2f(
                            pos2.x - ((tam1.x + tam2.x) / 2.0f),
                            pos1.y
                        )
                    );

                    *direcao1 = "Direita";
                    *direcao2 = "Esquerda";
                }
            }
            else
            {
                if (distancia.y > 0.0f)
                {
                    pe1->set_posicao(
                        sf::Vector2f(
                            pos1.x,
                            pos2.y + ((tam1.y + tam2.y) / 2.0f)
                        )
                    );

                    *direcao1 = "Emcima";
                    *direcao2 = "Embaixo";
                }
                else
                {
                    pe1->set_posicao(
                        sf::Vector2f(
                            pos1.x,
                            pos2.y - ((tam1.y + tam2.y) / 2.0f)
                        )
                    );

                    *direcao1 = "Embaixo";
                    *direcao2 = "Emcima";
                }
            }

            return true;
        }

        return false;
    }

    bool GerenciadorColisoes::verificarColisaoMapa(
        Entidades::Entidade* pEnt,
        const sf::FloatRect& bloco,
        std::string* direcao
    )
    {
        if (!pEnt || !direcao)
        {
            return false;
        }

        sf::Vector2f pos = pEnt->get_posicao();
        sf::Vector2f tam = pEnt->get_tamanho();

        sf::FloatRect corpoEnt(
            pos.x - tam.x / 2.0f,
            pos.y - tam.y / 2.0f,
            tam.x,
            tam.y
        );

        if (!corpoEnt.intersects(bloco))
        {
            return false;
        }

        float centroEntX = corpoEnt.left + corpoEnt.width / 2.0f;
        float centroEntY = corpoEnt.top + corpoEnt.height / 2.0f;

        float centroBlocoX = bloco.left + bloco.width / 2.0f;
        float centroBlocoY = bloco.top + bloco.height / 2.0f;

        float distanciaX = centroEntX - centroBlocoX;
        float distanciaY = centroEntY - centroBlocoY;

        float somaMetadeX = corpoEnt.width / 2.0f + bloco.width / 2.0f;
        float somaMetadeY = corpoEnt.height / 2.0f + bloco.height / 2.0f;

        float intersecaoX = somaMetadeX - std::fabs(distanciaX);
        float intersecaoY = somaMetadeY - std::fabs(distanciaY);

        sf::Vector2f novaPos = pos;
        sf::Vector2f vel = pEnt->get_vel();

        if (intersecaoX < intersecaoY)
        {
            if (distanciaX > 0.0f)
            {
                novaPos.x += intersecaoX;
                *direcao = "Esquerda";
            }
            else
            {
                novaPos.x -= intersecaoX;
                *direcao = "Direita";
            }

            vel.x = 0.0f;
        }
        else
        {
            if (distanciaY > 0.0f)
            {
                novaPos.y += intersecaoY;
                *direcao = "Emcima";
            }
            else
            {
                novaPos.y -= intersecaoY;
                *direcao = "Embaixo";
            }

            vel.y = 0.0f;
        }

        pEnt->set_posicao(novaPos);
        pEnt->set_vel(vel);

        Entidades::Personagens::Personagem* pPers =
            dynamic_cast<Entidades::Personagens::Personagem*>(pEnt);

        if (pPers && *direcao == "Embaixo")
        {
            pPers->set_noChao(true);
        }

        return true;
    }

    void GerenciadorColisoes::tratarColisaoComLimites(Entidades::Entidade* pEnt)
    {
        if (!pEnt || !pEnt->get_vivo())
        {
            return;
        }

        sf::Vector2f pos = pEnt->get_posicao();
        sf::Vector2f tam = pEnt->get_tamanho();
        sf::Vector2f vel = pEnt->get_vel();

        float meiaLargura = tam.x / 2.0f;
        float meiaAltura = tam.y / 2.0f;

        Entidades::Personagens::Personagem* pPers =
            dynamic_cast<Entidades::Personagens::Personagem*>(pEnt);

        if (pos.y + meiaAltura > limiteInferior)
        {
            pos.y = limiteInferior - meiaAltura;
            vel.y = 0.0f;

            if (pPers)
            {
                pPers->set_noChao(true);
            }
        }

        if (pos.y - meiaAltura < limiteSuperior)
        {
            pos.y = limiteSuperior + meiaAltura;
            vel.y = 0.0f;
        }

        if (pos.x - meiaLargura < limiteEsquerdo)
        {
            pos.x = limiteEsquerdo + meiaLargura;
            vel.x = 0.0f;
        }

        if (pos.x + meiaLargura > limiteDireito)
        {
            pos.x = limiteDireito - meiaLargura;
            vel.x = 0.0f;
        }

        pEnt->set_posicao(pos);
        pEnt->set_vel(vel);
    }

    void GerenciadorColisoes::tratarColisaoComMapa(Entidades::Entidade* pEnt)
    {
        if (!pEnt || !pEnt->get_vivo())
        {
            return;
        }

        for (unsigned int i = 0; i < colisoresMapa.size(); i++)
        {
            std::string direcao;

            verificarColisaoMapa(pEnt, colisoresMapa[i], &direcao);
        }
    }

    void GerenciadorColisoes::tratarColisoesJogInimigos(
        Entidades::Personagens::Jogador* pJog
    )
    {
        if (!pJog || !pJog->get_vivo())
        {
            return;
        }

        for (unsigned int i = 0; i < LIs.size(); i++)
        {
            Entidades::Personagens::Inimigo* pIni = LIs[i];

            if (!pIni || !pIni->get_vivo())
            {
                continue;
            }

            std::string dirJog;
            std::string dirIni;

            if (verificarColisao(pJog, pIni, &dirJog, &dirIni))
            {
                pJog->colidir(pIni, dirJog);
                pIni->danificar(pJog);
            }
        }
    }

    void GerenciadorColisoes::tratarColisoesJogObstaculos(
        Entidades::Personagens::Jogador* pJog
    )
    {
        if (!pJog || !pJog->get_vivo())
        {
            return;
        }

        for (auto it = LOs.begin(); it != LOs.end(); ++it)
        {
            Entidades::Obstaculos::Obstaculo* pObs = *it;

            if (!pObs || !pObs->get_vivo())
            {
                continue;
            }

            std::string dirJog;
            std::string dirObs;

            if (verificarColisao(pJog, pObs, &dirJog, &dirObs))
            {
                pObs->obstaculizar(pJog, dirJog);
            }
        }
    }

    void GerenciadorColisoes::tratarColisoesInimigsObstacs()
    {
        for (unsigned int i = 0; i < LIs.size(); i++)
        {
            Entidades::Personagens::Inimigo* pIni = LIs[i];

            if (!pIni || !pIni->get_vivo())
            {
                continue;
            }

            for (auto it = LOs.begin(); it != LOs.end(); ++it)
            {
                Entidades::Obstaculos::Obstaculo* pObs = *it;

                if (!pObs || !pObs->get_vivo())
                {
                    continue;
                }

                std::string dirIni;
                std::string dirObs;

                if (verificarColisao(pIni, pObs, &dirIni, &dirObs))
                {
                    pObs->obstaculizar(pIni, dirIni);
                }
            }
        }
    }

    /*void GerenciadorColisoes::tratarColisoesProjeteisInimigs()
    {
        /*
            Será implementado quando Projetil estiver pronto.
        
    }*/

    /*void GerenciadorColisoes::tratarColisoesProjeteisObstacs()
    {
        /*
            Será implementado quando Projetil estiver pronto.
        
    }*/

    void GerenciadorColisoes::executar()
    {
        tratarColisaoComLimites(pJog1);
        tratarColisaoComLimites(pJog2);

        tratarColisaoComMapa(pJog1);
        tratarColisaoComMapa(pJog2);

        for (unsigned int i = 0; i < LIs.size(); i++)
        {
            tratarColisaoComLimites(LIs[i]);
            tratarColisaoComMapa(LIs[i]);
        }

        tratarColisoesJogObstaculos(pJog1);
        tratarColisoesJogObstaculos(pJog2);

        tratarColisoesJogInimigos(pJog1);
        tratarColisoesJogInimigos(pJog2);

        tratarColisoesInimigsObstacs();

        //tratarColisoesProjeteisInimigs();
        //tratarColisoesProjeteisObstacs();
    }
}