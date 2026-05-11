#include "../include/Estado.h"

#include "../include/GerenciadorEstado.h"

namespace Estados
{
	Gerenciadores::GerenciadorEstado* Estado::pEG(Gerenciadores::GerenciadorEstado::get_instance());

	Estado::Estado(int id) : id_estado(id)
	{
		pEG->add_estado(this);
	}

	Estado::~Estado()
	{
		pEG = nullptr;
	}

	void Estado::setGerenciadorEstado(Gerenciadores::GerenciadorEstado* p)
	{
		pEG = p;
	}

	int Estado::getId() const
	{
		return id_estado;
	}

	const bool Estado::get_ativo()
	{
		return (id_estado == pEG->get_AtualEstadoID() ? true : false);
	}

}