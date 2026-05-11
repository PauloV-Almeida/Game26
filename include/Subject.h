#pragma once
#include <list>
#include "GerenciadorGrafico.h"

namespace Observers {
	class Observer;
}

namespace Gerenciadores {
	class Subject {
	protected:
		std::list<Observers::Observer*> lista_observers;
		std::list<Observers::Observer*>::iterator it;
	public:
		Subject();
		virtual ~Subject();
		virtual void detach(Observers::Observer* pObserver);
		virtual void attach(Observers::Observer* pObserver);
		virtual void notify(sf::Keyboard::Key key_code);
	};
}