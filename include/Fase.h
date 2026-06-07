#pragma once

#include <cstdlib>
#include "State.h"
#include "Jogador.h"
#include "Estrutura.h"
#include "Plataforma.h"
#include "EspinhoVenenoso.h"
#include "Andarilho.h"
//#include "Projetil.h"
#include "GerenciadorColisoes.h"
#include "Hub.h"
#include <sstream>
#include <fstream>
#include "ListaEntidades.h"




namespace Fases {
	class Fase : public State
	{
	protected:
		int pontuacaoTotal;
		int id;

		sf::View view;
		Hub hub;
		
		Gerenciadores::GerenciadorColisao gC;
		
		Listas::ListaEntidades listaEntidades;

		bool jogador2Ativo;
		Entidades::Personagens::Jogador* jogador2;
		Entidades::Personagens::Jogador* jogador1;
	public:
		~Fase();
		Fase(Entidades::Personagens::Jogador* jg1, Entidades::Personagens::Jogador* jg2, bool carregaArquivo);
		virtual void lidarEvent();
		virtual void executar() = 0;
		virtual void executarJanela();
		void salvar();

		
		int getPontuacaoTotal();
		void carregarSalvamento();
		virtual void carregamentoPadrao();

		void criarAndarilhos();
		void criarPlataformas();
		virtual void criarInimigos() = 0;
		virtual void criarObstaculo() = 0;
		void controladorEstado(int id);
		void criarCenario();
		int verificarQuantidadeInimigos();
	};
}