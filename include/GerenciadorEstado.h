#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include "Subject.h"
#include "Acoes.h"
#include "Ente.h"
#include <vector>
#include "EstadoPause.h"
#include "ArenaGelo.h"
#include "FlorestaGelo.h"
#include "FimDeJogo.h"
#include "MenuRanking.h"
#include "MenuPrincipal.h"
#include "MenuSelecionar.h"



namespace Gerenciadores {
	class GerenciadorEstado : public Ente, public Subject
	{
	private:
		Entidades::Personagens::Jogador* jogador1;
		Entidades::Personagens::Jogador* jogador2;
		sf::RenderWindow* janela;
		std::vector<State*> stack;
		Actions pendingChange;
	public:
		void setJogador1(Entidades::Personagens::Jogador* jogador);
		void setJogador2(Entidades::Personagens::Jogador* jogador);
		GerenciadorEstado(Entidades::Personagens::Jogador* jogador_1, Entidades::Personagens::Jogador* jogador_2);
		void aplicarMudancas();
		void update(Actions act);
		void executar();
		void pop();
		void push(State* newState);
		void clear();


	};

}