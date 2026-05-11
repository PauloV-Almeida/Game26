#pragma once

#include "GerenciadorGrafico.h"
#include "GerenciadorEstado.h"


#include <iostream>
#include "Subject.h"

namespace Observadores {
	class Observer;
}

namespace Gerenciadores {
	class GerenciadorEventos : public Subject {
	private:

		GerenciadorGrafico* pGG;
		//Singleton
		static GerenciadorEventos* instance; 
		GerenciadorEventos();
	public:
		~GerenciadorEventos();
		static GerenciadorEventos* get_instance();
		void executar();

	};
}