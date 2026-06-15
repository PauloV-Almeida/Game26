#include "../include/EspinhoVenenoso.h"
#include "../include/Jogador.h"

namespace Entidades
{
    namespace Obstaculos
    {
        EspinhoVenenoso::EspinhoVenenoso() :
            Obstaculo(),
            danoContato(1),
            danoVeneno(1),
            tempoVeneno(1.0f),
            venenoAtivo(false),
            relogioVeneno(),
            relogioDanoContato(),
            intervaloDanoContato(0.8f)
        {
            id = Id::Espinho;

            danoso = true;
            colidivel = true;

            forma.setTexture(*pGG->getTextura(Texturas::espinho));
            setFigura(&forma);
        }

        EspinhoVenenoso::EspinhoVenenoso(sf::Vector2f pos) :
            Obstaculo(pos),
            danoContato(1),
            danoVeneno(1),
            tempoVeneno(1.0f),
            venenoAtivo(false),
            relogioVeneno(),
            relogioDanoContato(),
            intervaloDanoContato(0.8f)
        {
            id = Id::Espinho;

            danoso = true;
            colidivel = true;

            forma.setTexture(*pGG->getTextura(Texturas::espinho));
            forma.setPosition(pos);

            setFigura(&forma);
        }

        EspinhoVenenoso::EspinhoVenenoso(sf::Vector2f pos, sf::Vector2f tamanho) :
            Obstaculo(pos),
            danoContato(1),
            danoVeneno(1),
            tempoVeneno(1.0f),
            venenoAtivo(false),
            relogioVeneno(),
            relogioDanoContato(),
            intervaloDanoContato(0.8f)
        {
            id = Id::Espinho;

            danoso = true;
            colidivel = true;

            forma.setTexture(*pGG->getTextura(Texturas::espinho));
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

        EspinhoVenenoso::~EspinhoVenenoso()
        {}

        void EspinhoVenenoso::executar()
        {
            /*
                Espinho é fixo.
                Não aplica gravidade e não move.

                O dano de veneno é controlado no obstaculizar(),
                porque ele depende do contato com o jogador.
            */
        }

        void EspinhoVenenoso::obstaculizar(Personagens::Jogador* jogador)
        {
            if (!jogador || !jogador->ativado())
            {
                return;
            }

            /*
                Dano de contato:
                Enquanto o jogador estiver colidindo com o espinho,
                ele pode tomar dano, mas com intervalo para não perder
                toda a vida em poucos frames.
            */
            if (relogioDanoContato.getElapsedTime().asSeconds() >= intervaloDanoContato)
            {
                jogador->tirarVida(danoContato);
                relogioDanoContato.restart();

                /*
                    Ativa o veneno.
                    A lógica do veneno fica aqui, como você pediu.
                */
                venenoAtivo = true;
                relogioVeneno.restart();
            }

            /*
                Veneno:
                Depois de 1 segundo do contato, aplica mais 1 de dano
                e desativa o veneno.
            */
            if (venenoAtivo && relogioVeneno.getElapsedTime().asSeconds() >= tempoVeneno)
            {
                jogador->tirarVida(danoVeneno);
                venenoAtivo = false;
            }
        }

        std::string EspinhoVenenoso::salvar()
        {
            salvarObstaculo();

            buffer << danoContato << " ";
            buffer << danoVeneno << " ";
            buffer << tempoVeneno << " ";
            buffer << venenoAtivo << " ";

            return buffer.str();
        }
    }
}