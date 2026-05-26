#include "../include/Valkiria.h"

namespace Entidades
{
    namespace Personagens
    {
        Valkiria::Valkiria(
            int indice,
            sf::Vector2f pos,
            sf::Vector2f velo,
            sf::Vector2f tam,
            Jogador* pJ1,
            Jogador* pJ2
        ) :
            Inimigo(indice, pos, velo, tam, pJ1, pJ2),
            tamanho(static_cast<int>(tam.x))
        {
            dano_base = 1;
            dano = dano_base;
            n_vidas = 5;

            texturas = pGG->carregar_texturas("./assets/valkiria.png");
            corpo.setTexture(texturas);
        }

        Valkiria::~Valkiria()
        {}

        void Valkiria::executar()
        {
            if (n_vidas <= 0)
            {
                vivo = false;
                return;
            }

            mover();
        }

        void Valkiria::danificar(Jogador* pJog)
        {
            if (!pJog || !pJog->get_vivo())
            {
                return;
            }

            if (!jogadorNoRaioAtaque(pJog))
            {
                return;
            }

            aumentarMaldade();

            sf::Vector2f velJog = pJog->get_vel();

            float empurrao = EMPURRAO_BASE + static_cast<float>(nivel_maldade) * 0.7f;

            if (empurrao > EMPURRAO_MAX)
            {
                empurrao = EMPURRAO_MAX;
            }

            sf::Vector2f posIni = get_posicao();
            sf::Vector2f posJog = pJog->get_posicao();

            if (posJog.x < posIni.x)
            {
                velJog.x = -empurrao;
            }
            else
            {
                velJog.x = empurrao;
            }

            /*
                Pequeno impulso vertical para dar sensação de impacto,
                mas sem jogar longe demais.
            */
            if (velJog.y > -2.0f)
            {
                velJog.y = -2.0f;
            }

            pJog->set_vel(velJog);
        }

        void Valkiria::salvarDataBuffer()
        {
            Inimigo::salvarDataBuffer();

            bufferSalvar
                << "Valkiria" << ' '
                << tamanho << '\n';
        }

        void Valkiria::salvar(std::ostream& out)
        {
            salvarDataBuffer();
            out << getBufferSalvar();
        }
    }
}