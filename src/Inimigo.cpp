#include "../include/Inimigo.h"

#include <cmath>
#include <cstdlib>

namespace Entidades
{
    namespace Personagens
    {
        Inimigo::Inimigo(
            int indice,
            sf::Vector2f pos,
            sf::Vector2f velo,
            sf::Vector2f tam,
            Jogador* pJ1,
            Jogador* pJ2
        ) :
            Personagem(indice, pos, velo, tam),
            nivel_maldade(0),
            dano_base(1),
            pJog1(pJ1),
            pJog2(pJ2),
            direcaoAleatoria(1),
            tempoTrocaDirecao(0)
        {
            dano = dano_base;
        }

        Inimigo::~Inimigo()
        {
            pJog1 = nullptr;
            pJog2 = nullptr;
        }

        void Inimigo::aplicarGravidade()
        {
            if (!noChao)
            {
                vel.y += GRAVIDADE;
            }
        }

        void Inimigo::limitarVelocidade()
        {
            if (vel.x > VEL_MAX_INI)
            {
                vel.x = VEL_MAX_INI;
            }
            else if (vel.x < -VEL_MAX_INI)
            {
                vel.x = -VEL_MAX_INI;
            }
        }

        void Inimigo::aumentarMaldade()
        {
            if (nivel_maldade < NIVEL_MALDADE_MAX)
            {
                nivel_maldade++;
            }

            dano = calcularDanoAtual();
        }

        int Inimigo::calcularDanoAtual() const
        {
            return dano_base + nivel_maldade;
        }

        Jogador* Inimigo::escolherAlvo()
        {
            const bool j1Valido = pJog1 && pJog1->get_vivo();
            const bool j2Valido = pJog2 && pJog2->get_vivo();

            if (!j1Valido && !j2Valido)
            {
                return nullptr;
            }

            if (j1Valido && !j2Valido)
            {
                return pJog1;
            }

            if (!j1Valido && j2Valido)
            {
                return pJog2;
            }

            sf::Vector2f posIni = get_posicao();

            sf::Vector2f pos1 = pJog1->get_posicao();
            sf::Vector2f pos2 = pJog2->get_posicao();

            float dist1 =
                std::fabs(posIni.x - pos1.x) +
                std::fabs(posIni.y - pos1.y);

            float dist2 =
                std::fabs(posIni.x - pos2.x) +
                std::fabs(posIni.y - pos2.y);

            if (dist1 <= dist2)
            {
                return pJog1;
            }

            return pJog2;
        }

        bool Inimigo::jogadorNoRaioPerseguicao(Jogador* pJog)
        {
            if (!pJog)
            {
                return false;
            }

            sf::Vector2f posIni = get_posicao();
            sf::Vector2f posJog = pJog->get_posicao();

            return std::fabs(posIni.x - posJog.x) <= RAIO_PERSEGUIR_X &&
                std::fabs(posIni.y - posJog.y) <= RAIO_PERSEGUIR_Y;
        }

        bool Inimigo::jogadorNoRaioAtaque(Jogador* pJog)
        {
            if (!pJog)
            {
                return false;
            }

            sf::Vector2f posIni = get_posicao();
            sf::Vector2f posJog = pJog->get_posicao();

            return std::fabs(posIni.x - posJog.x) <= RAIO_ATAQUE_X &&
                std::fabs(posIni.y - posJog.y) <= RAIO_ATAQUE_Y;
        }

        void Inimigo::andarAleatorio()
        {
            tempoTrocaDirecao++;

            if (tempoTrocaDirecao > 90)
            {
                tempoTrocaDirecao = 0;

                int r = std::rand() % 100;

                if (r < 45)
                {
                    direcaoAleatoria = -1;
                }
                else if (r < 90)
                {
                    direcaoAleatoria = 1;
                }
                else
                {
                    direcaoAleatoria = 0;
                }
            }

            if (direcaoAleatoria < 0)
            {
                vel.x -= 0.08f;
            }
            else if (direcaoAleatoria > 0)
            {
                vel.x += 0.08f;
            }
            else
            {
                vel.x *= 0.8f;
            }
        }

        void Inimigo::perseguir(Jogador* pJog)
        {
            if (!pJog)
            {
                return;
            }

            sf::Vector2f posIni = get_posicao();
            sf::Vector2f posJog = pJog->get_posicao();

            if (posJog.x < posIni.x)
            {
                vel.x -= 0.12f;
            }
            else if (posJog.x > posIni.x)
            {
                vel.x += 0.12f;
            }
        }

        void Inimigo::mover()
        {
            if (!vivo)
            {
                return;
            }

            aplicarGravidade();

            Jogador* alvo = escolherAlvo();

            if (alvo && jogadorNoRaioPerseguicao(alvo))
            {
                perseguir(alvo);
            }
            else
            {
                andarAleatorio();
            }

            limitarVelocidade();

            corpo.move(vel.x, vel.y);

            noChao = false;
        }

        void Inimigo::salvarDataBuffer()
        {
            Personagem::salvarDataBuffer();

            bufferSalvar
                << nivel_maldade << ' '
                << dano_base << ' ';
        }
    }
}