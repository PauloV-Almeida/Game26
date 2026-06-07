#include "../include/MenuEstado.h"

menuEstado::~menuEstado()
{
	for (auto& botao : botaoVector) {
		delete botao;
	}
}

menuEstado::menuEstado()
	:State()
{
	fundoMenu.setTexture(*pGG->getTextura(Texturas::fundoMenu));
	fundoMenu.setScale(0.84, 0.7);
	setFigura(&fundoMenu);
}
void menuEstado::execBotoes()
{

	for (const auto& buttons : botaoVector) {
		buttons->desenhar();
	}
}

void menuEstado::executar() {

	pGG->limpar();
	desenhar();
	handleEvent();
	execBotoes();

}

void menuEstado::lidarEvent()
{
	sf::Event ev;
	while (pGG->get_janela()->pollEvent(ev)) {
		switch (ev.type) {
		case sf::Event::Closed:
		{
			mediador->notify(Actions::VOLTAR_1_MENU);
		}
		case  sf::Event::KeyPressed:
		{
			if (ev.key.code == sf::Keyboard::Escape) {
				mediador->notify(Actions::VOLTAR_1_MENU);
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

void menuEstado::mouseClick()
{
	
	for (const auto& x : botaoVector) {
		x->getClicked(mousePos);
	}
}