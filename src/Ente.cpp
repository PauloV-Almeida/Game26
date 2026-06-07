#include "../include/Ente.h"

Gerenciadores::GerenciadorGrafico* Ente::pGG = Gerenciadores::GerenciadorGrafico::get_instance();

Ente::Ente() : id(Id::NULO)
{
	figura = nullptr;
}

Ente::~Ente()
{
}

void Ente::desenhar()
{
	pGG->desenharEnte(this);
}

Id Ente::getId()
{
	return id;
}

sf::Drawable* Ente::getFigura()
{
	return figura;
}

void Ente::setFigura(sf::Drawable* fig)
{
	figura = fig;
}