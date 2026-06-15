#include "../include/Runa.h"
#include "../include/Jogador.h"

namespace Entidades
{
    namespace Obstaculos
    {
        Runa::Runa() :
            Obstaculo(),
            tempoTravamento(2.0f),
            jogadorTravado(nullptr),
            travandoJogador(false),
            relogioTravamento()
        {
            id = Id::Runa;

            danoso = false;
            colidivel = false;

            forma.setTexture(*pGG->getTextura(Texturas::runa));
            setFigura(&forma);
        }

        Runa::Runa(sf::Vector2f pos) :
            Obstaculo(pos),
            tempoTravamento(2.0f),
            jogadorTravado(nullptr),
            travandoJogador(false),
            relogioTravamento()
        {
            id = Id::Runa;

            danoso = false;
            colidivel = false;

            forma.setTexture(*pGG->getTextura(Texturas::runa));
            forma.setPosition(pos);

            setFigura(&forma);
        }

        Runa::Runa(sf::Vector2f pos, sf::Vector2f tamanho) :
            Obstaculo(pos),
            tempoTravamento(2.0f),
            jogadorTravado(nullptr),
            travandoJogador(false),
            relogioTravamento()
        {
            id = Id::Runa;

            danoso = false;
            colidivel = false;

            forma.setTexture(*pGG->getTextura(Texturas::runa));
            forma.setPosition(pos);

            sf::FloatRect limites = forma.getLocalBounds();

            if (limites.width > 0.f && limites.height > 0.f)
            {
                forma.setScale(
                    tamanho.x / limites.width,
                    tamanho.y / limites.height
                );
            }

            setFigura(&forma);
        }

        Runa::~Runa()
        {
            if (jogadorTravado)
            {
                jogadorTravado->setTravado(false);
                jogadorTravado = nullptr;
            }
        }

        void Runa::executar()
        {
            /*
                A Runa é fixa.
                Não aplica gravidade nem movimento.

                Ela apenas controla o tempo de travamento do jogador.
            */

            if (travandoJogador && jogadorTravado)
            {
                if (relogioTravamento.getElapsedTime().asSeconds() >= tempoTravamento)
                {
                    jogadorTravado->setTravado(false);
                    jogadorTravado = nullptr;
                    travandoJogador = false;
                }
            }
        }

        void Runa::obstaculizar(Personagens::Jogador* jogador)
        {
            if (!jogador || !jogador->ativado())
            {
                return;
            }

            /*
                Se já tem alguém travado nessa Runa, não reinicia o tempo.
                Isso evita o jogador ficar preso para sempre caso continue em cima dela.
            */
            if (travandoJogador)
            {
                return;
            }

            jogadorTravado = jogador;
            jogadorTravado->setTravado(true);

            travandoJogador = true;
            relogioTravamento.restart();
        }

        std::string Runa::salvar()
        {
            salvarObstaculo();

            buffer << tempoTravamento << " ";
            buffer << travandoJogador << " ";

            if (jogadorTravado)
            {
                buffer << jogadorTravado->getIdUnico() << " ";
            }
            else
            {
                buffer << -1 << " ";
            }

            return buffer.str();
        }
    }
}