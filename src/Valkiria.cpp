#include "../include/Valkiria.h"
#include "../include/Jogador.h"

namespace Entidades
{
    namespace Personagens
    {
        Valkiria::Valkiria() :
            Inimigo(),
            forcaEmpurraoBase(3.5f),
            forcaEmpurraoMaxima(7.0f),
            escalaX(1.0f),
            escalaY(1.0f)
        {
            id = Id::Valkiria;

            num_vidas = 4;

            danoBase = 1;
            danoMaximo = 4;

            nivel_maldade = 2;

            raioVisao = 320.f;
            raioAtaque = 55.f;

            velocidadeMovimento = 1.1f;
            velocidadeMaxima = 3.0f;

            intervaloAtaque = 1.2f;

            forma.setTexture(*pGG->getTextura(Texturas::valkiria));
            forma.setScale(escalaX, escalaY);

            setFigura(&forma);
        }

        Valkiria::Valkiria(sf::Vector2f pos) :
            Inimigo(pos),
            forcaEmpurraoBase(3.5f),
            forcaEmpurraoMaxima(7.0f),
            escalaX(1.0f),
            escalaY(1.0f)
        {
            id = Id::Valkiria;

            num_vidas = 4;

            danoBase = 1;
            danoMaximo = 4;

            nivel_maldade = 2;

            raioVisao = 320.f;
            raioAtaque = 55.f;

            velocidadeMovimento = 1.1f;
            velocidadeMaxima = 3.0f;

            intervaloAtaque = 1.2f;

            forma.setTexture(*pGG->getTextura(Texturas::valkiria));
            forma.setPosition(pos);
            forma.setScale(escalaX, escalaY);

            setFigura(&forma);
        }

        Valkiria::Valkiria(sf::Vector2f pos, Jogador* j1, Jogador* j2) :
            Inimigo(pos, j1, j2),
            forcaEmpurraoBase(3.5f),
            forcaEmpurraoMaxima(7.0f),
            escalaX(1.0f),
            escalaY(1.0f)
        {
            id = Id::Valkiria;

            num_vidas = 4;

            danoBase = 1;
            danoMaximo = 4;

            nivel_maldade = 2;

            raioVisao = 320.f;
            raioAtaque = 55.f;

            velocidadeMovimento = 1.1f;
            velocidadeMaxima = 3.0f;

            intervaloAtaque = 1.2f;

            forma.setTexture(*pGG->getTextura(Texturas::valkiria));
            forma.setPosition(pos);
            forma.setScale(escalaX, escalaY);

            setFigura(&forma);
        }

        Valkiria::~Valkiria()
        {}

        void Valkiria::empurrarJogador(Jogador* jogador)
        {
            if (!jogador)
            {
                return;
            }

            float forcaEmpurrao = forcaEmpurraoBase + static_cast<float>(nivel_maldade) * 0.5f;

            if (forcaEmpurrao > forcaEmpurraoMaxima)
            {
                forcaEmpurrao = forcaEmpurraoMaxima;
            }

            sf::Vector2f minhaPos = getCentro();
            sf::Vector2f posJogador = jogador->getCentro();

            sf::Vector2f velJogador = jogador->getVelocidade();

            if (posJogador.x < minhaPos.x)
            {
                velJogador.x = -forcaEmpurrao;
            }
            else
            {
                velJogador.x = forcaEmpurrao;
            }

            /*
                Pequeno impulso para cima.
                Isso dá sensação de pancada, mas sem exagerar.
            */
            velJogador.y = -2.0f;

            jogador->setVelocidade(velJogador);
        }

        void Valkiria::danificar(Jogador* jogador)
        {
            if (!jogador || !jogador->ativado() || !jogador->vivo())
            {
                return;
            }

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
            empurrarJogador(jogador);

            relogioAtaque.restart();
        }

        void Valkiria::executar()
        {
            if (!ativo)
            {
                return;
            }

            Inimigo::executar();
        }

        std::string Valkiria::salvar()
        {
            salvarInimigo();

            buffer << forcaEmpurraoBase << " ";
            buffer << forcaEmpurraoMaxima << " ";
            buffer << escalaX << " ";
            buffer << escalaY << " ";

            return buffer.str();
        }
    }
}