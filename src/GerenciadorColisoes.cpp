#include "../include/GerenciadorColisoes.h"
#include <iostream>
namespace Gerenciadores {

	void GerenciadorColisao::executar()
	{
		colision();

	}
	GerenciadorColisao::GerenciadorColisao()
		:tamVetorX(100),
		tamVetorY(100),
		jogador1(nullptr),
		jogador2(nullptr)
	{
		for (int i = 0; i < tamVetorX; i++) {
			for (int j = 0; j < tamVetorY; j++) {
				estruturaArray[i][j] = nullptr;
			}
		}

	}

	GerenciadorColisao::~GerenciadorColisao()
	{

	}

	const bool GerenciadorColisao::verificarColisao(Entidades::Entidade* pe1, Entidades::Entidade* pe2)
	{
		if (!pe1->ativado() || !pe2->ativado()) {
			return 0;
		}
		sf::FloatRect ent1Bounds = pe1->getLimites();
		sf::FloatRect ent2Bounds = pe2->getLimites();
		return ent1Bounds.intersects(ent2Bounds);
	}


	void GerenciadorColisao::tratarColisoesJogsInimigos()
	{
		if (jogador1) {
			for (auto& inimigo : inimigos) {
				if (inimigo->ativado()) {
					if (verificarColisao(jogador1, inimigo)) {
						inimigo->danificar(jogador1);
					}
				}
			}
		}
		if (jogador2) {
			for (auto& inimigo : inimigos) {
				if (inimigo->ativado()) {
					if (verificarColisao(jogador2, inimigo)) {
						inimigo->danificar(jogador2);
					}
				}
			}
		}
	}

	void GerenciadorColisao::tratarColisoesJogsObstaculos()
	{
		if (jogador1) {
			for (auto& obstac : obstaculos) {
				if (verificarColisao(obstac, jogador1)) {
					if (obstac->ehColidivel()) {
						empurrarPersonagem(jogador1, obstac);
					}
					obstac->obstaculizar(jogador1);
				}
			}

		}
		if (jogador2) {
			for (auto& obstac : obstaculos) {
				if (verificarColisao(obstac, jogador2)) {
					if (obstac->ehColidivel()) {
						empurrarPersonagem(jogador2, obstac);
					}
					obstac->obstaculizar(jogador2);
				}
			}

		}


	}

	void GerenciadorColisao::tratarColisoesJogsEstruturas()
	{
		if (jogador1) {
			int minX = static_cast<int>(jogador1->getPosicao().x / 100) - 3;
			int minY = static_cast<int>(jogador1->getPosicao().y / 100) - 3;

			int maxX = static_cast<int>(jogador1->getPosicao().x / 100) + 3;
			int maxY = static_cast<int>(jogador1->getPosicao().y / 100) + 3;
			for (int i = minX; i < maxX; i++) {
				for (int j = minY; j < maxY; j++) {
					if (j >= 0 && i >= 0 && i < 100 && j < 100) {
						if (estruturaArray[i][j]) {
							if (verificarColisao(estruturaArray[i][j], jogador1)) {
								empurrarPersonagem(jogador1, estruturaArray[i][j]);
							}
						}

					}
				}
			}
		}
		if (jogador2) {
			int minX = static_cast<int>(jogador2->getPosicao().x / 100) - 3;
			int minY = static_cast<int>(jogador2->getPosicao().y / 100) - 3;

			int maxX = static_cast<int>(jogador2->getPosicao().x / 100) + 3;
			int maxY = static_cast<int>(jogador2->getPosicao().y / 100) + 3;
			for (int i = minX; i < maxX; i++) {
				for (int j = minY; j < maxY; j++) {
					if (j >= 0 && i >= 0 && i < 100 && j < 100) {
						if (estruturaArray[i][j]) {
							if (verificarColisao(estruturaArray[i][j], jogador2)) {
								empurrarPersonagem(jogador2, estruturaArray[i][j]);
							}
						}

					}
				}
			}

		}
	}

	void GerenciadorColisao::tratarColisoesObstaculosEstruturas()
	{
		for (auto& obst : obstaculos) {
			for (const auto& estrut : estruturas) {
				if (verificarColisao(obst, estrut)) {
					obst->setVelocidade(0, 0);
				}
			}
		}
	}

	/*void GerenciadorColisao::tratarColisaoProjeteis()
	{
		for (auto& projet : projeteis) {
			if (projet->ativado()) {
				sf::FloatRect projBounds = projet->getBounds();
				for (const auto& obst : obstaculos) {
					if (verificarColisao(obst, projet)) {
						projet->desativar();
					}
				}
				for (const auto& estrut : estruturas) {
					if (verificarColisao(estrut, projet)) {
						projet->desativar();
					}
				}

				for (auto& charact : inimigos) {
					if (verificarColisao(projet, charact)) {
						if (charact->getTipo() != projet->getTipo()) {
							projet->desativar();
							projet->danifica(charact);
							projet->aumentaPontosDono();

						}
					}
				}

				if (verificarColisao(projet, jogador1)) {
					if (projet->getTipo() == TipoPersonagem::INIMIGO) {
						projet->danifica(jogador1);
						projet->desativar();
					}
				}
				if (jogador2) {
					if (verificarColisao(projet, jogador2)) {
						if (projet->getTipo() == TipoPersonagem::INIMIGO) {
							projet->danifica(jogador2);
							projet->desativar();
						}
					}
				}
			}
		}
	}*/

