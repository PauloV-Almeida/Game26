#include "../include/Obstaculo.h"

namespace Entidades
{
    namespace Obstaculos
    {
        Obstaculo::Obstaculo(int indice, sf::Vector2f pos, sf::Vector2f tam) :
            Entidade::Entidade(indice, sf::Vector2f(0.f, 0.f)),
            corpo(tam),
            existir(true),
            danoso(false)
        {
            corpo.setOrigin(corpo.getSize() / 2.f);
            corpo.setPosition(pos);
        }

        Obstaculo::~Obstaculo()
        {}

        void Obstaculo::desenhar()
        {
            if (get_vivo())
            {
                pGG->desenhar(&corpo);
            }
        }

        void Obstaculo::mover()
        {
            vel.y += GRAVIDADE;
            corpo.setPosition(corpo.getPosition() + vel);
        }

        void Obstaculo::salvarDataBuffer()
        {
            limparBufferSalvar();

            bufferSalvar
                << id << ' '
                << get_posicao().x << ' '
                << get_posicao().y << ' '
                << get_tamanho().x << ' '
                << get_tamanho().y << ' '
                << existir << ' '
                << danoso << ' ';
        }
    }
}