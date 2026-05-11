#include "../include/Entidades.h"


int Entidades::Entidade::contar(0);
float Entidades::Entidade::velocidade(2.f);

sf::Vector2f Entidades::Entidade::posJogador(200.f, 200.f);

namespace Entidades
{				
	Entidade::Entidade(int indice, sf::Vector2f velo):
		Ente(),
		id(indice),
		gColisao(nullptr),
		vel(velo),
		deCastigo(false),
		massa(1)
	{
	
	}

	Entidade::~Entidade()
	{
	}
}
