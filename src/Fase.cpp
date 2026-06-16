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
		sf::Event ev;

		while (pGG->get_janela()->pollEvent(ev))
		{
			switch (ev.type)
			{
			case sf::Event::Closed:
				pGG->fechar();
				break;

			case sf::Event::KeyPressed:
				if (ev.key.code == sf::Keyboard::P)
				{
					if (jogador2 && !jogador2Ativo)
					{
						hub.setPlayer2(jogador2);
						jogador2Ativo = true;

						listaEntidades.inserirNoFim(jogador2);
						gC.incluirJogador2(jogador2);
					}
				}

				if (ev.key.code == sf::Keyboard::Escape)
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
		pGG->limpar();
		pGG->desenharFundo();

		if (jogador1)
		{
			if (jogador2Ativo && jogador2)
			{
				sf::Vector2f centro;
				centro.x = (jogador1->getCentro().x + jogador2->getCentro().x) / 2.f;
				centro.y = (jogador1->getCentro().y + jogador2->getCentro().y) / 2.f;

				view.setCenter(centro);
			}
			else
			{
				view.setCenter(jogador1->getCentro());
			}
		}

		pGG->setView(view);
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

		if (!arquivo.is_open())
		{
			criarCenario();
			carregamentoPadrao();
			return;
		}

		std::string linha;

		std::getline(arquivo, linha);
		std::istringstream linhaId(linha);
		linhaId >> id;

		std::getline(arquivo, linha);
		std::istringstream linhaJ2(linha);
		linhaJ2 >> jogador2Ativo;

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
					jogador->setNumVidas(vida);
					jogador->setNoChao(noChao);
					jogador->setTravado(travado);
					jogador->setVelocidadeMovimento(velocidadeMovimento);
					jogador->setVelocidadeMaxima(velocidadeMaxima);
					jogador->setForcaPulo(forcaPulo);
					jogador->setDanoAtaque(danoAtaque);
					jogador->setVenceu(venceu);
				}
			}
			else if (tipoEntidade == "ANDARILHO")
			{
				Entidades::Personagens::Andarilho* andarilho =
					new Entidades::Personagens::Andarilho(
						sf::Vector2f(posicaoX, posicaoY),
						jogador1,
						jogador2Ativo ? jogador2 : nullptr
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
						jogador1,
						jogador2Ativo ? jogador2 : nullptr
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
						sf::Vector2f(posicaoX, posicaoY),
						jogador1,
						jogador2Ativo ? jogador2 : nullptr
					);

				thor->setProjetilAtual(projetil);

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

	void Fase::carregamentoPadrao()
	{
		
		criarInimigos();
		criarObstaculo();
	}

	void Fase::criarAndarilhos()
	{
		int maxA = sortearQuantidade(MIN, MAX);
		for (int i = 0; i < maxA; i++)
		{
			Entidades::Personagens::Andarilho* andarilho =
				new Entidades::Personagens::Andarilho(
					sf::Vector2f(2500.f + (250.f * i), 300.f),
					jogador1,
					jogador2Ativo ? jogador2 : nullptr
				);

			listaEntidades.inserirNoFim(andarilho);
			gC.incluirInimigo(andarilho);
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

		int quantidade = MIN + rand() % (MAX - MIN + 1);
		int criadas = 0;

		int y = 0;

		while (std::getline(arquivo, linha) && criadas < quantidade)
		{
			int x = 0;

			for (auto& num : linha)
			{
				if (criadas >= quantidade)
				{
					break;
				}

				float posX = TAM_TILE * x;
				float posY = TAM_TILE * y;

				if (num == '2')
				{
					Entidades::Obstaculos::Plataforma* plataforma =
						new Entidades::Obstaculos::Plataforma(
							sf::Vector2f(posX, posY),
							sf::Vector2f(TAM_TILE, TAM_TILE)
						);

					listaEntidades.inserirNoFim(plataforma);
					gC.incluirObstaculo(plataforma);

					criadas++;
				}

				x++;
			}

			y++;
		}

		arquivo.close();
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
		std::ofstream arquivo("salvar/save.txt");
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

		if (arquivo.is_open())
		{
			int y = 0;

			while (std::getline(arquivo, linha))
			{
				int x = 0;

				for (auto& num : linha)
				{
					float posX = TAM_TILE * x;
					float posY = TAM_TILE * y;

					if (num == '1')
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
					else if (num == '9')
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
	}

	int Fase::verificarQuantidadeInimigos()
	{
		return gC.getQuantidadeInimigosAtivos();
	}
}