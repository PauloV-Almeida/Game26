#pragma once

#include "Fase.h"

namespace Fases
{
    class FlorestaGelo : public Fase
    {
    private:
        const int maxValkiria = 5;

    public:
        FlorestaGelo(
            Entidades::Personagens::Jogador* jg1,
            Entidades::Personagens::Jogador* jg2 = nullptr,
            bool carregaArquivo = false
        );

        ~FlorestaGelo();
		void criarValkiria();
        void criarEspinhoVenenoso();
        void criarInimigos();
        void criarObstaculo();
        void executar();
    };
}