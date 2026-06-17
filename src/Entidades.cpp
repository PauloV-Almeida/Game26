#include "../include/Entidades.h"

int Entidades::Entidade::contarEntidades = 0;

namespace Entidades
{
    Entidade::Entidade() :
		posicao(sf::Vector2f(0.f, 0.f)),
        velo(0.f, 0.f),
        buffer()
    {
		idUni = contarEntidades++;
		ativo = 1;
        forma.scale(0.7f, 0.7f);
        forma.setPosition(posicao);
        setFigura(&forma);
    }

    Entidade::Entidade(sf::Vector2f pos) :
		posicao(pos),
        velo(0.f, 0.f),
        buffer()
    {
        idUni = contarEntidades++;
        ativo = 1;
        forma.scale(0.7f, 0.7f);
        forma.setPosition(posicao);
        setFigura(&forma);
    }

    Entidade::~Entidade()
    {}

    const sf::Vector2f Entidade::getCentro()
    {
        sf::Vector2f center;

        center.x = forma.getGlobalBounds().left + forma.getGlobalBounds().width / 2.f;

        center.y = forma.getGlobalBounds().top + forma.getGlobalBounds().height / 2.f;

        return center;
    }

    const sf::Vector2f Entidade::getPosicao()
    {
        return forma.getPosition();
    }

    const int Entidade::getIdUnico() const
    {
        return idUni;
    }

	const sf::FloatRect Entidade::getLimites()
	{
		return forma.getGlobalBounds();
	}

    void Entidade::mover()
    {
		forma.move(velo);
    }

	void Entidade::mudarVelocidade(sf::Vector2f addVel)
	{
		velo += addVel;
	}
    const sf::Vector2f Entidade::getVelocidade() const
    {
        return velo;
    }

    void Entidade::salvarDataBuffer()
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
            break;
        }

        buffer << idUni << " ";
        buffer << ativo << " ";
        buffer << getPosicao().x << " ";
        buffer << getPosicao().y << " ";
        buffer << velo.x << " ";
        buffer << velo.y << " ";
    }

    void Entidade::desativar() {
        ativo = 0;
    }

	bool Entidade::ativado() const {
		return ativo;
	}

	void Entidade::setAtivo(bool at)
	{
		ativo = at;
	}

	void Entidade::setIdUnico(int id)
	{
		idUni = id;
	}

    void Entidade::aplicarGravidade()
	{
		velo.y += gravidade;
	}

	void Entidade::setPosicao(float x, float y)
	{
		forma.setPosition(x, y);
	}

	void Entidade::setVelocidade(float x, float y)
	{
		velo.x = x;
		velo.y = y;
	}
}