#include "../include/GerenciadorEstado.h"
#include <iostream>

namespace Gerenciadores
{
	GerenciadorEstado* GerenciadorEstado::instance = nullptr;

	GerenciadorEstado* GerenciadorEstado::get_instance()
	{
		if (instance == nullptr)
		{
			instance = new GerenciadorEstado();
		}
		return instance;
	}

	GerenciadorEstado::GerenciadorEstado() :
		AtualEstado(0)
	{
		vector_estados.resize(8);
	}

	GerenciadorEstado::~GerenciadorEstado()
	{
		for (int i = 0; i < vector_estados.size(); i++)
		{
			delete vector_estados[i];
		}
	}
	void GerenciadorEstado::set_AtualEstado(int i)
	{
		AtualEstado = i;
	}

	int GerenciadorEstado::get_AtualEstadoID()
	{
		return AtualEstado;
	}

	void GerenciadorEstado::add_estado(Estados::Estado* pEstado)
	{
		try
		{
			vector_estados.at(pEstado->getId()) = pEstado;
		}
		catch (const std::out_of_range& oor)
		{
			std::cerr << "Erro: ID do estado fora do intervalo permitido." << std::endl;
		}
	}

	void GerenciadorEstado::reseta_AtualEstado()
	{
		if (vector_estados[AtualEstado])
			vector_estados[AtualEstado]->reiniciar();
	}

	void GerenciadorEstado::executar()
	{
		if(vector_estados[AtualEstado])
			vector_estados[AtualEstado]->executar();
	}
}