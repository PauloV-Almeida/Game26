#include "../include/Andarilho.h"
#include "../include/Jogador.h"

namespace Entidades
{
    namespace Personagens
    {
        Andarilho::Andarilho() :
            Inimigo(),
            escalaX(1.0f),
            escalaY(1.0f)
        {
            id = Id::Andarilho;

            num_vidas = 2;

            danoBase = 1;
            danoMaximo = 3;

            nivel_maldade = 1;

            raioVisao = 260.f;
            raioAtaque = 45.f;

            velocidadeMovimento = 0.8f;
            velocidadeMaxima = 2.0f;

            intervaloAtaque = 1.0f;

            forma.setTexture(*pGG->getTextura(Texturas::andarilho));
            forma.setScale(escalaX, escalaY);

            setFigura(&forma);
        }

        Andarilho::Andarilho(sf::Vector2f pos) :
            Inimigo(pos),
            escalaX(1.0f),
            escalaY(1.0f)
        {
            id = Id::Andarilho;

            num_vidas = 2;

            danoBase = 1;
            danoMaximo = 3;

            nivel_maldade = 1;

            raioVisao = 260.f;
            raioAtaque = 45.f;

            velocidadeMovimento = 0.8f;
            velocidadeMaxima = 2.0f;

            intervaloAtaque = 1.0f;

            forma.setTexture(*pGG->getTextura(Texturas::andarilho));
            forma.setPosition(pos);
            forma.setScale(escalaX, escalaY);

            setFigura(&forma);
        }

        Andarilho::Andarilho(sf::Vector2f pos, Jogador* j1, Jogador* j2) :
            Inimigo(pos, j1, j2),
            escalaX(1.0f),
            escalaY(1.0f)
        {
            id = Id::Andarilho;

            num_vidas = 2;

            danoBase = 1;
            danoMaximo = 3;

            nivel_maldade = 1;

            raioVisao = 260.f;
            raioAtaque = 45.f;

            velocidadeMovimento = 0.8f;
            velocidadeMaxima = 2.0f;

            intervaloAtaque = 1.0f;

            forma.setTexture(*pGG->getTextura(Texturas::andarilho));
            forma.setPosition(pos);
            forma.setScale(escalaX, escalaY);

            setFigura(&forma);
        }

        Andarilho::~Andarilho()
        {}

        void Andarilho::danificar(Jogador* jogador)
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

            relogioAtaque.restart();
        }

        void Andarilho::executar()
        {
            if (!ativo)
            {
                return;
            }

            /*
                Usa o comportamento padrão do Inimigo:
                - escolhe alvo
                - persegue se estiver no raio de visão
                - anda aleatório se não tiver alvo
                - aplica gravidade
                - move
            */
            Inimigo::executar();
        }

        std::string Andarilho::salvar()
        {
            salvarInimigo();

            buffer << escalaX << " ";
            buffer << escalaY << " ";

            return buffer.str();
        }
    }
}