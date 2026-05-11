#include "../include/Observer.h"

namespace Observers {
    Observer::Observer()
    {
        this->pGE = Gerenciadores::GerenciadorEventos::get_instance();
        this->pEG = Gerenciadores::GerenciadorEstado::get_instance();
        this->pGG = Gerenciadores::GerenciadorGrafico::get_instance();
    }

    Observer::~Observer()
    {
        pGE->detach(this);
    }
}