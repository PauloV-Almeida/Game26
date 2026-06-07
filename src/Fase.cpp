#include "../include/Fase.h"

namespace Fases {

	Fase::Fase(Entidades::Personagens::Jogador* jogador1, Entidades::Personagens::Jogador* jogador2, bool carregaArquivo) :
		State(),
		jogador1(jogador1),
		jogador2(jogador2),
		jogador2Ativo(0),
		view(pGG->getPadraoView())
	{
		mediador = mediadorEventos::getMediadorEventos();
		pontuacaoTotal = 0;
		id = 0;
		Entidades::Personagens::Inimigo::zerarInimigos();
		gerenciadorColisao.incluirJogador1(jogador1);
		listaEntidades.inserirNoFim(jogador1);
		hub.setPlayer(jogador1);
		pGG->setView(view);
	}



	Fase::~Fase() {
		listaEntidades.desalocar();
	}

	void Fase::lidarEvent()
	{

		if (jogador2Ativo) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				jogador2->movimentar(Directions::LEFT);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				jogador2->movimentar(Directions::RIGHT);
			}
			else {
				jogador2->stopAxisX();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {

				jogador2->movimentar(Directions::UP);

			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				jogador2->movimentar(Directions::DOWN);
			}

		}

		//Ações do jogador principal
		if (jogador1) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				jogador1->movimentar(Directions::LEFT);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				jogador1->movimentar(Directions::RIGHT);
			}
			else {
				jogador1->stopAxisX();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				jogador1->movimentar(Directions::UP);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				jogador1->movimentar(Directions::DOWN);
			}

		}
		sf::Event ev;
		while (pGG->get_janela()->pollEvent(ev)) {
			switch (ev.type) {
			case sf::Event::Closed:
				pGG->fechar();
				break;
			case sf::Event::KeyPressed:
				if (ev.key.code == sf::Keyboard::P) {
					if (!jogador2Ativo) {
						hub.setPlayer2(jogador2);
						jogador2Ativo = 1;
						listaEntidades.inserirNoFim(jogador2);
						gerenciadorColisao.incluirJogador2(jogador2);
					}
				}
				if (ev.key.code == sf::Keyboard::Escape) {
					mediador->notify(Actions::PAUSE);
				}
				break;
			}
		}
	}

	void Fase::executarJanela()
	{
		pGG->limpar();
		pGG->desenharFundo();
		pGG->setView(view);
		if (jogador2Ativo) {
			sf::Vector2f centro;
			centro.x = (jogador1->getCentro().x + jogador2->getCentro().x) / 2.f;
			centro.y = (jogador1->getCentro().y + jogador2->getCentro().y) / 2.f;
			view.setCenter(centro);
		}
		else {
			view.setCenter(jogador1->getCentro());
		}

	}

	int Fase::getPontuacaoTotal()
	{
		return pontuacaoTotal;
	}

	void Fase::carregarSalvamento()
	{
		Entidades::Personagens::Inimigo::zerarInimigos();
		hub.setPlayer(jogador1);
		pGG->setView(view);


		std::ifstream arquivo("../salvar/salvar.txt");
		std::string linha;
		if (arquivo.is_open()) {
			std::getline(arquivo, linha);
			std::getline(arquivo, linha);
			std::istringstream linhaOutput(linha);
			linhaOutput >> jogador2Ativo;
			std::map<int, Entidades::Personagens::Andarilho*> AndarilhosMap;
			std::map<int, Entidades::Personagens::Thor*> ThorMap;
			std::map<int, Entidades::Personagens::Personagem*> personagensMap;
			//std::vector<Entidades::Projetil*> projeteis;

			while (std::getline(arquivo, linha)) {

				std::istringstream linhaOutput(linha);
				
				std::string tipoEntidade;
				int idEntidade, ativo;
				float posicaoX, posicaoY, velocidadeX, velocidadeY;
				
				int vida, pulos;
				
				int nivelMaldade;
				
				int pontuacao;
				bool jogadorDois;
				
				int forca;
				
				int hmax, hmin;
				float velocidade;
				bool obstaculou;
			
				float largura;
				
				float altura;

				linhaOutput >> tipoEntidade;

				if (tipoEntidade == "JOGADOR") {
					linhaOutput >> idEntidade >> ativo >> posicaoX >> posicaoY >> velocidadeX >> velocidadeY >> vida >> pulos >> pontuacao >> jogadorDois;

					if (!jogadorDois) {
						jogador1->setId(idEntidade);
						jogador1->setAtivo(ativo);
						jogador1->setPosicao(posicaoX, posicaoY);
						jogador1->setVelocidade(velocidadeX, velocidadeY);
						jogador1->setVida(vida);
						jogador1->setPulos(pulos);
						jogador1->setPontuacao(pontuacao);
						personagensMap.emplace(idEntidade, jogador1);
					}
					else {
						jogador2->setId(idEntidade);
						jogador2->setAtivo(ativo);
						jogador2->setPosicao(posicaoX, posicaoY);
						jogador2->setVelocidade(velocidadeX, velocidadeY);
						jogador2->setVida(vida);
						jogador2->setPulos(pulos);
						jogador2->setPontuacao(pontuacao);
						personagensMap.emplace(idEntidade, jogador2);
					}
				}
				else if (tipoEntidade == "Andarilho") {
					linhaOutput >> idEntidade >> ativo >> posicaoX >> posicaoY >> velocidadeX >> velocidadeY >> vida >> pulos >> nivelMaldade >> Andarilhomap;
					Entidades::Personagens::Andarilho* Andarilho = new Entidades::Personagens::Andarilho(sf::Vector2f(posicaoX, posicaoY), jogador1);
					listaEntidades.inserirNoFim(Andarilho);
					gerenciadorColisao.incluirInimigo(Andarilho);
					Andarilho->setId(idEntidade);
					Andarilho->setAtivo(ativo);
					Andarilho->setVida(vida);
					Andarilho->setPulos(pulos);
					Andarilho->setNivelMaldade(nivelMaldade);
					personagensMap.emplace(idEntidade, Andarilho);
					AndarilhosMap.emplace(idEntidade, Andarilho);
				}
				else if (tipoEntidade == "Thor") {
					linhaOutput >> idEntidade >> ativo >> posicaoX >> posicaoY >> velocidadeX >> velocidadeY >> vida >> pulos >> nivelMaldade >> thor;
					Entidades::Personagens::thor* thor = new Entidades::Personagens::Thor(sf::Vector2f(posicaoX, posicaoY), jogador1);
					listaEntidades.inserirNoFim(thor);
					gerenciadorColisao.incluirInimigo(thor);
					thor->setId(idEntidade);
					thor->setAtivo(ativo);
					thor->setVida(vida);
					thor->setPulos(pulos);
					thor->setNivelMaldade(nivelMaldade);
					thor->setId(idEntidade);
					personagensMap.emplace(idEntidade, thor);
				}
				else if (tipoEntidade == "Valkiria") {
					linhaOutput >> idEntidade >> ativo >> posicaoX >> posicaoY >> velocidadeX >> velocidadeY >> vida >> pulos >> nivelMaldade >> forca;
					Entidades::Personagens::Valkiria* valkiria = new Entidades::Personagens::Valkiria(sf::Vector2f(posicaoX, posicaoY), jogador1, forca);
					listaEntidades.inserirNoFim(valkiria);
					gerenciadorColisao.incluirInimigo(valkiria);
					valkiria->setId(idEntidade);
					valkiria->setAtivo(ativo);
					valkiria->setVida(vida);
					valkiria->setPulos(pulos);
					valkiria->setNivelMaldade(nivelMaldade);
					personagensMap.emplace(idEntidade, valkiria);
				}
				else if (tipoEntidade == "PLATAFORMA") {
					linhaOutput >> idEntidade >> ativo >> posicaoX >> posicaoY >> velocidadeX >> velocidadeY >> velocidade >> hmax >> hmin >> obstaculou;
					Entidades::Obstaculos::Plataforma* plat = new Entidades::Obstaculos::Plataforma(sf::Vector2f(posicaoX, posicaoY), velocidade, hmax, hmin);
					listaEntidades.inserirNoFim(plat);
					gerenciadorColisao.incluirObstaculo(plat);
					plat->setVelocidade(velocidadeX, velocidadeY);
				}
				else if (tipoEntidade == "Runa") {
					linhaOutput >> idEntidade >> ativo >> posicaoX >> posicaoY >> velocidadeX >> velocidadeY >> largura >> obstaculou;
					Entidades::Obstaculos::Runa* runa = new Entidades::Obstaculos::Runa(sf::Vector2f(posicaoX, posicaoY), largura);
					listaEntidades.inserirNoFim(runa);
					gerenciadorColisao.incluirObstaculo(runa);
					runa->setVelocidade(velocidadeX, velocidadeY);
					runa->setObstaculou(obstaculou);
				}
				else if (tipoEntidade == "ESPINHOVENENOSO") {
					linhaOutput >> idEntidade >> ativo >> posicaoX >> posicaoY >> velocidadeX >> velocidadeY >> altura;
					Entidades::Obstaculos::EspinhoVenenoso* espinhoV = new Entidades::Obstaculos::EspinhoVenenoso(sf::Vector2f(posicaoX, posicaoY), altura);
					listaEntidades.inserirNoFim(espinhoV);
					gerenciadorColisao.incluirObstaculo(espinhoV);
				}
				/*else if (tipoEntidade == "PROJETIL") {
					linhaOutput >> idEntidade >> ativo >> posicaoX >> posicaoY >> velocidadeX >> velocidadeY >> Projetil;
					Entidades::Projetil* projetil = new Entidades::Projetil(sf::Vector2f(posicaoX, posicaoY));
					projetil->setVelocidade(velocidadeX, velocidadeY);
					projetil->setAtivo(ativo);
					listaEntidades.inserirNoFim(projetil);
					gerenciadorColisao.incluirProjetil(projetil);
					projeteis.push_back(projetil);
				}*/
			}

			/*for (auto& projet : projeteis) {
				for (auto& personagem : personagensMap) {
					if (projet->getIdDono() == personagem.first) {
						projet->setDono(personagem.second);
					}
				}
			}*/

			
			/*for (auto& thor : ThorMap) {
				
			}*/
		}
		if (jogador2Ativo) {
			listaEntidades.inserirNoFim(jogador2);
			gerenciadorColisao.incluirJogador2(jogador2);
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
		for (int i = 0; i < 3; i++) {
			Entidades::Personagens::Andarilho* andarilho = new Entidades::Personagens::Andarilho(sf::Vector2f(2500 + (250 * i), 300), jogador1);
			listaEntidades.inserirNoFim(andarilho);
			gerenciadorColisao.incluirInimigo(andarilho);
		}

	}

	void Fase::criarPlataformas()
	{
		std::ifstream arquivo("../assents/mapaFloGelo.txt");
		std::string linha;
		if (arquivo.is_open()) {
			int y = 0;
			while (std::getline(arquivo, linha)) {

				int i = 0;
				for (auto& num : linha) {
					if (num == '2') {
						Entidades::Obstaculos::Plataforma* plat = new Entidades::Obstaculos::Plataforma(sf::Vector2f((100 * i), 100 * y), (3 + (rand() % 5)), (y * 100) + 250, (y * 100) - 250);
						listaEntidades.inserirNoFim(plat);
						gerenciadorColisao.incluirObstaculo(plat);
					}
					if (num == '3') {
						if (rand() % 2) {
							Entidades::Obstaculos::Plataforma* plat = new Entidades::Obstaculos::Plataforma(sf::Vector2f((100 * i), 100 * y), (3 + (rand() % 5)), (y * 100) + 250, (y * 100) - 250);
							listaEntidades.inserirNoFim(plat);
							gerenciadorColisao.incluirObstaculo(plat);
						}
					}
					i++;
				}
				y++;
			}
			arquivo.close();
		}
	}

	void Fase::controladorEstado(int idFase)
	{
		if (idFase == 1) {
			if (!jogador1->vivo() || !jogador2->vivo())
			{
				mediador->notify(Actions::GAME_OVER);
			}
			if (verificarQuantidadeInimigos() == 0) {
				mediador->notify(Actions::PASSOU_DE_FASE);
			}
		}
		if (idFase == 2) {
			if (!jogador1->vivo() || !jogador2->vivo())
			{
				mediador->notify(Actions::GAME_OVER);
			}
			if (verificarQuantidadeInimigos() == 0) {
				mediador->notify(Actions::GAME_OVER);
			}
		}
	}

	void Fase::salvar() {
		std::ofstream arquivo("save.txt");
		if (arquivo.is_open()) {
			arquivo << id << std::endl;
			arquivo << jogador2Ativo << std::endl;
			arquivo.close();
		}
		listaEntidades.salvar();
	}
	void Fase::criarCenario()
	{
		std::ifstream arquivo("../assents/mapaFloGelo.txt");
		std::string linha;
		if (arquivo.is_open()) {
			int y = 0;
			while (std::getline(arquivo, linha)) {

				int i = 0;
				for (auto& num : linha) {
					if (num == '1') {
						Entidades::Estrutura* estrutura = new Entidades::Estrutura(sf::Vector2f((100 * i), 100 * y), TipoEstrutura::CHAO);
						listaEntidades.inserirNoFim(estrutura);
						gerenciadorColisao.incluirEstrutura(estrutura);
					}
					i++;
				}
				y++;
			}
			arquivo.close();
		}
	}

	int Fase::verificarQuantidadeInimigos()
	{
		return Entidades::Personagens::Inimigo::getQuantidadeInimigos();
	}
}