#pragma once

#include "Personagem.h"
#include "Jogador.h"
#include "../stdafx/stdafx.h"
#include "ListaEntidades.h"
#define VEL_MAX_INI 3.0f
#define RAIOY 50.0f
#define RAIOX 50.0f

namespace Entidades
{
	namespace Obstaculos
	{
		class Obstaculo;
	}

	namespace Personagens
	{
		class Jogador;

		class Inimigo :public Personagem
		{
		protected:
			int nivel_maldade;
			Listas::ListaEntidades* LJogs;
		public:
			Inimigo(int indice = -1,sf::Vector2f pos = sf::Vector2f(10.f, 0.f), sf::Vector2f vel = sf::Vector2f(0.f, 0.f), sf::Vector2f tam = sf::Vector2f(50.f, 50.f));
			~Inimigo();
			virtual void executar()= 0;
			virtual void danificar() = 0;
			virtual void colidir(Jogador* pJog, std::string direcao = "") = 0;
			virtual void colidir(Obstaculos::Obstaculo* pObs, std::string direcao = "") = 0;
			void mover();
			void movimentoaleatorio();
			void persegue(sf::Vector2f posJogador, sf::Vector2f posInimigo);
			void set_ListaJogadores(Listas::ListaEntidades* ListaJg) { LJogs = ListaJg; }
		};
	}
}