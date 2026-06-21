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
        posicaoAlvo(0.f, 0.f),
        pThor(nullptr),
        tempoSemColisao(0.15f)
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
        posicaoAlvo(0.f, 0.f),
        pThor(nullptr),
        tempoSemColisao(0.15f)
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

    bool Projetil::podeColidir() const
    {
        return relogioLancamento.getElapsedTime().asSeconds() >= tempoSemColisao;
    }

    int Projetil::getDano() const
    {
        return dano;
    }

    bool Projetil::foiLancado() const
    {
        return lancado;
    }

    void Projetil::setLancado(bool estado)
    {
        lancado = estado;
    }

    void Projetil::setPosicaoAlvo(sf::Vector2f alvo)
    {
        posicaoAlvo = alvo;
    }

    sf::Vector2f Projetil::getPosicaoAlvo() const
    {
        return posicaoAlvo;
    }

    void Projetil::setThor(Personagens::Thor* thor)
    {
        pThor = thor;
    }

    Personagens::Thor* Projetil::getThor() const
    {
        return pThor;
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

        posicaoAlvo = alvo;

        /*
            Ajusta para o centro do sprite ficar na origem,
            em vez do canto superior esquerdo nascer no centro do Thor.
        */
        sf::FloatRect limites = forma.getGlobalBounds();

        setPosicao(
            origem.x - limites.width / 2.f,
            origem.y - limites.height / 2.f - 20.f
        );

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

        float velocidadeY = -10.f - static_cast<float>(aumentoVelo) * 0.4f;

        setVelocidade(velocidadeX, velocidadeY);

        relogioLancamento.restart();
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