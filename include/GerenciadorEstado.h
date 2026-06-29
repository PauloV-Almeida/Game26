#pragma once
// Baseado No Filepe Simpalista https://github.com/Sk-3/jogoSimao1
#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>

#include "Subject.h"
#include "Acoes.h"
#include "Ente.h"

#include "EstadoPause.h"
#include "ArenaGelo.h"
#include "FlorestaGelo.h"
#include "FimDeJogo.h"
#include "MenuRanking.h"
#include "MenuPrincipal.h"
#include "MenuSelecionar.h"

namespace Gerenciadores
{
    class GerenciadorEstado : public Ente, public Subject
    {
    private:
        Entidades::Personagens::Jogador* jogador1;
        Entidades::Personagens::Jogador* jogador2;



        std::vector<State*> stack;
        Actions pendingChange;

    public:
        GerenciadorEstado(
            Entidades::Personagens::Jogador* jogador_1,
            Entidades::Personagens::Jogador* jogador_2
        );

        ~GerenciadorEstado();        

        void aplicarMudancas();
        void update(Actions act);
        void executar();

        void pop();
        void push(State* newState);
        void clear();
    };
}