#include "../include/Entidades.h"

int Entidades::Entidade::contarEntidades = 0;

namespace Entidades
{
    Entidade::Entidade() :
        idUni(contarEntidades++),
        forma(),
        vel(0.f, 0.f),
        ativo(true),
        buffer()
    {
        forma.setPosition(0.f, 0.f);
        setFigura(&forma);
    }

    Entidade::Entidade(sf::Vector2f pos) :
        idUni(contarEntidades++),
        forma(),
        vel(0.f, 0.f),
        ativo(true),
        buffer()
    {
        forma.setPosition(pos);
        setFigura(&forma);
    }

    Entidade::~Entidade()
    {}

    sf::Vector2f Entidade::getCentro() const
    {
        sf::FloatRect limites = forma.getGlobalBounds();

        return sf::Vector2f(
            limites.left + limites.width / 2.f,
            limites.top + limites.height / 2.f
        );
    }

    sf::Vector2f Entidade::getPosicao() const
    {
        return forma.getPosition();
    }

    sf::Vector2f Entidade::getVelocidade() const
    {
        return vel;
    }

    sf::FloatRect Entidade::getLimites() const
    {
        return forma.getGlobalBounds();
    }

    int Entidade::getIdUnico() const
    {
        return idUni;
    }

    bool Entidade::ativado() const
    {
        return ativo;
    }

    void Entidade::setIdUnico(int id)
    {
        idUni = id;
    }

    void Entidade::setAtivo(bool at)
    {
        ativo = at;
    }

    void Entidade::desativar()
    {
        ativo = false;
    }

    void Entidade::setPosicao(float x, float y)
    {
        forma.setPosition(x, y);
    }

    void Entidade::setPosicao(sf::Vector2f pos)
    {
        forma.setPosition(pos);
    }

    void Entidade::setVelocidade(float x, float y)
    {
        vel.x = x;
        vel.y = y;
    }

    void Entidade::setVelocidade(sf::Vector2f novaVel)
    {
        vel = novaVel;
    }

    void Entidade::mudarVelocidade(sf::Vector2f addVel)
    {
        vel += addVel;
    }

    void Entidade::aplicarGravidade()
    {
        vel.y += gravidade;
    }

    void Entidade::mover()
    {
        forma.move(vel);
    }

    void Entidade::salvarEntidade()
    {
        buffer.str("");
        buffer.clear();

        switch (getId())
        {
        case Id::Jogador:
            buffer << "JOGADOR ";
            break;

        case Id::Valkiria:
            buffer << "VALKIRIA ";
            break;

        case Id::Andarilho:
            buffer << "ANDARILHO ";
            break;

        case Id::Espinho:
            buffer << "ESPINHO ";
            break;

        case Id::Thor:
            buffer << "THOR ";
            break;

        case Id::Runa:
            buffer << "RUNA ";
            break;

        case Id::Projetil:
            buffer << "PROJETIL ";
            break;

        case Id::Plataforma:
            buffer << "PLATAFORMA ";
            break;

        case Id::Estrutura:
            buffer << "ESTRUTURA ";
            break;

        default:
            buffer << "NULO ";
            break;
        }

        buffer << idUni << " ";
        buffer << ativo << " ";
        buffer << getPosicao().x << " ";
        buffer << getPosicao().y << " ";
        buffer << vel.x << " ";
        buffer << vel.y << " ";
    }
}