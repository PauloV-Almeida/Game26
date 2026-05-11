#include "../include/ListaEntidades.h"

namespace Listas
{
	ListaEntidades::ListaEntidades()
	{
	}
	ListaEntidades::~ListaEntidades()
	{
	}
	void ListaEntidades::executar()
	{
		Listas::Lista<Entidades::Entidade>::Iterator<Entidades::Entidade> aux = lEnt.get_Primeiro();
		while (aux != nullptr)
		{
			(*aux)->executar();
			aux++;
		}
	}
	void ListaEntidades::desenhar()
	{
		Listas::Lista<Entidades::Entidade>::Iterator<Entidades::Entidade> aux = lEnt.get_Primeiro();
		while (aux != nullptr)
		{
			(*aux)->desenhar();
			aux++;
		}
	}
	void ListaEntidades::add(Entidades::Entidade* ent)
	{
		lEnt.empurrar(ent);
	}
	void ListaEntidades::limpar()
	{
		lEnt.clear();
	}
	void ListaEntidades::set_posicao(sf::Vector2f pos)
	{
		Listas::Lista<Entidades::Entidade>::Iterator<Entidades::Entidade> aux = lEnt.get_Primeiro();
		while (aux != nullptr)
		{
			(*aux)->set_posicao(pos);
			aux++;
		}
	}
	/*const int ListaEntidades::get_nNeutralizados()
	{
		int n = 0;
		Listas::Lista<Entidades::Entidade>::Iterator<Entidades::Entidade> aux = list.get_Primeiro();
		while (aux != nullptr)
		{
			if (!((*aux)->get_vivo()))
			{
				n++;
			}
			aux++;
		}
		return n;
	}*/
}