#include "../include/GerenciadorColisoes.h"
#include <cmath>
#include <iostream>

namespace Gerenciadores
{
	GerenciadorColisoes::GerenciadorColisoes() :
		LIs(), LOs(), LJogs(nullptr), LInisPtr(nullptr), LObsPtr(nullptr)
	{
		LIs.clear();
		LOs.clear();
	}
	GerenciadorColisoes::~GerenciadorColisoes()
	{
		LIs.clear();
		LOs.clear();
	}


	const bool GerenciadorColisoes::verificarColisao(Entidades::Entidade* pe1, Entidades::Entidade* pe2, std::string* direcao1, std::string* direcao2) const
	{
		if (!pe1 || !pe2) return false;

		bool colidiu = false;

		sf::Vector2f pos1 = pe1->get_posicao();
		sf::Vector2f pos2 = pe2->get_posicao();
		sf::Vector2f tam1 = pe1->get_tamanho();
		sf::Vector2f tam2 = pe2->get_tamanho();
		sf::Vector2f distancia = pos1 - pos2;

		if (std::fabs(distancia.x) <= std::fabs((tam1.x + tam2.x) / 2.f) &&
			std::fabs(distancia.y) <= std::fabs((tam1.y + tam2.y) / 2.f))
		{
			colidiu = true;

			if (std::fabs(distancia.x) - std::fabs((tam1.x + tam2.x) / 2.f) <=
				std::fabs(distancia.y) - std::fabs((tam1.y + tam2.y) / 2.f))
			{
				if (pos1.y < pos2.y)
				{
					sf::Vector2f aux(pos1.x, pos2.y - (tam2.y + tam1.y) / 2.f);
					pe1->set_posicao(aux);
					*direcao1 = "Embaixo";
					*direcao2 = "Emcima";
				}
				else
				{
					sf::Vector2f aux(pos1.x, pos2.y + (tam2.y + tam1.y) / 2.f);
					pe1->set_posicao(aux);
					*direcao1 = "Emcima";
					*direcao2 = "Embaixo";
				}
			}



			else if (std::fabs(distancia.x) - std::fabs((tam1.x + tam2.x) / 2.f) >=
				std::fabs(distancia.y) - std::fabs((tam1.y + tam2.y) / 2.f))
			{
				if (pos1.x < pos2.x)
				{
					sf::Vector2f aux(pos2.x - (tam2.x + tam1.x) / 2.f, pos1.y);
					pe1->set_posicao(aux);
					*direcao1 = "Direita";
					*direcao2 = "Esquerda";
				}
				else
				{
					sf::Vector2f aux(pos2.x + (tam2.x + tam1.x) / 2.f, pos1.y);
					pe1->set_posicao(aux);
					*direcao1 = "Esquerda";
					*direcao2 = "Direita";

				}
			}
		}

		return colidiu;
	}
	void GerenciadorColisoes::colisor()
	{
		std::string dir1, dir2;

		if (!LJogs) {
			std::cout << "[Colisao] LJogs == nullptr\n";
			return;
		}

		// Reconstruir coleções internas a cada execução a partir das listas atuais
		LIs.clear();
		LOs.clear();

		if (LInisPtr) {
			auto itrIni = LInisPtr->get_Primeiro();
			while (itrIni != nullptr)
			{
				Entidades::Entidade* e = *itrIni;
				Entidades::Personagens::Inimigo* ini = dynamic_cast<Entidades::Personagens::Inimigo*>(e);
				if (ini && ini->get_vivo())
					LIs.push_back(ini);
				itrIni++;
			}
		}

		if (LObsPtr) {
			auto itrObs = LObsPtr->get_Primeiro();
			while (itrObs != nullptr)
			{
				Entidades::Entidade* e = *itrObs;
				Entidades::Obstaculos::Obstaculo* obs = dynamic_cast<Entidades::Obstaculos::Obstaculo*>(e);
				if (obs && obs->get_vivo())
					LOs.push_back(obs);
				itrObs++;
			}
		}

		int cntJ = 0;
		auto itrCount = LJogs->get_Primeiro();
		while (itrCount != NULL)
		{
			cntJ++; itrCount++;
		}
		// debug: conta jogadores

		auto itr = LJogs->get_Primeiro();
		while (itr != NULL)
		{
			Entidades::Entidade* e = *itr;
			Entidades::Personagens::Jogador* jog =
				dynamic_cast<Entidades::Personagens::Jogador*>(e);

			for (std::list<Entidades::Obstaculos::Obstaculo*>::iterator it = LOs.begin();
				it != LOs.end(); ++it)
			{
				if (!jog || !(*it)) continue;
				if (verificarColisao(jog, *it, &dir1, &dir2))
					tratarColisoesJogsObstacs(jog, *it, &dir1, &dir2);
			}

			for (std::vector<Entidades::Personagens::Inimigo*>::iterator itI = LIs.begin();
				itI != LIs.end(); ++itI)
			{
				Entidades::Personagens::Inimigo* ini = *itI;
				if (!ini || !ini->get_vivo()) continue;

				if (verificarColisao(jog, ini, &dir1, &dir2))
				{
					tratarColisoesJogsInimigs(jog, ini, &dir1, &dir2);
				}
			}

			for (std::vector<Entidades::Personagens::Inimigo*>::iterator itI = LIs.begin(); itI != LIs.end(); ++itI)
			{
				Entidades::Personagens::Inimigo* ini = *itI;
				if (!ini || !ini->get_vivo()) continue;

				for (std::list<Entidades::Obstaculos::Obstaculo*>::const_iterator itO = LOs.begin(); itO != LOs.end(); ++itO)
				{
					Entidades::Obstaculos::Obstaculo* obs = *itO;
					if (!obs || !obs->get_vivo()) continue;

					if (verificarColisao(ini, obs, &dir1, &dir2))
					{
						sf::Vector2f vel = ini->get_vel();
						if (dir1 == "Emcima" || dir1 == "Embaixo")
							vel.y = 0.f;
						else
							vel.x = 0.f;
						ini->set_vel(vel);
					}
				}
			}

			itr++;
		}

	}

	void GerenciadorColisoes::tratarColisoesJogsObstacs(Entidades::Personagens::Jogador* pJog, Entidades::Obstaculos::Obstaculo* pObs, std::string* dir1, std::string* dir2)const
	{
		pJog->colidir(pObs, *dir1);
		pObs->obstaculizar(pJog, *dir2);
	}

	void GerenciadorColisoes::tratarColisoesJogsInimigs(Entidades::Personagens::Jogador* pJog, Entidades::Personagens::Inimigo* pIni, std::string * dir1, std::string * dir2)const
	{
		pJog->colidir(pIni, *dir1);
		pIni->colidir(pJog, *dir2);
	}

	void GerenciadorColisoes::tratarColisoesInimigsObstacs(Entidades::Personagens::Inimigo* pIni, Entidades::Obstaculos::Obstaculo* pObs, std::string* dir1, std::string* dir2)const
	{
		pIni->colidir(pObs, *dir1);
		pObs->obstaculizar(pIni, *dir2);
	}

	/*
	* void GerenciadorColisoes::tratarColisoesJogsProjeteis()
	{
		// Implement projectile collision handling if needed
	}
	*/
		
	void GerenciadorColisoes::executar()
	{
		
		colisor();
	}

}