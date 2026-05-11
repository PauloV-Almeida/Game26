#pragma once

#include <SFML/Graphics.hpp>
#include "../stdafx/stdafx.h"
#include "Personagem.h"
#include "Jogador.h"
#include "Inimigo.h"
#include "ListaEntidades.h"
#include "Plataforma.h"


namespace Gerenciadores
{
	class GerenciadorColisoes
	{
	private:
		std::vector<Entidades::Personagens::Inimigo*> LIs;
		std::list<Entidades::Obstaculos::Obstaculo*> LOs;
		//std::set <Entidades::Projetil*> LPs;

		Listas::ListaEntidades* LJogs;
		Listas::ListaEntidades* LInisPtr;
		Listas::ListaEntidades* LObsPtr;
	private:
		const bool verificarColisao(Entidades::Entidade* pe1, Entidades::Entidade* pe2, std::string* direcao1 = nullptr, std::string* direcao2 = nullptr)const;
		void colisor();
		void tratarColisoesJogsObstacs(Entidades::Personagens::Jogador* pJog, Entidades::Obstaculos::Obstaculo* pObs, std::string* dir1 = nullptr, std::string* dir2 = nullptr)const;
		void tratarColisoesJogsInimigs(Entidades::Personagens::Jogador* pJog, Entidades::Personagens::Inimigo* pIni, std::string* dir1 = nullptr, std::string* dir2 = nullptr)const;
		void tratarColisoesInimigsObstacs(Entidades::Personagens::Inimigo* pIni, Entidades::Obstaculos::Obstaculo* pObs, std::string* dir1 = nullptr, std::string* dir2 = nullptr)const;
		//void tratarColisoesJogsProjeteis();



	public:
		GerenciadorColisoes();
		~GerenciadorColisoes();
		void incluirJogadores(Listas::ListaEntidades* ListaJg) { if (ListaJg) { LJogs = ListaJg; } }
		Listas::ListaEntidades* get_ListaJogadores() { return LJogs; }

		// Mantém vector/list como requerido: guarda ponteiro para a fonte e popula inicialmente.
		void incluirInimigos(Listas::ListaEntidades* ListaIni) {
			if (!ListaIni) return;
			LInisPtr = ListaIni;
			LIs.clear();
			auto itr = ListaIni->get_Primeiro();
			while (itr != nullptr)
			{
				Entidades::Entidade* e = *itr;
				Entidades::Personagens::Inimigo* ini = dynamic_cast<Entidades::Personagens::Inimigo*>(e);
				if (ini && ini->get_vivo())
				{
					LIs.push_back(ini);
				}
				itr++;
			}
		}

		void incluirObstaculos(Listas::ListaEntidades* ListaObs) {
			if (!ListaObs) return;
			LObsPtr = ListaObs;
			LOs.clear();
			auto itr = ListaObs->get_Primeiro();
			while (itr != nullptr)
			{
				Entidades::Entidade* e = *itr;
				Entidades::Obstaculos::Obstaculo* obs = dynamic_cast<Entidades::Obstaculos::Obstaculo*>(e);
				if (obs && obs->get_vivo())
				{
					LOs.push_back(obs);
				}
				itr++;
			}
		}
		//void incluirProjetil(Projetil* p);

		void executar();
	};
}