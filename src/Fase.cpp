#include "../include/Fase.h"

namespace Fases {

	Fase::Fase(Entidades::Personagens::Jogador* jogador1, Entidades::Personagens::Jogador* jogador2, bool carregaArquivo) :
		State(),
		jogador1(jogador1),
		jogador2(jogador2),
		jogador2Ativo(0),
		view(pGG->getPadraoView()),
		areaPassagem(),
		possuiPassagem(false),
		caminhoMapa("assets/mapaFloGelo.txt")
	{
		mediador = mediadorEventos::getMediadorEventos();
		pontuacaoTotal = 0;
		id = 0;
		gC.incluirJogador1(jogador1);
		listaEntidades.inserirNoFim(jogador1);
		hub.setPlayer(jogador1);
		pGG->setView(view);
	}



	Fase::~Fase() {
		listaEntidades.desalocar();
	}

	int Fase::sortearQuantidade(int minimo, int maximo)
	{
		return minimo + rand() % (maximo - minimo + 1);
	}



	void Fase::lidarEvent()
	{
		
		if (jogador1 && jogador1->ativado())
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				jogador1->movimentar(Direcao::LEFT);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				jogador1->movimentar(Direcao::RIGHT);
			}
			else
			{
				jogador1->pararEixoX();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
					jogador1->movimentar(Direcao::UP);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
					jogador1->atacar();
			}
		}

		if (jogador2Ativo && jogador2 && jogador2->ativado())
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				jogador2->movimentar(Direcao::LEFT);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				jogador2->movimentar(Direcao::RIGHT);
			}
			else
			{
				jogador2->pararEixoX();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				jogador2->movimentar(Direcao::UP);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				jogador2->atacar();
			}
		}
		

		sf::Event ev;

		while (pGG->get_janela()->pollEvent(ev))
		{
			switch (ev.type)
			{
			case sf::Event::Closed:
				pGG->fechar();
				break;

			case sf::Event::KeyPressed:
				if (ev.key.code == sf::Keyboard::J)
				{
					if (jogador2 && !jogador2Ativo)
					{
						hub.setPlayer2(jogador2);
						jogador2Ativo = true;

						listaEntidades.inserirNoFim(jogador2);
						gC.incluirJogador2(jogador2);
					}
				}

				if (ev.key.code == sf::Keyboard::P)
				{
					mediador->notify(Actions::PAUSE);
				}
				break;

			default:
				break;
			}
		}
	}

	void Fase::executarJanela()
	{
		if (jogador2Ativo && jogador2)
		{
			sf::Vector2f centro;
			centro.x = (jogador1->getCentro().x + jogador2->getCentro().x) / 2.f;
			centro.y = (jogador1->getCentro().y + jogador2->getCentro().y) / 2.f;

			view.setCenter(centro);
		}
		else if (jogador1)
		{
			view.setCenter(jogador1->getCentro());
		}

		pGG->limpar();
		pGG->setView(view);
		pGG->desenharFundo(id);
	}

	int Fase::getPontuacaoTotal() const
	{
		return pontuacaoTotal;
	}

	void Fase::carregarSalvamento()
	{
		hub.setPlayer(jogador1);
		pGG->setView(view);

		std::ifstream arquivo("salvar/salvar.txt");
		std::string linha;
		if (arquivo.is_open()) {
			std::getline(arquivo, linha);
			std::istringstream linhaOutput(linha);
			while (std::getline(arquivo, linha))
			{
				std::istringstream entrada(linha);

				std::string tipoEntidade;

				int idEntidade;
				int ativo;

				float posicaoX;
				float posicaoY;
				float velocidadeX;
				float velocidadeY;

				entrada >> tipoEntidade;

				entrada >> idEntidade;
				entrada >> ativo;
				entrada >> posicaoX;
				entrada >> posicaoY;
				entrada >> velocidadeX;
				entrada >> velocidadeY;

				if (tipoEntidade == "JOGADOR")
				{
					int vida;
					bool noChao;
					bool travado;
					float velocidadeMovimento;
					float velocidadeMaxima;
					float forcaPulo;

					int idJogador;
					int danoAtaque;
					int maxPulos;
					int pulosRestantes;
					bool atacando;
					bool olhandoDireita;
					bool venceu;

					entrada >> vida;
					entrada >> noChao;
					entrada >> travado;
					entrada >> velocidadeMovimento;
					entrada >> velocidadeMaxima;
					entrada >> forcaPulo;

					entrada >> idJogador;
					entrada >> danoAtaque;
					entrada >> maxPulos;
					entrada >> pulosRestantes;
					entrada >> atacando;
					entrada >> olhandoDireita;
					entrada >> venceu;

					Entidades::Personagens::Jogador* jogador = nullptr;

					if (idJogador == 1)
					{
						jogador = jogador1;
					}
					else
					{
						jogador = jogador2;
					}

					if (jogador)
					{
						jogador->setIdUnico(idEntidade);
						jogador->setAtivo(ativo);
						jogador->setPosicao(posicaoX, posicaoY);
						jogador->setVelocidade(velocidadeX, velocidadeY);
						jogador->setTravado(travado);
						
					}
				}
				else if (tipoEntidade == "ANDARILHO")
				{
					Entidades::Personagens::Andarilho* andarilho =
						new Entidades::Personagens::Andarilho(
							sf::Vector2f(posicaoX, posicaoY),
							jogador1
						);

					andarilho->setIdUnico(idEntidade);
					andarilho->setAtivo(ativo);
					andarilho->setVelocidade(velocidadeX, velocidadeY);

					listaEntidades.inserirNoFim(andarilho);
					gC.incluirInimigo(andarilho);
				}
				else if (tipoEntidade == "VALKIRIA")
				{
					Entidades::Personagens::Valkiria* valkiria =
						new Entidades::Personagens::Valkiria(
							sf::Vector2f(posicaoX, posicaoY),
							jogador1
						);

					valkiria->setIdUnico(idEntidade);
					valkiria->setAtivo(ativo);
					valkiria->setVelocidade(velocidadeX, velocidadeY);

					listaEntidades.inserirNoFim(valkiria);
					gC.incluirInimigo(valkiria);
				}
				else if (tipoEntidade == "THOR")
				{
					Entidades::Projetil* projetil = new Entidades::Projetil();

					Entidades::Personagens::Thor* thor =
						new Entidades::Personagens::Thor(
							sf::Vector2f(900.f * 420.f, 250.f),
							jogador1,
							projetil
						);


					thor->setIdUnico(idEntidade);
					thor->setAtivo(ativo);
					thor->setVelocidade(velocidadeX, velocidadeY);

					listaEntidades.inserirNoFim(thor);
					listaEntidades.inserirNoFim(projetil);

					gC.incluirInimigo(thor);
					gC.incluirProjetil(projetil);
				}
				else if (tipoEntidade == "PLATAFORMA")
				{
					Entidades::Obstaculos::Plataforma* plataforma =
						new Entidades::Obstaculos::Plataforma(
							sf::Vector2f(posicaoX, posicaoY),
							sf::Vector2f(TAM_TILE, TAM_TILE)
						);

					plataforma->setIdUnico(idEntidade);
					plataforma->setAtivo(ativo);
					plataforma->setVelocidade(velocidadeX, velocidadeY);

					listaEntidades.inserirNoFim(plataforma);
					gC.incluirObstaculo(plataforma);
				}
				else if (tipoEntidade == "ESPINHO")
				{
					Entidades::Obstaculos::EspinhoVenenoso* espinho =
						new Entidades::Obstaculos::EspinhoVenenoso(
							sf::Vector2f(posicaoX, posicaoY),
							sf::Vector2f(TAM_TILE, TAM_TILE)
						);

					espinho->setIdUnico(idEntidade);
					espinho->setAtivo(ativo);
					espinho->setVelocidade(velocidadeX, velocidadeY);

					listaEntidades.inserirNoFim(espinho);
					gC.incluirObstaculo(espinho);
				}
				else if (tipoEntidade == "RUNA")
				{
					Entidades::Obstaculos::Runa* runa =
						new Entidades::Obstaculos::Runa(
							sf::Vector2f(posicaoX, posicaoY),
							sf::Vector2f(TAM_TILE, TAM_TILE)
						);

					runa->setIdUnico(idEntidade);
					runa->setAtivo(ativo);
					runa->setVelocidade(velocidadeX, velocidadeY);

					listaEntidades.inserirNoFim(runa);
					gC.incluirObstaculo(runa);
				}
				else if (tipoEntidade == "ESTRUTURA")
				{
					Entidades::Estrutura* estrutura =
						new Entidades::Estrutura(
							sf::Vector2f(posicaoX, posicaoY),
							TipoEstrutura::CHAO,
							sf::Vector2f(TAM_TILE, TAM_TILE)
						);

					estrutura->setIdUnico(idEntidade);
					estrutura->setAtivo(ativo);

					listaEntidades.inserirNoFim(estrutura);
					gC.incluirEstrutura(estrutura);
				}
			}

			arquivo.close();

			listaEntidades.inserirNoFim(jogador1);
			gC.incluirJogador1(jogador1);
			hub.setPlayer(jogador1);

			if (jogador2Ativo && jogador2)
			{
				listaEntidades.inserirNoFim(jogador2);
				gC.incluirJogador2(jogador2);
				hub.setPlayer2(jogador2);
			}

		}
	}

	void Fase::carregamentoPadrao()
	{
		
		criarInimigos();
		criarObstaculo();
	}

	void Fase::criarAndarilhos()
	{
		std::ifstream arquivo(caminhoMapa);
		std::string linha;

		if (!arquivo.is_open())
		{
			return;
		}

		std::vector<sf::Vector2f> posicoes;

		int y = 0;

		while (std::getline(arquivo, linha))
		{
			std::istringstream entrada(linha);

			int tile;
			int x = 0;

			while (entrada >> tile)
			{
				if (tile == 6)
				{
					posicoes.push_back(
						sf::Vector2f(TAM_TILE * x, TAM_TILE * y)
					);
				}

				x++;
			}

			y++;
		}

		arquivo.close();

		if (posicoes.empty())
		{
			return;
		}

		int quantidade = sortearQuantidade(MIN, MAX);

		int criados = 0;

		while (!posicoes.empty() && criados < quantidade)
		{
			int indice = rand() % posicoes.size();

			Entidades::Personagens::Andarilho* andarilho =
				new Entidades::Personagens::Andarilho(
					posicoes[indice],
					jogador1
				);

			listaEntidades.inserirNoFim(andarilho);
			gC.incluirInimigo(andarilho);

			posicoes.erase(posicoes.begin() + indice);
			criados++;
		}
	}

	void Fase::criarPlataformas()
	{
		std::ifstream arquivo(caminhoMapa);
		std::string linha;

		if (!arquivo.is_open())
		{
			return;
		}

		std::vector<sf::Vector2f> posicoes;

		int y = 0;

		while (std::getline(arquivo, linha))
		{
			std::istringstream entrada(linha);

			int tile;
			int x = 0;

			while (entrada >> tile)
			{
				if (tile == 2)
				{
					posicoes.push_back(
						sf::Vector2f(TAM_TILE * x, TAM_TILE * y)
					);
				}

				x++;
			}

			y++;
		}

		arquivo.close();

		if (posicoes.empty())
		{
			return;
		}

		int quantidade = sortearQuantidade(MIN, MAX);

		int criadas = 0;

		while (!posicoes.empty() && criadas < quantidade)
		{
			int indice = rand() % posicoes.size();

			Entidades::Obstaculos::Plataforma* plataforma =
				new Entidades::Obstaculos::Plataforma(
					posicoes[indice],
					sf::Vector2f(TAM_TILE, TAM_TILE)
				);

			listaEntidades.inserirNoFim(plataforma);
			gC.incluirObstaculo(plataforma);

			posicoes.erase(posicoes.begin() + indice);
			criadas++;
		}
	}

	bool Fase::jogadorChegouNaPassagem() const
	{
		if (!possuiPassagem)
		{
			return false;
		}

		if (jogador1 && jogador1->ativado())
		{
			if (jogador1->getLimites().intersects(areaPassagem))
			{
				return true;
			}
		}

		if (jogador2Ativo && jogador2 && jogador2->ativado())
		{
			if (jogador2->getLimites().intersects(areaPassagem))
			{
				return true;
			}
		}

		return false;
	}

	void Fase::controladorEstado(int idFase)
	{
		bool jogador1Morreu = jogador1 && !jogador1->vivo();
		bool jogador2Morreu = jogador2Ativo && jogador2 && !jogador2->vivo();

		if (jogador1Morreu || jogador2Morreu)
		{
			mediador->notify(Actions::GAME_OVER);
			return;
		}

		if (idFase == 1)
		{
			/*
				Na fase 1, passa de fase quando o jogador
				chega no tile 9 do mapa.
			*/
			if (jogadorChegouNaPassagem())
			{
				mediador->notify(Actions::PASSOU_DE_FASE);
				return;
			}
		}
		else if (idFase == 2)
		{
			/*
				Na fase 2, termina quando todos os inimigos
				forem derrotados.
			*/
			if (verificarQuantidadeInimigos() == 0)
			{
				mediador->notify(Actions::GAME_OVER);
				return;
			}
		}
	}

	void Fase::salvar() {
		std::ofstream arquivo("salvar/salvar.txt");
		if (arquivo.is_open()) {
			arquivo << id << std::endl;
			arquivo << jogador2Ativo << std::endl;
			arquivo.close();
		}
		listaEntidades.salvar();
	}
	void Fase::criarCenario()
	{
		std::ifstream arquivo(caminhoMapa);
		std::string linha;

		if (!arquivo.is_open())
		{
			return;
		}

		int y = 0;

		while (std::getline(arquivo, linha))
		{
			std::istringstream entrada(linha);

			int tile;
			int x = 0;

			while (entrada >> tile)
			{
				float posX = TAM_TILE * x;
				float posY = TAM_TILE * y;

				if (tile == 1)
				{
					Entidades::Estrutura* estrutura =
						new Entidades::Estrutura(
							sf::Vector2f(posX, posY),
							TipoEstrutura::CHAO,
							sf::Vector2f(TAM_TILE, TAM_TILE)
						);

					listaEntidades.inserirNoFim(estrutura);
					gC.incluirEstrutura(estrutura);
				}
				else if (tile == 3)
				{
					if (jogador1)
					{
						jogador1->setPosicao(posX, posY);
					}
				}
				else if (tile == 4)
				{
					if (jogador2)
					{
						jogador2->setPosicao(posX, posY);
					}
				}
				else if (tile == 9)
				{
					areaPassagem = sf::FloatRect(posX, posY, TAM_TILE, TAM_TILE);
					possuiPassagem = true;
				}

				x++;
			}

			y++;
		}

		arquivo.close();
	}

	int Fase::verificarQuantidadeInimigos()
	{
		return gC.getQuantidadeInimigosAtivos();
	}
}