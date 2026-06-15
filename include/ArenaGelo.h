#pragma once

#include "Fase.h"

namespace Fases
{
    class ArenaGelo : public Fase
    {
    private:
        const int maxThor = 4;

    public:
        ArenaGelo(
            Entidades::Personagens::Jogador* jg1,
            Entidades::Personagens::Jogador* jg2 = nullptr,
            bool carregaArquivo = false
        );

        ~ArenaGelo();
        void criarThor();
        void criarRuna();
		void criarProjetil();
        void criarInimigos();
        void criarObstaculo();
        void executar();
    };
}