#pragma once
#include "Jogador.h"
#include "Estrutura.h"
#include "Obstaculo.h"
//#include "Projetil.h"
#include <set>
#include <list>

namespace Gerenciadores {
	class GerenciadorColisao
	{
	private:
		const int tamVetorX = 100;
		const int tamVetorY = 100;
		Entidades::Estrutura* estruturaArray[100][100];

		std::vector<Entidades::Personagens::Inimigo*> inimigos;
		std::vector<Entidades::Obstaculos::Obstaculo*> obstaculos;
		//std::vector<Entidades::Projetil*> projeteis;
		std::vector<Entidades::Estrutura*> estruturas;
		Entidades::Personagens::Jogador* jogador1;
		Entidades::Personagens::Jogador* jogador2;
	public:

		void executar();
		GerenciadorColisao();
		~GerenciadorColisao();


		const bool verificarColisao(Entidades::Entidade* pe1, Entidades::Entidade* pe2);

		//TRATAMENTO DE COLISOES
		void tratarColisoesJogsInimigos();
		void tratarColisoesJogsObstaculos();
		void tratarColisoesJogsEstruturas();
		void tratarColisoesObstaculosEstruturas();
		void tratarColisaoProjeteis();
		void tratarColisaoInimigos();
		void empurrarPersonagem(Entidades::Personagens::Personagem* personagem, Entidades::Entidade* entidade);
		void colision();

		//INCLUIR ENTIDADES
		void incluirInimigo(Entidades::Personagens::Inimigo* inimigo);
		void incluirObstaculo(Entidades::Obstaculos::Obstaculo* obstaculo);
		//void incluirProjetil(Entidades::Projetil* projetil);
		void incluirEstrutura(Entidades::Estrutura* estrutura);
		void incluirJogador1(Entidades::Personagens::Jogador* jogador);
		void incluirJogador2(Entidades::Personagens::Jogador* jogador);

	};

}