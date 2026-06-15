#pragma once

#include "Jogador.h"
#include "Estrutura.h"
#include "Obstaculo.h"
#include "Inimigo.h"
#include "Projetil.h"
#include "Direcao.h"

#include <vector>
#include <list>
#include <set>

namespace Gerenciadores
{
    class GerenciadorColisao
    {
    private:
        static const int tamVetorX = 100;
        static const int tamVetorY = 100;

        Entidades::Estrutura* estruturaArray[tamVetorX][tamVetorY];

        std::vector<Entidades::Personagens::Inimigo*> inimigos;
        std::list<Entidades::Obstaculos::Obstaculo*> obstaculos;
        std::set<Entidades::Projetil*> projeteis;
        std::vector<Entidades::Estrutura*> estruturas;

        Entidades::Personagens::Jogador* jogador1;
        Entidades::Personagens::Jogador* jogador2;

    private:
        const bool verificarColisao(
            Entidades::Entidade* pe1,
            Entidades::Entidade* pe2
        );

        void tratarColisoesJogsInimigos();
        void tratarColisoesJogsObstaculos();
        void tratarColisoesJogsEstruturas();
        void tratarColisoesObstaculosEstruturas();
        void tratarColisaoProjeteis();
        void tratarColisaoInimigos();

        void empurrarPersonagem(
            Entidades::Personagens::Personagem* personagem,
            Entidades::Entidade* entidade
        );

        void colisao();

    public:
        GerenciadorColisao();
        ~GerenciadorColisao();

        void incluirInimigo(Entidades::Personagens::Inimigo* inimigo);
        void incluirObstaculo(Entidades::Obstaculos::Obstaculo* obstaculo);
        void incluirProjetil(Entidades::Projetil* projetil);
        void incluirEstrutura(Entidades::Estrutura* estrutura);

        void incluirJogador1(Entidades::Personagens::Jogador* jogador);
        void incluirJogador2(Entidades::Personagens::Jogador* jogador);
        int getQuantidadeInimigosAtivos() const;
        void executar();
    };
}