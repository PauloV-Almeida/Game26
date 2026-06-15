#pragma once

#include "Entidades.h"
#include "TipoEstrutura.h"

namespace Entidades
{
    class Estrutura : public Entidade
    {
    private:
        TipoEstrutura tipoEstrutura;

    public:
        Estrutura();
        Estrutura(sf::Vector2f pos, TipoEstrutura tipo);
        Estrutura(sf::Vector2f pos, TipoEstrutura tipo, sf::Vector2f tamanho);
        virtual ~Estrutura();

        TipoEstrutura getTipoEstrutura() const;
        void setTipoEstrutura(TipoEstrutura tipo);

        void configurarTextura();
        void configurarTamanho(sf::Vector2f tamanho);

        void executar();
        void desenhar();

        std::string salvar();
    };
}