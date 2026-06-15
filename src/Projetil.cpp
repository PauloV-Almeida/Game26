#include "../include/Projetil.h"
#include "../include/Jogador.h"
#include "../include/Estrutura.h"

#include <cmath>

namespace Entidades
{
    Projetil::Projetil() :
        Entidade(),
        dano(3),
        velocidadeInicial(7.0f),
        posicaoAlvo(0.f, 0.f),
        lancado(false)
    {
        id = Id::Projetil;
        ativo = false;

        forma.setTexture(*pGG->getTextura(Texturas::projetil));
        setFigura(&forma);
    }

    Projetil::Projetil(sf::Vector2f posInicial, sf::Vector2f alvo) :
        Entidade(posInicial),
        dano(3),
        velocidadeInicial(7.0f),
        posicaoAlvo(alvo),
        lancado(false)
    {
        id = Id::Projetil;

        forma.setTexture(*pGG->getTextura(Texturas::projetil));
        forma.setPosition(posInicial);
        setFigura(&forma);

        lancar(posInicial, alvo);
    }

    Projetil::Projetil(sf::Vector2f posInicial, sf::Vector2f alvo, float velocidade, int danoBase) :
        Entidade(posInicial),
        dano(danoBase),
        velocidadeInicial(velocidade),
        posicaoAlvo(alvo),
        lancado(false)
    {
        id = Id::Projetil;

        forma.setTexture(*pGG->getTextura(Texturas::projetil));
        forma.setPosition(posInicial);
        setFigura(&forma);

        lancar(posInicial, alvo);
    }

    Projetil::~Projetil()
    {}

    int Projetil::getDano() const
    {
        return dano;
    }

    bool Projetil::foiLancado() const
    {
        return lancado;
    }

    sf::Vector2f Projetil::getPosicaoAlvo() const
    {
        return posicaoAlvo;
    }

    void Projetil::setDano(int danoBase)
    {
        if (danoBase < 0)
        {
            danoBase = 0;
        }

        dano = danoBase;
    }

    void Projetil::setVelocidadeInicial(float velocidade)
    {
        if (velocidade < 0.f)
        {
            velocidade = 0.f;
        }

        velocidadeInicial = velocidade;
    }

    void Projetil::lancar(sf::Vector2f posInicial, sf::Vector2f alvo)
    {
        setPosicao(posInicial);
        posicaoAlvo = alvo;

        sf::Vector2f direcao(
            alvo.x - posInicial.x,
            alvo.y - posInicial.y
        );

        float modulo = std::sqrt(direcao.x * direcao.x + direcao.y * direcao.y);

        if (modulo == 0.f)
        {
            modulo = 1.f;
        }

        direcao.x /= modulo;
        direcao.y /= modulo;

        vel.x = direcao.x * velocidadeInicial;
        vel.y = direcao.y * velocidadeInicial;

        ativo = true;
        lancado = true;
    }

    void Projetil::colidir(Personagens::Jogador* jogador)
    {
        if (!ativo || !jogador || !jogador->ativado())
        {
            return;
        }

        jogador->tirarVida(dano);
        desativar();
    }

    void Projetil::colidir(Estrutura* estrutura)
    {
        if (!ativo || !estrutura)
        {
            return;
        }

        desativar();
    }

    void Projetil::executar()
    {
        if (!ativo)
        {
            return;
        }

        aplicarGravidade();
        mover();
    }

    std::string Projetil::salvar()
    {
        salvarEntidade();

        buffer << dano << " ";
        buffer << velocidadeInicial << " ";
        buffer << posicaoAlvo.x << " ";
        buffer << posicaoAlvo.y << " ";
        buffer << lancado << " ";

        return buffer.str();
    }
}