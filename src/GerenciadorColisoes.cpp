#include "../include/GerenciadorColisoes.h"

#include <cmath>

namespace Gerenciadores
{
    GerenciadorColisoes::GerenciadorColisoes(
        Entidades::Personagens::Jogador* pJ1,
        Entidades::Personagens::Jogador* pJ2
    ) :
        LIs(),
        LOs(),
        //LPs(),
        pJog1(pJ1),
        pJog2(pJ2)
    {}

    GerenciadorColisoes::~GerenciadorColisoes()
    {
        LIs.clear();
        LOs.clear();
        //LPs.clear();

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
            Implementaremos depois que você mandar Projetil.h / Projetil.cpp.

            Aqui provavelmente ficará algo como:

            for (auto itP = LPs.begin(); itP != LPs.end(); ++itP)
            {
                Projetil* pProj = *itP;

                for (unsigned int i = 0; i < LIs.size(); i++)
                {
                    Inimigo* pIni = LIs[i];

                    if (verificarColisao(pProj, pIni, &dirProj, &dirIni))
                    {
                        pIni->receber_dano(pProj->get_dano());
                        pProj->set_vivo(false);
                    }
                }
            }
        
    }*/

    /*void GerenciadorColisoes::tratarColisoesProjeteisObstacs()
    {
        /*
            Implementaremos depois que você mandar Projetil.h / Projetil.cpp.

            Aqui provavelmente ficará:

            Projétil x Obstáculo
                projétil deixa de existir
                ou obstáculo trata com obstaculizar()
        
    }*/

    void GerenciadorColisoes::executar()
    {
        tratarColisoesJogObstaculos(pJog1);
        tratarColisoesJogInimigos(pJog1);

        tratarColisoesJogObstaculos(pJog2);
        tratarColisoesJogInimigos(pJog2);

        tratarColisoesInimigsObstacs();

       // tratarColisoesProjeteisInimigs();
        //tratarColisoesProjeteisObstacs();
    }
}