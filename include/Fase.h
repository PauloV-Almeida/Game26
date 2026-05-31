#pragma once

#include "Jogador.h"
#include "Plataforma.h"
#include "ListaEntidades.h"
#include "GerenciadorColisoes.h"
#include "GerenciadorEventos.h"
#include "GerenciadorEstado.h"
#include "Estado.h"


#include <fstream>
#include <string>
#include <iostream>


namespace Fases
{
	class Fase : public Ente, public Estados::Estado
	{
	protected:
		int pontucaoTotal;


		Gerenciadores::GerenciadorColisoes gColisoes;
		Gerenciadores::GerenciadorEventos* pGE;
		Listas::ListaEntidades listaEntidades;

		Entidades::Personagens::Jogador* pJog1;
		Entidades::Personagens::Jogador* pJog2;

	protected:
		Entidades::Entidade* criarAndarilho();
		Entidades::Entidade* criarPlataformas();
		

		virtual void criarInimigos() = 0;
		virtual void criarObstaculos() = 0;

		void criarCenario();
	public:
		Fase(int id = -1);
		virtual ~Fase();
		virtual void executar() = 0;
		void salvar();

		void carregarSalvamente();
		virtual void reiniciar();

		int getPontuacaoTotal() { return pontucaoTotal; }
		
	};
}