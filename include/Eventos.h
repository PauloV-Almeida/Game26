#pragma once

#include "Subject.h"
#include "Acoes.h"

#include <vector>

class mediadorEventos
{
private:
    static mediadorEventos* instancia;
    std::vector<Subject*> sujeitos;

private:
    mediadorEventos();

public:
    ~mediadorEventos();

    static mediadorEventos* getMediadorEventos();

    void incluirSubject(Subject* sujeito);
    void notify(Actions action);
};