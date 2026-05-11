#pragma once

#include "../include/Entidades.h"
#include "../include/Lista.h"

namespace Listas
{
	class ListaEntidades
    {
    private:
        Listas::Lista<Entidades::Entidade> lEnt;
    public:
        ListaEntidades();
        ~ListaEntidades();

        void executar();
        void desenhar();
        void add(Entidades::Entidade* ent);

        void limpar();
        //void save(std::ofstream& file);

        void set_posicao(sf::Vector2f pos);

        const int get_tamanho() const { return lEnt.get_Tamanho(); }
        //const int get_nNeutralizados();
        Listas::Lista<Entidades::Entidade>::Iterator<Entidades::Entidade> get_Primeiro() { return lEnt.get_Primeiro(); }
    };
}
