#pragma once

#include "../include/Entidades.h"
#include "../include/Lista.h"

namespace Listas
{
    class ListaEntidades
    {
    private:
        Lista<Entidades::Entidade> LEs;

    public:
        ListaEntidades();
        ~ListaEntidades();

        ListaEntidades(const ListaEntidades&) = delete;
        ListaEntidades& operator=(const ListaEntidades&) = delete;

        void executar();
        void desenhar();

        void incluir(Entidades::Entidade* ent);
        void add(Entidades::Entidade* ent);

        void limpar();

        void set_posicao(sf::Vector2f pos);

        int getTamanho() const;
        int get_tamanho() const;

        Lista<Entidades::Entidade>::Iterator<Entidades::Entidade> getPrimeiro();
        Lista<Entidades::Entidade>::Iterator<Entidades::Entidade> getFim();

        Lista<Entidades::Entidade>::Iterator<Entidades::Entidade> get_Primeiro();
        Lista<Entidades::Entidade>::Iterator<Entidades::Entidade> get_Fim();

        Entidades::Entidade* operator[](int indice);
    };
}