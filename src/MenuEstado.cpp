#include "../include/MenuEstado.h"

menuEstado::~menuEstado()
{
	for (auto& botao : botaoVector) {
		delete botao;
	}
}

menuEstado::menuEstado() :
	State(),
	botaoVector(),
	fundoMenu()
{
	fundoMenu.setTexture(*pGG->getTextura(Texturas::fundoMenu));
	fundoMenu.setScale(1.f, 1.f);

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
	lidarEvent();
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
	pGG->atualizarMousePos();

	for (const auto& botao : botaoVector)
	{
		botao->getClicked(pGG->getMousePos());
	}
}