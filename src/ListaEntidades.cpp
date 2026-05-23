#include "../include/ListaEntidades.h"

namespace Listas
{
    ListaEntidades::ListaEntidades()
    {}

    ListaEntidades::~ListaEntidades()
    {
        limpar();
    }

    void ListaEntidades::executar()
    {
        for (auto it = LEs.getPrimeiro(); it != LEs.getFim(); ++it)
        {
            Entidades::Entidade* ent = *it;

            if (ent)
            {
                ent->executar();
            }
        }
    }

    void ListaEntidades::desenhar()
    {
        for (auto it = LEs.getPrimeiro(); it != LEs.getFim(); ++it)
        {
            Entidades::Entidade* ent = *it;

            if (ent)
            {
                ent->desenhar();
            }
        }
    }

    void ListaEntidades::incluir(Entidades::Entidade* ent)
    {
        if (ent)
        {
            LEs.incluir(ent);
        }
    }

    void ListaEntidades::add(Entidades::Entidade* ent)
    {
        incluir(ent);
    }

    void ListaEntidades::limpar()
    {
        LEs.limpar();
    }

    void ListaEntidades::set_posicao(sf::Vector2f pos)
    {
        for (auto it = LEs.getPrimeiro(); it != LEs.getFim(); ++it)
        {
            Entidades::Entidade* ent = *it;

            if (ent)
            {
                ent->set_posicao(pos);
            }
        }
    }

    int ListaEntidades::getTamanho() const
    {
        return LEs.getTamanho();
    }

    int ListaEntidades::get_tamanho() const
    {
        return getTamanho();
    }

    Lista<Entidades::Entidade>::Iterator<Entidades::Entidade> ListaEntidades::getPrimeiro()
    {
        return LEs.getPrimeiro();
    }

    Lista<Entidades::Entidade>::Iterator<Entidades::Entidade> ListaEntidades::getFim()
    {
        return LEs.getFim();
    }

    Lista<Entidades::Entidade>::Iterator<Entidades::Entidade> ListaEntidades::get_Primeiro()
    {
        return getPrimeiro();
    }

    Lista<Entidades::Entidade>::Iterator<Entidades::Entidade> ListaEntidades::get_Fim()
    {
        return getFim();
    }

    Entidades::Entidade* ListaEntidades::operator[](int indice)
    {
        return LEs[indice];
    }
}