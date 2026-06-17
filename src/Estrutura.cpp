#include "../include/Estrutura.h"

namespace Entidades
{
    Estrutura::Estrutura() :
        Entidade(),
        tipoEstrutura(TipoEstrutura::NULO)
    {
        id = Id::Estrutura;
        configurarTextura();
    }

    Estrutura::Estrutura(sf::Vector2f pos, TipoEstrutura tipo) :
        Entidade(pos),
        tipoEstrutura(tipo)
    {
        id = Id::Estrutura;
        configurarTextura();
    }

    Estrutura::Estrutura(sf::Vector2f pos, TipoEstrutura tipo, sf::Vector2f tamanho) :
        Entidade(pos),
        tipoEstrutura(tipo)
    {
        id = Id::Estrutura;
        configurarTextura();
        configurarTamanho(tamanho);
    }

    Estrutura::~Estrutura()
    {}

    TipoEstrutura Estrutura::getTipoEstrutura() const
    {
        return tipoEstrutura;
    }

    void Estrutura::setTipoEstrutura(TipoEstrutura tipo)
    {
        tipoEstrutura = tipo;
        configurarTextura();
    }

    void Estrutura::configurarTextura()
    {
        switch (tipoEstrutura)
        {
        case TipoEstrutura::CHAO:
            forma.setTexture(*pGG->getTextura(Texturas::chao));
            break;

        case TipoEstrutura::PAREDE:
            forma.setTexture(*pGG->getTextura(Texturas::parede));
            break;

        default:
            break;
        }

        setFigura(&forma);
    }

    void Estrutura::configurarTamanho(sf::Vector2f tamanho)
    {
        sf::FloatRect limites = forma.getLocalBounds();

        if (limites.width > 0.f && limites.height > 0.f)
        {
            forma.setScale(
                tamanho.x / limites.width,
                tamanho.y / limites.height
            );
        }
    }

    void Estrutura::executar()
    {
        /*
            Estrutura é fixa.
            Não aplica gravidade e não se move.
            A colisão com ela é tratada pelo GerenciadorColisao.
        */
    }

    std::string Estrutura::salvar()
    {
        Entidade::salvarDataBuffer();

        switch (tipoEstrutura)
        {
        case TipoEstrutura::CHAO:
            buffer << "CHAO ";
            break;

        case TipoEstrutura::PAREDE:
            buffer << "PAREDE ";
            break;

        default:
            buffer << "NULO ";
            break;
        }

        return buffer.str();
    }
}