#pragma once

#include "Fase.h"

#include <vector>

namespace Fases
{
    class ArenaGelo : public Fase
    {
    private:
        const int maxThor = 4;

        std::vector<Entidades::Projetil*> projeteisThor;

    public:
        ArenaGelo(
            Entidades::Personagens::Jogador* jg1,
            Entidades::Personagens::Jogador* jg2 = nullptr,
            bool carregaArquivo = false
        );

        virtual ~ArenaGelo();

        void criarThor();
        void criarRuna();
        void criarProjetil();

        void criarInimigos();
        void criarObstaculo();
        void executar();
    };
}