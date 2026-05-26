#include "../include/Personagem.h"

namespace Entidades
{
    namespace Personagens
    {
        Personagem::Personagem(int indice, sf::Vector2f pos, sf::Vector2f vel, sf::Vector2f tam) :
            Entidade::Entidade(indice, vel),
            corpo(tam),
            vivo(true),
            n_vidas(1),
            noChao(false)
        {
            corpo.setOrigin(corpo.getSize() / 2.f);
            corpo.setPosition(pos);
        }

        Personagem::~Personagem()
        {}

        void Personagem::desenhar()
        {
            if (vivo)
            {
                pGG->desenhar(&corpo);
            }
        }

        void Personagem::salvarDataBuffer()
        {
            limparBufferSalvar();

            bufferSalvar
                << id << ' '
                << get_posicao().x << ' '
                << get_posicao().y << ' '
                << get_tamanho().x << ' '
                << get_tamanho().y << ' '
                << get_vel().x << ' '
                << get_vel().y << ' '
                << n_vidas << ' '
                << vivo << ' '
                << dano << ' ';
        }
    }
}