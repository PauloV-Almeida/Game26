#pragma once

#include <SFML/Graphics.hpp>
#include "../stdafx/stdafx.h"
#include <vector>
#include <list>
#include <set>
#include <string>

#include "Jogador.h"
#include "Inimigo.h"
#include "Obstaculo.h"
//#include "Projetil.h"

namespace Gerenciadores
{
    class GerenciadorColisoes
    {
    private:
        std::vector<Entidades::Personagens::Inimigo*> LIs;
        std::list<Entidades::Obstaculos::Obstaculo*> LOs;
        //std::set<Entidades::Projetil*> LPs;

        std::vector<sf::FloatRect> colisoresMapa;

        Entidades::Personagens::Jogador* pJog1;
        Entidades::Personagens::Jogador* pJog2;

        float limiteEsquerdo;
        float limiteDireito;
        float limiteSuperior;
        float limiteInferior;

    private:
        bool verificarColisao(
            Entidades::Entidade* pe1,
            Entidades::Entidade* pe2,
            std::string* direcao1,
            std::string* direcao2
        );

        bool verificarColisaoMapa(
            Entidades::Entidade* pEnt,
            const sf::FloatRect& bloco,
            std::string* direcao
        );

        void tratarColisaoComLimites(Entidades::Entidade* pEnt);
        void tratarColisaoComMapa(Entidades::Entidade* pEnt);

        void tratarColisoesJogObstaculos(Entidades::Personagens::Jogador* pJog);
        void tratarColisoesJogInimigos(Entidades::Personagens::Jogador* pJog);
        void tratarColisoesInimigsObstacs();

        //void tratarColisoesProjeteisInimigs();
        //void tratarColisoesProjeteisObstacs();

    public:
        GerenciadorColisoes(
            Entidades::Personagens::Jogador* pJ1 = nullptr,
            Entidades::Personagens::Jogador* pJ2 = nullptr,
            float limEsq = 0.f,
            float limDir = 1920.f,
            float limInf = 1080.f,
            float limSup = 0.f
        );

        ~GerenciadorColisoes();

        void incluirInimigo(Entidades::Personagens::Inimigo* pIni);
        void incluirObstaculo(Entidades::Obstaculos::Obstaculo* pObs);
        //void incluirProjetil(Entidades::Projetil* pProj);

        void setColisoresMapa(const std::vector<sf::FloatRect>& colisores);

        void executar();
    };
}