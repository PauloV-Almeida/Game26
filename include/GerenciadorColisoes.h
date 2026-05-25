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

        Entidades::Personagens::Jogador* pJog1;
        Entidades::Personagens::Jogador* pJog2;

    private:
        bool verificarColisao(
            Entidades::Entidade* pe1,
            Entidades::Entidade* pe2,
            std::string* direcao1,
            std::string* direcao2
        );

        void tratarColisoesJogObstaculos(Entidades::Personagens::Jogador* pJog);
        void tratarColisoesJogInimigos(Entidades::Personagens::Jogador* pJog);
        void tratarColisoesInimigsObstacs();

        //void tratarColisoesProjeteisInimigs();
        //void tratarColisoesProjeteisObstacs();

    public:
        GerenciadorColisoes(
            Entidades::Personagens::Jogador* pJ1 = nullptr,
            Entidades::Personagens::Jogador* pJ2 = nullptr
        );

        ~GerenciadorColisoes();

        void incluirInimigo(Entidades::Personagens::Inimigo* pIni);
        void incluirObstaculo(Entidades::Obstaculos::Obstaculo* pObs);
        //void incluirProjetil(Entidades::Projetil* pProj);

        void executar();
    };
}