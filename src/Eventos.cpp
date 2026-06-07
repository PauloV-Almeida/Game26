#include "../include/Eventos.h"
#include <iostream>
mediadorEventos* mediadorEventos::pMediadorEventos = nullptr;

mediadorEventos::mediadorEventos() {

}
mediadorEventos::~mediadorEventos() {

}


void mediadorEventos::incluirSubject(Subject* subject)
{
    vectorSubjects.push_back(subject);
}

mediadorEventos* mediadorEventos::getMediadorEventos()
{
    if (pMediadorEventos == nullptr) {
        pMediadorEventos = new mediadorEventos();
    }
    return pMediadorEventos;
}

void mediadorEventos::notify(Actions act) {
    for (const auto& subject : vectorSubjects) {
        subject->update(act);
    }
}