#pragma once
#include "Entidades.h"
#include "Jogador.h"
#include "TipoEstrutura.h"

namespace Entidades {
	class Estrutura : public Entidade
	{
	private:
		TipoEstrutura tipo;

	public:
		Estrutura(sf::Vector2f pos, TipoEstrutura tipoE);
		Estrutura();
		~Estrutura();
		void formatarEstrutura(TipoEstrutura tipoE);
		void executar();
		std::string salvar();
		void salvarEstrutura();
	};
}