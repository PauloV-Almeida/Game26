#include "../include/Plataforma.h"

namespace Entidades
{
    namespace Obstaculos
    {
        Plataforma::Plataforma(int indice, sf::Vector2f pos, sf::Vector2f tam) :
            Obstaculo(indice, pos, tam),
            altura(static_cast<int>(tam.y))
        {
            danoso = false;

            texturas = pGG->carregar_texturas("./assets/plataforma_gelo.png");
            corpo.setTexture(texturas);
        }

        Plataforma::~Plataforma()
        {}

        void Plataforma::executar()
        {
            // Plataforma fixa. Não precisa mover.
        }

        void Plataforma::obstaculizar(Entidades::Entidade* outro, std::string direcao)
        {
            if (!outro || !outro->get_vivo())
            {
                return;
            }

            sf::Vector2f vel = outro->get_vel();

            Entidades::Personagens::Personagem* personagem =
                dynamic_cast<Entidades::Personagens::Personagem*>(outro);

            if (direcao == "Embaixo")
            {
                vel.y = 0.0f;

                if (personagem)
                {
                    personagem->set_noChao(true);
                }

                /*
                    Efeito de gelo:
                    se a entidade já está se movendo na horizontal,
                    ela escorrega mais um pouco.
                */
                vel.x *= ESCORREGAMENTO_GELO;

                if (vel.x > VELOCIDADE_MAX_GELO)
                {
                    vel.x = VELOCIDADE_MAX_GELO;
                }
                else if (vel.x < -VELOCIDADE_MAX_GELO)
                {
                    vel.x = -VELOCIDADE_MAX_GELO;
                }
            }
            else if (direcao == "Emcima" || direcao == "Cima")
            {
                vel.y = 0.0f;
            }
            else if (direcao == "Esquerda" || direcao == "Direita")
            {
                vel.x = 0.0f;
            }

            outro->set_vel(vel);
        }

        void Plataforma::salvarDataBuffer()
        {
            Obstaculo::salvarDataBuffer();

            bufferSalvar
                << "Plataforma" << ' '
                << altura << '\n';
        }

        void Plataforma::salvar(std::ostream& out)
        {
            salvarDataBuffer();
            out << getBufferSalvar();
        }
    }
}