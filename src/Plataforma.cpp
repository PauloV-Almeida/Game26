#include "../include/Plataforma.h"
#include "../include/Jogador.h"
#include "../include/Inimigo.h"

namespace Entidades
{
    namespace Obstaculos
    {
        Plataforma::Plataforma(sf::Vector2f pos, bool veri) :
            Obstaculo(11, pos),
            pVerifica(veri)
        {
            if (pVerifica)
                corpo.setFillColor(sf::Color::Cyan);
            else
            {
                texturas = pGG->carregar_texturas("./assets/obstaculo3.png");
                corpo.setTexture(texturas);
            }
        }
        Plataforma:: ~Plataforma()
        {

        }
        void Plataforma::executar()
        {
            mover();
        }
        void Plataforma::mover()
        {
            if (pVerifica)
            {
                // plataforma móvel: aplica gravidade/movimento
                vel.y += GRAVIDADE;
                if (deCastigo)
                {
                    vel.y -= GRAVIDADE;
                }
                corpo.setPosition(corpo.getPosition() + vel);
            }
            else
            {
                // plataforma fixa: garante velocidade zero (não cai)
                vel = sf::Vector2f(0.f, 0.f);
            }
        }
        void Plataforma::obstaculizar(Entidade* outro, std::string direcao)
        {
        }
    }
}