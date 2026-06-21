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
            jaAtivada(false),
            relogioTravamento()
        {
            id = Id::Runa;

            danoso = false;
            colidivel = true;

            forma.setTexture(*pGG->getTextura(Texturas::runa));
            setFigura(&forma);
        }

        Runa::Runa(sf::Vector2f pos) :
            Obstaculo(pos),
            tempoTravamento(2.0f),
            jogadorTravado(nullptr),
            travandoJogador(false),
            jaAtivada(false),
            relogioTravamento()
        {
            id = Id::Runa;

            danoso = false;
            colidivel = true;

            forma.setTexture(*pGG->getTextura(Texturas::runa));
            setPosicao(pos.x, pos.y);

            setFigura(&forma);
        }

        Runa::Runa(sf::Vector2f pos, sf::Vector2f tamanho) :
            Obstaculo(pos),
            tempoTravamento(2.0f),
            jogadorTravado(nullptr),
            travandoJogador(false),
            jaAtivada(false),
            relogioTravamento()
        {
            id = Id::Runa;

            danoso = false;
            colidivel = true;

            forma.setTexture(*pGG->getTextura(Texturas::runa));
            setPosicao(pos.x, pos.y);

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
            if (!ativado())
            {
                return;
            }

            atualizarFisicaObstaculo();

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
                Só ativa uma vez.
                Depois de travar por 2 segundos, a runa não trava de novo.
            */
            if (jaAtivada || travandoJogador)
            {
                return;
            }

            jogadorTravado = jogador;
            jogadorTravado->setTravado(true);

            travandoJogador = true;
            jaAtivada = true;

            relogioTravamento.restart();
        }

        void Runa::salvarDataBuffer()
        {
            Obstaculo::salvarDataBuffer();

            buffer << tempoTravamento << " ";
            buffer << travandoJogador << " ";
            buffer << jaAtivada << " ";

            if (jogadorTravado)
            {
                buffer << jogadorTravado->getIdUnico() << " ";
            }
            else
            {
                buffer << -1 << " ";
            }
        }

        std::string Runa::salvar()
        {
            salvarDataBuffer();
            return buffer.str();
        }
    }
}