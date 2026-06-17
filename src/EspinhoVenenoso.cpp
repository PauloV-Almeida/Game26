#include "../include/EspinhoVenenoso.h"
#include "../include/Jogador.h"

namespace Entidades
{
    namespace Obstaculos
    {
        EspinhoVenenoso::EspinhoVenenoso() :
            Obstaculo(),
            dano(1),
            intervaloDano(0.8f),
            relogioDano()
        {
            id = Id::Espinho;

            danoso = true;
            colidivel = true;

            forma.setTexture(*pGG->getTextura(Texturas::espinho));
            setFigura(&forma);
        }

        EspinhoVenenoso::EspinhoVenenoso(sf::Vector2f pos) :
            Obstaculo(pos),
            dano(1),
            intervaloDano(0.8f),
            relogioDano()
        {
            id = Id::Espinho;

            danoso = true;
            colidivel = true;

            forma.setTexture(*pGG->getTextura(Texturas::espinho));
            setPosicao(pos.x, pos.y);

            setFigura(&forma);
        }

        EspinhoVenenoso::EspinhoVenenoso(sf::Vector2f pos, sf::Vector2f tamanho) :
            Obstaculo(pos),
            dano(1),
            intervaloDano(0.8f),
            relogioDano()
        {
            id = Id::Espinho;

            danoso = true;
            colidivel = true;

            forma.setTexture(*pGG->getTextura(Texturas::espinho));
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

        EspinhoVenenoso::~EspinhoVenenoso()
        {}

        void EspinhoVenenoso::executar()
        {
            if (!ativo)
            {
                return;
            }

            atualizarFisicaObstaculo();
        }

        void EspinhoVenenoso::obstaculizar(Personagens::Jogador* jogador)
        {
            if (!jogador || !jogador->ativado())
            {
                return;
            }

            if (relogioDano.getElapsedTime().asSeconds() >= intervaloDano)
            {
                jogador->tiraVida(dano);
                relogioDano.restart();
            }
        }

        void EspinhoVenenoso::salvarDataBuffer()
        {
            Obstaculo::salvarDataBuffer();

            buffer << dano << " ";
            buffer << intervaloDano << " ";
        }

        std::string EspinhoVenenoso::salvar()
        {
            salvarDataBuffer();
            return buffer.str();
        }
    }
}