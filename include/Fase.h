#pragma once

#include <SFML/Graphics.hpp>

#include "Entidades.h"
#include "Jogador.h"
#include "Esqueleto.h"
#include "Plataforma.h"
#include "ListaEntidades.h"
#include "GerenciadorGrafico.h"
#include "GerenciadorColisoes.h"
#include "GerenciadorEventos.h"
#include "GerenciadorEstado.h"
#include "Estado.h"



#include <fstream>
#include <string>
#include <iostream>

#define ARQUIVO_FASE_1 "./salvar/fase1.dat"
#define SALVAR_FASE_1 "./salvar/savefase1.dat"
#define SALVAR_BASE_1 "./salvar/savebase1.dat"

#define ARQUIVO_FASE_2 "./salvar/fase2.dat"
#define SALVAR_FASE_2 "./salvar/savefase2.dat"
#define SALVAR_BASE_2 "./salvar/savebase2.dat"

namespace Fases
{
	class Fase : public Ente, public Estados::Estado
	{
	protected:
		Listas::ListaEntidades jogadores;
		Listas::ListaEntidades inimigos;
		Listas::ListaEntidades obstaculos;

		std::string salvarArq;
		std::string infoFase;
		std::string salvarBase;


		Gerenciadores::GerenciadorColisoes gColisoes;
		Gerenciadores::GerenciadorEventos* pGE;


		int n_nasceu;
		bool carregado;

		sf::RectangleShape corpo;

	protected:
		Entidades::Entidade* criarEsqueleto(std::ifstream& arquivo);
		Entidades::Entidade* criarPlataformas(std::ifstream& arquivo);
		

		//virtual void criarInimigos(Entidades::Entidade* ini) = 0;
		//virtual void criarObstaculos(Entidades::Entidade* obs) = 0;
		void criarCenario(std::string arquivo,  std::string save);
		void carregaCenario(std::string saveCenarioArq);
	public:
		Fase(int id = -1);
		virtual ~Fase();
		virtual void executar() = 0;
		void desenhar();

		virtual void salvar() = 0;
		virtual void carregar() = 0;
		virtual void resetar() = 0;
		
	};
}