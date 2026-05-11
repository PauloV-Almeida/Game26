#include "../include/Subject.h"
#include "../include/Observer.h"


namespace Gerenciadores
{

    Subject::Subject()
    {
        lista_observers.clear();
    }
    Subject:: ~Subject()
    {
        for (it = lista_observers.begin(); it != lista_observers.end(); it++)
        {
            delete(*it);
        }
        lista_observers.clear();

    }
    void  Subject::attach(Observers::Observer* pObserver)
    {
        lista_observers.push_back(pObserver);
    }

    void Subject::detach(Observers::Observer* pObserver)
    {
        lista_observers.remove(pObserver);
    }
    void Subject::notify(sf::Keyboard::Key key_code)
    {
        for (it = lista_observers.begin(); it != lista_observers.end(); it++)
        {
            (*it)->executar((key_code));
        }
    }
}