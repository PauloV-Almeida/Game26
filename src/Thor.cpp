#include "../include/Thor.h"
#include "../include/Jogador.h"

namespace Entidades
{
    namespace Personagens
    {
        Thor::Thor() :
            Inimigo(),
            projetilAtual(nullptr),
            raioDisparo(420.f),
            intervaloDisparo(2.0f),
            velocidadeProjetil(7.0f),
            danoProjetil(3),
            relogioDisparo(),
            escalaX(1.0f),
            escalaY(1.0f)
        {
            id = Id::Thor;

            num_vidas = 12;

            danoBase = 2;
            danoMaximo = 6;

            nivel_maldade = 3;

            raioVisao = 500.f;
            raioAtaque = 60.f;

            velocidadeMovimento = 0.9f;
            velocidadeMaxima = 2.5f;

            intervaloAtaque = 1.2f;

            forma.setTexture(*pGG->getTextura(Texturas::thor));
            forma.setScale(escalaX, escalaY);

            setFigura(&forma);
        }

        Thor::Thor(sf::Vector2f pos) :
            Inimigo(pos),
            projetilAtual(nullptr),
            raioDisparo(420.f),
            intervaloDisparo(2.0f),
            velocidadeProjetil(7.0f),
            danoProjetil(3),
            relogioDisparo(),
            escalaX(1.0f),
            escalaY(1.0f)
        {
            id = Id::Thor;

            num_vidas = 12;

            danoBase = 2;
            danoMaximo = 6;

            nivel_maldade = 3;

            raioVisao = 500.f;
            raioAtaque = 60.f;

            velocidadeMovimento = 0.9f;
            velocidadeMaxima = 2.5f;

            intervaloAtaque = 1.2f;

            forma.setTexture(*pGG->getTextura(Texturas::thor));
            forma.setPosition(pos);
            forma.setScale(escalaX, escalaY);

            setFigura(&forma);
        }

        Thor::Thor(sf::Vector2f pos, Jogador* j1, Jogador* j2) :
            Inimigo(pos, j1, j2),
            projetilAtual(nullptr),
            raioDisparo(420.f),
            intervaloDisparo(2.0f),
            velocidadeProjetil(7.0f),
            danoProjetil(3),
            relogioDisparo(),
            escalaX(1.0f),
            escalaY(1.0f)
        {
            id = Id::Thor;

            num_vidas = 12;

            danoBase = 2;
            danoMaximo = 6;

            nivel_maldade = 3;

            raioVisao = 500.f;
            raioAtaque = 60.f;

            velocidadeMovimento = 0.9f;
            velocidadeMaxima = 2.5f;

            intervaloAtaque = 1.2f;

            forma.setTexture(*pGG->getTextura(Texturas::thor));
            forma.setPosition(pos);
            forma.setScale(escalaX, escalaY);

            setFigura(&forma);
        }

        Thor::~Thor()
        {
            /*
                Atenção:
                Se o projetilAtual estiver dentro da ListaEntidades,
                quem deve deletar é a ListaEntidades.

                Por isso aqui só limpamos o ponteiro.
            */
            projetilAtual = nullptr;
        }

        Projetil* Thor::getProjetilAtual() const
        {
            return projetilAtual;
        }

        void Thor::setProjetilAtual(Projetil* projetil)
        {
            projetilAtual = projetil;
        }

        void Thor::setVelocidadeProjetil(float velocidade)
        {
            if (velocidade < 0.f)
            {
                velocidade = 0.f;
            }

            velocidadeProjetil = velocidade;
        }

        void Thor::setDanoProjetil(int dano)
        {
            if (dano < 0)
            {
                dano = 0;
            }

            danoProjetil = dano;
        }

        bool Thor::podeDisparar()
        {
            return relogioDisparo.getElapsedTime().asSeconds() >= intervaloDisparo;
        }

        void Thor::dispararProjetil(Jogador* jogador)
        {
            if (!jogador || !jogador->ativado() || !jogador->vivo())
            {
                return;
            }

            if (!podeDisparar())
            {
                return;
            }

            /*
                O projétil mira na posição atual do jogador.
                Depois disso, ele não persegue mais.
            */
            sf::Vector2f posInicial = getCentro();
            sf::Vector2f posAlvo = jogador->getCentro();

            if (!projetilAtual)
            {
                projetilAtual = new Projetil(
                    posInicial,
                    posAlvo,
                    velocidadeProjetil,
                    danoProjetil
                );
            }
            else
            {
                projetilAtual->setDano(danoProjetil);
                projetilAtual->setVelocidadeInicial(velocidadeProjetil);
                projetilAtual->lancar(posInicial, posAlvo);
            }

            relogioDisparo.restart();
        }

        void Thor::danificar(Jogador* jogador)
        {
            if (!jogador || !jogador->ativado() || !jogador->vivo())
            {
                return;
            }

            /*
                Ataque corpo a corpo:
                só acontece se o jogador estiver bem perto.
            */
            if (!jogadorNoRaioAtaque(jogador))
            {
                return;
            }

            if (!podeAtacar())
            {
                return;
            }

            int danoAtual = calcularDanoAtual();

            jogador->tirarVida(danoAtual);

            relogioAtaque.restart();
        }

        void Thor::executar()
        {
            if (!ativo)
            {
                return;
            }

            Jogador* alvo = escolherAlvo();

            if (alvo)
            {
                float distancia = calcularDistancia(alvo);

                /*
                    Se estiver perto, Thor persegue e o GerenciadorColisao
                    chama danificar(jogador) quando houver colisão.

                    Se estiver em distância média/longe, ele pode lançar projétil.
                */
                if (distancia <= raioVisao)
                {
                    perseguir(alvo);

                    if (distancia > raioAtaque && distancia <= raioDisparo)
                    {
                        dispararProjetil(alvo);
                    }
                }
                else
                {
                    andarAleatorio();
                }
            }
            else
            {
                andarAleatorio();
            }

            atualizarFisica();

            if (projetilAtual && projetilAtual->ativado())
            {
                projetilAtual->executar();
            }
        }

        std::string Thor::salvar()
        {
            salvarInimigo();

            buffer << raioDisparo << " ";
            buffer << intervaloDisparo << " ";
            buffer << velocidadeProjetil << " ";
            buffer << danoProjetil << " ";
            buffer << escalaX << " ";
            buffer << escalaY << " ";

            return buffer.str();
        }
    }
}