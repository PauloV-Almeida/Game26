#include "../include/Projetil.h"
#include "../include/Jogador.h"
#include "../include/Estrutura.h"

#include <cmath>

namespace Entidades
{
    Projetil::Projetil() :
        Entidade(),
        dano(2),
        veloProjetil(6),
        lancado(false),
        posicaoAlvo(0.f, 0.f)
    {
        id = Id::Projetil;

        setAtivo(false);
        setVelocidade(0.f, 0.f);

        forma.setTexture(*pGG->getTextura(Texturas::projetil));
        forma.setTextureRect(sf::IntRect(0, 0, 64, 64));
        forma.setScale(1.f, 1.f);

        setFigura(&forma);
    }

    Projetil::Projetil(sf::Vector2f pos) :
        Entidade(pos),
        dano(2),
        veloProjetil(6),
        lancado(false),
        posicaoAlvo(0.f, 0.f)
    {
        id = Id::Projetil;

        setAtivo(false);
        setVelocidade(0.f, 0.f);

        forma.setTexture(*pGG->getTextura(Texturas::projetil));
        forma.setTextureRect(sf::IntRect(0, 0, 64, 64));
        forma.setScale(1.f, 1.f);

        setFigura(&forma);
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
        dano = danoBase;
    }

    void Projetil::setVelocidadeInicial(int velocidade)
    {
        veloProjetil = velocidade;
    }

    void Projetil::lancar(sf::Vector2f origem, sf::Vector2f alvo, int aumentoVelo)
    {
        if (lancado)
        {
            return;
        }

        setAtivo(true);
        lancado = true;

        setPosicao(origem.x, origem.y);
        posicaoAlvo = alvo;

        /*
            Movimento de ensino superior:
            O projétil é lançado com velocidade inicial e depois sofre gravidade.
            Isso gera trajetória parabólica.
        */

        float dx = alvo.x - origem.x;

        float velocidadeX = 0.f;

        if (dx > 0.f)
        {
            velocidadeX = static_cast<float>(veloProjetil + aumentoVelo);
        }
        else
        {
            velocidadeX = -static_cast<float>(veloProjetil + aumentoVelo);
        }

        /*
            Velocidade inicial vertical negativa:
            em SFML, Y negativo sobe.
            Depois aplicarGravidade() faz ele cair.
        */
        float velocidadeY = -10.f - static_cast<float>(aumentoVelo) * 0.4f;

        setVelocidade(velocidadeX, velocidadeY);
    }

    void Projetil::colidir(Personagens::Jogador* jogador)
    {
        if (!jogador || !lancado || !ativado())
        {
            return;
        }

        jogador->tiraVida(dano);

        lancado = false;
        setAtivo(false);
        setVelocidade(0.f, 0.f);
    }

    void Projetil::colidir(Estrutura* estrutura)
    {
        if (!estrutura || !lancado || !ativado())
        {
            return;
        }

        lancado = false;
        setAtivo(false);
        setVelocidade(0.f, 0.f);
    }

    void Projetil::executar()
    {
        if (!ativado() || !lancado)
        {
            return;
        }

        aplicarGravidade();
        mover();
    }

    void Projetil::salvarDataBuffer()
    {
        Entidade::salvarDataBuffer();

        buffer << dano << " ";
        buffer << veloProjetil << " ";
        buffer << posicaoAlvo.x << " ";
        buffer << posicaoAlvo.y << " ";
        buffer << lancado << " ";
    }

    std::string Projetil::salvar()
    {
        salvarDataBuffer();
        return buffer.str();
    }
}