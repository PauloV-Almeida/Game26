#include "../include/Eventos.h"

mediadorEventos* mediadorEventos::instancia = nullptr;

mediadorEventos::mediadorEventos() :
    sujeitos()
{}

mediadorEventos::~mediadorEventos()
{
    sujeitos.clear();
}

mediadorEventos* mediadorEventos::getMediadorEventos()
{
    if (instancia == nullptr)
    {
        instancia = new mediadorEventos();
    }

    return instancia;
}

void mediadorEventos::incluirSubject(Subject* sujeito)
{
    if (sujeito)
    {
        sujeitos.push_back(sujeito);
    }
}

void mediadorEventos::notify(Actions action)
{
    for (auto& sujeito : sujeitos)
    {
        if (sujeito)
        {
            sujeito->update(action);
        }
    }
}