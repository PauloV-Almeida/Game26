#include "../include/FimDeJogo.h"

FimJogo::FimJogo(Fases::Fase* fase)
	:pFase(fase), nomeJogador()
{
	pontuacao = fase->getPontuacaoTotal();

	carregarBotoes();
	textoNomeJogador.setPosition(400, 400);
	textoNomeJogador.setCharacterSize(35);
	textoNomeJogador.setFont(*(pGG->getFont()));
	textoNomeJogador.setString("NOME: ");
	setFigura(&textoNomeJogador);
}

FimJogo::~FimJogo()
{}
void FimJogo::salvarRanking()
{
	std::ofstream arquivo("../salvar/ranking.txt", std::ios::app);
	if (arquivo.is_open()) {
		arquivo << nomeJogador << " " << pontuacao << std::endl;
		arquivo.close();
	}
}
void FimJogo::executar() {
	pGG->limpar();
	setFigura(&imgMenu);
	desenhar();
	lidarEvent();
	execButtons();
	setFigura(&textoNomeJogador);
	std::stringstream texto;
	texto << "NOME: " << nomeJogador;
	textoNomeJogador.setString(texto.str());
	desenhar();


}

void GameOver::handleEvent()
{
	/***
	* @brief Gerencia o evento de teclado e mouse
	* @return void
	*/

	sf::Event ev;
	while (pGerGraphic->getWindow()->pollEvent(ev)) {
		switch (ev.type) {
		case sf::Event::Closed:
		{
			mediador->notify(Actions::VOLTAR_1_MENU);
			break;
		}
		case  sf::Event::KeyPressed:
		{
			if (ev.key.code == sf::Keyboard::A) {
				nomeJogador.push_back('A');
			}
			if (ev.key.code == sf::Keyboard::B) {
				nomeJogador.push_back('B');

			}
			if (ev.key.code == sf::Keyboard::C) {
				nomeJogador.push_back('C');

			}
			if (ev.key.code == sf::Keyboard::D) {
				nomeJogador.push_back('D');

			}
			if (ev.key.code == sf::Keyboard::E) {
				nomeJogador.push_back('E');

			}
			if (ev.key.code == sf::Keyboard::F) {
				nomeJogador.push_back('F');

			}
			if (ev.key.code == sf::Keyboard::G) {
				nomeJogador.push_back('G');
			}
			if (ev.key.code == sf::Keyboard::H) {
				nomeJogador.push_back('H');

			}
			if (ev.key.code == sf::Keyboard::I) {
				nomeJogador.push_back('I');

			}
			if (ev.key.code == sf::Keyboard::J) {
				nomeJogador.push_back('J');

			}
			if (ev.key.code == sf::Keyboard::K) {
				nomeJogador.push_back('K');

			}
			if (ev.key.code == sf::Keyboard::L) {
				nomeJogador.push_back('L');

			}
			if (ev.key.code == sf::Keyboard::M) {
				nomeJogador.push_back('M');

			}
			if (ev.key.code == sf::Keyboard::N) {
				nomeJogador.push_back('N');

			}
			if (ev.key.code == sf::Keyboard::O) {
				nomeJogador.push_back('O');

			}
			if (ev.key.code == sf::Keyboard::P) {
				nomeJogador.push_back('P');

			}
			if (ev.key.code == sf::Keyboard::Q) {
				nomeJogador.push_back('Q');

			}
			if (ev.key.code == sf::Keyboard::R) {
				nomeJogador.push_back('R');

			}
			if (ev.key.code == sf::Keyboard::S) {
				nomeJogador.push_back('S');

			}
			if (ev.key.code == sf::Keyboard::T) {
				nomeJogador.push_back('T');

			}
			if (ev.key.code == sf::Keyboard::U) {
				nomeJogador.push_back('U');

			}
			if (ev.key.code == sf::Keyboard::V) {
				nomeJogador.push_back('V');

			}
			if (ev.key.code == sf::Keyboard::W) {
				nomeJogador.push_back('W');

			}
			if (ev.key.code == sf::Keyboard::X) {
				nomeJogador.push_back('X');

			}
			if (ev.key.code == sf::Keyboard::Y) {
				nomeJogador.push_back('Y');

			}
			if (ev.key.code == sf::Keyboard::Z) {
				nomeJogador.push_back('Z');

			}



			if (ev.key.code == sf::Keyboard::BackSpace) {
				if (!nomeJogador.empty()) {
					nomeJogador.pop_back();
				}
			}
			if (ev.key.code == sf::Keyboard::Enter) {
				salvarRanking();
				mediador->notify(Actions::VOLTAR_2_MENUS);
			}

			if (ev.key.code == sf::Keyboard::Escape) {
				mediador->notify(Actions::VOLTAR_2_MENUS);
			}
			break;
		}
		case sf::Event::MouseButtonPressed:
		{
			if (ev.mouseButton.button == sf::Mouse::Left) {
				mouseClick();
			}
		}
		default:
			break;
		}
	}
}

void GameOver::carregarBotoes() {
	buttonVector.push_back(new Entidades::Button(sf::Vector2f(200.f, 300.f), "Voltar", Actions::VOLTAR_2_MENUS));
}