	void GerenciadorColisao::tratarColisaoInimigos()
	{
		for (auto& charact : inimigos) {
			if (charact->ativado()) {
				for (const auto& obstac : obstaculos) {
					if (verificarColisao(obstac, charact)) {
						if (obstac->ehColidivel()) {
							empurrarPersonagem(charact, obstac);
						}
						obstac->obstaculizar(charact);
					}
				}
			}
		}

		for (auto& charact : inimigos) {
			if (charact->ativado()) {
				int minX = static_cast<int>(charact->getPosicao().x / 100) - 3;
				int minY = static_cast<int>(charact->getPosicao().y / 100) - 3;

				int maxX = static_cast<int>(charact->getPosicao().x / 100) + 3;
				int maxY = static_cast<int>(charact->getPosicao().y / 100) + 3;
				for (int i = minX; i < maxX; i++) {
					for (int j = minY; j < maxY; j++) {
						if (j >= 0 && i >= 0 && i < 100 && j < 100) {
							if (estruturaArray[i][j]) {
								if (verificarColisao(estruturaArray[i][j], charact)) {
									empurrarPersonagem(charact, estruturaArray[i][j]);
								}
							}

						}
					}
				}
			}
		}
	}

	void GerenciadorColisao::incluirInimigo(Entidades::Personagens::Inimigo* inimigo)
	{
		inimigos.emplace_back(inimigo);
	}
	void GerenciadorColisao::incluirObstaculo(Entidades::Obstaculos::Obstaculo* obstaculo)
	{
		obstaculos.emplace_back(obstaculo);
	}
	/*void GerenciadorColisao::incluirProjetil(Entidades::Projetil* projetil)
	{
		projeteis.emplace_back(projetil);
	}*/
	void GerenciadorColisao::incluirEstrutura(Entidades::Estrutura* estrutura)
	{
		estruturas.emplace_back(estrutura);
		std::cout << "\nPos x: " << estrutura->getPosicao().x / 100 << ",pos Y: " << estrutura->getPosicao().y;
		estruturaArray[static_cast<int>(estrutura->getPosicao().x / 100)][static_cast<int>(estrutura->getPosicao().y / 100)] = estrutura;
	}
	void GerenciadorColisao::incluirJogador1(Entidades::Personagens::Jogador* jogador)
	{
		jogador1 = jogador;
	}
	void GerenciadorColisao::incluirJogador2(Entidades::Personagens::Jogador* jogador)
	{
		jogador2 = jogador;
	}
	void GerenciadorColisao::empurrarPersonagem(Entidades::Personagens::Personagem* personagem, Entidades::Entidade* entidade)
	{

	
		sf::FloatRect characterBounds = personagem->getLimites();
		sf::FloatRect entBounds = entidade->getLimites();

		//Centro do personagem
		float charCenterX = characterBounds.left + characterBounds.width / 2.f;
		float charCenterY = characterBounds.top + characterBounds.height / 2.f;

		//Centro do obstaculo
		float entCenterX = entBounds.left + entBounds.width / 2.0f;
		float entCenterY = entBounds.top + entBounds.height / 2.0f;

		//Sobreposição em cada eixo

		float overlapX = std::min(characterBounds.left + characterBounds.width, entBounds.left + entBounds.width) - std::max(characterBounds.left, entBounds.left);
		//interseção no eixo X


		float overlapY = std::min(characterBounds.top + characterBounds.height, entBounds.top + entBounds.height) - std::max(characterBounds.top, entBounds.top);
		//interseção no eixo y

		// Determinar a direção da colisão pela menor sobreposição
		if (overlapX < overlapY) {
			if (charCenterX < entCenterX) {
				personagem->colidiu(entidade, Directions::RIGHT);
			}
			else {
				personagem->colidiu(entidade, Directions::LEFT);
			}
		}
		else {

			if (charCenterY < entCenterY) {
				personagem->colidiu(entidade, Directions::DOWN);
			}
			else {
				personagem->colidiu(entidade, Directions::UP);
			}
		}
	}
	void GerenciadorColisao::colision()
	{
		
		tratarColisaoProjeteis();
		tratarColisaoInimigos();
		tratarColisoesJogsObstaculos();
		tratarColisoesJogsEstruturas();
		tratarColisoesJogsInimigos();
		tratarColisoesObstaculosEstruturas();
	}

}