#pragma once
//Referencia Monitor Felipe Simbalista
#include "Lista.h"
#include "Entidades.h"

namespace Listas
{
    class ListaEntidades
    {
    private:
        Lista<Entidades::Entidade*> lista;
        Lista<Entidades::Entidade*>::Iterator it;

    public:
        ListaEntidades();
        ~ListaEntidades();

        void limpar();

        void inserirNoFim(Entidades::Entidade* ent);
        void inserirNoInicio(Entidades::Entidade* ent);

        void removerDoInicio();
        void removerDoFim();

        const int getTam() const;

        Lista<Entidades::Entidade*>::Iterator apagar(Lista<Entidades::Entidade*>::Iterator iter);
        Lista<Entidades::Entidade*>::Iterator inicio();
        Lista<Entidades::Entidade*>::Iterator fim();

        void executar();
        void salvar();
        void desenhar();
        void desalocar();
    };
} using namespace Listas;